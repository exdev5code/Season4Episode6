#include "StdAfx.h"
#include "SystemOfRage.h"
#include "logproc.h"
#include "ObjUseSkill.h"
#include "ObjCalCharacter.h"
#include "giocp.h"
#include "Message.h"
#include "..\include\ReadScript.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "gObjMonster.h"
#include "ConnectEx.h"
#ifdef _SYSTEM_OF_RAGE_

cSystemOfRage gSystemOfRage;

void cSystemOfRage::LoadSkill(int ID, char *cName, int a1, int a2, int NextPoint, bool Percent)
{
	strcpy(this->rSkill[ID].Name,cName);
	this->rSkill[ID].StartDamage = a1;
	this->rSkill[ID].MaxPoint = a2;
	this->rSkill[ID].PointNext = NextPoint;
	this->rSkill[ID].Percent = Percent;
}

void cSystemOfRage::Load()
{
	this->Enable = true;

	ZeroMemory(&this->rUser,sizeof(this->rUser));

	SMDFile = fopen(RAGE_SYSTEM_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,RAGE_SYSTEM_DIR,"CRITICAL ERROR",0);
		this->Enable = false;
		return;
	}

	int Token;
	int type = -1;

	int sNum = 1;
	int lNum = 1;

	while ( true )
	{
	    Token = GetToken();

        if( Token == END)
		{
            break;
		}

		type = (int)TokenNumber;

		while ( true )
		{
			if(type == 0)
			{
				Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					break;
				}

				this->Enable = TokenNumber;

				Token = GetToken();
				this->AddExp = TokenNumber;

				Token = GetToken();
				this->CreateMob = TokenNumber;

				Token = GetToken();
				this->MaxLevel = TokenNumber;

				Token = GetToken();
				this->rPointLvl = TokenNumber;

				Token = GetToken();
				this->NextExp = TokenNumber;

				Token = GetToken();
				this->MobExpLvL = TokenNumber;
			}	
			else if(type == 1)
			{
				Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					break;
				}

				this->TeleportMap = TokenNumber;

				Token = GetToken();
				this->TeleportX = TokenNumber;

				Token = GetToken();
				this->TeleportY = TokenNumber;
			}
			else if(type == 2)
			{
				Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					break;
				}

				if(sNum >= R_MAX_SKILL)
				{
					break;
				}

				int sN = TokenNumber;

				char sName[50];
				Token = GetToken();
				strcpy(sName, TokenString );

				Token = GetToken();
				int Damage = TokenNumber;

				Token = GetToken();
				int MaxPoint = TokenNumber;

				Token = GetToken();
				int NextPoint = TokenNumber;

				Token = GetToken();
				int sProc = TokenNumber;

				this->LoadSkill(sN, sName,Damage,MaxPoint,NextPoint,(bool)sProc);

				sNum++;
			}
		}
    }

	fclose(SMDFile);
}

void cSystemOfRage::FilterSkill(int aIndex, int SkillID)
{
	switch(SkillID)
	{
	case eSkill1:  this->rUser[aIndex].Damage++;		break;
	case eSkill2:  this->rUser[aIndex].FreePoints++;		break;
	case eSkill3:  this->rUser[aIndex].SummonPet++;		break;
	case eSkill4:  this->rUser[aIndex].WingsDamagePlus++;		break;
	case eSkill5:  this->rUser[aIndex].FinalMana++;		break;
	case eSkill6:  this->rUser[aIndex].IgnoreDefence++;		break;
	case eSkill7:  this->rUser[aIndex].ResetLevel++;		break;
	case eSkill8:  this->rUser[aIndex].Teleport++;		break;
	case eSkill9:  this->rUser[aIndex].CriticalDamageRate++;		break;
	case eSkill10: this->rUser[aIndex].AbsordDamage++;	break;
	case eSkill11: this->rUser[aIndex].PetDamageBonus++;	break;
	case eSkill12: this->rUser[aIndex].FinalLife++;	break;
	case eSkill13: this->rUser[aIndex].Strength++;	break;
	case eSkill14: this->rUser[aIndex].DefenceRate++;	break;
	case eSkill15: this->rUser[aIndex].FireDamage++;	break;
	case eSkill16: this->rUser[aIndex].Energy++;	break;
	case eSkill17: this->rUser[aIndex].Agility++;	break;
	case eSkill18: this->rUser[aIndex].DoubleDamage++;	break;
	case eSkill19: this->rUser[aIndex].FinalSD++;	break;
	case eSkill20: this->rUser[aIndex].FinalDefence++;	break;
	case eSkill21: this->rUser[aIndex].ZenDrop++;	break;
	case eSkill22: this->rUser[aIndex].GuildBonus++;	break;
	case eSkill23: this->rUser[aIndex].ReflectDamage++;	break;
	case eSkill24: this->rUser[aIndex].ExellentDamageRate++;	break;
	case eSkill25: this->rUser[aIndex].PvPBonusPlus++;	break;
	case eSkill26: this->rUser[aIndex].MinDefence++;	break;
	case eSkill27: this->rUser[aIndex].Experience++;	break;
	case eSkill28: this->rUser[aIndex].StartSD++;	break;
	case eSkill29: this->rUser[aIndex].PartyBonus++;	break;
	case eSkill30: this->rUser[aIndex].IceDamage++;	break;
	case eSkill31: this->rUser[aIndex].DistanceAttack++;	break;
	case eSkill32: this->rUser[aIndex].AttackRate++;	break;
	case eSkill33: this->rUser[aIndex].WeaponBonus++;	break;
	case eSkill34: this->rUser[aIndex].ExellentDamage++;	break;
	case eSkill35: this->rUser[aIndex].CriticalDamage++;	break;
	}

	//LPOBJ lpObj =&gObj[aIndex];
	//if(SkillID == eSkill2)
	//{
	//	lpObj->LevelUpPoint += this->rSkill[eSkill2].StartDamage; 
	//	//lpObj->ExFreePoints += this->rSkill[eSkill2].StartDamage;
	//	ExUser[aIndex].ExFreePoints += this->rSkill[eSkill2].StartDamage;
	//}
}

