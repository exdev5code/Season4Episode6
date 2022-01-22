#pragma once

#include "StdAfx.h"

void SetByte(DWORD dwOffset, BYTE btValue);
void Protect(DWORD dwAddr, DWORD size, DWORD dwProtection);
DWORD UnProtect(DWORD dwAddr, DWORD size);
void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset);
void WriteJmp(DWORD dwWriteOffset, DWORD dwDstJmp);
void HookExactOffset(DWORD my, DWORD tohook, BYTE type);
void HookOffset(DWORD my, DWORD tohook, BYTE type);
void SetNop(DWORD dwOffset,int Size);			