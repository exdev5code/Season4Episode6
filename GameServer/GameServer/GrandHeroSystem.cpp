#include "StdAfx.h"
#if(_GRAND_HERO_SYSTEM_)
#include "user.h"
#include "GrandHeroSystem.h"
#include "Message.h"
#include "Functions.h"
#include "MixSystem.h"
#include "..\common\winutil.h"
#include "DSProtocol.h"
#include "logproc.h"
#include "protocol.h"
#include "ConnectEx.h"

cGrandHero GrandHero;

void cGrandHero::Load()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",1,GRANDHERO_DIR);
	this->GRTp = GetPrivateProfileInt("Common","GRTp",0,GRANDHERO_DIR);
	this->GRItem = GetPrivateProfileInt("Common","GRItem",1,GRANDHERO_DIR);
	this->MixItemRate = GetPrivateProfileInt("Common","MixItemRate",100,GRANDHERO_DIR);
	this->MixMoney = GetPrivateProfileInt("Common","MixMoney",0,GRANDHERO_DIR);
	this->ExStoneDropRate = GetPrivateProfileInt("Common","ExStoneDropRate",0,GRANDHERO_DIR);
	this->OffTradeLoren = GetPrivateProfileInt("Common","OffTradeLoren",1,GRANDHERO_DIR);
	this->BossAncDrop = GetPrivateProfileInt("Common","BossAncDrop",10000,GRANDHERO_DIR);

	

	this->ResetTP = GetPrivateProfileInt("Common","ResetTP",0,GRANDHERO_DIR);

	this->BossDropCount = GetPrivateProfileInt("Common","BossDropCount",1,GRANDHERO_DIR);

	this->TPMap = GetPrivateProfileInt("Common","TPMap",80,GRANDHERO_DIR);
	this->TPX = GetPrivateProfileInt("Common","TPX",30,GRANDHERO_DIR);
	this->TPY = GetPrivateProfileInt("Common","TPY",80,GRANDHERO_DIR);

	for (int i=0; i < 100; i++)
	{
		Items[i].Index		= 0;
		Items[i].ItemID		= 0;
		Items[i].Level		= 0;
		Items[i].Skill		= 0;
		Items[i].Luck		= 0;
		Items[i].Options	= 0;
		Items[i].Exl		= 0;
		Items[i].Anc		= 0;
	}

	FILE * file = fopen(GRANDHERO_DIR,"r");

	if (file == NULL)
	{
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;
	this->ItemCoint = 0;

	while (!feof(file))
	{
		fgets(Buff,256,file);

		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if (Flag == 1)
		{
			int n[8];

			sscanf(Buff,"%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);

			Items[this->ItemCoint].Index	= n[0];
			Items[this->ItemCoint].ItemID	= n[1];
			Items[this->ItemCoint].Level	= n[2];
			Items[this->ItemCoint].Skill	= n[3];
			Items[this->ItemCoint].Luck		= n[4];
			Items[this->ItemCoint].Options	= n[5];
			Items[this->ItemCoint].Exl		= n[6];
			Items[this->ItemCoint].Anc		= n[7];

			this->ItemCoint++;
		}
	}

	fclose(file);
}

void cGrandHero::NPCLoad(int aIndex, int MonsterClass)
{
	if(!this->Enable)return;

 	LPOBJ lpObj = &gObj[aIndex];

	if(MonsterClass == 520 || MonsterClass == 521)
	{
		lpObj->Type = OBJ_NPC;
	}
}

bool cGrandHero::NPCTeleport(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(!this->Enable)return false;

	if(lpNpc->Class == 520)
	{
		if(lpObj->MapNumber == 79)
		{
			gObjTeleport(lpObj->m_Index,0,146,136);
		}
		else
		{
			gObjTeleport(lpObj->m_Index,79,116,127);
		}
		return true;
	}
	else if(lpNpc->Class == 521)
	{
		if(ExUser[lpObj->m_Index].GReset >= this->GRTp && ExUser[lpObj->m_Index].Reset >= this->ResetTP )
		{
			gObjTeleport(lpObj->m_Index,this->TPMap,this->TPX,this->TPY);
		}
		else
		{
			if(this->ResetTP > ExUser[lpObj->m_Index].Reset)
			{
				MsgOutput(lpObj->m_Index,"Need %d Reset",this->ResetTP);
			}
			else
			{
				ChatTargetSend(lpNpc, "Need Grand Reset", lpObj->m_Index);
			}
			
		}

		return true;
	}
	return false;
}

void cGrandHero::ItemOption(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if( lpObj->pInventory[7].m_Type >= ITEMGET(7,60) && lpObj->pInventory[7].m_Type <= ITEMGET(7,65) )
	{
		lpObj->m_Defense += 30;

		lpObj->m_AttackDamageMaxLeft +=  30;
		lpObj->m_AttackDamageMinLeft +=  30;
		lpObj->m_AttackDamageMaxRight += 30;
		lpObj->m_AttackDamageMinRight += 30;
		lpObj->m_MagicDamageMax += 30;
		lpObj->m_MagicDamageMin += 30;
	}
	if( lpObj->pInventory[8].m_Type >= ITEMGET(8,60) && lpObj->pInventory[8].m_Type <= ITEMGET(8,65) )
	{
		lpObj->m_Defense += 30;

		lpObj->m_AttackDamageMaxLeft +=  30;
		lpObj->m_AttackDamageMinLeft +=  30;
		lpObj->m_AttackDamageMaxRight += 30;
		lpObj->m_AttackDamageMinRight += 30;
		lpObj->m_MagicDamageMax += 30;
		lpObj->m_MagicDamageMin += 30;
	}
	if( lpObj->pInventory[9].m_Type >= ITEMGET(9,60) && lpObj->pInventory[9].m_Type <= ITEMGET(9,65) )
	{
		lpObj->m_Defense += 30;

		lpObj->m_AttackDamageMaxLeft +=  30;
		lpObj->m_AttackDamageMinLeft +=  30;
		lpObj->m_AttackDamageMaxRight += 30;
		lpObj->m_AttackDamageMinRight += 30;
		lpObj->m_MagicDamageMax += 30;
		lpObj->m_MagicDamageMin += 30;
	}
	if( lpObj->pInventory[10].m_Type >= ITEMGET(10,60) && lpObj->pInventory[10].m_Type <= ITEMGET(10,65) )
	{
		lpObj->m_Defense += 30;

		lpObj->m_AttackDamageMaxLeft +=  30;
		lpObj->m_AttackDamageMinLeft +=  30;
		lpObj->m_AttackDamageMaxRight += 30;
		lpObj->m_AttackDamageMinRight += 30;
		lpObj->m_MagicDamageMax += 30;
		lpObj->m_MagicDamageMin += 30;
	}
	if( lpObj->pInventory[11].m_Type >= ITEMGET(11,60) && lpObj->pInventory[11].m_Type <= ITEMGET(11,65) )
	{
		lpObj->m_Defense += 30;

		lpObj->m_AttackDamageMaxLeft +=  30;
		lpObj->m_AttackDamageMinLeft +=  30;
		lpObj->m_AttackDamageMaxRight += 30;
		lpObj->m_AttackDamageMinRight += 30;
		lpObj->m_MagicDamageMax += 30;
		lpObj->m_MagicDamageMin += 30;
	}


	if( lpObj->pInventory[0].m_Type == ITEMGET(0,40) || 
		lpObj->pInventory[0].m_Type == ITEMGET(0,41) ||
		lpObj->pInventory[1].m_Type == ITEMGET(0,40) || 
		lpObj->pInventory[1].m_Type == ITEMGET(0,41) ||
		lpObj->pInventory[0].m_Type == ITEMGET(2,20) )
	{
		lpObj->SetOpDoubleDamage += 3;
		lpObj->SetOpIgnoreDefense += 3;
	}

	if(	lpObj->pInventory[0].m_Type == ITEMGET(4,30) ||
		lpObj->pInventory[0].m_Type == ITEMGET(5,41) ||
		lpObj->pInventory[0].m_Type == ITEMGET(5,41) )
	{
		lpObj->SetOpDoubleDamage += 6;
		lpObj->SetOpIgnoreDefense += 6;
	}
}

bool cGrandHero::SockeetItem(int ItemNumber)
{
	switch(ItemNumber)
	{
		case ITEMGET(0,40):
		case ITEMGET(0,41):
		case ITEMGET(2,20):
		case ITEMGET(4,30):
		case ITEMGET(5,40):
		case ITEMGET(5,41):
		case ITEMGET(6,30):
		case ITEMGET(6,31):
		case ITEMGET(6,32):
		case ITEMGET(6,33):
			return true;
	}

	if( ItemNumber >= ITEMGET(7,60) && ItemNumber <= ITEMGET(7,65) ||
		ItemNumber >= ITEMGET(8,60) && ItemNumber <= ITEMGET(8,65) ||
		ItemNumber >= ITEMGET(9,60) && ItemNumber <= ITEMGET(9,65) ||
		ItemNumber >= ITEMGET(10,60) && ItemNumber <= ITEMGET(10,65) ||
		ItemNumber >= ITEMGET(11,60) && ItemNumber <= ITEMGET(11,65) )
	{
		return true;
	}

	return false;
}

void cGrandHero::MixGrandItem(LPOBJ lpObj)
{
	int Item = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x86;
	pMsg.h.size = sizeof(PMSG_CHAOSMIXRESULT);

	pMsg.Result = CB_ERROR;

	int ExStone = 0;
	int ExlItem = 0;
	int AncItem = 0;
	int Creation = 0;
	int Chaos = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++ )
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,208) )
			{
				ExStone++;
			}
			else if(lpObj->pChaosBox[n].m_Type == ITEMGET(12,15))
			{
				Chaos++;
			}
			else if(lpObj->pChaosBox[n].m_Type == ITEMGET(14,22))
			{
				Creation++;
			}
			else if( g_MixSystem.CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,1) != FALSE )
			{
				ExlItem++;
			}
			else if( g_MixSystem.CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,1,0) != FALSE )
			{
				AncItem++;
			}
		}
	}

	if(ExStone != 10 || ExlItem == 0 || AncItem == 0 || Creation == 0 || Chaos == 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(this->MixMoney > lpObj->Money)
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	lpObj->Money -= this->MixMoney;
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	srand(time(NULL));
	if(this->MixItemRate > (rand()%100))
	{
		srand(time(NULL));
		int ItemType = rand()%39;

		switch(ItemType)
		{
			case 0: ItemType = ITEMGET(0,40); break;
			case 1: ItemType = ITEMGET(0,41); break;
			case 2: ItemType = ITEMGET(2,20); break;
			case 3: ItemType = ITEMGET(4,30); break;
			case 4: ItemType = ITEMGET(5,40); break;
			case 5: ItemType = ITEMGET(5,41); break;
			case 6: ItemType = ITEMGET(6,30); break;
			case 7: ItemType = ITEMGET(6,31); break;
			case 8: ItemType = ITEMGET(6,32); break;
			case 9: ItemType = ITEMGET(6,33); break;
			case 10:ItemType = ITEMGET(7,60); break;
			case 11:ItemType = ITEMGET(7,61); break;
			case 12:ItemType = ITEMGET(7,62); break;
			case 13:ItemType = ITEMGET(7,64); break;
			case 14:ItemType = ITEMGET(7,65); break;
			case 15:ItemType = ITEMGET(8,60); break;
			case 16:ItemType = ITEMGET(8,61); break;
			case 17:ItemType = ITEMGET(8,62); break;
			case 18:ItemType = ITEMGET(8,63); break;
			case 19:ItemType = ITEMGET(8,64); break;
			case 20:ItemType = ITEMGET(8,65); break;
			case 21:ItemType = ITEMGET(9,60); break;
			case 22:ItemType = ITEMGET(9,61); break;
			case 23:ItemType = ITEMGET(9,62); break;
			case 24:ItemType = ITEMGET(9,63); break;
			case 25:ItemType = ITEMGET(9,64); break;
			case 26:ItemType = ITEMGET(9,65); break;
			case 27:ItemType = ITEMGET(10,60);break;
			case 28:ItemType = ITEMGET(10,61);break;
			case 29:ItemType = ITEMGET(10,62);break;
			case 30:ItemType = ITEMGET(10,63);break;
			case 31:ItemType = ITEMGET(10,64);break;
			case 32:ItemType = ITEMGET(10,65);break;
			case 33:ItemType = ITEMGET(11,60);break;
			case 34:ItemType = ITEMGET(11,61);break;
			case 35:ItemType = ITEMGET(11,62);break;
			case 36:ItemType = ITEMGET(11,63);break;
			case 37:ItemType = ITEMGET(11,64);break;
			case 38:ItemType = ITEMGET(11,65);break;
			default:ItemType = ITEMGET(0,40);
		}

		int iSkill = 0;
		
		switch(ItemType)
		{
			case ITEMGET(0,40):
			case ITEMGET(0,41):
			case ITEMGET(2,20):
			case ITEMGET(4,30):
			case ITEMGET(6,30):
			case ITEMGET(6,31):
			case ITEMGET(6,32):
			case ITEMGET(6,33):
				iSkill = 1; break;
		}

		int AncItem = 0;

		if( ItemType >= ITEMGET(7,60) && ItemType <= ITEMGET(7,65) ||
			ItemType >= ITEMGET(8,60) && ItemType <= ITEMGET(8,65) ||
			ItemType >= ITEMGET(9,60) && ItemType <= ITEMGET(9,65) ||
			ItemType >= ITEMGET(10,60) && ItemType <= ITEMGET(10,65) ||
			ItemType >= ITEMGET(11,60) && ItemType <= ITEMGET(11,65) )
		{
			AncItem = 5;
		}

		srand(time(NULL));
		int iLevel = rand()%5;

		srand(time(NULL));
		int iLuck = rand()%2;

		int ExcellentOpt[6] = { 1, 2, 4, 8, 16, 32 };
		srand(time(NULL));
		int ExlRand = ExcellentOpt[rand()%6];

		int Option = rand()%8;

		ItemSerialCreateSend(lpObj->m_Index, 0xFF, 0, 0, ItemType, iLevel, 0, iSkill, iLuck, Option, lpObj->m_Index, ExlRand, AncItem);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[GrandHeroSystem][Mix Item] CBMix Item Create Item:%d, Accaunt:%s, Nick:%s",ItemType,lpObj->AccountID,lpObj->Name);
	}
	else
	{
		g_MixSystem.ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[GrandHeroSystem][Mix Item] CBMix Fail");
	}
}

