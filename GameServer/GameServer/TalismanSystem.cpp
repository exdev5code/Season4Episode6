#include "stdafx.h"
#ifdef TALISMAN_SYSTEM
#include "USER.h"
#include "TalismanSystem.h"
#include "Functions.h"

cTalismanSystem TalismanSystem;

void cTalismanSystem::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,TALISMANSYSTEM_DIR);

	this->TalismanOfDamage = GetPrivateProfileInt("Talisman","TalismanOfDamage",10,TALISMANSYSTEM_DIR);
	this->TalismanOfDefence = GetPrivateProfileInt("Talisman","TalismanOfDefence",10,TALISMANSYSTEM_DIR);
	this->TalismanOfDouble = GetPrivateProfileInt("Talisman","TalismanOfDouble",3,TALISMANSYSTEM_DIR);
	this->TalismanOfExellent = GetPrivateProfileInt("Talisman","TalismanOfExellent",5,TALISMANSYSTEM_DIR);
	this->TalismanOfCritical = GetPrivateProfileInt("Talisman","TalismanOfCritical",5,TALISMANSYSTEM_DIR);
	this->TalismanOfExperience = GetPrivateProfileInt("Talisman","TalismanOfExperience",10,TALISMANSYSTEM_DIR);
	this->TalismanOfIgnore = GetPrivateProfileInt("Talisman","TalismanOfIgnore",3,TALISMANSYSTEM_DIR);
	this->TalismanOfReflect = GetPrivateProfileInt("Talisman","TalismanOfReflect",5,TALISMANSYSTEM_DIR);
}

void cTalismanSystem::Main(int aIndex)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,200),0) > 0)	//Talisman Of Damage
	{
		lpObj->m_AttackDamageMaxLeft +=  (( lpObj->m_AttackDamageMaxLeft * this->TalismanOfDamage ) / 100 );
		lpObj->m_AttackDamageMinLeft +=  (( lpObj->m_AttackDamageMinLeft * this->TalismanOfDamage ) / 100 );
		lpObj->m_AttackDamageMaxRight += (( lpObj->m_AttackDamageMaxRight* this->TalismanOfDamage ) / 100 );
		lpObj->m_AttackDamageMinRight += (( lpObj->m_AttackDamageMinRight* this->TalismanOfDamage ) / 100 );

		lpObj->m_MagicDamageMax += (( gObj->m_MagicDamageMax * this->TalismanOfDamage ) / 100 );
		lpObj->m_MagicDamageMin += (( gObj->m_MagicDamageMin * this->TalismanOfDamage ) / 100 );
	}
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,201),0) > 0)	//Talisman Of Defence
	{
		lpObj->m_Defense += (( lpObj->m_Defense * this->TalismanOfDefence) / 100 );
		lpObj->m_MagicDefense += ((lpObj->m_MagicDefense * this->TalismanOfDefence) / 100 );
	}
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,202),0) > 0)	//Talisman Of Double
	{
		lpObj->SetOpDoubleDamage += this->TalismanOfDouble;
	}
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,203),0) > 0)	//Talisman Of Exellent
	{
		lpObj->m_ExcelentDamage += this->TalismanOfExellent;
	}
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,204),0) > 0)	//Talisman Of Critical
	{
		lpObj->m_CriticalDamage += this->TalismanOfCritical;
	}
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,206),0) > 0)	//Talisman Of Ignore
	{
		lpObj->SetOpIgnoreDefense += this->TalismanOfIgnore;
	}
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,207),0) > 0)	//Talisman Of Reflect
	{
		lpObj->DamageReflect += this->TalismanOfReflect;
	}
}

void cTalismanSystem::MainExperience(int aIndex,__int64 & Experience)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,205),0) > 0)	//Talisman Of Experience
	{
		LPOBJ lpObj = &gObj[aIndex];
		int Bonus = (Experience * this->TalismanOfExperience) / 100;
		Experience += Bonus;
		lpObj->Experience += Bonus;
	}
}
#endif