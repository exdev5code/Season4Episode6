
#include "user.h"
#include "StdAfx.h"

#ifdef _MuReal_

#define VIPSYSTEM_DIR "..\\ExTeam\\VipSystem.ini"

class cVipSystem 
{
private:
	int vipSystemEnable;
	char BuyVipCMD[50];

	int vipExpRate;
	int vipDropRate;

	int priceVipCRMin;

	char PostVipCmd[50];
	int colorVipChatMsg;
	char VipPrefics[50];

	int needLvlFromTeleport;
	int offTeleportPhonoman;
	char TeleportCmd[50];
	int TeleportMap;
	int TeleportX;
	int TeleportY;

	int VipX1;
	int VipY1;
	int VipX2;
	int VipY2;

	//���������, ���� �� ��������� ��������.
	char msgNotEnoughCR[50];
	//���������, ���� ������ ���������������� � ��� ����� ��������
	char msgOffTeleportPhonoman[50];
	//���������, ���� �� ���������� ������ ��� ���������������� � ��� �����
	char msgNotNeedLvlFromTeleport[50];

	//� ���-�� ���������, �������� ��� ��������� ��� �� ��������. 1 ��� 2
	int msgVipConnectEnable;
	// ��� ��������� ��� �����
	//����� �������� ��������� ��� ����� � ���� �� �������� ��� ������ ��� ���������, ����������� � ����, ������. � ������������ � ����� ���, ��� ��������� ��� ����� "!"  ����. 
	char msgVipConnect[50];
	// ������� ������� ����	/buyvip {min}
public:

	void LoadConfig();
	void BuyVip(int aIndex,LPBYTE Protocol);
	void ConnectMessage(int aIndex);
	void VipExperience(LPOBJ lpObj, __int64 & Experience);	//Vip User Experience
	void VipZen (LPOBJ lpObj, float & money);
	void TickTime(int aIndex);
	void Teleport(int aIndex,LPBYTE Protocol);
	void PostVip(int aIndex,LPBYTE Protocol);
};
extern cVipSystem VipSystem;

#endif