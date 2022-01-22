// AccountCharDBSet.cpp: implementation of the CAccountCharDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AccountCharDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccountCharDBSet::CAccountCharDBSet()
{

}

CAccountCharDBSet::~CAccountCharDBSet()
{

}

BOOL CAccountCharDBSet::Connect()
{
	if(m_DBQuery.Connect(3,szDbConnectDsn,szDbConnectID,szDbConnectPass) == FALSE)
	{
		MsgBox("계정정보 DB 접속 실패");
		return FALSE;
	}

	return TRUE;
}

BOOL CAccountCharDBSet::CreateAccountCharacter(char* id)
{
	CString qSQL;
	qSQL.Format("INSERT AccountCharacter (Id) VALUES ('%s')", id);
	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}

int CAccountCharDBSet::DeleteAccountCharacter(char* id, char* gameid)
{
	CString qSQL;
	char gid[MAX_IDSTRING+1];

	qSQL.Format("SELECT * FROM AccountCharacter where Id='%s'", id);
	
	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return -1;
	}

	m_DBQuery.GetStr("GameID1", gid);

	if(strcmp(gid, gameid) == 0)
	{
		m_DBQuery.Clear();
		SaveAccountCharacter(id, 0, "");
		return 0;
	}

	m_DBQuery.GetStr("GameID2", gid);

	if(strcmp(gid, gameid) == 0)
	{
		m_DBQuery.Clear();
		SaveAccountCharacter(id, 1, "");
		return 1;
	}

	m_DBQuery.GetStr("GameID3", gid);

	if(strcmp(gid, gameid) == 0)
	{
		m_DBQuery.Clear();
		SaveAccountCharacter(id, 2, "");
		return 2;
	}

	m_DBQuery.GetStr("GameID4", gid);

	if(strcmp(gid, gameid) == 0)
	{
		m_DBQuery.Clear();
		SaveAccountCharacter(id, 3, "");
		return 3;
	}

	m_DBQuery.GetStr("GameID5", gid);

	if(strcmp(gid, gameid) == 0)
	{
		m_DBQuery.Clear();
		SaveAccountCharacter(id, 4, "");
		return 4;
	}

	m_DBQuery.Clear();
	
	return -1;
}

