#include "Utilits.h"
#include "Stdafx.h"
#include "MakePreviewCharSet.h"
#include "Wings.h"
#include "Console.h"
#include "Player.h"
#include "TMemory.h"

//---------------------------------------------------------------------------
// Main 1.03k Jpn
//MapOffset: 8C5CF8
//ObjOffset: 8D6F7C
//ObjMakePreviewCharSet mObjMakePreviewCharSet	= (ObjMakePreviewCharSet)0x4FDFE0;	//Main 1.03Y+ JPN: 51564C ; Main 1.03k JPN: 4FDFE0
//// ----
//IsChaosCastle		gIsChaosCastle				= (IsChaosCastle)0x490280;			//Main 1.03Y+ JPN: 49A450 ; Main 1.03k JPN: 490280
//ItemCharSetConvert	gItemCharSetConvert			= (ItemCharSetConvert)0x504A69;		//Main 1.03Y+ JPN: 51C4EC ; Main 1.03k JPN: 504A69
//AmpersandConvert	gAmpersandConvert			= (AmpersandConvert)0x45A030;		//Main 1.03Y+ JPN: 463890 ; Main 1.03k JPN: 45A030
//SetObjMaunt			gSetObjMaunt				= (SetObjMaunt)0x4AC2C4;			//Main 1.03Y+ JPN: 4B6B54 ; Main 1.03k JPN: 4AC2C4
//SetObjMaunt2		gSetObjMaunt2				= (SetObjMaunt2)0x4ABF7C;			//Main 1.03Y+ JPN: 4B680C ; Main 1.03k JPN: 4ABF7C
//ObjPetGetThis		gObjPetGetThis				= (ObjPetGetThis)0x81AB71;			//Main 1.03Y+ JPN: 8831F1 ; Main 1.03k JPN: 81AB71
//SetObjPetOnSwitch	gSetObjPetOnSwitch			= (SetObjPetOnSwitch)0x81BA70;		//Main 1.03Y+ JPN: 884245 ; Main 1.03k JPN: 81BA70
//SetObjPetReset		gSetObjPetReset				= (SetObjPetReset)0x81BDA7;			//Main 1.03Y+ JPN: 88457C ; Main 1.03k JPN: 81BDA7
//CheckPetStatus		gCheckPetStatus				= (CheckPetStatus)0x4997AD;			//Main 1.03Y+ JPN: 4A3A7D ; Main 1.03k JPN: 4997AD
//ReturnPetSlot		gReturnPetSlot				= (ReturnPetSlot)0x4ABEB0;			//Main 1.03Y+ JPN: 4B6740 ; Main 1.03k JPN: 4ABEB0
//ObjPreviewDarkRaven	gObjPreviewDarkRaven		= (ObjPreviewDarkRaven)0x4A2AD6;	//Main 1.03Y+ JPN: 4ACDA6 ; Main 1.03k JPN: 4A2AD6
//// ----
//Objsub_49A50A		sub_49A50A					= (Objsub_49A50A)0x49033A;			//Main 1.03Y+ JPN: 49A50A ; Main 1.03k JPN: 49033A
//Objsub_514A21		sub_514A21					= (Objsub_514A21)0x4FC216;			//Main 1.03Y+ JPN: 514A21 ; Main 1.03k JPN: 4FC216
//Objsub_4ADABB		sub_4ADABB					= (Objsub_4ADABB)0x4A3820;			//Main 1.03Y+ JPN: 4ADABB ; Main 1.03k JPN: 4A3820
////---------------------------------------------------------------------------
//
//Objdword_7B65114	dword_7B65114				= (Objdword_7B65114)0x7A723B8;		//Main 1.03Y+ JPN: 7B65114 ; Main 1.03k JPN: 7A723B8
//Objdword_7BA6278	dword_7BA6278				= (Objdword_7BA6278)0x7AB3518;		//Main 1.03Y+ JPN: 7BA6278 ; Main 1.03k JPN: 7AB3518
//Objdword_7B650F8	dword_7B650F8				= (Objdword_7B650F8)0x7A7239C;		//Main 1.03Y+ JPN: 7B650F8 ; Main 1.03k JPN: 7A7239C
//DWORD				gObjGameState				= *(DWORD*)oObjState;
//---------------------------------------------------------------------------
ObjMakePreviewCharSet mObjMakePreviewCharSet	= (ObjMakePreviewCharSet)0x4FDFE0;	//Main 1.03Y+ JPN: 51564C ; Main 1.03k JPN: 4FDFE0
// ----
IsChaosCastle		gIsChaosCastle				= (IsChaosCastle)0x490280;			//Main 1.03Y+ JPN: 49A450 ; Main 1.03k JPN: 490280
ItemCharSetConvert	gItemCharSetConvert			= (ItemCharSetConvert)0x504A69;		//Main 1.03Y+ JPN: 51C4EC ; Main 1.03k JPN: 504A69
AmpersandConvert	gAmpersandConvert			= (AmpersandConvert)0x45A030;		//Main 1.03Y+ JPN: 463890 ; Main 1.03k JPN: 45A030
SetObjMaunt			gSetObjMaunt				= (SetObjMaunt)0x4AC2C4;			//Main 1.03Y+ JPN: 4B6B54 ; Main 1.03k JPN: 4AC2C4
SetObjMaunt2		gSetObjMaunt2				= (SetObjMaunt2)0x4ABF7C;			//Main 1.03Y+ JPN: 4B680C ; Main 1.03k JPN: 4ABF7C
ObjPetGetThis		gObjPetGetThis				= (ObjPetGetThis)0x81AB71;			//Main 1.03Y+ JPN: 8831F1 ; Main 1.03k JPN: 81AB71
SetObjPetOnSwitch	gSetObjPetOnSwitch			= (SetObjPetOnSwitch)0x81BA70;		//Main 1.03Y+ JPN: 884245 ; Main 1.03k JPN: 81BA70
SetObjPetReset		gSetObjPetReset				= (SetObjPetReset)0x81BDA7;			//Main 1.03Y+ JPN: 88457C ; Main 1.03k JPN: 81BDA7
CheckPetStatus		gCheckPetStatus				= (CheckPetStatus)0x4997AD;			//Main 1.03Y+ JPN: 4A3A7D ; Main 1.03k JPN: 4997AD
ReturnPetSlot		gReturnPetSlot				= (ReturnPetSlot)0x4ABEB0;			//Main 1.03Y+ JPN: 4B6740 ; Main 1.03k JPN: 4ABEB0
ObjPreviewDarkRaven	gObjPreviewDarkRaven		= (ObjPreviewDarkRaven)0x4A2AD6;	//Main 1.03Y+ JPN: 4ACDA6 ; Main 1.03k JPN: 4A2AD6
// ----
Objsub_49A50A		sub_49A50A					= (Objsub_49A50A)0x49033A;			//Main 1.03Y+ JPN: 49A50A ; Main 1.03k JPN: 49033A
Objsub_514A21		sub_514A21					= (Objsub_514A21)0x4FC216;			//Main 1.03Y+ JPN: 514A21 ; Main 1.03k JPN: 4FC216
Objsub_4ADABB		sub_4ADABB					= (Objsub_4ADABB)0x4A3820;			//Main 1.03Y+ JPN: 4ADABB ; Main 1.03k JPN: 4A3820
//---------------------------------------------------------------------------

