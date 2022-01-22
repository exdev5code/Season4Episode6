#pragma once
#include "StdAfx.h"
#include "user.h"
#include "..\\common\zzzitem.h"

#if(DEV_COMBO_CUSTOM==TRUE)

class ComboCustom
{
public:
	ComboCustom();
	~ComboCustom();

	void Init();
	void Load();
	void Read(char* File);

	int Main(int aIndex, int skillnumber);

	int DarkWizard(int skillnumber);
	int Elf(int skillnumber);
	int Summoner(int skillnumber);
	int MagicGladiator(int skillnumber);
	int DarkLord(int skillnumber);
	int RageFighter(int skillnumber);

	int Enable;

	bool DWComboEnable;
	int DWComboSkill_1;
	int DWComboSkill_2;
	int DWComboSkill_3;

	bool AEComboEnable;
	int AEComboSkill_1;
	int AEComboSkill_2;
	int AEComboSkill_3;

	bool SUMComboEnable;
	int SUMComboSkill_1;
	int SUMComboSkill_2;
	int SUMComboSkill_3;

	bool MGComboEnable;
	int MGComboSkill_1;
	int MGComboSkill_2;
	int MGComboSkill_3;

	bool DLComboEnable;
	int DLComboSkill_1;
	int DLComboSkill_2;
	int DLComboSkill_3;

	bool RFComboEnable;
	int RFComboSkill_1;
	int RFComboSkill_2;
	int RFComboSkill_3;

	int Master_DWComboSkill_1;
	int Master_DWComboSkill_2;
	int Master_DWComboSkill_3;

	int Master_AEComboSkill_1;
	int Master_AEComboSkill_2;
	int Master_AEComboSkill_3;

	int Master_SUMComboSkill_1;
	int Master_SUMComboSkill_2;
	int Master_SUMComboSkill_3;

	int Master_MGComboSkill_1;
	int Master_MGComboSkill_2;
	int Master_MGComboSkill_3;

	int Master_DLComboSkill_1;
	int Master_DLComboSkill_2;
	int Master_DLComboSkill_3;

	int Master_RFComboSkill_1;
	int Master_RFComboSkill_2;
	int Master_RFComboSkill_3;
};
extern ComboCustom g_ComboCustom;

#endif