#include "stdafx.h"
#include "ToolKit.h"
#include "Utilits.h"
#include "Items.h"
#include "LoadItem.h"
#include "Wings.h"

//=============================================
//			Загрузка новых вещей
//=============================================
#if __ExGames__ || __EvilTwin__
char * ItemsFolder	= "ExTeam\\";
char * ItemsDir		= "Data\\ExTeam\\";
#endif

char * JewelFolder	= "ExTeam\\Jewels\\";
char * JewelDir		= "Data\\ExTeam\\Jewels\\";

char * WingsFolder	= "ExTeam\\Wings\\";
char * WingsDir		= "Data\\ExTeam\\Wings\\";

#ifdef _GRAND_SYSTEM_
char * StormWingSetFol = "ExTeam\\Items\\StormWingSet(BM)\\";
char * StormWingSetDir = "Data\\ExTeam\\Items\\StormWingSet(BM)\\";

char * CerberusSetFol = "ExTeam\\Items\\CerberusSet(GM)\\";
char * CerberusSetDir = "Data\\ExTeam\\Items\\CerberusSet(GM)\\";

char * UpperKeysSetFol = "ExTeam\\Items\\UpperKeysSet(HE)\\";
char * UpperKeysSetDir = "Data\\ExTeam\\Items\\UpperKeysSet(HE)\\";

char * HellKnightSetFol = "ExTeam\\Items\\HellKnightSet(DM)\\";
char * HellKnightSetDir = "Data\\ExTeam\\Items\\HellKnightSet(DM)\\";

char * EmbisyeonSetFol = "ExTeam\\Items\\EmbisyeonSet(LE)\\";
char * EmbisyeonSetDir = "Data\\ExTeam\\Items\\EmbisyeonSet(LE)\\";

char * SuccubusSetFol = "ExTeam\\Items\\SuccubusSet(Sum)\\";
char * SuccubusSetDir = "Data\\ExTeam\\Items\\SuccubusSet(Sum)\\";
#endif

void InitModel(int ItemID, char *ModelName, char *Folder, char *Form)
{
	char * Dir1 = Folder;
	char * Dir2 = Form;
	_asm
	{
		push -1;
		push ModelName;
		push Dir2//Form;
		push ItemID;
		mov eax, 0x005D5DC3;
		call eax;

		push 1;
		push 0x2600;
		push 0x2901;
		push Dir1//Folder;
		push ItemID;
		mov eax, 0x005D5710;
		call eax;
	}
}

