// CharDBSet.cpp: implementation of the CCharDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CharDBSet.h"
#include "..\\MainFrm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharDBSet::CCharDBSet()
{

}

CCharDBSet::~CCharDBSet()
{

}

BOOL CCharDBSet::Connect()
{
	if( m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("Character DB Connect Fail");
		return FALSE;
	}

	if(CheckSP_WZ_CreateCharacterGetVersion() == FALSE)
	{
		MsgBox("Error : WZ_CreateChracter Stored Procedure Version : %d", m_CreateCharacterVer);
		return FALSE;
	}

	DefaultCreateCharacterAllDelete();

	DefaultCharacterCreate(DB_CLASS_TYPE_WIZARD);
	DefaultCharacterCreate(DB_CLASS_TYPE_KNIGHT);
	DefaultCharacterCreate(DB_CLASS_TYPE_ELF);
	DefaultCharacterCreate(DB_CLASS_TYPE_MAGUMSA);
	DefaultCharacterCreate(DB_CLASS_TYPE_DARKLORD);
	DefaultCharacterCreate(DB_CLASS_TYPE_SUMMONER);

	return TRUE;
}

BOOL CCharDBSet::GetCharacter(char *name)
{
	CString qSQL;
	char buffer[256];

	qSQL.Format("SELECT Name FROM Character WHERE Name='%s'", name);

	if(m_DBQuery.ExecGetStr(qSQL, buffer) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

int CCharDBSet::DeleteCharacter(char* AccoundID, char* CharacterID)
{
	if( strlen(CharacterID) < 1)
	{
		return 3;
	}

	CString qSql;

	qSql.Format("DELETE FROM Character WHERE AccountID='%s' AND Name='%s' ", AccoundID, CharacterID);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	m_DBQuery.Clear();

	return 1;
}

int CCharDBSet::DeleteCharacter_DregInfo(char* CharacterID)
{
	CString qSql;

	qSql.Format("EXEC WZ_Delete_C_DregInfo '%s'", CharacterID);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	m_DBQuery.Clear();

	return 1;
}

int CCharDBSet::CreateCharacter(CString accountId, CString Name, BYTE Class)
{
	CString qSql;

	int result = 3;

	qSql.Format("WZ_CreateCharacter '%s', '%s', '%d'", accountId, Name, Class);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return result;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();

	return result;
}

BOOL CCharDBSet::DefaultCharacterCreate(BYTE classskin)
{
	CharacterInfo_Struct tCharInfo;
	BYTE defclass;
	int n;

	defclass = classskin >> 4;

	if(defclass > MAX_CLASSTYPE-1)
	{
		MsgBox("error-L3 : Class over value %s %d", __FILE__, __LINE__);
		defclass = CLASS_KNIGHT;
	}

	tCharInfo.Level = 1;
	tCharInfo.LevelUpPoint = 0;
	tCharInfo.Leadership = DCInfo.DefClass[defclass].Leadership;
	tCharInfo.Class = classskin;
	tCharInfo.Experience = DCInfo.DefClass[defclass].Experience;
	tCharInfo.Strength = DCInfo.DefClass[defclass].Strength;
	tCharInfo.Dexterity = DCInfo.DefClass[defclass].Dexterity;
	tCharInfo.Vitality = DCInfo.DefClass[defclass].Vitality;
	tCharInfo.Energy = DCInfo.DefClass[defclass].Energy;
	tCharInfo.Money = 0;
	tCharInfo.Life = DCInfo.DefClass[defclass].Life;
	tCharInfo.MaxLife = DCInfo.DefClass[defclass].MaxLife;
	tCharInfo.Mana = DCInfo.DefClass[defclass].Mana;
	tCharInfo.MaxMana = DCInfo.DefClass[defclass].MaxMana;
	tCharInfo.MapNumber = 0;
	tCharInfo.MapX = 182;
	tCharInfo.MapY = 128;
	tCharInfo.PkCount = 0;
	tCharInfo.PkLevel = PK_LEVEL_DEFAULT;
	tCharInfo.PkTime = 0;

	for ( n = 0; n < ((MAX_INVENTORYMAP)+MAX_EQUIPMENT+MAX_PSHOP_SIZE); n++ )
	{
		memset(&tCharInfo.dbInventory[MAX_ITEMDBBYTE * n], 0xFF, MAX_ITEMDBBYTE);
	}

	for ( n = 0; n < MAX_MAGIC; n++ )
	{
		tCharInfo.dbMagicList[3 * n] = 0xFF;
		tCharInfo.dbMagicList[3 * n + 1] = 0;
		tCharInfo.dbMagicList[3 * n + 2] = 0;
	}
	
	for ( n = 0; n < MAX_QUEST; n++ )
	{
		tCharInfo.dbQuest[n] = 0xFF;
	}

	if(defclass == CLASS_WIZARD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_ENERGYBALL;
	}

	if(defclass == CLASS_DARKLORD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_SPEAR;
	}

	ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT+2);

	DefaultCreateCharacterInsert(&tCharInfo);
	return TRUE;
}

void CCharDBSet::SetSP_WZ_CreateCharacterGetVersion(int version)
{
	m_CreateCharacterVer = version;
}

BOOL CCharDBSet::CheckSP_WZ_CreateCharacterGetVersion()
{
	CString qSql;
	int version = 0;

	qSql.Format("exec WZ_CreateCharacter_GetVersion");

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		version = m_DBQuery.GetInt(1);

		if(version == m_CreateCharacterVer)
		{
			m_DBQuery.Clear();
			return TRUE;
		}
	}

	m_DBQuery.Clear();

	return FALSE;
}