int cSystemOfRage::ReturnPoint(int aIndex, int SkillID)
{
	switch(SkillID)
	{
	case eSkill1:  return this->rUser[aIndex].Damage;		break;
	case eSkill2:  return this->rUser[aIndex].FreePoints;		break;
	case eSkill3:  return this->rUser[aIndex].SummonPet;		break;
	case eSkill4:  return this->rUser[aIndex].WingsDamagePlus;		break;
	case eSkill5:  return this->rUser[aIndex].FinalMana;		break;
	case eSkill6:  return this->rUser[aIndex].IgnoreDefence;		break;
	case eSkill7:  return this->rUser[aIndex].ResetLevel;		break;
	case eSkill8:  return this->rUser[aIndex].Teleport;		break;
	case eSkill9:  return this->rUser[aIndex].CriticalDamageRate;		break;
	case eSkill10: return this->rUser[aIndex].AbsordDamage;	break;
	case eSkill11: return this->rUser[aIndex].PetDamageBonus;	break;
	case eSkill12: return this->rUser[aIndex].FinalLife;	break;
	case eSkill13: return this->rUser[aIndex].Strength;	break;
	case eSkill14: return this->rUser[aIndex].DefenceRate;	break;
	case eSkill15: return this->rUser[aIndex].FireDamage;	break;
	case eSkill16: return this->rUser[aIndex].Energy;	break;
	case eSkill17: return this->rUser[aIndex].Agility;	break;
	case eSkill18: return this->rUser[aIndex].DoubleDamage;	break;
	case eSkill19: return this->rUser[aIndex].FinalSD;	break;
	case eSkill20: return this->rUser[aIndex].FinalDefence;	break;
	case eSkill21: return this->rUser[aIndex].ZenDrop;	break;
	case eSkill22: return this->rUser[aIndex].GuildBonus;	break;
	case eSkill23: return this->rUser[aIndex].ReflectDamage;	break;
	case eSkill24: return this->rUser[aIndex].ExellentDamageRate;	break;
	case eSkill25: return this->rUser[aIndex].PvPBonusPlus;	break;
	case eSkill26: return this->rUser[aIndex].MinDefence;	break;
	case eSkill27: return this->rUser[aIndex].Experience;	break;
	case eSkill28: return this->rUser[aIndex].StartSD;	break;
	case eSkill29: return this->rUser[aIndex].PartyBonus;	break;
	case eSkill30: return this->rUser[aIndex].IceDamage;	break;
	case eSkill31: return this->rUser[aIndex].DistanceAttack;	break;
	case eSkill32: return this->rUser[aIndex].AttackRate;	break;
	case eSkill33: return this->rUser[aIndex].WeaponBonus;	break;
	case eSkill34: return this->rUser[aIndex].ExellentDamage;	break;
	case eSkill35: return this->rUser[aIndex].CriticalDamage;	break;
	}
	CloseClient(aIndex);
	return -1;
}

