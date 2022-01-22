#include "StdAfx.h"
#include "user.h"
#include "NewJewels.h"
#include "Configs.h"
#include "Functions.h"
#include "..\common\SetItemOption.h"
#include "logproc.h"

#ifdef _NEW_JEWELS_2_

cNewJewels gNewJewels;

void cNewJewels::Load()
{

	this->Enable  = GetPrivateProfileInt("Common","Enable",0,NewJewels_DIR);


	this->JewelOfExellentType = GetPrivateProfileInt("Common","JewelOfExellentType",0,NewJewels_DIR);
	this->JewelOfExellentIndex = GetPrivateProfileInt("Common","JewelOfExellentIndex",0,NewJewels_DIR);
	this->JewelOfExellentEnable = GetPrivateProfileInt("Common","JewelOfExellentEnable",0,NewJewels_DIR);
	this->JewelOfExellentRate = GetPrivateProfileInt("Common","JewelOfExellentRate",0,NewJewels_DIR);
	this->JewelOfExellentMaxOpt = GetPrivateProfileInt("Common","JewelOfExellentMaxOpt",0,NewJewels_DIR);

	this->JewelOfMisticType = GetPrivateProfileInt("Common","JewelOfMisticType",0,NewJewels_DIR);
	this->JewelOfMisticIndex = GetPrivateProfileInt("Common","JewelOfMisticIndex",0,NewJewels_DIR);
	this->JewelOfMisticEnable = GetPrivateProfileInt("Common","JewelOfMisticEnable",0,NewJewels_DIR);
	this->JewelOfMisticMaxLvl = GetPrivateProfileInt("Common","JewelOfMisticMaxLvl",0,NewJewels_DIR);
	this->JewelOfMisticMinLvl = GetPrivateProfileInt("Common","JewelOfMisticMinLvl",0,NewJewels_DIR);
	this->JewelOfMisticRate = GetPrivateProfileInt("Common","JewelOfMisticRate",0,NewJewels_DIR);

	this->JewelOfLuckType = GetPrivateProfileInt("Common","JewelOfLuckType",0,NewJewels_DIR);
	this->JewelOfLuckIndex = GetPrivateProfileInt("Common","JewelOfLuckIndex",0,NewJewels_DIR);
	this->JewelOfLuckEnable = GetPrivateProfileInt("Common","JewelOfLuckEnable",0,NewJewels_DIR);
	this->JewelOfLuckEnable = GetPrivateProfileInt("Common","JewelOfLuckEnable",0,NewJewels_DIR);
	this->JewelOfLuckRate = GetPrivateProfileInt("Common","JewelOfLuckRate",0,NewJewels_DIR);

	this->JewelOfSkillType = GetPrivateProfileInt("Common","JewelOfSkillType",0,NewJewels_DIR);
	this->JewelOfSkillIndex = GetPrivateProfileInt("Common","JewelOfSkillIndex",0,NewJewels_DIR);
	this->JewelOfSkillEnable = GetPrivateProfileInt("Common","JewelOfSkillEnable",0,NewJewels_DIR);
	this->JewelOfSkillRate = GetPrivateProfileInt("Common","JewelOfSkillRate",0,NewJewels_DIR);

	this->JewelOfLevelType = GetPrivateProfileInt("Common","JewelOfLevelType",0,NewJewels_DIR);
	this->JewelOfLevelIndex = GetPrivateProfileInt("Common","JewelOfLevelIndex",0,NewJewels_DIR);
	this->JewelOfLevelEnable = GetPrivateProfileInt("Common","JewelOfLevelEnable",0,NewJewels_DIR);
	this->JewelOfLevelMax = GetPrivateProfileInt("Common","JewelOfLevelMax",0,NewJewels_DIR);
	this->JewelOfLevelMin = GetPrivateProfileInt("Common","JewelOfLevelMin",0,NewJewels_DIR);
	this->JewelOfLevelRate = GetPrivateProfileInt("Common","JewelOfLevelRate",0,NewJewels_DIR);

	this->JewelOfEvalutionType = GetPrivateProfileInt("Common","JewelOfEvalutionType",0,NewJewels_DIR); 
	this->JewelOfEvalutionIndex = GetPrivateProfileInt("Common","JewelOfEvalutionIndex",0,NewJewels_DIR); 
	this->JewelOfEvalutionEnable = GetPrivateProfileInt("Common","JewelOfEvalutionEnable",0,NewJewels_DIR); 
	this->JewelOfEvalutionRate = GetPrivateProfileInt("Common","JewelOfEvalutionRate",0,NewJewels_DIR);

	this->JewelOfAncentType = GetPrivateProfileInt("Common","JewelOfAncentType",0,NewJewels_DIR); 
	this->JewelOfAncentIndex = GetPrivateProfileInt("Common","JewelOfAncentIndex",0,NewJewels_DIR); 
	this->JewelOfAncentEnable = GetPrivateProfileInt("Common","JewelOfAncentEnable",0,NewJewels_DIR); 
	this->JewelOfAncentRate = GetPrivateProfileInt("Common","JewelOfAncentRate",0,NewJewels_DIR); 

	this->JewelOfOptionType = GetPrivateProfileInt("Common","JewelOfOptionType",0,NewJewels_DIR); 
	this->JewelOfOptionIndex = GetPrivateProfileInt("Common","JewelOfOptionIndex",0,NewJewels_DIR); 
	this->JewelOfOptionEnable = GetPrivateProfileInt("Common","JewelOfOptionEnable",0,NewJewels_DIR); 
	this->JewelOfOptionRate = GetPrivateProfileInt("Common","JewelOfOptionRate",0,NewJewels_DIR); 

}