void __declspec(naked) PatchNewModel()
{			
	//New Jewels
	InitModel(LOAD_ITEM(14,180), "ExcelentJewel", JewelFolder, JewelDir); // ExcelentJewel.bmd
	InitModel(LOAD_ITEM(14,181), "BlueJewel",     JewelFolder, JewelDir); // BlueJewel.bmd
	InitModel(LOAD_ITEM(14,182), "BlackJewel",    JewelFolder, JewelDir); // BlackJewel.bmd
	InitModel(LOAD_ITEM(14,183), "RedJewel",      JewelFolder, JewelDir); // RedJewel.bmd
	InitModel(LOAD_ITEM(14,184), "GreenJewel",    JewelFolder, JewelDir); // GreenJewel.bmd
	InitModel(LOAD_ITEM(14,185), "Jewel201", JewelFolder, JewelDir); 
	InitModel(LOAD_ITEM(14,186), "Jewel202", JewelFolder, JewelDir); 
	InitModel(LOAD_ITEM(14,187), "Jewel203", JewelFolder, JewelDir); 
	InitModel(LOAD_ITEM(14,188), "Jewel204", JewelFolder, JewelDir); 
	//InitModel(LOAD_ITEM(14,204), "Jewel205", ItemsFolder, ItemsDir); 
	//InitModel(LOAD_ITEM(14,205), "Jewel206", ItemsFolder, ItemsDir); 
	//InitModel(LOAD_ITEM(14,206), "Jewel207", ItemsFolder, ItemsDir); 
	//InitModel(LOAD_ITEM(14,207), "Jewel208", ItemsFolder, ItemsDir); 
	//Wings 4 rd
	InitModel(LOAD_ITEM(12,180), "Wings180", WingsFolder, WingsDir); // Wings201.bmd	- Grand Master
	InitModel(LOAD_ITEM(12,181), "Wings181", WingsFolder, WingsDir); // Wings202.bmd	- Blade Master
	InitModel(LOAD_ITEM(12,182), "Wings182", WingsFolder, WingsDir); // Wings203.bmd	- Hight Elf
	InitModel(LOAD_ITEM(12,183), "Wings183", WingsFolder, WingsDir); // Wings206.bmd	-  Summoner
	InitModel(LOAD_ITEM(12,185), "Wings185", WingsFolder, WingsDir); // Wings204.bmd	- Magic Gladiator
	InitModel(LOAD_ITEM(12,184), "Wings184", WingsFolder, WingsDir); // Wing51.bmd		- Lord Emperor
	//Wings 2.5 
	InitModel(LOAD_ITEM(12,186), "Wings186", WingsFolder, WingsDir); // Wings201.bmd	- Black Knight
	InitModel(LOAD_ITEM(12,187), "Wings187", WingsFolder, WingsDir); // Wings202.bmd	- Soul Master
	InitModel(LOAD_ITEM(12,188), "Wings188", WingsFolder, WingsDir); // Wings203.bmd	- Muse Elf
#ifdef _GRAND_SYSTEM_
	//StormWingSet(BM)
	InitModel(LOAD_ITEM(7,60),  "HelmMale75",  StormWingSetFol, StormWingSetDir);
	InitModel(LOAD_ITEM(8,60),  "ArmorMale75", StormWingSetFol, StormWingSetDir);
	InitModel(LOAD_ITEM(9,60),  "PantMale75",  StormWingSetFol, StormWingSetDir);
	InitModel(LOAD_ITEM(10,60), "GloveMale75", StormWingSetFol, StormWingSetDir);
	InitModel(LOAD_ITEM(11,60), "BootMale75",  StormWingSetFol, StormWingSetDir);
	//CerberusSet(GM)
	InitModel(LOAD_ITEM(7,61),  "HelmMale160",  CerberusSetFol, CerberusSetDir);
	InitModel(LOAD_ITEM(8,61),  "ArmorMale160", CerberusSetFol, CerberusSetDir);
	InitModel(LOAD_ITEM(9,61),  "PantMale160",  CerberusSetFol, CerberusSetDir);
	InitModel(LOAD_ITEM(10,61), "GloveMale160", CerberusSetFol, CerberusSetDir);
	InitModel(LOAD_ITEM(11,61), "BootMale160",  CerberusSetFol, CerberusSetDir);
	//UpperKeysSet(HE)
	InitModel(LOAD_ITEM(7,62),  "HelmMale76",  UpperKeysSetFol, UpperKeysSetDir);
	InitModel(LOAD_ITEM(8,62),  "ArmorMale76", UpperKeysSetFol, UpperKeysSetDir);
	InitModel(LOAD_ITEM(9,62),  "PantMale76",  UpperKeysSetFol, UpperKeysSetDir);
	InitModel(LOAD_ITEM(10,62), "GloveMale76", UpperKeysSetFol, UpperKeysSetDir);
	InitModel(LOAD_ITEM(11,62), "BootMale76",  UpperKeysSetFol, UpperKeysSetDir);
	//HellKnightSet(DM)
	InitModel(LOAD_ITEM(8,63),  "ArmorMale57", HellKnightSetFol, HellKnightSetDir);
	InitModel(LOAD_ITEM(9,63),  "PantMale57",  HellKnightSetFol, HellKnightSetDir);
	InitModel(LOAD_ITEM(10,63), "GloveMale57", HellKnightSetFol, HellKnightSetDir);
	InitModel(LOAD_ITEM(11,63), "BootMale57",  HellKnightSetFol, HellKnightSetDir);	
	//EmbisyeonSet(LE)
	InitModel(LOAD_ITEM(7,64),  "HelmMale59",  EmbisyeonSetFol, EmbisyeonSetDir);
	InitModel(LOAD_ITEM(8,64),  "ArmorMale59", EmbisyeonSetFol, EmbisyeonSetDir);
	InitModel(LOAD_ITEM(9,64),  "PantMale59",  EmbisyeonSetFol, EmbisyeonSetDir);
	InitModel(LOAD_ITEM(10,64), "GloveMale59", EmbisyeonSetFol, EmbisyeonSetDir);
	InitModel(LOAD_ITEM(11,64), "BootMale59",  EmbisyeonSetFol, EmbisyeonSetDir);
	//SuccubusSet(Sum)
	InitModel(LOAD_ITEM(7,65),  "HelmMale55",  SuccubusSetFol, SuccubusSetDir);
	InitModel(LOAD_ITEM(8,65),  "ArmorMale55", SuccubusSetFol, SuccubusSetDir);
	InitModel(LOAD_ITEM(9,65),  "PantMale55",  SuccubusSetFol, SuccubusSetDir);
	InitModel(LOAD_ITEM(10,65), "GloveMale55", SuccubusSetFol, SuccubusSetDir);
	InitModel(LOAD_ITEM(11,65), "BootMale55",  SuccubusSetFol, SuccubusSetDir);
	//Weapons
	InitModel(LOAD_ITEM(5,40), "Staff26",  "ExTeam\\Weapon\\ApocalypseStaff\\", "Data\\ExTeam\\Weapon\\ApocalypseStaff\\");
	InitModel(LOAD_ITEM(4,30), "BowDraconic",  "ExTeam\\Weapon\\DraconicBow\\", "Data\\ExTeam\\Weapon\\DraconicBow\\");
	InitModel(LOAD_ITEM(0,40), "Sword37",  "ExTeam\\Weapon\\NagaSword\\", "Data\\ExTeam\\Weapon\\NagaSword\\");
	InitModel(LOAD_ITEM(2,20), "Staff20",  "ExTeam\\Weapon\\SepScepetr\\", "Data\\ExTeam\\Weapon\\SepScepetr\\");
	InitModel(LOAD_ITEM(5,41), "Staff38",  "ExTeam\\Weapon\\SpiritStick\\", "Data\\ExTeam\\Weapon\\SpiritStick\\");
	InitModel(LOAD_ITEM(0,41), "Sword33",  "ExTeam\\Weapon\\StormSword\\", "Data\\ExTeam\\Weapon\\StormSword\\");
	//Shield
	InitModel(LOAD_ITEM(6,30), "Shield27",  "ExTeam\\Shield\\EmbisyeonShield(LE)\\", "Data\\ExTeam\\Shield\\EmbisyeonShield(LE)\\");
	InitModel(LOAD_ITEM(6,31), "Shield26",  "ExTeam\\Shield\\HellKnightShield(DM)\\", "Data\\ExTeam\\Shield\\HellKnightShield(DM)\\");
	InitModel(LOAD_ITEM(6,32), "Shield23",  "ExTeam\\Shield\\LazyWingShield(BM)\\", "Data\\ExTeam\\Shield\\LazyWingShield(BM)\\");
	InitModel(LOAD_ITEM(6,33), "ShieldofDivine",  "ExTeam\\Shield\\ShieldofDivine\\", "Data\\ExTeam\\Shield\\ShieldofDivine\\");

	InitModel(LOAD_ITEM(14,208), "suho", "ExTeam\\stone\\",  "Data\\ExTeam\\stone\\"); // Mix Stone
#endif

#if __ExGames__ || __EvilTwin__
	InitModel(LOAD_ITEM(14,200), "Jewel201", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,201), "Jewel202", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,202), "Jewel203", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,203), "Jewel204", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,204), "Jewel205", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,205), "Jewel206", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,206), "Jewel207", ItemsFolder, ItemsDir); 
	InitModel(LOAD_ITEM(14,207), "Jewel208", ItemsFolder, ItemsDir); 
