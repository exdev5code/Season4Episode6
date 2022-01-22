//GameServer 1.00.90 JPN - Completed
#include "StdAfx.h"
#include <iostream>
#include <iomanip>
#include "zzzitem.h"
#include "SetItemOption.h"
#include "..\GameServer\logproc.h"
#include "WzMemScript.h"
#include "..\include\Readscript.h"
#include "..\GameServer\JewelOfHarmonySystem.h"
#include "..\GameServer\ItemSystemFor380.h"
#include "..\GameServer\user.h"
#include "..\GameServer\StdAfx.h"
#include "..\GameServer\Configs.h"
//#include "Configs.h"

ITEM_ATTRIBUTE ItemAttribute[MAX_ITEMS];
CPetItemExp gPetItemExp;
int g_MaxItemIndexOfEachItemType[MAX_TYPE_ITEMS];

CItem::CItem()
{
	this->Clear();
}

void CItem::Clear()
{
	this->m_Type =-1;
	this->m_Level =0;
	this->m_Part=0;
	this->m_Class=0;
	this->m_TwoHand=0;
	this->m_AttackSpeed=0;
	this->m_DamageMin=0;
	this->m_DamageMax=0;
	this->m_SuccessfulBlocking=0;
	this->m_Defense=0;
	this->m_MagicDefense =0;
	this->m_Durability=0;
	this->m_SpecialNum=0;
	this->m_Value=0;
	this->m_Option1 =0;
	this->m_Option2 =0;
	this->m_Option3 =0;
	this->m_NewOption =0;
	this->m_Number =0;
	this->m_DurabilitySmall =0;
	this->m_iPShopValue=-1;
	this->m_bItemExist=true;
	this->m_CurrentDurabilityState=-1;
	this->m_SetOption=0;
	this->m_QuestItem=false;

	memset(this->m_Special, 0, sizeof(this->m_Special));
	memset(this->m_SpecialValue, 0, sizeof(this->m_SpecialValue));
	memset(this->m_Resistance, 0, sizeof(this->m_Resistance));

	this->m_IsLoadPetItemInfo=0;
	this->m_PetItem_Level =1;
	this->m_PetItem_Exp =0;
	this->m_Leadership=0;
	this->m_JewelOfHarmonyOption = 0;
	this->m_ItemOptionEx = 0;

	//Season 4 add-on
	this->m_SocketOptionIndex = 0xFF;

	memset(this->m_SocketOption, 0xFF, sizeof(this->m_SocketOption));

	this->m_SocketBonus = 0;
}

