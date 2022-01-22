// SocketOption.cpp: implementation of the CSocketOption class.
// GS-CS 1.00.90  -	0xXXXXXXXX
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SocketOption.h"
#include "..\\Include\\ReadScript.h"
#include "LogProc.h"
#include "GameMain.h"
#include "LargeRand.h"
#include "SocketSphere.h"
#include "GrandHeroSystem.h"

//************************************
// Globals
//************************************
int g_iSeedExtractMoney;//3EE3324
int g_iSeedSphereCompositeMoney;//3EE3328
int g_iSeedSphereSetMoney;//3EE332C
int g_iSeedSphereRemoveMoney;//3EE3330
int g_iShopBuySocketItemSlotCount;//3EE3334


CSocketOption g_SocketOption;

CSocketOption::CSocketOption()//00556A40
{

}

CSocketOption::~CSocketOption()//00556B80
{

}

void CSocketOption::Init()//00556C60 - identical?:D
{
	int i = 0;

	for(i = 0; i < 50;i++)
	{
		this->SocketSeed[i].ClearData();
	}

	for(i = 0;i < MAX_SOCKET_OPTION;i++)
	{	
		this->SocketSphere[i].ClearData();
	}

	for(i = 0;i < 6;i++) //sphere element
	{
		this->SocketSpear[i].ClearData();
	}

	this->SocketSlotRandomPool.InitPool();
	this->SocketRandomPool.InitPool();

	for(i = 0;i < MAX_SOCKET_OPTION;i++)
	{
		this->iSphereDropRate[i] = 0;
		this->iSphereDropLevel[i] = 0;
	}

}

BYTE CSocketOption::LoadScript(LPSTR lpszFileName)//00556DA0- identical
{
	this->Init();

	SMDFile = fopen(lpszFileName, "r");

	if(SMDFile == NULL)
	{
		MsgBox("[SocketOption] SocketOption Script file Load failed. (%s)",lpszFileName);
		return 0;
	}

	SMDToken Token;

	int m_0C = 0;
	int m_10 = 0;
	int m_14 = 0;
	int m_18 = 0;
	int m_1C = 0;

	while(TRUE)
	{
		Token = GetToken();

		if ( Token == END )
			break;
			
		if(!strcmp("end",TokenString))
			break;

		if( Token == NUMBER )
		{
			m_0C = (int)TokenNumber;

			while(true)
			{
				if(m_0C == 0)// m_0c == 0 - identical
				{
					BYTE bt_20 = 0;
					BYTE bt_24 = 0;
					BYTE bt_28 = 0;
					BYTE bt_2C = 0;
					BYTE bt_34[MAX_SOCKET_OPTION] = {0};

					int m_38 = 0;
					int m_3C = 0;

					Token = GetToken();

					if(!strcmp("end",TokenString))
						break;

					bt_20 = (BYTE)TokenNumber;
					
					Token = GetToken();		bt_24		= (BYTE)TokenNumber;	
					Token = GetToken();		bt_28		= (BYTE)TokenNumber;		
					Token = GetToken();		// Reserved for Name
					Token = GetToken();		bt_2C		= (BYTE)TokenNumber;		
					Token = GetToken();		bt_34[0]	= (BYTE)TokenNumber;	
					Token = GetToken();		bt_34[1]	= (BYTE)TokenNumber;	
					Token = GetToken();		bt_34[2]	= (BYTE)TokenNumber;		
					Token = GetToken();		bt_34[3]	= (BYTE)TokenNumber;	
					Token = GetToken();		bt_34[4]	= (BYTE)TokenNumber;	
					Token = GetToken();		m_38		= (int)TokenNumber;


					this->SocketRandomPool.AddValue(bt_20,m_38);

					this->SocketSeed[m_10].SetInfo(bt_20,bt_24,bt_28,bt_2C,bt_34,m_38);

					m_10++;

					if(m_10 > MAX_SEED_OPTION)
					{
						MsgBox("[ERROR] MAX SeedSphere Option Data Overflow! [%d]",m_10);
						break;
					}
				}

				else if(m_0C == 1)//m0C == 1 - identical
				{
					Token = GetToken();

					if(!strcmp("end",TokenString))
						break;

					CSocketSphere temp;

					memset(&temp,0,sizeof(temp));

					temp.m_btOptionIndex = (BYTE)TokenNumber;


					Token = GetToken();		temp.m_btElementIndex	= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_btElementType	= (BYTE)TokenNumber;
					Token = GetToken();		// Reserved for Name
					Token = GetToken();		temp.m_btOptionType	= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_btOptionValue	= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_iOptionRate	= (int)TokenNumber;
					Token = GetToken();		temp.m_btSocketSlot[0]= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_btSocketSlot[1]= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_btSocketSlot[2]= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_btSocketSlot[3]= (BYTE)TokenNumber;
					Token = GetToken();		temp.m_btSocketSlot[4]= (BYTE)TokenNumber;

					for(int n = 0;n < MAX_SOCKET_OPTION;n++)
					{
						if(temp.m_btSocketSlot[n] != NULL)
						{
							temp.m_btSocketSlotCount++;
						}
					}

					switch(temp.m_btOptionIndex)
					{
						case 0:	temp.m_btEffectType = 0;	break;
						case 1:	temp.m_btEffectType = 18;	break;
						case 2:	temp.m_btEffectType = 0;	break;
						case 3:	temp.m_btEffectType = 18;	break;
						case 4:	temp.m_btEffectType = 11;	break;
						case 5:	temp.m_btEffectType = 22;	break;
					}

					memcpy(&this->SocketSpear[m_18],&temp,sizeof(temp));
					m_18++;
				
				}
				else if(m_0C == 2)//m_0C == 2  - Identical
				{
					int m_58 = 0;
					BYTE m_5C = 0;
					BYTE m_60 = 0;
					BYTE m_64 = 0;
					int m_68 = 0;
					BYTE m_70[MAX_SPHERE_OPTION] = { 0 };

					Token = GetToken();

					if(!strcmp("end",TokenString))
						break;

					m_58 = (int)TokenNumber;

					Token = GetToken();		m_5C = (BYTE)TokenNumber;
					Token = GetToken();		// Reserved for Name
					Token = GetToken();		m_60 = (BYTE)TokenNumber;
					Token = GetToken();		m_64 = (BYTE)TokenNumber;
					Token = GetToken();		m_68 = (int)TokenNumber;
					Token = GetToken();		m_70[0] = (BYTE)TokenNumber;
					Token = GetToken();		m_70[1] = (BYTE)TokenNumber;
					Token = GetToken();		m_70[2] = (BYTE)TokenNumber;
					Token = GetToken();		m_70[3] = (BYTE)TokenNumber;
					Token = GetToken();		m_70[4] = (BYTE)TokenNumber;
					Token = GetToken();		m_70[5] = (BYTE)TokenNumber;

					this->SocketBonusOption[m_1C].btNumber		= m_1C;
					this->SocketBonusOption[m_1C].btType		= m_60;
					this->SocketBonusOption[m_1C].btIncrease	= m_64;
					this->SocketBonusOption[m_1C].iProbability	= m_68;
					this->SocketBonusOption[m_1C].btElements[0]	= m_70[0];
					this->SocketBonusOption[m_1C].btElements[1]	= m_70[1];
					this->SocketBonusOption[m_1C].btElements[2]	= m_70[2];
					this->SocketBonusOption[m_1C].btElements[3]	= m_70[3];
					this->SocketBonusOption[m_1C].btElements[4]	= m_70[4];
					this->SocketBonusOption[m_1C].btElements[5]	= m_70[5];

					switch(m_58)
					{
					case 0:	this->SocketBonusOption[m_1C].btOption = 44;	break;
					case 1:	this->SocketBonusOption[m_1C].btOption = 45;	break;
					}
					
					m_1C++;
				}
			}
		}
	}

	this->_InitOption(); 

	return 1;
}

