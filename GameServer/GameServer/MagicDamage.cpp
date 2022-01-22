#include "stdafx.h"
#include "MagicDamage.h"
#include "..\include\readscript.h"
#include "..\common\WzMemScript.h"
#include "LogProc.h"
#include "GameMain.h"
#include "MasterSkillSystem.h"

#include "Configs.h"

//	GS-N	1.00.77	JPN		-	Completed
//	GS-N	1.00.90	JPN		-	Completed

CMagicDamage MagicDamageC;

CMagicDamage::CMagicDamage()
{
	return;
}


CMagicDamage::~CMagicDamage()
{
	return;
}

//Identical
void CMagicDamage::Init()
{
	for ( int n=0; n< MAX_SKILL;n++)
	{
		this->m_Damage[n] = -1;
	}
}

//Identical
void CMagicDamage::LogSkillList(char * filename)
{
	this->Init();


	SMDFile = fopen(filename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(1, 199)), filename);
		return;
	}

	int Token;
	int n=0;
	int number;
	char name[50];
	int requireLevel;
	int damage;
	int mana;
	int bp=0;
	int dis;
	int rEnergy;
	int iSkillType;
	int rLeadership;
	int rDelay;
	int attr;
	int iSkillUseType;
	int iSkillBrand;
	int iKillCount;
	int RequireStatus[MAX_REQ_SKILL_STATUS] = {0};
	BYTE RequireClass[MAX_TYPE_PLAYER];
	//Season 3 add-on
	short SkillRank;
	short SkillGroup;
	short rMLPoint;
	short rAG;
	short rShield;
	short Duration;
	short rStrength;
	short rDexterity;
	BYTE IconNumber;
	int iUseType;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)TokenNumber;

			Token = GetToken();
			strcpy(name, TokenString);

			Token = GetToken();
			requireLevel = (int)TokenNumber;

			Token = GetToken();
			damage = (int)TokenNumber;

			Token = GetToken();
			mana = (int)TokenNumber;

			Token = GetToken();
			bp = (int)TokenNumber;

			Token = GetToken();
			dis = (int)TokenNumber;

			Token = GetToken();
			rDelay = (int)TokenNumber;

			Token = GetToken();
			rEnergy = (int)TokenNumber;

			Token = GetToken();
			rLeadership = (int)TokenNumber;

			Token = GetToken();
			attr = (int)TokenNumber;

			Token = GetToken();
			iSkillType = (int)TokenNumber;

			Token = GetToken();
			iSkillUseType = (int)TokenNumber;

			Token = GetToken();
			iSkillBrand = (int)TokenNumber;

			Token = GetToken();
			iKillCount = (int)TokenNumber;

			Token = GetToken();
			RequireStatus[0] = (int)TokenNumber;

			Token = GetToken();
			RequireStatus[1] = (int)TokenNumber;

			Token = GetToken();
			RequireStatus[2] = (int)TokenNumber;

			Token = GetToken();
			RequireClass[0] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[1] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[2] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[3] = (BYTE)TokenNumber;

			Token = GetToken();
			RequireClass[4] = (BYTE)TokenNumber;

			///////////////Summoner
			Token = GetToken();
			RequireClass[5] = (BYTE)TokenNumber;

			////////////////////
			Token = GetToken();
			SkillRank = (short)TokenNumber;

			Token = GetToken();
			SkillGroup = (short)TokenNumber;

			Token = GetToken();
			rMLPoint = (short)TokenNumber;

			Token = GetToken();
			rAG = (short)TokenNumber;

			Token = GetToken();
			rShield = (short)TokenNumber;

			Token = GetToken();
			Duration = (short)TokenNumber;

			Token = GetToken();
			rStrength = (short)TokenNumber;

			Token = GetToken();
			rDexterity = (short)TokenNumber;

			Token = GetToken();
			IconNumber = (BYTE)TokenNumber;

			Token = GetToken();
			iUseType = (int)TokenNumber;

			this->Set(name, number,damage, requireLevel, mana, bp, dis, attr, iSkillType, RequireClass, rEnergy, rLeadership, rDelay);
			this->SetEx(number, iSkillUseType, iSkillBrand, iKillCount, RequireStatus);
			this->SetML(number, SkillRank, SkillGroup, rMLPoint, rAG, rShield, Duration, rStrength, rDexterity);
			DefMagicInf[number].Set(number, 0);
		}
	}

	fclose(SMDFile);
	LogAdd(lMsg.Get(MSGGET(1, 200)), filename);
}


