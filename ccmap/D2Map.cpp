#include "D2Map.h"

#define D2_DIR L"C:\\Users\\dell\\Documents\\Diablo II 1.12\\"
d2client_struct D2Client;

VOID __stdcall ExceptionHandler(VOID);
DWORD D2ClientInterface(VOID);
DWORD D2LAUNCH_QueryInterface(VOID);

Level* __fastcall GetLevel(ActMisc *misc, DWORD levelno)
{
	for(Level *pLevel = misc->pLevelFirst; pLevel; pLevel = pLevel->pNextLevel)
		if (pLevel->dwLevelNo == levelno)
			return pLevel;

	return D2COMMON_GetLevel(misc, levelno);
}

VOID __declspec(naked) D2CLIENT_InitGameMisc(VOID)
{
   __asm
   {
      PUSH ECX
      PUSH EBP
      PUSH ESI
      PUSH EDI
      JMP D2CLIENT_InitGameMisc_I
      RETN
   }
}

DWORD D2ClientInterface(VOID)
{
	return D2Client.dwInit;
}

VOID __stdcall ExceptionHandler(VOID)
{
	printf("] We got a big Error here! [\n");
	ExitProcess(NULL);
}

VOID __fastcall D2OpenFile(CHAR* szFile)
{
	printf("Loading: %s\n",szFile);
}
	
DWORD dwJmpBck = 0x6FD59900+6;
VOID __declspec(naked) D2OpenFile_ASM()
{
	__asm
	{
		PUSH ECX
		PUSH EBP
		MOV EBP, DWORD PTR SS:[ESP+0x10]

		PUSHAD
		MOV ECX, EAX
		CALL D2OpenFile
		POPAD
		JMP dwJmpBck
	}
}

extern "C" {
    
    __declspec(dllexport) void __stdcall GetMap(int seed, int act, int level, char* value)
    {
		//0x1B8E7001 test map seed

        BYTE bActLevels[] = {1, 40, 75, 103, 109, 137};
        
        Act* pAct = D2COMMON_LoadAct(act, seed, 1, 1, 1, NULL, NULL, D2CLIENT_LoadAct_1, D2CLIENT_LoadAct_2);
        
        if (pAct)
        {
            Level* pLevel = GetLevel(pAct->pMisc, level); // Loading Town Level
            
            if (!pLevel)
			{
				return;
			}
          
            if (!pLevel->pRoom2First) 
			{
				D2COMMON_InitLevel(pLevel);
			}

            if (!pLevel->pRoom2First)
			{
				return;
			}

            CCollisionMap cMap;
            cMap.CreateMap(pAct, pLevel->dwLevelNo);

			if (cMap.Export(value)) 
			{
				//return value;
				return;
			}

			return;
        }
		return;
    }

	__declspec(dllexport) void __stdcall Init()
    {
        memset(&D2Client, NULL, sizeof(d2client_struct));

        SetCurrentDirectory(D2_DIR);
        DefineOffsets();
        InstallPatchs();

        D2Client.dwInit = 1;
        D2Client.fpInit = (DWORD)D2ClientInterface;
        
        FOG_10021("D2");
        FOG_10019("D2", (DWORD)ExceptionHandler, "D2", 1);
        FOG_10101(1, NULL);
        FOG_10089(1);
        
        if (!FOG_10218()) 
		{
            ExitProcess(NULL);
        }
        
        if (!(D2WIN_10059() && D2WIN_10073(NULL, NULL, NULL, &D2Client))) 
        {
            //failed to load mpq
            ExitProcess(NULL);
        }
        
        //loading language tables
        D2LANG_10003(0,"ENG",0);
        
        
        if (!D2COMMON_InitDataTables(0,0,0))
		{
			//couldn't initialize sqptDataTable
            ExitProcess(NULL);
        }
        
        D2CLIENT_InitGameMisc();
	}
}
