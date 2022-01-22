// SocketOption.h: interface for the CSocketOption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETOPTION_H__18EA21AE_2F1E_4DDA_AAFF_A542E8807753__INCLUDED_)
#define AFX_SOCKETOPTION_H__18EA21AE_2F1E_4DDA_AAFF_A542E8807753__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\common\\zzzitem.h"
#include "TRandomPoolMgr.h"
#include "SocketData.h"
#include "SocketSphere.h"

#define MAX_SOCKET_OPTION		5
#define MAX_SEED_OPTION			50
#define MAX_SPHERE_OPTION		6
#define MAX_SOCKET_BONUS_TYPE	2

#define SOCKET_SLOT_1		0
#define SOCKET_SLOT_2		1
#define SOCKET_SLOT_3		2
#define SOCKET_SLOT_4		3
#define SOCKET_SLOT_5		4

#define MAX_SOCKET_SLOT		5
#define SOCKET_BONUS_SLOT	5

enum eItemSocketEffect
{
	SOCKET_EFFECT_OPADDATTACKPOWER	= 0,
	SOCKET_EFFECT_OPADDSPEEDPOWER	= 1,
	SOCKET_EFFECT_OPADDMAXDMGWEAPONS= 2,
	SOCKET_EFFECT_OPADDMINDMGWEAPONS= 3,
	SOCKET_EFFECT_OPADDALLDMGWEAPONS= 4,
	SOCKET_EFFECT_OPADDUNK			= 5,
};

typedef struct
{
	BYTE btNumber; // 0x4A0
	BYTE btType; // 0x4A1
	BYTE btIncrease; // 0x4A2
	BYTE btOption; // 0x4A3
	int iProbability; // 0x4A4
	BYTE btElements[MAX_SPHERE_OPTION]; // 0x4A8
}_SOCKET_BONUS_OPTION, *LPSOCKET_BONUS_OPTION;


class CSocketOption  
{
public:
	CSocketOption();
	virtual ~CSocketOption();

	void Init(); 
	BYTE LoadScript(LPSTR lpszFileName);
	void _InitOption();
	BYTE IsActive(CItem *pItem);
	BYTE CheckItemType(int iItemNumber);
	BYTE GetActiveSocketSlots(CItem * pItem);
	BYTE ModifySeedSphereData(BYTE SeedSphereIndex,BYTE & OptionIndex,BYTE & OptionType,BYTE & SocketSlot);
	void GetActiveSocketOption(CItem *pItem, BYTE *SocketOption, BYTE &SocketIndex);
	BYTE IsSocketOption(CItem *pItem);
	BYTE IsSeedSphereItem(int m_Type);
	BYTE IsSeedItem(int m_Type);
	BYTE IsSeedSpearItem(int m_Type);
	BYTE GetSeedOptionIndex(int m_Type, BYTE m_Level);
	BYTE GetSphereLevel(int m_Type);
	BYTE CheckEmptySlot(CItem * pItem, WORD m_Type, BYTE m_Level);
	BYTE GetItemSocketByteOption(WORD m_Type, BYTE m_Level);
	int	 GetValue(BYTE index);
	BYTE CheckItemElementInfo(CItem * pItem,BYTE index);
	BYTE CheckMapNumber(int MapNumber);
	int GetSphereItemIndex(int Level);
	int GetSocketByteOption(BYTE OptionIndex,BYTE SocketSlotCount);
	BYTE SetSeedSphereData(CSeedSphere * lpSeedSphere,BYTE OptionIndex,BYTE SocketSlotCount);
	CSeed * GetSeedData(BYTE OptionIndex);
	CSphere * GetSphereData(BYTE level);
	BYTE SortOptionIndex();
	BYTE GetElementIndex(BYTE index);
	CSocketSphere * GetSeedSpear(BYTE OptionIndex);
	int CalcEquipmentSocketOption(struct OBJECTSTRUCT* lpObj);
	void SetBonusSocketOption(struct OBJECTSTRUCT* lpObj);
	void SetFullBonusSocketOption(struct OBJECTSTRUCT* lpObj);
	BYTE CalCharacterSocketOption(struct OBJECTSTRUCT* lpObj);
	void ClearEquipmentSocketOption(struct OBJECTSTRUCT* lpObj);
	void ApplySocketEffect(struct OBJECTSTRUCT* lpObj,int arg2,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplyTESTSocketEffect();
	void ApplySocketFireEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketWaterEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketIceEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketWindEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketLightningEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketEarthEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketReservedEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	void ApplySocketBonusEffect(struct OBJECTSTRUCT* lpObj,BYTE btEffectType,BYTE btOptionType,WORD wOptionValue);
	int _CalcIncreaseValue(int iValue,WORD wOptionValue,BYTE btOptionType);
	void ApplySocketEffectforWeapons(CItem * lpItem);
    void ClearSlotOption(CItem * lpItem,BYTE btSocketSlotCount);
	BYTE GetRandomSlotCount(int item_num);
	void ClearSocketData(struct OBJECTSTRUCT* lpObj);
	BYTE MakeManualOptionbyJewel(CItem *lpFirstItem,CItem *lpSecondItem,BYTE btSocketSlot);
	BYTE MakeManualOptionbyCalc(CItem * lpItem,BYTE arg2,BYTE arg3,BYTE btSocketSlot);
	BYTE MakeManualOption(CItem * lpItem,BYTE arg2,BYTE btSocketSlot);
	BYTE ManualSetBonusSocketOption(CItem * lpItem);
	BYTE RemakeSocketOption(CItem *lpItem,BYTE btSlotIndex);

public:
	CSeed					SocketSeed[MAX_SEED_OPTION];					//this+004
	CSphere					SocketSphere[MAX_SOCKET_OPTION];				//this+3EC
	CSocketSphere			SocketSpear[MAX_SPHERE_OPTION];					//this+428
	_SOCKET_BONUS_OPTION	SocketBonusOption[MAX_SOCKET_BONUS_TYPE];		//this+4A0
	TRandomPoolMgr			SocketRandomPool;								//this+4C0
	TRandomPoolMgr			SocketSlotRandomPool;							//this+4D8
	TRandomPoolMgr			TwoHandWeaponSocketSlotRandomPool;				//this+4F0
	int						iSocketSlotCountRate[MAX_SOCKET_OPTION];		//this+508
	int						iTwoHandSlotCountRate[MAX_SOCKET_OPTION];		//this+51C
	BOOL					bSphereDrop;									//this+530
	int						iSphereDropRate[MAX_SOCKET_OPTION];				//this+534
	int						iSphereDropLevel[MAX_SOCKET_OPTION];			//this+548
};

extern CSocketOption g_SocketOption;
extern int g_iShopBuySocketItemSlotCount;
extern int g_iSeedExtractMoney;
extern int g_iSeedSphereCompositeMoney;
extern int g_iSeedSphereSetMoney;
extern int g_iSeedSphereRemoveMoney;

struct SOCKET_ITEM
{
	BYTE m_btEffectType;
	BYTE m_btOptionType;
	WORD m_wOptionValue;
	BYTE m_btOptionCount;

	void RESET();
};
#endif // !defined(AFX_SOCKETOPTION_H__18EA21AE_2F1E_4DDA_AAFF_A542E8807753__INCLUDED_)