void CMagicDamage::LogSkillNameList(char* filename)
{
	int Token;
	int n;
	int number;
	char name[50];
	
	SMDFile = fopen(filename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox(lMsg.Get(MSGGET(1, 199)), filename);
		return;
	}

	n=0;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)TokenNumber;

			Token = GetToken();
			strcpy(name, TokenString);

			strcpy(this->m_Name[number], name);
		}
	}

	fclose(SMDFile);
	LogAdd(lMsg.Get(MSGGET(1, 200)), filename);
}

//Identical
void CMagicDamage::LogSkillList(char* Buffer, int iSize) //0048E160
{
	this->Init();
	CWzMemScript WzMemScript;

	WzMemScript.SetBuffer(Buffer, iSize);

	int Token;
	int n=0;
	int number;
	char name[50];
	int requireLevel;
	int damage;
	int mana;
	int bp=0;
	int dis;
	int rEnergy;
	int iSkillType;
	int rLeadership;
	int rDelay;
	int attr;
	int iSkillUseType;
	int iSkillBrand;
	int iKillCount;
	int RequireStatus[MAX_REQ_SKILL_STATUS] = {0};
	BYTE RequireClass[MAX_TYPE_PLAYER];
	//Season 3 add-on
	int SkillRank;
	int SkillGroup;
	short rMLPoint;
	int rAG;
	int rShield;
	short Duration;
	int rStrength;
	int rDexterity;
	BYTE IconNumber;
	int iUseType;

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			strcpy(name, WzMemScript.GetString() );

			Token = WzMemScript.GetToken();
			requireLevel = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			damage = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			mana = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			bp = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			dis = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rDelay = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rEnergy = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rLeadership = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			attr = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillType = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillUseType = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iSkillBrand = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iKillCount = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[0] = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[1] = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireStatus[2] = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			RequireClass[0] = WzMemScript.GetNumber(); //SM

			Token = WzMemScript.GetToken();
			RequireClass[1] = WzMemScript.GetNumber(); //DK

			Token = WzMemScript.GetToken();
			RequireClass[2] = WzMemScript.GetNumber(); //ELF

			Token = WzMemScript.GetToken();
			RequireClass[3] = WzMemScript.GetNumber(); //MG

			Token = WzMemScript.GetToken();
			RequireClass[4] = WzMemScript.GetNumber(); //DL

			///////////////Summoner (23)
			Token = WzMemScript.GetToken();
			RequireClass[5] = WzMemScript.GetNumber(); //SUM

			////////////////////
			Token = WzMemScript.GetToken();
			SkillRank = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			SkillGroup = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rMLPoint = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rAG = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rShield = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			Duration = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rStrength = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			rDexterity = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			IconNumber = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			iUseType = WzMemScript.GetNumber();

			this->Set(name, number,damage, requireLevel, mana, bp, dis, attr, iSkillType, RequireClass, rEnergy, rLeadership, rDelay);
			this->SetEx(number, iSkillUseType, iSkillBrand, iKillCount, RequireStatus);
			this->SetML(number, SkillRank, SkillGroup, rMLPoint, rAG, rShield, Duration, rStrength, rDexterity);
			DefMagicInf[number].Set(number, 0);
		}
	}

	LogAdd(lMsg.Get(MSGGET(1, 200)), "Skill");
}





void CMagicDamage::LogSkillNameList(char* Buffer, int iSize)
{
	CWzMemScript WzMemScript;
	int Token;
	int n;
	int number;
	char name[50];
	
	WzMemScript.SetBuffer(Buffer, iSize);

	n=0;

	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			number = (int)TokenNumber;

			Token = WzMemScript.GetToken();	
			strcpy(name, TokenString);

			strcpy(this->m_Name[number], name);
		}
	}

	
	LogAdd(lMsg.Get(MSGGET(1, 200)), "Skill_Local");
}

//Identical
void CMagicDamage::SetML(int iSkill, int SkillRank, int SkillGroup, int rMLPoint, int rAG, int rShield, short Duration, int rStrength, int rDexterity) //0048EAC0
{
	if ( iSkill <0 || iSkill > MAX_SKILL -1 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return;
	}

	if ( this->m_Damage[iSkill] == -1 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 50)), __FILE__, __LINE__);
		return;
	}

	this->m_sSkillRank[iSkill] = SkillRank;
	this->m_sSkillGroup[iSkill] = SkillGroup;
	this->m_sReqMLPoint[iSkill] = rMLPoint;

	this->m_sReqAG[iSkill] = rAG;
	this->m_sReqShield[iSkill] = rShield;
	this->m_sDuration[iSkill] = Duration;

	this->m_sReqStrength[iSkill] = rStrength;
	this->m_sReqDexterity[iSkill] = rDexterity;
}

