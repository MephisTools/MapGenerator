#pragma once

#include "windows.h"
#include <stdio.h>

#include "D2Structs.h"
#include "D2Ptrs.h"
#include "Offset.h"

#include "ArrayEx.h"
#include "Matrix.h"
#include "CollisionMap.h"

#define ArraySize(x) (sizeof(x) / sizeof(x[0]))

VOID __fastcall D2OpenFile(CHAR* szFile);
VOID D2OpenFile_ASM();
Level* __fastcall GetLevel(ActMisc *misc, DWORD levelno);
VOID D2CLIENT_InitGameMisc(VOID);