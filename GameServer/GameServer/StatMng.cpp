//	GS-N	1.00.90	JPN		-	Completed
//	GS-CS	1.00.90	JPN		-	Completed
#include "stdafx.h"
#include "StatMng.h"
#include "user.h"

CStatMng gStatMng;

CStatMng::CStatMng()
{
	this->Init();
}

CStatMng::~CStatMng()
{
	return;
}

void CStatMng::Init()
{
	int firstState = 2;
	int MagunfirstState = 2;
	int iDarkLordFirstState = 2;

	for (int i=0;i<STAT_TABLE_SIZE;i++)
	{
		if ( ( (i+1) % 10) == 0)
		{
			firstState +=  3 * ( i + 11 ) / 400 + 2;//Season 4.5 changed
			MagunfirstState += 3 * ( i + 11 ) / 700 + 2;//Season 4.5 changed
			iDarkLordFirstState += 3 * ( i + 11 ) / 500 + 2;//Season 4.5 changed
		}

		this->gObjNormalAddStatTable[i] = firstState;
		this->gObjMagumAddStatTable[i] = MagunfirstState;
		this->gObjDarkLordAddStatTable[i] = iDarkLordFirstState;
	}

	firstState = 2;
	MagunfirstState = 2;
	iDarkLordFirstState = 2;

	for (int i=0;i<STAT_TABLE_SIZE;i++)
	{
		if ( ( (i+1) % 10) == 0)
		{
			firstState += 3 * ( i + 11 ) / 400 + 2;//Season 4.5 changed
			MagunfirstState += 3 * ( i + 11) / 700 + 2;//Season 4.5 changed
			iDarkLordFirstState += 3 * ( i + 11 ) / 500 + 2;//Season 4.5 changed
		}

		this->gObjNormalMinusStatTable[i] = firstState;
		this->gObjMagumMinusStatTable[i] = MagunfirstState;
		this->gObjDarkLordMinusStatTable[i] = iDarkLordFirstState;
	}
}


int CStatMng::GetMaxStat(int level, int Class)
{
	if ( (level < 1) || (level> MAX_CHAR_LEVEL) )
	{
		return 0;
	}

	if (Class == CLASS_MAGUMSA)
	{
		return this->gObjMagumAddStatTable[level-1];
	}
	
	if ( Class == CLASS_DARKLORD )
	{
		return this->gObjDarkLordAddStatTable[level-1];
	}
	
	return this->gObjNormalAddStatTable[level-1];
}


int CStatMng::GetMaxMinusStat(int iLevel, int iClass)
{
	if ( (iLevel < 1) || (iLevel> MAX_CHAR_LEVEL) )
	{
		return 0;
	}

	if ( iClass == CLASS_MAGUMSA)
	{
		return this->gObjMagumMinusStatTable[iLevel-1];
	}
	
	if ( iClass == CLASS_DARKLORD )
	{
		return this->gObjDarkLordMinusStatTable[iLevel-1];
	}
	
	return this->gObjNormalMinusStatTable[iLevel-1];
}