Objdword_7B65114	dword_7B65114				= (Objdword_7B65114)0x7A723B8;		//Main 1.03Y+ JPN: 7B65114 ; Main 1.03k JPN: 7A723B8
Objdword_7BA6278	dword_7BA6278				= (Objdword_7BA6278)0x7AB3518;		//Main 1.03Y+ JPN: 7BA6278 ; Main 1.03k JPN: 7AB3518
Objdword_7B650F8	dword_7B650F8				= (Objdword_7B650F8)0x7A7239C;		//Main 1.03Y+ JPN: 7B650F8 ; Main 1.03k JPN: 7A7239C
DWORD				gObjGameState				= *(DWORD*)oObjState;
//---------------------------------------------------------------------------
//51551C -> 14 Calls
//BYTE gLevelSmallConvert(int SmallValue)
//{
//  BYTE ResultValue;
//  // ----
//  switch(SmallValue)
//  {
//    case 0:
//      ResultValue = 0;
//      break;
//	  // --
//    case 1:
//      ResultValue = 3;
//      break;
//	  // --
//    case 2:
//      ResultValue = 5;
//      break;
//	  // --
//    case 3:
//      ResultValue = 7;
//      break;
//	  // --
//    case 4:
//      ResultValue = 9;
//      break;
//	  // --
//    case 5:
//      ResultValue = 11;
//      break;
//	  // --
//    case 6:
//      ResultValue = 13;
//      break;
//	  // --
//    case 7:
//      ResultValue = 15;
//      break;
//	  // --
//    default:
//      ResultValue = 0;
//      break;
//  }
//  // ----
//  return ResultValue;
//}
//---------------------------------------------------------------------------
BYTE gLevelSmallConvert(int SmallValue)
{
	BYTE ResultValue;
	// ----
	switch(SmallValue)
	{
	case 0:
		ResultValue = 0;
		break;
		// --
	case 1:
		ResultValue = 3;
		break;
		// --
	case 2:
		ResultValue = 5;
		break;
		// --
	case 3:
		ResultValue = 7;
		break;
		// --
	case 4:
		ResultValue = 9;
		break;
		// --
	case 5:
		ResultValue = 11;
		break;
		// --
	case 6:
		ResultValue = 12;
		break;
		// --
	case 7:
		ResultValue = 13;
		break;
		// --
	default:
		ResultValue = 0;
		break;
	}
	// ----
	return ResultValue;
} 
//515596 -> 1 Call
int gMakePreviewSoldierElf(int Struct) 
{
	Preview * gPreview = &*(Preview*)Struct;
	// ----
//	gPreview->WeaponFirstSlot		= ITEM2(2, 16);
//	gPreview->WeaponFirstLevel	= 13;
////	 ----
//	gPreview->WeaponSecondSlot	= ITEM2(6, 21);
//	gPreview->WeaponSecondLevel	= 13;
//	 ----
	gPreview->WingsSlot			= ITEM2(12, 188);
//	 ----
	gPreview->HelmSlot			= ITEM2(7, 24);
	gPreview->HelmLevel			= 13;
//	 ----
	gPreview->ArmorSlot			= ITEM2(8, 24);
	gPreview->ArmorLevel		= 13;
//	 ----
	gPreview->PantsSlot			= ITEM2(9, 24);
	gPreview->PantsLevel		= 13;
//	 ----
	gPreview->GlovesSlot		= ITEM2(10, 24);
	gPreview->GlovesLevel		= 13;
//	 ----
	gPreview->BootsSlot			= ITEM2(11, 24);
	gPreview->BootsLevel		= 13;
	// ----
	gPreview->Action			= 11;
	gPreview->ModelScale		= 0x3F800000;
	gPreview->SelectZone		+= 70.0;
	// ----
	gPreview->PKLevel			= 10;
	return gPreview->Unknown700;
}
//---------------------------------------------------------------------------

