#ifndef _mob_hp_bar_H
#define _mob_hp_bar_H

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

//---------------------------------
// GUI indexes

#define NEWUI_BAR_SWITCH01 0x00007A5B
#define NEWUI_BAR_SWITCH02 0x00007A5C
//---------------------------------
// Functions

#define MU_DRAW_INTERFACE			0x00739CB5
#define MU_DRAWGUI					0x006FBD23
#define MU_CREATE_COLOR				0x004109C0
#define MU_DRAW_BUTTON				0x006FBE13
#define MU_DRAW_COLORED_BUTTON      0x006FBED6

#define MU_CDC_GET_THIS_POINTER		0x0041EB98
#define MU_CDC_TABBEDTEXTOUT		0x0041EE57
#define MU_CDC_SETTEXTCOLOR			0x0041ED68

//void __cdecl DrawGui(DWORD dwUI, float x, float y, float width, float height) -> return void
typedef void (__cdecl *pMU_DrawGUI)(DWORD, float, float, float, float);
extern pMU_DrawGUI MU_DrawGUI;

//DWORD __cdecl CreateColor(BYTE r, BYTE g, BYTE b, BYTE h) -> return DWORD (color)
typedef DWORD (__cdecl *pMU_CreateColor)(BYTE, BYTE, BYTE, BYTE);
extern pMU_CreateColor MU_CreateColor;

//void __cdecl DrawButton(DWORD dwUI, float x, float y, float width, float height, float movex, float movey) -> return void
typedef void (__cdecl *pMU_DrawButton)(DWORD, float, float, float, float, float, float); 
extern pMU_DrawButton MU_DrawButton;

//void __cdecl DrawColoredButton(DWORD dwUI, float x, float y, float width, float height, float movex, float movey, DWORD color) -> return void
typedef void (__cdecl *pMU_DrawColoredButton)(DWORD, float, float, float, float, float, float, DWORD);
extern pMU_DrawColoredButton MU_DrawColorButton;

//CSize __thiscall CDC::TabbedTextOut(int x, int y, LPCTSTR lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin) -> return CSize
typedef int(__thiscall *pCDCTabbedTextOut)(LPVOID This, int x, int y, LPCTSTR lpszString, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

//DWORD __thiscall CDC:SetTextColor(char r, char g, char b, char h) -> return DWORD (RGB color)
typedef DWORD(__thiscall *pCDCSetTextColor)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h);

typedef LPVOID(__cdecl *pCDC_This)(void);
extern pCDC_This CDC_This;

#include <Windows.h>
#include <stdio.h>
#include "Interface.h"


class CMob_HPBar
{
	private:
		int HP;
		int MaxHP;
	
	public:
		BOOL isDraw;
		WORD aIndex;

		CMob_HPBar();
		virtual ~CMob_HPBar();
		
		void SetupMob(int Life, int MaxLife, WORD index);
		void Draw();
		void ShowHp();
};

extern CMob_HPBar Mob_HP_Bar;

#endif