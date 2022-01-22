#include "stdafx.h"

extern bool g_bGlowGraphic;

#if(NEW_GLOW_EFFECT)
//0x0041EB98
#define pSelectDraw				((int(__cdecl*)(DWORD)) 0x0041EB98)		//0x0041FE10
#define oSelectDraw_Call		0x004063FF//0x004063FF//	0x00405A32

static DWORD gSelectEnter = 0x0040B008;	//0x0040AB4A;
static DWORD gGraphicsEnter = 0x006E8D0E;//0x006E8BFC;//0x00777B3B;
static DWORD gSelectASMJmp00 = gSelectEnter+6;
static DWORD gGraphicsASM00Jmp00 = gGraphicsEnter+5;


class Graphics
{
public:
	Graphics();
	// ----
	void		Load();
	static void	InitGraphics();
	static void	InterfaceDraw();
	static int  SelectDraw(int value);

}; extern Graphics gGraphics;

#endif