#endif

#ifdef PACK_SYSTEM
	InitModel(LOAD_ITEM(14,210), "ChaosPack",	"ExTeam\\Pack\\", "Data\\ExTeam\\Pack\\");
	InitModel(LOAD_ITEM(14,211), "CreationPack","ExTeam\\Pack\\", "Data\\ExTeam\\Pack\\");
	InitModel(LOAD_ITEM(14,212), "GuardianPack","ExTeam\\Pack\\", "Data\\ExTeam\\Pack\\");
	InitModel(LOAD_ITEM(14,213), "LifePack",	"ExTeam\\Pack\\", "Data\\ExTeam\\Pack\\");
	InitModel(LOAD_ITEM(14,214), "HarmonyPack",	"ExTeam\\Pack\\", "Data\\ExTeam\\Pack\\");
#endif
#ifdef _WINGS_5LVL_
	InitModel(LOAD_ITEM(12,189), "DW_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\"); 
	InitModel(LOAD_ITEM(12,190), "DK_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	InitModel(LOAD_ITEM(12,191), "Elf_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	InitModel(LOAD_ITEM(12,192), "MG_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	InitModel(LOAD_ITEM(12,193), "MG_Wings5_2", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
	InitModel(LOAD_ITEM(12,194), "DL_Wings5", "ExTeam\\Wings5\\", "Data\\ExTeam\\Wings5\\");
#endif

	InitModel(LOAD_ITEM(14,215), "cr1", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,216), "cr5", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,217), "cr10", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,218), "cr20", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,219), "cr50", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,220), "cr100", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 

	InitModel(LOAD_ITEM(14,221), "BronzeCoin", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,222), "BronzeCoin", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 
	InitModel(LOAD_ITEM(14,223), "BronzeCoin", "ExTeam\\Coins\\", "Data\\ExTeam\\Coins\\"); 

#if(_ITEM_LOAD_)
	for(int i=0;i<gLoadItem.Count;i++)
	{
		//Console.ConsoleOutput(GREEN,"%d %d %s %s %s",gLoadItem.ILoad[i].Type,gLoadItem.ILoad[i].Index, gLoadItem.ILoad[i].BMD,	gLoadItem.ILoad[i].Dir1, gLoadItem.ILoad[i].Dir2);

		char * TT = gLoadItem.ILoad[i].BMD;
		char * TT2 = gLoadItem.ILoad[i].Dir1;
		char * TT3 = gLoadItem.ILoad[i].Dir2;

		InitModel(LOAD_ITEM(gLoadItem.ILoad[i].Type,gLoadItem.ILoad[i].Index), TT,	TT2, TT3);
		//InitModel(LOAD_ITEM(gLoadItem.ILoad[i].Type,gLoadItem.ILoad[i].Index), gLoadItem.ILoad[i].BMD,	gLoadItem.ILoad[i].Dir1, gLoadItem.ILoad[i].Dir2);
	}
