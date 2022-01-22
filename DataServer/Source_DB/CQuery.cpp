// API ������Ʈ�� ���� ��� ���� �� ���� ���Խ��� �ָ� �ȴ�.
#include <windows.h>


// MFC ������Ʈ�� ���� ���� stdafx.h�� CQuery.h�� ���Խ��� �ְ� ���� ���ٸ�
// ������ �ȴ�.
#include "stdafx.h"
#include "DelayHandler.h"

// ������:���� �ʱ�ȭ�� ����Ѵ�.
CQuery::CQuery()
{
	AffectCount=-1;
	ret=SQL_SUCCESS;

	// ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.
	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv);
	SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
}

// �ı���:���� �ڵ��� �����Ѵ�.
CQuery::~CQuery()
{
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
}

// ���� �ڵ��� �Ҵ��ϰ� ������ �� ����ڵ���� ���� �Ҵ��Ѵ�.
// Type=1:ConStr�� MDB ������ ��θ� ������. ��� ������ ���� ���丮���� MDB�� ã�´�.
// Type=2:ConStr�� SQL ������ ���� ������ ������ DSN ������ ��θ� ������. 
//        ��δ� �ݵ�� ���� ��η� �����ؾ� �Ѵ�.
// Type=3:SQLConnect �Լ��� DSN�� ���� �����Ѵ�.
// ���� �Ǵ� ��� �ڵ� �Ҵ翡 �����ϸ� FALSE�� �����Ѵ�.
BOOL CQuery::Connect(int Type, char *ConStr, char *UID, char *PWD)
{
	SQLCHAR InCon[255];
	SQLCHAR OutCon[255];
    SQLSMALLINT cbOutCon;

	int ii=1;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	m_Type = Type;
	strcpy(m_szConnect, ConStr);
	strcpy(m_Id, UID);
	strcpy(m_Pass, PWD);

	// ���� Ÿ�Կ� ���� MDB �Ǵ� SQL ����, �Ǵ� DSN�� �����Ѵ�.
	SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc);
	switch (Type) {
	case 1:
		wsprintf((char *)InCon,"DRIVER={Microsoft Access Driver (*.mdb)};DBQ=%s;",ConStr);
		ret=SQLDriverConnect(hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,
			sizeof(OutCon),&cbOutCon, SQL_DRIVER_NOPROMPT);
		break;
	case 2:
		wsprintf((char *)InCon, "FileDsn=%s",ConStr);
		ret=SQLDriverConnect(hDbc,NULL,(SQLCHAR *)InCon,sizeof(InCon),OutCon,
			sizeof(OutCon),&cbOutCon, SQL_DRIVER_NOPROMPT);
		break;
	case 3:
		ret=SQLConnect(hDbc,(SQLCHAR *)ConStr,SQL_NTS,(SQLCHAR *)UID,SQL_NTS,
			(SQLCHAR *)PWD,SQL_NTS);
		break;
	}

	// ���� ������ ���� ������ �����ش�.
	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
		while (Ret=SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, ii, SqlState, &NativeError, 
			Msg, sizeof(Msg), &MsgLen)!=SQL_NO_DATA) {
			wsprintf(str, "(1) SQLSTATE:%s, Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
			//::MessageBox(NULL,str,"���� ����",0);
			LogAddTD(str);
			ii++;
		}
		return FALSE;
	}

	// ��� �ڵ��� �Ҵ��Ѵ�.
	ret=SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt);
	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO)) {
		hStmt=0;
		return FALSE;
	}

	// ==========

	struct Temp
	{  
		char AddQuery[255];
		char Column[35];	  
		char Table[35];
	};

	Temp QueryMuOnline[] = 
	{	
		{"alter table [Character] add [gr_res] int not null default(0)","gr_res","Character"},
		{"alter table [Character] add [pcpoint] int not null default(0)","pcpoint","Character"},
		{"alter table [Character] add [ExFreePoints] int not null default(0)","ExFreePoints","Character"},
		{"alter table [Character] add [ExQuestNum] int not null default(0)","ExQuestNum","Character"},
		{"alter table [Character] add [ExQuestKill] int not null default(0)","ExQuestKill","Character"},
//#ifdef PREMIUM_SYSTEM
		{"alter table [Character] add [PremiumTime] int not null default(0)","PremiumTime","Character"},
//#endif
//#if __ExGames__
		{"alter table [Character] add [ChatBanTime] int not null default(0)","ChatBanTime","Character"},
//#endif
//#if __MuRain__
		{"alter table [Character] add [NoobTime] int not null default(0)","NoobTime","Character"},
//#endif
//#ifdef __MuReal__
		{"alter table [Character] add [OffAfk] int not null default(0)","OffAfk","Character"},
		{"alter table [Character] add [VipTime] int not null default(0)","VipTime","Character"},
		{"alter table [Character] add [CR] int not null default(0)","CR","Character"},
//#endif
		{"alter table [Character] add [ExCred] int not null default(0)","ExCred","Character"},
//#ifdef _MULTI_VAULT_
		{"alter table [warehouse] add [Items2] varbinary(3840)","Items2","warehouse"},
		{"alter table [warehouse] add [Items3] varbinary(3840)","Items3","warehouse"},
		{"alter table [warehouse] add [Items4] varbinary(3840)","Items4","warehouse"},
		{"alter table [warehouse] add [Items5] varbinary(3840)","Items5","warehouse"},
//#endif
		{"alter table [Character] add [BMQuest_num] int not null default(0)","BMQuest_num","Character"},//int BMQuest_num;
		{"alter table [Character] add [BMQuest_kill] int not null default(0)","BMQuest_kill","Character"},//int BMQuest_kill;
		{"alter table [Character] add [BMQuest_start] int not null default(0)","BMQuest_start","Character"},//int BMQuest_start;
		{"alter table [Character] add [BMDamageReflect] int not null default(0)","BMDamageReflect","Character"},//int BMDamageReflect;
		{"alter table [Character] add [BMDamage] int not null default(0)","BMDamage","Character"},//int BMDamage;
		{"alter table [Character] add [BMDefense] int not null default(0)","BMDefense","Character"},//int BMDefense;
		{"alter table [Character] add [BMCriticalDamage] int not null default(0)","BMCriticalDamage","Character"},//int BMCriticalDamage;
		{"alter table [Character] add [BMExcelentDamage] int not null default(0)","BMExcelentDamage","Character"},//int BMExcelentDamage;
		{"alter table [Character] add [BMLife] int not null default(0)","BMLife","Character"},//int BMLife;

		{"alter table [Character] add [ChaosBank] int not null default(0)","ChaosBank","Character"},
		{"alter table [Character] add [BlessBank] int not null default(0)","BlessBank","Character"},
		{"alter table [Character] add [SoulBank] int not null default(0)","SoulBank","Character"},
		{"alter table [Character] add [LifeBank] int not null default(0)","LifeBank","Character"},



#ifdef _CR_MEMB_INFO_
		{"alter table [MEMB_INFO] add [ExCredit] int not null default(0)","ExCredit","MEMB_INFO"},
#endif

		{"alter table [MEMB_INFO] add [MTDate] int not null default(0)","MTDate","MEMB_INFO"},

		//{"alter table [Character] add [BMQuest_num] int not null default(0)","BMQuest_num","Character"},//
	};

	for(int i=0;i<(sizeof(QueryMuOnline)/sizeof(QueryMuOnline[0]));i++)
	{
		char SendQuery[257] = {0};

		sprintf(SendQuery,"SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.Columns where COLUMN_NAME = '%s' and TABLE_NAME = '%s'",QueryMuOnline[i].Column,QueryMuOnline[i].Table);

		//if(this->Exec(SendQuery) == FALSE)
		{
		//	if (this->Fetch()==SQL_NO_DATA) 
			{
				//this->Clear();

				this->Exec(QueryMuOnline[i].AddQuery);
				this->Fetch();
				this->Clear();
				//LogAdd(QueryMuOnline[i].AddQuery);
			}
		}
	}