void CSocketOption::_InitOption()//00557A60 - identical
{
	this->SocketSlotRandomPool.InitPool();
	this->TwoHandWeaponSocketSlotRandomPool.InitPool();

	this->iSocketSlotCountRate[SOCKET_SLOT_1]	= GetPrivateProfileInt("GameServerInfo","SocketSlotCountRate1",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSocketSlotCountRate[SOCKET_SLOT_2]	= GetPrivateProfileInt("GameServerInfo","SocketSlotCountRate2",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSocketSlotCountRate[SOCKET_SLOT_3]	= GetPrivateProfileInt("GameServerInfo","SocketSlotCountRate3",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSocketSlotCountRate[SOCKET_SLOT_4]	= GetPrivateProfileInt("GameServerInfo","SocketSlotCountRate4",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSocketSlotCountRate[SOCKET_SLOT_5]	= GetPrivateProfileInt("GameServerInfo","SocketSlotCountRate5",0,gDirPath.GetNewPath("commonserver.cfg"));

	this->iTwoHandSlotCountRate[SOCKET_SLOT_1]	= GetPrivateProfileInt("GameServerInfo","TwoHandWeaponSocketSlotCountRate1",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iTwoHandSlotCountRate[SOCKET_SLOT_2]	= GetPrivateProfileInt("GameServerInfo","TwoHandWeaponSocketSlotCountRate2",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iTwoHandSlotCountRate[SOCKET_SLOT_3]	= GetPrivateProfileInt("GameServerInfo","TwoHandWeaponSocketSlotCountRate3",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iTwoHandSlotCountRate[SOCKET_SLOT_4]	= GetPrivateProfileInt("GameServerInfo","TwoHandWeaponSocketSlotCountRate4",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iTwoHandSlotCountRate[SOCKET_SLOT_5]	= GetPrivateProfileInt("GameServerInfo","TwoHandWeaponSocketSlotCountRate5",0,gDirPath.GetNewPath("commonserver.cfg"));

	g_iSeedExtractMoney				= GetPrivateProfileInt("GameServerInfo","SeedExtractMoney",1000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_iSeedSphereCompositeMoney		= GetPrivateProfileInt("GameServerInfo","SeedSphereCompositeMoney",1000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_iSeedSphereSetMoney			= GetPrivateProfileInt("GameServerInfo","SeedSphereSetMoney",1000000,gDirPath.GetNewPath("commonserver.cfg"));
	g_iSeedSphereRemoveMoney		= GetPrivateProfileInt("GameServerInfo","SeedSphereRemoveMoney",1000000,gDirPath.GetNewPath("commonserver.cfg"));

	this->SocketSlotRandomPool.AddValue(1,this->iSocketSlotCountRate[SOCKET_SLOT_1]);
	this->SocketSlotRandomPool.AddValue(2,this->iSocketSlotCountRate[SOCKET_SLOT_2]);
	this->SocketSlotRandomPool.AddValue(3,this->iSocketSlotCountRate[SOCKET_SLOT_3]);
	this->SocketSlotRandomPool.AddValue(4,this->iSocketSlotCountRate[SOCKET_SLOT_4]);
	this->SocketSlotRandomPool.AddValue(5,this->iSocketSlotCountRate[SOCKET_SLOT_5]);

	this->TwoHandWeaponSocketSlotRandomPool.AddValue(1,this->iTwoHandSlotCountRate[SOCKET_SLOT_1]);
	this->TwoHandWeaponSocketSlotRandomPool.AddValue(2,this->iTwoHandSlotCountRate[SOCKET_SLOT_2]);
	this->TwoHandWeaponSocketSlotRandomPool.AddValue(3,this->iTwoHandSlotCountRate[SOCKET_SLOT_3]);
	this->TwoHandWeaponSocketSlotRandomPool.AddValue(4,this->iTwoHandSlotCountRate[SOCKET_SLOT_4]);
	this->TwoHandWeaponSocketSlotRandomPool.AddValue(5,this->iTwoHandSlotCountRate[SOCKET_SLOT_5]);

	g_iShopBuySocketItemSlotCount	= GetPrivateProfileInt("GameServerInfo","ShopBuySocketItemSlotCount",3,gDirPath.GetNewPath("commonserver.cfg"));

	this->bSphereDrop				= GetPrivateProfileInt("GameServerInfo","SphereDropOn",0,gDirPath.GetNewPath("commonserver.cfg"));

	this->iSphereDropRate[SOCKET_SLOT_1]		= GetPrivateProfileInt("GameServerInfo","SphereDropRate_Lv1",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropRate[SOCKET_SLOT_2]		= GetPrivateProfileInt("GameServerInfo","SphereDropRate_Lv2",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropRate[SOCKET_SLOT_3]		= GetPrivateProfileInt("GameServerInfo","SphereDropRate_Lv3",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropRate[SOCKET_SLOT_4]		= GetPrivateProfileInt("GameServerInfo","SphereDropRate_Lv4",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropRate[SOCKET_SLOT_5]		= GetPrivateProfileInt("GameServerInfo","SphereDropRate_Lv5",0,gDirPath.GetNewPath("commonserver.cfg"));

	this->iSphereDropLevel[SOCKET_SLOT_1]		= GetPrivateProfileInt("GameServerInfo","SphereDropLevel_Lv1",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropLevel[SOCKET_SLOT_2]		= GetPrivateProfileInt("GameServerInfo","SphereDropLevel_Lv2",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropLevel[SOCKET_SLOT_3]		= GetPrivateProfileInt("GameServerInfo","SphereDropLevel_Lv3",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropLevel[SOCKET_SLOT_4]		= GetPrivateProfileInt("GameServerInfo","SphereDropLevel_Lv4",0,gDirPath.GetNewPath("commonserver.cfg"));
	this->iSphereDropLevel[SOCKET_SLOT_5]		= GetPrivateProfileInt("GameServerInfo","SphereDropLevel_Lv5",0,gDirPath.GetNewPath("commonserver.cfg"));
}

BYTE CSocketOption::IsActive(CItem *pItem)//00558160 - identical
{
	if(pItem == NULL)
	{
		return FALSE;
	}

	if(pItem->IsItem() == FALSE)
	{
		return FALSE;
	}

	return this->CheckItemType(pItem->m_Type);
}

BYTE CSocketOption::CheckItemType(int iItemNumber)//005581B0 -identical //calls alloc 8x
{
	
	switch(iItemNumber)
	{
	case ITEMGET(0,26)://
	case ITEMGET(0,27)://
	case ITEMGET(0,28)://
	case ITEMGET(2,16)://
	case ITEMGET(2,17)://
	case ITEMGET(4,23)://
	case ITEMGET(5,30):
	case ITEMGET(5,31):
	case ITEMGET(5,32):
	case ITEMGET(6,17):
	case ITEMGET(6,18):
	case ITEMGET(6,19):
	case ITEMGET(6,20):
	case ITEMGET(7,45):
	case ITEMGET(7,46):
	case ITEMGET(7,49):
	case ITEMGET(7,50):
	case ITEMGET(7,51):
	case ITEMGET(7,52):
	case ITEMGET(7,53):
	case ITEMGET(8,45):
	case ITEMGET(8,46):
	case ITEMGET(8,47):
	case ITEMGET(8,48):
	case ITEMGET(8,49):
	case ITEMGET(8,50):
	case ITEMGET(8,51):
	case ITEMGET(8,52):
	case ITEMGET(8,53):
	case ITEMGET(9,45):
	case ITEMGET(9,46):
	case ITEMGET(9,47):
	case ITEMGET(9,48):
	case ITEMGET(9,49):
	case ITEMGET(9,50):
	case ITEMGET(9,51):
	case ITEMGET(9,52):
	case ITEMGET(9,53):
	case ITEMGET(10,45):
	case ITEMGET(10,46):
	case ITEMGET(10,47):
	case ITEMGET(10,48):
	case ITEMGET(10,49):
	case ITEMGET(10,50):
	case ITEMGET(10,51):
	case ITEMGET(10,52):
	case ITEMGET(10,53):
	case ITEMGET(11,45):
	case ITEMGET(11,46):
	case ITEMGET(11,47):
	case ITEMGET(11,48):
	case ITEMGET(11,49):
	case ITEMGET(11,50):
	case ITEMGET(11,51):
	case ITEMGET(11,52):
	case ITEMGET(11,53):
		return TRUE;
	}
#if(_GRAND_HERO_SYSTEM_)
	if(GrandHero.SockeetItem(iItemNumber)==true)
	{
		return TRUE;
	}
#endif

	return FALSE;
}

//00558300 - identical (unused)
BYTE CSocketOption::GetActiveSocketSlots(CItem * pItem)
{
	BYTE btCount = 0;

	for(int i = 0;i < MAX_SOCKET_OPTION; i++)
	{
		if(pItem->m_SocketOption[i] == 0xFE)
		{
			btCount++;
		}
	}

	return btCount;
}

//00558370 - identical (unused)
BYTE CSocketOption::ModifySeedSphereData(BYTE SeedSphereIndex,BYTE & OptionIndex,BYTE & OptionType,BYTE & SocketSlot)
{
	BYTE loc5 = 0;
	BYTE loc6 = 0;

	CSeed * lpSeed = NULL;//loc7
	CSphere * lpSphere = NULL;//loc8
	CSeedSphere  SeedSphere;

	loc5 = SeedSphereIndex % 50;
	loc6 = (SeedSphereIndex - loc5) / 50 + 1;

	lpSeed = this->GetSeedData(loc5);
	lpSphere = this->GetSphereData(loc6);

	if(lpSeed == NULL)
	{
		return (BYTE)0;
	}

	SeedSphere.SetInfo(lpSeed,loc6); //

	OptionIndex = SeedSphere.m_btOptionIndex;
	OptionType = SeedSphere.m_btOptionType;
	SocketSlot = SeedSphere.m_wSocketSlot;
	
	return (BYTE)1;
}

//005584C0 - identical
void CSocketOption::GetActiveSocketOption(CItem *pItem, BYTE *SocketOption, BYTE &SocketIndex)
{
	if(pItem == NULL)
	{
		return;
	}

	if(pItem->IsItem() == FALSE || this->IsActive(pItem) == FALSE)
	{
		return;	
	}

	for( int i = 0; i < MAX_SOCKET_OPTION; i++)
	{
		SocketOption[i] = pItem->m_SocketOption[i];
	}

	SocketIndex =  pItem->m_SocketOptionIndex;
}

//00558560 - identical
BYTE CSocketOption::IsSocketOption(CItem *pItem)
{
	if(pItem == NULL)
	{
		return FALSE;
	}

	if(pItem->IsItem() == FALSE)
	{
		return FALSE;
	}

	if(this->IsActive(pItem) == FALSE)
	{
		return FALSE;
	}
		
	for (int i = 0; i < MAX_SOCKET_OPTION; i++ )
	{
		if ( pItem->m_SocketOption[i] != 0xFF )
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

//00558600- identical
BYTE CSocketOption::IsSeedSphereItem(int m_Type)
{
	switch(m_Type)
	{
	case ITEMGET(12,60):
	case ITEMGET(12,61):
	case ITEMGET(12,62):
	case ITEMGET(12,63):
	case ITEMGET(12,64):
	case ITEMGET(12,65):
		return TRUE;
	}

	return FALSE;
}

//00558650- identical
BYTE CSocketOption::IsSeedItem(int m_Type)
{
	switch(m_Type)
	{
	case ITEMGET(12,70):
	case ITEMGET(12,71):
	case ITEMGET(12,72):
	case ITEMGET(12,73):
	case ITEMGET(12,74):
	
		return TRUE;
	}

	return FALSE;
}

//005586A0- identical
BYTE CSocketOption::IsSeedSpearItem(int m_Type)
{
	BYTE loc2 = 0;
	BYTE loc3 = 0;

	loc3 = m_Type % 512;

	loc2 = (m_Type - loc3) / 512 ;

	if(loc2 == 12)
	{
		if(loc3 >= 100 && loc3 <= 129)
		{
			return TRUE;
		}
	}

	return FALSE;
}


//00558740 - identical
BYTE CSocketOption::GetSeedOptionIndex(int m_Type, BYTE m_Level)
{
	for(int i = 0; i < MAX_SEED_OPTION; i++)
	{
		if(this->SocketSeed[i].m_iItemIndex == m_Type && this->SocketSeed[i].m_btItemLevel == m_Level)
		{
			return this->SocketSeed[i].m_btOptionIndex;
		}
	}

	return -1;
}

//005587D0- identical
BYTE CSocketOption::GetSphereLevel(int m_Type)
{
	switch ( m_Type )
	{
	case ITEMGET(12,70):	return 1;	break;
	case ITEMGET(12,71):	return 2;	break;
	case ITEMGET(12,72):	return 3;   break;
	case ITEMGET(12,73):	return 4;	break;
	case ITEMGET(12,74):	return 5;   break;
	}

	return 0;
}

//00558850  /> \55            PUSH EBP
BYTE CSocketOption::CheckEmptySlot(CItem * pItem, WORD m_Type, BYTE m_Level)//identical
{
	BYTE loc2 = 0;
	BYTE loc3 = 0;

	if(this->IsActive(pItem) == 0)
	{
		return 0;
	}
	
	loc3 = this->GetItemSocketByteOption(m_Type,m_Level);
	loc2 = loc3 % 50;

	for (int i = 0; i < MAX_SOCKET_OPTION; i++ )
	{
		if (pItem->m_SocketOption[i] == 0xFF || pItem->m_SocketOption[i] == 0xFE )
		{
			continue;
		}

		if(	pItem->m_SocketOption[i] % 50 == loc2 )
		{
			return 0;
		}

	}
	
	return 1;
}


//00558960  -identical
BYTE CSocketOption::GetItemSocketByteOption(WORD m_Type, BYTE m_Level)
{
	BYTE loc2 = 0;
	BYTE loc3 = 0;
	BYTE loc4 = 0;

			//lol
	loc3 = (m_Type % 512 - 100) / 6;
	loc2 = (m_Type % 512 - 100) % 6 + 1;
	
	for(int i = 0; i < MAX_SEED_OPTION; i++)
	{
		if(	this->SocketSeed[i].m_btElementIndex == loc2 && this->SocketSeed[i].m_btItemLevel == m_Level)
		{
			loc4 = loc3 * 50 + this->SocketSeed[i].m_btOptionIndex; //SOCKET BYTE ON ITEM BINARY

			return loc4;
		}
	}
	return -1;
}


//00558A80
int CSocketOption::GetValue(BYTE index) //chaos mix used?
{
	BYTE loc5 = 0;
	BYTE loc6 = 0;
	
	CSeed * lpSeed = NULL;//loc7
	CSphere * lpSphere = NULL;

	CSeedSphere SeedSphere;//loc1

	int loc13 = 0;

	loc5 = index % 50;
	loc6 = (index - loc5) / 50 + 1;
	
	lpSeed = this->GetSeedData(loc5);

	if( lpSeed == NULL)
	{
		return NULL;
	}
	
	SeedSphere.SetInfo(lpSeed, loc6);
	
	loc13 = ItemAttribute[SeedSphere.GetItemIndex()].BuyMoney;
		
	return loc13;
}

//00558BC0 - identical
BYTE CSocketOption::CheckItemElementInfo(CItem * pItem,BYTE index)
{
	if(this->IsActive(pItem) == 0)
	{
		return 0;
	}

	BYTE loc2 = 0;
	BYTE loc3 = 0;
	BYTE loc4 = 0;

	loc3 = pItem->m_Type % 512;//
	loc2 = (pItem->m_Type - loc3) / 512;
	loc4 = this->GetElementIndex(index);

	if(loc2 >= 0 && loc2 <= 5)
	{
		switch(loc4)
		{
		case 1:
		case 3:
		case 5:
			return 1;
		}
	}
	else if(loc2 >= 6 && loc2 <= 11)
	{
		switch(loc4)
		{
		case 2:
		case 4:
		case 6:
			return 1;
		}

	}
	else
	{
		return 0;
	}

	return 0;
}

//00558D10 - identical
BYTE CSocketOption::CheckMapNumber(int MapNumber)
{
	switch(MapNumber)
	{
	case MAP_INDEX_RAKLION:
	case MAP_INDEX_RAKLION_BOSS:
		return 1;
	}

	return 0;
}

//00558D50 - identical
int CSocketOption::GetSphereItemIndex(int Level)
{
	int loc2 = -1;
	int loc3 = 0;

	if(this->bSphereDrop != TRUE)
	{
		return loc2;
	}
	
	if(this->iSphereDropLevel[SOCKET_SLOT_5] != 0 && this->iSphereDropLevel[SOCKET_SLOT_5] <= Level)
	{
		loc3 = 5;
	}
	else if(this->iSphereDropLevel[SOCKET_SLOT_4] != 0 && this->iSphereDropLevel[SOCKET_SLOT_4] <= Level)
	{
		loc3 = 4;
	}
	else if(this->iSphereDropLevel[SOCKET_SLOT_3] != 0 && this->iSphereDropLevel[SOCKET_SLOT_3] <= Level)
	{
		loc3 = 3;
	}
	else if(this->iSphereDropLevel[SOCKET_SLOT_2] != 0 && this->iSphereDropLevel[SOCKET_SLOT_2] <= Level)
	{
		loc3 = 2;
	}
	else if(this->iSphereDropLevel[SOCKET_SLOT_1] != 0 && this->iSphereDropLevel[SOCKET_SLOT_1] <= Level)
	{
		loc3 = 1;
	}
	else
	{
		return loc2;
	}

	for(int i = 0;i < loc3;i++)
	{
		if(this->iSphereDropRate[i] >= GetLargeRand()%10000)
		{
			loc2 = i + ITEMGET(12,70);
		}
	}

	return loc2;
}

//00558EE0 - identical
int CSocketOption::GetSocketByteOption(BYTE OptionIndex,BYTE SocketSlotCount)
{
	return SocketSlotCount * 50 + OptionIndex; //SOCKET BYTE ON ITEM BINARY
}

//00558F20 - identical
BYTE CSocketOption::SetSeedSphereData(CSeedSphere * lpSeedSphere,BYTE OptionIndex,BYTE SocketSlotCount)
{
	CSeed * lpSeed = NULL;
	int loc3 = NULL;

	lpSeed = this->GetSeedData(OptionIndex);

	if(lpSeed == NULL)
	{
		return 0;
	}

	if(lpSeedSphere->SetInfo(lpSeed,SocketSlotCount) == 0)
	{
		return 0;
	}

	return 1;
}

//00558FA0 identical
CSeed * CSocketOption::GetSeedData(BYTE OptionIndex)
{
	for (int i = 0; i < MAX_SEED_OPTION; i++ )
	{
		if ( this->SocketSeed[i].m_btOptionIndex == OptionIndex )
		{
			return &this->SocketSeed[i];
		}
	}
	
	return 0;
}

//00559020 - identical
CSphere * CSocketOption::GetSphereData(BYTE level)
{
	for(int i = 0; i < MAX_SOCKET_OPTION; i ++ )
	{
		if(this->SocketSphere[i].m_btItemLevel == level)
		{
			return &this->SocketSphere[i];
		}
	}

	return 0;
}

//005590A0 - identical
BYTE CSocketOption::SortOptionIndex()
{
	int loc2 = 0;

	loc2 = this->SocketRandomPool.GetRandomValue(eRANDOMPOOL_BY_WEIGHT);

	return loc2;
}

//005590E0 - identical
BYTE CSocketOption::GetElementIndex(BYTE index)
{
	BYTE loc2 = 0;
	CSeed * lpSeed = NULL;

	loc2 = index % 50;

	lpSeed = this->GetSeedData(loc2);

	if(lpSeed == NULL)
	{
		return 0;
	}

	return lpSeed->m_btElementIndex;
}

//00559150 - identical
CSocketSphere * CSocketOption::GetSeedSpear(BYTE OptionIndex)
{
	for(int i = 0 ; i < MAX_SPHERE_OPTION; i ++ )
	{
		if(this->SocketSpear[i].m_btOptionIndex == OptionIndex)
		{
			return &this->SocketSpear[i];
		}
	}

	return 0;
}

//005591D0 - identical
int CSocketOption::CalcEquipmentSocketOption(LPOBJ lpObj)
{
	int loc5 = 0;
	BYTE loc6 = 0;
	BYTE loc7 = 0;
	BYTE loc8 = 0;

	CSeedSphere SeedSphere;

	for(int i = 0; i < INVETORY_WEAR_SIZE; i++)
	{
		if(this->IsActive(&lpObj->pInventory[i]) == 0)
		{
			continue;
		}
		
		for(int n = 0; n < MAX_SOCKET_OPTION; n++)
		{
			loc6 = lpObj->pInventory[i].m_SocketOption[n];

			if(loc6 == 0xFF || loc6 == 0xFE)
			{
				continue;
			}

			loc7 = loc6 % 50;
			loc8 = (loc6 - loc7 ) / 50 + 1;

			if(this->SetSeedSphereData(&SeedSphere,loc7,loc8) == 0)
			{
				continue;
			}
			
			this->ApplySocketEffect(lpObj,1,loc7,SeedSphere.m_btOptionType,SeedSphere.m_wSocketSlot);

			loc5++;
		}

	}

	return loc5;
}


//005593D0 - identical
void CSocketOption::SetBonusSocketOption(LPOBJ lpObj)
{
	BYTE loc2 = 0;
	CSocketSphere * lpSeedSpear = NULL;

	for(int i = 0;i < INVETORY_WEAR_SIZE; i ++)
	{
		if(this->IsActive(&lpObj->pInventory[i]) == 0)
		{
			continue;
		}

		loc2 = lpObj->pInventory[i].m_SocketOptionIndex;

		if(loc2 == 0xFF || loc2 == 0xFE)
		{
			continue;
		}

		lpSeedSpear = this->GetSeedSpear(loc2);

		if(lpSeedSpear == NULL)
		{
			continue;
		}

		LogAddTD("[SocketItem] [%s][%s] Set Bonus Socket Option - OptionIndex : %d, EffectType : %d, OptionType : %d, OptionValue : %d",lpObj->AccountID,lpObj->Name,lpSeedSpear->m_btOptionIndex,lpSeedSpear->m_btEffectType,lpSeedSpear->m_btOptionType,lpSeedSpear->m_btOptionValue);

		//							EffectType : %d, OptionType : %d, OptionValue : %d
		this->ApplySocketEffect(lpObj,2,lpSeedSpear->m_btEffectType,lpSeedSpear->m_btOptionType,lpSeedSpear->m_btOptionValue);
	}
}

void CSocketOption::SetFullBonusSocketOption(LPOBJ lpObj) //identical
{
	BYTE loc3[8];
	BYTE loc4 = 0;
	BYTE loc5 = 0;

	memset(&loc3, NULL, sizeof(loc3));

	for(int i = 0;i< 35; i++) //loc6
	{
		loc4 = this->GetElementIndex(lpObj->m_SocketSet[i].m_btEffectType);

		if(loc4 == 0)
		{
			break;
		}

		loc3[loc4-1] += lpObj->m_SocketSet[i].m_btOptionCount;
	}

	for(int n = 0;n< 2; n++) //loc7
	{
		for(int j = 0;j< 6; j++) //loc8
		{
			if(this->SocketBonusOption[n].btElements[j] <= loc3[j])
			{
				loc5++;
			}
		}

		if(loc5 == 6)
		{
			this->ApplySocketEffect(lpObj, 3, this->SocketBonusOption[n].btOption, this->SocketBonusOption[n].btType, this->SocketBonusOption[n].btIncrease);
		}
		loc5 = 0;
	}
}

//005596F0
BYTE CSocketOption::CalCharacterSocketOption(LPOBJ lpObj)
{
	int loc2 = 0;

	if(lpObj == NULL)
	{
		return 0;
	}
	
	if(lpObj->Type != 1 || lpObj->Connected < 3)
	{
		return 0;
	}

	this->ClearEquipmentSocketOption(lpObj);

	loc2 = this->CalcEquipmentSocketOption(lpObj);

	if(loc2 <= 0)
	{
		return 0;
	}
	
	this->SetBonusSocketOption(lpObj);
	this->SetFullBonusSocketOption(lpObj);

	return 1;
}


//00559790 - identical
void CSocketOption::ClearEquipmentSocketOption(LPOBJ lpObj)
{
	if(lpObj == NULL)
	{
		return;
	}

	if(lpObj->Type != 1 || lpObj->Connected < 3)
	{
		return;
	}

	int i = 0;

	for(i = 0;i < 35; i++)
	{
		if(lpObj->m_SocketSet[i].m_btEffectType == 0xFF) 
			break;

		lpObj->m_SocketSet[i].RESET();
	}

	for(i = 0;i < 7; i++)
	{
		if(lpObj->m_SocketWeapon[i].m_btEffectType == 0xFF) 
			break;
		lpObj->m_SocketWeapon[i].RESET();
	}

	for(i = 0;i < 2; i++)
	{
		if(lpObj->m_SocketBonus[i].m_btEffectType == 0xFF) 
			break;

		lpObj->m_SocketBonus[i].RESET();
	}

	lpObj->m_wSocketOpIncLifePower = 0;
	lpObj->m_wSocketOpIncMaxMana = 0;
	lpObj->m_wSocketOpAddLife =0;
	lpObj->m_wSocketOpAddMana =0;
	lpObj->m_btSocketOpDecreaseAG =0;


}

//00559950 - identical	
void CSocketOption::ApplySocketEffect(LPOBJ lpObj,int arg2,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	if(btEffectType >= 0 && btEffectType <= 9)
	{
		this->ApplySocketFireEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 10 && btEffectType <= 15)
	{
		this->ApplySocketWaterEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 16 && btEffectType <= 20)
	{
		this->ApplySocketIceEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 21 && btEffectType <= 28)
	{
		this->ApplySocketWindEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 29 && btEffectType <= 33)
	{
		this->ApplySocketLightningEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 34 && btEffectType <= 40)
	{
		this->ApplySocketEarthEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 41 && btEffectType <= 43)
	{
		this->ApplySocketReservedEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}
	else if(btEffectType >= 44 && btEffectType <= 45)
	{
		this->ApplySocketBonusEffect(lpObj,btEffectType,btOptionType,wOptionValue);
	}

	for(int i = 0;i < 43; i++)
	{
		if(lpObj->m_SocketSet[i].m_btEffectType == btEffectType &&  lpObj->m_SocketSet[i].m_btOptionType == btOptionType)
		{
			lpObj->m_SocketSet[i].m_wOptionValue += wOptionValue;
			lpObj->m_SocketSet[i].m_btOptionCount ++;
			break;
		}
		
		if(lpObj->m_SocketSet[i].m_btEffectType == 0xFF)
		{
			lpObj->m_SocketSet[i].m_btEffectType = btEffectType;
			lpObj->m_SocketSet[i].m_btOptionType = btOptionType;
			lpObj->m_SocketSet[i].m_wOptionValue = wOptionValue;
			lpObj->m_SocketSet[i].m_btOptionCount = 1;
			break;
		}
	}
}

//00559CF0 - identical
void CSocketOption::ApplyTESTSocketEffect()
{

}

//00559D10 - identical
void CSocketOption::ApplySocketFireEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;

	switch(btEffectType)
	{
	case SOCKET_EFFECT_OPADDATTACKPOWER:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMaxLeft,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMaxLeft += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMinLeft,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMinLeft += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMaxRight,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMaxRight += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMinRight,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMinRight += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDamageMin,wOptionValue,btOptionType);
		lpObj->m_MagicDamageMin += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDamageMax,wOptionValue,btOptionType);
		lpObj->m_MagicDamageMax += iIncValue;

		break;
	case SOCKET_EFFECT_OPADDSPEEDPOWER:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackSpeed,wOptionValue,btOptionType);
		lpObj->m_AttackSpeed += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicSpeed,wOptionValue,btOptionType);
		lpObj->m_MagicSpeed += iIncValue;
		break;
	case SOCKET_EFFECT_OPADDMAXDMGWEAPONS:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMaxLeft,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMaxLeft += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMaxRight,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMaxRight += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDamageMax,wOptionValue,btOptionType);
		lpObj->m_MagicDamageMax += iIncValue;
		break;
	case SOCKET_EFFECT_OPADDMINDMGWEAPONS:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMinLeft,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMinLeft += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMinRight,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMinRight += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDamageMin,wOptionValue,btOptionType);
		lpObj->m_MagicDamageMin += iIncValue;
		break;
	case SOCKET_EFFECT_OPADDALLDMGWEAPONS:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMaxLeft,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMaxLeft += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMinLeft,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMinLeft += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMaxRight,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMaxRight += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_AttackDamageMinRight,wOptionValue,btOptionType);
		lpObj->m_AttackDamageMinRight += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDamageMin,wOptionValue,btOptionType);
		lpObj->m_MagicDamageMin += iIncValue;

		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDamageMax,wOptionValue,btOptionType);
		lpObj->m_MagicDamageMax += iIncValue;
		break;
	case SOCKET_EFFECT_OPADDUNK:
		lpObj->m_btSocketOpDecreaseAG += wOptionValue;

		if(lpObj->m_btSocketOpDecreaseAG > 100)
		{
			lpObj->m_btSocketOpDecreaseAG = 100;
		}
		break;
	}

}

//0055A2D0 - identical
void CSocketOption::ApplySocketWaterEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;

	switch(btEffectType)
	{
	case 10:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_SuccessfulBlocking,wOptionValue,btOptionType);
		lpObj->m_SuccessfulBlocking += iIncValue;
		break;
	case 11:
		iIncValue = this->_CalcIncreaseValue(lpObj->m_Defense,wOptionValue,btOptionType);
		lpObj->m_Defense += iIncValue;
		
		iIncValue = this->_CalcIncreaseValue(lpObj->m_MagicDefense,wOptionValue,btOptionType);
		lpObj->m_MagicDefense += iIncValue;
		break;
	case 12:
		lpObj->SetOpImproveSheldDefence += wOptionValue;
		break;
	case 13:
		lpObj->DamageMinus += wOptionValue;
		break;
	case 14:
		lpObj->DamageReflect += wOptionValue;
		break;

	}
}

//0055A460 - identical
void CSocketOption::ApplySocketIceEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;

	switch(btEffectType)
	{
	case 16:
		iIncValue += this->_CalcIncreaseValue((int)lpObj->AddLife + (int)lpObj->MaxLife,wOptionValue,btOptionType);
		lpObj->m_wSocketOpAddLife += iIncValue;
		break;
	case 17:
		iIncValue += this->_CalcIncreaseValue((int)lpObj->AddMana + (int)lpObj->MaxMana,wOptionValue,btOptionType);
		lpObj->m_wSocketOpAddMana += iIncValue;
		break;
	case 18:
		iIncValue = this->_CalcIncreaseValue(lpObj->SetOpAddSkillAttack,wOptionValue,btOptionType);
		lpObj->SetOpAddSkillAttack += iIncValue;
		break;
	case 19:
		lpObj->m_AttackRating += wOptionValue;
		break;
	}
}

//0055A600 - identical
void CSocketOption::ApplySocketWindEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;

	switch(btEffectType)
	{
	case 21:
		iIncValue = this->_CalcIncreaseValue((int)lpObj->AddLife+(int)lpObj->MaxLife,wOptionValue,btOptionType);
		lpObj->m_wSocketOpIncLifePower += iIncValue;
		break;
	case 22:
		iIncValue = this->_CalcIncreaseValue((int)lpObj->AddLife+(int)lpObj->MaxLife,wOptionValue,btOptionType);
		lpObj->AddLife += iIncValue;
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife+lpObj->MaxLife),0xFE,0, (int)(lpObj->iMaxShield+lpObj->iAddShield));
		GCReFillSend(lpObj->m_Index,(int)lpObj->Life,0xFF,0,(int)lpObj->iShield);
		break;
	case 23:
		iIncValue = this->_CalcIncreaseValue((int)lpObj->AddMana+(int)lpObj->MaxMana,wOptionValue,btOptionType);
		lpObj->AddMana += iIncValue;
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana+lpObj->MaxMana),0xFE,0,(int)(lpObj->MaxBP+lpObj->AddBP));
		GCManaSend(lpObj->m_Index,(int)lpObj->Mana,0xFF,0,(int)lpObj->BP);
		break;
	case 24:
		iIncValue = this->_CalcIncreaseValue((int)lpObj->AddMana+(int)lpObj->MaxMana,wOptionValue,btOptionType);
		lpObj->m_wSocketOpIncMaxMana += iIncValue;
		break;
	case 25:
		iIncValue = this->_CalcIncreaseValue(lpObj->MaxBP+lpObj->AddBP,wOptionValue,btOptionType);
		lpObj->AddBP += iIncValue;
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana+lpObj->MaxMana),0xFE,0,(int)(lpObj->MaxBP+lpObj->AddBP));
		GCManaSend(lpObj->m_Index,(int)lpObj->Mana,0xFF,0,(int)lpObj->BP);
		break;
	case 26:
		iIncValue = this->_CalcIncreaseValue(lpObj->SetOpIncAGValue,wOptionValue,btOptionType);
		lpObj->SetOpIncAGValue += iIncValue;
		break;
	case 27:
		lpObj->MonsterDieGetMoney += wOptionValue;
		break;
	}
}

