#include "D2Map.h"

PatchHook pHooks[] = {
	{PatchJmp, 0x6fd59900, (DWORD)D2OpenFile_ASM,6},
//	{PatchJmp, GetDllOffset("D2GAME.dll",0x95AC0), (DWORD)WardenActionPacket,5},
//	{PatchJmp, GetDllOffset("D2GAME.dll",0xED509), (DWORD)PlayerJoin_Intercept,5},
//	{PatchCall, GetDllOffset("D2GAME.dll",0x719A), (DWORD)PlayerLeave_Intercept,5},
//	{PatchJmp, 0x00406EFC, (DWORD)GameInterception, 5},
	/*	
00406EFC   56               PUSH ESI
00406EFD   56               PUSH ESI
00406EFE   FF75 F4          PUSH DWORD PTR SS:[EBP-C]

00A15AC0   . 33C0           XOR EAX,EAX


GAMEServer Add Player to Game (ECX = PlayerUnit)
009ED509   C2 1400          RETN 14

00A3719A  |. 68 CB010000    PUSH 1CB

	
	{PatchJmp, GetDllOffset("D2GFX.dll", 0x8920+5), (DWORD)GameMinimize_Interception, 5},
	{PatchCall, GetDllOffset("D2Client.dll", 0x869B5), (DWORD)GameInput_Interception, 5},
	{PatchJmp, GetDllOffset("D2Client.dll", 0x90524), (DWORD)GameDraw_STUB, 6},
	{PatchCall, GetDllOffset("D2Client.dll", 0x65111), (DWORD)GamePacketReceived_STUB, 5}, // v
	{PatchCall, GetDllOffset("D2CLIENT", 0x4FF63), (DWORD)GameCreateMissile_STUB,6},
	{PatchCall, GetDllOffset("D2CLIENT", 0x4FEF8), (DWORD)GameCreateMissile2_STUB,7},
	{PatchCall, GetDllOffset("D2CLIENT", 0x5CEF4), (DWORD)myGetSelectedUnit, 5},
	{PatchCall, GetDllOffset("D2Win.dll", 0xD848), (DWORD)GameDrawOOG, 5},
	{PatchCall, GetDllOffset("D2MULTI", 0xFC3C), (DWORD)Whsiper_Intercept, 7},
	{PatchCall, GetDllOffset("D2Client.dll", 0x5B050), (DWORD)GameAttack_STUB,5},
	{PatchJmp, GetDllOffset("D2CLIENT.dll", 0x66487), (DWORD)PlayerAssignment_STUB, 5},
	//6FB16487   E8 D4A8FBFF      CALL d2client.6FAD0D60

	{PatchCall, GetDllOffset("D2Client.dll", 0xBE103), (DWORD)GamePacketRecv_Interception, 7},
	{PatchJmp, GetDllOffset("D2Client.dll", 0x66DC5), (DWORD)GameDraw_STUB, 5},
	6FB369B5  |. E8 B62CFFFF    CALL d2client.6FB29670

6FB0CEF4  |. E8 A71D0100    CALL d2client.6FB1ECA0


6F9E0190   . 81EC F8040000        SUB ESP,4F8
6F9E0196   . 56                   PUSH ESI
	
6F9DFC3C   8BAC24 FC010000  MOV EBP,DWORD PTR SS:[ESP+1FC]



	{PatchCall, GetDllOffset("BNClient.dll", 0xDE41), (DWORD)BNCLIENT_LoadExtraWork, 6},
	{PatchCall, GetDllOffset("BNClient.dll", 0xCC7A), (DWORD)BNCLIENT_CheckRevision, 6},
*/};