//51564C -> 7 Calls
int gObjMakePreviewCharSet(int Index, BYTE * CharSet, int UseStruct, int Mode) 
{
	if( Mode )
	{
//		TDEBUG("Mode == %d");
	}
	int Result;
	int ObjPreview;
	// ----
	if( UseStruct )
	{
		ObjPreview = UseStruct;
	}
	else
	{
		ObjPreview = CS_GET_STRUCT(Index, dword_7B650F8);
	}
//	 ----
	Result = ObjPreview + 700;
	// ----
	Preview * gPreview = &*(Preview*)ObjPreview;
	// ----
	if( gPreview->Unknown748 == (ITEM_INTER - 8) )
	{
		short WeaponFirstType = CS_GET_WEAPON(CharSet[11], CharSet[0]);
		// ----
		if( WeaponFirstType == CS_EMPTY_WEAPON )
		{
			gPreview->WeaponFirstSlot		= CS_EMPTY_SLOT;
			gPreview->WeaponFirstExcellent	= NULL;
			gPreview->WeaponFirstAncient	= NULL;
		}
		else
		{
			gPreview->WeaponFirstSlot = WeaponFirstType + ITEM_INTER;
		}
		// ----
		short WeaponSecondType = CS_GET_WEAPON(CharSet[12], CharSet[1]);
		// ----
		if( WeaponSecondType == CS_EMPTY_WEAPON )
		{
			gPreview->WeaponSecondSlot		= CS_EMPTY_SLOT;
			gPreview->WeaponSecondExcellent	= NULL;
			gPreview->WeaponSecondAncient	= NULL;
		}
		else
		{
			if( gAmpersandConvert(pPlayerClass(ObjPreview)) != ObjClass::DarkLord || WeaponSecondType != ITEM(5, 5) )
			{
				gPreview->WeaponSecondSlot = WeaponSecondType + ITEM_INTER;
			}
			else
			{
				int CallArg = *(int*)sub_4ADABB(*(int*)dword_7BA6278 + 4413); // # Need check
				gObjPreviewDarkRaven(ObjPreview);
				// ----
				/*
				if ( !gIsChaosCastle(gObjUser.MapNumber) )
				{
					//TDEBUG("sub_4AECB0(CallArg)");
					//sub_4AECB0(CallArg);
				}
				*/
			}
		}
		if( (CS_SET_1(CharSet[4]) & 3) == 3 )
		{
			BYTE SecondWingsType = CharSet[8] & 7;

			//Console.ConsoleOutput(GREEN,"[SecondWingsType] %d",(int)SecondWingsType);
			// ----
			if( SecondWingsType )
			{
				switch( SecondWingsType )
				{
				case 1: // Wings Of Spirit
					gPreview->WingsSlot = ITEM2(12, 3);
					break;
				case 2: // Wings of Soul
					gPreview->WingsSlot = ITEM2(12, 4);
					break;
				case 3: // Wings of Dragon
					gPreview->WingsSlot = ITEM2(12, 5);
					break;
				case 4: // Wings of Darkness
					gPreview->WingsSlot = ITEM2(12, 6);
					break;
				case 5: // Cape Of Lord
					gPreview->WingsSlot = ITEM2(13, 30);
					break;
					// --
				case 6: // Wings Of Curse
					gPreview->WingsSlot = ITEM2(12, 41);
					break;
					// --
				case 7: // Wings Of Despair
					gPreview->WingsSlot = ITEM2(12, 42);
					break;
					// --
				default: // Other Wings
					gPreview->WingsSlot = ITEM2(12, 3) + SecondWingsType;
					break;
				}
			}
			else
			{
				gPreview->WingsSlot		= CS_EMPTY_SLOT;
				gPreview->Unknown459	= NULL;
				gPreview->Unknown460	= NULL;
			}
		}
		else	//1 LvL Wings
		{
			gPreview->WingsSlot = ITEM2(12, 0) + (CS_SET_1(CharSet[4]) & 3);	// Fix 1 lvl Wings Visual
		}
		// 3 rd Wings
		// ----
		BYTE ThirdWingsType = CS_SET_1(CharSet[15]) & 7;
		// ----
		if( ThirdWingsType > 0 )
		{
			if( ThirdWingsType == 6 )
			{
				gPreview->WingsSlot = ITEM2(12, 43);
			}
			else
			{
				gPreview->WingsSlot = ITEM2(12, 35) + ThirdWingsType;
			}
		}
		// ----
//#if CLIENT_TYPE == 1	//-> Season 5.4 GMO
		//BYTE MiniWingsType = CharSet[16] >> 5;
		//// ----
		//if( MiniWingsType > 0 )
		//{
		//	switch( MiniWingsType )
		//	{
		//	case 1:
		//		gPreview->WingsSlot = ITEM2(12, 130);
		//		break;
		//		// --
		//	case 2:
		//		gPreview->WingsSlot = ITEM2(12, 131);
		//		break;
		//		// --
		//	case 3:
		//		gPreview->WingsSlot = ITEM2(12, 132);
		//		break;
		//		// --
		//	//case 4:
		//	//	gPreview->WingsSlot = ITEM2(12, 133);
		//	//	break;
		//	//	// --
		//	//case 5:
		//	//	gPreview->WingsSlot = ITEM2(12, 134);
		//	//	break;
		//	}
		//}
//#endif
		// ----
//#ifdef CLIENT_0	//-> Custom
		BYTE CustomWings = CharSet[16] >> 2;
		// ----
		if( CustomWings > 0 )
		{
			//TDEBUG("Wings Switch: [%d]", CustomWings);
			// ----
			switch( CustomWings )
			{
			case 1:
				gPreview->WingsSlot = ITEM2(12, 180);
				break;
				// --
			case 2:
				gPreview->WingsSlot = ITEM2(12, 181);
				break;
				// --
			case 3:
				gPreview->WingsSlot = ITEM2(12, 182);
				break;
				// --
			case 4:
				gPreview->WingsSlot = ITEM2(12, 183);
				break;
				// --
			case 5:
				gPreview->WingsSlot = ITEM2(12, 184);
				break;
				// --
			case 6:
				gPreview->WingsSlot = ITEM2(12, 185);
				break;
				//Custom Wing2.5
			case 7:
				gPreview->WingsSlot = ITEM2(12, 186);
				break;
			case 8:
				gPreview->WingsSlot = ITEM2(12, 187);
				break;
			case 9:
				gPreview->WingsSlot = ITEM2(12, 188);
				break;
#ifdef _WINGS_5LVL_
            case 10:
                gPreview->WingsSlot = ITEM2(12, 189);
                break;
            case 11:
                gPreview->WingsSlot = ITEM2(12, 190);
                break;
            case 12:
                gPreview->WingsSlot = ITEM2(12, 191);
                break;
            case 13:
                gPreview->WingsSlot = ITEM2(12, 192);
                break;
            case 14:
                gPreview->WingsSlot = ITEM2(12, 193);
                break;
            case 15:
                gPreview->WingsSlot = ITEM2(12, 194);
                break;
#endif
			}
		}
//#endif
		 //----
		if( Mode )
		{
			*(BYTE *)(Mode + 4) = NULL;
		}
		else
		{
			ReturnPetSlot(ObjPreview + 700);
			gSetObjPetReset(gObjPetGetThis(), ObjPreview, pPetSlot(ObjPreview), 1);
		}
		// ----
		BYTE NormalPetType = CharSet[4] & 3;
		// ----
		if( NormalPetType == 3 )
		{
			if( (CharSet[9] & 1) == 1 )
			{
				gPreview->PetSlot = ITEM(13, 3);
				// ----
				if( Mode )
				{
					gSetObjMaunt2(eMauntType::Dinorant, ObjPreview + 952, ObjPreview + 700, Mode, 0);
				}
				else
				{
					gSetObjMaunt(eMauntType::Dinorant, ObjPreview + 952, ObjPreview + 700, 0, 0);
				}
			}
			else
			{
				gPreview->PetSlot		= CS_EMPTY_SLOT;
				gPreview->FenrirCharSet	= NULL;
				gPreview->ExpectPet		= 1;
			}
		}
		else
		{
			BYTE PetCharSet = CharSet[15] & 0xE0;
			// ----
			if( PetCharSet != 32 && PetCharSet != 64 
				&& PetCharSet != 128 && PetCharSet != 224 
				&& PetCharSet != 160 && PetCharSet != 96 )
			{
				gPreview->PetSlot	= ITEM2(13, 0) + NormalPetType;
				int MauntCode		= NULL;
				bool Check			= true;
				// ----
				if( NormalPetType )
				{
					if( NormalPetType == 2 )
					{
						MauntCode = eMauntType::Uniria;
					}
					else
					{
						if( NormalPetType == 3 )
						{
							MauntCode = eMauntType::Dinorant;
						}
						else
						{
							Check = false;
						}
					}
				}
				else
				{
					MauntCode = ITEM2(13, 0);
				}
				// ----
				if( Check == true )
				{
					if( Mode )
					{
						gSetObjMaunt2(MauntCode, ObjPreview + 952, ObjPreview + 700, Mode, 0);
					}
					else
					{
						gSetObjMaunt(MauntCode, ObjPreview + 952, ObjPreview + 700, 0, 0);
					}
				}
			}
			else
			{
				short ShopPetType = NULL;
				// ----
				switch( PetCharSet )
				{
				case 0x20: // Demon
					ShopPetType = 64;
					break;
					// --
				case 0x40: // Spirit Of Guardian
					ShopPetType = 65; 
					break;
					// --
				case 0x80: // Rudolf
					ShopPetType = 67;
					break;
					// --
				case 0xE0: // Panda
					ShopPetType = 80;
					break;
					// --
				case 0xA0: // Unicorn
					ShopPetType = 106;	//-> Not in use on GMO
					break;
					// --
				case 0x60: // Skeleton
					ShopPetType = 123;
					break;
				}
				// ----
				gPreview->PetSlot = ITEM2(13, 0) + ShopPetType;
				// ----
				if( *(DWORD*)oObjState == ObjState::SwitchCharacter || ObjPreview == LODWORD(dword_7B65114) )
				{
					gSetObjPetOnSwitch(gObjPetGetThis(), ITEM(13, 0) + ShopPetType, pPetSlot(ObjPreview), ObjPreview + 952, ObjPreview, 0, 0);
				}
			}
		}
		
		if( (CharSet[11] & 1) == 1 )
		{
			gPreview->PetSlot = ITEM2(13, 4);
			// ----
			
			if( Mode )
			{
				gSetObjMaunt2(eMauntType::DarkHorse, ObjPreview + 952, ObjPreview + 700, Mode, 0);
			}
			else
			{
				gSetObjMaunt(eMauntType::DarkHorse, ObjPreview + 952, ObjPreview + 700, 0, 0);
			}
		}
		if( (CharSet[11] & 4) == 4 )
		{
			gPreview->PetSlot		= ITEM2(13, 37);
			gPreview->FenrirCharSet	= CharSet[15] & 3;
			// ----
			if( (CharSet[16] & 1) == 1 )
			{
				gPreview->FenrirCharSet = 4;
			}
			// ----
			switch(gPreview->FenrirCharSet)
			{
			case 1: // Black Fenrir
				{
					if( Mode )
					{
						gSetObjMaunt2(eMauntType::BlackFenrir, ObjPreview + 952, ObjPreview + 700, Mode, 0);
					}
					else
					{
						gSetObjMaunt(eMauntType::BlackFenrir, ObjPreview + 952, ObjPreview + 700, 0, 0);
					}
				}
				break;
				// --
			case 2: // Blue Fenrir
				{
					if( Mode )
					{
						gSetObjMaunt2(eMauntType::BlueFenrir, ObjPreview + 952, ObjPreview + 700, Mode, 0);
					}
					else
					{
						gSetObjMaunt(eMauntType::BlueFenrir, ObjPreview + 952, ObjPreview + 700, 0, 0);
					}
				}
				break;
				// --
			case 4: // Golden Fenrir
				{
					if( Mode )
					{
						gSetObjMaunt2(eMauntType::GoldenFenrir, ObjPreview + 952, ObjPreview + 700, Mode, 0);
					}
					else
					{
						gSetObjMaunt(eMauntType::GoldenFenrir, ObjPreview + 952, ObjPreview + 700, 0, 0);
					}
				}
				break;
				// --
			default: // Red Fenrir
				{
					if( Mode )
					{
						gSetObjMaunt2(eMauntType::RedFenrir, ObjPreview + 952, ObjPreview + 700, Mode, 0);
					}
					else
					{
						gSetObjMaunt(eMauntType::RedFenrir, ObjPreview + 952, ObjPreview + 700, 0, 0);
					}
				}
				break;
			}
		}
	//	// ----
		gCheckPetStatus(ObjPreview);
	//	// ----
		if( ((CharSet[11] >> 1) & 1) == 1 )
		{
			if( gPreview->PetStatus <= NULL || gPreview->PetStatus > 3 )
			{
				gPreview->PetStatus = eEffectState::AtFenrir;
			}
		}
		else
		{
			if( gPreview->PetStatus <= NULL || gPreview->PetStatus > 3 )
			{
				gPreview->PetStatus = NULL;
			}
		}
	//	// ----
		int TempBuff				= CharSet[7] + (CharSet[6] << 8) + (CharSet[5] << 16);
		gPreview->WeaponFirstLevel	= gLevelSmallConvert(CharSet[7] & 7);
		gPreview->WeaponSecondLevel	= gLevelSmallConvert((TempBuff >> 3) & 7);
		gPreview->Unknown458		= NULL;
		gPreview->Unknown490		= NULL;
		Result						= ObjPreview;
		// ----
		if( !pVisible(ObjPreview) )
		{
			short HelmType = CS_GET_HELM(CharSet[8], CharSet[2], CharSet[12]);
			// ----
			if( HelmType == CS_EMPTY_ITEM )
			{
				gPreview->HelmSlot = (BYTE)gItemCharSetConvert(gPreview->Class) + CS_HELM;
			}
			else
			{
				gPreview->HelmSlot = ITEM2(7, 0) + HelmType;
			}
			// ----
			short ArmorType = CS_GET_ARMOR(CharSet[8], CharSet[2], CharSet[13]);
	//		 ----
			if( ArmorType == CS_EMPTY_ITEM )
			{
				gPreview->ArmorSlot = (BYTE)gItemCharSetConvert(gPreview->Class) + CS_ARMOR;
			}
			else
			{
				gPreview->ArmorSlot = ITEM2(8, 0) + ArmorType;
			}
			// ----
			short PantsType = CS_GET_PANTS(CharSet[8], CharSet[3], CharSet[13]);
			// ----
			if( PantsType == CS_EMPTY_ITEM )
			{
				gPreview->PantsSlot = (BYTE)gItemCharSetConvert(gPreview->Class) + CS_PANTS;
			}
			else
			{
				gPreview->PantsSlot = ITEM2(9, 0) + PantsType;
			}
			// ----
			short GlovesType = CS_GET_GLOVES(CharSet[8], CharSet[3], CharSet[14]);
			// ----
			if( GlovesType == CS_EMPTY_ITEM )
			{
				gPreview->GlovesSlot = (BYTE)gItemCharSetConvert(gPreview->Class) + CS_GLOVES;
			}
			else
			{
				gPreview->GlovesSlot = ITEM2(10, 0) + GlovesType;
			}
			// ----
			short BootsType = CS_GET_BOOTS(CharSet[8], CharSet[4], CharSet[14]);
			// ----
			if( BootsType == CS_EMPTY_ITEM )
			{
				gPreview->BootsSlot = (BYTE)gItemCharSetConvert(gPreview->Class) + CS_BOOTS;
			}
			else
			{
				gPreview->BootsSlot = ITEM2(11, 0) + BootsType;
			}
			// ----
			gPreview->HelmLevel				= gLevelSmallConvert((TempBuff >> 6) & 7);
			gPreview->HelmExcellent			= (CharSet[9] & 0x80) >> 7;
			gPreview->HelmAncient			= (CharSet[9] & 0x80) >> 7;
			// ----
			gPreview->ArmorLevel			= gLevelSmallConvert((TempBuff >> 9) & 7);
			gPreview->ArmorExcellent		= (CharSet[9] & 0x40) >> 6;
			gPreview->ArmorAncient			= (CharSet[9] & 0x40) >> 6;
			// ----
			gPreview->PantsLevel			= gLevelSmallConvert((TempBuff >> 12) & 7);
			gPreview->PantsExcellent		= (CharSet[9] & 0x20) >> 5;
			gPreview->PantsAncient			= (CharSet[9] & 0x20) >> 5;
			// ----
			gPreview->GlovesLevel			= gLevelSmallConvert((TempBuff >> 15) & 7);
			gPreview->GlovesExcellent		= (CharSet[9] & 0x10) >> 4;
			gPreview->GlovesAncient			= (CharSet[9] & 0x10) >> 4;
			// ----
			gPreview->BootsLevel			= gLevelSmallConvert((TempBuff >> 18) & 7);
			gPreview->BootsExcellent		= (CharSet[9] & 8) >> 3;
			gPreview->BootsAncient			= (CharSet[9] & 8) >> 3;
			// ----
			gPreview->WeaponFirstExcellent	= (CharSet[9] & 4) >> 2;
			gPreview->WeaponFirstAncient	= (CharSet[10] & 4) >> 2;
			// ----
			gPreview->WeaponSecondExcellent = (CharSet[9] & 2) >> 1;
			gPreview->WeaponSecondAncient	= (CharSet[10] & 2) >> 1;
			// ----
			gPreview->AncientEffect			= CharSet[10] & 1;
			// ----
			sub_49A50A(ObjPreview);
			// ----
			//Result = sub_514A21(ObjPreview);
			//sub_514A21(ObjPreview);
		}
	}
	// ----
	return Result;
}