//0055AA30 - identical
void CSocketOption::ApplySocketLightningEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;

	switch(btEffectType)
	{
	case 29:
		iIncValue = this->_CalcIncreaseValue(lpObj->SetOpAddExDamage,wOptionValue,btOptionType);
		lpObj->SetOpAddExDamage += iIncValue;
		break;
	case 30:
		lpObj->m_ExcelentDamage += wOptionValue;
		break;
	case 31:
		iIncValue = this->_CalcIncreaseValue(lpObj->SetOpAddCriticalDamage,wOptionValue,btOptionType);
		lpObj->SetOpAddCriticalDamage += iIncValue;
		break;
	case 32:
		lpObj->m_CriticalDamage += wOptionValue;
		break;
	}
}

//0055AB80 - identical
void CSocketOption::ApplySocketEarthEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;
	
	switch(btEffectType)
	{
	case 34:
		iIncValue = this->_CalcIncreaseValue(lpObj->Strength+lpObj->AddStrength,wOptionValue,btOptionType);
		lpObj->AddStrength += iIncValue;
		break;
	case 35:
		iIncValue = this->_CalcIncreaseValue(lpObj->Dexterity+lpObj->AddDexterity,wOptionValue,btOptionType);
		lpObj->AddDexterity += iIncValue;
		break;
	case 36:
		iIncValue = this->_CalcIncreaseValue(lpObj->Vitality+lpObj->AddVitality,wOptionValue,btOptionType);
		lpObj->AddVitality += iIncValue;
		break;
	case 37:
		iIncValue = this->_CalcIncreaseValue(lpObj->Energy+lpObj->AddEnergy,wOptionValue,btOptionType);
		lpObj->AddEnergy += iIncValue;
		break;
	}
}