#endif

	_asm
	{
		push -1;
		push 0x008C7E74;
		push 0x008C7E7C;
		push 0x1F61;
		mov eax, 0x005D5DC3;
		call eax;
		add esp, 0x10;
		mov eax, 0x005D940C;
		jmp eax;
	}	   
}


//=============================================
//			Информационный текст на вещи
//=============================================
//#if __LOCAL__
//char * Text					= "Ex-Team";
//#endif
#if __ExGames__
char * Text					= "Ex-Games";
#endif
#if __DoubleDamage__
char * Text					= "DoubleDamage";
#endif
#if __EvilTwin__
char * Text					= "Mu-Guard";
#endif
//#if __MuRain__
//char * Text					= "MuRain";
//#endif
#if __MUFreeZone__
char * Text					= "MU Free Zone";
#endif

#if _MegaMu_
char * Text					= "MuEvo";
#endif

#ifdef TEXT_TITLE
char * Text					= TEXT_TITLE;
#endif

#if __MuAltair__ || __MuReal__
char * Text					= ITEM_TITLE;
#endif

char * JewelofSkill			= "Add skill to weapons";
char * JewelofExcellent		= "Excellent option add to Items";
char * JewelofDivinity		= "Add Pendants and Ring level to +9";
char * JewelofLuck			= "Luck option add to Items";
char * JewelofAssembly		= "Add item option to +28";
char * JewelOfLevel			= "Add level";
char * JewelOfEvalution		= "Exellent Status Item";
char * JewelOfAncent		= "Ancent Status Item";
char * JewelOfOption		= "Add item option to +28";

#if __ExGames__||__EvilTwin__
char * TalismanTitle = "Talisman System";
char * TalismanOfDamage = "Added 10%% to the Damage";
char * TalismanOfDefence = "Added 10%% to the Defense";
char * TalismanOfDouble = "Added 3%% to the Double Damage";
char * TalismanOfExellent = "Added 5%% to the Exellent Damage";
char * TalismanOfCritical = "Added 5%% to the Critical Damage";
char * TalismanOfExperience = "Added 10%% to the Experience";
char * TalismanOfIgnore = "Added 3%% to the Ignore Defense";
char * TalismanOfReflect = "Added 5%% to the Damage Reflect";
#endif

#ifdef _GRAND_SYSTEM_
//Grand Item Text
char * GrandItemText		= "Grand Hero Item";
char * GrandOpion1			= "Defense +30";
char * GrandOpion2			= "Attack Damage +30";
char * FullItem				= "Add if Full Set";
char * GrandOpion3			= "Critical Damage +5%%";

char * ExStoneText			= "Need to Create Grand Item";

//Grand Weapon Text
char * GrandWeaponDKDL1		= "Double Damage +3%%";
char * GrandWeaponDKDL2		= "Ignore Defense +3%%";
char * GrandWeaponOther1	= "Double Damage +6%%";
char * GrandWeaponOther2	= "Ignore Defense +6%%";
#endif

char *nText = "100 000 000 Zen";
char *nText2 = "500 000 000 Zen";
char *nText3 = "1 000 000 000 Zen";

char *nText4 = "1 cr";
char *nText5 = "5 cr";
char *nText6 = "10 cr";
char *nText7 = "20 cr";
char *nText8 = "50 cr";
char *nText9 = "100 cr";

#ifdef _Mu_Online_MD_
	char * Text = "Mu Online MD";
#endif


#ifdef _WINGS4_NEW_OPT_
	char * w4Opt1 = "Critical Damage increase 5%%";
	char * w4Opt2 = "Ignor Defense enemy 5%%";
	char * w4Opt3 = "Recover hp 5%%";
	char * w4Opt4 = "Increase damage : 30%%";
	char * w4Opt5 = "Absorb Damage: 15%%";
	char * w4Opt6 = "Increaase Wizard Damage: 15%%";
#endif
#ifdef _WINGS5_NEW_OPT_
	char * w5Opt1 = "Critical Damage Increase 7%%";
	char * w5Opt2 = "Reflect Damage increase 7%%";
	char * w5Opt3 = "Increase Defense: 15%%";
	char * w5Opt4 = "Absorb Damage: 20%%";
	char * w5Opt5 = "Ignor Defense enemy 10%%";
	char * w5Opt6 = "Increase HP recover 25%%";
#endif


DWORD ItemInfoType;

