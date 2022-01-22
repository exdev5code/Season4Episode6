// ViewportSkillState.cpp: implementation of the CViewportSkillState class.
//	GS	1.00.77	JPN	0xXXXXXXXX	- Completed
//	GS	1.00.90	JPN	0xXXXXXXXX	- Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ViewportSkillState.h"
#include "user.h"
#include "protocol.h"
#include "ItemAddOption.h"

CViewportSkillState g_ViewportSkillState;

CViewportSkillState::CViewportSkillState()
{

}

CViewportSkillState::~CViewportSkillState()
{

}

void CViewportSkillState::AddBuffEffect(LPOBJ lpObj, BYTE btEffectType, int iValue) //0063D4D0
{
	if(lpObj == NULL || btEffectType < 0)
	{
		return;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

	switch(btEffectType)
	{
	case 1:
		{
			lpObj->m_AttackSpeed += iValue;
			lpObj->m_MagicSpeed += iValue;
		}
		break;
	case 3:
		{
			lpObj->m_Defense += iValue;
			lpObj->m_MagicDefense += iValue;
		}
		break;
	case 4:
		{
			lpObj->AddLife += iValue;
			GCReFillSend(lpObj->m_Index, (int)(lpObj->MaxLife + lpObj->AddLife), -2, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield));
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, -1, 0, (int)lpObj->iShield);
		}
		break;
	case 5:
		{
			lpObj->AddMana += iValue;
			GCManaSend(lpObj->m_Index, (int)(lpObj->MaxMana + lpObj->AddMana), -2, 0, (int)(lpObj->MaxBP + lpObj->AddBP));
			GCManaSend(lpObj->m_Index, (int)lpObj->Mana, -1, 0, (int)lpObj->BP);
		}
		break;
	case 21:
		{
			lpObj->m_iSoulBarrierDefense = iValue;
		}
		break;
	case 22:
		{
			lpObj->m_MagicDefense += iValue;
		}
		break;
	case 24:
		{
			lpObj->DamageReflect += iValue;
		}
		break;
	case 26:
		{
			lpObj->m_AttackRating -= iValue;
		}
		break;
	case 28:
		{
			lpObj->m_sSoulBarrierDuration = iValue;
		}
		break;
		//Season 4 add-on
	case 31: //good
		{
			lpObj->AddMana += (int)( (((float)(iValue) * (float)(lpObj->MaxMana))) / 100.0f);
			GCManaSend(lpObj->m_Index, (int)(lpObj->MaxMana + lpObj->AddMana), -2, 0, (int)(lpObj->MaxBP + lpObj->AddBP));
			GCManaSend(lpObj->m_Index, (int)lpObj->Mana, -1, 0, (int)lpObj->BP);
		}
		break;
	case 32: //good :)
		{
			float loc2 = 0; //loc2

			float loc3 = (((float)(40.0f) - (float)(iValue))/100.0f); //good

			loc3 = (loc3 > 0.1f)?loc3:0.1f; //good
			
			loc2 = loc3 * lpObj->MaxLife; //good

			lpObj->AddLife -= (int)((float)(loc2)); //good

			lpObj->Life = ( (float)(lpObj->Life) < ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) )?( (float)(lpObj->Life) ):( ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) ); //good

			GCReFillSend(lpObj->m_Index, (int)(lpObj->MaxLife + lpObj->AddLife), -2, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield)); //good
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, -1, 0, (int)lpObj->iShield); //good
		}
		break;
	case 33: //Wizardry Expansion ??
		{
			lpObj->m_MagicDamageMin += iValue;
			lpObj->m_MagicDamageMax += iValue;
		}
		break;
	case 57: //XMas Attack ??
		{
			lpObj->m_AttackDamageMaxLeft += iValue;
			lpObj->m_AttackDamageMinLeft += iValue;
			lpObj->m_AttackDamageMaxRight += iValue;
			lpObj->m_AttackDamageMinRight += iValue;

			lpObj->m_MagicDamageMin += iValue;
			lpObj->m_MagicDamageMax += iValue;

			lpObj->m_iSummonerBookSpellDamageMin += iValue;
			lpObj->m_iSummonerBookSpellDamageMax += iValue;
		}
		break;
	case 58: //XMas Defense??
		{
			lpObj->m_Defense += iValue;
		}
		break;
	default:
		return;
	}
}