//0055AD50 - identical / Reserved Sphere!
void CSocketOption::ApplySocketReservedEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = btEffectType;
}

//0055AD80 - identical - bonus types
void CSocketOption::ApplySocketBonusEffect(LPOBJ lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue)
{
	int iIncValue = 0;
	
	switch(btEffectType)
	{
	case 44:
		lpObj->SetOpDoubleDamage += wOptionValue;
		break;
	case 45:
		lpObj->SetOpIgnoreDefense += wOptionValue;
		break;
	}
}

//0055AE00 - identical
int CSocketOption::_CalcIncreaseValue(int iValue,WORD wOptionValue,BYTE btOptionType)
{
	int iIncValue = 0;

	if(wOptionValue == 0)
	{
		return 0;
	}
	
	switch(btOptionType)
	{
	case 1:iIncValue = wOptionValue;					break;
	case 2:iIncValue = iValue * wOptionValue / 100;		break;
	case 3:iIncValue = iValue / wOptionValue;			break;
	case 4:iIncValue = iValue / wOptionValue;			break;
	case 5:iIncValue = iValue / wOptionValue;			break;
	default: return -1;									break;
	
	}

	return iIncValue;
}


//0055AF10 -identical
void CSocketOption::ApplySocketEffectforWeapons(CItem * lpItem)
{
	if(lpItem == NULL)
	{
		return;
	}

	if(lpItem->IsItem() == FALSE || this->IsSocketOption(lpItem) == FALSE)
	{
		return ;
	}
	
	BYTE loc5 = 0;
	BYTE loc6 = 0;
	BYTE loc7 = 0;
	CSeedSphere SeedSphere;
	int iIncValue = 0;

	for(int i = 0;i < 5; i ++)
	{
		if(lpItem->m_SocketOption[i] == 0xFF || lpItem->m_SocketOption[i] == 0xFE)
		{
			continue;
		}
		
		loc7 = lpItem->m_SocketOption[i];
		loc5 = loc7 % 50;
		loc6 = (loc7 - loc5) / 50 + 1;
		
		if(this->SetSeedSphereData(&SeedSphere,loc5,loc6) == NULL)
		{
			continue;
		}

		if(loc5 == 38)
		{
			iIncValue = this->_CalcIncreaseValue(lpItem->m_HJOpStrength,SeedSphere.m_wSocketSlot,SeedSphere.m_btOptionType);
			lpItem->m_HJOpStrength += iIncValue;
		}

		else if(loc5 == 39)
		{
			iIncValue = this->_CalcIncreaseValue(lpItem->m_HJOpDexterity,SeedSphere.m_wSocketSlot,SeedSphere.m_btOptionType);
			lpItem->m_HJOpDexterity += iIncValue;
		}

		else if(loc5 == 20)
		{
			lpItem->m_SocketBonus += SeedSphere.m_wSocketSlot;
		}
	}
}