//============================================================================
void __declspec(naked) ItemInfoText()//finished
{
// Color de la tabla:
//------------------------------------------------------------------------
// 0x00 = Белый
// 0x01 = Синий
// 0x02 = Красный
// 0x03 = Желтый
// 0x04 = Зеленый
// 0x05 = Красная оболочка внутри белым
// 0x06 = Розовый
// 0x07 = Синяя оболочка внутри белый
// 0x08 = Желтая оболочка внутри черным 
// 0x09 = Синяя оболочка внутри зеленый
// 0x0A = Серый
// 0x0B = Фиолетовый

	_asm
	{
		movsx edx,WORD PTR DS:[EDI]
		mov ItemInfoType, edx
	}

	if(ItemInfoType == ITEMGET(12,15))	//Default Chaos
	{
		_asm
		{
			CMP WORD PTR DS:[EDI],0x180F
			//JNE SHORT 00594E93
			PUSH 0x23E                                
			MOV ECX, 0x07AAD828 //MOV ECX,OFFSET 07AAD828                 
			mov esi, 0x00402F50//CALL 0x00402F50  
			call esi
			PUSH EAX
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			LEA EAX,[EAX*4+EAX]
			LEA EAX,[EAX*4+EAX]
			LEA ECX,[EAX*4+0x7BE1238]
			PUSH ECX
			mov esi, 0x00851348//00851348
			call esi//CALL 00851348
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],EBX
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX

			mov esi, 0x00594E93 //1.03k
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,180))	//Jewel Of Exellent
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelofExcellent
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,181))	//JewelofDivinity
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelofDivinity
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,182))	//Jewel Of Divinity
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelofLuck
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,182))	//JewelofLuck
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelofLuck
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,183))	//JewelOfSkill
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelofSkill
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,184))	//JewelOfLevel
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelOfLevel
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,185))	//JewelOfEvalution
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelOfEvalution
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,186))	//JewelOfAncent
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelOfAncent
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,187))	//JewelOfOption
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH JewelOfOption
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x00	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}

//====================================
	else if(ItemInfoType >= ITEMGET(12,186) && ItemInfoType <= ITEMGET(12,188))	//New Wings
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			//=======
			mov esi, 0x00594E93
			jmp esi;
		}
	}
	else if(ItemInfoType >= ITEMGET(12,180) && ItemInfoType <= ITEMGET(12,185))	//New Wings
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
#ifdef _WINGS4_NEW_OPT_
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt1	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt2	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt3	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt4	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt5	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt6	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
#endif
			//=======
			mov esi, 0x00594E93
			jmp esi;
		}
	}
	else if(ItemInfoType >= ITEMGET(12,180) && ItemInfoType <= ITEMGET(12,188))	//New Wings
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
#ifdef _WINGS4_NEW_OPT_
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt1	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt2	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt3	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt4	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt5	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w4Opt6	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
#endif
			//=======
			mov esi, 0x00594E93
			jmp esi;
		}
	}
#ifdef _WINGS_5LVL_
	else if(ItemInfoType >= ITEMGET(12,189) && ItemInfoType <= ITEMGET(12,194))	//Wings 5 lvl
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX

#ifdef _WINGS4_NEW_OPT_
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w5Opt1	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w5Opt2	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w5Opt3	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w5Opt4	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w5Opt5	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH w5Opt6	//<<---
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
#endif
			//----
			mov esi, 0x00594E93
			jmp esi;
		}
	}
