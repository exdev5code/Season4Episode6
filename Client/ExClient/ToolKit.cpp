#include "StdAfx.h"
#include "ToolKit.h"

void SetByte(DWORD dwOffset, BYTE btValue) {
	__try {
		DWORD dwP = UnProtect(dwOffset, 1);
		*(BYTE*)(dwOffset)=btValue;
		Protect(dwOffset, 1, dwP);
	}
	__finally{}
}

void Protect(DWORD dwAddr, DWORD size, DWORD dwProtection) {
	DWORD old = 0;
	VirtualProtect((LPVOID)dwAddr, size, dwProtection, &old);
}

DWORD UnProtect(DWORD dwAddr, DWORD size) {
	DWORD old = 0;
	VirtualProtect((LPVOID)dwAddr, size, PAGE_EXECUTE_READWRITE, &old);
	return old;
}

void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset) {
	*(DWORD*)(dwJmpOffset + 1) = dwMyFuncOffset-(dwJmpOffset+5);
}

void WriteJmp(DWORD dwWriteOffset, DWORD dwDstJmp) {
	if(dwWriteOffset)	{
		__try {
			DWORD dwP = UnProtect(dwWriteOffset, 10);
			SetByte(dwWriteOffset, 0xE9);
			HookThis(dwDstJmp, dwWriteOffset);
			Protect(dwWriteOffset, 10, dwP);
		}
		__finally{}
	}
}

void HookExactOffset(DWORD my, DWORD tohook, BYTE type) {
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook+1) = my;
}

void HookOffset(DWORD my, DWORD tohook, BYTE type) {
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook+1) = my - (tohook+5);
}

void SetNop(DWORD dwOffset,int Size) {
	for(int n=0;n<Size;n++) {
		*(BYTE*)(dwOffset+n) = 0x90;
	}
}