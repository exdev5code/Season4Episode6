#include "stdafx.h"
#include "Interface.h"
#include "Defines.h"
#include "TMemory.h"
#include "MonsterHPBar.h"
#include "DrawTime.h"
#include "RageSystem.h"
#include "MonsterHPBar.h"
#include "ConnectEx.h"
#include "Console.h"
#include "GameCharacter.h"
#include "User.h"
#include "JewelsBank.h"
#include "Graphics.h"

Interface	gInterface;

Interface::Interface()
{
	ZeroMemory(this->Data, sizeof(this->Data));
}

void Interface::BindObject(short ID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[ID].EventTick	= 0;
	this->Data[ID].OnClick		= false;
	this->Data[ID].OnShow		= false;
	this->Data[ID].ModelID		= ModelID;
	this->Data[ID].Width		= Width;
	this->Data[ID].Height		= Height;
	this->Data[ID].X			= X;
	this->Data[ID].Y			= Y;
	this->Data[ID].MaxX			= X + Width;
	this->Data[ID].MaxY			= Y + Height;
	this->Data[ID].Attribute	= 0;
}

void Interface::LoadImages(char * Folder, int Code, int Arg3, int Arg4, int Arg5)
{
	pLoadImage(Folder, Code, Arg3, Arg4, Arg5);
}

void Interface::LoadTga()
{
#if(_JEWELS_BANK_)
	gJewelsBank.JewelsBankImageLoad();
#endif
	TimeImageLoad();
//#ifdef _SYSTEM_OF_RAGE_
	gRageSystem.LoadImages();
//#endif
	/*gInterface.LoadImages("ExTeam\\Interface\\TimeBar.tga", 0x787E, 0x2601, 0x2900, 1);*/
	//pLoadImage("ExTeam\\Interface\\TimeBar.tga", 0x787E, 0x2601, 0x2900, 1);
#if(NEW_HP_BAR)
	gInterface.LoadImages("ExTeam\\Interface\\HPLine.jpg", 0x7880, 0x2601, 0x2900, 1);
#endif

#if(NEW_GLOW_EFFECT)
	gGraphics.InitGraphics();
#endif

	pLoadSomeForm();
}

void Interface::Load()
{
	TimeLoad();

#if(_JEWELS_BANK_)
	gJewelsBank.JewelsBankLoad();
#endif

	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadTga, ASM::CALL);
}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}

void Interface::DrawGUI(short ObjectID)
{
	pDrawGUI(this->Data[ObjectID].ModelID, this->Data[ObjectID].X, this->Data[ObjectID].Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawColoredGUI(short ObjectID,DWORD Color)
{
	pDrawColorButton(this->Data[ObjectID].ModelID,this->Data[ObjectID].X, this->Data[ObjectID].Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawColoredGUIObj(short ObjectID, float X, float Y, DWORD Color)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawColorGUI(int MainID, int X, int Y, int Width, int Height, DWORD Color)
{
	pDrawColorButton(MainID, X, Y, Width, Height, 0, 0, Color);
}

int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	int LineCount = 0;
	// ----
	char * Line = strtok(Buff, "\n");
	// ----
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	// ----
	return PosY;
}

void Interface::DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	pDrawColorText(Buff, PosX, PosY, Width, 0, Color, 0, Align);
}

int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawToolTip(X, Y, Buff);
}
// ----------------------------------------------------------------------------------------------

int Interface::DrawToolTipEx(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	int LineCount = 0;
	// ----
	char * Line = strtok(Buff, "\n");
	// ----
	while( Line != NULL )
	{
		pDrawToolTip(X, Y, Line);
		Y += 10;
		Line = strtok(NULL, "\n");
	}
	// ----
	return Y;
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY)
{
	if( (pCursorX < X || pCursorX > MaxX) 
		|| (pCursorY < Y || pCursorY > MaxY) )
	{
		return false;
	}
	// ----
	return true;
}

bool Interface::IsWorkZoneObj(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;
	// ----
	//if( ObjectID == eSAMPLEBUTTON 
	//	|| ObjectID == eCAMERA_MAIN 
	//	|| ObjectID == eCAMERA_BUTTON1
	//	|| ObjectID == eCAMERA_BUTTON2 )
	//{
	//	PosX = this->GetResizeX(ObjectID);
	//	MaxX = PosX + this->Data[ObjectID].Width;
	//}
	// ----
	if( (pCursorX < PosX || pCursorX > MaxX) 
		|| (pCursorY < this->Data[ObjectID].Y || pCursorY > this->Data[ObjectID].MaxY) )
	{
		return false;
	}
	// ----
	return true;
}



//signed int __cdecl sub_4FC000(int a1)
//{
//  int v2; // [sp+0h] [bp-Ch]@3
//  signed int v3; // [sp+4h] [bp-8h]@1
//  signed int i; // [sp+8h] [bp-4h]@1
//
//  v3 = 400;
//  for ( i = 0; i < 400; ++i )
//  {
//    v2 = 1236 * i += *(DWORD*)0x7A7239C;
//    if ( *(BYTE *)(1236 * i + *(DWORD*)0x7A7239C + 704) )
//    {
//      if ( *(WORD *)(v2 + 94) == a1 )
//        v3 = i;
//    }
//    *(BYTE *)(v2 + 23) = 0;
//  }
//  return v3;
//}

void Interface::Work()
{
#ifdef CONSOLE
	

	//Console.ConsoleOutput(RED,"%d",pViewAttackTargetID);
	//for(int a = 0; a < 10000; a++)
	//{
	//	if(*(WORD *)(*(DWORD*)0x7A7239C + 1236  + a) == *GameIndex)
	//	Console.ConsoleOutput(GREEN," %d",*(WORD *)(*(DWORD*)0x7A7239C + 1236  + 3905));

	//}
		
#endif
	gObjUser.Refresh();
#ifndef NEW_HP_BAR
	Mob_HP_Bar.Draw();
#endif
	DrawTime();
#ifdef _SYSTEM_OF_RAGE_
	gRageSystem.rDrawInterface();
#endif
#if(exRECONNECT)
	gConnectEx.Run();
#endif
#if(_JEWELS_BANK_)
	gJewelsBank.JewelsBankDraw();
#endif
	pDrawInterface();
}