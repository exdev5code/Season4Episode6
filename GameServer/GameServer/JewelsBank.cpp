#include "StdAfx.h"
#include "JewelsBank.h"
#include "user.h"
#include "Message.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "ExUser.h"

#if(_JEWELS_BANK_)

JewelsBank gJewelsBank;

void JewelsBank::Load()
{
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",1,JEWELSBANK_DIR); 
}

void JewelsBank::sendchaosbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(12,15),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Chaos",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(12,15),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->ChaosBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Send %d Chaos",Count);
}

void JewelsBank::sendblessbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,13),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Bless",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,13),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->BlessBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Send %d Bless",Count);
}

void JewelsBank::sendsoulbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,14),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Soul",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,14),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->SoulBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Send %d Soul",Count);
}

void JewelsBank::sendlifebank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,16),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Life",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,16),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->LifeBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Send %d Life",Count);
}

//-----------------------------------------------------

void JewelsBank::recvchaosbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->ChaosBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Chaos",Count);
		return;
	}

	//if(CheckInventoryEmptySpace(lpObj,4,2) == false )
	if(EmptyPointInventory(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->ChaosBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(12,15),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Recv %d Chaos",Count);
}

void JewelsBank::recvblessbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->BlessBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Bless",Count);
		return;
	}
	if(EmptyPointInventory(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->BlessBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,13),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Recv %d Bless",Count);
}

void JewelsBank::recvsoulbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->SoulBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Soul",Count);
		return;
	}
	if(EmptyPointInventory(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->SoulBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,14),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Recv %d Soul",Count);
}

void JewelsBank::recvlifebank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LifeBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Life",Count);
		return;
	}
	if(EmptyPointInventory(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->LifeBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,16),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,"[JewelsBank] Recv %d Life",Count);
}

#endif