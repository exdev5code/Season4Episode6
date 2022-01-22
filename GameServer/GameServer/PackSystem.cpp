#include "StdAfx.h"

#ifdef PACK_SYSTEM

#include "PackSystem.h"
#include "Functions.h"
#include "user.h"
#include "Message.h"
#include "DSProtocol.h"
#include "logproc.h"


cPackSystem gPackSystem;

void cPackSystem::Load()
{
	this->Enable   = GetPrivateProfileInt("Common","Enable",0,PACK_SYSTEM_DIR);
	this->MixCount = GetPrivateProfileInt("Common","MixCount",10,PACK_SYSTEM_DIR);
}

void cPackSystem::ChatOperation(int aIndex, LPBYTE Protocol)
{
	LPOBJ lpObj = &gObj[aIndex];

	char PackChaos[]	= "/pack chaos";
	if(!memcmp(&Protocol[13],PackChaos,strlen(PackChaos)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(12,15),0) < this->MixCount))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to pack");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(12,15),0,this->MixCount);
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,210),0,0,0,0,0,aIndex,0,0);
		MsgNormal(aIndex,"[Pack] Jewels packed");
	}

	char UnPackChaos[]	= "/unpack chaos";
	if(!memcmp(&Protocol[13],UnPackChaos,strlen(UnPackChaos)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,210),0) < 1))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to unpack");
			return;
		}
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( lpObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if ( iEmptyCount < this->MixCount )
		{
			MsgNormal(aIndex,"[Pack] You dont have inventory space");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,210),0,1);
		for(int i=0;i<this->MixCount;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(12,15),0,0,0,0,0,aIndex,0,0);
		}
		MsgNormal(aIndex,"[Pack] Jewels Un packed");
	}

	// ---------------------------------------------------------------------------------------------

	char PackCreation[]	= "/pack creation";
	if(!memcmp(&Protocol[13],PackCreation,strlen(PackCreation)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,22),0) < this->MixCount))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to pack");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,22),0,this->MixCount);
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,211),0,0,0,0,0,aIndex,0,0);
		MsgNormal(aIndex,"[Pack] Jewels packed");
	}

	char UnPackCreation[]	= "/unpack creation";
	if(!memcmp(&Protocol[13],UnPackCreation,strlen(UnPackCreation)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,211),0) < 1))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to unpack");
			return;
		}
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( lpObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if ( iEmptyCount < this->MixCount )
		{
			MsgNormal(aIndex,"[Pack] You dont have inventory space");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,211),0,1);
		for(int i=0;i<this->MixCount;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,22),0,0,0,0,0,aIndex,0,0);
		}
		MsgNormal(aIndex,"[Pack] Jewels Un packed");
	}

	// ---------------------------------------------------------------------------------------------

	char PackGuardian[]	= "/pack guardian";
	if(!memcmp(&Protocol[13],PackGuardian,strlen(PackGuardian)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,31),0) < this->MixCount))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to pack");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,31),0,this->MixCount);
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,212),0,0,0,0,0,aIndex,0,0);
		MsgNormal(aIndex,"[Pack] Jewels packed");
	}

	char UnPackGuardian[]	= "/unpack guardian";
	if(!memcmp(&Protocol[13],UnPackGuardian,strlen(UnPackGuardian)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,212),0) < 1))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to unpack");
			return;
		}
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( lpObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if ( iEmptyCount < this->MixCount )
		{
			MsgNormal(aIndex,"[Pack] You dont have inventory space");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,212),0,1);
		for(int i=0;i<this->MixCount;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,31),0,0,0,0,0,aIndex,0,0);
		}
		MsgNormal(aIndex,"[Pack] Jewels Un packed");
	}

	// ---------------------------------------------------------------------------------------------

	char PackLife[]	= "/pack life";
	if(!memcmp(&Protocol[13],PackLife,strlen(PackLife)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,16),0) < this->MixCount))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to pack");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,16),0,this->MixCount);
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,213),0,0,0,0,0,aIndex,0,0);
		MsgNormal(aIndex,"[Pack] Jewels packed");
	}

	char UnPackLife[]	= "/unpack life";
	if(!memcmp(&Protocol[13],UnPackLife,strlen(UnPackLife)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,213),0) < 1))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to unpack");
			return;
		}
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( lpObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if ( iEmptyCount < this->MixCount )
		{
			MsgNormal(aIndex,"[Pack] You dont have inventory space");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,213),0,1);
		for(int i=0;i<this->MixCount;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,16),0,0,0,0,0,aIndex,0,0);
		}
		MsgNormal(aIndex,"[Pack] Jewels Un packed");
	}

	// ---------------------------------------------------------------------------------------------

	char PackHarmony[]	= "/pack harmony";
	if(!memcmp(&Protocol[13],PackHarmony,strlen(PackHarmony)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,42),0) < this->MixCount))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to pack");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,42),0,this->MixCount);
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,214),0,0,0,0,0,aIndex,0,0);
		MsgNormal(aIndex,"[Pack] Jewels packed");
	}

	char UnPackHarmony[]	= "/unpack harmony";
	if(!memcmp(&Protocol[13],UnPackHarmony,strlen(UnPackHarmony)))
	{
		if((gObjGetItemCountInInventory(aIndex,ITEMGET(14,214),0) < 1))
		{
			MsgNormal(aIndex,"[Pack] You dont have jewels to unpack");
			return;
		}
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( lpObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if ( iEmptyCount < this->MixCount )
		{
			MsgNormal(aIndex,"[Pack] You dont have inventory space");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,214),0,1);
		for(int i=0;i<this->MixCount;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,42),0,0,0,0,0,aIndex,0,0);
		}
		MsgNormal(aIndex,"[Pack] Jewels Un packed");
	}

	// --------------------------------------------------------------------------------------------
}

#endif