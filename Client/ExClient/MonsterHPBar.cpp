#include "stdafx.h"
#include "MonsterHPBar.h"
#include "Protocol.h"

#include "Configs.h"

pMU_DrawGUI MU_DrawGUI = (pMU_DrawGUI)MU_DRAWGUI;
pMU_CreateColor MU_CreateColor = (pMU_CreateColor)MU_CREATE_COLOR;
pMU_DrawButton MU_DrawButton = (pMU_DrawButton)MU_DRAW_BUTTON;
pMU_DrawColoredButton MU_DrawColorButton = (pMU_DrawColoredButton)MU_DRAW_COLORED_BUTTON;
pCDC_This CDC_This = (pCDC_This)MU_CDC_GET_THIS_POINTER;

pCDCSetTextColor MU_SetTextColor = (pCDCSetTextColor)MU_CDC_SETTEXTCOLOR;
pCDCTabbedTextOut MU_TabbedTextOut = (pCDCTabbedTextOut)MU_CDC_TABBEDTEXTOUT;

#ifdef DEBUG_INTERFACE
#define MU_SetTextColorTEST		((DWORD(__thiscall*)(LPVOID, BYTE , BYTE , BYTE , BYTE )) 0x0041EDCA)
#endif

//

void MU_SetColor(BYTE r, BYTE g, BYTE b, BYTE h)
{
	MU_SetTextColor(CDC_This(), r, g, b, h);
#ifdef DEBUG_INTERFACE
	//MU_SetTextColorTEST(CDC_This(), r, g, b, h);
#endif
}

void MU_OutText(int x, int y, LPCTSTR lpszString)
{
	MU_TabbedTextOut(CDC_This(), x, y, lpszString, 1, 1, (LPINT)0, 0);
}

void MU_SetTextColorEx(BYTE red, BYTE blue, BYTE green, BYTE Header)
{
	MU_SetTextColor(CDC_This(), red, blue, green, Header);
}

CMob_HPBar Mob_HP_Bar;

CMob_HPBar::CMob_HPBar(): isDraw (false)
{

}

CMob_HPBar::~CMob_HPBar()
{

}

void CMob_HPBar::Draw()
{
	if(!Config.exHPBar)return;

	if (this->MaxHP == 0 || this->isDraw == false) return;
	int pHP = (this->HP * 100) / this->MaxHP;
	if (pHP)
	{
		//Center
		MU_DrawGUI(NEWUI_BAR_SWITCH01, (MAX_WIDTH / 2) - 80, 0, 160, 18);
		MU_DrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIDTH / 2) - 75, 5, (150 * pHP) / 100, 8, 0, 0, MU_CreateColor(255, 0, 0, 130));

		this->ShowHp();
		//Left
		//MU_DrawGUI(NEWUI_BAR_SWITCH01, (MAX_WIDTH / 2) - 260, 0, 160, 18);
		//MU_DrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIDTH / 2) - 255, 5, (150 * pHP) / 100, 8, 0, 0, MU_CreateColor(255, 0, 0, 130));

		//Right
		//MU_DrawGUI(NEWUI_BAR_SWITCH01, (MAX_WIDTH / 2) + 85, 0, 160, 18);
		//MU_DrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIDTH / 2) + 90, 5, (150 * pHP) / 100, 8, 0, 0, MU_CreateColor(255, 0, 0, 130));
	}
	else
	{
		this->isDraw = false;
	}
}

void CMob_HPBar::ShowHp()
{
	char wiad[256];
	sprintf_s(wiad, "%d / %d", this->HP, MaxHP);
	int len = strlen(wiad);
	int Width = (MAX_WIDTH / 2)-len*2;
	MU_SetTextColorEx(255, 255, 255, 255);
	MU_OutText(Width,4,(LPCTSTR)wiad);
}

void CMob_HPBar::SetupMob(int Life, int MaxLife, WORD index)
{
	if (Life > MaxLife || 0 > Life)
	{
		this->isDraw = false; //something is wrong ^.^
	}
	this->HP = Life;
	this->MaxHP = MaxLife;
	this->aIndex = index;
	this->isDraw = TRUE;
}