#ifdef _RAGE_SYSTEM_
	char NextSQLp[4096] = "CREATE TABLE RageSystem(Name varchar(10),RageLevel int,RagePoint int,RageExp int,";
	strcat(NextSQLp, "Damage int,FreePoints int,SummonPet int,WingsDamagePlus int,FinalMana int,IgnoreDefence int,ResetLevel int,Teleport int,CriticalDamageRate int,AbsordDamage int,PetDamageBonus int,");
	strcat(NextSQLp,"FinalLife int,Strength int,DefenceRate int,FireDamage int,Energy int,Agility int,DoubleDamage int,FinalSD int,FinalDefence int,ZenDrop int,GuildBonus int,");
	strcat(NextSQLp,"ReflectDamage int,ExellentDamageRate int,PvPBonusPlus int,MinDefence int,Experience int,StartSD int,PartyBonus int,IceDamage int,DistanceAttack int,AttackRate int,WeaponBonus int,");
	strcat(NextSQLp,"ExellentDamage int,CriticalDamage int);");
	this->Exec(NextSQLp);
	this->Fetch();
	this->Clear();
#endif

	// ==========

	return TRUE;
}

BOOL CQuery::ReConnect()
{
	return Connect(m_Type, m_szConnect, m_Id, m_Pass);
}