bool cNewJewels::IsAccessory(int ItemID)
{
	if(		ItemID >= ITEMGET(13, 21) && ItemID <= ITEMGET(13, 29)
		||	ItemID == ITEMGET(13, 8)
		||	ItemID == ITEMGET(13, 9)
		||	ItemID == ITEMGET(13, 12)
		||	ItemID == ITEMGET(13, 13) )
	{
		return true;
	}
	// ----
	return false;

}

BYTE cNewJewels::GetExcUnusedOption(BYTE ExcellentOption)
{
	int arrayopt[6]	= { 0, 0, 0, 0, 0, 0};
	int num			= 32;
	int amountopt	= 0;
	int added		= 0;
	// ----
	for( int i = 5; i >= 0; i-- )
	{
		if( ExcellentOption >= num )
		{
			arrayopt[i] = 1;
			amountopt++;
			ExcellentOption -= num;
		}
		num = num / 2;
	}
	// ----
	int randomopt = rand()%(6-amountopt)+1;
	amountopt = 0;

	for(int i=0; i<6; i++)
	{
		if(!arrayopt[i])
		{ 
			amountopt++;
			if( amountopt == randomopt )
			{
				arrayopt[i] = 1;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	num = 1; 
	ExcellentOption = 0;

	for (int i=0 ; i<6; i++)
	{
		if (arrayopt[i])
		{
			ExcellentOption += num;
		}
		num = num * 2;
	}

	return ExcellentOption;
}

bool cNewJewels::CheckJewel(int iType)
{
	if(iType == ITEMGET(this->JewelOfExellentType,this->JewelOfExellentIndex) && this->JewelOfExellentEnable) return true;
	else if(iType == ITEMGET(this->JewelOfMisticType,this->JewelOfMisticIndex) && this->JewelOfMisticEnable) return true;
	else if(iType == ITEMGET(this->JewelOfLuckType,this->JewelOfLuckIndex) && this->JewelOfLuckEnable) return true;
	else if(iType == ITEMGET(this->JewelOfSkillType,this->JewelOfSkillIndex) && this->JewelOfSkillEnable) return true;
	else if(iType == ITEMGET(this->JewelOfLevelType,this->JewelOfLevelIndex) && this->JewelOfLevelEnable) return true;
	else if(iType == ITEMGET(this->JewelOfEvalutionType,this->JewelOfEvalutionIndex) && this->JewelOfEvalutionEnable) return true;
	else if(iType == ITEMGET(this->JewelOfAncentType,this->JewelOfAncentIndex) && this->JewelOfAncentEnable) return true;
	else if(iType == ITEMGET(this->JewelOfOptionType,this->JewelOfOptionIndex) && this->JewelOfOptionEnable) return true;
	else return false;
}

void cNewJewels::JewelMain(LPOBJ lpObj, int source, int target)
{
	if( source < 0 || source > MAIN_INVENTORY_SIZE - 1 )
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}
	// ----
	if( target < 0 || target > MAIN_INVENTORY_SIZE - 1 )
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}
	// ----
	if( !lpObj->pInventory[source].IsItem() || !lpObj->pInventory[target].IsItem() )
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}
#ifdef LUCKYITEM
	if(g_LuckyItemManager.IsLuckyItemEquipment(lpObj->pInventory[target].m_Type))
	{
		return;
	}
#endif

	int JewelIndex = lpObj->pInventory[source].m_Type;
	int TargetIndex = lpObj->pInventory[target].m_Type;
	int TargetLevel = lpObj->pInventory[target].m_Level;

	if(TargetLevel > 13)
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}

	srand(time(NULL));

	int iRate = rand()%100;

	bool JewelAdded = false;