int cSystemOfRage::ReturnCalc(int aIndex, int SkillID, int Pw)
{
	int Result = 0;
	switch(SkillID)
	{
	case eSkill1:  Result = this->rUser[aIndex].Damage * this->rSkill[SkillID].StartDamage;		break;
	case eSkill2:  Result = this->rUser[aIndex].FreePoints * this->rSkill[SkillID].StartDamage;		break;
	case eSkill3:  Result = this->rUser[aIndex].SummonPet * this->rSkill[SkillID].StartDamage;		break;
	case eSkill4:  Result = this->rUser[aIndex].WingsDamagePlus * this->rSkill[SkillID].StartDamage;		break;
	case eSkill5:  Result = this->rUser[aIndex].FinalMana * this->rSkill[SkillID].StartDamage;		break;
	case eSkill6:  Result = this->rUser[aIndex].IgnoreDefence * this->rSkill[SkillID].StartDamage;		break;
	case eSkill7:  Result = this->rUser[aIndex].ResetLevel * this->rSkill[SkillID].StartDamage;		break;
	case eSkill8:  Result = this->rUser[aIndex].Teleport * this->rSkill[SkillID].StartDamage;		break;
	case eSkill9:  Result = this->rUser[aIndex].CriticalDamageRate * this->rSkill[SkillID].StartDamage;		break;
	case eSkill10: Result = this->rUser[aIndex].AbsordDamage * this->rSkill[SkillID].StartDamage;	break;
	case eSkill11: Result = this->rUser[aIndex].PetDamageBonus * this->rSkill[SkillID].StartDamage;	break;
	case eSkill12: Result = this->rUser[aIndex].FinalLife * this->rSkill[SkillID].StartDamage;	break;
	case eSkill13: Result = this->rUser[aIndex].Strength * this->rSkill[SkillID].StartDamage;	break;
	case eSkill14: Result = this->rUser[aIndex].DefenceRate * this->rSkill[SkillID].StartDamage;	break;
	case eSkill15: Result = this->rUser[aIndex].FireDamage * this->rSkill[SkillID].StartDamage;	break;
	case eSkill16: Result = this->rUser[aIndex].Energy * this->rSkill[SkillID].StartDamage;	break;
	case eSkill17: Result = this->rUser[aIndex].Agility * this->rSkill[SkillID].StartDamage;	break;
	case eSkill18: Result = this->rUser[aIndex].DoubleDamage * this->rSkill[SkillID].StartDamage;	break;
	case eSkill19: Result = this->rUser[aIndex].FinalSD * this->rSkill[SkillID].StartDamage;	break;
	case eSkill20: Result = this->rUser[aIndex].FinalDefence * this->rSkill[SkillID].StartDamage;	break;
	case eSkill21: Result = this->rUser[aIndex].ZenDrop * this->rSkill[SkillID].StartDamage;	break;
	case eSkill22: Result = this->rUser[aIndex].GuildBonus * this->rSkill[SkillID].StartDamage;	break;
	case eSkill23: Result = this->rUser[aIndex].ReflectDamage * this->rSkill[SkillID].StartDamage;	break;
	case eSkill24: Result = this->rUser[aIndex].ExellentDamageRate * this->rSkill[SkillID].StartDamage;	break;
	case eSkill25: Result = this->rUser[aIndex].PvPBonusPlus * this->rSkill[SkillID].StartDamage;	break;
	case eSkill26: Result = this->rUser[aIndex].MinDefence * this->rSkill[SkillID].StartDamage;	break;
	case eSkill27: Result = this->rUser[aIndex].Experience * this->rSkill[SkillID].StartDamage;	break;
	case eSkill28: Result = this->rUser[aIndex].StartSD * this->rSkill[SkillID].StartDamage;	break;
	case eSkill29: Result = this->rUser[aIndex].PartyBonus * this->rSkill[SkillID].StartDamage;	break;
	case eSkill30: Result = this->rUser[aIndex].IceDamage * this->rSkill[SkillID].StartDamage;	break;
	case eSkill31: Result = this->rUser[aIndex].DistanceAttack * this->rSkill[SkillID].StartDamage;	break;
	case eSkill32: Result = this->rUser[aIndex].AttackRate * this->rSkill[SkillID].StartDamage;	break;
	case eSkill33: Result = this->rUser[aIndex].WeaponBonus * this->rSkill[SkillID].StartDamage;	break;
	case eSkill34: Result = this->rUser[aIndex].ExellentDamage * this->rSkill[SkillID].StartDamage;	break;
	case eSkill35: Result = this->rUser[aIndex].CriticalDamage * this->rSkill[SkillID].StartDamage;	break;
	}

	if(Pw > 0)
	{
		return ( Result * Pw ) / 100;
	}
	else if(this->rSkill[SkillID].Percent == true)
	{
		return ( Result * 100 ) / 100;
	}
	else
	{
		return Result;
	}
}

void cSystemOfRage::DataRecv(ClickSend *aRecv, int aIndex)
{
	int iSkill = aRecv->SkillID;

	if(this->rUser[aIndex].rPoints > 0 && this->rSkill[iSkill].MaxPoint > this->ReturnPoint(aIndex,iSkill))
	{
		this->rUser[aIndex].rPoints--;
		this->FilterSkill(aIndex,iSkill);

		ClickSend rSend;
		rSend.h.set((LPBYTE)&rSend, 0xFB, 1, sizeof(rSend));
		rSend.Click = 1;
		rSend.SkillID = aRecv->SkillID;
		DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
		gObjCalCharacter(aIndex);
		this->SendSaveData(aIndex);
	}
	else
	{
		CloseClient(aIndex);
	}
}