BOOL CItem::IsItem()
{
	if (this->m_Type < 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int CItem::IsSetItem()
{
	if (this->m_Type < 0)
	{
		return 0;
	}
	else
	{
		return this->m_SetOption & 3;
	}
}	

void CItem::Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3,  BYTE Attribute2, BYTE SetOption, BYTE ItemEffectEx, BYTE SocketOption[5], BYTE SocketIndex, BYTE DbVersion)
{
	int _type; //2
	int ItemLevel; //3
	LPITEM_ATTRIBUTE p; //4
	int SOption; //5
	int SOptionStatValue; //6
	
	_type = type;

	if ( (DbVersion ) == 0)
	{
		_type=(type/MAX_TYPE_ITEMS*MAX_SUBTYPE_ITEMS)+(type % MAX_TYPE_ITEMS);

	}
	else if ( DbVersion <= 2 )
	{
		_type = (type/32*MAX_SUBTYPE_ITEMS) + (type % 32 );
	}
	
	if ( _type >MAX_ITEMS-1)
	{
		LogAddC(2, "error-L1 : ItemIndex error %d", _type);
	}
	
	p=&ItemAttribute[_type];
	this->m_serial=ItemAttribute[_type].Serial ;
	this->m_Type=type;
	
	if ( (DbVersion ) <= 2)
	{
		this->m_Type=_type;
	}

	this->m_NewOption =Attribute2;
	
	if (p->OptionFlag  == 0)
	{
		this->m_NewOption=0;
	}

	if ( ((_type >= ITEMGET(12,3) ) && (_type <= ITEMGET(12,6) ) ) || (_type == ITEMGET(13,30) || _type == ITEMGET(12,41) || _type == ITEMGET(12,42) || _type == ITEMGET(12,43) || (_type >= ITEMGET(12,36) && _type <= ITEMGET(12,40)) || (_type >= ITEMGET(12,180) && _type <= ITEMGET(12,END_WING_NUM)) ))	//Custom Wings4
	{
		Attribute2=0;
	}

	if ( _type == ITEMGET(13,37) )
	{
		Attribute2 = 0;
	}

	SetOption = SetOption & 15;
		
	SOption=SetOption & 3;
	SOptionStatValue=0;



	if (SOption != 1 && SOption != 2)
	{
		SOption=0;
	}

	if ( (( (SetOption>>2) & 3) != 1) && ( ((SetOption>>2) & 3) != 2) )
	{
		SOption=0;
	}

	#if(ENABLE_ITEMS_ALLOPT)

	if ( gSetItemOption.IsSetItem(_type) != 0 && SetOption != 255 && SOption != 0)
	{
		this->m_SetOption = SetOption;
	}
	else
	{
		this->m_SetOption = 0;
	}

	this->m_ItemOptionEx = ItemEffectEx;

	if(g_SocketOption.IsActive(this) == 1)
	{
		if(SocketOption != 0)
		{
			this->m_SocketOptionIndex = SocketIndex;

			for(int i = 0; i < 5; i++)
			{
				this->m_SocketOption[i] = SocketOption[i];
			}
		}

		if(!g_SocketOption.IsSocketOption(this) )
		{
			this->m_SocketOptionIndex = 0;
		}
	}
	else
	{
		this->m_SocketOptionIndex = 0;

		for(int i = 0; i < 5; i++)
		{
			this->m_SocketOption[i] = 0xFF;
		}
	}

	#else

	if ( gSetItemOption.IsSetItem(_type) != 0 && SetOption != 255 && SOption != 0)
	{
		this->m_SetOption = SetOption;
		if ( this->m_SetOption != 0 )
		{
			//int ExExcellentAncient = GetPrivateProfileInt("Items","ExcellentAncient",1,"..\\ExTeam\\CommonServer.ini");
			if(!ExConfig.CommonServer.ExExcellentAncient)
				this->m_NewOption = 0;
			Attribute2 = 0;
			SOptionStatValue = (SetOption>>2)&3;
		}
	}
	else
	{
		this->m_SetOption = 0;
	}
	
	this->m_ItemOptionEx = ItemEffectEx;



	//Socket Season 4 OPTION #START!
	if(g_SocketOption.IsActive(this) == 1)
	{
		if(SocketOption != 0)
		{
			this->m_SocketOptionIndex = SocketIndex;

			for(int i = 0; i < 5; i++) //7
			{
				this->m_SocketOption[i] = SocketOption[i];
			}
		}

		if(g_SocketOption.IsSocketOption(this) == 1)
		{	//Zero SET
			this->m_ItemOptionEx = 0;
			//int ExAncientSocket = GetPrivateProfileInt("Items","AncientSocket",1,"..\\ExTeam\\CommonServer.ini");
			if(!ExConfig.CommonServer.ExAncientSocket)
				this->m_SetOption = 0;
			Attribute2 = 0;
			//int ExExcellentSocket = GetPrivateProfileInt("Items","ExcellentSocket",1,"..\\ExTeam\\CommonServer.ini");
			if(!ExConfig.CommonServer.ExExcellentSocket)
				this->m_NewOption = 0;
			this->m_JewelOfHarmonyOption = 0;
		}
		else
		{
			//Zero SET
			this->m_SocketOptionIndex = 0;
		}
	}
	else
	{
		//Zero SET
		this->m_SocketOptionIndex = 0;

		for(int i = 0; i < 5; i++) //8
		{
			this->m_SocketOption[i] = 0xFF;
		}
	}

	#endif

	memset( this->m_SkillResistance , 0, sizeof(this->m_SkillResistance) );
	
	if ( _type == ITEMGET(0,19) || _type == ITEMGET(4,18) || _type == ITEMGET(5,10) || _type == ITEMGET(2,13))
	{
		Attribute2=0;
	}

	int iChaosItem = 0;

	if ( this->m_Type == ITEMGET(2,6) )
	{
		iChaosItem = 15;
	}
	else if ( this->m_Type == ITEMGET(5,7) )
	{
		iChaosItem = 25;
	}
	else if ( this->m_Type == ITEMGET(4,6) )
	{
		iChaosItem = 30;
	}

	if ( ItemGetDurability(this->m_Type, 0, 0, 0) != 0 )
	{
		this->m_BaseDurability = (float)ItemGetDurability(this->m_Type, this->m_Level, Attribute2 & 0x7F, this->m_SetOption );
	}
	else
	{
		this->m_BaseDurability = 0;
	}

	this->m_DurabilityState[0] = this->m_BaseDurability * 0.5f;
	this->m_DurabilityState[1] = this->m_BaseDurability * 0.3f;
	this->m_DurabilityState[2] = this->m_BaseDurability * 0.2f;
	this->m_Value = p->Value;
	this->m_AttackSpeed = p->AttackSpeed;
	this->m_TwoHand = p->TwoHand;
	this->m_DamageMin = p->DamageMin;
	this->m_DamageMax = p->DamageMax;
	this->m_SuccessfulBlocking = p->SuccessfulBlocking;
	this->m_Defense = p->Defense;
	this->m_MagicDefense = p->MagicDefense;
	this->m_WalkSpeed = p->WalkSpeed;

	if((_type >> 9) == 5 && p->ItemSlot == 1) //Season3 add-on
	{
		this->m_Magic = 0;
		this->m_BookSpell = p->MagicPW;
	}
	else
	{
		this->m_Magic = p->MagicPW;
		this->m_BookSpell = 0;
	}
	
	this->m_serial = p->Serial;
	this->m_QuestItem = (bool)p->QuestItem;
	this->m_RequireLeaderShip = 0;

	/////////
	if ( this->m_BaseDurability > 10.0f && 
		_type != ITEMGET(13,20) &&
		_type != ITEMGET(13,38) &&
		this->m_Durability > this->m_BaseDurability) //season 4.5 add-on
	{
		this->m_Durability = this->m_BaseDurability;
	}
	////////

	if ( this->m_Durability == 0 )
	{
		this->m_CurrentDurabilityState = 1;
	}
	else if ( this->m_Durability < this->m_DurabilityState[2] )
	{
		this->m_CurrentDurabilityState = (float)0.5;
	}
	else if ( this->m_Durability < this->m_DurabilityState[1] )
	{
		this->m_CurrentDurabilityState = (float)0.3;
	}
	else if ( this->m_Durability < this->m_DurabilityState[0] )
	{
		this->m_CurrentDurabilityState = (float)0.2;
	}
	else
	{
		this->m_CurrentDurabilityState = 0.0;
	}

	memcpy(this->m_RequireClass, p->RequireClass , sizeof(this->m_RequireClass));

	for (int i = 0; i<MAX_ITEM_SPECIAL_ATTRIBUTE ; i++ ) //9
	{
		this->m_Resistance[i] = p->Resistance[i] * this->m_Level;
	}

	ItemLevel = p->Level;

	if ( ( Attribute2 & 0x3F) > 0 )
	{
		ItemLevel = p->Level + 25;
	}
	else
	{
		if (this->m_SetOption != 0 )
		{
			ItemLevel = p->Level + 25;
		}
	}

	if ( p->RequireStrength != 0 )
	{
		this->m_RequireStrength = ((p->RequireStrength * (ItemLevel + this->m_Level * 3 ) ) * 3) / 100 + 20;
	}
	else
	{
		this->m_RequireStrength = 0;
	}


	if ( p->RequireDexterity != 0 )
	{
		this->m_RequireDexterity = ((p->RequireDexterity * (ItemLevel + this->m_Level * 3 ) ) * 3) / 100 + 20;
	}
	else
	{
		this->m_RequireDexterity  = 0;
	}

	if ( p->RequireEnergy != 0 )
	{
		this->m_RequireEnergy = ((p->RequireEnergy * (ItemLevel + this->m_Level * 3 ) ) * 4) / 100 + 20;
	}
	else
	{
		this->m_RequireEnergy = 0;
	}

	if(p->RequireEnergy != 0)
	{
		if((_type >> 9) == 5 && p->ItemSlot == 1) //Season3 add-on
		{
			this->m_RequireEnergy = ((p->RequireEnergy * (ItemLevel + this->m_Level) ) * 3) / 100 + 20;
		}
	}
	else
	{
		this->m_RequireEnergy = 0;
	}

	if ( _type >= ITEMGET(0,0) && _type < ITEMGET(12,0) )
	{
		if ( p->RequireVitality != 0 )
		{
			this->m_RequireVitality = ((p->RequireVitality * (ItemLevel + this->m_Level * 3 ) ) * 3) / 100 + 20;
		}
		else
		{
			this->m_RequireVitality = 0;
		}

		if ( p->RequireLeadership != 0 )
		{
			this->m_RequireLeaderShip = ((p->RequireVitality * (ItemLevel + this->m_Level * 3 ) ) * 3) / 100 + 20;
		}
		else
		{
			this->m_RequireLeaderShip = 0;
		}
	}

	if ( _type == ITEMGET(13,5) )
	{
		this->m_RequireLeaderShip = this->m_PetItem_Level * 15 + 185;
		p->RequireLeadership = this->m_PetItem_Level * 15 + 185; //season4 add-on
	}

	if ( g_kJewelOfHarmonySystem.IsActive(this) == TRUE )
	{
		BYTE btOption = g_kJewelOfHarmonySystem.GetItemStrengthenOption(this);
		int iItemType = g_kJewelOfHarmonySystem._GetItemType(this);

		if(iItemType == 1)
		{
			if ( btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR )
			{
				this->m_HJOpStrength = g_kJewelOfHarmonySystem.GetItemEffectValue(this,	AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR);
			}
			else if ( btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX )
			{
				this->m_HJOpDexterity = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX);
			}
		}
		else if(iItemType == 2)
		{
			if ( btOption == AT_JEWELOFHARMONY_WEAPON_IMPROVE_MAXATTACKDAMAGE )
			{
				this->m_HJOpStrength = g_kJewelOfHarmonySystem.GetItemEffectValue(this,	AT_JEWELOFHARMONY_WEAPON_IMPROVE_MAXATTACKDAMAGE);
			}
			else if ( btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR )
			{
				this->m_HJOpDexterity = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR);
			}
		}		
	}
	else //WZ Fix for Season3.0
	{
		this->m_HJOpStrength = 0;
		this->m_HJOpDexterity = 0;
	}

	g_SocketOption.ApplySocketEffectforWeapons(this); //season 4 add-on

	if ( p->RequireLevel != 0 )
	{
		if ( _type == ITEMGET(13,4) )	// DarkHorse
		{
			this->m_RequireLevel = this->m_PetItem_Level * 2 + 218;
		}
		else if ( _type >= ITEMGET(12,36) && _type <= ITEMGET(12,40) )
		{
			this->m_RequireLevel = p->RequireLevel;
		}
		else if ( _type >= ITEMGET(12,180) && _type <= ITEMGET(12,END_WING_NUM) )	//Custom Wings4
		{
			this->m_RequireLevel = p->RequireLevel;
		}
		else if ( _type >= ITEMGET(12,3) && _type <= ITEMGET(12,6) )
		{
			this->m_RequireLevel = p->RequireLevel + (this->m_Level * 5);
		}
		else if ( _type == ITEMGET(12,42) ) //Season3
		{
			this->m_RequireLevel = p->RequireLevel + (this->m_Level * 5);
		}
		else if ( _type == ITEMGET(12,43) ) //Season3
		{
			this->m_RequireLevel = p->RequireLevel;
		}
		else if ( _type >= ITEMGET(12,7) && _type <= ITEMGET(12,24) )
		{
			this->m_RequireLevel = p->RequireLevel;
		}
		else if ( _type >= ITEMGET(0,0) && _type < ITEMGET(12,0) )
		{
			if ( p->RequireLevel )
				this->m_RequireLevel = p->RequireLevel;
		}
		else
		{
			this->m_RequireLevel = p->RequireLevel + this->m_Level * 4;
		}
	}
	else
	{
		this->m_RequireLevel = 0;
	}

	if ( this->m_Type == ITEMGET(13,10) )
	{
		if ( ItemLevel <= 2 )
		{
			this->m_RequireLevel = 20;
		}
		else
		{
			this->m_RequireLevel = 50;
		}
	}

	if ( (Attribute2 & 0x3F) > 0 )
	{
		if ( this->m_RequireLevel > 0 )
		{
			if ( _type < ITEMGET(0,0) || _type >= ITEMGET(12,0) )
				this->m_RequireLevel += 20;
		}
	}

	if ( this->m_SetOption != 0 )
	{
		ItemLevel = p->Level + 30;
	}
	
	this->m_Leadership = 0;

	if ( this->m_DamageMax > 0 )
	{
		if ( this->m_SetOption != 0 && ItemLevel != 0 )
		{
			this->m_DamageMax += (this->m_DamageMin * 25) / p->Level + 5;
			this->m_DamageMax += ItemLevel / 40 + 5;
		}
		else
		{
			if ( (Attribute2 & 0x3F)  > 0 )
			{
				if ( iChaosItem != 0 )
				{
					this->m_DamageMax += iChaosItem;
				}
				else if ( p->Level != 0 )
				{
					this->m_DamageMax += (this->m_DamageMin * 25) / p->Level + 5;
				}
			}
		}

		this->m_DamageMax += this->m_Level * 3;

		if ( this->m_Level >= 10 )
		{
			this->m_DamageMax += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	if ( this->m_DamageMin > 0 )	
	{
		if ( this->m_SetOption != 0 && ItemLevel != 0 )
		{
			this->m_DamageMin += (this->m_DamageMin * 25) / p->Level + 5;
			this->m_DamageMin += ItemLevel / 40 + 5;
		}
		else
		{
			if ( (Attribute2 & 0x3F)  > 0 )
			{
				if ( iChaosItem != 0 )
				{
					this->m_DamageMin += iChaosItem;
				}
				else if ( p->Level != 0 )
				{
					this->m_DamageMin += (this->m_DamageMin * 25) / p->Level + 5;
				}
			}
		}

		this->m_DamageMin += this->m_Level * 3;

		if ( this->m_Level >= 10 )
		{
			this->m_DamageMin += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	if ( this->m_Magic > 0 )	
	{
		if ( this->m_SetOption != 0 && ItemLevel != 0 )
		{
			this->m_Magic += (this->m_Magic * 25) / p->Level + 5;
			this->m_Magic += ItemLevel / 60 + 2;
		}
		else
		{
			if ( (Attribute2 & 0x3F)  > 0 )
			{
				if ( iChaosItem != 0 )
				{
					this->m_Magic += iChaosItem;
				}
				else if ( p->Level != 0 )
				{
					this->m_Magic += (this->m_Magic * 25) / p->Level + 5;
				}
			}
		}

		this->m_Magic += this->m_Level * 3;

		if ( this->m_Level >= 10 )
		{
			this->m_Magic += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	if( this->m_BookSpell > 0) //Season3 Summoner
	{
		if ( this->m_SetOption != 0 && ItemLevel != 0 )
		{
			this->m_BookSpell += (this->m_BookSpell * 25) / p->Level + 5;
			this->m_BookSpell += ItemLevel / 60 + 2;
		}
		else
		{
			if ( (Attribute2 & 0x3F)  > 0 )
			{
				if ( iChaosItem != 0 ) //season4 changed
				{
					this->m_BookSpell += iChaosItem; //season4 changed
				}
				else if ( p->Level != 0 )
				{
					this->m_BookSpell += (this->m_BookSpell * 25) / p->Level + 5;
				}
			}
		}

		this->m_BookSpell += this->m_Level * 3;

		if ( this->m_Level >= 10 )
		{
			this->m_BookSpell += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	if ( p->SuccessfulBlocking > 0 )	
	{
		if ( this->m_SetOption != 0 && ItemLevel != 0 )
		{
			this->m_SuccessfulBlocking += (this->m_SuccessfulBlocking * 25) / p->Level + 5;
			this->m_SuccessfulBlocking += ItemLevel / 40 + 5;
		}
		else
		{
			if ( (Attribute2 & 0x3F)  > 0 )
			{
				if ( p->Level != 0 )
				{
					this->m_SuccessfulBlocking += (this->m_SuccessfulBlocking * 25) / p->Level + 5;
				}
			}
		}

		this->m_SuccessfulBlocking += this->m_Level * 3;

		if ( this->m_Level >= 10 )
		{
			this->m_SuccessfulBlocking += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	if ( p->Defense > 0 )	
	{
		if ( this->m_Type >= ITEMGET(6,0) && this->m_Type < ITEMGET(7,0) )
		{
			this->m_Defense += this->m_Level;

			if ( this->m_SetOption != 0 && ItemLevel != 0 )
			{
				this->m_Defense += (this->m_Defense * 20) / ItemLevel + 2;
			}
		}
		else 
		{
			if ( this->m_SetOption != 0 && ItemLevel != 0 )
			{
				this->m_Defense += (this->m_Defense * 12) / p->Level + (p->Level / 5 ) + 4;
				this->m_Defense += (this->m_Defense * 3) / ItemLevel  + ( ItemLevel / 30 ) + 2;
			}
			else if ( (Attribute2 & 0x3F) > 0 )
			{
				if ( p->Level != 0 )
				{
					this->m_Defense += (this->m_Defense * 12) / p->Level + (p->Level / 5 ) + 4;
				}
			}
			
			if ( ( _type >= ITEMGET(12,36) && _type <= ITEMGET(12,40)) )
			{
				this->m_Defense += this->m_Level * 4;

				if ( this->m_Level >= 10 )
				{
					this->m_Defense += (this->m_Level - 9);
				}
			}
			else if ( ( _type >= ITEMGET(12,180) && _type <= ITEMGET(12,END_WING_NUM)) )	//Custom Wings4
			{
				this->m_Defense += this->m_Level * 4;

				if ( this->m_Level >= 10 )
				{
					this->m_Defense += (this->m_Level - 9);
				}
			}
			else if ( ( _type >= ITEMGET(12,3) && _type <= ITEMGET(12,6)) || _type == ITEMGET(13,30) || _type == ITEMGET(13,4) )
			{
				this->m_Defense += this->m_Level * 2;
			}
			else
			{
				this->m_Defense += this->m_Level * 3;
			}

			if ( this->m_Level >= 10 )
			{
				this->m_Defense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
			}
		}
	}

	if ( _type == ITEMGET(13,30) )
	{
		this->m_Defense = this->m_Level*2 + 15;

		if ( this->m_Level >= 10 )
		{
			this->m_Defense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	//Summoner Wings
	if ( _type == ITEMGET(12,41) )
	{
		this->m_Defense += this->m_Level*3;

		if ( this->m_Level >= 10 )
		{
			this->m_Defense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	else if ( _type == ITEMGET(12,42) )
	{
		this->m_Defense += this->m_Level*2;

		if ( this->m_Level >= 10 )
		{
			this->m_Defense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}
	else if ( _type == ITEMGET(12,43) )
	{
		this->m_Defense += this->m_Level*4;

		if ( this->m_Level >= 10 )
		{
			this->m_Defense += (this->m_Level - 9);
		}
	}
	//

	if ( p->MagicDefense > 0 )
	{
		this->m_MagicDefense += this->m_Level * 3;

		if ( this->m_Level >= 10 )
		{
			this->m_MagicDefense += (this->m_Level - 9) * (this->m_Level - 8) / 2;
		}
	}

	this->m_Level &= 15;

	memset(this->m_Special, 0, sizeof(this->m_Special));
	memset(this->m_SpecialValue, 0, sizeof(this->m_SpecialValue));
	this->m_SpecialNum = 0;
	this->m_Option1 = 0;
	this->m_Option2 = 0;
	this->m_Option3 = 0;
	this->m_SkillChange = FALSE;

	if ( Option1	!= 0 )
	{
		if ( p->SkillType != 0 )
		{
			if ( p->SkillType == 66 )
			{
				this->m_SkillChange = TRUE;
				this->m_Special[this->m_SpecialNum] = 0;
				this->m_Option1 = 1;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = p->SkillType;
				this->m_Option1 = 1;
			}
		}
	}

	if ( this->m_Type == ITEMGET(13,3) )	// Dinorant
	{
		this->m_Option1 = TRUE;
		this->m_Special[this->m_SpecialNum] = 49;
	}

	if ( this->m_Type == ITEMGET(13,4) )	//Dark Horse
	{
		this->m_Option1 = TRUE;
		this->m_Special[this->m_SpecialNum] = 62;
	}

	if ( this->m_Type == ITEMGET(13,37) )
	{
		this->m_Option1 = TRUE;
		this->m_Special[this->m_SpecialNum] = 76;
	}

	this->m_SpecialNum++;

	if ( Option2 != 0 )
	{
		if ( _type >= ITEMGET(0,0) && _type < ITEMGET(12,0) )
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}

		if ( _type >= ITEMGET(12,0) && _type <= ITEMGET(12,6) )	// Wings
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}

		if ( _type == ITEMGET(13,30) )	// Cape of Lord
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}

		if ( _type >= ITEMGET(12,36) && _type <= ITEMGET(12,40) )	//Season 2.5 Third Wings
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}

		if ( _type >= ITEMGET(12,180) && _type <= ITEMGET(12,END_WING_NUM) )	//Custom Wings4
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}

		if ( _type >= ITEMGET(12,41) && _type <= ITEMGET(12,43) )	//Season 3.5 Summoner Wings
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}
	}

	this->m_SpecialNum++;

	if ( Option3 != 0 )
	{
		if ( _type >= ITEMGET(0,0) && _type < ITEMGET(5,0) )
		{
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}

		if ( _type >= ITEMGET(5,0) && _type < ITEMGET(6,0) )
		{
			if(p->ItemSlot == 1)
			{
				this->m_Special[this->m_SpecialNum] = 113;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 81;
			}
			
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}
		
		if ( _type >= ITEMGET(6,0) && _type < ITEMGET(7,0) )
		{
			this->m_Special[this->m_SpecialNum] = 82;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}

		if ( _type >= ITEMGET(7,0) && _type < ITEMGET(12,0) )
		{
			this->m_Special[this->m_SpecialNum] = 83;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}

		if ( (_type >= ITEMGET(13,8) && _type < ITEMGET(13,14)) || (_type >= ITEMGET(13,20) && _type <= ITEMGET(13,28)) )
		{
			if ( _type == ITEMGET(13,24) ) // Ring of MAgic
			{
				this->m_Special[this->m_SpecialNum] = 172;
				this->m_Option3 = Option3;
			}
			else if ( _type == ITEMGET(13,28) ) // Pendant of abilit
			{
				this->m_Special[this->m_SpecialNum] = 173;
				this->m_Option3 = Option3;
			}
			else  
			{
				this->m_Special[this->m_SpecialNum] = 85;
				this->m_Option3 = Option3;
			}
		}
		
		if ( _type == ITEMGET(13,30) ) // Cape of lord 
		{
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}

		if ( _type == ITEMGET(12,0) )	// Wing elf
		{
			this->m_Special[this->m_SpecialNum] = 85;
			this->m_Option3 = Option3;
		}
		else if ( _type == ITEMGET(12,1) ) // winf Heaven
		{
			this->m_Special[this->m_SpecialNum] = 81;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}
		else if ( _type == ITEMGET(12,2) ) // wing devil
		{
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}
		else if ( _type == ITEMGET(12,3) ) // wing spitits
		{
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;

			if ( (this->m_NewOption&0x20) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 85;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 80;
			}

		}
		else if ( _type == ITEMGET(12,4) ) // wing soul
		{
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;

			if ( (this->m_NewOption&0x20) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 81;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 85;
			}

		}
		else if ( _type == ITEMGET(12,5) ) // wing dragon
		{
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;

			if ( (this->m_NewOption&0x20) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 80;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 85;
			}

		}			
		else if ( _type == ITEMGET(12,6) ) // wing darkness
		{
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;

			if ( (this->m_NewOption&0x20) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 80;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 81;
			}

		}
		else if ( _type == ITEMGET(13,3) ) // dinorant
		{
			this->m_Option3 = Option3;
	
			if ( (this->m_Option3&0x02) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x67;
				this->m_SpecialNum++;
			}
		
			if ( (this->m_Option3&0x04) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x61;
				this->m_SpecialNum++;
				this->m_AttackSpeed+=5;
			}
		
			if ( (this->m_Option3&0x01) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x68;
			}
		}

		if ( _type == ITEMGET(13,30) ) // Cape ofLord
		{
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
			this->m_Special[this->m_SpecialNum] = 0x50;
		}

		//Season 2.5 add-on (Third Wings)
		if ( _type == ITEMGET(12,36) ) // Wing of Storm
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}
		}

		if ( _type >= ITEMGET(12,180) && _type <= ITEMGET(12,END_WING_NUM) ) //Custom Wings4
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}
		}

		if ( _type == ITEMGET(12,37) ) // Wing of Eternal
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x51;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}
		}

		if ( _type == ITEMGET(12,38) ) // Wing of Illusion
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}
		}

		if ( _type == ITEMGET(12,39) ) // Wing of Ruin
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x51;
			}
		}

		if ( _type == ITEMGET(12,40) ) // Cape of Emperor
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}
		}
		else if ( _type == ITEMGET(12,41) ) // Wing of Curse
		{
			this->m_Special[this->m_SpecialNum] = 81;
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;
		}
		else if ( _type == ITEMGET(12,42) ) // Wing of Despair
		{
			this->m_Option3 = Option3;
			this->m_RequireStrength +=  Option3 * 4;

			if ( (this->m_NewOption&0x20) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 81;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 113;
			}
		}
		else if ( _type == ITEMGET(12,43) ) // Wing of Dimension
		{
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 0x55;

			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 81;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 113;
			}
		}
	}

	this->m_SpecialNum++;

	if ( (_type >=ITEMGET(6,0) && _type <ITEMGET(12,0) ) || ( _type >=ITEMGET(13,8) && _type <= ITEMGET(13,9)) || (_type>=ITEMGET(13,21) && _type <= ITEMGET(13,24) ) )
	{
		if ( ((this->m_NewOption>>5)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x56;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption>>4)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x57;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption>>3)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x58;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption>>2)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x59;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption>>1)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x5A;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x5B;
			this->m_SpecialNum++;
		}
	}

	if ( (_type >=ITEMGET(0,0) && _type <ITEMGET(6,0) ) || ( _type >=ITEMGET(13,12) && _type <= ITEMGET(13,13)) || (_type>=ITEMGET(13,25) && _type <= ITEMGET(13,28) ) )
	{
		if ( ((this->m_NewOption>>5)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x5C;
			this->m_SpecialNum++;
		}

		if ( (_type >=ITEMGET(5,0) && _type <ITEMGET(6,0) ) || (_type ==ITEMGET(13,12) ) || (_type == ITEMGET(13,25)) || (_type == ITEMGET(13,27) ) )
		{
			if ( ((this->m_NewOption>>4)&1) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x5F;
				this->m_SpecialNum++;
			}
			if ( ((this->m_NewOption>>3)&1) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x60;
				this->m_SpecialNum++;
			}
		}
		else
		{
			if ( ((this->m_NewOption>>4)&1) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x5D;
				this->m_SpecialNum++;
			}
			if ( ((this->m_NewOption>>3)&1) != 0 )
			{
				this->m_Special[this->m_SpecialNum] = 0x5E;
				this->m_SpecialNum++;
			}
		}

		if ( ((this->m_NewOption>>2)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x61;
			this->m_SpecialNum++;
			this->m_AttackSpeed += 7;
		}

		if ( ((this->m_NewOption>>1)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x62;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x63;
			this->m_SpecialNum++;
		}
	}

	if ( ((_type >= ITEMGET(12,3)) && (_type <= ITEMGET(12,6))) || (_type ==ITEMGET(12,42)) || (_type ==ITEMGET(13,30)) )
	{
		if ( ((this->m_NewOption)&1) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x64;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption)&2) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x65;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption)&4) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x66;
			this->m_SpecialNum++;
		}

		if ( ((this->m_NewOption)&8) != 0 )
		{
			this->m_Special[this->m_SpecialNum] = 0x69;
			this->m_SpecialNum++;
		}
	}

	if ( _type == ITEMGET(13,37) )
	{
		if ( (this->m_NewOption &1) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6A;
			this->m_SpecialNum++;
		}
		else if ( (this->m_NewOption &2) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6B;
			this->m_SpecialNum++;
		}
		else if ( (this->m_NewOption &4) ) //Season 2.5 Golden Fenrir
		{
			this->m_Special[this->m_SpecialNum] = 0x70;
			this->m_SpecialNum++;
		}
	}

	//Season 2.5 Third Wings
	if ( _type >= ITEMGET(12,36) && _type <= ITEMGET(12,40) || _type == ITEMGET(12,43))
	{
		if ( (this->m_NewOption &1) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6C;
			this->m_SpecialNum++;
		}
		if ( (this->m_NewOption &2) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6D;
			this->m_SpecialNum++;
		}
		if ( (this->m_NewOption &4) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6E;
			this->m_SpecialNum++;
		}
		if ( (this->m_NewOption &8) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6F;
			this->m_SpecialNum++;
		}
	}

	//Custom Wings4
	if ( _type >= ITEMGET(12,180) && _type <= ITEMGET(12,END_WING_NUM))
	{
		if ( (this->m_NewOption &1) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6C;
			this->m_SpecialNum++;
		}
		if ( (this->m_NewOption &2) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6D;
			this->m_SpecialNum++;
		}
		if ( (this->m_NewOption &4) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6E;
			this->m_SpecialNum++;
		}
		if ( (this->m_NewOption &8) )
		{
			this->m_Special[this->m_SpecialNum] = 0x6F;
			this->m_SpecialNum++;
		}
	}

	if ( SOptionStatValue != 0 )
	{
		if (p->SetAttr != 0 )
		{
			this->m_Special[this->m_SpecialNum] = p->SetAttr + 0xC3;
			this->m_SetAddStat = SOptionStatValue * 5;
			this->m_SpecialNum++;
		}
	}

	this->m_Part = p->ItemSlot;
	this->Value();

	if ( this->m_Type != ITEMGET(4,7) && this->m_Type != ITEMGET(4,15) ) // arrow and bolts
	{
		this->m_DamageMinOrigin = this->m_DamageMin;
		this->m_DefenseOrigin = this->m_Defense;
		this->m_DamageMin -= (int)(this->m_DamageMin * this->m_CurrentDurabilityState);
		this->m_DamageMax -= (int)(this->m_DamageMax * this->m_CurrentDurabilityState);
		this->m_Defense -= (int)(this->m_Defense * this->m_CurrentDurabilityState);
		this->m_SuccessfulBlocking -= (int)(this->m_SuccessfulBlocking * this->m_CurrentDurabilityState);

		if ( this->m_Durability < 1.0f )
		{
			this->m_AttackSpeed = 0;
		}
	}
	
	if ( this->m_Durability == 0.0f )
	{
		memset(this->m_Resistance , 0, sizeof(this->m_Resistance));
	}
}
 
