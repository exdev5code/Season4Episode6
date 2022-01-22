#include "stdafx.h"

/*
005995B0	- отрисовка имени и клана
0059985B - вызов функция вычисляет название над головой
0065FB59	- Выдает как Хак

005985F0 - функция рисует ник чат клан

0080F6B2 - все функции для отрисовки интерфейса
*/

#define pWinWidth				*(GLsizei*)0x008D65C8
#define pWinHeight				*(GLsizei*)0x008D65CC

#ifdef NEW_HP_BAR

#define MAX_MONSTER		1024


//~~~~~

#define pPartyListStruct        *(PartyList*)0x7B46C98	//1.03K
#define pGetPosFromAngle        ((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY)) 0x5F3770)
#define pTextThis                ((LPVOID(*)()) 0x41EB98)	//1.03K
#define pDrawText                ((int(__thiscall*)(LPVOID This, int PosX, int PosY, char * Text, int Arg4, int Arg5, int * Arg6, int Arg7)) 0x41EE57)
#define pSetTextColor            ((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 
#define pSetBlend                ((void(__cdecl*)(BYTE Mode)) 0x5F3BD0)
#define pDrawBarForm            ((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x5F518C)
#define pGLSwitchBlend            ((void(__cdecl*)()) 0x5F3C6B)

#define sub_4FC000 ((signed int(__cdecl*)(int a1)) 0x4FC000)	//ModelID Return aIndex

//1.04D
//#define pPartyListStruct        *(PartyList*)0x81CB4E8
//#define pGetPreviewStruct        ((DWORD(__thiscall*)(LPVOID This, int ViewportID)) 0x96A340)
//#define pPreviewThis            ((LPVOID(*)()) 0x402BC0)
//#define pGetPosFromAngle        ((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY)) 0x635B00)
//#define pSetTextColor            ((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 
//#define pTextThis                ((LPVOID(*)()) 0x0041FE10)
//#define pDrawText                ((int(__thiscall*)(LPVOID This, int PosX, int PosY, char * Text, int Arg4, int Arg5, int * Arg6, int Arg7)) 0x00420150)
//#define pSetBlend                ((void(__cdecl*)(BYTE Mode)) 0x635FD0)
//#define pDrawBarForm            ((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x6378A0)
//#define pGLSwitchBlend            ((void(__cdecl*)()) 0x636070)
//#define pGLSwitch                ((void(__cdecl*)()) 0x635F50)
//#define	pViewAttackTargetID		*(int*)0xE61730
//
//#define CheckBattleCursor        ((bool(__cdecl*)()) 0x59A8B0)

struct PartyList //-> Complete (size: 32)
{
/*+0*/	char	Name[10];
/*+10*/	BYTE	Unknown10;
/*+11*/	BYTE	Unknown11;
/*+12*/	BYTE	MapNumber;
/*+13*/	BYTE	PosX;
/*+14*/	BYTE	PosY;
BYTE gap01;
/*+16*/	int		Life;
/*+20*/	int		MaxLife;
/*+24*/	BYTE	LifePercent;
BYTE gap02[3];
/*+28*/	int		ViewportID;
}; typedef PartyList * lpPartyList;

enum eObjectType	//-> Complete
{
	emPlayer	= 1,
	emMonster	= 2,
	emNPC		= 4,
	emNone		= 8,
};

//#pragma pack(push, 1)
struct VAngle
{
    float X;
    float Y;
    float Z;
};
//#pragma pack(pop)

// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct ObjectModel_424
{
    float Unknown0;
    float Unknown4;
    float Unknown8;
    float Unknown12;
    float Unknown16;
    float Unknown20;
    float Unknown24;
    float Unknown28;
    float Unknown32;
    float Unknown36;
    float Unknown40;
    float Unknown44;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ObjectModel    //648?
{
BYTE gap00[4];
/*+4*/        BYTE    Unknown4;
BYTE gap01[4];
/*+9*/        BYTE    Unknown9;
BYTE gap02[5];
/*+15*/        BYTE    Unknown15;
BYTE gap03[2];
/*+18*/        WORD    AnimationID;
/*+20*/        WORD    Unknown20;
/*+22*/        BYTE    Unknown22;
/*+23*/        BYTE    Unknown23;
/*+24*/        BYTE    ObjectType;
BYTE gap04[13];
/*+38*/        WORD    Unknown38;
BYTE gap05[8];
/*+48*/        DWORD    Unknown48;
BYTE gap06[44];
/*+96*/        float    Scale;
BYTE gap07[16];
/*+116*/    float    Unknown116;
BYTE gap08[20];
/*+140*/    float    Unknown140;
/*+144*/    float    Unknown144;
BYTE gap09[56];
/*+204*/    VAngle    Unknown204;
/*+216*/    VAngle    Unknown216;
BYTE gap10[24];
/*+252*/    float    VecPosX;
/*+256*/    float    VecPosY;
/*+260*/    float    VecPosZ;
/*+264*/    float    Unknown264;
/*+268*/    float    Unknown268;
/*+272*/    float    Unknown272;
BYTE gap11[148];
/*+424*/    ObjectModel_424 Unknown424;
BYTE gap12[176];
/*+484*/
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------


#pragma pack(push, 1)
typedef struct    //-> InDev (size: 1432)
{
BYTE gap01[14];
/*+14*/        bool    InSafeZone;
/*+15*/        BYTE    Unknown15;
/*+16*/        BYTE    Unknown16;
/*+17*/        BYTE    IsLiveObject;
/*+18*/        BYTE    Unknown18;
/*+19*/        BYTE    Class;
/*+20*/        BYTE    Unknown20;
/*+21*/        BYTE    CtlCode;    //Bit decomposit (0x10)
/*+22*/        BYTE    Unknown22;
/*+23*/        BYTE    Unknown23;
/*+24*/        BYTE    Unknown24;
/*+25*/        BYTE    Unknown25;
/*+26*/        BYTE    Unknown26;
/*+27*/        BYTE    Unknown27;
/*+28*/        BYTE    Unknown28;
/*+29*/        BYTE    Unknown29;
/*+30*/        BYTE    Unknown30;
/*+31*/        BYTE    GensInfluence;    //0 - None, 1 - D, 2 - V
/*+32*/        BYTE    Unknown32;
/*+33*/        BYTE    Unknown33;
/*+34*/        BYTE    Unknown34;
/*+35*/        BYTE    Unknown35;
/*+36*/        BYTE    Unknown36;    //Personal Shop
/*+37*/        BYTE    Unknown37;
/*+38*/        WORD    Unknown38;
/*+40*/        BYTE    Unknown40;
/*+41*/        BYTE    Unknown41;
/*+42*/        BYTE    Unknown42;
BYTE gap03[2];
/*+45*/        BYTE    RespawnPosX;
/*+46*/        BYTE    RespawnPosY;
BYTE gap04[3];
/*+50*/        BYTE    ActiveMagic;
BYTE gap05[5];
/*+56*/        char    Name[25];    //need check size
BYTE gap06[39];
/*+120*/    BYTE    Unknown120;
/*+121*/    BYTE    Unknown121;
BYTE gap07[2];
/*+124*/    WORD    Unknown124;
/*+126*/    WORD    aIndex;
/*+128*/    WORD    Unknown128;
/*+130*/    WORD    Unknown130;
/*+132*/    WORD    ID;
/*+134*/    WORD    Unknown134;
/*+136*/    //maybe word
BYTE gap09[36];
/*+172*/    DWORD    MapPosX;
/*+176*/    DWORD    MapPosY;
BYTE gap10[8];
/*+188*/    float    Unknown188;
BYTE gap11[76];
/*+268*/    short    HelmSlot;
/*+270*/    BYTE    HelmLevel;
/*+271*/    BYTE    HelmExcellent;
/*+272*/    BYTE    HelmAncient;
BYTE gap12[31];
/*+304*/    short    ArmorSlot;
/*+306*/    BYTE    ArmorLevel;
/*+307*/    BYTE    ArmorExcellent;
/*+308*/    BYTE    ArmorAncient;
BYTE gap13[31];
/*+340*/    short    PantsSlot;
/*+342*/    BYTE    PantsLevel;
/*+343*/    BYTE    PantsExcellent;
/*+344*/    BYTE    PantsAncient;
BYTE gap14[31];
/*+376*/    short    GlovesSlot;
/*+378*/    BYTE    GlovesLevel;
/*+379*/    BYTE    GlovesExcellent;
/*+380*/    BYTE    GlovesAncient;
BYTE gap15[31];
/*+412*/    short    BootsSlot;
/*+414*/    BYTE    BootsLevel;
/*+415*/    BYTE    BootsExcellent;
/*+416*/    BYTE    BootsAncient;
BYTE gap16[31];
/*+448*/    short    WeaponFirstSlot;
/*+450*/    BYTE    WeaponFirstLevel;
/*+451*/    BYTE    WeaponFirstExcellent;
/*+452*/    BYTE    WeaponFirstAncient;
BYTE gap17[31];
/*+484*/    short    WeaponSecondSlot;
/*+486*/    BYTE    WeaponSecondLevel;
/*+487*/    BYTE    WeaponSecondExcellent;
/*+488*/    BYTE    WeaponSecondAncient;
BYTE gap18[31];
/*+520*/    short    WingsSlot;
/*+522*/    BYTE    WingsLevel;
/*+523*/    BYTE    WingsExcellent;
/*+524*/    BYTE    WingsAncient;
BYTE gap19[31];
/*+556*/    short    PetSlot;
/*+558*/    BYTE    PetLevel;
/*+559*/    BYTE    PetExcellent;
/*+560*/    BYTE    PetAncient;
BYTE gap20[111];
/*+672*/    DWORD    Unknown672;
/*+676*/    DWORD    Unknown676;
BYTE gap21[84];
/*+764*/    DWORD    Unknown764;
BYTE gap22[8];
/*+776*/    ObjectModel    m_Model;
/*+1424*/    BYTE    Unknown1424;    //maybe gens rank
BYTE gap23[3];
/*+1428*/    DWORD    Unknown1428;    //-> end
} ObjectPreview, * lpViewObj;
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct  //-> Complete (size: 27)
{
	WORD	ObjectID;
	char	Name[25];
} NpcNameList, * lpNpcNameList;
#pragma pack(pop)


class ViewePortInfo
{
public:

	//int iMonsterHPBar;
	//int iUserHpBar;
	//int iPartyHpBar;

	void Load();

	static void DrawPartyHP(int a1, int a2, int a3);

	void TargetMonsterHpBar();
	void AllMonsterHpBar();

	void TargetUserHpBar();
	void AllUserHpBar();

	void NewHpBarLoad();
	void InitNewHpBar();

	void PartyHPBar();



};
extern ViewePortInfo gViewePortInfo;



#endif