#endif
#if __ExGames__||__EvilTwin__
	else if(ItemInfoType == ITEMGET(14,200))	//Talisman Of Damage
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfDamage
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,201))	//Talisman Of Defence
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfDefence
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,202))	//Talisman Of Double
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfDouble			//Test
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,203))	//Talisman Of Exellent
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfExellent			//Test
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,204))	//Talisman Of Critical
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfCritical			//Test
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,205))	//Talisman Of Experience
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfExperience			//Test
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,206))	//Talisman Of Ignore
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfIgnore			//Test
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,207))	//Talisman Of Reflect
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanTitle
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH TalismanOfReflect			//Test
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
#endif
#ifdef _GRAND_SYSTEM_
	else if(ItemInfoType == ITEMGET(14,208))	//ExStone
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH ExStoneText
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if( ItemInfoType >= ITEMGET(7,60) && ItemInfoType <= ITEMGET(7,65)  ||	//Grand Item Option
			 ItemInfoType >= ITEMGET(8,60) && ItemInfoType <= ITEMGET(8,65)  ||
			 ItemInfoType >= ITEMGET(9,60) && ItemInfoType <= ITEMGET(9,65)  ||
			 ItemInfoType >= ITEMGET(10,60) && ItemInfoType <= ITEMGET(10,65)||
			 ItemInfoType >= ITEMGET(11,60) && ItemInfoType <= ITEMGET(11,65) )
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandItemText
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x05	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandOpion1
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandOpion2
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(0,40) || ItemInfoType == ITEMGET(0,41) || ItemInfoType == ITEMGET(2,20))
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandItemText
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x05	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandWeaponDKDL1
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandWeaponDKDL2
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93
			jmp esi;
		}
	}
	else if (ItemInfoType == ITEMGET(4,30) || ItemInfoType == ITEMGET(6,32) || ItemInfoType == ITEMGET(6,33) ||
			 ItemInfoType == ITEMGET(5,40) || ItemInfoType == ITEMGET(5,41) || ItemInfoType == ITEMGET(6,30) || ItemInfoType == ITEMGET(6,31))
	{
		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandItemText
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x05	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandWeaponOther1
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH GrandWeaponOther2
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x04	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93
			jmp esi;
		}
	}
	////
	else if(ItemInfoType == ITEMGET(14,221))	//Zen Coin
	{
		

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,222))	//Zen Coin
	{
		//char *nText = "500 000 000 Zen";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText2
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,223))	//Zen Coin
	{
		//char *nText = "1 000 000 000 Zen";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText3
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,215))	//cr Coin
	{
		//char *nText = "1 Kp";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText4
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,216))	//cr Coin
	{
	//	char *nText = "5 Kp";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText5
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,217))	//cr Coin
	{
		//char *nText = "10 Kp";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText6
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,218))	//cr Coin
	{
		//char *nText = "20 Kp";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText7
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,219))	//cr Coin
	{
		//char *nText = "50 Kp";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText8
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
	else if(ItemInfoType == ITEMGET(14,220))	//cr Coin
	{
		//char *nText = "100 Kp";

		_asm
		{
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH Text
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x08
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			LEA EAX,DWORD PTR DS:[EAX+EAX*4]
			PUSH nText9
			LEA EDX,DWORD PTR DS:[EAX+EAX*4]
			LEA EAX,DWORD PTR DS:[EDX*4+0x7BE1238]
			PUSH EAX
			mov esi, 0x00851348
			call esi
			MOV EAX,DWORD PTR DS:[0x7C13C7C]
			ADD ESP,8
			MOV DWORD PTR DS:[EAX*4+0x7BE239C],0x0B	//Color
			MOV DWORD PTR DS:[EAX*4+0x7C114A0],EBX
			INC EAX
			MOV DWORD PTR DS:[0x7C13C7C],EAX
			//----
			mov esi, 0x00594E93 
			jmp esi;
		}
	}
#endif
	else
	{
		_asm
		{
			mov esi, 0x00594E93 //1.03k
			jmp esi;
		}
	}	
	_asm
	{
		mov esi, 0x00594E93 //1.03k
		jmp esi;
	}
}

//=============================================
//			Визуальная цена вещи
//=============================================
DWORD PriceItemType;
DWORD PriceItem;
void __declspec(naked) ItemsPrices()
{
	PriceItem = 0;
	_asm
	{
		mov ecx, dword ptr ss:[ebp+0x8];
		movsx edx, word ptr ds:[ecx];
		mov PriceItemType, edx;
	}

	if (PriceItemType == ITEMGET(14,13)) // Jewel of Bless (Hook place)
	{
		PriceItem = 9000000; // Item Price (Default: 9000000)
	}
	else if (PriceItemType == ITEMGET(14,180)) // Jewel of Exelent
	{
		PriceItem = 50000000; // Item Price
	}
	else if (PriceItemType == ITEMGET(14,181)) // Jewel of Divinity
	{
		PriceItem = 40000000; // Item Price
	}
	else if (PriceItemType == ITEMGET(14,182)) // Jewel of Luck
	{
		PriceItem = 30000000; // Item Price
	}
	else if (PriceItemType == ITEMGET(14,183)) // Jewel of Assembly
	{
		PriceItem = 20000000; // Item Price
	}
	else if (PriceItemType == ITEMGET(14,184)) // Jewel of Skill
	{
		PriceItem = 10000000; // Item Price
	}


	if (PriceItem == 0)
	{
		_asm
		{
			mov edx, 0x0050D0D3;
			jmp edx;
		}
	}
	else
	{
		_asm
		{
			mov eax, PriceItem;
			mov dword ptr ss:[ebp-0x8], eax;
			mov dword ptr ss:[ebp-0x4], 0x0;
			mov eax, 0x0050E3DF;
			jmp eax;
		}
	}
}

