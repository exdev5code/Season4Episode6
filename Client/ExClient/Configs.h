#define _CONFIG_CLASS_
#ifdef _CONFIG_CLASS_

#define CONFIG_DIR "./Settings.ini"

extern int VK_MINIMAP;

class cConfig
{
public:
	cConfig();
	~cConfig();
	//Configs
	int CAM_IsActive;
	int CastleSkills;
	int HPBar;
	int MiniMap;
	int Time;

	bool Ctrl;

	int exCAM_IsActive;
	int exCastleSkills;
	int exHPBar;
	int exMiniMap;
	int exTime;

	int iMonsterHPBar;
	int iUserHpBar;
	int iPartyHpBar;

	bool gJEWELSBANK;

	void Start();
};
extern cConfig Config;

#endif

#if(_CONFIG_SAVE_)
void SaveGame();
void LoadGame();
#endif