// SQL���� �����Ѵ�. ���н� ���� ������ ����ϰ� FALSE�� �����Ѵ�.
BOOL CQuery::Exec(LPCTSTR szSQL)
{
	int c;

	while( true )
	{		
		LogAddTD("%s", szSQL);
		// SQL���� �����Ѵ�. SQL_NO_DATA�� ������ ��쵵 �ϴ� �������� ����Ѵ�. 
		// �� ��� Fetch���� EOF�� �����ϵ��� �Ǿ� �ֱ� ������ ���� ������ ����� �ʿ�� ����.
		ret=SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);
		if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
		{			
			bool bReConnect = false;

			PrintDiag(bReConnect);

			Clear();

			if(bReConnect == true)
			{
				::Sleep(1);
				continue;
			}
			return FALSE;
		}

		// Update, Delete, Insert ��ɽ� ������� ���ڵ� ������ ���� ���´�.
		SQLRowCount(hStmt,&AffectCount);

		SQLNumResultCols(hStmt,&nCol);
		if (nCol > MAXCOL) {
			//::MessageBox(NULL,"�ִ� �÷� ���� �ʰ��߽��ϴ�","CQuery ����",MB_OK);
			LogAdd("CQuery error :�ִ� �÷� ���� �ʰ��߽��ϴ�");
			return FALSE;
		}

		// nCol�� 0�� ���� Select�� �̿��� �ٸ� ����� ������ ����̹Ƿ� 
		// ���ε��� �� �ʿ䰡 ����.
		if (nCol == 0) {
			Clear();
			return TRUE;
		}

		// ��� �÷��� ���ڿ��� ���ε��� ���´�. Col�迭�� zero base, 
		// �÷� ��ȣ�� one base�ӿ� ������ ��
		for (c=0;c<nCol;c++) {
			SQLBindCol(hStmt,c+1,SQL_C_CHAR,Col[c],255,&lCol[c]);
			SQLDescribeCol(hStmt,c+1,ColName[c],30,NULL,NULL,NULL,NULL,NULL);
		}
		return TRUE;
	}
}

// SQL���� �����ϰ� ������� ù Į������ �������� �о� ������ �ش�. 
// ����� ���� �� �������� �� �ش�.
int CQuery::ExecGetInt(LPCTSTR szSQL)
{
	int i;

	//LogAdd("%s", szSQL);

	if (Exec(szSQL) == FALSE) 
		return CQUERYERROR;

	// �����Ͱ� ���� ��� EOF�� �����Ѵ�.
	if (Fetch()==SQL_NO_DATA) {
		Clear();
		return CQUERYEOF;
	}
	i=GetInt(1);
	Clear();
	return i;
}

int CQuery::ExecGetInt(char* szSQL, int * retvalue)
{
	LogAddTD("%s", szSQL);

	if (Exec(szSQL) == FALSE) 
	{
		return FALSE;
	}


	if (Fetch()==SQL_NO_DATA) 
	{
		Clear();

		return FALSE;
	}

	int i=GetInt(1);
	Clear();
	*retvalue = i;
	
	return TRUE;
}

// SQL���� �����ϰ� ������� ù Į������ ���ڿ��� �о� ������ �ش�.
BOOL CQuery::ExecGetStr(LPCTSTR szSQL, char *buf)
{
//	LogAdd("%s", szSQL);

	// SQL�� ������ ������ �߻��� ��� ���ڿ� ���ۿ� ������ ���� ������.
	if (Exec(szSQL) == FALSE) {
		//strcpy(buf, "CQUERYERROR");
		buf[0] = '\0';
		return FALSE;
	}

	// �����Ͱ� ���� ��� EOF�� �����Ѵ�.
	if (Fetch()==SQL_NO_DATA) {
		Clear();
		//strcpy(buf,"EOF");
		buf[0] = '\0';
		return FALSE;
	}
	GetStr(1,buf);
	Clear();
	return TRUE;
}

// ����¿��� �� ���� �����´�.
SQLRETURN CQuery::Fetch()
{
	ret=SQLFetch(hStmt);
	return ret;
}