//0055B190 - identical
void CSocketOption::ClearSlotOption(CItem * lpItem,BYTE btSocketSlotCount)
{
	lpItem->ClearSocketOption(btSocketSlotCount);
}

//0055B1C0 - identical
BYTE CSocketOption::GetRandomSlotCount(int item_num)
{
	int loc2 = 0;

	if(ItemAttribute[item_num].HaveItemInfo == 1)
	{
		if(ItemAttribute[item_num].TwoHand == 0)
		{
			loc2 = this->SocketSlotRandomPool.GetRandomValue(eRANDOMPOOL_BY_WEIGHT);
		}
		else
		{
			loc2 = this->TwoHandWeaponSocketSlotRandomPool.GetRandomValue(eRANDOMPOOL_BY_WEIGHT);
		}
	}

	return loc2;
}


//0055B250 - identical
void CSocketOption::ClearSocketData(LPOBJ lpObj)
{
	int i = 0;

	if(lpObj == NULL)
	{
		return;
	}

	if(lpObj->Type != 1)
	{
		return;
	}

	for(i = 0;i < 35; i++)
	{
		lpObj->m_SocketSet[i].RESET();
	}

	for(i = 0;i < 7; i++)
	{
		lpObj->m_SocketWeapon[i].RESET();
	}

	for(i = 0;i < 2; i++)
	{
		lpObj->m_SocketBonus[i].RESET();
	}
}