//Identical
void CMagicDamage::SetEx(int iSkill, int iSkillUseType, int iSkillBrand, int iKillCount, int * pReqStatus)
{
	if ( iSkill <0 || iSkill > MAX_SKILL -1 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return;
	}

	if ( this->m_Damage[iSkill] == -1 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 50)), __FILE__, __LINE__);
		return;
	}

	this->m_iSkillUseType[iSkill] = iSkillUseType;
	this->m_iSkillBrand[iSkill] = iSkillBrand;
	this->m_iKillCount[iSkill] = iKillCount;
	memcpy(this->m_iRequireStatus[iSkill], pReqStatus, sizeof(this->m_iRequireStatus[0]));
}

//Identical
void CMagicDamage::Set(char* name, int skill, int damage,  int rlevel,  int mana,  int bp,  int dis, int Attr,  int iSkillType, BYTE* ReqClass, int rEnergy, int rLeadership, int rdelay) //0048ED40
{
	if ( skill <0 || skill > MAX_SKILL -1 )
	{
		MsgBox(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return;
	}

	if ( this->m_Damage[skill] != -1 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 50)), __FILE__, __LINE__);
		return;
	}

	strcpy(this->m_Name[skill], name);
	this->m_Damage[skill] = damage;
	this->m_rLevel[skill] = rlevel;
	this->m_Mana[skill] = mana;
	this->m_Distance[skill] = dis;
	this->m_RequireLeadership[skill] = rLeadership;
	this->m_Delay[skill] = rdelay;
	this->m_BrainPower[skill] = bp;
	this->m_Attr[skill] = Attr;
	this->m_iSkillType[skill] = iSkillType;
	memcpy(this->m_RequireClass[skill], ReqClass, sizeof(this->m_RequireClass[0]));

	int loc2 = (rEnergy * rlevel * 4);

	if(loc2 > 0)
	{
		loc2 = loc2 / 100;
	}
	else
	{
		loc2 = 0;
	}

	this->m_RequireEnergy[skill] = loc2 + 20;

	if ( skill == 13 ) // Blast
	{
		LogAddL("skill:%d", this->m_RequireEnergy[skill]);
	}

	// Set Level Requirements for Skills
	this->m_RequireLevel[skill] = 0;	// Required Level to use the skill

	if ( skill == 41 )	// Twisting Slash
	{
		this->m_RequireLevel[skill] = ExConfig.Skills.TwistingSlashLevel;//80;
	}
	else if ( skill == 42 )	// Rageful Blow
	{
		this->m_RequireLevel[skill] = ExConfig.Skills.RagefulBlowLevel;//170;
	}
	else if ( skill == 43 )	// Death Stab
	{
		this->m_RequireLevel[skill] = ExConfig.Skills.DeathStabLevel;//160;
	}
	else if ( skill == 47 )	// Impale
	{
		this->m_RequireLevel[skill] = ExConfig.Skills.ImpaleLevel;//28;
	}
	else if ( skill == 48 )	// Inner Strength
	{
		this->m_RequireLevel[skill] = ExConfig.Skills.InnerStrengthLevel;//120;
	}
	else if ( skill == 52 )	// Penetration
	{
		this->m_RequireLevel[skill] = ExConfig.Skills.PenetrationLevel;//130;
	}

	if ( skill == 30 )
	{
		this->m_RequireEnergy[skill] = 30;
	}
	else if ( skill == 31 )
	{
		this->m_RequireEnergy[skill] = 60;
	}
	else if ( skill == 32 )
	{
		this->m_RequireEnergy[skill] = 90;
	}
	else if ( skill == 33 )
	{
		this->m_RequireEnergy[skill] = 130;
	}
	else if ( skill == 34 )
	{
		this->m_RequireEnergy[skill] = 170;
	}
	else if ( skill == 35 )
	{
		this->m_RequireEnergy[skill] = 210;
	}
	else if ( skill == 36 )
	{
		this->m_RequireEnergy[skill] = 300;
	}
	else if ( skill == 41 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 42 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 43 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 47 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 48 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 49  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 55  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 51  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 52  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 24  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 17 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 18 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 19 )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 20  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 21  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 22  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 23  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 25  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 56  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 60  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 44  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 45  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 46  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 57  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 73  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 74  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 67  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 68  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 69  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 70  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 71  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 72  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 76  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 77  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 78  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 79  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 62  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 214  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 215  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 216  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 217  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 219  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 220  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 223  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 224  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 221  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	else if ( skill == 222  )
	{
		this->m_RequireEnergy[skill] = 0;
	}
	//Season 4
    else if ( skill == 225  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 230  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 218  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 232  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 233  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 234  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 235  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 236  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 237  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
    else if ( skill == 238  )
    {
        this->m_RequireEnergy[skill] = 0;
    }
}

