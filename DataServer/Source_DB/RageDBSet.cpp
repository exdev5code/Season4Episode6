#include "StdAfx.h"
#include "RageDBSet.h"
#include "winutil.h"
#include "MainFrm.h"

cRageSystem::cRageSystem()
{
	// ----
}
// -----------------------------------------------------------------

cRageSystem::~cRageSystem()
{
	// ----
}
// -----------------------------------------------------------------
bool cRageSystem::Connect()
{
	return m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);
	//return CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

void RageSendError(int aIndex)
{
	DSRageUser rSend;
	ZeroMemory(&rSend,sizeof(rSend));
	rSend.h.c = PMHC_BYTE;
	rSend.h.size = sizeof(DSRageUser);
	rSend.h.headcode = 0xE0;
	rSend.aIndex = aIndex;
	rSend.Result = 0;
	wsjServer.DataSend(aIndex, (char*)&rSend, rSend.h.size);
}

void cRageSystem::DefaultRageChar(char *Name, int Type, int aIndex, int pIndex)
{
	CString qSql;

	//char NextSQLp[4096] = "CREATE TABLE RageSystem(Name varchar(10),RageLevel int,RagePoint int,RageExp int,";
	//strcat(NextSQLp, "Damage int,FreePoints int,SummonPet int,WingsDamagePlus int,FinalMana int,IgnoreDefence int,ResetLevel int,Teleport int,CriticalDamageRate int,AbsordDamage int,PetDamageBonus int,");
	//strcat(NextSQLp,"/*FinalLife*/ int,/*Strength*/ int,/*DefenceRate*/ int,/*FireDamage*/ int,/*Energy*/ int,Agility int,DoubleDamage int,FinalSD int,FinalDefence int,ZenDrop int,GuildBonus int,");
	//strcat(NextSQLp,"ReflectDamage int,ExellentDamageRate int,/*PvPBonusPlus*/ int,MinDefence int,Experience int,StartSD int,PartyBonus int,IceDamage int,DistanceAttack int,AttackRate int,WeaponBonus int,");
	//strcat(NextSQLp,"ExellentDamage int,CriticalDamage int);");

	char NextSQLpq[4096] = "INSERT INTO RageSystem (Name,RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
		strcat(NextSQLpq,"FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,");
		strcat(NextSQLpq,"WeaponBonus,ExellentDamage,CriticalDamage)");
		strcat(NextSQLpq,"VALUES ('%s',1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)");

	qSql.Format(NextSQLpq,Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		RageSendError(aIndex);
		return;
	}

	m_DBQuery.Clear();

	if(Type == 1 && aIndex >= 0 && pIndex >= 0)
	{
		char chBuffer[4024] = "SELECT RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
		strcat(chBuffer, " FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,WeaponBonus,ExellentDamage,CriticalDamage");
		strcat(chBuffer, " FROM RageSystem where Name = '%s'");

		//LogAddC(LOGC_BLUE,"Recv Name: %s", Recv->Name);

		qSql.Format(chBuffer, Name);

		if(m_DBQuery.Exec(qSql) == FALSE)
		{
			m_DBQuery.Clear();
			RageSendError(aIndex);
			return;
		}

		if(m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			RageSendError(aIndex);
			return;
		}

		DSRageUser rSend;

		rSend.h.c = PMHC_BYTE;
		rSend.h.size = sizeof(DSRageUser);
		rSend.h.headcode = 0xE0;

		rSend.aIndex = aIndex;
		rSend.Result = 1;

		rSend.rLevel = m_DBQuery.GetInt("RageLevel");
		rSend.rPoints = m_DBQuery.GetInt("RagePoint");
		rSend.rExperience = m_DBQuery.GetInt("RageExp");

		rSend.Damage = m_DBQuery.GetInt("Damage");	
		rSend.FreePoints = m_DBQuery.GetInt("FreePoints");
		rSend.SummonPet = m_DBQuery.GetInt("SummonPet");
		rSend.WingsDamagePlus = m_DBQuery.GetInt("WingsDamagePlus");
		rSend.FinalMana = m_DBQuery.GetInt("FinalMana");
		rSend.IgnoreDefence = m_DBQuery.GetInt("IgnoreDefence");
		rSend.ResetLevel = m_DBQuery.GetInt("ResetLevel");
		rSend.Teleport = m_DBQuery.GetInt("Teleport");
		rSend.CriticalDamageRate = m_DBQuery.GetInt("CriticalDamageRate");
		rSend.AbsordDamage = m_DBQuery.GetInt("AbsordDamage");
		rSend.PetDamageBonus = m_DBQuery.GetInt("PetDamageBonus");
		rSend.FinalLife = m_DBQuery.GetInt("FinalLife");
		rSend.Strength = m_DBQuery.GetInt("Strength");
		rSend.DefenceRate = m_DBQuery.GetInt("DefenceRate");
		rSend.FireDamage = m_DBQuery.GetInt("FireDamage");
		rSend.Energy = m_DBQuery.GetInt("Energy");
		rSend.Agility = m_DBQuery.GetInt("Agility");
		rSend.DoubleDamage = m_DBQuery.GetInt("DoubleDamage");
		rSend.FinalSD = m_DBQuery.GetInt("FinalSD");
		rSend.FinalDefence = m_DBQuery.GetInt("FinalDefence");
		rSend.ZenDrop = m_DBQuery.GetInt("ZenDrop");
		rSend.GuildBonus = m_DBQuery.GetInt("GuildBonus");
		rSend.ReflectDamage = m_DBQuery.GetInt("ReflectDamage");
		rSend.ExellentDamageRate = m_DBQuery.GetInt("ExellentDamageRate");
		rSend.PvPBonusPlus = m_DBQuery.GetInt("PvPBonusPlus");
		rSend.MinDefence = m_DBQuery.GetInt("MinDefence");
		rSend.Experience = m_DBQuery.GetInt("Experience");
		rSend.StartSD = m_DBQuery.GetInt("StartSD");
		rSend.PartyBonus = m_DBQuery.GetInt("PartyBonus");
		rSend.IceDamage = m_DBQuery.GetInt("IceDamage");
		rSend.DistanceAttack = m_DBQuery.GetInt("DistanceAttack");
		rSend.AttackRate = m_DBQuery.GetInt("AttackRate");
		rSend.WeaponBonus = m_DBQuery.GetInt("WeaponBonus");
		rSend.ExellentDamage = m_DBQuery.GetInt("ExellentDamage");
		rSend.CriticalDamage = m_DBQuery.GetInt("CriticalDamage");

		m_DBQuery.Clear();

		wsjServer.DataSend(pIndex, (char*)&rSend, rSend.h.size);

	}

	//wsjServer.DataSend(aIndex, (char*)&pMsgResult, pMsgResult.h.size);
}