//0055B350 - identical
BYTE CSocketOption::MakeManualOptionbyJewel(CItem *lpFirstItem,CItem *lpSecondItem,BYTE btSocketSlot)
{
	if(lpFirstItem == 0 || lpSecondItem == 0)
	{
		return 0;
	}
	
	if(lpFirstItem->IsItem() == 0 || lpSecondItem->IsItem() == 0 )
	{
		return 0;
	}

	if(this->IsActive(lpFirstItem) == 0)
	{
		return 0;
	}

	if(btSocketSlot > 5)
	{
		return 0;
	}
	
	if(lpFirstItem->m_SocketOption[btSocketSlot] != 0xFE)
	{
		return 0;
	}

	BYTE loc2 = 0;
	BYTE loc3 = 0;
	BYTE loc4 = 0;
	BYTE loc5 = 0;

	loc2 = lpSecondItem->m_Type % 512;
	loc3 = loc2 - 100;
	loc4 = (loc3 - 1) / 6 + 1;
	loc5 = loc4 * 50 + loc3;

	lpFirstItem->m_SocketOption[btSocketSlot] = loc5; //SOCKET BYTE ON ITEM BINARY

	this->ManualSetBonusSocketOption(lpFirstItem);

	return 1;
}

//0055B4D0 - identical
BYTE CSocketOption::MakeManualOptionbyCalc(CItem * lpItem,BYTE arg2,BYTE arg3,BYTE btSocketSlot)
{
	if(lpItem == NULL)
	{
		return 0;
	}

	if(lpItem->IsItem() == FALSE)
	{
		return 0;
	}

	if(this->IsActive(lpItem) == FALSE)
	{
		return 0;
	}

	if(btSocketSlot > 5)
	{
		return 0;
	}

	if(lpItem->m_SocketOption[btSocketSlot] != 0xFE)
	{
		return 0;
	}

	BYTE loc2 = 0;

	loc2 = 50 * arg3 + arg2;

	lpItem->m_SocketOption[btSocketSlot] = loc2; //SOCKET BYTE ON ITEM BINARY

	this->ManualSetBonusSocketOption(lpItem);

	return 1;
}