// Ŀ���� �ݰ� ���ε� ������ �����Ѵ�.
void CQuery::Clear()
{
	SQLCloseCursor(hStmt);
	::SQLFreeStmt(hStmt, SQL_UNBIND);
}

// �÷� �̸����κ��� �÷� �ε����� ã�´�. ���� ��� -1�� �����Ѵ�.
int CQuery::FindCol(char *name)
{
	int i;
	for (i=0;i<nCol;i++) {
		if (stricmp(name,(LPCTSTR)ColName[i])==0)
			return i+1;
	}
	return -1;
}

// nCol�� �÷����� ������ �о��ش�. NULL�� ��� CQUERYNULL�� �����Ѵ�.
int CQuery::GetInt(int nCol)
{
	if (nCol > nCol)
		return CQUERYNOCOL;

	if (lCol[nCol-1]==SQL_NULL_DATA) {
		return CQUERYNULL;
	} else {
		return atoi(Col[nCol-1]);
	}
}

// sCol�� �÷����� ������ �о��ش�.
int CQuery::GetInt(char *sCol)
{
	int n;
	n=FindCol(sCol);
	if (n==-1) {
		return CQUERYNOCOL;
	} else {
		return GetInt(n);
	}
}

__int64 CQuery::GetInt64(int nCol)
{
	if (nCol > nCol)
	{
		return CQUERYNOCOL;
	}

	if (lCol[nCol-1]==SQL_NULL_DATA) 
	{
		return CQUERYNULL;
	} 
	else 
	{
		return _atoi64(Col[nCol-1]);
	}

}

__int64 CQuery::GetInt64(char* sCol)
{
	int n;
	n = FindCol(sCol);

	if (n==-1) 
	{
		return CQUERYNOCOL;
	} 
	else 
	{
		return GetInt64(n);
	}
}

// nCol�� �÷����� �Ǽ��� �о��ش�. NULL�� ��� CQUERYNULL�� �����Ѵ�.
float CQuery::GetFloat(int nCol)
{
	if (nCol > nCol)
		return CQUERYNOCOL;

	if (lCol[nCol-1]==SQL_NULL_DATA) {
		return CQUERYNULL;
	} else {
		return (float)atof(Col[nCol-1]);
	}
}

// sCol�� �÷����� �Ǽ��� �о��ش�.
float CQuery::GetFloat(char *sCol)
{
	int n;
	n=FindCol(sCol);
	if (n==-1) {
		return CQUERYNOCOL;
	} else {
		return GetFloat(n);
	}
}


// nCol�� �÷����� ���ڿ��� �о��ش�. NULL�� ��� ���ڿ��� NULL�� ä���ش�. 
// buf�� ���̴� �ּ��� 256�̾�� �ϸ� ���� ������ ���� �ʴ´�.
void CQuery::GetStr(int nCol, char *buf)
{
	if (nCol > nCol) {
		//strcpy(buf, "CQUERYNOCOL");
		buf[0] = '\0';
		return;
	}

	if (lCol[nCol-1]==SQL_NULL_DATA) 
	{
		buf[0] = '\0';
		//lstrcpy(buf,"NULL");
	} else {
		lstrcpy(buf,Col[nCol-1]);
	}
}

// sCol�� �÷����� ���ڿ��� �о��ش�.
void CQuery::GetStr(char *sCol, char *buf)
{
	int n;
	n=FindCol(sCol);
	if (n==-1) {
		//lstrcpy(buf,"ERROR:Colume not found");
		buf[0] = '\0';
	} else {
		GetStr(n, buf);
	}
}

// ���� �߻��� ���� ������ ����� �ش�.
void CQuery::PrintDiag(bool &bReconnect)
{
	int ii;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	char str[256];

	ii=1;
	while (Ret=SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, ii, SqlState, &NativeError, 
		Msg, sizeof(Msg), &MsgLen)!=SQL_NO_DATA) {
		wsprintf(str, "(2) SQLSTATE:%s, Diagnosis:%s",(LPCTSTR)SqlState,(LPCTSTR)Msg);
		//::MessageBox(NULL,str,"���� ����",0);
		LogAddTD(str);
		//LogAdd(str);
		ii++;
		if(ii > 3) break;
	}

	// ������ ��� �������.. �ٽ� ������ ����.
	if( strcmp((LPCTSTR)SqlState, "08S01") == 0 )
	{
		if(ReConnect() == 1) g_DelayHandler.IncreaseQuerySessionId();

		bReconnect = true;
	}
	// ���� �Ұ����� ������ �߻��� ��� ���α׷��� �����Ѵ�. �ش��� ���� ó���� ���ʿ���
	// ���� �� �ڵ带 �ּ� ó���ϰų� �����ϰ� �ٸ� ��ƾ���� �ٲ�� �Ѵ�.
