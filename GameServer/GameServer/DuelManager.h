#pragma once

#include "user.h"
//#include "..includeprodef.h"
#include "DarkSpirit.h"
#include "GameMain.h"

#define DUEL_WIN_POINT_COUNT  10
#define MAX_DUEL_ROOMS      4
#define MAX_DUEL_LEARNERS    10
#define DUEL_TIME        30 // 15 minutos

////////////////////////////////////////////////////////////////////////////////////////////////
// PROTOCOL PACKETS
////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)

struct PMSG_DUEL_ANSWER_START
{
  PBMSG_HEAD2 h;
  bool bDuelOK;
  BYTE NumberH;
  BYTE NumberL;
  char szName[10];
};

struct PMSG_DUEL_START
{
  PBMSG_HEAD2 h;  // C1:AA
  BYTE bDuelStart;  // 3
  BYTE NumberH;  // 4
  BYTE NumberL;  // 5
  char szName[10];  // 6
};

struct PMSG_DUEL_REQUEST_END
{
  PBMSG_HEAD2 h;
  BYTE NumberH;  // 3
  BYTE NumberL;  // 4
  char szName[10];  // 6
};

struct PMSG_DUEL_REQUEST_WATCH // 0x07
{
  PBMSG_HEAD2 h;
  BYTE btRoomIndex;
  BYTE btRandomValue;
};

// SERVER -> CLIENT

struct PMSG_DUEL_QUESTION_START // 0x01
{
  PBMSG_HEAD2 h;
  BYTE NumberH;
  BYTE NumberL;
  BYTE szName[10];
};

struct PMSG_DUEL_REQUEST_START // 0x02
{
  PBMSG_HEAD2 h;
  BYTE NumberH;  // 3
  BYTE NumberL;  // 4
  char szName[10];  // 5
};

struct PMSG_DUEL_END // 0x03
{
  PBMSG_HEAD2 h;
};

struct PMSG_DUEL_SCORE // 0x04
{
  PBMSG_HEAD2 h;  
  BYTE NumberH1;  
  BYTE NumberL1;  
  BYTE NumberH2;  
  BYTE NumberL2;  
  BYTE btDuelScore1;  
  BYTE btDuelScore2;  
};

struct PMSG_DUEL_LIFEBAR_REFILL // 0x05
{
  PBMSG_HEAD2 h;
  BYTE btObjId01H;
  BYTE btObjId01L;
  BYTE btObjId02H;
  BYTE btObjId02L;
  BYTE btLife01;
  BYTE btLife02;
  BYTE btShield01;
  BYTE btShield02;
};

struct PMSG_DUEL_ROOMSTATUS // Complemento de 0x06
{
  BYTE szName1[10];
  BYTE szName2[10];
  BYTE btDuelRunning;
  BYTE btDuelOpen;
};

struct PMSG_DUEL_STATUS // 0x06
{
  PBMSG_HEAD2 h;
  PMSG_DUEL_ROOMSTATUS pRoomStatus[MAX_DUEL_ROOMS];
};

struct PMSG_DUEL_LIFEBAR_NAME // 0x07 00 
{
  PBMSG_HEAD2 h;
  WORD Type; // 4
  BYTE szName1[10]; // 5
  BYTE szName2[10]; // f
  BYTE btObjId1H;
  BYTE btObjId1L;
  BYTE btObjId2H;
  BYTE btObjId2L;
};

struct PMSG_DUEL_SPEC_ADD // 0x08
{
  PBMSG_HEAD2 h;
  BYTE szName[10];
};

struct PMSG_DUEL_SPEC_DELEX // 0x09 - confirmar
{
  PBMSG_HEAD2 h;
  BYTE szName[10];
};

struct PMSG_DUEL_SPEC_DEL // 0x0A
{
  PBMSG_HEAD2 h;
  BYTE szName[10];
};

struct PMSG_DUEL_SPEC_LIST // 0x0B
{
  PBMSG_HEAD2 h;
  BYTE btCount;
  BYTE szName[MAX_DUEL_LEARNERS][10];
};