void cSystemOfRage::CalcCharacter(int aIndex)
{
	if(!Enable)return;
	LPOBJ lpObj = &gObj[aIndex];
	//Damage
	lpObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill1,0);	// 6
	lpObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill1,0);// 4
	lpObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill1,0);	// 6
	lpObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill1,0);	// 4
	lpObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill1,0);
	lpObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill1,0);
	//WingsDamagePlus
	if(gObjWingSprite(lpObj))
	{
		lpObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill4,0);
		lpObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill4,0);
		lpObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill4,0);
		lpObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill4,0);
		lpObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill4,0);
		lpObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill4,0);
	}
	//FinalMana
	lpObj->AddMana +=  this->ReturnCalc(aIndex, eSkill5,(lpObj->Mana));
	//IgnoreDefence
	lpObj->SetOpIgnoreDefense += this->ReturnCalc(aIndex, eSkill6,0);
	if(lpObj->SetOpIgnoreDefense>90)
	{
		lpObj->SetOpIgnoreDefense = 90;
	}
	//CriticalDamageRate
	lpObj->m_CriticalDamage += this->ReturnCalc(aIndex, eSkill9,0);
	if(lpObj->m_CriticalDamage>90)
	{
		lpObj->m_CriticalDamage = 90;
	}
	//AbsordDamage
	lpObj->DamageMinus += this->ReturnCalc(aIndex, eSkill10,0);	//DeBug Error Fix
	if(lpObj->DamageMinus > 50)
	{
		lpObj->DamageMinus = 50;
	}
	//PetDamageBonus
	if(lpObj->pInventory[8].IsItem())
	{
		lpObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill11,0);
		lpObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill11,0);
		lpObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill11,0);
		lpObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill11,0);
		lpObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill11,0);
		lpObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill11,0);
	}
	//FinalLife
	lpObj->AddLife +=  this->ReturnCalc(aIndex, eSkill12,(lpObj->Life));
	//DoubleDamage
	lpObj->SetOpDoubleDamage +=  this->ReturnCalc(aIndex, eSkill18,0);
	//FinalSD
	lpObj->iAddShield += this->ReturnCalc(aIndex, eSkill19,(lpObj->iAddShield+lpObj->iAddShield));
	//FinalDefence
	lpObj->m_Defense += this->ReturnCalc(aIndex, eSkill20,lpObj->m_Defense);

	//GuildBonus
	if ( lpObj->GuildNumber > 0 )
	{
		lpObj->AddLife += this->ReturnCalc(aIndex, eSkill22,0);
		lpObj->m_Defense += this->ReturnCalc(aIndex, eSkill22,0);
	}
	//ReflectDamage
	lpObj->DamageReflect += this->ReturnCalc(aIndex, eSkill23,0);
	if(lpObj->DamageReflect>90)
	{
		lpObj->DamageReflect = 90;
	}
	//MinDefence
	lpObj->m_Defense += this->ReturnCalc(aIndex, eSkill26,0);
	//StartSD
	lpObj->iAddShield += this->ReturnCalc(aIndex, eSkill28,0);
	//PartyBonus
	if(lpObj->PartyNumber >= 0)
	{
		lpObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill29,0);
		lpObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill29,0);
		lpObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill29,0);
		lpObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill29,0);
		lpObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill29,0);
		lpObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill29,0);
		lpObj->AddLife += this->ReturnCalc(aIndex, eSkill29,0);
	}
	//WeaponBonus
	if(lpObj->pInventory[0].IsItem() || lpObj->pInventory[1].IsItem())
	{
		lpObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill33,0);
		lpObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill33,0);
		lpObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill33,0);
		lpObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill33,0);
		lpObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill33,0);
		lpObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill33,0);
	}
	//ExellentDamageRate
	lpObj->m_ExcelentDamage += this->ReturnCalc(aIndex, eSkill24,0);		
	if(lpObj->m_ExcelentDamage>90)
	{
		lpObj->m_ExcelentDamage = 90;
	}
	//Fix Debug
	//Strength
	lpObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill13,0);
	lpObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill13,0);
	lpObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill13,0);
	lpObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill13,0);
	//if(SkillID == eSkill13)
	//{
	//	lpObj->Strength += this->rSkill[SkillID].StartDamage;
	//}
	////Energy
	lpObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill16,0);
	lpObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill16,0);
	//if(SkillID == eSkill16)
	//{
	//	lpObj->Energy += this->rSkill[SkillID].StartDamage;
	//}
	////Agility
	if(lpObj->pInventory[1].m_Type >= ITEMGET(6,0) && lpObj->pInventory[1].m_Type <= ITEMGET(6,255))
	{
		lpObj->m_Defense += this->ReturnCalc(aIndex, eSkill17,0);
	}
}

void cSystemOfRage::SummonPetSkill(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	gObjUseSkill.SkillMonsterCall(lpObj->m_Index,this->CreateMob,lpObj->X-1,lpObj->Y+1);

	int mIndex = gObj[aIndex].m_RecallMon;
	LPOBJ mObj = &gObj[mIndex];

	mObj->m_AttackDamageMin += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_AttackDamageMax += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_AttackDamageMinRight += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_AttackDamageMaxRight += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_AttackDamageMinLeft += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_AttackDamageMaxLeft += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_MagicDamageMin += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_MagicDamageMax += this->ReturnCalc(aIndex, eSkill3,0);
	mObj->m_Defense += this->ReturnCalc(aIndex, eSkill3,0);
}