/*	if (ii > 1) {
		::MessageBox(NULL,"���� ������ ��µǾ����ϴ�. �� ������ ��µ� ���� ��Ʈ�� ����, DB ���� ���� ����\r\n"
			"���� �Ұ����� ������ �߻��� ����̸� ���α׷� ������ ����� �� �����ϴ�.\r\n"
			"������ �����Ͻ� �� ���α׷��� �ٽ� ������ �ֽʽÿ�.","Critical Error",MB_OK | MB_ICONERROR);

		// ���� �� �� �ϳ��� ������ ��
		PostQuitMessage(0);
		// ExitProcess(0);
	}
*/
}

// BLOB �����͸� buf�� ä���ش�. �̶� buf�� ����� ũ���� �޸𸮸� �̸� �Ҵ��� 
// ���ƾ� �Ѵ�. NULL�� ��� 0�� �����ϰ� ���� �߻��� -1�� �����Ѵ�. ������ ���� 
// �� ����Ʈ ���� �����Ѵ�. szSQL�� �ϳ��� BLOB �ʵ带 �д� Select SQL���̾�� �Ѵ�.
int CQuery::ReadBlob(LPCTSTR szSQL, void *buf)
{
	SQLCHAR BinaryPtr[BLOBBATCH];
	SQLINTEGER LenBin;
	char *p;
	int nGet;
	int TotalGet=0;

	//LogAdd("%s", szSQL);

	while( true )
	{
		ret=SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);
		if (ret!=SQL_SUCCESS)
		{
			bool bReconnect = false;

			PrintDiag(bReconnect);

			if(bReconnect == true){
				::Sleep(1);
				continue;
			}

			return -1;
		}

		while ((ret=SQLFetch(hStmt)) != SQL_NO_DATA) {
			p=(char *)buf;
			while ((ret=SQLGetData(hStmt,1,SQL_C_BINARY,BinaryPtr,sizeof(BinaryPtr),
				&LenBin))!=SQL_NO_DATA) {
				if (LenBin==SQL_NULL_DATA) {
					Clear();
					return 0;
				}
				if (ret==SQL_SUCCESS)
					nGet=LenBin;
				else
					nGet=BLOBBATCH;
				TotalGet+=nGet;
				memcpy(p,BinaryPtr,nGet);
				p+=nGet;
			}
		}
		Clear();
		return TotalGet;
	}
}

// buf�� BLOB �����͸� �����Ѵ�. szSQL�� �ϳ��� BLOB �����͸� �����ϴ� Update, Insert
// SQL���̾�� �Ѵ�.
void CQuery::WriteBlob(LPCTSTR szSQL, void *buf, int size)
{
	SQLINTEGER cbBlob;
	char tmp[BLOBBATCH],*p;
	SQLPOINTER pToken;
	int nPut;

	//LogAdd("%s", szSQL);

	cbBlob=SQL_LEN_DATA_AT_EXEC(size);
	SQLBindParameter(hStmt,1,SQL_PARAM_INPUT,SQL_C_BINARY,SQL_LONGVARBINARY,
		size,0,(SQLPOINTER)1,0,&cbBlob);
	SQLExecDirect(hStmt,(SQLCHAR *)szSQL,SQL_NTS);
	ret=SQLParamData(hStmt, &pToken);
	while (ret==SQL_NEED_DATA) {
		if (ret==SQL_NEED_DATA) {
			if ((int)pToken==1) {
				for (p=(char *)buf;p<(char *)buf+size;p+=BLOBBATCH) {
					nPut=min(BLOBBATCH,(char *)buf+size-p);
					memcpy(tmp,p,nPut);
					SQLPutData(hStmt,(PTR)tmp,nPut);
				}
			}
		}
		ret=SQLParamData(hStmt, &pToken);
	}
	Clear();
}

int CQuery::BindParameterBinaryOutput(int nCol, BYTE *nValue, int iSize, long *lLength)
{
	int iRet = SQLBindParameter(hStmt, nCol, 4, -2, -3, iSize, 0, nValue, iSize, lLength);
	return iRet;
}