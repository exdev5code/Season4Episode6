#include "stdafx.h"
#include "Interface.h"
#include "User.h"
#include "Configs.h"
#include "JewelsBank.h"

#if(_JEWELS_BANK_)

JewelsBank gJewelsBank;

void JewelsBank::JewelsBankImageLoad()
{
	//if(!gJEWELSBANK) return;
	gInterface.LoadImages("ExTeam\\JewelsBank\\newui_gens_rankback.tga", 400000, 0x2601, 0x2900, 1);
}

void JewelsBank::JewelsBankLoad()
{
	//if(!gJEWELSBANK) return;
	this->Active = false;
	gInterface.BindObject(eJewelsBank, 400000, 85, 100, 1, 23);
	gInterface.Data[eJewelsBank].OnShow = true;
}

void JewelsBank::JewelsBankDraw()
{
	//if(!gJEWELSBANK) return;

	if( /*gInterface.CheckWindow(ObjWindow::ChatWindow) ||*/ gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::MoveList) /*|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30*/ )
	{
		return;
	}

	if(this->Active == false) return;

	gInterface.DrawGUI(eJewelsBank);

	gInterface.DrawFormat(eGold, 22, 25+5, 50, 1, "ExInfo Table");
#ifdef _MegaMu_
	gInterface.DrawFormat(eShinyGreen, 10, 25+10+10, 60, 1, "Premium:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+20+10, 60, 1, "Chaos:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+30+10, 60, 1, "Bless:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+40+10, 60, 1, "Soul:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+50+10, 60, 1, "Life:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+60+10, 60, 1, "Credits:");
#else
	gInterface.DrawFormat(eShinyGreen, 10, 25+10+10, 60, 1, "Premium Hour:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+20+10, 60, 1, "Jewel Of Chaos:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+30+10, 60, 1, "Jewel Of Bless:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+40+10, 60, 1, "Jewel Of Soul:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+50+10, 60, 1, "Jewel Of Life:");
	gInterface.DrawFormat(eShinyGreen, 10, 25+60+10, 60, 1, "Credits:");
#endif

	gInterface.DrawFormat(eWhite, 68, 25+10+10, 40, 1, "%d",(gObjUser.Premium/3600));
	gInterface.DrawFormat(eWhite, 68, 25+20+10, 40, 1, "%d",gObjUser.ChaosBank);
	gInterface.DrawFormat(eWhite, 68, 25+30+10, 40, 1, "%d",gObjUser.BlessBank);
	gInterface.DrawFormat(eWhite, 68, 25+40+10, 40, 1, "%d",gObjUser.SoulBank);
	gInterface.DrawFormat(eWhite, 68, 25+50+10, 40, 1, "%d",gObjUser.LifeBank);
	gInterface.DrawFormat(eWhite, 40, 25+60+10, 40, 1, "%.2f",gObjUser.ExCred);

	//gInterface.DrawColorGUI(0x7880, 100, 200, 250, 250, eBlack);
	//pDrawColorButton(0x7880, (MAX_WIN_WIDTH / 2) - 85, 6, (175 * pHP) / 100, 6, 0, 0, (int)Color4f(255, 0, 0, 130));
}

void JewelsBank::JewelsBankRecv(EXINFO_UPDATE * aRecv)
{
	gObjUser.Premium = aRecv->PremiumTime;
	gObjUser.ChaosBank = aRecv->Chaos;
	gObjUser.BlessBank = aRecv->Bless;
	gObjUser.SoulBank = aRecv->Soul;
	gObjUser.LifeBank = aRecv->Life;
	gObjUser.ExCred = aRecv->ExCred;
}

#endif