void CViewportSkillState::RemoveBuffEffect(LPOBJ lpObj, BYTE btEffectType, int iValue) //0063DBB0
{
	if(lpObj == NULL || btEffectType < 0)
	{
		return;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

	switch(btEffectType)
	{
	case 1:
		{
			lpObj->m_AttackSpeed -= iValue;
			lpObj->m_MagicSpeed -= iValue;
		}
		break;
	case 3:
		{
			lpObj->m_Defense -= iValue;
			lpObj->m_MagicDefense -= iValue;
		}
		break;
	case 4:
		{
			lpObj->AddLife -= iValue;
			GCReFillSend(lpObj->m_Index, (int)(lpObj->MaxLife + lpObj->AddLife), -2, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield));
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, -1, 0, (int)lpObj->iShield);
		}
		break;
	case 5:
		{
			lpObj->AddMana -= iValue;
			GCManaSend(lpObj->m_Index, (int)(lpObj->MaxMana + lpObj->AddMana), -2, 0, (int)(lpObj->MaxBP + lpObj->AddBP));
			GCManaSend(lpObj->m_Index, (int)lpObj->Mana, -1, 0, (int)lpObj->BP);
		}
		break;
	case 21:
		{
			lpObj->m_iSoulBarrierDefense -= iValue;
		}
		break;
	case 22:
		{
			lpObj->m_MagicDefense -= iValue;
		}
		break;
	case 24:
		{
			lpObj->DamageReflect -= iValue;
		}
		break;
	case 26:
		{
			lpObj->m_AttackRating += iValue;
		}
		break;
	case 28:
		{
			lpObj->m_sSoulBarrierDuration = 0;
		}
		break;
		//Season 4 add-on
	case 31: //good
		{
			lpObj->AddMana -= (int)( (((float)(iValue) * (float)(lpObj->MaxMana))) / 100.0f);
			lpObj->Mana = ( (float)(lpObj->Mana) < ( (float)(lpObj->AddMana) + (float)(lpObj->MaxMana) ) )?( (float)(lpObj->Mana) ):( ( (float)(lpObj->AddMana) + (float)(lpObj->MaxMana) ) ); //good
			GCManaSend(lpObj->m_Index, (int)(lpObj->MaxMana + lpObj->AddMana), -2, 0, (int)(lpObj->MaxBP + lpObj->AddBP));
			GCManaSend(lpObj->m_Index, (int)lpObj->Mana, -1, 0, (int)lpObj->BP);
		}
		break;
	case 32: //good :)
		{
			float loc2 = 0; //loc2

			float loc3 = (((float)(40.0f) - (float)(iValue))/100.0f); //good

			loc3 = (loc3 > 0.1f)?loc3:0.1f; //good
			
			loc2 = loc3 * lpObj->MaxLife; //good

			lpObj->AddLife += (int)(loc2); //good

			GCReFillSend(lpObj->m_Index, (int)(lpObj->MaxLife + lpObj->AddLife), -2, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield)); //good
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, -1, 0, (int)lpObj->iShield); //good
		}
		break;
	case 33: //Wizardry Expansion ??
		{
			lpObj->m_MagicDamageMin -= iValue;
			lpObj->m_MagicDamageMax -= iValue;
		}
		break;
	case 57: //XMas Attack ??
		{
			lpObj->m_AttackDamageMaxLeft -= iValue;
			lpObj->m_AttackDamageMinLeft -= iValue;
			lpObj->m_AttackDamageMaxRight -= iValue;
			lpObj->m_AttackDamageMinRight -= iValue;

			lpObj->m_MagicDamageMin -= iValue;
			lpObj->m_MagicDamageMax -= iValue;

			lpObj->m_iSummonerBookSpellDamageMin -= iValue;
			lpObj->m_iSummonerBookSpellDamageMax -= iValue;
		}
		break;
	case 58: //XMas Defense??
		{
			lpObj->m_Defense -= iValue;
		}
		break;
	default:
		return;
	}
}

void CViewportSkillState::SetDamageType(LPOBJ lpObj, BYTE DamageType, int iDamageValue)
{
	if(DamageType <= 0)
	{
		return;
	}

	switch(DamageType)
	{
	case 18: //Reflect?
		this->ReflectDamage(lpObj, iDamageValue);
		break;
	case 19: //Poison?
		this->PoisonDamage(lpObj, iDamageValue);
		break;
	}
}

