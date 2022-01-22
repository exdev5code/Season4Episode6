#ifndef _mu_utils_H
#define _mu_utils_H

#include <Windows.h>
#include <stdlib.h>

struct tJMP
{
	BYTE op;
	DWORD Address;
};

//Opcode const
#define _asm_call       0xE8
#define _asm_push       0x68
#define _asm_jmp        0xE9
#define _asm_jmps       0xEB//jmp short
#define _asm_jes        0x74
#define _asm_jnzs       0x75
#define _asm_jnz2       0x0F85//jmp short
#define _asm_nop        0x90
#define _asm_retn       0xC3
#define _asm_push_eax 0x50
 
#define MEMORY4(value) *(unsigned int*)(value)
#define MEMORY2(value) *(unsigned short*)(value)
#define MEMORY1(value) *(unsigned char*)(value)

LPVOID HookFunction(LPVOID origf, LPVOID callbackf, DWORD copylen);
DWORD WriteMemory2(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd);

#endif