//Identical
int CMagicDamage::Get(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	return this->m_Damage[skill];
}

//Identical
int CMagicDamage::SkillGet(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	return this->m_Damage[skill];
}

//Identical
int CMagicDamage::SkillGetMana(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return this->m_Mana[0];
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return this->m_Damage[0];
	}

	return this->m_Mana[skill];
}

//Identical
int CMagicDamage::SkillGetBP(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	if ( this->m_Damage[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return 0;
	}

	return this->m_BrainPower[skill];
}

//Identical
int CMagicDamage::SkillGetRequireEnergy(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	if ( this->m_RequireEnergy[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_RequireEnergy[skill];
}

//Identical
BOOL CMagicDamage::SkillGetRequireClass(int Cclass, int ChangeUP, int ChangeUP3rd, int skill) //0048FBD0
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	if ( Cclass < 0 || Cclass > MAX_TYPE_PLAYER-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return -1;
	}

	int requireclass = this->m_RequireClass[skill][Cclass];

	if ( requireclass == 0 )
	{
		return FALSE;
	}

	if (requireclass == 3)
	{
		if(ChangeUP3rd > 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if (requireclass > 1)
		{
			if ( requireclass  != (ChangeUP+1) )
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

//Identical
int CMagicDamage::GetSkillAttr(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		return -1;
	}

	return this->m_Attr[skill];
}

//Identical
int CMagicDamage::CheckSkillAttr(int skill, int attr)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		return FALSE;
	}

	return this->m_Attr[skill];
}

//Identical
int CMagicDamage::GetskillRequireLeadership(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	if ( this->m_RequireLeadership[skill] == -1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 202)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_RequireLeadership[skill];
}

//Identical
int CMagicDamage::GetDelayTime(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	return this->m_Delay[skill];
}

//Identical
int CMagicDamage::GetSkillType(int iSkill)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}
	
	return this->m_iSkillType[iSkill];
}

//Identical
int CMagicDamage::SkillGetRequireLevel(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_RequireLevel[skill];
}

//Identical
BOOL CMagicDamage::CheckStatus(int iSkill, int iGuildStatus) //0048FFE0
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	if ( this->m_iSkillUseType[iSkill] == 0 )
	{
		return TRUE;
	}

	if(g_MasterSkillSystem.CheckRequireStatus(iSkill) != FALSE) //Season3 add-on
	{
		return TRUE;
	}

	if ( iGuildStatus == G_MASTER )
	{
		if ( this->m_iRequireStatus[iSkill][0] == 1 )
		{
			return TRUE;
		}
	}
	else if ( iGuildStatus == G_SUB_MASTER )
	{
		if ( this->m_iRequireStatus[iSkill][1] == 1 )
		{
			return TRUE;
		}
	}
	else if ( iGuildStatus == G_BATTLE_MASTER )
	{
		if ( this->m_iRequireStatus[iSkill][2] == 1 )
		{
			return TRUE;
		}
	}

	return FALSE;
}

//Identical
BOOL CMagicDamage::CheckBrandOfSkill(int iSkill)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return 0;
	}

	if ( this->m_iSkillBrand[iSkill] > 0 )
	{
		return TRUE;
	}

	return FALSE;
}

//Identical
int CMagicDamage::CheckKillCount(int iSkill, int iKillCount)
{
	if ( iSkill < 0 || iSkill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return iKillCount - this->m_iKillCount[iSkill];
}

//Identical
int CMagicDamage::GetSkillDistance(int skill)
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_Distance[skill];
}

//Identical
int CMagicDamage::GetSkillReqMLPoint(int skill) //004902A0
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_sReqMLPoint[skill];
}

//Identical
int CMagicDamage::GetSkillReqStrength(int skill) //00490320
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_sReqStrength[skill];
}

//Identical
int CMagicDamage::GetSkillReqDexterity(int skill) //004903A0
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_sReqDexterity[skill];
}

//Identical
int CMagicDamage::GetSkillReqBrandOfSkill(int skill) //00490420
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_iSkillBrand[skill];
}

//Identical
int CMagicDamage::GetSkillUseType(int skill) //004904A0
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_iSkillUseType[skill];
}

//Identical
int CMagicDamage::GetSkillReqLevel(int skill) //00490520
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_rLevel[skill];
}

//Identical
int CMagicDamage::GetSkillGroup(int skill) //004905A0
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_sSkillGroup[skill];
}

//Identical
int CMagicDamage::GetSkillRank(int skill) //00490620
{
	if ( skill < 0 || skill > MAX_SKILL-1 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 201)), __FILE__, __LINE__);
		return -1;
	}

	return this->m_sSkillRank[skill];
}