bool cGrandHero::BossDrop(LPOBJ lpObj, LPOBJ lpTargetObj)	//lpTargetObj - тот кто убивает
{
	if(!this->Enable)return false;

	if(lpObj->Class == 600)
	{
		srand(time(NULL));
		int num = rand()%this->ItemCoint;
		int Exe = 0;
		int Anc = 0;
		int Type = ITEMGET(this->Items[num].Index,this->Items[num].ItemID);
		if ( this->Items[num].Exl > 0 )
		{
			Exe = GenExcOpt(this->Items[num].Exl);
		}

		if ( this->Items[num].Anc == 5 || this->Items[num].Anc == 10 )
		{
			Anc = this->Items[num].Anc;
		}

		for(int i=0;i<this->BossDropCount;i++)
		{
			ItemSerialCreateSend(lpTargetObj->m_Index,(BYTE)lpObj->MapNumber,(BYTE)lpObj->X,(BYTE)lpObj->Y,Type,(BYTE)Items[num].Level,0,(BYTE)Items[num].Skill,(BYTE)Items[num].Luck,(BYTE)Items[num].Options,lpTargetObj->m_Index,(BYTE)Exe,(BYTE)Anc);
		}

		srand(time(NULL));
		if(this->BossAncDrop > rand()%10000)
		{
			MakeRewardSetItem(lpTargetObj->m_Index, lpObj->X, lpObj->Y, 1, lpObj->MapNumber);
		}

#if(_MegaMu_)
		return true;
#endif
	}
	else if(lpTargetObj->MapNumber == 80)
	{
		srand(time(NULL));
		if(this->ExStoneDropRate > rand()%10000)
		{
			ItemSerialCreateSend(lpTargetObj->m_Index,(BYTE)lpObj->MapNumber,(BYTE)lpObj->X,(BYTE)lpObj->Y,ITEMGET(14,208),0,0,0,0,0,lpTargetObj->m_Index,0,0);
		}
#if(_MegaMu_)
		return true;
#endif
	}
	return false;
}