void CViewportSkillState::ReflectDamage(LPOBJ lpObj, int iDamageValue)
{
	int iDamage = 0;
	int iShieldDamage = 0;

	iDamage = iDamageValue;
	iShieldDamage = iDamage;

	if(lpObj->Live == false)
	{
		return;
	}

	if(lpObj->lpAttackObj != 0 && lpObj->Type == OBJ_USER && lpObj->lpAttackObj->Type == OBJ_USER)
	{
		iShieldDamage = 90 * iDamage / 100;
		iDamage -= iShieldDamage;

		if(lpObj->iShield-iShieldDamage > 0) //Shield Damage
		{
			lpObj->iShield -= iShieldDamage;
			lpObj->Life -= iDamage;
		}
		else
		{
			iDamage += iShieldDamage - lpObj->iShield;
			iShieldDamage = lpObj->iShield;
			lpObj->Life -= iDamage;
			lpObj->iShield = 0;
		}
	}
	else
	{
		iShieldDamage = 0;
		lpObj->Life -= iDamage;
	}

	if(lpObj->Life < 0.0f)
	{
		lpObj->Life = 0.0f;
	}

	if(lpObj->lpAttackObj != 0)
	{
		gObjLifeCheck(lpObj, lpObj->lpAttackObj, iDamage, 3, 0, 0, 0, iShieldDamage);
	}
}

void CViewportSkillState::PoisonDamage(LPOBJ lpObj, BYTE btDamageValue)
{
	int iDamage = 0;
	int iShieldDamage = 0;

	int loc4 = btDamageValue; //useless

	iDamage = (int)(loc4 * lpObj->Life / 100);

	iShieldDamage = iDamage;

	if(lpObj->lpAttackObj != 0 && lpObj->Type == OBJ_USER && lpObj->lpAttackObj->Type == OBJ_USER)
	{
		if(lpObj->iShield-iShieldDamage > 0) //Shield Damage
		{
			lpObj->iShield -= iShieldDamage;
			iDamage = 0;
		}
		else
		{
			iDamage = iShieldDamage - lpObj->iShield;
			iShieldDamage = lpObj->iShield;
			lpObj->Life -= iDamage;
			lpObj->iShield = 0;
		}
	}
	else
	{
		lpObj->Life -= iDamage;
		iShieldDamage = 0;
	}
	
	if(lpObj->Life < 0.0f)
	{
		lpObj->Life = 0.0f;
	}

	if(lpObj->lpAttackObj != 0)
	{
		gObjLifeCheck(lpObj, lpObj->lpAttackObj, iDamage, 2, 0, 0, 1, iShieldDamage);
	}
}

void CViewportSkillState::PrevBuffLastEffect(LPOBJ lpObj)
{
	if(lpObj == 0)
	{
		return;
	}

	int BuffCount = 0;

	for(int States = 0; States < MAX_STATE_COUNT; States++)
	{
		if(lpObj->m_BuffEffectState[States].btBuffIndex == NULL)
		{
			continue;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType1)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType1, lpObj->m_BuffEffectState[States].iValue1);
			break;
		default:
			break;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType2)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType2, lpObj->m_BuffEffectState[States].iValue2);
			break;
		default:
			break;
		}
	}
}

void CViewportSkillState::NextSetBuffLastEffect(LPOBJ lpObj)
{
	if(lpObj == 0)
	{
		return;
	}

	int BuffCount = 0;

	for(int States = 0; States < MAX_STATE_COUNT; States++)
	{
		if(lpObj->m_BuffEffectState[States].btBuffIndex == NULL)
		{
			continue;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType1)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			break;
		default:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType1, lpObj->m_BuffEffectState[States].iValue1);
			break;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType2)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			break;
		default:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType2, lpObj->m_BuffEffectState[States].iValue2);
			break;
		}
	}
}

void CViewportSkillState::CalCharacterRemoveBuffEffect(LPOBJ lpObj) //0063EA80 identical
{
	for(int States = 0; States < MAX_STATE_COUNT; States++)
	{
		if(lpObj->m_BuffEffectState[States].btBuffIndex == NULL)
		{
			continue;
		}

		this->RemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType1, lpObj->m_BuffEffectState[States].iValue1);
		this->RemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType2, lpObj->m_BuffEffectState[States].iValue2);
	}
}