int CItem::GetLevel() 
{
	return ItemAttribute[this->m_Type].Level;
}

DWORD CItem::GetNumber()
{
	return this->m_Number;
}

void CItem::Value()
{
	if ( this->m_Type == -1 )
	{
		return;
	}

	LPITEM_ATTRIBUTE p = &ItemAttribute[this->m_Type];

	if ( p->BuyMoney != 0 )
	{
		this->m_SellMoney = p->BuyMoney;
		this->m_BuyMoney = p->BuyMoney;
		this->m_SellMoney /= 3;
		
		if ( this->m_SellMoney >= 1000 )
		{
			this->m_SellMoney = this->m_SellMoney/100*100;
		}
		else if ( this->m_SellMoney >= 100 )
		{
			this->m_SellMoney = this->m_SellMoney/10*10;
		}

		if ( this->m_BuyMoney >= 1000 )
		{
			this->m_BuyMoney = this->m_BuyMoney/100*100;
		}
		else if ( this->m_BuyMoney >= 100 )
		{
			this->m_BuyMoney = this->m_BuyMoney/10*10;
		}

		return;
	}

	int Level = (int)(sqrt((double)this->m_Level));
	__int64 Gold = 0;
	int Type = (this->m_Type)/MAX_SUBTYPE_ITEMS;
	int Level2 = p->Level + this->m_Level*3;
	int excellent = 0;

	for (int i=0;i<this->m_SpecialNum;i++)
	{
		switch ( this->m_Special[i] )
		{
			case 0x56:	// 86.
			case 0x57:
			case 0x58:
			case 0x59:
			case 0x5A:
			case 0x5B:
			case 0x5C:
			case 0x5D:
			case 0x5E:
			case 0x5F:
			case 0x60:
			case 0x61:
			case 0x62:
			case 0x63:	// 99.
				excellent = 1;
		}
	}

	if ( excellent != 0 )
	{
		Level2 += 25;
	}

	if ( this->m_Type == ITEMGET(4,15) ) // Arrow
	{
		int lc10 = 70;

		if ( this->m_Level == 1 )
		{
			lc10 = 1200;
		}
		else if ( this->m_Level == 2 )
		{
			lc10 = 2000;
		}
		else if ( this->m_Level == 3 ) //season 4 add-on
		{
			lc10 = 2800;
		}

		if ( this->m_Durability > 0.0f )
		{
			Gold = (__int64)(lc10 * this->m_Durability/p->Durability);
		}
	}
	else if ( this->m_Type == ITEMGET(4,7) ) // Arrow of Crossbow
	{
		int lc11;

		if ( this->m_Durability > 0.0f )
		{
			lc11 = 100;

			if ( this->m_Level == 1 )
			{
				lc11 = 1400;
			}
			else if ( this->m_Level == 2 )
			{
				lc11 = 2200;
			}
			else if ( this->m_Level == 3 ) //season4 add-on
			{
				lc11 = 3000;
			}
		
			Gold = (__int64)(lc11 * this->m_Durability/p->Durability);
		}
	}
	else if ( this->m_Type == ITEMGET(14,13) ) // Bless
	{
		Gold = 9000000;
	}
	else if ( this->m_Type == ITEMGET(14,14) ) // soul
	{
		Gold = 6000000;
	}
	else if ( this->m_Type == ITEMGET(12,15) ) // chaos
	{
		Gold = 810000;
	}
	else if ( this->m_Type == ITEMGET(14,16) ) // Life
	{
		Gold = 45000000;
	}
	else if ( this->m_Type == ITEMGET(14,22) ) // Creation
	{
		Gold = 36000000;
	}
	else if ( this->m_Type == ITEMGET(12,30) ) //Pack Of Bless
	{
		Gold = (this->m_Level+1)*9000000*10;
	}
	else if ( this->m_Type == ITEMGET(12,31) ) //Pack Of Soul
	{
		Gold = (this->m_Level+1)*6000000*10;
	}
	else if ( this->m_Type == ITEMGET(13,15) ) //Fruits
	{
		Gold = 33000000;
	}
	else if ( this->m_Type == ITEMGET(13,14) ) //Loch Feather
	{
		if ( this->m_Level == 1 )
		{
			Gold = 7500000;	// Crest ofMonarch
		}
		else
		{
			Gold = 180000;	// Blue Feather
		}
	}
	else if ( this->m_Type == ITEMGET(14,31) ) // Jewel of Guardian
	{
		Gold = 60000000;
	}
	else if ( this->m_Type == ITEMGET(14,7) ) // Siege Potion
	{
		if ( this->m_Level == 0 )
		{
			Gold = (int)(this->m_Durability) * 900000;
		}
		else if ( this->m_Level == 1 )
		{
			Gold = (int)(this->m_Durability) * 450000;
		}
	}
	else if ( this->m_Type == ITEMGET(13,11) ) // Order(Guardian/Life Stone)
	{
		if ( this->m_Level == 1 )
		{
			Gold = 2400000;
		}
	}
	else if ( this->m_Type == ITEMGET(13,7) ) // Contract(Summon)
	{
		if ( this->m_Level == 0 )
		{
			Gold = 1500000;
		}
		else if ( this->m_Level == 1 )
		{
			Gold = 1200000;
		}
	}
	else if ( this->m_Type == ITEMGET(13,32) ) 
	{
		Gold = (int)this->m_Durability * 150;
	}
	else if ( this->m_Type == ITEMGET(13,33) ) 
	{
		Gold = (int)this->m_Durability * 300;
	}
	else if ( this->m_Type == ITEMGET(13,34) ) 
	{
		Gold = (int)this->m_Durability * 3000;
	}
	else if ( this->m_Type == ITEMGET(13,35) ) 
	{
		Gold = 30000;
	}
	else if ( this->m_Type == ITEMGET(13,36) ) 
	{
		Gold = 90000;
	}
	else if ( this->m_Type == ITEMGET(13,37) ) 
	{
		Gold = 150000;
	}
	else if ( this->m_Type == ITEMGET(14,35) ) 
	{
		Gold = (int)this->m_Durability * 2000;
	}
	else if ( this->m_Type == ITEMGET(14,36) ) 
	{
		Gold = (int)this->m_Durability * 4000;
	}
	else if ( this->m_Type == ITEMGET(14,37) ) 
	{
		Gold = (int)this->m_Durability * 6000;
	}
	else if ( this->m_Type == ITEMGET(14,38) ) 
	{
		Gold = (int)this->m_Durability * 2500;
	}
	else if ( this->m_Type == ITEMGET(14,39) ) 
	{
		Gold = (int)this->m_Durability * 5000;
	}
	else if ( this->m_Type == ITEMGET(14,40) ) 
	{
		Gold = (int)this->m_Durability * 7500;
	}
	else if ( this->m_Type == ITEMGET(13,3) ) // Dinorant
	{
		Gold = 960000;

		for ( int k=0;k<3;k++)
		{
			if ( (this->m_Option3 & (1<<k)) != 0 )
			{
				Gold += 300000;
			}
		}
	}
	else if ( this->m_Type == ITEMGET(14,17) ) // Devil Eye
	{
		switch ( this->m_Level )
		{
			case 1:
				Gold = 10000;
				break;
			case 2:
				Gold = 50000;
				break;
			case 3:
				Gold = 100000;
				break;
			case 4:
				Gold = 300000;
				break;
			case 5:
				Gold = 500000;
				break;
			case 6:
				Gold = 800000;
				break;
			case 7:
				Gold = 1000000;
				break;
			default:
				Gold = 30000;
				break;
		}
	}
	else if ( this->m_Type == ITEMGET(14,18) ) // Devil Key
	{
		switch ( this->m_Level )
		{
			case 1:
				Gold = 15000;
				break;
			case 2:
				Gold = 75000;
				break;
			case 3:
				Gold = 150000;
				break;
			case 4:
				Gold = 450000;
				break;
			case 5:
				Gold = 750000;
				break;
			case 6:
				Gold = 1200000;
				break;
			case 7:
				Gold = 1500000;
				break;
			default:
				Gold = 30000;
				break;
		}
	}
	else if ( this->m_Type == ITEMGET(14,19) ) // Devil's Invitation
	{
		switch ( this->m_Level )
		{
			case 1:
				Gold = 60000;
				break;
			case 2:
				Gold = 84000;
				break;
			case 3:
				Gold = 120000;
				break;
			case 4:
				Gold = 180000;
				break;
			case 5:
				Gold = 240000;
				break;
			case 6:
				Gold = 300000;
				break;
			case 7:
				Gold = 180000;
				break;
			default:
				Gold = 120000;
				break;
		}
	}
	else if ( this->m_Type == ITEMGET(14,20) ) // Remedy Of Love
	{
		Gold = 900;
	}
	else if ( this->m_Type == ITEMGET(14,21) ) // Rena
	{
		switch ( this->m_Level )
		{
			case 0:	// Rena
				Gold = 9000;
				this->m_Durability = this->m_BaseDurability;
			case 1:	// Stone
				Gold = 9000;
				this->m_Durability = this->m_BaseDurability;
				break;
			case 3:	// Mark of Lord
				Gold = (int)(this->m_Durability) * 3900;
				break;
			default:
				Gold = 9000;
				this->m_Durability = this->m_BaseDurability;
		}
	}
	else if ( this->m_Type == ITEMGET(14,100)) // Lucky Coin season 4.5
	{
		Gold = (int)(this->m_Durability) * 300;
	}
	else if ( this->m_Type == ITEMGET(14,9) && this->m_Level == 1) // Ale
	{
		Gold = 1000;
	}
	else if ( this->m_Type == ITEMGET(13,18) ) // Invisibility Cloak
	{
		switch ( this->m_Level )
		{
			case 1:
				Gold = 150000;
				break;
			case 2:
				Gold = 660000;
				break;
			case 3:
				Gold = 720000;
				break;
			case 4:
				Gold = 780000;
				break;
			case 5:
				Gold = 840000;
				break;
			case 6:
				Gold = 900000;
				break;
			case 7:
				Gold = 960000;
				break;
			case 8:
				Gold = 1020000;
				break;
			default:
				Gold = 600000;
				break;
		}
	}
	else if ( this->m_Type == ITEMGET(13,16) || this->m_Type == ITEMGET(13,17) ) // Blood and Paper of BloodCastle
	{
		switch ( this->m_Level )
		{
			case 1:
				Gold = 10000;
				break;
			case 2:
				Gold = 50000;
				break;
			case 3:
				Gold = 100000;
				break;
			case 4:
				Gold = 300000;
				break;
			case 5:
				Gold = 500000;
				break;
			case 6:
				Gold = 800000;
				break;
			case 7:
				Gold = 1000000;
				break;
			case 8:
				Gold = 1200000;
				break;
			default:
				Gold = 15000;
				break;
		}
	}
	else if ( this->m_Type == ITEMGET(13,29) ) // Armor of Guardman
	{
		Gold = 5000;
	}
	else if ( this->m_Type == ITEMGET(13,20) ) // Wizards Ring
	{
		switch ( this->m_Level )
		{
			case 0:
				Gold =30000;
				break;

			default:
				Gold = 0;
		}
	}
	else if ( this->m_Type == ITEMGET(13,31) ) // Spirit
	{
		switch ( this->m_Level )
		{
			case 0:
				Gold = 30000000;
				break;

			case 1:
				Gold = 15000000;
		}
	}
	else if ( this->m_Type == ITEMGET(14,28) ) // Lost Map
	{
		Gold = 600000;
	}
	else if ( this->m_Type == ITEMGET(14,29) ) // Symbol of Kundun
	{
		Gold = (__int64)(((10000.0f) * this->m_Durability) * 3.0f);
	}
	else if ( this->m_Type == ITEMGET(14,45) ||
		      this->m_Type == ITEMGET(14,46) ||
			  this->m_Type == ITEMGET(14,47) ||
			  this->m_Type == ITEMGET(14,48) ||
			  this->m_Type == ITEMGET(14,49) ||
			  this->m_Type == ITEMGET(14,50) )
	{
		Gold = (__int64)(((50.0f) * this->m_Durability) * 3.0f);
	}
	else if ( this->m_Type == ITEMGET(12,26) )
	{
		switch ( this->m_Level )
		{
			case 0:
				Gold = 60000;
				break;
		}
	}
	//
	else if ( this->m_Type == ITEMGET(14,51) ) //Star
	{
		Gold = 200000;
	}
	else if ( this->m_Type == ITEMGET(14,55) || //Green Chaos Box (Season 4.5)
			  this->m_Type == ITEMGET(14,56) || //Red Chaos Box (Season 4.5)
			  this->m_Type == ITEMGET(14,57) )  //Purple Chaos Box (Season 4.5)
	{
		Gold = 9000;
	}
	else if ( this->m_Type == ITEMGET(13,49) || //Illusion Temple Items -> (Old Scroll, Covenant and Scroll of Blood)
			  this->m_Type == ITEMGET(13,50) ||
			  this->m_Type == ITEMGET(13,51) )
	{
		switch ( this->m_Level )
		{
			case 1:
				Gold = 500000;
				break;
				//season 4 add-on
			case 2:
				Gold = 600000;
				break;
			case 3:
				Gold = 800000;
				break;
			case 4:
				Gold = 1000000;
				break;
			case 5:
				Gold = 1200000;
				break;
			case 6:
				Gold = 1400000;
				break;
			default:
				Gold = 9000;
				break;
		}
	}
	else if ( this->m_Type == ITEMGET(13,52) || //Condor Flame and Condor Feather
			  this->m_Type == ITEMGET(13,53) )
	{
		Gold = 3000000;
	}
	else if ( this->m_Type == ITEMGET(14,23) || //Quest Items since Second Evolution
			  this->m_Type == ITEMGET(14,24) ||
			  this->m_Type == ITEMGET(14,25) ||
			  this->m_Type == ITEMGET(14,26) ||
			  this->m_Type == ITEMGET(14,65) ||
			  this->m_Type == ITEMGET(14,66) ||
			  this->m_Type == ITEMGET(14,67) ||
			  this->m_Type == ITEMGET(14,68))
	{
		Gold = 9000;
	}
	//
	else if ( p->Value > 0 )
	{
		Gold += (p->Value * p->Value * 10)/12;

		if ( this->m_Type >= ITEMGET(14,0) && this->m_Type <= ITEMGET(14,8) )	// Potions + Antidote
		{
			if( this->m_Type == ITEMGET(14,3) || this->m_Type == ITEMGET(14,6) ) //season4 add-on
			{
				Gold *= 2; 
			}

			if ( this->m_Level > 0 )
			{
				Gold *= (__int64)(pow(2.0f, Level)) ;
			}

			Gold = Gold/10*10;
			Gold *= (__int64)this->m_Durability;
			this->m_BuyMoney = Gold;
			this->m_SellMoney = Gold/3;
			this->m_SellMoney = this->m_SellMoney/10*10;
			return;
		}
	}
	else if ( (Type == 12 && this->m_Type > ITEMGET(12,6) && (this->m_Type < ITEMGET(12,36) && this->m_Type > ITEMGET(12,43)) && (this->m_Type < ITEMGET(12,180) && this->m_Type > ITEMGET(12,END_WING_NUM)) ) || Type == 13 || Type == 15 ) //Third Wings Addition	//Custom Wings4
	{
		Gold = Level2*Level2*Level2+100;

		for (int u=0;u<this->m_SpecialNum;u++)
		{
			switch ( this->m_Special[u] )
			{
				case 0x55:
					Gold += Gold*this->m_Option3;
			}
		}
	}
	//
	else if ( this->m_Type == ITEMGET(14,63) ) //Season 2.5 Firecreacker (from Natasha Seller)
	{
		Gold = 200000;
	}
	//
	else if ( this->m_Type == ITEMGET(14,85) || //Season 4 fix
			  this->m_Type == ITEMGET(14,86) ||
			  this->m_Type == ITEMGET(14,87) ||
			  this->m_Type == ITEMGET(14,90)) 
	{
		Gold = (int)this->m_Durability * 300;
	}
	else
	{
		switch ( this->m_Level )
		{
			case  5:	Level2 +=   4;	break;
			case  6:	Level2 +=  10;	break;
			case  7:	Level2 +=  25;	break;
			case  8:	Level2 +=  45;	break;
			case  9:	Level2 +=  65;	break;
			case 10:	Level2 +=  95;	break;
			case 11:	Level2 += 135;	break;
			case 12:	Level2 += 185;	break;
			case 13:	Level2 += 245;	break;
		}

		if ( Type == 12 && this->m_Type <= ITEMGET(12,6) )	// Wings
		{
			Gold = (Level2+40)*Level2*Level2*11+40000000;
		}
		else if( Type == 12 && (this->m_Type >= ITEMGET(12,36) && this->m_Type <= ITEMGET(12,40)) ) //Third Wings
		{
			Gold = (Level2+40)*Level2*Level2*11+40000000;
		}
		else if( Type == 12 && (this->m_Type >= ITEMGET(12,41) && this->m_Type <= ITEMGET(12,43)) ) //Summoner Wings
		{
			Gold = (Level2+40)*Level2*Level2*11+40000000;
		}
		else if( Type == 12 && (this->m_Type >= ITEMGET(12,180) && this->m_Type <= ITEMGET(12,END_WING_NUM)) ) //Custom Wings4
		{
			Gold = (Level2+40)*Level2*Level2*11+40000000;
		}
		else
		{
			Gold = (Level2+40)*Level2*Level2/8+100;
		}

		if ( Type >= 0 && Type <=  6 )
		{
			if ( p->TwoHand == 0 )
			{
				Gold = Gold*80/100;
			}
		}

		for ( int g=0;g<this->m_SpecialNum;g++)
		{
			switch ( this->m_Special[g] )
			{
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 56:
					Gold += (__int64)(Gold * 1.5);
					break;

				case 80:
				case 81:
				case 83:
				case 85:
				case 113: //Summoner

					switch ( this->m_Option3 )
					{
						case 1:
							Gold += (__int64)(Gold * 6.0 / 10.0);
							break;

						case 2:
							Gold += (__int64)(Gold * 14.0 / 10.0);
							break;

						case 3:
							Gold += (__int64)(Gold * 28.0 / 10.0);
							break;

						case 4:
							Gold += (__int64)(Gold * 56.0 / 10.0);
							break;
					}
					break;

				case 82:

					switch ( this->m_Option3 )
					{
					case 1:
							Gold += (__int64)(Gold * 6.0 / 10.0);
							break;

						case 2:
							Gold += (__int64)(Gold * 14.0 / 10.0);
							break;

						case 3:
							Gold += (__int64)(Gold * 28.0 / 10.0);
							break;

						case 4:
							Gold += (__int64)(Gold * 56.0 / 10.0);
							break;
					}
					break;

				case 84:
					Gold += (__int64)(Gold * 25.0 / 100.0);
					break;

				case 86:
				case 87:
				case 88:
				case 89:
				case 90:
				case 91:
				case 92:
				case 93:
				case 94:
				case 95:
				case 96:
				case 97:
				case 98:
				case 99:
					Gold += Gold;
					break;

				case 100:
				case 101:
				case 102:
				case 103:
				case 104:
					//Season 2.5 add-on third wing option
				case 108:
				case 109:
				case 110:
				case 111:
					Gold += (__int64)(Gold * 25.0 / 100.0);
					break;

			}
		}
	}

	if ( g_kItemSystemFor380.Is380OptionItem(this) == TRUE )
	{
		Gold += (__int64)(Gold * 16.0 / 100.0);
	}

	if ( g_SocketOption.IsSocketOption(this) == 1 ) //season 4 add-on
	{
		int loc15 = 0;
		int loc16 = 0;
		DWORD loc17 = 0; //17

		for(int loc18 = 0; loc18 < 5; loc18++)
		{
			if(this->m_SocketOption[loc18] != 0xFF)
			{
				if(this->m_SocketOption[loc18] != 0xFE)
				{
					loc17 += g_SocketOption.GetValue(this->m_SocketOption[loc18]);
				}
				loc15+=1;
			}
		}

		Gold += (DWORD)( (((float)(Gold) * (float)(loc15*8))) / 10.0f);
		Gold += (DWORD)loc17;
	}

	if ( Gold > 3000000000 )
	{
		Gold = 3000000000;
	}

	this->m_BuyMoney = (DWORD)Gold;
	this->m_SellMoney = (DWORD)Gold;
	
	this->m_SellMoney = this->m_SellMoney/3;

	if ( (this->m_Type < ITEMGET(14,0) || this->m_Type >  ITEMGET(14,8)) &&
		  this->m_Type != ITEMGET(13,20) &&
		  this->m_Type != ITEMGET(14,28) &&
		  this->m_Type != ITEMGET(14,29) &&
		  this->m_Type != ITEMGET(14,21) &&
		  this->m_Type != ITEMGET(13,15) &&
		  this->m_Type != ITEMGET(13,16) &&
		  this->m_Type != ITEMGET(13,17) &&
		  this->m_Type != ITEMGET(13,18) &&
		  this->m_Type != ITEMGET(13,11) &&
		  this->m_Type != ITEMGET(13,7)  &&
		  this->m_Type != ITEMGET(13,32) &&
		  this->m_Type != ITEMGET(13,33) &&
		  this->m_Type != ITEMGET(13,34) &&
		  this->m_Type != ITEMGET(13,35) &&
		  this->m_Type != ITEMGET(13,36) &&
		  this->m_Type != ITEMGET(13,37) &&
		  this->m_Type != ITEMGET(14,45) &&
		  this->m_Type != ITEMGET(14,46) &&
		  this->m_Type != ITEMGET(14,47) &&
		  this->m_Type != ITEMGET(14,48) &&
		  this->m_Type != ITEMGET(14,49) &&
		  this->m_Type != ITEMGET(14,50) &&
		  this->m_Type != ITEMGET(14,51) &&  //Season 2.5 Star of Christmas
		  this->m_Type != ITEMGET(14,100) && //Season 4.5 Lucky Coin
		  this->m_Type == ITEMGET(14,85) && //S4
		  this->m_Type == ITEMGET(14,86) && //S4
		  this->m_Type == ITEMGET(14,87) && //S4
		  this->m_Type == ITEMGET(14,90) ) //S4
	{
		float lc15 = 1.0f-(this->m_Durability / this->m_BaseDurability);
		int lc16 = (int)(this->m_SellMoney*0.6*lc15);
		this->m_SellMoney -= lc16;
	}

	if ( this->m_SellMoney >= 1000 )
	{
		this->m_SellMoney = this->m_SellMoney/100*100;
	}
	else if ( this->m_SellMoney >= 100 )
	{
		this->m_SellMoney = this->m_SellMoney/10*10;
	}

	if ( this->m_BuyMoney >= 1000 )
	{
		this->m_BuyMoney = this->m_BuyMoney/100*100;
	}
	else if ( this->m_BuyMoney >= 100 )
	{
		this->m_BuyMoney = this->m_BuyMoney/10*10;
	}
}