void cSystemOfRage::TeleportSkill(int aIndex)
{
	gObjTeleport(aIndex, this->TeleportMap, this->TeleportX, this->TeleportY);
}

void cSystemOfRage::CalcStats(int aIndex)
{
	//LPOBJ lpObj = &gObj[aIndex];
	////Strength
	//lpObj->AddStrength += this->ReturnCalc(aIndex, eSkill13,0);
	////Energy
	//lpObj->AddEnergy += this->ReturnCalc(aIndex, eSkill16,0);
	////Agility
	//lpObj->AddDexterity += this->ReturnCalc(aIndex, eSkill17,0);
}

void cSystemOfRage::DropZen (int aIndex, float & money)
{
	if(!this->Enable) return;

	money += this->ReturnCalc(aIndex, eSkill17,0);
}

void cSystemOfRage::ExpFunction(int aIndex, __int64 & exp)
{
	exp += this->ReturnCalc(aIndex, eSkill27,0);
}

void cSystemOfRage::AttackDefenceRate(int aIndex, int Target, float &Attack, float &Defence)
{
	Attack += this->ReturnCalc(aIndex, eSkill32,0);
	Defence += this->ReturnCalc(Target, eSkill14,0);
}

void cSystemOfRage::ExlCritDamage(int aIndex, int effect, int &AttackDamage)
{
	if(effect == 2)//Exl Damage
	{
		AttackDamage += this->ReturnCalc(aIndex, eSkill34,0);
	}
	if(effect == 3)//Critical Damage
	{
		AttackDamage += this->ReturnCalc(aIndex, eSkill35,0);
	}
}

void cSystemOfRage::AttackDamageRG(LPOBJ lpObj, LPOBJ lpTarget, int & dmg, bool bDamageReflect)
{
	if(bDamageReflect == true) return;
	if(lpObj->Type != OBJ_USER)
	{
		return;
	}
	int aIndex =  lpObj->m_Index;
	int Magic = lpObj->UseMagicNumber;
	//Ice Damage
	if(Magic == 7 || Magic == 39 || Magic == 51 || Magic == 75 ||
		Magic == 450 || Magic == 451 || Magic == 452 || Magic == 453 || Magic == 454)
	{
		dmg += this->ReturnCalc(aIndex, eSkill30,0);
	}
	//Fire Damage
	else if(Magic == 4 || Magic == 10 || Magic == 49 || Magic == 61 ||
		Magic == 74 ||Magic == 78 ||Magic == 14 || Magic == 55 )
	{
		dmg += this->ReturnCalc(aIndex, eSkill15,0);
	}
	//DistanceAttack
	if(gObjCalDistance(lpObj, lpTarget) > 2)
	{
		dmg += this->ReturnCalc(aIndex, eSkill31,0);
	}
	if(lpObj->Type == OBJ_USER && lpTarget->Type == OBJ_USER)
	{
		dmg += this->ReturnCalc(aIndex, eSkill25,0);
	}
}

void cSystemOfRage::SendUser(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	sRageUserSend rSend;

	rSend.h.set((LPBYTE)&rSend, 0xFB, 2, sizeof(rSend));

	rSend.rLevel = this->rUser[aIndex].rLevel;
	rSend.rPoints = this->rUser[aIndex].rPoints;
	rSend.rExperience = this->rUser[aIndex].rExperience;

	rSend.Damage = this->rUser[aIndex].Damage;
	rSend.FreePoints = this->rUser[aIndex].FreePoints;
	rSend.SummonPet = this->rUser[aIndex].SummonPet;
	rSend.WingsDamagePlus = this->rUser[aIndex].WingsDamagePlus;
	rSend.FinalMana = this->rUser[aIndex].FinalMana;
	rSend.IgnoreDefence = this->rUser[aIndex].IgnoreDefence;
	rSend.ResetLevel = this->rUser[aIndex].ResetLevel;
	rSend.Teleport = this->rUser[aIndex].Teleport;
	rSend.CriticalDamageRate = this->rUser[aIndex].CriticalDamageRate;
	rSend.AbsordDamage = this->rUser[aIndex].AbsordDamage;
	rSend.PetDamageBonus = this->rUser[aIndex].PetDamageBonus;
	rSend.FinalLife = this->rUser[aIndex].FinalLife;
	rSend.Strength = this->rUser[aIndex].Strength;
	rSend.DefenceRate = this->rUser[aIndex].DefenceRate;
	rSend.FireDamage = this->rUser[aIndex].FireDamage;
	rSend.Energy = this->rUser[aIndex].Energy;
	rSend.Agility = this->rUser[aIndex].Agility;
	rSend.DoubleDamage = this->rUser[aIndex].DoubleDamage;
	rSend.FinalSD = this->rUser[aIndex].FinalSD;
	rSend.FinalDefence = this->rUser[aIndex].FinalDefence;
	rSend.ZenDrop = this->rUser[aIndex].ZenDrop;
	rSend.GuildBonus = this->rUser[aIndex].GuildBonus;
	rSend.ReflectDamage = this->rUser[aIndex].ReflectDamage;
	rSend.ExellentDamageRate = this->rUser[aIndex].ExellentDamageRate;
	rSend.PvPBonusPlus = this->rUser[aIndex].PvPBonusPlus;
	rSend.MinDefence = this->rUser[aIndex].MinDefence;
	rSend.Experience = this->rUser[aIndex].Experience;
	rSend.StartSD = this->rUser[aIndex].StartSD;
	rSend.PartyBonus = this->rUser[aIndex].PartyBonus;
	rSend.IceDamage = this->rUser[aIndex].IceDamage;
	rSend.DistanceAttack = this->rUser[aIndex].DistanceAttack;
	rSend.AttackRate = this->rUser[aIndex].AttackRate;
	rSend.WeaponBonus = this->rUser[aIndex].WeaponBonus;
	rSend.ExellentDamage = this->rUser[aIndex].ExellentDamage;
	rSend.CriticalDamage = this->rUser[aIndex].CriticalDamage;

	rSend.NextExp = this->NextExp * this->rUser[aIndex].rLevel;

	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}

