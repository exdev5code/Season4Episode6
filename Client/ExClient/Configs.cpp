#include "StdAfx.h"
#include "Configs.h"
#include "3DCamera.h"
#include "Console.h"
#include "NewHpBar.h"

cConfig Config;

cConfig::cConfig()
{
	CAM_IsActive = 1;
	CastleSkills = 1;
	HPBar = 1;
	MiniMap = 1;
	Time = 1;
	Ctrl = false;
}

cConfig::~cConfig()
{

}

void cConfig::Start()
{
	exCAM_IsActive = GetPrivateProfileIntA("Common", "3DActive", 1, CONFIG_DIR);
	exCastleSkills = GetPrivateProfileIntA("Common", "CastleSkills", 1, CONFIG_DIR);
	exHPBar = GetPrivateProfileIntA("Common", "HPBar", 1, CONFIG_DIR);
	exMiniMap = GetPrivateProfileIntA("Common", "MiniMap", 1,CONFIG_DIR);
	exTime = GetPrivateProfileIntA("Common", "Time", 1,CONFIG_DIR);

	gJEWELSBANK = GetPrivateProfileInt("Common","JewelsBank",1,CONFIG_DIR);

	Ctrl = false;

	Config.iMonsterHPBar = 1;
	Config.iUserHpBar = 1;
	Config.iPartyHpBar = 1;
}

#if(_CONFIG_SAVE_)

#define ENCODER	1

#define MAX_XoR	8

BYTE XoRT[MAX_XoR] = {  0xD4, 0x7B, 0x5E, 0x2B, 0x58, 0x48, 0xD4, 0xD9 };

void Encode(char* buffer, int size)
{
	int a = 0;
	for ( int i = 0 ; i < size ; i++ )
	{
		if( a == MAX_XoR )
		{
			a = 0;
		}
		buffer[i] = buffer[i] ^ XoRT[a];
		a++;
	}
}

#define GAMEINFO_DIR	".\\Data\\ExTeam\\Game.ex"

#define GAMEBUFFER "%d %d %d %d %d %d"

void SaveGame()
{
	FILE * file = fopen(GAMEINFO_DIR,"w+");

	char InfoDate[512];

	sprintf(InfoDate, GAMEBUFFER,Config.CAM_IsActive, Config.MiniMap, Config.Time,Config.iMonsterHPBar,Config.iUserHpBar,Config.iPartyHpBar);
#ifdef CONSOLE
	Console.ConsoleOutput(GREEN,InfoDate);
#endif
#if(ENCODER)
	Encode(InfoDate,strlen(InfoDate));
#endif
	fputs(InfoDate, file);

	fclose(file);
}

void LoadGame()
{

	Config.iMonsterHPBar = 1;
	Config.iUserHpBar = 1;
	Config.iPartyHpBar = 1;

	Config.CAM_IsActive = 1;
	Config.CastleSkills = 1;
	Config.HPBar = 1;
	Config.MiniMap = 1;
	Config.Time = 1;
	Config.Ctrl = false;

	//g_bGlowGraphic = 1;

	float LoadCamera = 35.00;

	FILE * file = fopen(GAMEINFO_DIR,"r");

	if (file == NULL)
	{
		SaveGame();
		return;
	}

	char Buff[512];

	while (!feof(file))
	{
		fgets(Buff,512,file);
#if(ENCODER)
		Encode(Buff,strlen(Buff));
#endif
#ifdef CONSOLE
		Console.ConsoleOutput(RED,Buff);
#endif

		sscanf(Buff, GAMEBUFFER, &Config.CAM_IsActive, &Config.MiniMap, &Config.Time,&Config.iMonsterHPBar,&Config.iUserHpBar,&Config.iPartyHpBar);
	}
	fclose(file);

}

#endif