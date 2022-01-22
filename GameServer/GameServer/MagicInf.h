#ifndef MAGICINF_H
#define MAGICINF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MagicDamage.h"

#define MAX_MAGIC_INFO	1

class CMagicInf
{

public:

	CMagicInf();
	virtual ~CMagicInf();
	
	int IsMagic();
	void Clear();
	
	int Set(BYTE aType, BYTE aIndex, BYTE aLevel);

	int GetDamage();

	int Set(int aSkill, BYTE aLevel);

	int UpdateML(DWORD aSkill, BYTE aLevel);
	
	
	CMagicInf & operator = (CMagicInf const & __that)
	{
		this->m_Level = __that.m_Level;
		this->m_Skill = __that.m_Skill;
		this->m_DamageMin = __that.m_DamageMin;
		this->m_DamageMax = __that.m_DamageMax;

		return *this;
	};

public:

	BYTE m_Level;	// 4
	int m_Skill;	// 8
	int m_DamageMin;	// C
	int m_DamageMax;	// 10

};

extern CMagicInf DefMagicInf[];

int GetSkillNumberInex(int type, int Index, int level);
void MagicByteConvert(LPBYTE buf, CMagicInf Magici[], int maxmagic);

#endif