void cMakePreviewCharSetLoad()
{
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x0046D96B, ASM::CALL);		//Main 1.03Y+ JPN: 0047797F ; Main 1.03k JPN: 0046D96B
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x00611613, ASM::CALL);		//Main 1.03Y+ JPN: 006317A3 ; Main 1.03k JPN: 00611613
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x006177F5, ASM::CALL);		//Main 1.03Y+ JPN: 00637C15 ; Main 1.03k JPN: 006177F5
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x006182D0, ASM::CALL);		//Main 1.03Y+ JPN: 00638702 ; Main 1.03k JPN: 006182D0
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x006188B6, ASM::CALL);		//Main 1.03Y+ JPN: 00638CF3 ; Main 1.03k JPN: 006188B6
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x0063D4FC, ASM::CALL);		//Main 1.03Y+ JPN: 0065EDCC ; Main 1.03k JPN: 0063D4FC
	SetHook((LPVOID)gObjMakePreviewCharSet, (LPVOID)0x00640572, ASM::CALL);		//Main 1.03Y+ JPN: 00663A57 ; Main 1.03k JPN: 00640572
	// ----
	SetHook((LPVOID)gMakePreviewSoldierElf, (LPVOID)0x005025B8, ASM::CALL);		//Main 1.03Y+ JPN: 00519CCF ; Main 1.03k JPN: 005025B8
}
//---------------------------------------------------------------------------