#include <windows.h>

DWORD WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			// DisableThreadLibraryCalls(hModule);
			break;
	}
	return TRUE;
}