BOOL CAccountCharDBSet::SaveAccountCharacter(char* id, char* GameID1, char* GameID2, char* GameID3, char* GameID4, char* GameID5)
{
	CString qSQL;

	qSQL.Format("UPDATE AccountCharacter SET GameID1='%s',GameID2='%s', GameID3='%s', GameID4='%s', GameID5='%s'  WHERE Id='%s'", GameID1, GameID2, GameID3, GameID4, GameID5, id);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CAccountCharDBSet::SaveAccountCharacter(char* id, int pos, char* GameID)
{
	CString qSQL;

	switch(pos)
	{
	case 0:
		qSQL.Format("UPDATE AccountCharacter SET GameID1='%s' WHERE Id='%s'", GameID, id);
		break;
	case 1:
		qSQL.Format("UPDATE AccountCharacter SET GameID2='%s' WHERE Id='%s'", GameID, id);
		break;
	case 2:
		qSQL.Format("UPDATE AccountCharacter SET GameID3='%s' WHERE Id='%s'", GameID, id);
		break;
	case 3:
		qSQL.Format("UPDATE AccountCharacter SET GameID4='%s' WHERE Id='%s'", GameID, id);
		break;
	case 4:
		qSQL.Format("UPDATE AccountCharacter SET GameID5='%s' WHERE Id='%s'", GameID, id);
		break;
	default:
		LogAdd("error : %s %d pos: %d ", __FILE__, __LINE__, pos);
		break;
	}

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CAccountCharDBSet::GetAccountId(char* Id)
{
	CString qSQL;

	qSQL.Format("SELECT Id FROM AccountCharacter WHERE Id='%s'", Id);

	char buffer[256];

	if (m_DBQuery.ExecGetStr(qSQL, buffer) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAccountCharDBSet::GetAccountInfo(char* Id, LPAccountCharacterInfo lpACInfo)
{
	CString qSQL;

	qSQL.Format("SELECT * FROM AccountCharacter WHERE Id='%s'", Id);

	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;		
	}

	m_DBQuery.GetStr("Id", lpACInfo->AccountId);
	
	if( strlen(lpACInfo->AccountId) < 1 )
	{
		m_DBQuery.Clear();
		return FALSE;		
	}

	if( strcmp(lpACInfo->AccountId,Id) != 0)
	{
		LogAddC(2,"error-L1:'%s' '%s' 아이디가 같지 않다.", lpACInfo->AccountId, Id);
		m_DBQuery.Clear();
		return FALSE;		
	}
	
	int ctl_code = 0;
	
	lpACInfo->DBNumber = m_DBQuery.GetInt("Number");
	
	m_DBQuery.GetStr("GameID1", lpACInfo->GameID1);
	m_DBQuery.GetStr("GameID2", lpACInfo->GameID2);
	m_DBQuery.GetStr("GameID3", lpACInfo->GameID3);
	m_DBQuery.GetStr("GameID4", lpACInfo->GameID4);
	m_DBQuery.GetStr("GameID5", lpACInfo->GameID5);
	
	int movecount = m_DBQuery.GetInt("MoveCnt");
	
	if (movecount < 0)
	{
		movecount = 0;
	}

	lpACInfo->MoveCnt = movecount;

	LogAddTD("CharName : %s 1[%s] 2[%s] 3[%s] 4[%s] 5[%s]", Id, lpACInfo->GameID1, lpACInfo->GameID2, lpACInfo->GameID3, lpACInfo->GameID4, lpACInfo->GameID5);
	
	m_DBQuery.Clear();
	return TRUE;
}

BYTE CAccountCharDBSet::GetAccountCharCtlCode(char* Id)
{
	CString qSQL;
	
	int ctl_code = 0;
	
	qSQL.Format("SELECT CtlCode FROM AccountCharacter WHERE Id=%s",Id);
	
	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		LogAdd("%s CtlCode가 없다. #1", Id);
		return 0;
	}
	
	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		LogAdd("%s CtlCode가 없다. #2", Id);
		return 0;		
	}
	
	ctl_code = m_DBQuery.GetInt("CtlCode");
	
	if (ctl_code < 0)
	{
		ctl_code = 0;
	}
	
	m_DBQuery.Clear();
	
	return ctl_code;
}

int CAccountCharDBSet::GetAccountCharBlank(char* Id)
{
	CString qSQL;

	char GameID[5][MAX_IDSTRING+1];
	char szAccountId[MAX_IDSTRING+1];

	qSQL.Format("SELECT * FROM AccountCharacter WHERE Id='%s'", Id);

	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		m_DBQuery.Clear();
		return 0;
	}
	
	m_DBQuery.Fetch();
	m_DBQuery.GetStr("Id", szAccountId);
	
	if ( strlen(szAccountId) < 1)
	{
		LogAdd("계정이 없다. 1");
		m_DBQuery.Clear();
		return -1;	
	}
	
	if ( strcmp(szAccountId,Id) != 0)
	{
		LogAdd("계정이 없다. 2 %s %s", szAccountId, Id);
		m_DBQuery.Clear();
		return -1;	
	}
	
	m_DBQuery.GetStr("GameID1",GameID[0]);
	
	if ( strlen(GameID[0]) < 1)
	{
		m_DBQuery.Clear();
		return 0;			
	}
	
	m_DBQuery.GetStr("GameID2",GameID[1]);
	
	if ( strlen(GameID[1]) < 1)
	{
		m_DBQuery.Clear();
		return 1;			
	}
	
	m_DBQuery.GetStr("GameID3",GameID[2]);
	
	if ( strlen(GameID[2]) < 1)
	{
		m_DBQuery.Clear();
		return 2;			
	}
	
	m_DBQuery.GetStr("GameID4",GameID[3]);
	
	if ( strlen(GameID[3]) < 1)
	{
		m_DBQuery.Clear();
		return 3;			
	}
	
	m_DBQuery.GetStr("GameID5",GameID[4]);
	
	if ( strlen(GameID[4]) < 1)
	{
		m_DBQuery.Clear();
		return 4;			
	}

	m_DBQuery.Clear();
	
	return -1;
}

BOOL CAccountCharDBSet::CurAccountCharacterSet(char* id, char* GameID)
{
	CString qSQL;
	
	qSQL.Format("UPDATE AccountCharacter SET GameIDC='%s' WHERE Id='%s'", GameID, id);
	
	m_DBQuery.Exec(qSQL);
	
	return TRUE;
}

BOOL CAccountCharDBSet::GetSummonerCardInfo(char* Id)
{
	CString qSQL;
	
	qSQL.Format("SELECT Summoner FROM AccountCharacter WHERE Id = '%s'", Id);
	
	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}
	
	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;		
	}
	
	if (m_DBQuery.GetInt(1) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;	
	}
	
	m_DBQuery.Clear();
	return TRUE;
}

BOOL CAccountCharDBSet::SetSummonerCardInfo(char* Id)
{
	CString qSQL;
	
	qSQL.Format("UPDATE AccountCharacter SET Summoner = 1 WHERE Id = '%s'", Id);
	
	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}
	
	return TRUE;
}

int CAccountCharDBSet::WcoinSelect(char* Acc,int count,int type)
{
	CString qSQL;

	if(type == 1)
	{
		qSQL.Format("UPDATE MEMB_INFO SET cspoints = cspoints + %d WHERE memb___id='%s'",count,Acc);
	}
	else if(type == 2)
	{
		qSQL.Format("UPDATE MEMB_INFO SET cspoints = cspoints - %d WHERE memb___id='%s'",count,Acc);
	}

	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		m_DBQuery.Clear();
		return 0;
	}
	
	return count;
	//return wcoin;
}