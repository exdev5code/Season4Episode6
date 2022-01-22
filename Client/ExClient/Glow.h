#include "StdAfx.h"
#ifdef _GRAND_SYSTEM_

struct FRGB
{
    float r, g, b;
};

#define OriginalGlow ((signed int (__cdecl *)(DWORD, DWORD, DWORD, FRGB&, BYTE)) 0x005C2744)

void InitGlowFunc();
#endif