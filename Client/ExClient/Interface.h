#pragma once
// ----------------------------------------------------------------------------------------------

#include "Defines.h"
// ----------------------------------------------------------------------------------------------

#define INTERFACE_DEBUG		1
// ----------------------------------------------------------------------------------------------

#define MAX_OBJECT			100
#define MAX_WIN_WIDTH		640
#define MAX_WIN_HEIGHT		480
// ----------------------------------------------------------------------------------------------

#define oDrawInterface_Call 0x00739C02	//Done
#define oLoadSomeForm_Call	0x006E80DC	//Done
#define pDrawInterface		((void(__cdecl*)()) 0x00739CB5)	//done
#define pLoadImage			((int(__cdecl*)(char * Folder, int Code, int Arg3, int Arg4, int Arg5)) 0x006C167E)	//Done
#define pLoadSomeForm		((void(__cdecl*)()) 0x006E8721)	//Done
#define pWindowThis			((LPVOID(*)()) 0x007747FF)	//done
#define pCheckWindow		((bool(__thiscall*)(LPVOID This, int Code)) 0x00772B6D)	//Done
#define pDrawGUI			((void(__cdecl*)(DWORD, float, float, float, float))	0x006FBD23)	//Done
#define pDrawColorText		((int(__cdecl*)(LPCTSTR Text, int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align)) 0x0072DDF7)	//Done

#define pDrawToolTip		((int(__cdecl*)(int X, int Y, LPCSTR Text)) 0x00514E80)	//Done
#define pDrawColorButton	((void(__cdecl*)(DWORD, float, float, float, float, float, float, DWORD)) 0x006FBED6)	//Done

#define	pCursorX			*(int*)0x809F0FC //Done
#define	pCursorY			*(int*)0x809F0F8 //Done

#define pSetCursorFocus		*(DWORD*)0x80A39D8	//Done


// ----------------------------------------------------------------------------------------------
enum ObjectID
{
	eTIME = 1,
	eRageSystem,
	eRageTable,
	eRageClose,
	eRagePointTable,
	eRageIcon1,
	eRageIcon2,
	eRageIcon3,
	eRageIcon4,
	eRageIcon5,
	eRageIcon6,
	eRageIcon7,
	eRageIcon8,
	eRageIcon9,
	eRageIcon10,
	eRageIcon11,
	eRageIcon12,
	eRageIcon13,
	eRageIcon14,
	eRageIcon15,
	eRageIcon16,
	eRageIcon17,
	eRageIcon18,
	eRageIcon19,
	eRageIcon20,
	eRageIcon21,
	eRageIcon22,
	eRageIcon23,
	eRageIcon24,
	eRageIcon25,
	eRageIcon26,
	eRageIcon27,
	eRageIcon28,
	eRageIcon29,
	eRageIcon30,
	eRageIcon31,
	eRageIcon32,
	eRageIcon33,
	eRageIcon34,
	eRageIcon35,
	eRageTeleport,
	eRagePet,
	eJewelsBank,
};
// ----------------------------------------------------------------------------------------------

enum ObjWindow // -> Season 6.3
{
	FriendList		= 1,
	MoveList		= 2,
	Party			= 3,
	Guild			= 6,
	Trade			= 7,
	Warehouse		= 8,
	ChaosBox		= 9,
	CommandWindow	= 10,
	PetInfo			= 11,
	Shop			= 12,
	Inventory		= 13,
	Store			= 14,
	OtherStore		= 15,
	Character		= 16,
	ChatWindow		= 33,
	FastMenu		= 34,
	Options			= 35,
	Help			= 36,
	FastDial		= 39,
	SkillTree		= 57,
	NPC_Titus		= 63,
	CashShop		= 65,
	FullMap			= 72,
	NPC_Dialog		= 73,
	GensInfo		= 74,
	NPC_Julia		= 75,
	ExpandInventory	= 77,
	ExpandWarehouse	= 78,
};
// ----------------------------------------------------------------------------------------------

enum ColorMacro
{
	eShinyGreen		= Color4f(172, 255, 56, 255),
	eGold			= Color4f(255, 189, 25, 255),
	eWhite			= Color4f(255, 255, 255, 255),
	eWhite180		= Color4f(255, 255, 255, 180),
	eOrange			= Color4f(255, 105, 25, 255),
	eGray100		= Color4f(50, 50, 50, 100),
	eGray150		= Color4f(50, 50, 50, 150),
	eBlowPink		= Color4f(220, 20, 60, 255),
	eRed			= Color4f(225, 0, 0, 255),
	eExcellent		= Color4f(0, 225, 139, 255),
	eAncient		= Color4f(1, 223, 119, 255),
	eSocket			= Color4f(153, 102, 204, 255),
	eBlue			= Color4f(36, 242, 252, 255),
	eYellow			= Color4f(255, 255, 0, 255),
	eBrown			= Color4f(69, 39, 18, 255),
	eBlack			= Color4f(0, 0, 0, 255),	
};
// ----------------------------------------------------------------------------------------------

struct InterfaceObject
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;
};
// ----------------------------------------------------------------------------------------------

class Interface
{
public:
	Interface();
	// ----
	void		BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
	void		Load();
	void		LoadImages(char * Folder, int Code, int Arg3, int Arg4, int Arg5);
	static void	LoadTga();
	// ----
	static void	Work();
	bool		CheckWindow(int WindowID);
	void		DrawGUI(short ObjectID);
	void		DrawGUI(short ObjectID, float PosX, float PosY);
	void		DrawColoredGUI(short ObjectID, DWORD Color);
	void		DrawColoredGUIObj(short ObjectID, float X, float Y, DWORD Color);
	int			DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void		DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	bool		IsWorkZone(float X, float Y, float MaxX, float MaxY);
	bool		IsWorkZoneObj(short ObjectID);

	int			DrawToolTip(int X, int Y, LPCSTR Text, ...);
	int			DrawToolTipEx(int X, int Y, LPCSTR Text, ...);

	void		DrawColorGUI(int MainID, int X, int Y, int Width, int Height, DWORD Color);
	// ----
	InterfaceObject Data[MAX_OBJECT];
};
extern Interface gInterface;