bool cGrandHero::MoveGRItem(int aIndex, int ItemNumber, int target)
{
	if(!this->Enable)return true;

	if(this->SockeetItem(ItemNumber) == true && target >= 0 && target <= 6)
	{
		if(ExUser[aIndex].GReset >= this->GRItem)
		{
			return true;
		}
		else
		{
			MsgNormal(aIndex, "Grand Item Need Grand Reset: %d", this->GRItem);
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool cGrandHero::OffTradeLorenMarket(int aIndex, int type)
{
	if(!this->Enable)return false;

	if(!this->OffTradeLoren) return false;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber==79)
	{
		if(type == 1)
		{
			strcpy(lpObj->m_szPShopText,".::ZEN SHOP::.");
		}
		else if(type == 2)
		{
			strcpy(lpObj->m_szPShopText,".::EXPOINT SHOP::.");
		}
		else if(type == 3)
		{
			strcpy(lpObj->m_szPShopText,".::WCOINT SHOP::.");
		}
		else if(type == 4)
		{
			strcpy(lpObj->m_szPShopText,".::CREDIT SHOP::.");
		}
		else
		{
			strcpy(lpObj->m_szPShopText,".::ZEN SHOP::.");
		}

		MessaageAllGlobal("[OffTrade][%s] Loren Market %d %d",lpObj->Name,lpObj->X,lpObj->Y);

#ifdef _RECONNECT_
		g_ConnectEx.SendClose(aIndex,type);
#else
		CloseClient(aIndex);
		ExUser[aIndex].OffTrade = type;
#endif
	}
	else
	{
		MsgNormal(aIndex,"[OffTrade] OffTrade work only Loren Market");
	}

	return true;
}

bool cGrandHero::HeroMap(int iMap)
{
	if(!this->Enable) return false;

	if(iMap == 80)
	{
		return true;
	}

	return false;
}

void cGrandHero::CheckGRMap(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->MapNumber == 80)
	{
		if(ExUser[aIndex].GReset < this->GRTp)
		{
			MsgNormal(aIndex,"Need %d Grand Reset",this->GRTp);
			gObjTeleport(aIndex,0,140,135);
		}
	}
}

#endif