//*************************************
//	Jewel Of Exellent
//*************************************
	if( JewelIndex == ITEMGET(this->JewelOfExellentType,this->JewelOfExellentIndex) )
	{
		if( this->JewelOfExellentRate > iRate )
		{
			if( lpObj->pInventory[target].m_Type < ITEMGET(12,0) )
			{
				if( lpObj->pInventory[target].m_NewOption > 0)
				{
					if(this->JewelOfExellentMaxOpt > GetExcOptionCount(lpObj->pInventory[target].m_NewOption) )
					{
						BYTE NewOption = this->GetExcUnusedOption(lpObj->pInventory[target].m_NewOption);
						lpObj->pInventory[target].m_NewOption = NewOption;
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
					}
					else
					{
						MsgOutput(lpObj->m_Index,"[Jewels] Max %d Exellent Option",this->JewelOfExellentMaxOpt);
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Need Item Exellent Status");
				}
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Mistic
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfMisticType,this->JewelOfMisticIndex) ) //
	{
		if( this->JewelOfMisticRate > iRate )
		{
			if(this->IsAccessory(TargetIndex) == true )
			{
				if(TargetLevel >= this->JewelOfMisticMinLvl ) 
				{
					if(TargetLevel <= this->JewelOfMisticMaxLvl)
					{
						lpObj->pInventory[target].m_Level++;
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
					}
					else
					{
						MsgOutput(lpObj->m_Index,"[Jewels] Max Item Level %d",this->JewelOfMisticMaxLvl);
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Min Item Level %d",this->JewelOfMisticMinLvl);
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels] Need Item Accessory");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Luck
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfLuckType,this->JewelOfLuckIndex) ) 
	{
		if( this->JewelOfLuckRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0))
			{
				if(lpObj->pInventory[target].m_Option2 == 0)
				{
					lpObj->pInventory[target].m_Option2++;
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Is Set to Luck");
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels] No use item luck");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Skill
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfSkillType,this->JewelOfSkillIndex) )
	{
		if( this->JewelOfSkillRate > iRate )
		{
			if(ItemAttribute[lpObj->pInventory[target].m_Type].SkillType != 0)
			{
				if(lpObj->pInventory[target].m_Option1 == 0)
				{
					lpObj->pInventory[target].m_Option1++;
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Is Weapon to Skill");
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels] No use item skill");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Level
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfLevelType,this->JewelOfLevelIndex) ) 
	{
		if( this->JewelOfLevelRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0))
			{
				if(TargetLevel >= this->JewelOfLevelMin)
				{
					if(TargetLevel <= this->JewelOfLevelMax)
					{
						lpObj->pInventory[target].m_Level++;
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
					}
					else
					{
						MsgOutput(lpObj->m_Index,"[Jewels] Max Level Item %d",this->JewelOfLevelMax);
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Min Level Item %d",this->JewelOfLevelMin);
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels] No use item Level");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}		
//*************************************
//	Jewel Of Evalution
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfEvalutionType,this->JewelOfEvalutionIndex) )
	{
		if( this->JewelOfEvalutionRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0))
			{
				if(lpObj->pInventory[target].m_NewOption == 0)
				{
						int ExcellentOpt[6] = { 1, 2, 4, 8, 16, 32 };
						srand(time(NULL));
						lpObj->pInventory[target].m_NewOption = ExcellentOpt[rand()%6];
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Item Exellent status");
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels] No use item");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Ancent
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfAncentType,this->JewelOfAncentIndex) )
	{
		if( this->JewelOfAncentRate > iRate )
		{
			if(lpObj->pInventory[target].m_SetOption == 0)
			{
				if(gSetItemOption.IsSetItem(TargetIndex) != FALSE)
				{
					lpObj->pInventory[target].m_SetOption = gSetItemOption.ExGenSetOption(TargetIndex);
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] No Use Item Ancent");
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels] Item is Ancent");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Option
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfOptionType,this->JewelOfOptionIndex) ) //JewelOfOption
	{
		if( this->JewelOfOptionRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0))
			{
				if(lpObj->pInventory[target].m_Option3 != 7)
				{
					lpObj->pInventory[target].m_Option3 = 7;
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,"[Jewels] Max Option to Item");
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,"[Jewels]  No Use Item");
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}		
}

#endif

BYTE GetExcUnusedOption(BYTE ExcellentOption)
{
	int arrayopt[6]	= { 0, 0, 0, 0, 0, 0};
	int num			= 32;
	int amountopt	= 0;
	int added		= 0;
	// ----
	for( int i = 5; i >= 0; i-- )
	{
		if( ExcellentOption >= num )
		{
			arrayopt[i] = 1;
			amountopt++;
			ExcellentOption -= num;
		}
		num = num / 2;
	}
	// ----
	int randomopt = rand()%(6-amountopt)+1;
	amountopt = 0;

	for(int i=0; i<6; i++)
	{
		if(!arrayopt[i])
		{ 
			amountopt++;
			if( amountopt == randomopt )
			{
				arrayopt[i] = 1;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	num = 1; 
	ExcellentOption = 0;

	for (int i=0 ; i<6; i++)
	{
		if (arrayopt[i])
		{
			ExcellentOption += num;
		}
		num = num * 2;
	}

	return ExcellentOption;
}

bool ExJewelOfExellentAdded (LPOBJ lpObj, int source, int target)	//Jewel Of Exellent
{
	if(ExSecurityJewel(lpObj,source,target) == false)
	{
		return false;
	}

	if(lpObj->pInventory[target].m_Type < ITEMGET(12,0)/* && lpObj->pInventory[target].m_NewOption == 0*/)	//Exellent Item
	{
#if(JoExl_IN_JoGooD)
		if(  ExConfig.ExNewJewel.JewelOfExellentRate > ( rand()%100 )  )
		{
			if(lpObj->pInventory[target].m_Level >= 9 && lpObj->pInventory[target].m_Level != 13 )
			{
				lpObj->pInventory[target].m_Level++;

				gObjMakePreviewCharSet(lpObj->m_Index);

				float levelitemdur = (float)ItemGetDurability(lpObj->pInventory[target].m_Type,lpObj->pInventory[target].m_Level,lpObj->pInventory[target].IsExtItem(),lpObj->pInventory[target].IsSetItem());

				lpObj->pInventory[target].m_Durability = levelitemdur * lpObj->pInventory[target].m_Durability / lpObj->pInventory[target].m_BaseDurability;

				lpObj->pInventory[target].Convert(
					lpObj->pInventory[target].m_Type,
					lpObj->pInventory[target].m_Option1,
					lpObj->pInventory[target].m_Option2,
					lpObj->pInventory[target].m_Option3,
					lpObj->pInventory[target].m_NewOption,
					lpObj->pInventory[target].m_SetOption,
					lpObj->pInventory[target].m_ItemOptionEx,
					NULL, 0xFF, CURRENT_DB_VERSION);
				return true;
			}
			else
			{
				return false;
			}
			
		}
#else

#ifdef JOE_FULL_OPT
		srand(time(NULL));
		if(  ExConfig.ExNewJewel.JewelOfExellentRate > ( rand()%100 )  )
		{
			if( 5 > GetExcOptionCount(lpObj->pInventory[target].m_NewOption) )
			{
				BYTE NewOption = GetExcUnusedOption(lpObj->pInventory[target].m_NewOption);
				lpObj->pInventory[target].m_NewOption = NewOption;

				gObjMakePreviewCharSet(lpObj->m_Index);

				float levelitemdur = (float)ItemGetDurability(lpObj->pInventory[target].m_Type,lpObj->pInventory[target].m_Level,lpObj->pInventory[target].IsExtItem(),lpObj->pInventory[target].IsSetItem());

				lpObj->pInventory[target].m_Durability = levelitemdur * lpObj->pInventory[target].m_Durability / lpObj->pInventory[target].m_BaseDurability;

				lpObj->pInventory[target].Convert(
					lpObj->pInventory[target].m_Type,
					lpObj->pInventory[target].m_Option1,
					lpObj->pInventory[target].m_Option2,
					lpObj->pInventory[target].m_Option3,
					lpObj->pInventory[target].m_NewOption,
					lpObj->pInventory[target].m_SetOption,
					lpObj->pInventory[target].m_ItemOptionEx,
					NULL, 0xFF, CURRENT_DB_VERSION);
			}
			else if (5 == GetExcOptionCount(lpObj->pInventory[target].m_NewOption))
			{
				lpObj->pInventory[target].m_NewOption = 63;

				gObjMakePreviewCharSet(lpObj->m_Index);

				float levelitemdur = (float)ItemGetDurability(lpObj->pInventory[target].m_Type,lpObj->pInventory[target].m_Level,lpObj->pInventory[target].IsExtItem(),lpObj->pInventory[target].IsSetItem());

				lpObj->pInventory[target].m_Durability = levelitemdur * lpObj->pInventory[target].m_Durability / lpObj->pInventory[target].m_BaseDurability;

				lpObj->pInventory[target].Convert(
					lpObj->pInventory[target].m_Type,
					lpObj->pInventory[target].m_Option1,
					lpObj->pInventory[target].m_Option2,
					lpObj->pInventory[target].m_Option3,
					lpObj->pInventory[target].m_NewOption,
					lpObj->pInventory[target].m_SetOption,
					lpObj->pInventory[target].m_ItemOptionEx,
					NULL, 0xFF, CURRENT_DB_VERSION);
			}

		}
#else
		int ExcellentOpt[5] = { 1, 4, 8, 16, 32 };
		srand(time(NULL));
		if(  ExConfig.ExNewJewel.JewelOfExellentRate > ( rand()%100 )  )
		{
			lpObj->pInventory[target].m_NewOption = ExcellentOpt[rand()%4];

			gObjMakePreviewCharSet(lpObj->m_Index);

			float levelitemdur = (float)ItemGetDurability(lpObj->pInventory[target].m_Type,lpObj->pInventory[target].m_Level,lpObj->pInventory[target].IsExtItem(),lpObj->pInventory[target].IsSetItem());

			lpObj->pInventory[target].m_Durability = levelitemdur * lpObj->pInventory[target].m_Durability / lpObj->pInventory[target].m_BaseDurability;

			lpObj->pInventory[target].Convert(
				lpObj->pInventory[target].m_Type,
				lpObj->pInventory[target].m_Option1,
				lpObj->pInventory[target].m_Option2,
				lpObj->pInventory[target].m_Option3,
				lpObj->pInventory[target].m_NewOption,
				lpObj->pInventory[target].m_SetOption,
				lpObj->pInventory[target].m_ItemOptionEx,
				NULL, 0xFF, CURRENT_DB_VERSION);
		}
#endif

#endif

		return true;
	}
	return false;
}
//Jewel of Divinity
bool ExJewelOfDivinityAdded (LPOBJ lpObj, int source, int target)
{
	if(ExSecurityJewel(lpObj,source,target) == false)
	{
		return false;
	}

	if( lpObj->pInventory[target].m_Type == ITEMGET(13,8) || lpObj->pInventory[target].m_Type == ITEMGET(13,9) ||
		lpObj->pInventory[target].m_Type == ITEMGET(13,12)|| lpObj->pInventory[target].m_Type == ITEMGET(13,13)||
		lpObj->pInventory[target].m_Type == ITEMGET(13,21)|| lpObj->pInventory[target].m_Type == ITEMGET(13,22)||
		lpObj->pInventory[target].m_Type == ITEMGET(13,23)|| lpObj->pInventory[target].m_Type == ITEMGET(13,24)||
		lpObj->pInventory[target].m_Type == ITEMGET(13,25)|| lpObj->pInventory[target].m_Type == ITEMGET(13,26)||
		lpObj->pInventory[target].m_Type == ITEMGET(13,27)|| lpObj->pInventory[target].m_Type == ITEMGET(13,28)||
		lpObj->pInventory[target].m_Type == ITEMGET(13,8) )
	{
		if(lpObj->pInventory[target].m_Level >= 9)	//Не точит бижутерию больше +9
		{
			return false;
		}
		srand(time(NULL));
		if( ExConfig.ExNewJewel.JewelOfDivinityRate > (rand()%100) )
		{
			lpObj->pInventory[target].m_Level++;

			gObjMakePreviewCharSet(lpObj->m_Index);

			float levelitemdur = (float)ItemGetDurability(lpObj->pInventory[target].m_Type,lpObj->pInventory[target].m_Level,lpObj->pInventory[target].IsExtItem(),lpObj->pInventory[target].IsSetItem());

			lpObj->pInventory[target].m_Durability = levelitemdur * lpObj->pInventory[target].m_Durability / lpObj->pInventory[target].m_BaseDurability;

			lpObj->pInventory[target].Convert(
				lpObj->pInventory[target].m_Type,
				lpObj->pInventory[target].m_Option1,
				lpObj->pInventory[target].m_Option2,
				lpObj->pInventory[target].m_Option3,
				lpObj->pInventory[target].m_NewOption,
				lpObj->pInventory[target].m_SetOption,
				lpObj->pInventory[target].m_ItemOptionEx,
				NULL, 0xFF, CURRENT_DB_VERSION);
		}

		return true;
	}
	return false;
}
//Jewel Of Luck
bool ExJewelOfLuckAdded (LPOBJ lpObj, int source, int target)	//Jewel Of Luck
{
	if(ExSecurityJewel(lpObj,source,target) == false)
	{
		return false;
	}

	if(lpObj->pInventory[target].m_Type < ITEMGET(12,0) && lpObj->pInventory[target].m_Option2 == 0)	//Luck Item
	{
		srand(time(NULL));
		if(  ExConfig.ExNewJewel.JewelOfLuckRate > ( rand()%100 )  )
		{
			lpObj->pInventory[target].m_Option2 = 1;

			gObjMakePreviewCharSet(lpObj->m_Index);

			float levelitemdur = (float)ItemGetDurability(lpObj->pInventory[target].m_Type,lpObj->pInventory[target].m_Level,lpObj->pInventory[target].IsExtItem(),lpObj->pInventory[target].IsSetItem());

			lpObj->pInventory[target].m_Durability = levelitemdur * lpObj->pInventory[target].m_Durability / lpObj->pInventory[target].m_BaseDurability;

			lpObj->pInventory[target].Convert(
				lpObj->pInventory[target].m_Type,
				lpObj->pInventory[target].m_Option1,
				lpObj->pInventory[target].m_Option2,
				lpObj->pInventory[target].m_Option3,
				lpObj->pInventory[target].m_NewOption,
				lpObj->pInventory[target].m_SetOption,
				lpObj->pInventory[target].m_ItemOptionEx,
				NULL, 0xFF, CURRENT_DB_VERSION);
		}

		return true;
	}
	return false;
}

bool ExSecurityJewel (LPOBJ lpObj, int source, int target)
{
	if(source < 0 || source > MAIN_INVENTORY_SIZE -1)
	{
		return false;
	}

	if(target < 0 || target > MAIN_INVENTORY_SIZE -1)
	{
		return false;
	}

	if(lpObj->pInventory[source].IsItem() == 0)
	{
		return false;
	}

	if(lpObj->pInventory[target].IsItem() == 0)
	{
		return false;
	}

	return true;
}