//0055B5D0 - identical
BYTE CSocketOption::MakeManualOption(CItem * lpItem,BYTE arg2,BYTE btSocketSlot)
{
	if(lpItem == NULL)
	{
		return 0;
	}

	if(lpItem->IsItem() == FALSE)
	{
		return 0;
	}

	if(this->IsActive(lpItem) == FALSE)
	{
		return 0;
	}

	if(btSocketSlot > 5)
	{
		return 0;
	}

	if(lpItem->m_SocketOption[btSocketSlot] != 0xFE)
	{
		return 0;
	}

	lpItem->m_SocketOption[btSocketSlot] = arg2;

	this->ManualSetBonusSocketOption(lpItem);

	return 1;
}


//0055B6A0 - identical
BYTE CSocketOption::ManualSetBonusSocketOption(CItem * lpItem)
{
	BYTE btSocketOption[5];

	if(lpItem == NULL)
	{
		return 0;
	}

	if(lpItem->IsItem() == FALSE || this->IsActive(lpItem) == FALSE)
	{
		return 0;
	}
	
	for(int n = 0; n < 5; n++)
	{
		if(lpItem->m_SocketOption[n] != 0xFF && lpItem->m_SocketOption[n] != 0xFE)
		{
			btSocketOption[n] = this->GetElementIndex(lpItem->m_SocketOption[n]);
		}
	}

	BYTE loc5 = 0;
	WORD loc6 = 0;
	BYTE loc7 = 0;
	
	loc6 = lpItem->m_Type % 512;
	loc5 = (lpItem->m_Type - loc6) / 512;

	for(int i = 0; i < 6; i++)
	{
		if(loc5 >= this->SocketSpear[i].m_btElementIndex && loc5 <= this->SocketSpear[i].m_btElementType)
		{
			for(int j = 0;j < 5;j++)
			{
				if(this->SocketSpear[i].m_btSocketSlot[j] == btSocketOption[j] && btSocketOption[j] != 0)
				{
					loc7++;
				}

				if(loc7 >= this->SocketSpear[i].m_btSocketSlotCount)
				{
					if(rand() % 100 < this->SocketSpear[i].m_iOptionRate)
					{
						lpItem->m_SocketOptionIndex = this->SocketSpear[i].m_btOptionIndex;
						
						LogAddTD("[SocketItem] Set Bonus Socket Option Success - OptionIndex : %d, ItemCode : %d, SocketOption[%d,%d,%d,%d,%d]", 
							lpItem->m_SocketOptionIndex,lpItem->m_Type,
							lpItem->m_SocketOption[0],
							lpItem->m_SocketOption[1],
							lpItem->m_SocketOption[2],
							lpItem->m_SocketOption[3],
							lpItem->m_SocketOption[4]);

						return 1;
					}
					
					lpItem->m_SocketOptionIndex = 0xFF;

					return 0;
				}
			}

			loc7 = 0;
		}
	}

	lpItem->m_SocketOptionIndex = 0xFF;

	return 0;
}

//0055B9E0 - identical
BYTE CSocketOption::RemakeSocketOption(CItem *lpItem,BYTE btSlotIndex)
{
	if(lpItem == NULL)
	{
		return 0;
	}
	
	if(this->IsActive(lpItem) == FALSE)
	{
		return 0;
	}

	if(btSlotIndex > 5)
	{
		return 0;
	}

	if(lpItem->m_SocketOption[btSlotIndex] == 0xFF || lpItem->m_SocketOption[btSlotIndex] == 0xFE)
	{
		return 0;
	}

	lpItem->m_SocketOption[btSlotIndex] = 0xFE;

	this->ManualSetBonusSocketOption(lpItem);

	return 1;
}

//0055BAC0 -identical
void SOCKET_ITEM::RESET()
{
	this->m_btEffectType = 0xFF;
	this->m_wOptionValue = 0;
	this->m_btOptionType = 0;
	this->m_btOptionCount = 0;
}