void cSystemOfRage::ExpFunction(LPOBJ lpObj, LPOBJ TargetObj)
{
	int aIndex = lpObj->m_Index;
	

	if(this->rUser[aIndex].rLevel >= this->MaxLevel)
	{
		return;
	}

	int tExp = TargetObj->Level * this->AddExp;
	MsgNormal(aIndex,"Rage Exp: %d Obtainded",tExp);
	this->rUser[aIndex].rExperience += tExp;
	if(this->rUser[aIndex].rExperience > (this->NextExp * this->rUser[aIndex].rLevel))
	{
		this->rUser[aIndex].rLevel++;
		this->rUser[aIndex].rPoints += this->rPointLvl;
		this->rUser[aIndex].rExperience = 0;
		MsgNormal(aIndex,"Rage Level: %d",this->rUser[aIndex].rLevel);

		this->SendSaveData(aIndex);
	}

	//RageExpSend rSend;
	//rSend.h.set((LPBYTE)&rSend, 0xFB, 3, sizeof(rSend));
	//rSend.Level = this->rUser[aIndex].rLevel;
	//rSend.Point = this->rUser[aIndex].rPoints;
	//rSend.Exp = this->rUser[aIndex].rExperience;
	//rSend.NextExp = (this->NextExp * this->rUser[aIndex].rLevel);
	//
	//DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}

void cSystemOfRage::RecvActiveSkill(sRageTabSend *aRecv, int aIndex)
{
	if(aRecv->Num == eSkill8 && this->rUser[aIndex].Teleport > 0)	//Teleport
	{
		this->TeleportSkill(aIndex);
	}
	else if(aRecv->Num == eSkill3 && this->rUser[aIndex].SummonPet > 0)
	{
		this->SummonPetSkill(aIndex);
	}
}

void cSystemOfRage::ConfigSend(int aIndex)
{
	for(int i=1;i<R_MAX_SKILL;i++)
	{
		sConfigStruct rSend;
		rSend.h.set((LPBYTE)&rSend, 0xFB, 0x00, sizeof(rSend));
		rSend.SkillID = i;
		strcpy(rSend.Name,this->rSkill[i].Name);
		rSend.Damage = this->rSkill[i].StartDamage;
		rSend.MaxPoint = this->rSkill[i].MaxPoint;
		rSend.PointNext = this->rSkill[i].PointNext;
		rSend.Percent = this->rSkill[i].Percent;
		DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
	}
}

void cSystemOfRage::SendDataServer(int aIndex, char *NAme)
{
	DSQuerySend pInfo;

	pInfo.h.c =0xC1;
	pInfo.h.size = sizeof(DSQuerySend);
	pInfo.h.headcode =0xE0;
	pInfo.aIndex = aIndex;
	strcpy(pInfo.Name,NAme);

	cDBSMng.Send((char*)&pInfo, pInfo.h.size);
}

void cSystemOfRage::RecvDSProtocol(DSRageUser *aRecv)
{
	int aIndex = aRecv->aIndex;


	char szName[MAX_ACCOUNT_LEN+1];

	szName[MAX_ACCOUNT_LEN] = 0;
	memcpy(szName, aRecv->Name, sizeof(aRecv->Name));

	if ( gObjIsConnectedGP(aIndex, szName) == FALSE )
	{
		this->rUser[aIndex].InfoLoad = 0;
		//LogAddC(2, lMsg.Get(MSGGET(1, 170)), szAccountId);
#ifdef _RECONNECT_
		g_ConnectEx.SendClose(aIndex,0);
#else
		CloseClient(aIndex);
#endif
		return;
	}

	if(aRecv->Result == FALSE)
	{
		this->rUser[aIndex].InfoLoad = 0;
#ifdef _RECONNECT_
		g_ConnectEx.SendClose(aIndex,0);
#else
		CloseClient(aIndex);
#endif
		return;
	}

	this->rUser[aIndex].InfoLoad = 1;

	this->rUser[aIndex].rLevel = 0;
	this->rUser[aIndex].rPoints = 0;
	this->rUser[aIndex].rExperience = 0;

	this->rUser[aIndex].Damage = 0;
	this->rUser[aIndex].FreePoints = 0;
	this->rUser[aIndex].SummonPet = 0;
	this->rUser[aIndex].WingsDamagePlus = 0;
	this->rUser[aIndex].FinalMana = 0;
	this->rUser[aIndex].IgnoreDefence = 0;
	this->rUser[aIndex].ResetLevel = 0;
	this->rUser[aIndex].Teleport = 0;
	this->rUser[aIndex].CriticalDamageRate = 0;
	this->rUser[aIndex].AbsordDamage = 0;
	this->rUser[aIndex].PetDamageBonus = 0;
	this->rUser[aIndex].FinalLife = 0;
	this->rUser[aIndex].Strength = 0;
	this->rUser[aIndex].DefenceRate = 0;
	this->rUser[aIndex].FireDamage = 0;
	this->rUser[aIndex].Energy = 0;
	this->rUser[aIndex].Agility = 0;
	this->rUser[aIndex].DoubleDamage = 0;
	this->rUser[aIndex].FinalSD = 0;
	this->rUser[aIndex].FinalDefence = 0;
	this->rUser[aIndex].ZenDrop = 0;
	this->rUser[aIndex].GuildBonus;
	this->rUser[aIndex].ReflectDamage = 0;
	this->rUser[aIndex].ExellentDamageRate = 0;
	this->rUser[aIndex].PvPBonusPlus = 0;
	this->rUser[aIndex].MinDefence = 0;
	this->rUser[aIndex].Experience = 0;
	this->rUser[aIndex].StartSD = 0;
	this->rUser[aIndex].PartyBonus = 0;
	this->rUser[aIndex].IceDamage = 0;
	this->rUser[aIndex].DistanceAttack = 0;
	this->rUser[aIndex].AttackRate = 0;
	this->rUser[aIndex].WeaponBonus = 0;
	this->rUser[aIndex].ExellentDamage = 0;
	this->rUser[aIndex].CriticalDamage = 0;

	//----

	this->rUser[aIndex].rLevel = aRecv->rLevel;
	this->rUser[aIndex].rPoints = aRecv->rPoints;
	this->rUser[aIndex].rExperience = aRecv->rExperience;

	this->rUser[aIndex].Damage = aRecv->Damage;
	this->rUser[aIndex].FreePoints = aRecv->FreePoints;
	this->rUser[aIndex].SummonPet = aRecv->SummonPet;
	this->rUser[aIndex].WingsDamagePlus = aRecv->WingsDamagePlus;
	this->rUser[aIndex].FinalMana = aRecv->FinalMana;
	this->rUser[aIndex].IgnoreDefence = aRecv->IgnoreDefence;
	this->rUser[aIndex].ResetLevel = aRecv->ResetLevel;
	this->rUser[aIndex].Teleport = aRecv->Teleport;
	this->rUser[aIndex].CriticalDamageRate = aRecv->CriticalDamageRate;
	this->rUser[aIndex].AbsordDamage = aRecv->AbsordDamage;
	this->rUser[aIndex].PetDamageBonus = aRecv->PetDamageBonus;
	this->rUser[aIndex].FinalLife = aRecv->FinalLife;
	this->rUser[aIndex].Strength = aRecv->Strength;
	this->rUser[aIndex].DefenceRate = aRecv->DefenceRate;
	this->rUser[aIndex].FireDamage = aRecv->FireDamage;
	this->rUser[aIndex].Energy = aRecv->Energy;
	this->rUser[aIndex].Agility = aRecv->Agility;
	this->rUser[aIndex].DoubleDamage = aRecv->DoubleDamage;
	this->rUser[aIndex].FinalSD = aRecv->FinalSD;
	this->rUser[aIndex].FinalDefence = aRecv->FinalDefence;
	this->rUser[aIndex].ZenDrop = aRecv->ZenDrop;
	this->rUser[aIndex].GuildBonus = aRecv->GuildBonus;
	this->rUser[aIndex].ReflectDamage = aRecv->ReflectDamage;
	this->rUser[aIndex].ExellentDamageRate = aRecv->ExellentDamageRate;
	this->rUser[aIndex].PvPBonusPlus = aRecv->PvPBonusPlus;
	this->rUser[aIndex].MinDefence = aRecv->MinDefence;
	this->rUser[aIndex].Experience = aRecv->Experience;
	this->rUser[aIndex].StartSD = aRecv->StartSD;
	this->rUser[aIndex].PartyBonus = aRecv->PartyBonus;
	this->rUser[aIndex].IceDamage = aRecv->IceDamage;
	this->rUser[aIndex].DistanceAttack = aRecv->DistanceAttack;
	this->rUser[aIndex].AttackRate = aRecv->AttackRate;
	this->rUser[aIndex].WeaponBonus = aRecv->WeaponBonus;
	this->rUser[aIndex].ExellentDamage = aRecv->ExellentDamage;
	this->rUser[aIndex].CriticalDamage = aRecv->CriticalDamage;

	this->SendUser(aIndex);
	gObjCalCharacter(aIndex);
}

void cSystemOfRage::RageConnect(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	this->ConfigSend(aIndex);

	this->SendDataServer(aIndex, lpObj->Name);
}

void cSystemOfRage::SendSaveData(int aIndex)
{
	if(!this->Enable) return;
	if(!this->rUser[aIndex].InfoLoad)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	DSRageUserSAVE rSend;

	rSend.h.c =0xC1;
	rSend.h.size = sizeof(DSRageUserSAVE);
	rSend.h.headcode =0xE1;

	strcpy(rSend.Name,lpObj->Name);

	rSend.rLevel = this->rUser[aIndex].rLevel;
	rSend.rPoints = this->rUser[aIndex].rPoints;
	rSend.rExperience = this->rUser[aIndex].rExperience;

	rSend.Damage = this->rUser[aIndex].Damage;
	rSend.FreePoints = this->rUser[aIndex].FreePoints;
	rSend.SummonPet = this->rUser[aIndex].SummonPet;
	rSend.WingsDamagePlus = this->rUser[aIndex].WingsDamagePlus;
	rSend.FinalMana = this->rUser[aIndex].FinalMana;
	rSend.IgnoreDefence = this->rUser[aIndex].IgnoreDefence;
	rSend.ResetLevel = this->rUser[aIndex].ResetLevel;
	rSend.Teleport = this->rUser[aIndex].Teleport;
	rSend.CriticalDamageRate = this->rUser[aIndex].CriticalDamageRate;
	rSend.AbsordDamage = this->rUser[aIndex].AbsordDamage;
	rSend.PetDamageBonus = this->rUser[aIndex].PetDamageBonus;;
	rSend.FinalLife = this->rUser[aIndex].FinalLife;
	rSend.Strength = this->rUser[aIndex].Strength;
	rSend.DefenceRate = this->rUser[aIndex].DefenceRate;
	rSend.FireDamage = this->rUser[aIndex].FireDamage;
	rSend.Energy = this->rUser[aIndex].Energy;
	rSend.Agility = this->rUser[aIndex].Agility;
	rSend.DoubleDamage = this->rUser[aIndex].DoubleDamage;
	rSend.FinalSD = this->rUser[aIndex].FinalSD;
	rSend.FinalDefence = this->rUser[aIndex].FinalDefence;
	rSend.ZenDrop = this->rUser[aIndex].ZenDrop;
	rSend.GuildBonus = this->rUser[aIndex].GuildBonus;
	rSend.ReflectDamage = this->rUser[aIndex].ReflectDamage;
	rSend.ExellentDamageRate = this->rUser[aIndex].ExellentDamageRate;
	rSend.PvPBonusPlus = this->rUser[aIndex].PvPBonusPlus;
	rSend.MinDefence = this->rUser[aIndex].MinDefence;
	rSend.Experience = this->rUser[aIndex].Experience;
	rSend.StartSD = this->rUser[aIndex].StartSD;
	rSend.PartyBonus = this->rUser[aIndex].PartyBonus;
	rSend.IceDamage = this->rUser[aIndex].IceDamage;
	rSend.DistanceAttack = this->rUser[aIndex].DistanceAttack;
	rSend.AttackRate = this->rUser[aIndex].AttackRate;
	rSend.WeaponBonus = this->rUser[aIndex].WeaponBonus;
	rSend.ExellentDamage = this->rUser[aIndex].ExellentDamage;
	rSend.CriticalDamage = this->rUser[aIndex].CriticalDamage;

	cDBSMng.Send((char*)&rSend, rSend.h.size);
}
void cSystemOfRage::JewelsDropRate(LPOBJ lpObj, LPOBJ lpMobObj)
{
	if(!this->Enable) return;
	if ( (rand()%10000) < this->ReturnCalc(lpObj->m_Index, eSkill2,0) )
	{
		int iTopHitUser = gObjMonsterTopHitDamageUser(lpMobObj);

		int Type;
		int num = rand()%4;
		if(num == 0)
		Type = ITEMGET(12,15);
		else if(num == 1)
		Type = ITEMGET(14,13);
		else if(num == 2)
		Type =  ITEMGET(14,14);
		else if(num == 3)
		Type = ITEMGET(14,16);
		else
		Type = ITEMGET(14,22);

		ItemSerialCreateSend(lpMobObj->m_Index,lpMobObj->MapNumber,lpMobObj->X,lpMobObj->Y,Type,0,0,0,0,0,iTopHitUser,0,0);
	}
}

void cSystemOfRage::RageClientSend()
{
	if(!this->Enable) return;
	for (int  aIndex=OBJ_STARTUSERINDEX;aIndex<OBJMAX;aIndex++)
	{
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->Connected < PLAYER_PLAYING ) continue;

		if(ExUser[aIndex].OffExp != 0 || ExUser[aIndex].OffTrade != 0) continue;

		RageExpSend rSend;
		rSend.h.set((LPBYTE)&rSend, 0xFB, 3, sizeof(rSend));
		rSend.Level = this->rUser[aIndex].rLevel;
		rSend.Point = this->rUser[aIndex].rPoints;
		rSend.Exp = this->rUser[aIndex].rExperience;
		rSend.NextExp = (this->NextExp * this->rUser[aIndex].rLevel);
	
		DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
	}
}

#endif