struct PMSG_DUEL_FINISH // 0x0C
{
  PBMSG_HEAD2 h;
  BYTE szWinner[10];
  BYTE szLooser[10];
};

struct PMSG_DUEL_LIFEBAR_INIT // 0x0D
{
  PBMSG_HEAD2 h;
  BYTE Unknow00;
};

#pragma pack()

////////////////////////////////////////////////////////////////////////////////////////////////
// END PROTOCOL PACKETS
////////////////////////////////////////////////////////////////////////////////////////////////



struct DUEL_ROOM
{

  BOOL  bFree;
  BOOL  bWaiting;

  LPOBJ  lpObj01;
  BYTE  btPoints01;

  LPOBJ  lpObj02;
  BYTE  btPoints02;

  LPOBJ  lpLearners[MAX_DUEL_LEARNERS];

  DWORD  dwTickCount;
  DWORD  dwStartTime;

  BOOL  bHasWinner;

};

static const struct DUEL_RESPAWN_RECTS
{
  int LowX;
  int LowY;
  int HighX;
  int HighY;
} 
g_DuelRespawns [MAX_DUEL_ROOMS] = 
{
  { 89,  62,    110,  81    },
  { 89,  113,  110,  130    },
  { 141,  63,    163,  82    },
  { 142,  111,  163,  131    }
};

class CDuelManager
{
private:
  DWORD m_UpdateTickCount;
  DWORD m_UpdateLifebarTime;

public:

  DUEL_ROOM  m_Rooms[MAX_DUEL_ROOMS];

  CDuelManager(void);
  ~CDuelManager(void);

  void Run();
  void ProtocolCore(LPOBJ lpObj, BYTE* lpPacket);

  void KillUserProc ( LPOBJ lpObj, LPOBJ lpTarget);
  int GetUserDuelRoom(LPOBJ lpObj);
  int GetFreeRoomIndex();

  bool IsDuelEnable(int aIndex);
  bool DuelCheck(LPOBJ lpObj) { return this->IsOnDuel(lpObj->m_Index); }
  bool DuelCheck(LPOBJ lpObj, LPOBJ lpObj2) { return this->IsOnDuel(lpObj->m_Index, lpObj2->m_Index); }

  void UserDuelInfoReset(LPOBJ lpObj);
  void RoomReset(int iRoom, bool dontMove = false, bool dontSendEnd = false);

  void RemoveUser(LPOBJ lpObj);

  void SetDuelOption(int lpObj, BOOL bState);

  bool IsOnDuel(int lpObj);
  bool IsOnDuel(int lpObj, int lpObj2);

  void PlayerScore(LPOBJ lpObj);

  int GetSpectatorCount(int iRoom);
  void SendDuelStatus(LPOBJ lpObj);

  void UpdateDuelScore(int iRoom);

  void RecvDuelRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_START* lpMsg);
  void RecvDuelAnswer(LPOBJ lpObj, PMSG_DUEL_ANSWER_START* lpMsg);
  void RecvWatchRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_WATCH* lpMsg);

  void SendRefuseDuel(LPOBJ lpObj)
  { 

    if(lpObj == NULL) return;

    PMSG_DUEL_START pMsgSend;
    
    pMsgSend.h.c = 0xC1;
    pMsgSend.h.headcode = 0xAA;
    pMsgSend.h.subcode = 0x01;
    pMsgSend.bDuelStart = 0x0F;
    pMsgSend.h.size = sizeof(pMsgSend);

    DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);

  }

  void SendEndDuel(LPOBJ lpObj);
  void SendEndDuelNotification(LPOBJ lpObj, char* Winner, char* Looser);

  void SendLifebarStatus(int iRoom);
  void SendLifebarStatus(LPOBJ lpObj, int iRoom);
  void SendLifebarInit(LPOBJ lpObj, int iRoom);
  void SendSpectatorList(int iRoom);
  void SendSpectatorList(LPOBJ lpObj, int iRoom);
  void SendSpectatorAdd(int iSpecIndex, int iRoom);
  void SendSpectatorRemove(int iSpecIndex, int iRoom);


};


extern CDuelManager    g_DuelManager;