void cRageSystem::SendRageUser(DSQuerySend * Recv, int aIndex)
{
	//char Name[11];

	//memcpy(Name, Recv->Name, MAX_IDSTRING);

	char Name[11];
	Name[MAX_IDSTRING] = '\0';
	memcpy(Name, Recv->Name, MAX_IDSTRING);

	CString qSql;

	char chBuffer[4024] = "SELECT RageLevel,RagePoint,RageExp,Damage,FreePoints,SummonPet,WingsDamagePlus,FinalMana,IgnoreDefence,ResetLevel,Teleport,CriticalDamageRate,AbsordDamage,PetDamageBonus,FinalLife,Strength,DefenceRate,";
	strcat(chBuffer, " FireDamage,Energy,Agility,DoubleDamage,FinalSD,FinalDefence,ZenDrop,GuildBonus,ReflectDamage,ExellentDamageRate,PvPBonusPlus,MinDefence,Experience,StartSD,PartyBonus,IceDamage,DistanceAttack,AttackRate,WeaponBonus,ExellentDamage,CriticalDamage");
	strcat(chBuffer, " FROM RageSystem where Name = '%s'");

	//LogAddC(LOGC_BLUE,"Recv Name: %s aIndex:%d", Recv->Name,aIndex);

	qSql.Format(chBuffer,Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		RageSendError(aIndex);
		return;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		this->DefaultRageChar(Name, 1, Recv->aIndex,aIndex);
		return;
	}

	DSRageUser rSend;

	rSend.h.c = PMHC_BYTE;
	rSend.h.size = sizeof(DSRageUser);
	rSend.h.headcode = 0xE0;

	rSend.aIndex = Recv->aIndex;
	rSend.Result = 1;

	rSend.Name[MAX_IDSTRING] = '\0';
	memcpy(rSend.Name, Name, MAX_IDSTRING);

	rSend.rLevel = m_DBQuery.GetInt("RageLevel");
	rSend.rPoints = m_DBQuery.GetInt("RagePoint");
	rSend.rExperience = m_DBQuery.GetInt("RageExp");

	rSend.Damage = m_DBQuery.GetInt("Damage");	
	rSend.FreePoints = m_DBQuery.GetInt("FreePoints");
	rSend.SummonPet = m_DBQuery.GetInt("SummonPet");
	rSend.WingsDamagePlus = m_DBQuery.GetInt("WingsDamagePlus");
	rSend.FinalMana = m_DBQuery.GetInt("FinalMana");
	rSend.IgnoreDefence = m_DBQuery.GetInt("IgnoreDefence");
	rSend.ResetLevel = m_DBQuery.GetInt("ResetLevel");
	rSend.Teleport = m_DBQuery.GetInt("Teleport");
	rSend.CriticalDamageRate = m_DBQuery.GetInt("CriticalDamageRate");
	rSend.AbsordDamage = m_DBQuery.GetInt("AbsordDamage");
	rSend.PetDamageBonus = m_DBQuery.GetInt("PetDamageBonus");
	rSend.FinalLife = m_DBQuery.GetInt("FinalLife");
	rSend.Strength = m_DBQuery.GetInt("Strength");
	rSend.DefenceRate = m_DBQuery.GetInt("DefenceRate");
	rSend.FireDamage = m_DBQuery.GetInt("FireDamage");
	rSend.Energy = m_DBQuery.GetInt("Energy");
	rSend.Agility = m_DBQuery.GetInt("Agility");
	rSend.DoubleDamage = m_DBQuery.GetInt("DoubleDamage");
	rSend.FinalSD = m_DBQuery.GetInt("FinalSD");
	rSend.FinalDefence = m_DBQuery.GetInt("FinalDefence");
	rSend.ZenDrop = m_DBQuery.GetInt("ZenDrop");
	rSend.GuildBonus = m_DBQuery.GetInt("GuildBonus");
	rSend.ReflectDamage = m_DBQuery.GetInt("ReflectDamage");
	rSend.ExellentDamageRate = m_DBQuery.GetInt("ExellentDamageRate");
	rSend.PvPBonusPlus = m_DBQuery.GetInt("PvPBonusPlus");
	rSend.MinDefence = m_DBQuery.GetInt("MinDefence");
	rSend.Experience = m_DBQuery.GetInt("Experience");
	rSend.StartSD = m_DBQuery.GetInt("StartSD");
	rSend.PartyBonus = m_DBQuery.GetInt("PartyBonus");
	rSend.IceDamage = m_DBQuery.GetInt("IceDamage");
	rSend.DistanceAttack = m_DBQuery.GetInt("DistanceAttack");
	rSend.AttackRate = m_DBQuery.GetInt("AttackRate");
	rSend.WeaponBonus = m_DBQuery.GetInt("WeaponBonus");
	rSend.ExellentDamage = m_DBQuery.GetInt("ExellentDamage");
	rSend.CriticalDamage = m_DBQuery.GetInt("CriticalDamage");

	m_DBQuery.Clear();

	wsjServer.DataSend(aIndex, (char*)&rSend, rSend.h.size);
}