void CItem::OldValue()
{
	if ( this->m_Type == -1 )
	{
		return;
	}

	int Gold = 0;

	if ( this->m_Type == ITEMGET(14,13) ) // Bless
	{
		Gold = 100000;
	}
	else if ( this->m_Type == ITEMGET(14,14) ) // Soul
	{
		Gold = 70000;
	}
	else if ( this->m_Type == ITEMGET(12,15) ) // Chaos
	{
		Gold = 40000;
	}
	else if ( this->m_Type == ITEMGET(14,22) ) // Creation
	{
		Gold = 450000;
	}
	else if ( this->m_Type == ITEMGET(14,16) ) // Life
	{
		Gold = 450000;
	}
	else
	{
		this->m_OldBuyMoney = this->m_BuyMoney;
		return;
	}

	this->m_OldBuyMoney = Gold;

	if ( this->m_OldBuyMoney >= 1000 )
	{
		this->m_OldBuyMoney = this->m_OldBuyMoney /100*100;
	}
	else if ( this->m_OldBuyMoney >= 100 )
	{
		this->m_OldBuyMoney = this->m_OldBuyMoney / 10 * 10;
	}
}

CPetItemExp::CPetItemExp()
{
	this->m_DarkSpiritExpTable[0] = 0;
	this->m_DarkSpiritExpTable[1] = 0;

	for ( int i = 2 ; i < MAX_PET_LEVEL+2 ; i++ )
	{
		this->m_DarkSpiritExpTable[i] = (i+10) * i * i * i * 100;
	}

	this->m_DarkHorseExpTable[0] = 0;
	this->m_DarkHorseExpTable[1] = 0;

	for (int i = 2 ; i < MAX_PET_LEVEL+2 ; i++ )
	{
		this->m_DarkHorseExpTable[i] = (i+10) * i * i * i * 100;
	}
}

BOOL CItem::GetSize(int & w, int & h)
{
	w=ItemAttribute[this->m_Type].Width  ;
	h=ItemAttribute[this->m_Type].Height  ;

	return 1;
}

int CItem::ItemDamageMin()
{
	int damagemin;
	
	if (this->m_Type < 0)
	{
		return 0;
	}
	else
	{
		damagemin=this->m_DamageMinOrigin;
		this->PlusSpecial(&damagemin, 80);
		return damagemin;
	}
}

int CItem::ItemDefense()
{
	int Defense;
	
	if (this->m_Type < 0)
	{
		return 0;
	}
	else
	{
		if (this->m_IsValidItem == false)
		{
			return 0;
		}
		else
		{
			Defense=this->m_Defense;
			this->PlusSpecial(&Defense, 83);
			return Defense;
		}
	}
}

int CItem::BookSpellDmg()
{
	int Value;
	
	if (this->m_Type < 0)
	{
		return 0;
	}

	if(this->m_IsValidItem == false)
	{
		return 0;
	}
	
	Value = this->m_BookSpell;

	return Value;
}

BOOL CItem::IsClass(char aClass, int ChangeUP, int ChangeUP3rd)
{
	if ((aClass < 0) || (aClass >= MAX_TYPE_PLAYER ))
	{
		LogAdd("Ŭ���� ���� : %d (%s %d)", aClass, __FILE__, __LINE__);
		return 0;
	}
	
	int requireclass=this->m_RequireClass[aClass];
	if (requireclass == 0)
	{
		return 0;
	}
	if (requireclass >= 3)
	{
		if (requireclass != (ChangeUP3rd+2))
		{
			return 0;
		}
	}
	else
	{
		if (requireclass > 1)
		{
			if ( requireclass  != (ChangeUP+1) )
			{
				return 0;
			}
		}
	}
	return 1;
}

