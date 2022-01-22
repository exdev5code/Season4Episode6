//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "ComboAttack.h"
#include "user.h"
#include "MasterSkillSystem.h" //

CComboAttack gComboAttack;

CComboAttack::CComboAttack()
{
	return;
}

CComboAttack::~CComboAttack()
{
	return;
}

int CComboAttack::GetSkillPos(int skillnum)
{
	switch (skillnum)
	{
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			return 0;
			break;
		case 41:
		case 42:
		case 43:
		case 232: //season4 add-on
			return 1;
			break;
		default:
			if(g_MasterSkillSystem.GetSkillID(skillnum) == 455)
			{
				return 1;
			}
			else if(g_MasterSkillSystem.GetSkillID(skillnum) == 460 || //season4 add-on
				g_MasterSkillSystem.GetSkillID(skillnum) == 465)
			{
				return 1;
			}
			return -1;
			break;
	}
}

BOOL CComboAttack::CheckCombo(int aIndex, int skillnum)
{
	LPOBJ lpObj = &gObj[aIndex];
	
#if(DEV_COMBO_CUSTOM==TRUE)
	if( lpObj->Class == CLASS_KNIGHT && lpObj->ComboSkillquestClear == true || 
		lpObj->Class == CLASS_WIZARD && lpObj->PlusStatQuestClear == true ||
		lpObj->Class == CLASS_ELF && lpObj->PlusStatQuestClear == true ||
		lpObj->Class == CLASS_MAGUMSA ||
		lpObj->Class == CLASS_DARKLORD ||
		lpObj->Class == CLASS_SUMMONER && lpObj->PlusStatQuestClear == true ||
		lpObj->Class == CLASS_MONK )
#else
	if ( lpObj->ComboSkillquestClear  != false )
#endif
	{
		int sp = this->GetSkillPos(skillnum);

		if ( sp == 0 )
		{
			lpObj->comboSkill.ProgressIndex  = 0;
			lpObj->comboSkill.dwTime = GetTickCount() + 3000;
			lpObj->comboSkill.Skill[0]  = skillnum;
		}
		else if ( sp == 1 )
		{
			if ( lpObj->comboSkill.Skill[0]  == 0xFF )
			{
				lpObj->comboSkill.Init();
				return 0;
			}

			int Time =GetTickCount();

			if (lpObj->comboSkill.dwTime < GetTickCount() )
			{
				lpObj->comboSkill.Init();
				return 0;
			}

			if ( lpObj->comboSkill.ProgressIndex == 0 )
			{
				lpObj->comboSkill.ProgressIndex = 1;
				lpObj->comboSkill.dwTime = GetTickCount() + 3000;
				lpObj->comboSkill.Skill[1] = skillnum;
			}
			else if ( lpObj->comboSkill.Skill[1]  != skillnum )
			{
				lpObj->comboSkill.Init();
				return 1;
			}
			else
			{
				lpObj->comboSkill.Init();
			}
		}
		else
		{
			lpObj->comboSkill.ProgressIndex= -1;
			lpObj->comboSkill.dwTime = 0;
			lpObj->comboSkill.Skill[0] = -1;
		}
	}

	return 0;
}