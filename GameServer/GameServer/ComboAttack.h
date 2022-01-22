#ifndef COMBOATTACK_H
#define COMBOATTACK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct ComboSkillData
{

public:
	void Init();
	DWORD dwTime;	// 0
	short Skill[3];	// 4
	int ProgressIndex;	// 8

};

class CComboAttack
{

public:

	CComboAttack();
	virtual ~CComboAttack();

private:

	int GetSkillPos(int skillnum);

public:

	BOOL CheckCombo(int aIndex, int skillnum);

};

extern CComboAttack gComboAttack;

#endif