LPSTR CItem::GetName()
{
	return &ItemAttribute[this->m_Type].Name[0];
}

void CItem::PlusSpecialSetRing(BYTE* Value)
{
	if ( this->m_Type < 0 )
	{
		return;
	}

	if ( this->IsSetItem() == FALSE )
	{
		return;
	}

	if ( this->m_Durability == 0.0f)
	{
		return;
	}

	if ( this->m_IsValidItem == false )
	{
		return;
	}

	LPITEM_ATTRIBUTE p = &ItemAttribute[this->m_Type];

	if ( p->ResistanceType == -1 )
	{
		return;
	}

	BYTE iValue = 5;
	Value[p->ResistanceType] += iValue - (BYTE)( iValue * this->m_CurrentDurabilityState);
}

void CItem::PlusSpecial(int * Value, int Special)
{
	if ( this->m_Type < 0 )
	{
		return;
	}

	if ( this->m_Durability == 0.0f)
	{
		return;
	}

	if ( this->m_IsValidItem == false )
	{
		return;
	}

	for (int i =0;i<this->m_SpecialNum;i++)
	{
		if ( this->m_Special[i] == Special )
		{
			switch ( Special )
			{
				case 82:
					{
						int lc3 = this->m_Option3*5;
						*Value += lc3 - (int)( lc3 * this->m_CurrentDurabilityState );
					}
					break;

				case 84:
					* Value += 4;
					break;

				case 81:
				case 80:
				case 83:
				case 113: //Summoner
					{
						int lc4 = this->m_Option3*4;
						*Value += lc4 - (int)( lc4 * this->m_CurrentDurabilityState );
					}
					break;

				case 100:
				case 101:
					*Value =  *Value + this->m_Level * 5 + 50;
					break;

				case 103:
					*Value += 50;
					break;

				case 105:
					*Value =  *Value + this->m_Level * 5 + 10;

					break;

				default:
					*Value = *Value + (this->m_Option3*4);
					break;
			}
		}
	}
}

void CItem::PlusSpecialPercent(int * Value, int Special, WORD Percent)
{
	if ( this->m_Type < 0 )
	{
		return;
	}

	for (int i=0;i<this->m_SpecialNum;i++)
	{
		if ( this->m_Special[i] == Special )
		{
			*Value += (*Value * Percent)/ 100;
		}
	}
}

void CItem::PlusSpecialPercentEx(int * Value, int SourceValue, int Special)
{
	if ( this->m_Type < 0 )
	{
		return;
	}

	if ( this->m_Durability == 0.0f )
	{
		return;
	}

	if ( this->m_IsValidItem == false  )
	{
		return;
	}

	for ( int i =0;i<this->m_SpecialNum;i++)
	{
		if ( this->m_Special[i] == Special )
		{
			int lc3 = SourceValue * this->m_Option3/100;
			*Value += lc3 - (int)(lc3 * this->m_CurrentDurabilityState );
		}
	}
}

void CItem::SetItemPlusSpecialStat(short * Value, int Special)
{
	if ( this->m_Type < 0 )
	{
		return;
	}

	if ( this->m_Durability == 0.0f )
	{
		return;
	}

	for ( int i =0;i<this->m_SpecialNum;i++)
	{
		if ( this->m_Special[i] == Special )
		{
			switch ( Special )
			{
				case 0xC4:
				case 0xC5:
				case 0xC6:
				case 0xC7:
					{
						int lc3 = this->m_SetAddStat;
						*Value += lc3 - (int)(lc3 * this->m_CurrentDurabilityState);
					}
					break;

				default:
					*Value += this->m_Option3*3;
			}
		}
	}
}

int CItem::GetAddStatType()
{
	LPITEM_ATTRIBUTE p;
	p = &ItemAttribute[this->m_Type];
	return p->SetAttr;
}

int CItem::GetWeaponType()
{
	if ( this->m_Type <= ITEMGET(5,0) )
	{
		return 1;
	}

	if ( this->m_Type <= ITEMGET(6,0) )
	{
		return 2;
	}
	return 0;
}

void CItem::SetPetItemInfo(int petlevel, int petexp)
{
	if ( this->m_Type == ITEMGET(13,4) )
	{
		this->m_PetItem_Level = petlevel;
		this->m_PetItem_Exp = petexp;

		if ( this->m_PetItem_Exp < gPetItemExp.m_DarkHorseExpTable[this->m_PetItem_Level] || this->m_PetItem_Exp >= gPetItemExp.m_DarkHorseExpTable[1+this->m_PetItem_Level] )
		{
			this->m_PetItem_Exp = gPetItemExp.m_DarkHorseExpTable[this->m_PetItem_Level];
		}

		this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
			this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		this->PetValue();
		this->m_IsLoadPetItemInfo = 1;
	}
	else if ( this->m_Type == ITEMGET(13,5) )
	{
		this->m_PetItem_Level = petlevel;
		this->m_PetItem_Exp = petexp;

		if ( this->m_PetItem_Exp < gPetItemExp.m_DarkSpiritExpTable[this->m_PetItem_Level] || this->m_PetItem_Exp >= gPetItemExp.m_DarkSpiritExpTable[1+this->m_PetItem_Level] )
		{
			this->m_PetItem_Exp = gPetItemExp.m_DarkSpiritExpTable[this->m_PetItem_Level];
		}

		this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
			this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);

		this->PetValue();
		this->m_IsLoadPetItemInfo = 1;
	}
}

BOOL CItem::AddPetItemExp(int petexp)
{
	if ( this->m_Durability <= 0.0f )
	{
		return FALSE;
	}

	if ( this->m_IsLoadPetItemInfo == 0 )
	{
		return FALSE;
	}

	if ( this->m_PetItem_Level < 1 )
	{
		this->m_PetItem_Level = 1;
		this->m_PetItem_Exp = 0;
		this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
			this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		this->PetValue();

		return FALSE;
	}

	if ( this->m_Type == ITEMGET(13,4) )
	{
		if ( this->m_PetItem_Level >= MAX_PET_LEVEL )
		{
			return FALSE;
		}

		BOOL ret = FALSE;
		int maxexp = gPetItemExp.m_DarkHorseExpTable[1+this->m_PetItem_Level];
		this->m_PetItem_Exp += petexp;

		while ( this->m_PetItem_Exp >= maxexp )
		{
			this->m_PetItem_Level++;
			maxexp = gPetItemExp.m_DarkHorseExpTable[1+this->m_PetItem_Level];
			ret = TRUE;
		}

		if ( ret != FALSE )
		{
		this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
			this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		this->PetValue();

		return TRUE;
		}
	}
	else if ( this->m_Type == ITEMGET(13,5) )
	{
		if ( this->m_PetItem_Level >= MAX_PET_LEVEL )
		{
			return FALSE;
		}

		BOOL ret = FALSE;
		int maxexp = gPetItemExp.m_DarkSpiritExpTable[1+this->m_PetItem_Level];
		this->m_PetItem_Exp += petexp;

		while ( this->m_PetItem_Exp >= maxexp )
		{
			this->m_PetItem_Level++;
			maxexp = gPetItemExp.m_DarkSpiritExpTable[1+this->m_PetItem_Level];
			ret = TRUE;
		}

		if ( ret != FALSE )
		{
		this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
			this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		this->PetValue();

		return TRUE;
		}
	}

	return FALSE;
}