BOOL CCharDBSet::DefaultCreateCharacterAllDelete()
{
	if(m_DBQuery.Exec("DELETE FROM DefaultClassType") == FALSE)
	{
		LogAddTD("error-L3 : DELETE FROM DefaultClassType %s %d", __FILE__, __LINE__);
		return FALSE;
	}
	return TRUE;
}

BOOL CCharDBSet::DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj)
{
	CString qSql;

	qSql.Format("INSERT INTO DefaultClassType (Level, Class, Strength, Dexterity, Vitality, Energy, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, DbVersion, LevelUpPoint,Leadership)  VALUES (%d,%d,%d,%d,%d, %d, %f,%f,%f,%f, %d,%d,%d, %d, %d, %d)",
		lpObj->Level, lpObj->Class, lpObj->Strength, lpObj->Dexterity, lpObj->Vitality, lpObj->Energy, lpObj->Life, lpObj->MaxLife, lpObj->Mana, lpObj->MaxMana, lpObj->MapNumber, lpObj->MapX, lpObj->MapY, 3, lpObj->LevelUpPoint, lpObj->Leadership);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("UPDATE DefaultClassType SET Inventory=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, MAX_DBINVENTORY);

	qSql.Format("UPDATE DefaultClassType SET MagicList=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, MAX_DBMAGIC);

	qSql.Format("UPDATE DefaultClassType SET Quest=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, MAX_QUEST);

	return TRUE;
}

BYTE CCharDBSet::CurCharNameSave(char* Name)
{
	CString qSql;
	qSql.Format("INSERT INTO T_CurCharName (Name) VALUES('%s')", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}

	return 0x01;
}

BYTE CCharDBSet::SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj)
{
	CString qSql;

	BYTE result = 0x01;

	char chBuffer[1024] = "UPDATE Character SET cLevel=%d, Class=%d, LevelUpPoint=%d, Experience=%d, Strength=%d, Dexterity=%d, Vitality=%d, Energy=%d, Money=%d, Life=%f, MaxLife=%f, Mana=%f, MaxMana=%f, MapNumber=%d, MapPosX=%d, MapPosY=%d, MapDir=%d, PkCount=%d, ";

	strcat(chBuffer, " PkLevel=%d, ");
	strcat(chBuffer, " PkTime=%d,  ");
	strcat(chBuffer, " DbVersion=3, ");
	strcat(chBuffer, " Leadership=%d, ");
	strcat(chBuffer, " ChatLimitTime=%d, ");
	strcat(chBuffer, " FruitPoint=%d, ");
	strcat(chBuffer, " PCPoint=%d, ");	//ExAdd PCPoint
	strcat(chBuffer, " Resets=%d, ");	//ExAdd Resets
	strcat(chBuffer, " gr_res=%d, ");	//ExAdd GResets
	strcat(chBuffer, " ExFreePoints=%d, ");	//ExAdd ExFreePoints
	strcat(chBuffer, " ExQuestNum=%d, ");	//ExAdd ExQuestNum
	strcat(chBuffer, " ExQuestKill=%d ");	//ExAdd ExQuestKill
	strcat(chBuffer, ",ExCred=%d ");
//#ifdef PREMIUM_SYSTEM
	strcat(chBuffer, ",PremiumTime=%d ");
//#endif
//#if __ExGames__
	strcat(chBuffer, ",ChatBanTime=%d ");
//#endif
//#if __MuRain__
	strcat(chBuffer, ",NoobTime=%d ");
//#endif
//#ifdef __MuReal__
	strcat(chBuffer, ",OffAfk=%d ");
	strcat(chBuffer, ",VipTime=%d ");
	strcat(chBuffer, ",CR=%d ");
//#endif

	strcat(chBuffer, ",BMQuest_num=%d ");//int BMQuest_num;
	strcat(chBuffer, ",BMQuest_kill=%d ");//int BMQuest_kill;
	strcat(chBuffer, ",BMQuest_start=%d ");//int BMQuest_start;
	strcat(chBuffer, ",BMDamageReflect=%d ");//int BMDamageReflect;
	strcat(chBuffer, ",BMDamage=%d ");//int BMDamage;
	strcat(chBuffer, ",BMDefense=%d ");//int BMDefense;
	strcat(chBuffer, ",BMCriticalDamage=%d ");//int BMCriticalDamage;
	strcat(chBuffer, ",BMExcelentDamage=%d ");//int BMExcelentDamage;
	strcat(chBuffer, ",BMLife=%d ");//int BMLife;

	strcat(chBuffer, ",ChaosBank=%d ");	//int BMLife;//int ChaosBank;
	strcat(chBuffer, ",BlessBank=%d ");
	strcat(chBuffer, ",SoulBank=%d ");
	strcat(chBuffer, ",LifeBank=%d ");

	strcat(chBuffer, " where Name = '%s' ");

	qSql.Format(chBuffer, lpObj->Level, lpObj->Class, lpObj->LevelUpPoint, lpObj->Experience, lpObj->Strength, lpObj->Dexterity, lpObj->Vitality, lpObj->Energy, lpObj->Money, lpObj->Life, lpObj->MaxLife, lpObj->Mana, 
		lpObj->MaxMana, lpObj->MapNumber, lpObj->MapX, lpObj->MapY, lpObj->Dir, lpObj->PkCount, lpObj->PkLevel, lpObj->PkTime, lpObj->Leadership, lpObj->ChatLitmitTime, lpObj->FruitPoint, lpObj->PCPoint, lpObj->Reset,lpObj->GReset,
		lpObj->ExFreePoints,lpObj->ExQuestNum,lpObj->ExQuestKill,lpObj->ExCred,
//#ifdef PREMIUM_SYSTEM
		lpObj->PremiumTime,
//#endif
//#if __ExGames__
		lpObj->ChatBanTime,
//#endif
//#if __MuRain__
		lpObj->NoobTime,
//#endif
//#ifdef __MuReal__
		lpObj->OffAfk,lpObj->VipTime,lpObj->CR,
//#endif

	lpObj->BMQuest_num,//int BMQuest_num;
	lpObj->BMQuest_kill,// BMQuest_kill;
	lpObj->BMQuest_start,// BMQuest_start;
	lpObj->BMDamageReflect,// BMDamageReflect;
	lpObj->BMDamage,// BMDamage;
	lpObj->BMDefense,// BMDefense;
	lpObj->BMCriticalDamage,// BMCriticalDamage;
	lpObj->BMExcelentDamage,// BMExcelentDamage;
	lpObj->BMLife,// BMLife;

		lpObj->ChaosBank,
		lpObj->BlessBank,
		lpObj->SoulBank,
		lpObj->LifeBank,

		Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}

	qSql.Format("UPDATE Character SET Inventory=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, MAX_DBINVENTORY);

	qSql.Format("UPDATE Character SET MagicList=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, MAX_DBMAGIC);

	qSql.Format("UPDATE Character SET Quest=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, MAX_QUEST);

#ifdef _CR_MEMB_INFO_
	qSql.Format("SELECT AccountID FROM Character WHERE Name = '%s'", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 2;
	}

	char AccountID[MAX_IDSTRING+1];

	//m_DBQuery.GetStr(1, chBuffer);
	m_DBQuery.GetStr("AccountID", AccountID);

	//memcpy(chUserID, chBuffer, MAX_IDSTRING+1);

	m_DBQuery.Clear();

#ifdef _MEMB_CREDITS_
	qSql.Format("UPDATE MEMB_CREDITS SET credits=%d WHERE memb___id='%s'",lpObj->ExCred,AccountID);
#else
	qSql.Format("UPDATE MEMB_INFO SET ExCredit=%d WHERE memb___id='%s'",lpObj->ExCred,AccountID);
#endif

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}
#endif

	qSql.Format("SELECT AccountID FROM Character WHERE Name = '%s'", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 2;
	}

	char AccountID2[MAX_IDSTRING+1];

	//m_DBQuery.GetStr(1, chBuffer);
	m_DBQuery.GetStr("AccountID", AccountID2);

	//memcpy(chUserID, chBuffer, MAX_IDSTRING+1);

	m_DBQuery.Clear();

	qSql.Format("UPDATE MEMB_INFO SET MTDate=%d WHERE memb___id='%s'",lpObj->MTDate,AccountID2);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}

	return 0x01;
}

BOOL CCharDBSet::GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj)
{
	CString qSql;

//	char chBuffer[512] = "SELECT AccountID, cLevel, Class, LevelUpPoint, Experience, Strength, Dexterity, Vitality, Energy, Money, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, MapDir, PkCount, PkLevel, PkTime, CtlCode,";
//	
//	strcat(chBuffer, " Leadership, ");
//	strcat(chBuffer, " ChatLimitTime, ");
//	strcat(chBuffer, " FruitPoint, ");
//	strcat(chBuffer, " DbVersion, ");
//	strcat(chBuffer, " PCPoint, ");	//ExAdd PCPoint
//	strcat(chBuffer, " Resets, ");	//ExAdd Resets
//	strcat(chBuffer, " gr_res, ");	//ExAdd Grand Resets
//	strcat(chBuffer, " ExFreePoints, ");//ExAdd ExFreePoints
//	strcat(chBuffer, " ExQuestNum, ");	//ExAdd ExQuestNum
//	strcat(chBuffer, " ExQuestKill ");	//ExAdd ExQuestKill
//	strcat(chBuffer, ",ExCred ");
//#ifdef PREMIUM_SYSTEM
//	strcat(chBuffer, ",PremiumTime ");
//#endif
//#if __ExGames__
//	strcat(chBuffer, ",ChatBanTime ");
//#endif
//#if __MuRain__
//	strcat(chBuffer, ",NoobTime ");
//#endif
//#ifdef __MuReal__
//	strcat(chBuffer, ",OffAfk ");
//	strcat(chBuffer, ",VipTime ");
//	strcat(chBuffer, ",CR ");
//#endif
//
//	strcat(chBuffer, " FROM Character where Name = '%s' ");

	char chBuffer[512] = "SELECT * FROM Character where Name = '%s' ";

	qSql.Format(chBuffer, Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.GetStr("AccountID", lpObj->AccountID);

	if( strcmp(lpObj->AccountID, szAccountID) != 0)
	{
		LogAddC(LOGC_RED, "error-L1 :캐릭터의 계정과 요청한 계정이 맞지않다.%s %s", lpObj->AccountID, szAccountID);
		m_DBQuery.Clear();
		return FALSE;
	}

	lpObj->Level = m_DBQuery.GetInt("cLevel");
	lpObj->Class = m_DBQuery.GetInt("Class");
	lpObj->LevelUpPoint = m_DBQuery.GetInt("LevelUpPoint");
	lpObj->Experience = m_DBQuery.GetInt("Experience");
	lpObj->Strength = m_DBQuery.GetInt("Strength");
	lpObj->Dexterity = m_DBQuery.GetInt("Dexterity");
	lpObj->Vitality = m_DBQuery.GetInt("Vitality");
	lpObj->Energy = m_DBQuery.GetInt("Energy");
	lpObj->Money = m_DBQuery.GetInt("Money");
	lpObj->Life = m_DBQuery.GetFloat("Life");
	lpObj->MaxLife = m_DBQuery.GetFloat("MaxLife");
	lpObj->Mana = m_DBQuery.GetFloat("Mana");
	lpObj->MaxMana = m_DBQuery.GetFloat("MaxMana");
	lpObj->MapNumber = m_DBQuery.GetInt("MapNumber");
	lpObj->MapX = m_DBQuery.GetInt("MapPosX");
	lpObj->MapY = m_DBQuery.GetInt("MapPosY");
	lpObj->Dir = m_DBQuery.GetInt("MapDir");
	lpObj->PkCount = m_DBQuery.GetInt("PkCount");
	lpObj->PkLevel = m_DBQuery.GetInt("PkLevel");
	lpObj->PkTime = m_DBQuery.GetInt("PkTime");
	lpObj->PCPoint = m_DBQuery.GetInt("PCPoint");
	lpObj->Reset = m_DBQuery.GetInt("Resets");
	lpObj->GReset = m_DBQuery.GetInt("gr_res");
	lpObj->ExFreePoints = m_DBQuery.GetInt("ExFreePoints");
	lpObj->ExQuestNum = m_DBQuery.GetInt("ExQuestNum");
	lpObj->ExQuestKill = m_DBQuery.GetInt("ExQuestKill");
//#ifdef PREMIUM_SYSTEM
	lpObj->PremiumTime = m_DBQuery.GetInt("PremiumTime");
//#endif
//#if __ExGames__
	lpObj->ChatBanTime = m_DBQuery.GetInt("ChatBanTime");
//#endif
//#if __MuRain__
	lpObj->NoobTime = m_DBQuery.GetInt("NoobTime");
//#endif	
//#ifdef __MuReal__
	lpObj->OffAfk = m_DBQuery.GetInt("OffAfk");
	lpObj->VipTime = m_DBQuery.GetInt("VipTime");
	lpObj->CR = m_DBQuery.GetInt("CR");
//#endif
	lpObj->ExCred = m_DBQuery.GetInt("ExCred");

	//lpObj->ExCred = m_DBQuery.GetInt("ExCred");//
	lpObj->BMQuest_num = m_DBQuery.GetInt("BMQuest_num");//int BMQuest_num;
	lpObj->BMQuest_kill = m_DBQuery.GetInt("BMQuest_kill");//int BMQuest_kill;
	lpObj->BMQuest_start = m_DBQuery.GetInt("BMQuest_start");//int BMQuest_start;
	lpObj->BMDamageReflect = m_DBQuery.GetInt("BMDamageReflect");//int BMDamageReflect;
	lpObj->BMDamage = m_DBQuery.GetInt("BMDamage");//int BMDamage;
	lpObj->BMDefense = m_DBQuery.GetInt("BMDefense");//int BMDefense;
	lpObj->BMCriticalDamage = m_DBQuery.GetInt("BMCriticalDamage");//int BMCriticalDamage;
	lpObj->BMExcelentDamage = m_DBQuery.GetInt("BMExcelentDamage");//int BMExcelentDamage;
	lpObj->BMLife = m_DBQuery.GetInt("BMLife");//int BMLife;

	lpObj->ChaosBank = m_DBQuery.GetInt("ChaosBank");
	lpObj->BlessBank = m_DBQuery.GetInt("BlessBank");
	lpObj->SoulBank = m_DBQuery.GetInt("SoulBank");
	lpObj->LifeBank = m_DBQuery.GetInt("LifeBank");

	int ctlcode = m_DBQuery.GetInt("CtlCode");

	if(ctlcode < 0)
	{
		ctlcode = 0;
	}

	lpObj->CtlCode = ctlcode;

	int dbversion = m_DBQuery.GetInt("DbVersion");

	if(dbversion < 0)
	{
		dbversion = 0;
	}

	lpObj->DbVersion = dbversion;

	int leadership = m_DBQuery.GetInt("Leadership");

	if(leadership < 0)
	{
		leadership = 0;
	}

	int ChatLitmitTime = m_DBQuery.GetInt("ChatLimitTime");

	if(ChatLitmitTime < 0)
	{
		ChatLitmitTime = 0;
	}

	lpObj->Leadership = leadership;
	lpObj->ChatLitmitTime = ChatLitmitTime;

	int iFruitPoint = m_DBQuery.GetInt("FruitPoint");

	if(iFruitPoint < 0)
	{
		lpObj->FruitPoint = 0;
		LogAddC(LOGC_RED, "[Fruit System] [%s][%s] Fruit 컬럼 %d -> 0 으로 수정 ", lpObj->AccountID, Name, iFruitPoint);
	}
	else
	{
		lpObj->FruitPoint = iFruitPoint;
	}

	m_DBQuery.Clear();

	///////////////////////////////////
	qSql.Format("SELECT Inventory from Character where Name='%s'", Name);

	int nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbInventory);

	if(nRet == 0)
	{
		for(int n = 0; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	else if(nRet == 760)
	{
		for(int n = 760; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	else if(nRet > 0 && nRet < MAX_DBINVENTORY)
	{
		for(int n = nRet; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	///////////////////////////////////

	///////////////////////////////////
	qSql.Format("SELECT MagicList from Character where Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbMagicList);

	if(nRet == 0)
	{
		for (int n = 0; n < MAX_MAGIC; n++ )
		{
			lpObj->dbMagicList[3 * n] = 0xFF;
			lpObj->dbMagicList[3 * n + 1] = 0;
			lpObj->dbMagicList[3 * n + 2] = 0;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	else if(nRet > 0 && nRet < MAX_DBMAGIC)
	{
		int n = nRet;

		while(n < MAX_DBMAGIC)
		{
			lpObj->dbMagicList[n] = 0xFF;
			lpObj->dbMagicList[n + 1] = 0;
			lpObj->dbMagicList[n + 2] = 0;
			n += 3;
		}
	}
	///////////////////////////////////

	///////////////////////////////////
	qSql.Format("SELECT Quest from Character where Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbQuest);

	if(nRet == 0)
	{
		for (int n = 0; n < MAX_QUEST; n++ )
		{
			lpObj->dbQuest[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	///////////////////////////////////
	
#ifdef _CR_MEMB_INFO_

	//m_DBQuery.Clear();

#ifdef _MEMB_CREDITS_
	qSql.Format("SELECT credits FROM MEMB_CREDITS WHERE memb___id='%s'", szAccountID);
#else
	qSql.Format("SELECT ExCredit FROM MEMB_INFO WHERE memb___id='%s'", szAccountID);
#endif

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

#ifdef _MEMB_CREDITS_
	lpObj->ExCred = m_DBQuery.GetInt("credits");
#else
	lpObj->ExCred = m_DBQuery.GetInt("ExCredit");
#endif

	m_DBQuery.Clear();

#endif

	qSql.Format("SELECT MTDate FROM MEMB_INFO WHERE memb___id='%s'", szAccountID);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	//lpObj->ExCred = m_DBQuery.GetInt("ExCredit");
	lpObj->MTDate = m_DBQuery.GetInt("MTDate");

	m_DBQuery.Clear();

	return TRUE;
}

BOOL CCharDBSet::SaveItem(char* Name, BYTE* ItemBuf)
{
	CString qSql;
	
	qSql.Format("UPDATE Character SET DbVersion=3 where Name = '%s'", Name);
	
	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("UPDATE Character SET Inventory=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, ItemBuf, MAX_DBINVENTORY);

	return TRUE;
}

int CCharDBSet::CharServerMove(char* Name)
{
	CString qSql;

	qSql.Format("SP_CHARACTER_TRANSFER '%s'", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER error return #1");
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER error return #2");
		m_DBQuery.Clear();
		return 1;
	}

	int error = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();

	LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER result %d", error);

	if(error != 0)
	{
		return error;
	}

	return 0;
}

int CCharDBSet::ChangeName(char* AccountId, char* OldName, char* NewName)
{
	int result = 0;
	CString qSql;

	qSql.Format("WZ_ChangeCharacterName '%s', '%s', '%s'", AccountId, OldName, NewName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 5;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();
	
	return result;
}

int CCharDBSet::GetCharacterID(char* chName, char* chUserID)
{
	CString qSql;

	qSql.Format("SELECT AccountID FROM Character WHERE Name = '%s'", chName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 2;
	}

	char chBuffer[MAX_IDSTRING+1];

	m_DBQuery.GetStr(1, chBuffer);

	memcpy(chUserID, chBuffer, MAX_IDSTRING+1);

	m_DBQuery.Clear();

	return 0;
}

DWORD CCharDBSet::GetCharacterClass(char* chName)
{
	CString qSql;
	DWORD dwReturn = 0;

	qSql.Format("SELECT Class FROM Character WHERE Name = '%s'", chName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return -2;
	}

	dwReturn = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();

	return dwReturn;
}

//#ifdef _RAGE_SYSTEM_
//void CCharDBSet::DefaultRageChar(char *Name, int Type, int aIndex, int pIndex)
//{
//	CString qSql;
//
//	//char NextSQLp[4096] = "CREATE TABLE RageSystem(Name varchar(10),RageLevel int,RagePoint int,RageExp int,";
//	//strcat(NextSQLp, "Damage int,FreePoints int,SummonPet int,WingsDamagePlus int,FinalMana int,IgnoreDefence int,ResetLevel int,Teleport int,CriticalDamageRate int,AbsordDamage int,PetDamageBonus int,");
//	//strcat(NextSQLp,"/*FinalLife*/ int,/*Strength*/ int,/*DefenceRate*/ int,/*FireDamage*/ int,/*Energy*/ int,Agility int,DoubleDamage int,FinalSD int,FinalDefence int,ZenDrop int,GuildBonus int,");
//	//strcat(NextSQLp,"ReflectDamage int,ExellentDamageRate int,/*PvPBonusPlus*/ int,MinDefence int,Experience int,StartSD int,PartyBonus int,IceDamage int,DistanceAttack int,AttackRate int,WeaponBonus int,");
//	//strcat(NextSQLp,"ExellentDamage int,CriticalDamage int);");
//
//	char NextSQLpq[4096] = "INSERT INTO RageSystem (Name,RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
//		strcat(NextSQLpq,"FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,");
//		strcat(NextSQLpq,"WeaponBonus,ExellentDamage,CriticalDamage)");
//		strcat(NextSQLpq,"VALUES ('%s',1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)");
//
//	qSql.Format(NextSQLpq,Name);
//
//	if(m_DBQuery.Exec(qSql) == FALSE)
//	{
//		m_DBQuery.Clear();
//		return;
//	}
//
//	m_DBQuery.Clear();
//
//	if(Type == 1 && aIndex >= 0 && pIndex >= 0)
//	{
//		char chBuffer[4024] = "SELECT RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
//		strcat(chBuffer, " FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,WeaponBonus,ExellentDamage,CriticalDamage");
//		strcat(chBuffer, " FROM RageSystem where Name = '%s'");
//
//		//LogAddC(LOGC_BLUE,"Recv Name: %s", Recv->Name);
//
//		qSql.Format(chBuffer, Name);
//
//		if(m_DBQuery.Exec(qSql) == FALSE)
//		{
//			m_DBQuery.Clear();
//			return;
//		}
//
//		if(m_DBQuery.Fetch() == SQL_NO_DATA)
//		{
//			m_DBQuery.Clear();
//			return;
//		}
//
//		DSRageUser rSend;
//
//		rSend.h.c = PMHC_BYTE;
//		rSend.h.size = sizeof(DSRageUser);
//		rSend.h.headcode = 0xE0;
//
//		rSend.aIndex = aIndex;
//
//		rSend.rLevel = m_DBQuery.GetInt("RageLevel");
//		rSend.rPoints = m_DBQuery.GetInt("RagePoint");
//		rSend.rExperience = m_DBQuery.GetInt("RageExp");
//
//		rSend.Damage = m_DBQuery.GetInt("Damage");	
//		rSend.FreePoints = m_DBQuery.GetInt("FreePoints");
//		rSend.SummonPet = m_DBQuery.GetInt("SummonPet");
//		rSend.WingsDamagePlus = m_DBQuery.GetInt("WingsDamagePlus");
//		rSend.FinalMana = m_DBQuery.GetInt("FinalMana");
//		rSend.IgnoreDefence = m_DBQuery.GetInt("IgnoreDefence");
//		rSend.ResetLevel = m_DBQuery.GetInt("ResetLevel");
//		rSend.Teleport = m_DBQuery.GetInt("Teleport");
//		rSend.CriticalDamageRate = m_DBQuery.GetInt("CriticalDamageRate");
//		rSend.AbsordDamage = m_DBQuery.GetInt("AbsordDamage");
//		rSend.PetDamageBonus = m_DBQuery.GetInt("PetDamageBonus");
//		rSend.FinalLife = m_DBQuery.GetInt("FinalLife");
//		rSend.Strength = m_DBQuery.GetInt("Strength");
//		rSend.DefenceRate = m_DBQuery.GetInt("DefenceRate");
//		rSend.FireDamage = m_DBQuery.GetInt("FireDamage");
//		rSend.Energy = m_DBQuery.GetInt("Energy");
//		rSend.Agility = m_DBQuery.GetInt("Agility");
//		rSend.DoubleDamage = m_DBQuery.GetInt("DoubleDamage");
//		rSend.FinalSD = m_DBQuery.GetInt("FinalSD");
//		rSend.FinalDefence = m_DBQuery.GetInt("FinalDefence");
//		rSend.ZenDrop = m_DBQuery.GetInt("ZenDrop");
//		rSend.GuildBonus = m_DBQuery.GetInt("GuildBonus");
//		rSend.ReflectDamage = m_DBQuery.GetInt("ReflectDamage");
//		rSend.ExellentDamageRate = m_DBQuery.GetInt("ExellentDamageRate");
//		rSend.PvPBonusPlus = m_DBQuery.GetInt("PvPBonusPlus");
//		rSend.MinDefence = m_DBQuery.GetInt("MinDefence");
//		rSend.Experience = m_DBQuery.GetInt("Experience");
//		rSend.StartSD = m_DBQuery.GetInt("StartSD");
//		rSend.PartyBonus = m_DBQuery.GetInt("PartyBonus");
//		rSend.IceDamage = m_DBQuery.GetInt("IceDamage");
//		rSend.DistanceAttack = m_DBQuery.GetInt("DistanceAttack");
//		rSend.AttackRate = m_DBQuery.GetInt("AttackRate");
//		rSend.WeaponBonus = m_DBQuery.GetInt("WeaponBonus");
//		rSend.ExellentDamage = m_DBQuery.GetInt("ExellentDamage");
//		rSend.CriticalDamage = m_DBQuery.GetInt("CriticalDamage");
//
//		m_DBQuery.Clear();
//
//		wsjServer.DataSend(pIndex, (char*)&rSend, rSend.h.size);
//
//	}
//
//	//wsjServer.DataSend(aIndex, (char*)&pMsgResult, pMsgResult.h.size);
//}
//
//void CCharDBSet::SendRageUser(DSQuerySend * Recv, int aIndex)
//{
//	CString qSql;
//
//	char chBuffer[4024] = "SELECT RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
//	strcat(chBuffer, " FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,WeaponBonus,ExellentDamage,CriticalDamage");
//	strcat(chBuffer, " FROM RageSystem where Name = '%s'");
//
//	LogAddC(LOGC_BLUE,"Recv Name: %s aIndex:%d", Recv->Name,aIndex);
//
//	qSql.Format(chBuffer, Recv->Name);
//
//	if(m_DBQuery.Exec(qSql) == FALSE)
//	{
//		m_DBQuery.Clear();
//		return;
//	}
//
//	if(m_DBQuery.Fetch() == SQL_NO_DATA)
//	{
//		m_DBQuery.Clear();
//		this->DefaultRageChar(Recv->Name, 1, Recv->aIndex,aIndex);
//		return;
//	}
//
//	DSRageUser rSend;
//
//	rSend.h.c = PMHC_BYTE;
//	rSend.h.size = sizeof(DSRageUser);
//	rSend.h.headcode = 0xE0;
//
//	rSend.aIndex = Recv->aIndex;
//
//	rSend.rLevel = m_DBQuery.GetInt("RageLevel");
//	rSend.rPoints = m_DBQuery.GetInt("RagePoint");
//	rSend.rExperience = m_DBQuery.GetInt("RageExp");
//
//	rSend.Damage = m_DBQuery.GetInt("Damage");	
//	rSend.FreePoints = m_DBQuery.GetInt("FreePoints");
//	rSend.SummonPet = m_DBQuery.GetInt("SummonPet");
//	rSend.WingsDamagePlus = m_DBQuery.GetInt("WingsDamagePlus");
//	rSend.FinalMana = m_DBQuery.GetInt("FinalMana");
//	rSend.IgnoreDefence = m_DBQuery.GetInt("IgnoreDefence");
//	rSend.ResetLevel = m_DBQuery.GetInt("ResetLevel");
//	rSend.Teleport = m_DBQuery.GetInt("Teleport");
//	rSend.CriticalDamageRate = m_DBQuery.GetInt("CriticalDamageRate");
//	rSend.AbsordDamage = m_DBQuery.GetInt("AbsordDamage");
//	rSend.PetDamageBonus = m_DBQuery.GetInt("PetDamageBonus");
//	rSend.FinalLife = m_DBQuery.GetInt("FinalLife");
//	rSend.Strength = m_DBQuery.GetInt("Strength");
//	rSend.DefenceRate = m_DBQuery.GetInt("DefenceRate");
//	rSend.FireDamage = m_DBQuery.GetInt("FireDamage");
//	rSend.Energy = m_DBQuery.GetInt("Energy");
//	rSend.Agility = m_DBQuery.GetInt("Agility");
//	rSend.DoubleDamage = m_DBQuery.GetInt("DoubleDamage");
//	rSend.FinalSD = m_DBQuery.GetInt("FinalSD");
//	rSend.FinalDefence = m_DBQuery.GetInt("FinalDefence");
//	rSend.ZenDrop = m_DBQuery.GetInt("ZenDrop");
//	rSend.GuildBonus = m_DBQuery.GetInt("GuildBonus");
//	rSend.ReflectDamage = m_DBQuery.GetInt("ReflectDamage");
//	rSend.ExellentDamageRate = m_DBQuery.GetInt("ExellentDamageRate");
//	rSend.PvPBonusPlus = m_DBQuery.GetInt("PvPBonusPlus");
//	rSend.MinDefence = m_DBQuery.GetInt("MinDefence");
//	rSend.Experience = m_DBQuery.GetInt("Experience");
//	rSend.StartSD = m_DBQuery.GetInt("StartSD");
//	rSend.PartyBonus = m_DBQuery.GetInt("PartyBonus");
//	rSend.IceDamage = m_DBQuery.GetInt("IceDamage");
//	rSend.DistanceAttack = m_DBQuery.GetInt("DistanceAttack");
//	rSend.AttackRate = m_DBQuery.GetInt("AttackRate");
//	rSend.WeaponBonus = m_DBQuery.GetInt("WeaponBonus");
//	rSend.ExellentDamage = m_DBQuery.GetInt("ExellentDamage");
//	rSend.CriticalDamage = m_DBQuery.GetInt("CriticalDamage");
//
//	m_DBQuery.Clear();
//
//	wsjServer.DataSend(aIndex, (char*)&rSend, rSend.h.size);
//}
//
//
//
//void CCharDBSet::SaveRageSkill(DSRageUserSAVE *p)
//{
//	CString qSql;
//
//	char chBuffer[4024] = "UPDATE RageSystem SET RageLevel=%d, RagePoint=%d, RageExp=%d, Damage=%d, FreePoints=%d, SummonPet=%d, WingsDamagePlus=%d, FinalMana=%d, IgnoreDefence=%d, ResetLevel=%d, Teleport=%d, CriticalDamageRate=%d, AbsordDamage=%d, PetDamageBonus=%d, FinalLife=%d, Strength=%d, DefenceRate=%d, FireDamage=%d, ";
//
//	strcat(chBuffer, " Energy=%d, ");
//	strcat(chBuffer, " Agility=%d,  ");
//	strcat(chBuffer, " DoubleDamage=%d, ");
//	strcat(chBuffer, " FinalSD=%d, ");
//	strcat(chBuffer, " FinalDefence=%d, ");
//	strcat(chBuffer, " ZenDrop=%d, ");
//	strcat(chBuffer, " GuildBonus=%d, ");
//
//	strcat(chBuffer, " ReflectDamage=%d, ");	//ExAdd PCPoint
//	strcat(chBuffer, " ExellentDamageRate=%d ");	//ExAdd ExFreePoints
//	strcat(chBuffer, ", PvPBonusPlus=%d ");	//ExAdd Resets
//	strcat(chBuffer, ", MinDefence=%d ");	//ExAdd GResets
//	strcat(chBuffer, ", Experience=%d ");	//GensNumber
//	strcat(chBuffer, ", StartSD=%d ");	//GensRang
//	strcat(chBuffer, ", PartyBonus=%d ");	//GensExp
//	strcat(chBuffer, ", IceDamage=%d ");	//GensReward
//	strcat(chBuffer, ", DistanceAttack=%d ");
//	strcat(chBuffer, ", AttackRate=%d ");
//	strcat(chBuffer, ",WeaponBonus=%d ");
//	strcat(chBuffer, ",ExellentDamage=%d ");
//	strcat(chBuffer, ",CriticalDamage=%d ");
//	strcat(chBuffer, " where Name = '%s' ");
//
//	qSql.Format(chBuffer,p->rLevel,p->rPoints,p->rExperience,p->Damage,p->FreePoints,p->SummonPet,p->WingsDamagePlus,p->FinalMana,p->IgnoreDefence,p->ResetLevel,p->Teleport,p->CriticalDamageRate,p->AbsordDamage,p->PetDamageBonus,p->FinalLife,p->Strength,p->DefenceRate,p->FireDamage,
//		p->Energy,
//		p->Agility,
//		p->DoubleDamage,
//		p->FinalSD,
//		p->FinalDefence,
//		p->ZenDrop,
//		p->GuildBonus,
//		p->ReflectDamage,
//		p->ExellentDamageRate,
//		p->PvPBonusPlus,
//		p->MinDefence,
//		p->Experience,
//		p->StartSD,
//		p->PartyBonus,
//		p->IceDamage,
//		p->DistanceAttack,
//		p->AttackRate,
//		p->WeaponBonus,
//		p->ExellentDamage,
//		p->CriticalDamage,
//		p->Name);
//
//	LogAddC(LOGC_BLUE,"p->Name: %s", p->Name);
//
//	if(m_DBQuery.Exec(qSql) == FALSE)
//	{
//		return;
//	}
//
//	m_DBQuery.Clear();
//}
//
//#endif