//=============================================
//			Золотой цвет имени вещей
//=============================================
DWORD ColorItemType;
BOOL ColorItem;
void __declspec(naked) ItemsNameColor()
{
	ColorItem = FALSE;
	_asm
	{
		mov ColorItemType, eax;
	}

	if (ColorItemType == ITEMGET(14,14)) // Jewel of Soul (Hook place)
	{
		ColorItem = TRUE; // Yellow Item Name (Default: TRUE)
	}
	else if (ColorItemType == ITEMGET(14,180)) // Jewel of Exelent
	{
		ColorItem = TRUE; // Yellow Item Name
	}
	else if (ColorItemType == ITEMGET(14,181)) // Jewel of Divinity
	{
		ColorItem = TRUE; // Yellow Item Name
	}
	else if (ColorItemType == ITEMGET(14,182)) // Jewel of Luck
	{
		ColorItem = TRUE; // Yellow Item Name
	}
	else if (ColorItemType == ITEMGET(14,183)) // Jewel of Assembly
	{
		ColorItem = TRUE; // Yellow Item Name
	}
	else if (ColorItemType == ITEMGET(14,184)) // Jewel of Skill
	{
		ColorItem = TRUE; // Yellow Item Name
	}
	else if (ColorItemType == ITEMGET(14,185)) // Jewel of Blue
	{
		ColorItem = TRUE; // Yellow Item Name
	}
	else if (ColorItemType > ITEMGET(14,185) && ColorItemType < ITEMGET(14,255)) // ExStone
	{
		ColorItem = TRUE; // Yellow Item Name
	}

	if (ColorItem == TRUE)
	{
		_asm
		{
			mov edx, 0x0059061B;
			jmp edx;
		}
	}
	else
	{
		_asm
		{
			mov edx, 0x005904F8;
			jmp edx;
		}
	}
}

//=============================================
//			Запрет на выбрасывание вещей
//=============================================
DWORD DropItemType;
BOOL DropItem;
DWORD DropItemOff;
void __declspec(naked) ItemsDrop()
{
	DropItem = TRUE;
	_asm
	{
		mov DropItemType, eax;
	}

	if (DropItemType == ITEMGET(14,13)) // Jewel of Bless (Hook place)
	{
		DropItem = FALSE; // Item Drop (Default: FALSE)
	}
	else if (DropItemType == ITEMGET(14,180)) // Jewel of Exelent
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,181)) // Jewel of Divinity
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,182)) // Jewel of Luck
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,183)) // Jewel of Assembly
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,184)) // Jewel of Skill
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,185)) // Jewel of Skill
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,186)) // Jewel of Skill
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,187)) // Jewel of Skill
	{
		DropItem = FALSE; // Item Drop
	}
	else if (DropItemType == ITEMGET(14,188)) // Jewel of Skill
	{
		DropItem = FALSE; // Item Drop
	}
	if (DropItem == FALSE)
	{
		_asm
		{
			mov DropItemOff, 0x0059DCDE;
			jmp DropItemOff;
		}
	}
	else
	{
		_asm
		{
			mov DropItemOff, 0x0059DBD5;
			jmp DropItemOff;
		}
	}
}

//=============================================
//	Разрешить бросать вещи в доспехи (Разрешить заточку)
//=============================================
DWORD SwitItemType;
BOOL SwitItem;
void __declspec(naked) ItemsSwitch()
{
	SwitItem = FALSE;
	_asm
	{
		mov edx, dword ptr ss:[ebp-0x14];
		movsx eax, word ptr ds:[edx];
		mov SwitItemType, eax;
	}

	if (SwitItemType == ITEMGET(14,13)) // Jewel of Bless (Hook place)
	{
		SwitItem = TRUE; // Is Jewel Item (Default: TRUE)
	}
	else if (SwitItemType == ITEMGET(14,180)) // Jewel of Exelent
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,181)) // Jewel of Divinity
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,182)) // Jewel of Luck
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,183)) // Jewel of Assembly
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,184)) // Jewel of Skill
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,185)) // Jewel of Skill
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,186)) // Jewel of Skill
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,187)) // Jewel of Skill
	{
		SwitItem = TRUE; // Is Jewel Item
	}
	else if (SwitItemType == ITEMGET(14,188)) // Jewel of Skill
	{
		SwitItem = TRUE; // Is Jewel Item
	}

	if (SwitItem == TRUE)
	{
		_asm
		{
			mov eax, 0x007575E0;
			jmp eax;
		}
	}
	else
	{
		_asm
		{
			mov eax, 0x00757597;
			jmp eax;
		}
	}
}

//=============================================
//	Золотой цвет имени вещей лежащей на полу
//=============================================
DWORD Color2ItemType;
BOOL Color2Item;
void __declspec(naked) ItemsColorDrop()
{
	Color2Item = FALSE;
	_asm
	{
		mov Color2ItemType, eax;
	}

	if (Color2ItemType == ITEMGET(14,13) + 834) // Jewel of Bless (Hook place)
	{
		Color2Item = TRUE; // Yellow Item Name on Floor (Default: TRUE)
	}
	else if (Color2ItemType == ITEMGET(14,180) + 834) // Jewel of Exelent
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,181) + 834) // Jewel of Divinity
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,182) + 834) // Jewel of Luck
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,183) + 834) // Jewel of Assembly
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,184) + 834) // Jewel of Skill
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,185) + 834) // Jewel of Blue
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,186) + 834) // Jewel of Blue
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,187) + 834) // Jewel of Blue
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}
	else if (Color2ItemType == ITEMGET(14,208) + 834) // Jewel of Blue
	{
		Color2Item = TRUE; // Yellow Item Name on Floor
	}

	if (Color2Item == TRUE)
	{
		_asm
		{
			mov edx, 0x0059CC06;
			jmp edx;
		}
	}
	else
	{
		_asm
		{
			mov edx, 0x0059AD29;
			jmp edx;
		}
	}
}

