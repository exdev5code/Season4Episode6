#include "stdafx.h"
#include "Utilits.h"


//LPVOID HookFunction(LPVOID origf, LPVOID callbackf, DWORD copylen)
//{
//	LPVOID newf = malloc(copylen + 5);
//	DWORD dwOld;
//	VirtualProtect(origf, copylen, PAGE_EXECUTE_READWRITE, &dwOld);
//	memcpy(newf, origf, copylen);
//	PBYTE j = (PBYTE)((DWORD)newf + copylen);
//	j[0] = 0xE9;
//	*(DWORD*)&j[1] = (DWORD)(((DWORD)origf + copylen) - (DWORD)j - 5);
//	j = (PBYTE)origf;
//	j[0] = 0xE9;
//	*(DWORD*)&j[1] = (DWORD)((DWORD)callbackf - (DWORD)j - 5);
//	VirtualProtect(origf, copylen, dwOld, &dwOld);
//	return newf;
//} 

LPVOID HookFunction(LPVOID origf, LPVOID callbackf, DWORD copylen)
{
	LPVOID newf = malloc(copylen + 6);
	DWORD dwOld;
	VirtualProtect(origf, copylen, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy(newf, origf, copylen);
	PBYTE j = (PBYTE)((DWORD)newf + copylen);
	j[0] = 0x68;
	*(DWORD*)&j[1] = (DWORD)((DWORD)origf + copylen);
	j[5] = 0xC3;
	j = (PBYTE)origf;
	j[0] = 0x68;
	*(DWORD*)&j[1] = (DWORD)(DWORD)callbackf;
	j[5] = 0xC3;
	VirtualProtect(origf, copylen, dwOld, &dwOld);
	return newf;
}
DWORD WriteMemory2(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode   = 0;
	DWORD dwOldProtect  = 0;
	// ----
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
	// ----
	if ( iRes == 0 )
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	memcpy(lpAddress, lpBuf, uSize);
	// ----
	DWORD dwBytes   = 0;
	// ----
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
	// ----
	if ( iRes == 0 )
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	return 0x00;
}

DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	DWORD dwShift	= (ULONG_PTR)dwMyFuncOffset - ( (ULONG_PTR)dwJmpOffset + 5 );
	// ----
	btBuf[0] = cmd;
	// ----
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory2(dwJmpOffset, (LPVOID) btBuf, sizeof(btBuf));
}