void cRageSystem::SaveRageSkill(DSRageUserSAVE *p)
{
	CString qSql;

	char chBuffer[4024] = "UPDATE RageSystem SET RageLevel=%d, RagePoint=%d, RageExp=%d, Damage=%d, FreePoints=%d, SummonPet=%d, WingsDamagePlus=%d, FinalMana=%d, IgnoreDefence=%d, ResetLevel=%d, Teleport=%d, CriticalDamageRate=%d, AbsordDamage=%d, PetDamageBonus=%d, FinalLife=%d, Strength=%d, DefenceRate=%d, FireDamage=%d, ";

	strcat(chBuffer, " Energy=%d, ");
	strcat(chBuffer, " Agility=%d,  ");
	strcat(chBuffer, " DoubleDamage=%d, ");
	strcat(chBuffer, " FinalSD=%d, ");
	strcat(chBuffer, " FinalDefence=%d, ");
	strcat(chBuffer, " ZenDrop=%d, ");
	strcat(chBuffer, " GuildBonus=%d, ");

	strcat(chBuffer, " ReflectDamage=%d, ");	//ExAdd PCPoint
	strcat(chBuffer, " ExellentDamageRate=%d ");	//ExAdd ExFreePoints
	strcat(chBuffer, ", PvPBonusPlus=%d ");	//ExAdd Resets
	strcat(chBuffer, ", MinDefence=%d ");	//ExAdd GResets
	strcat(chBuffer, ", Experience=%d ");	//GensNumber
	strcat(chBuffer, ", StartSD=%d ");	//GensRang
	strcat(chBuffer, ", PartyBonus=%d ");	//GensExp
	strcat(chBuffer, ", IceDamage=%d ");	//GensReward
	strcat(chBuffer, ", DistanceAttack=%d ");
	strcat(chBuffer, ", AttackRate=%d ");
	strcat(chBuffer, ",WeaponBonus=%d ");
	strcat(chBuffer, ",ExellentDamage=%d ");
	strcat(chBuffer, ",CriticalDamage=%d ");
	strcat(chBuffer, " where Name = '%s' ");

	qSql.Format(chBuffer,p->rLevel,p->rPoints,p->rExperience,p->Damage,p->FreePoints,p->SummonPet,p->WingsDamagePlus,p->FinalMana,p->IgnoreDefence,p->ResetLevel,p->Teleport,p->CriticalDamageRate,p->AbsordDamage,p->PetDamageBonus,p->FinalLife,p->Strength,p->DefenceRate,p->FireDamage,
		p->Energy,
		p->Agility,
		p->DoubleDamage,
		p->FinalSD,
		p->FinalDefence,
		p->ZenDrop,
		p->GuildBonus,
		p->ReflectDamage,
		p->ExellentDamageRate,
		p->PvPBonusPlus,
		p->MinDefence,
		p->Experience,
		p->StartSD,
		p->PartyBonus,
		p->IceDamage,
		p->DistanceAttack,
		p->AttackRate,
		p->WeaponBonus,
		p->ExellentDamage,
		p->CriticalDamage,
		p->Name);

	LogAddC(LOGC_BLUE,"p->Name: %s", p->Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return;
	}

	m_DBQuery.Clear();
}