BOOL CItem::DecPetItemExp(int percent)
{
	if ( this->m_IsLoadPetItemInfo == 0 )
	{
		return FALSE;
	}

	if ( this->m_PetItem_Level < 1 )
	{
		this->m_PetItem_Level = 1;
		this->m_PetItem_Exp = 0;
		this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
			this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		this->PetValue();

		return FALSE;
	}

	if ( this->m_Type == ITEMGET(13,4) )
	{
		int exp = gPetItemExp.m_DarkHorseExpTable[1+this->m_PetItem_Level] - gPetItemExp.m_DarkHorseExpTable[this->m_PetItem_Level];
		exp = exp * percent/100;
		this->m_PetItem_Exp -= exp;

		if ( this->m_PetItem_Exp < 0 )
		{
			this->m_PetItem_Level = 1;
			this->m_PetItem_Exp = 0;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
				this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			this->PetValue();
		}
		else if ( this->m_PetItem_Exp < gPetItemExp.m_DarkHorseExpTable[this->m_PetItem_Level] )
		{
			this->m_PetItem_Level--;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
				this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			this->PetValue();
			
			return TRUE;
		}
	}
	else if ( this->m_Type == ITEMGET(13,5) )
	{
		int exp = gPetItemExp.m_DarkSpiritExpTable[1+this->m_PetItem_Level] - gPetItemExp.m_DarkSpiritExpTable[this->m_PetItem_Level];
		exp = exp * percent/100;
		this->m_PetItem_Exp -= exp;

		if ( this->m_PetItem_Exp < 0 )
		{
			this->m_PetItem_Level = 1;
			this->m_PetItem_Exp = 0;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
				this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			this->PetValue();
		}
		else if ( this->m_PetItem_Exp < gPetItemExp.m_DarkSpiritExpTable[this->m_PetItem_Level] )
		{
			this->m_PetItem_Level--;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
				this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			this->PetValue();
			
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CItem::PetItemLevelDown(int exp)
{
	if ( this->m_IsLoadPetItemInfo == FALSE )
	{
		return FALSE;
	}

	if ( this->m_PetItem_Level < 2 )
	{
		return FALSE;
	}

	this->m_PetItem_Exp -= exp;
	this->m_PetItem_Level--;

	if ( this->m_Type == ITEMGET(13,4) )
	{
		int petlevel = this->m_PetItem_Level;
		int petexp = gPetItemExp.m_DarkHorseExpTable[petlevel];

		while ( this->m_PetItem_Exp <= petexp )
		{
			if ( petlevel <= 1 )
			{
				break;
			}

			petlevel--;
			petexp = gPetItemExp.m_DarkHorseExpTable[petlevel];
		}

		this->m_PetItem_Level = petlevel;
	}
	else if ( this->m_Type == ITEMGET(13,5) )
	{
		int petlevel = this->m_PetItem_Level;
		int petexp = gPetItemExp.m_DarkSpiritExpTable[petlevel];

		while ( this->m_PetItem_Exp <= petexp )
		{
			if ( petlevel <= 1 )
			{
				break;
			}

			petlevel--;
			petexp = gPetItemExp.m_DarkSpiritExpTable[petlevel];
		}

		this->m_PetItem_Level = petlevel;
	}

	this->Convert(this->m_Type, this->m_Option1, this->m_Option2,
		this->m_Option3, this->m_NewOption, this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
	this->PetValue();

	return TRUE;
}

void CItem::PetValue()
{
	if ( this->m_Type == ITEMGET(13,4) )
	{
		this->m_SellMoney = this->m_PetItem_Level * 2000000;
	}
	else if ( this->m_Type == ITEMGET(13,5) )
	{
		this->m_SellMoney = this->m_PetItem_Level * 1000000;
	}	

	this->m_BuyMoney = this->m_SellMoney;
	this->m_SellMoney /= 3;

	if ( this->m_SellMoney >= 1000 )
	{
		this->m_SellMoney = this->m_SellMoney / 100 * 100;
	}
	else if ( this->m_SellMoney >= 100 )
	{
		this->m_SellMoney = this->m_SellMoney / 10 * 10;
	}

	if ( this->m_BuyMoney >= 1000 )
	{
		this->m_BuyMoney = this->m_BuyMoney / 100 * 100;
	}
	else if ( this->m_BuyMoney >= 100 )
	{
		this->m_BuyMoney = this->m_BuyMoney / 10 * 10;
	}
}

BOOL CItem::IsExtItem()
{
	if ( this->m_Type == ITEMGET(13,37) )
	{
		return FALSE;
	}

	if ( (this->m_NewOption & 0x7F)!= 0 )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CItem::IsExtLifeAdd()
{
	if ( (this->m_NewOption & 0x20) == 32 )
	{
		return 4;
	}

	return 0;
}

BOOL CItem::IsExtManaAdd()
{
	if ( (this->m_NewOption & 0x10) == 16 )
	{
		return 4;
	}

	return 0;
}

BOOL CItem::IsExtDamageMinus()
{
	if ( (this->m_NewOption & 8) == 8 )
	{
		return 4;
	}

	return 0;
}

BOOL CItem::IsExtDamageReflect()
{
	if ( (this->m_NewOption & 4) == 4 )
	{
		return 5;
	}

	return 0;
}


BOOL CItem::IsExtDefenseSuccessfull()
{
	if ( (this->m_NewOption & 2) == 2 )
	{
		return 10;
	}

	return 0;
}

BOOL CItem::IsExtMonsterMoney()
{
	if ( (this->m_NewOption & 1) == 1 )
	{
		return 30; //season4 changed
	}

	return 0;
}

BOOL CItem::IsExtExcellentDamage()
{
	if ( (this->m_Type >= ITEMGET(6,0) ) && (this->m_Type < ITEMGET(7,0) ) )
	{
		return 0;
	}

	if ( ( this->m_NewOption & 0x20 ) == 0x20 )
	{
		return 10;
	}
	return 0;
}

BOOL CItem::IsExtAttackRate()
{
	if ( (this->m_NewOption & 0x10) == 16 )
	{
		return 1;
	}

	return 0;
}

BOOL CItem::IsExtAttackRate2()
{
	if ( (this->m_NewOption & 8) == 8 )
	{
		return 2;
	}

	return 0;
}

BOOL CItem::IsExtAttackSpeed()
{
	if ( (this->m_NewOption & 4) == 4 )
	{
		return 7;
	}

	return 0;
}


BOOL CItem::IsExtMonsterDieLife()
{
	if ( (this->m_NewOption & 2) == 2 )
	{
		return 1;
	}

	return 0;
}


BOOL CItem::IsExtMonsterDieMana()
{
	if ( this->m_Type >= ITEMGET(6,0) && this->m_Type < ITEMGET(7,0) )
	{
		return 0;
	}

	if ( (this->m_NewOption & 1) == 1 )
	{
		return 1;
	}
	return 0;
}

BOOL CItem::IsWingOpGetOnePercentDamage()
{
	if ( this->m_Durability  < 1.0f )
	{
		return 0;
	}

	if ( this->m_Type >= ITEMGET(12,3) && this->m_Type <= ITEMGET(12,6) || this->m_Type == ITEMGET(13,30) || this->m_Type == ITEMGET(12,42) )
	{
		if ( (this->m_NewOption & 4)!= 0 )
		{
			return 3;
		}
	}
	return 0;
}

BOOL CItem::IsWingOpGetManaToMoster()
{
	if ( this->m_Durability < 1.0f )
	{
		return 0;
	}

	if ( this->m_Type >= ITEMGET(12,3) && this->m_Type <= ITEMGET(12,6) || this->m_Type == ITEMGET(13,30) || this->m_Type == ITEMGET(12,42) )
	{
		if ( (this->m_NewOption & 16 ) == 1 )
		{
			return 10;
		}
	}
	return 0;
}

BOOL CItem::IsDinorantReduceAttackDamaege()
{
	if ( this->m_Durability  < 1.0f )
	{
		return 0;
	}

	if ( (this->m_NewOption & 1 ) == 1 )
	{
		return 5;
	}
	return 0;
}


int CItem::IsFenrirIncLastAttackDamage()
{
	if ( this->m_Durability < 1.0f )
	{
		return 0;
	}

	if ( (this->m_NewOption&1) == 1 )
	{
		return 10;
	}

	return 0;
}

int CItem::IsFenrirDecLastAttackDamage()
{
	if ( this->m_Durability < 1.0f )
	{
		return 0;
	}

	if ( (this->m_NewOption&2) == 2 )
	{
		return 10;
	}

	return 0;
}

int CItem::IsFenrirSpecial()
{
	if ( this->m_Durability < 1.0f )
	{
		return 0;
	}

	if ( (this->m_NewOption&4) == 4 )
	{
		return 1;
	}

	return 0;
}

int CItem::IsThirdWingOpGetOnePercentDamage()
{
	if ( this->m_Type >= ITEMGET(12,36) && this->m_Type <= ITEMGET(12,40) || this->m_Type >= ITEMGET(12,180) && this->m_Type <= ITEMGET(12,END_WING_NUM) || this->m_Type == ITEMGET(12,43))	//Custom Wings4
	{
		if ( this->m_Durability < 1.0f )
		{
			return 0;
		}
		else if ( (this->m_NewOption&1) == 1 )
		{
			return 5;
		}
	}

	return 0;
}

int CItem::SimpleDurabilityDown(int iDecValue)
{
	this->m_Durability -= 1.0f ;

	if ( this->m_Durability < 0 )
	{
		this->m_Durability = 0.0f;
		return 0;
	}

	if ( this->CheckDurabilityState() != 0 )
	{
		return 2;
	}

	return (int)this->m_Durability;
}

int CItem::DurabilityDown(int dur, int iDecValue)
{
	if ( this->m_Durability <= 0 )
	{
		return 0;
	}

	this->m_DurabilitySmall += dur;

	int DurabilitySmall = 564;

	if(gObj[iDecValue].m_MLPassiveSkill.m_iML_DurationReduction2 > 0) //season3 add-on
	{
		DurabilitySmall += DurabilitySmall * gObj[iDecValue].m_MLPassiveSkill.m_iML_DurationReduction2 / 100;
	}
	
	if ( this->m_DurabilitySmall > DurabilitySmall )
	{
		this->m_DurabilitySmall = 0;
		this->m_Durability -= 1.0f;

		if ( this ->m_Durability < 0.0f )
		{
			this->m_Durability = 0;
		}

		if ( this->CheckDurabilityState() != FALSE )
		{
			return 2;
		}
		return 1;
	}
	
	return (int)this->m_Durability;
}

int CItem::DurabilityDown2(int dur, int iDecValue)
{
	if ( this->m_Durability <= 0 )
	{
		return 0;
	}

	this->m_DurabilitySmall += dur;

	int DurabilitySmall = 1000;

	if(gObj[iDecValue].m_MLPassiveSkill.m_iML_DurationReduction1 > 0) //season3 add-on
	{
		DurabilitySmall += DurabilitySmall * gObj[iDecValue].m_MLPassiveSkill.m_iML_DurationReduction1 / 100;
	}
	
	if ( this->m_DurabilitySmall > DurabilitySmall )
	{
		this->m_DurabilitySmall = 0;
		this->m_Durability -= 1.0f;

		if ( this->m_Durability < 0.0f )
		{
			this->m_Durability = 0;
		}

		if ( this->CheckDurabilityState() != FALSE )
		{
			return 2;
		}
		return 1;
	}
	
	return 0;
}

int CItem::NormalWeaponDurabilityDown(int defense, int aIndex)
{
	if ( this->m_Durability <= 0 )
	{
		return 0;
	}

	int damagemin = this->m_DamageMinOrigin; //2
	int plusdamage = 0; //3
	this->PlusSpecial(&plusdamage, 80);

	if ( damagemin == 0 )
	{
		LogAdd("damagemin�� 0�̴�");
		return 0;
	}

	int div = damagemin + damagemin/2 + plusdamage; //4

	if ( div == 0 )
	{
		return 0;
	}

	int DecreaseDur = (defense*2)/div; //5

	DecreaseDur -= DecreaseDur*(int)this->m_SocketBonus/100; //season4 add-on

	this->m_DurabilitySmall += DecreaseDur;

	int DurabilitySmall = 564;

	if(gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 > 0) //season3 add-on
	{
		DurabilitySmall += DurabilitySmall * gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 / 100;
	}

	if ( this->m_DurabilitySmall > DurabilitySmall )
	{
		this->m_DurabilitySmall = 0;
		this->m_Durability -= 1.0f;

		if ( this->m_Durability < 0.0f )
		{
			this->m_Durability = 0;
		}

		if ( this->CheckDurabilityState() != 0 )
		{
			return 2;
		}
		
		return 1;
		
	}
	return 0;
}

int CItem::BowWeaponDurabilityDown(int defense, int aIndex)
{
	if ( this->m_Durability <= 0 )
	{
		return 0;
	}

	int damagemin = this->m_DamageMinOrigin;
	int plusdamage = 0;
	this->PlusSpecial(&plusdamage, 80);
	
	int div = damagemin + damagemin/2 + plusdamage;

	if ( div == 0 )
	{
		return 0;
	}

	int DecreaseDur = (defense*2)/div;

	DecreaseDur -= DecreaseDur*(int)this->m_SocketBonus/100; //season4 add-on

	this->m_DurabilitySmall += DecreaseDur;

	int DurabilitySmall = 780;

	if(gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 > 0) //season3 add-on
	{
		DurabilitySmall += DurabilitySmall * gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 / 100;
	}

	if ( this->m_DurabilitySmall > DurabilitySmall )
	{
		this->m_DurabilitySmall = 0;
		this->m_Durability -= 1.0f;

		if ( this->m_Durability < 0.0f )
		{
			this->m_Durability = 0;
		}
		
		if ( this->CheckDurabilityState() != 0 )
		{
			return 2;
		}
		
		return 1;
		
	}
	return 0;
}

int CItem::StaffWeaponDurabilityDown(int defence, int aIndex)
{
	if ( this->m_Durability <= 0 )
	{
		return 0;
	}

	int magic = this->m_Magic/2 + this->m_Level*2;
	int plusmagic = 0;
	this->PlusSpecial(&plusmagic, 81);
	int div = magic + magic/3 + plusmagic;

	if ( div == 0 )
	{
		return 0;
	}

	int DecreaseDur = defence/div;

	DecreaseDur -= DecreaseDur*(int)this->m_SocketBonus/100; //season4 add-on

	this->m_DurabilitySmall += DecreaseDur;

	int DurabilitySmall = 1050;

	if(gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 > 0) //season3 add-on
	{
		DurabilitySmall += DurabilitySmall * gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 / 100;
	}

	if ( this->m_DurabilitySmall > DurabilitySmall )
	{
		this->m_DurabilitySmall = 0;
		this->m_Durability -= 1.0f;

		if ( this->m_Durability < 0.0f )
		{
			this->m_Durability = 0;
		}
		
		if ( this->CheckDurabilityState() != 0 )
		{
			return 2;
		}
		return 1;
		
	}
	return 0;
}

int CItem::ArmorDurabilityDown(int damagemin, int aIndex)
{
	if ( this->m_Durability <= 0 )
	{
		return 0;
	}

	if ( this->m_Type == -1 )
	{
		return 0;
	}

	int def = this->m_DefenseOrigin;
	int plusdef = 0;
	int DecreaseDur;

	if ( def == 0 )
	{
		LogAdd("def�� 0�̴�");
		return 0;
	}

	if ( this->m_Type >= ITEMGET(6,0) && this->m_Type < ITEMGET(7,0) )
	{
		this->PlusSpecial(&plusdef, 82);
		DecreaseDur = damagemin/(def * 5+ plusdef);
	}
	else if ( this->m_RequireClass[0] != 0 )	// Dark Wize
	{
		this->PlusSpecial(&plusdef, 83);
		DecreaseDur = damagemin/(def * 3 + plusdef);
	}
	else if ( this->m_RequireClass[1] != 0 )	// Dark Knight
	{
		this->PlusSpecial(&plusdef, 83);
		DecreaseDur = damagemin/(def * 3 + plusdef);
	}
	else if ( this->m_RequireClass[2] != 0 )	// Elf
	{
		this->PlusSpecial(&plusdef, 83);
		DecreaseDur = damagemin/(def * 2 + plusdef);
	}
	else if ( this->m_RequireClass[3] != 0 )	// MAgic Gladiator ( aka Magunsa )
	{
		this->PlusSpecial(&plusdef, 83);
		DecreaseDur = damagemin/(def * 7 + plusdef);
	}
	else if ( this->m_RequireClass[4] != 0 )	// Dark Lord
	{
		this->PlusSpecial(&plusdef, 83);
		DecreaseDur = damagemin/(def * 6 + plusdef);
	}
	else if ( this->m_RequireClass[5] != 0 )	// Summoner
	{
		this->PlusSpecial(&plusdef, 83);
		DecreaseDur = damagemin/(def * 3 + plusdef);
	}

	this->m_DurabilitySmall += DecreaseDur;

	int DurabilitySmall = 69;

	if(gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 > 0) //season3 add-on
	{
		DurabilitySmall += DurabilitySmall * gObj[aIndex].m_MLPassiveSkill.m_iML_DurationReduction1 / 100;
	}

	if ( this->m_DurabilitySmall > DurabilitySmall )
	{
		this->m_DurabilitySmall = 0;
		this->m_Durability -= 1.0f;

		if ( this->m_Durability < 0.0f )
		{
			this->m_Durability = 0;
		}
		
		if ( this->CheckDurabilityState() != 0 )
		{
			return 2;
		}
		
		return 1;
		
	}
	return 0;
}

BOOL CItem::CheckDurabilityState()
{
	if ( this->m_Durability == 0.0f )
	{
		if ( this->m_CurrentDurabilityState != 1.0f )
		{
			this->m_CurrentDurabilityState = 1.0f;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2, this->m_Option3, this->m_NewOption,
				this->m_SetOption, this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			return true;
		}
	}
	else if ( this->m_Durability < this->m_DurabilityState[2] )
	{
		if ( this->m_CurrentDurabilityState != 0.5f )
		{
			this->m_CurrentDurabilityState = 0.5f;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2, this->m_Option3, this->m_NewOption,
				this->m_SetOption,this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			return true;
		}
	}
	else if ( this->m_Durability < this->m_DurabilityState[1] )
	{
		if ( this->m_CurrentDurabilityState != 0.3f )
		{
			this->m_CurrentDurabilityState = 0.3f;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2, this->m_Option3, this->m_NewOption,
				this->m_SetOption,this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			return true;
		}
	}
	else if ( this->m_Durability < this->m_DurabilityState[0] )
	{
		if ( this->m_CurrentDurabilityState != 0.2f )
		{
			this->m_CurrentDurabilityState = 0.2f;
			this->Convert(this->m_Type, this->m_Option1, this->m_Option2, this->m_Option3, this->m_NewOption,
				this->m_SetOption,this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
			return true;
		}
	}
	else if ( this->m_CurrentDurabilityState != 0.0f )
	{
		this->m_CurrentDurabilityState = 0;
		this->Convert(this->m_Type, this->m_Option1, this->m_Option2, this->m_Option3, this->m_NewOption,
			this->m_SetOption,this->m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		return true;
	}

	return false;
}

//0056A0F0 - Season 4
BYTE CItem::SearchEmptySocketSlot()
{
	for (int i = 0; i < 5; i++)
	{
		if(this->m_SocketOption[i] == 0xFE)
		{
			return 1;
		}
	}
	return 0;
}

//0056A150 - Season 4
BYTE CItem::SetSocketOptionSlot(BYTE SocketSlot, BYTE arg2, BYTE arg3)
{
	BYTE loc2 = 0;

	if( SocketSlot < 0 || SocketSlot >= 5)
	{
		return 0;
	}

	loc2 = arg3 * 50 + arg2;

	if( this->m_SocketOption[SocketSlot] != 0xFF &&
		this->m_SocketOption[SocketSlot] == 0xFE)
	{
		this->m_SocketOption[SocketSlot] = loc2;
		return 1;
	}

	return 0;
}

//0056A220 - Season 4
BYTE CItem::DeleteSocketOptionSlot(BYTE SocketSlot)
{
	if( SocketSlot <= 0 || SocketSlot >= 5)
	{
		return 0;
	}

	if( this->m_SocketOption[SocketSlot] != 0xFF &&
		this->m_SocketOption[SocketSlot] != 0xFE)
	{
		this->m_SocketOption[SocketSlot] = 0xFE;
		return 1;
	}

	return 0;
}

//0056A2D0 - Season 4 identical
void CItem::ClearSocketOption(BYTE btSocketSlotCount)
{
	if(g_SocketOption.IsActive(this) == FALSE)
	{
		return;
	}

	for(int i = 0;i< btSocketSlotCount;i++)
	{
		this->m_SocketOption[i] = 0xFE;
	}

	this->m_SocketOptionIndex = 0xFF;
}

void BufferItemtoConvert3(LPBYTE buf, int& type, BYTE& level, BYTE& op1, BYTE& op2, BYTE& op3, BYTE& dur)
{
	type = buf[0] + ((buf[3]&0x80)*2)+((buf[5]&0xF0)<<5);
	level = (buf[1]>>3) & 15;
	op1 = (buf[1]>>7) & 1;
	op2 = (buf[1]>>2) & 1;
	op3 = (buf[1] & 3 );
	dur = buf[2];

	//if ( type == ITEMGET(13, 3) ) // Dinorant
	//{
		op3 |= (buf[3] & 0x40) >> 4;
	//}
	//else
	//{
	//	if ( (buf[3] & 0x40) == 0x40 )
	//	{
	//		op3 = 4;
	//	}
	//}
}

void ItemByteConvert7(LPBYTE buf, CItem * const item, int maxitem)
{
	int n = 0;
	WORD hiWord;
	WORD loWord;

	for ( int index = 0; index < maxitem ; index++ )
	{
		buf[n] = item[index].m_Type;
		n++;
		buf[n] = 0;
		buf[n] |= item[index].m_Level * 8;
		buf[n] |= item[index].m_Option1 * 128;
		buf[n] |= item[index].m_Option2 * 4;
		buf[n] |= item[index].m_Option3;
		n++;
		buf[n] = (BYTE)item[index].m_Durability;
		n++;
		hiWord = item[index].m_Number >> 16;
		loWord = item[index].m_Number & 0xFFFF;
		buf[n] = SET_NUMBERH(hiWord);
		n++;
		buf[n] = SET_NUMBERL(hiWord);
		n++;
		buf[n] = SET_NUMBERH(loWord);
		n++;
		buf[n] = SET_NUMBERL(loWord);
		n++;
	}
}

void ItemByteConvert10(LPBYTE buf, CItem * const item, int maxitem)
{
	int n = 0;
	WORD hiWord;
	WORD loWord;
	int index;

	for (index = 0; index < maxitem ; index++ )
	{
		if ( item[index].m_Type == ITEMGET(13,19) )
		{
			if ( (item[index].m_Level < 0)? FALSE : ( item[index].m_Level > 2)? FALSE : TRUE  )
			{
				buf[n] = -1;
				buf[n+1] = -1;
				buf[n+2] = -1;
				buf[n+3] = -1;
				buf[n+4] = -1;
				buf[n+5] = -1;
				buf[n+6] = -1;
				buf[n+7] = -1;
				buf[n+8] = -1;
				buf[n+9] = -1;
				n += 16;
				continue;
			}
		}
		
		if ( item[index].m_Type <  0 )
		{
			buf[n] = -1;
			buf[n+1] = -1;
			buf[n+2] = -1;
			buf[n+3] = -1;
			buf[n+4] = -1;
			buf[n+5] = -1;
			buf[n+6] = -1;
			buf[n+7] = -1;
			buf[n+8] = -1;
			buf[n+9] = -1;
			n += 16;
		}
		else
		{
			buf[n] = (BYTE)item[index].m_Type % 256 ;
			n++;
			buf[n] = 0;
			buf[n] |= item[index].m_Level * 8;
			buf[n] |= item[index].m_Option1 * 128;
			buf[n] |= item[index].m_Option2 * 4;
			buf[n] |= item[index].m_Option3 & 3;
			n++;
			buf[n] = (BYTE)item[index].m_Durability;
			n++;
			hiWord = item[index].m_Number >> 16;
			loWord = item[index].m_Number  & 0xFFFF;
			buf[n] = SET_NUMBERH(hiWord);
			n++;
			buf[n] = SET_NUMBERL(hiWord);
			n++;
			buf[n] = SET_NUMBERH(loWord);
			n++;
			buf[n] = SET_NUMBERL(loWord);
			n++;
			buf[n] = 0;

			if ( item[index].m_Type > 255 )
			{
				buf[n] = 0x80;	// Second Type of Item
			}

			if ( item[index].m_Option3 > 3 )
			{
				buf[n] |= 0x40;	// Duration ???
			}

			buf[n] |= item[index].m_NewOption;
			n++;
			buf[n] = item[index].m_SetOption;
			n++;
			n++;
		}
	}
}

void ItemByteConvert(LPBYTE buf, CItem item)
{
	int n=0;

	memset(buf, 0, MAX_ITEM_INFO);
	buf[n] = item.m_Type & 0xFF;
	n++;
	buf[n] = 0;
	buf[n] |= item.m_Level * 8;
	buf[n] |= item.m_Option1 * 128;
	buf[n] |= item.m_Option2 * 4;
	buf[n] |= item.m_Option3 & 3;
	n++;
	buf[n] = (BYTE)item.m_Durability;
	n++;
	buf[n] = 0;
	buf[n] |= ((item.m_Type & 0x100) >> 1);

	if ( item.m_Option3 > 3 )
	{
		buf[n] |= 0x40; // item +16 option
	}

	buf[n] |= item.m_NewOption;
	n++;
	buf[n] = item.m_SetOption;
	n++;
	buf[n] |= (item.m_Type & 0x1E00 ) >> 5;

	BYTE btItemEffectFor380 = 0;
	btItemEffectFor380 = (item.m_ItemOptionEx & 0x80 ) >> 4;
	buf[n] |= btItemEffectFor380;
	n++;
	buf[n] = item.m_JewelOfHarmonyOption;

	//Season4 Socket add-on
	if(g_SocketOption.IsSocketOption(&item) == 1){buf[n] = item.m_SocketOptionIndex;}
	n++;

	buf[n] = item.m_SocketOption[0];
	n++;

	buf[n] = item.m_SocketOption[1];
	n++;

	buf[n] = item.m_SocketOption[2];
	n++;

	buf[n] = item.m_SocketOption[3];
	n++;

	buf[n] = item.m_SocketOption[4];
}

void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption, BYTE JewelOfHarmonyOption, BYTE ItemEffectEx, BYTE SocketOption[5], BYTE SocketIndex)
{
	memset(buf, 0, MAX_ITEM_INFO);
	int n = 0;

	buf[n] = type & 0xFF;
	n++;
	buf[n] = 0;
	buf[n] |= level * 8;
	buf[n] |= Option1 * 128;
	buf[n] |= Option2 * 4;
	buf[n] |= Option3 & 3;
	n++;
	buf[n] = dur;
	n++;
	buf[n] = 0;
	buf[n] |= ((type& 0x100) >> 1);

	if ( Option3 > 3 )
	{
		buf[n] |= 0x40;
	}

	buf[n] |= Noption;
	n++;
	buf[n] = SetOption;
	n++;
	buf[n] |= (type & 0x1E00 ) >> 5;

	BYTE btItemEffectFor380 = 0;
	btItemEffectFor380 = (ItemEffectEx  & 0x80 ) >> 4;
	buf[n] |= btItemEffectFor380;
	n++;
	buf[n] = JewelOfHarmonyOption;

	//Season4 add-on (wz bugged -.-)
	if(SocketOption != NULL)
	{
		buf[n] = SocketIndex;
		n++;
		buf[n] = SocketOption[0];
		n++;
		buf[n] = SocketOption[1];
		n++;
		buf[n] = SocketOption[2];
		n++;
		buf[n] = SocketOption[3];
		n++;
		buf[n] = SocketOption[4];
	}
	else
	{
		n++; //wz fixed here -.-
		buf[n] = 0xFF;
		n++;
		buf[n] = 0xFF;
		n++;
		buf[n] = 0xFF;
		n++;
		buf[n] = 0xFF;
		n++;
		buf[n] = 0xFF;
	}
}

void ItemByteConvert16(LPBYTE buf, CItem * const item , int maxitem)
{
	int n=0;
	WORD hiWord, loWord;

	for (int index=0; index < maxitem ;index++)
	{
		if ( item[index].m_Type == ITEMGET(13,19) )
		{
			if ( CHECK_LIMIT(item[index].m_Level, 3) != FALSE )
			{
				buf[n+0]=-1;
				buf[n+1]=-1;
				buf[n+2]=-1;
				buf[n+3]=-1;
				buf[n+4]=-1;
				buf[n+5]=-1;
				buf[n+6]=-1;
				buf[n+7]=-1;
				buf[n+8]=-1;
				buf[n+9]=-1;
				buf[n+10]=-1;
				buf[n+11]=-1;
				buf[n+12]=-1;
				buf[n+13]=-1;
				buf[n+14]=-1;
				buf[n+15]=-1;
				n+=16;

				continue;
			}
		}

		if ( item[index].m_Type == ITEMGET(14,64) ) //Season 2.5 Illusion Torch add-on
		{
			buf[n] = -1;
			buf[n+1]= -1;
			buf[n+2]= -1;
			buf[n+3]= -1;
			buf[n+4]= -1;
			buf[n+5]= -1;
			buf[n+6]= -1;
			buf[n+7]= -1;
			buf[n+8]= -1;
			buf[n+9]= -1;
			buf[n+10]=-1;
			buf[n+11]=-1;
			buf[n+12]=-1;
			buf[n+13]=-1;
			buf[n+14]=-1;
			buf[n+15]=-1;
			n += 16;
			continue;
		}

		if ( item[index].m_Type < ITEMGET(0,0) )
		{
			buf[n+0]=-1;
			buf[n+1]=-1;
			buf[n+2]=-1;
			buf[n+3]=-1;
			buf[n+4]=-1;
			buf[n+5]=-1;
			buf[n+6]=-1;
			buf[n+7]=-1;
			buf[n+8]=-1;
			buf[n+9]=-1;
			buf[n+10]=-1;
			buf[n+11]=-1;
			buf[n+12]=-1;
			buf[n+13]=-1;
			buf[n+14]=-1;
			buf[n+15]=-1;
			n+=16;
		}
		else
		{
			memset(buf+n, 0, 16);

			buf[n] = (BYTE)item[index].m_Type % 256;
			n++;
			buf[n]=0;
			buf[n] |= item[index].m_Level * 8;
			buf[n] |= item[index].m_Option1 * 128;
			buf[n] |= item[index].m_Option2 * 4;
			buf[n] |= item[index].m_Option3 & 3;
			n++;
			buf[n] = (BYTE)item[index].m_Durability;
			n++;
			hiWord = item[index].m_Number >> 16;
			loWord = item[index].m_Number  & 0xFFFF;
			buf[n] = SET_NUMBERH(hiWord);
			n++;
			buf[n] = SET_NUMBERL(hiWord);
			n++;
			buf[n] = SET_NUMBERH(loWord);
			n++;
			buf[n] = SET_NUMBERL(loWord);
			n++;
			buf[n] = 0;
			BYTE btItemType=0;
			btItemType |= (item[index].m_Type & 0x1E00 ) >> 5;
			buf[n] |= ((item[index].m_Type & 0x100) >> 1);

			if ( item[index].m_Option3 > 3 )
			{
				buf[n] |= 0x40; // item +16 option
			}

			buf[n] |= item[index].m_NewOption;
			n++;
			buf[n] = item[index].m_SetOption;
			n++;
			buf[n] = 0;
			buf[n] |= btItemType;
			BYTE btItemEffectFor380 = 0;
			btItemEffectFor380 = (item[index].m_ItemOptionEx & 0x80 ) >> 4;
			buf[n] |= btItemEffectFor380;
			n++;
			
			if ( item[index].m_JewelOfHarmonyOption == 0xFF )
				item[index].m_JewelOfHarmonyOption = 0;

			buf[n] = item[index].m_JewelOfHarmonyOption;

			//Season4 add-on
			if(g_SocketOption.IsSocketOption(&item[index]) == 1){buf[n] = item[index].m_SocketOptionIndex;}
			n++;
			buf[n] = item[index].m_SocketOption[0];
			n++;
			buf[n] = item[index].m_SocketOption[1];
			n++;
			buf[n] = item[index].m_SocketOption[2];
			n++;
			buf[n] = item[index].m_SocketOption[3];
			n++;
			buf[n] = item[index].m_SocketOption[4];
			n++;
		}
	}
}

int ItemGetNumberMake(int type, int index)
{
	int make;

	make = type*MAX_SUBTYPE_ITEMS + index;

	if (ItemAttribute[make].Width < 1 ||  ItemAttribute[make].Height < 1)
	{
		return -1;
	}
	return make;
}

void ItemGetSize(int index, int & width, int & height)
{
	width = ItemAttribute[index].Width;
	height = ItemAttribute[index].Height;
}

BOOL HasItemDurability(int index)
{
	if ( ItemAttribute[index].Durability == 0 && ItemAttribute[index].MagicDurability == 0)
	{
		return FALSE; 
	}
	
	return TRUE;
}

int ItemGetDurability(int index, int itemLevel, int ExcellentItem, int SetItem)
{

	if ( index == ITEMGET(14,21) && itemLevel == 3 )	// Mark Lord
		itemLevel=0;
	
	if ( index == ITEMGET(14,29) )
		return 1;

	if ( index == ITEMGET(14,100) ) //season 4.5 lucky coin add-on
		return 1;

	int dur=0;

	if ( itemLevel < 5)
	{
		dur= ItemAttribute[index].Durability + itemLevel;
	}
	else if ( itemLevel >= 5 )
	{
		if ( itemLevel == 10 )
		{
			dur=ItemAttribute[index].Durability + itemLevel*2-3;
		}
		else if (itemLevel == 11 )
		{
			dur=ItemAttribute[index].Durability + itemLevel*2-1;
		}
		else if (itemLevel == 12 )
		{
			dur=ItemAttribute[index].Durability + itemLevel*2+2;
		}
		else if (itemLevel == 13 )
		{
			dur=ItemAttribute[index].Durability + itemLevel*2+6;
		}
		else
		{
			dur=ItemAttribute[index].Durability + itemLevel*2-4;
		}
	}
	
	if( index == ITEMGET(13,51) ) //Season 2.5 Illusion Temple Blood Scroll Ticket
	{
		dur = 1;
	}
	
	if ( (index < ITEMGET(12,3) || index > ITEMGET(12,6) ) &&
		  index != ITEMGET(0,19) &&
		  index != ITEMGET(4,18) &&
		  index != ITEMGET(5,10) &&
		  index != ITEMGET(2,13) &&
		  index != ITEMGET(13,30) &&
		  index != ITEMGET(12,36) &&
		  index != ITEMGET(12,37) &&
		  index != ITEMGET(12,38) &&
		  index != ITEMGET(12,39) &&
		  index != ITEMGET(12,40) &&
		  index != ITEMGET(12,41) &&
		  index != ITEMGET(12,42) &&
		  index != ITEMGET(12,43) &&
		  //Custom Wings4
		  index != ITEMGET(12,180) &&
		  index != ITEMGET(12,181) &&
		  index != ITEMGET(12,182) &&
		  index != ITEMGET(12,183) &&
		  index != ITEMGET(12,184) &&
		  index != ITEMGET(12,185) &&
		  index != ITEMGET(12,186) &&
		  index != ITEMGET(12,187) &&
		  index != ITEMGET(12,188) &&
#ifdef _WINGS_5LVL_
		  index != ITEMGET(12,189) &&
		  index != ITEMGET(12,190) &&
		  index != ITEMGET(12,191) &&
		  index != ITEMGET(12,192) &&
		  index != ITEMGET(12,193) &&
		  index != ITEMGET(12,194)
#else
		  index != ITEMGET(12,188) 
#endif		  
		  )
	{
		if ( SetItem != 0 )
			dur +=20;
		else if ( ExcellentItem != 0 ) // Prevent duple if items
			dur +=15;
	}

	if ( dur > 255 )
		dur = 255;

	return dur;
}

int ItemGetAttackDurability(int index)
{
	return ItemAttribute[index].AttackDur;
}

int ItemGetDefenseDurability(int index)
{
	return ItemAttribute[index].DefenceDur;
}

float GetRepairItemRate(int index)
{
	return ItemAttribute[index].RepaireMoneyRate;
}

float GetAllRepairItemRate(int index)
{
	return ItemAttribute[index].AllRepaireMoneyRate;
}

void CalRepairRate( int itemtype, int itemsubtype, LPITEM_ATTRIBUTE p)
{
	p->RepaireMoneyRate = (float)0.1;
	p->AllRepaireMoneyRate = (float)0.4;
}

BOOL OpenItemScript(char* FileName)
{
	int loop_count;
	int n;
	int Token;

	SMDFile = fopen(FileName, "r");

	if ( SMDFile == 0 )
	{
		return FALSE;
	}

	memset ( ItemAttribute, 0, sizeof(ItemAttribute) );
	
	for ( n=0;n<MAX_ITEMS;n++)
	{
		ItemAttribute[n].Level = -1;
		ItemAttribute[n].RepaireMoneyRate  = 0;
		ItemAttribute[n].AllRepaireMoneyRate  = 0;
	}

	
	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}
		if ( Token == 1 )
		{
			int ItemType;

			ItemType = (int)TokenNumber;
			loop_count = 0;
			while ( true )
			{
				int ItemSubType;
				LPITEM_ATTRIBUTE p;
				
				Token = GetToken();
				ItemSubType = (int)TokenNumber;

				if ( ItemType >= 0 && ItemType < MAX_TYPE_ITEMS )
				{
					if ( g_MaxItemIndexOfEachItemType[ItemType] <= ItemSubType )
					{
						g_MaxItemIndexOfEachItemType[ItemType] = ItemSubType;
					}
				}

				
				if ( Token == 0 )
				{
					if ( strcmp("end", TokenString ) == 0 )
					{
						break;
					}
				}
					
				p = &ItemAttribute[ItemType*MAX_SUBTYPE_ITEMS + ItemSubType];

				Token = GetToken();
				p->ItemSlot = (int)TokenNumber;

				Token = GetToken();
				p->SkillType = (int)TokenNumber;

				Token = GetToken();
				p->Width  = (BYTE)TokenNumber;

				Token = GetToken();
				p->Height  = (BYTE)TokenNumber;

				Token = GetToken();
				p->Serial = (char)TokenNumber;

				Token = GetToken();
				p->OptionFlag = (BYTE)TokenNumber;

				Token = GetToken();
				p->MondownFlag = (BYTE)TokenNumber;

				Token = GetToken();
				strcpy(&p->Name[0], TokenString );

				if ( ItemType >= 0 && ItemType <= 5 )
				{
					Token = GetToken();
					p->Level = (BYTE)TokenNumber;

					Token = GetToken();
					p->DamageMin = (BYTE)TokenNumber;

					Token = GetToken();
					p->DamageMax = (BYTE)TokenNumber;

					Token = GetToken();
					p->AttackSpeed = (BYTE)TokenNumber;

					Token = GetToken();
					p->Durability = (BYTE)TokenNumber;

					Token = GetToken();
					p->MagicDurability = (BYTE)TokenNumber;

					Token = GetToken();
					p->MagicPW = (int)TokenNumber;

					Token = GetToken();
					p->RequireLevel = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireStrength = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireDexterity = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireEnergy = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireVitality = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireLeadership = (int)TokenNumber;

					if ( p->Width  >= 2)
					{
						p->TwoHand = TRUE;
					}

					(BYTE)p->Durability += (BYTE)p->MagicDurability;
				}

				if ( ItemType >= 6 && ItemType <= 11 )
				{
					Token = GetToken();
					p->Level = (BYTE)TokenNumber;
					
					if ( ItemType == 6 )
					{

						Token = GetToken();
						p->Defense = (BYTE)TokenNumber;

						Token = GetToken();
						p->SuccessfulBlocking  = (BYTE)TokenNumber;

					}
					else if ( ItemType >= 7 && ItemType <= 9 )
					{

						Token = GetToken();
						p->Defense  = (BYTE)TokenNumber;

						Token = GetToken();
						p->MagicDefense = (BYTE)TokenNumber;
					}
					else if ( ItemType == 10 )
					{
						Token = GetToken();
						p->Defense = (BYTE)TokenNumber;

						Token = GetToken();
						p->AttackSpeed = (BYTE)TokenNumber;
					}
					else if ( ItemType == 11 )
					{
						Token = GetToken();
						p->Defense  = (BYTE)TokenNumber;

						Token = GetToken();
						p->WalkSpeed = (BYTE)TokenNumber;
					}
					
					Token = GetToken();
					p->Durability = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireLevel = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireStrength = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireDexterity = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireEnergy = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireVitality = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireLeadership = (int)TokenNumber;
				}

				if ( ItemType == 13 )
				{
					Token = GetToken();
					p->Level = (BYTE)TokenNumber;

					Token = GetToken();
					p->Durability = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[0] = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[1] = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[2] = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[3] = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[4] = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[5] = (BYTE)TokenNumber;

					Token = GetToken();
					p->Resistance[6] = (BYTE)TokenNumber;

					p->ResistanceType = -1;
					
					int n;

					for (n=0;n<MAX_ITEM_SPECIAL_ATTRIBUTE-1;n++)
					{
						if ( (p->Resistance[n]) != 0 )
						{
							p->ResistanceType=n;
						}
					}

					p->RequireLevel = p->Level ;
					
				}

				if ( ItemType == 14 )
				{
					Token = GetToken();
					p->Value = (WORD)TokenNumber;

					Token = GetToken();
					p->Level = (BYTE)TokenNumber;

					p->Durability = 1;
				}

				if ( ItemType == 12 )
				{
					Token = GetToken();
					p->Level = (BYTE)TokenNumber;

					Token = GetToken();
					p->Defense = (BYTE)TokenNumber;

					Token = GetToken();
					p->Durability = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireLevel = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireEnergy = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireStrength = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireDexterity = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireLeadership = (int)TokenNumber;

					Token = GetToken();
					p->BuyMoney = (int)TokenNumber;

				}
				
				if ( ItemType == 15 )
				{

					Token = GetToken();
					p->Level = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireLevel  = (WORD)TokenNumber;

					Token = GetToken();
					p->RequireEnergy  = (WORD)TokenNumber;

					Token = GetToken();
					p->BuyMoney  = (int)TokenNumber;

					p->DamageMin = p->Level;
					p->DamageMax = p->Level + p->Level/2; 
				}

				if ( ItemType <= 11 || ItemType == 13)
				{
					Token = GetToken();
				}

				p->SetAttr = (BYTE)TokenNumber;

				if ( ItemType <= 13 || ItemType == 15 )
				{

					Token = GetToken();
					p->RequireClass[0]  = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireClass[1]  = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireClass[2]  = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireClass[3]  = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireClass[4]  = (BYTE)TokenNumber;

					Token = GetToken();
					p->RequireClass[5]  = (BYTE)TokenNumber;
				}

				CalRepairRate(ItemType, ItemSubType, p);

				p->HaveItemInfo = TRUE;

				loop_count++;

				if ( loop_count > MAX_SUBTYPE_ITEMS )
				{
					MsgBox("Error : Item Data fail. (LoopCount:%d) Item Type:%d Index %d", loop_count, ItemType, ItemSubType);
					break;
				}
			}

			if ( loop_count > MAX_SUBTYPE_ITEMS )
			{
				break;
			}
			
		}


	}
	
	fclose(SMDFile);
	return TRUE;
}

BOOL OpenItemNameScript(char* FileName)
{
	
	int Token;

	SMDFile = fopen(FileName, "r");

	if (SMDFile == 0 )
	{
		return FALSE;
	}

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}
		if ( Token == 1 )
		{
			int ItemType;

			ItemType = (int)TokenNumber;

			while ( true )
			{
				int ItemSubType;
				LPITEM_ATTRIBUTE p;

				Token = GetToken();
				ItemSubType = (int)TokenNumber;

				if ( Token == 0 )
				{
					if ( strcmp("end", TokenString ) == 0 )
					{
						break;
					}
				}
					
				p = &ItemAttribute[ItemType*MAX_SUBTYPE_ITEMS + ItemSubType];

				Token = GetToken();
				strcpy(&p->Name[0], TokenString );

				
			}
		}
	}
	fclose(SMDFile);
	return TRUE;
}

BOOL OpenItemScript(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int n;
	int loop_count;

	int Token;

	WzMemScript.SetBuffer(Buffer, iSize);

	memset ( ItemAttribute, 0, sizeof(ItemAttribute) );
	
	for ( n=0;n<MAX_ITEMS;n++)
	{
		ItemAttribute[n].Level = -1;
		ItemAttribute[n].RepaireMoneyRate  = 0;
		ItemAttribute[n].AllRepaireMoneyRate  = 0;
	}

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}
		
		if ( Token == 1 )
		{
			int ItemType;

			ItemType = WzMemScript.GetNumber();
			loop_count = 0;
			while ( true )
			{
				int ItemSubType;
				LPITEM_ATTRIBUTE p;

				
				Token = WzMemScript.GetToken();
				ItemSubType = WzMemScript.GetNumber();

				if ( ItemType >= 0 && ItemType < MAX_TYPE_ITEMS )
				{
					if ( g_MaxItemIndexOfEachItemType[ItemType] <= ItemSubType )
					{
						g_MaxItemIndexOfEachItemType[ItemType] = ItemSubType;
					}
				}
				
				if ( Token == 0 )
				{
					if ( strcmp("end", WzMemScript.GetString() ) == 0 )
					{
						break;
					}
				}
					
				p = &ItemAttribute[ItemType*MAX_SUBTYPE_ITEMS + ItemSubType];

				Token = WzMemScript.GetToken();
				p->ItemSlot = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				p->SkillType = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				p->Width  = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				p->Height  = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				p->Serial = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				p->OptionFlag = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				p->MondownFlag = WzMemScript.GetNumber();

				Token = WzMemScript.GetToken();
				strcpy(&p->Name[0], WzMemScript.GetString() );

				if ( ItemType >= 0 && ItemType <= 5 )
				{
					Token = WzMemScript.GetToken();
					p->Level = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->DamageMin = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->DamageMax = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->AttackSpeed = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Durability = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->MagicDurability = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->MagicPW = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLevel = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireStrength = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireDexterity = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireEnergy = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireVitality = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLeadership = WzMemScript.GetNumber();

					if ( p->Width  >= 2)
					{
						p->TwoHand = TRUE;
					}

					(BYTE)p->Durability += (BYTE)p->MagicDurability;
				}

				if ( ItemType >= 6 && ItemType <= 11 )
				{
					Token = WzMemScript.GetToken();
					p->Level = WzMemScript.GetNumber();
					
					if ( ItemType == 6 )
					{

						Token = WzMemScript.GetToken();
						p->Defense = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						p->SuccessfulBlocking  = WzMemScript.GetNumber();

					}
					else if ( ItemType >= 7 && ItemType <= 9 )
					{

						Token = WzMemScript.GetToken();
						p->Defense  = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						p->MagicDefense = WzMemScript.GetNumber();
					}
					else if ( ItemType == 10 )
					{
						Token = WzMemScript.GetToken();
						p->Defense = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						p->AttackSpeed = WzMemScript.GetNumber();
					}
					else if ( ItemType == 11 )
					{
						Token = WzMemScript.GetToken();
						p->Defense  = WzMemScript.GetNumber();

						Token = WzMemScript.GetToken();
						p->WalkSpeed = WzMemScript.GetNumber();
					}
					
					Token = WzMemScript.GetToken();
					p->Durability = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLevel = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireStrength = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireDexterity = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireEnergy = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireVitality = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLeadership = WzMemScript.GetNumber();
				}

				if ( ItemType == 13 )
				{
					Token = WzMemScript.GetToken();
					p->Level = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Durability = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[0] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[1] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[2] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[3] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[4] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[5] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Resistance[6] = WzMemScript.GetNumber();

					p->ResistanceType = -1;
					
					int n;

					for (n=0;n<MAX_ITEM_SPECIAL_ATTRIBUTE-1;n++)
					{
						if ( (p->Resistance[n]) != 0 )
						{
							p->ResistanceType=n;
						}
					}

					p->RequireLevel = p->Level ;
					
				}

				if ( ItemType == 14 )
				{
					Token = WzMemScript.GetToken();
					p->Value = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Level = WzMemScript.GetNumber();

					p->Durability = 1;
				}

				if ( ItemType == 12 )
				{
					Token = WzMemScript.GetToken();
					p->Level = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Defense = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->Durability = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLevel = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireEnergy = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireStrength = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireDexterity = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLeadership = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->BuyMoney = WzMemScript.GetNumber();

				}
				
				if ( ItemType == 15 )
				{

					Token = WzMemScript.GetToken();
					p->Level = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireLevel  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireEnergy  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->BuyMoney  = WzMemScript.GetNumber();

					p->DamageMin = p->Level;
					p->DamageMax = p->Level + p->Level/2; 
				}

				if ( ItemType <= 11 || ItemType == 13)
				{
					Token = WzMemScript.GetToken();
				}

				p->SetAttr = WzMemScript.GetNumber();

				if ( ItemType <= 13 || ItemType == 15 )
				{

					Token = WzMemScript.GetToken();
					p->RequireClass[0]  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireClass[1]  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireClass[2]  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireClass[3]  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireClass[4]  = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken();
					p->RequireClass[5]  = WzMemScript.GetNumber();
				}

				CalRepairRate(ItemType, ItemSubType, p);

				p->HaveItemInfo = TRUE;

				loop_count++;

				if ( loop_count > MAX_SUBTYPE_ITEMS )
				{
					MsgBox("Error : Item Data fail. (LoopCount:%d) Item Type:%d Index %d", loop_count, ItemType, ItemSubType);
					break;
				}
			}
		}
	}
	
	return TRUE;

}

