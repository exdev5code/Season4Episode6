#ifndef MAPCLASS_H
#define MAPCLASS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\zzzitem.h"
#include "..\common\zzzpath.h"
#include "MapItem.h"
#ifdef _GRAND_HERO_SYSTEM_
#define MAX_NUMBER_MAP 90 //51 Season2.5 57 Season3
#else
#define MAX_NUMBER_MAP 65
#endif

#define MAX_MAPITEM	300

#define MAX_MAP_RANGE(x) (((x)<0)?FALSE:((x)>MAX_NUMBER_MAP-1)?FALSE:TRUE)
#define MAX_ITEM_TYPE_RANGE(x) ( ((x)<0)?FALSE:((x)>MAX_MAPITEM-1)?FALSE:TRUE   )

class MapClass
{

public:

	void SaveItemInfo();
	void GetLevelPos( short level, short& ox, short& oy);
	void GetMapPos(short Map, short& ox, short& oy);
	void GetRandomLengthPos(short& x, short& y, int length);
	void SearchStandAttr(short& x, short& y);
	BOOL AttrLoad(char* filename);
	void LoadMapAttr(char* filename, int MapNumber);
	BOOL CheckWall(int sx1, int sy1, int sx2, int sy2);
	BYTE CheckWall2(int sx1, int sy1, int sx2, int sy2);
	void ItemInit();
	int ItemGive(int aIndex, int item_num, bool bFailNotSend);
	int ItemDrop(int type, int level, float dur,  int x, int y, BYTE Option1, BYTE Option2, BYTE Option3, BYTE NOption, BYTE SOption, DWORD number, int aIndex, int PetLevel, int PetExp, BYTE ItemEffectEx, BYTE SocketOption[5], BYTE SocketIndex);
	int MonsterItemDrop(int type, int level, float dur,  int x, int y, BYTE Option1, BYTE Option2, BYTE Option3, BYTE NOption, BYTE SOption,  int aIndex, DWORD number, BYTE ItemEffectEx, BYTE SocketOption[5], BYTE SocketIndex);
	int MoneyItemDrop(int money, int x, int y);
	void WeatherVariationProcess();
	BYTE GetWeather();
	void SetWeather(BYTE a_weather, BYTE a_variation);
	int GetVisibleItemCount(LPOBJ lpObj,int distance);
	void StateSetDestroy();
	bool PathFinding2(int sx, int sy, int tx, int ty, PATH_t* a);
	bool PathFinding3(int sx, int sy, int tx, int ty, PATH_t* a);
	bool PathFinding4(int sx, int sy, int tx, int ty, PATH_t* a);
	void SetStandAttr(int x, int y);
	void ClearStandAttr(int x, int y);
	int GetStandAttr(int x, int y);
	BYTE GetAttr(int x, int y);

	void init()
	{
		this->m_attrbuf = 0;
		this->path = new PATH;
		this->m_width = 0;
		this->m_height = 0;
	}
	
	void free()
	{
		if ( this->m_attrbuf != 0 )
		{
			GlobalFree(this->m_attrbuf);
			this->m_attrbuf=0;
		}

		if ( this->path != 0 )
		{
			delete this->path;
			this->path = 0;
		}
	}

	MapClass();
	virtual ~MapClass();

public:

	BYTE m_Weather;	// 4
	BYTE m_WeatherVariation;	// 5
	DWORD m_WeatherTimer;	// 8
	DWORD m_NextWeatherTimer;	// C
	LPBYTE m_attrbuf;	// 10
	int m_width;	// 14
	int m_height;	// 18
	PATH* path;	// 1C
	class CMapItem m_cItem[MAX_MAPITEM];	// 20
	int m_ItemCount;	// 50DE0
	RECT gRegenRect[MAX_NUMBER_MAP];	// 50DE4
	int thisMapNumber;	// 51114
};

BOOL MapNumberCheck(int map);

#endif