//=============================================
//	Разрешить бросать вещи в вещи выше доспехов
//=============================================
BOOL UseItemType;
DWORD UseItem;
DWORD UseItem2;
void __declspec(naked) ItemsUseItem()
{
	UseItemType = FALSE;

	_asm
	{
		mov edx, dword ptr ss:[ebp-0x14];
		movsx eax, word ptr ds:[edx];
		mov UseItem, eax;
		mov edx, dword ptr ss:[ebp-0x30];
		mov UseItem2, edx;
	}

	if (UseItem == ITEMGET(14,181)) // Jewel of Assembly
	{
		if ( UseItem2 == ITEMGET(13,8)  || UseItem2 == ITEMGET(13,9) || // Pendants & Rings
			UseItem2 == ITEMGET(13,12) || UseItem2 == ITEMGET(13,13) || 
			UseItem2 == ITEMGET(13,21) || UseItem2 == ITEMGET(13,22) || 
			UseItem2 == ITEMGET(13,23) || UseItem2 == ITEMGET(13,24) || 
			UseItem2 == ITEMGET(13,25) || UseItem2 == ITEMGET(13,26) || 
			UseItem2 == ITEMGET(13,27) || UseItem2 == ITEMGET(13,28))
		{
			UseItemType = TRUE; // Can Use Jewel
		}
	}
	//Jewel Of Bless,Soul,Life in New Wings
	if (UseItem == ITEMGET(14,13) || UseItem == ITEMGET(14,14) || UseItem == ITEMGET(14,16))
	{
		if ( UseItem2 >= ITEMGET(12,180) && UseItem2 <= ITEMGET(12,END_NEW_WING) )	//Custom Wings4
		{
			UseItemType = TRUE; // Can Use Jewel
		}
	}

	if (UseItemType == TRUE)
	{
		_asm
		{
			mov ecx, 0x0075780B;
			jmp ecx;
		}
	}
	else
	{
		_asm
		{
			mov ecx, dword ptr ss:[ebp-0x28];
			and ecx, 0x0FF;
			test ecx, ecx;
			je End;
			mov edx, 0x0075780B;
			jmp edx;

End:
			mov edx, 0x007579CC;
			jmp edx;
		}
	}
}

DWORD aItem = 0;
DWORD aTrueJmp = 0x0059F37C;
DWORD aFalseJmp = 0x0059ECA5;
void __declspec(naked) AliginModeItem()
{
	_asm
	{
		MOV aItem, ESI
	}

	if(aItem == 0x1F7D)
	{
		_asm JMP aTrueJmp
	}
//#ifdef _CR_COIN_
	else if(aItem >= LOAD_ITEM(14,215) &&  aItem <= LOAD_ITEM(14,220))
	{
		_asm JMP aTrueJmp
	}
//#endif
//#ifdef _ZEN_COIN_
	else if( aItem >= LOAD_ITEM(14,221) && aItem <= LOAD_ITEM(14,223) )
	{
		_asm JMP aTrueJmp
	}
//#endif
	else
	{
		_asm JMP aFalseJmp
	}
}

void NewItemsInit()
{
	SetNop(0x00594E4D, 22);
	WriteJmp(0x00594E4D, (DWORD)&ItemInfoText);

	SetNop(0x005D93F3, 25);
	WriteJmp(0x005D93F3, (DWORD)&PatchNewModel);

	SetNop(0x0050D0B2, 33);
	WriteJmp(0x0050D0B2, (DWORD)&ItemsPrices);

	SetNop(0x005904EE, 10);
	WriteJmp(0x005904EE, (DWORD)&ItemsNameColor);

	SetNop(0x0059DBCB, 10);
	WriteJmp(0x0059DBCB, (DWORD)&ItemsDrop);

	SetNop(0x0075758A, 13);
	WriteJmp(0x0075758A, (DWORD)&ItemsSwitch);

	SetNop(0x0059AD1E, 11);
	WriteJmp(0x0059AD1E, (DWORD)&ItemsColorDrop);

	SetNop(0x007577FA, 17);
	WriteJmp(0x007577FA, (DWORD)&ItemsUseItem);

	SetNop(0x0059EC99,6);
	WriteJmp(0x0059EC99, (DWORD)&AliginModeItem);
}