BOOL OpenItemNameScript(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int Token;

	WzMemScript.SetBuffer(Buffer, iSize);

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			int ItemType;

			ItemType = WzMemScript.GetNumber();

			while ( true )
			{
				int ItemSubType;
				LPITEM_ATTRIBUTE p;

				Token = WzMemScript.GetToken();
				ItemSubType = WzMemScript.GetNumber();
				
				if ( Token == 0 )
				{
					if ( strcmp("end", WzMemScript.GetString() ) == 0 )
					{
						break;
					}
				}
					
				p = &ItemAttribute[ItemType*MAX_SUBTYPE_ITEMS + ItemSubType];

				Token = WzMemScript.GetToken();
				strcpy(&p->Name[0], WzMemScript.GetString() );

				
			}
		}
	}
	return TRUE;
}

int zzzItemLevel(int type, int index, int level)
{
	int item_num = (type*MAX_SUBTYPE_ITEMS)+index ;

	if (level < 0 )
	{
		level = 0;
	}
	
	if ( ItemAttribute[item_num].Level == (BYTE)-1 )
	{
		return 0;
	}

	if ( ItemAttribute[item_num].Level == 0 )
	{
		return 0;
	}

	if ( ItemAttribute[item_num].Level < level )
	{
		return 1;
	}

	return 0;
}

int GetLevelItem(int type, int index, int level)
{
	int item_num;
	int itemlevel;

	if ( level < 0 )
	{
		level = 0;
	}

	item_num = (type * MAX_SUBTYPE_ITEMS) + index;

	if (ItemAttribute[item_num].MondownFlag  == 0)
	{
		return -1;
	}

	if ( ItemAttribute[item_num].Level == 0xFF )
	{
		return -1;
	}

	if ( ItemAttribute[item_num].Level == 0 )
	{
		return -1;
	}

	if ( type == 14 )
	{
		itemlevel = ItemAttribute[item_num].Level;

		if ( index == 15 )
		{
			return -1;
		}

		if ( itemlevel >= (level-8) )
		{
			if ( itemlevel <= level )
			{
				return 0;
			}
		}

		return -1;
	}

	if ( type == 13 && index == 10  )
	{
		int ilevel;

		if ( (rand()%10) == 0 )
		{
			ilevel = 0;

			if ( level < 0 )
			{
				level = 0;
			}

			ilevel= level/10;

			if ( ilevel > 0 )
			{
				ilevel--;
			}

			if ( ilevel > 5)
			{
				ilevel = 5;
			}

			return ilevel;
		}

		return -1;
	}

	if ( type == 12 && index ==  11 )
	{
		int ilevel;

		if ( (rand()%10) == 0 )
		{
			ilevel = 0;

			if ( level < 0 )
			{
				level = 0;
			}

			ilevel= level/10;

			if ( ilevel > 0 )
			{
				ilevel--;
			}

			if ( ilevel > 6)
			{
				ilevel = 6;
			}

			return ilevel;
		}

		return -1;
	}	

	itemlevel = ItemAttribute[item_num].Level;
	
	if ( itemlevel >= level - 18 && itemlevel <= level)
	{
		if ( type == 15 )
		{
			return 0;
		}

		itemlevel = (level - itemlevel)/3;

		if ( type == 13 )
		{
			if ( index == 8 || index == 9 || index == 12 || index == 13 || index == 20 || index == 21 || index == 22 || index == 23 || index == 24 || index == 25 || index == 26 || index == 27 || index == 28 )
			{
				if ( itemlevel > 4 )
				{
					itemlevel=4;
				}
			}
		}

		return itemlevel;
		
	}
	return -1;
}

int GetSerialItem(int type)
{
	int item_num = type;

	if ( ItemAttribute[item_num].Level == 0xFF )
	{
		return -1;
	}
	if ( ItemAttribute[item_num].Serial  == 0 )
	{
		return 0;
	}
	return 1;
}

int IsItem(int item_num)
{
	if ( item_num < 0 || item_num >= MAX_ITEMS )
	{
		return 0;
	}

	return ItemAttribute[item_num].HaveItemInfo;
}

LPITEM_ATTRIBUTE GetItemAttr(int item_num)
{
	if ( item_num < 0 || item_num >= MAX_ITEMS )
	{
		return NULL;
	}

	return &ItemAttribute[item_num];
}
