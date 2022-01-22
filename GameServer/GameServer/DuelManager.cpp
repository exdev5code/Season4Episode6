#include "stdafx.h"
#include "user.h"
#include "protocol.h"
//#include "..includeprodef.h"
//#include "..commonwinutil.h"
#include "LogProc.h"
#include "DuelManager.h"
#include "GameMain.h"
#include "IllusionTempleEvent.h"
#include "BloodCastle.h"
#include "ChaosCastle.h"
#include "DevilSquare.h"
#include "DarkSpirit.h"
#include "ObjUseSkill.h"
#include "../common/winutil.h"
#include "Configs.h"

static const struct DUEL_GATES
{
  int UserGate01;
  int UserGate02;
  int LearnerGate;
} 
g_DuelGates[MAX_DUEL_ROOMS] = 
{
  { 295, 296, 303 },
  { 297, 298, 304 },
  { 299, 300, 305 },
  { 301, 302, 306 }
};


CDuelManager  g_DuelManager;

CDuelManager::CDuelManager(void)
{

  ZeroMemory(&this->m_Rooms, sizeof(this->m_Rooms));

  for(int i = 0; i < MAX_DUEL_ROOMS; i++) 
  {
    this->m_Rooms[i].bFree = true;
    this->m_Rooms[i].bWaiting = false;
    this->m_Rooms[i].bHasWinner = false;
  }

}

CDuelManager::~CDuelManager(void)
{
}

int CDuelManager::GetUserDuelRoom(LPOBJ lpObj)
{
  for(int i = 0; i < MAX_DUEL_ROOMS; i++)
  {
    if(this->m_Rooms[i].lpObj01 == lpObj ||
      this->m_Rooms[i].lpObj02 == lpObj) 
    {
      return i;
    }
  }
  return -1;
}

void CDuelManager::Run()
{
  for(int i = 0; i < MAX_DUEL_ROOMS; i++)
  {
    if(this->m_Rooms[i].bFree == FALSE)
    {

      if(GetTickCount() - this->m_Rooms[i].dwStartTime < 5000) continue;

      for(int u = 0; u < MAX_DUEL_LEARNERS; u++)
      {
        if(this->m_Rooms[i].lpLearners[u] == NULL) continue;
        if(gObjIsConnected(this->m_Rooms[i].lpLearners[u]->m_Index))
        {
          if(this->m_Rooms[i].lpLearners[u]->MapNumber != MAP_INDEX_VULCANROOM)
          {
            this->SendEndDuel(this->m_Rooms[i].lpLearners[u]);
            GCStateInfoSend(this->m_Rooms[i].lpLearners[u], 0, eVS_INVISIBLE);
            GCStateInfoSend(this->m_Rooms[i].lpLearners[u], 0, eVS_TRANSPARENCY);
            GCStateInfoSend(this->m_Rooms[i].lpLearners[u], 0, eVS_DUEL_INTERFACE);
            LogAddTD("[Duel Manager] Spectator (%s) leaves room %d", this->m_Rooms[i].lpLearners[u]->Name, i + 1);
            this->SendSpectatorRemove(u, i);
            this->m_Rooms[i].lpLearners[u] = NULL;
          }
        }
        else
        {
          LogAddTD("[Duel Manager] Some spectator leaves room %d", this->m_Rooms[i].lpLearners[u]->Name, i + 1);
          this->m_Rooms[i].lpLearners[u] = NULL;
          this->SendSpectatorList(i);
        }
      }

      if(this->m_Rooms[i].lpObj01 != NULL && this->m_Rooms[i].lpObj02 != NULL)
      {
        if(gObjIsConnected(this->m_Rooms[i].lpObj01->m_Index) == FALSE ||
          gObjIsConnected(this->m_Rooms[i].lpObj02->m_Index) == FALSE)
        {
          this->RoomReset(i);
          continue;
        }
        else if ((this->m_Rooms[i].lpObj01->MapNumber != MAP_INDEX_VULCANROOM ||
          this->m_Rooms[i].lpObj02->MapNumber != MAP_INDEX_VULCANROOM) && 
          this->m_Rooms[i].bHasWinner == FALSE)
        {
          this->RoomReset(i);
          continue;
        }
        else if (this->m_Rooms[i].lpObj01->Connected < PLAYER_PLAYING ||
          this->m_Rooms[i].lpObj02->Connected < PLAYER_PLAYING)
        {
          this->RoomReset(i);
          continue;
        }
      }
      else
      {
        this->RoomReset(i);
        continue;
      }

      if(this->m_UpdateLifebarTime < GetTickCount())
      {
        this->SendLifebarStatus(i);
        this->m_UpdateLifebarTime = GetTickCount() + 2000;
      }

      if(this->m_Rooms[i].dwTickCount != 0)
      {
        if(this->m_Rooms[i].dwTickCount < GetTickCount())
        {
          this->RoomReset(i);
          LogAddTD("[Duel Manager] Room %d cleaned.", i+1);
        }
      }
    }
  }

  if(this->m_UpdateTickCount < GetTickCount())
  {
    for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
    {
      if((gObj[i].m_IfState.use) && gObj[i].m_IfState.type == 20)
      {
        this->SendDuelStatus(&gObj[i]);
      }
    }
    this->m_UpdateTickCount = GetTickCount() + 6000;
  }

  return;
}

void CDuelManager::UpdateDuelScore(int iRoom) 
{ 

  if(iRoom < 0 || iRoom > MAX_DUEL_ROOMS - 1)
    return;

  if(this->m_Rooms[iRoom].lpObj01 == NULL || this->m_Rooms[iRoom].lpObj02 == NULL) return;

  int aIndex1 = this->m_Rooms[iRoom].lpObj01->m_Index;
  int aIndex2 = this->m_Rooms[iRoom].lpObj02->m_Index;

  if ( !OBJMAX_RANGE(aIndex1) || !OBJMAX_RANGE(aIndex2))
    return;

  if ( !gObjIsConnected(aIndex1) || !gObjIsConnected(aIndex2) )
    return;

  if ( gObj[aIndex1].Type == OBJ_MONSTER || gObj[aIndex2].Type == OBJ_MONSTER )
    return;
  
  if ( gObj[aIndex1].CloseCount >= 0 || gObj[aIndex2].CloseCount >= 0 )
    return;

  PMSG_DUEL_SCORE pMsg;

  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x04;
  pMsg.NumberH1 = SET_NUMBERH(aIndex1);
  pMsg.NumberL1 = SET_NUMBERL(aIndex1);
  pMsg.NumberH2 = SET_NUMBERH(aIndex2);
  pMsg.NumberL2 = SET_NUMBERL(aIndex2);
  pMsg.btDuelScore1 = this->m_Rooms[iRoom].btPoints01;
  pMsg.btDuelScore2 = this->m_Rooms[iRoom].btPoints02;

  DataSend(aIndex1, (LPBYTE)&pMsg, pMsg.h.size);
  DataSend(aIndex2, (LPBYTE)&pMsg, pMsg.h.size);

  for(int i = 0; i < MAX_DUEL_LEARNERS; i++)
  {
    if(this->m_Rooms[iRoom].lpLearners[i] == NULL) 
    {
      continue;
    }
    DataSend(this->m_Rooms[iRoom].lpLearners[i]->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
  }

}

void CDuelManager::PlayerScore(LPOBJ lpObj)
{
  int iRoom = this->GetUserDuelRoom(lpObj);
  if(iRoom >= 0 && iRoom < MAX_DUEL_ROOMS)
  {
    if(this->m_Rooms[iRoom].lpObj01 == lpObj)
    {
      this->m_Rooms[iRoom].btPoints01++;
      this->UpdateDuelScore(iRoom);
    }
    else if(this->m_Rooms[iRoom].lpObj02 == lpObj)
    {
      this->m_Rooms[iRoom].btPoints02++;
      this->UpdateDuelScore(iRoom);
    }
  }
}

void CDuelManager::SendEndDuel(LPOBJ lpObj) 
{ 

  if(lpObj == NULL) return;
  if(gObjIsConnected(lpObj->m_Index) == FALSE) return;

  BYTE lpMsgClose[5] = { 0xC1, 0x05, 0xAA, 0x03, 0x00 } ;

  DataSend(lpObj->m_Index, &lpMsgClose[0], lpMsgClose[1]);

}

int CDuelManager::GetSpectatorCount(int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS) 
  {
    return -1;
  }

  int iCount = 0;
  for(int i = 0; i < MAX_DUEL_LEARNERS; i++)
  {
    if(this->m_Rooms[iRoom].lpLearners[i] != NULL) 
    {
      iCount++;
    }
  }

  return iCount;

}

void CDuelManager::RemoveUser(LPOBJ lpObj) 
{ 

  //verificar se faz parte do duel
  //verificar se eh da batalha...
  // -> se for, finalizar a sala
  //resetar informações do duel
  //se for um watcher remover interface
  //mover para gate 294

}

void CDuelManager::SendDuelStatus(LPOBJ lpObj)
{

  PMSG_DUEL_STATUS pMsg;

  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x06;

  ZeroMemory(&pMsg.pRoomStatus, sizeof(pMsg.pRoomStatus));
  
  for(int i = 0; i < MAX_DUEL_ROOMS; i++)
  {

    if(this->m_Rooms[i].bFree == FALSE)
    {

      if(this->m_Rooms[i].lpObj01 == NULL || this->m_Rooms[i].lpObj02 == NULL)
      {
        continue;
      }

      pMsg.pRoomStatus[i].btDuelRunning = TRUE;

      int iSpecCount = this->GetSpectatorCount(i);
      if(iSpecCount < 0 || iSpecCount >= 10)
      {
        pMsg.pRoomStatus[i].btDuelOpen = FALSE;
      }
      else
      {
        pMsg.pRoomStatus[i].btDuelOpen = TRUE;
      }

      memcpy(&pMsg.pRoomStatus[i].szName1[0], &this->m_Rooms[i].lpObj01->Name[0], 10);
      memcpy(&pMsg.pRoomStatus[i].szName2[0], &this->m_Rooms[i].lpObj02->Name[0], 10);

    }

  }

  DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);

}

int CDuelManager::GetFreeRoomIndex()
{
  for(int i = 0; i < MAX_DUEL_ROOMS; i++)
  {
    if(this->m_Rooms[i].bFree == TRUE)
    {
      if(this->m_Rooms[i].bWaiting == FALSE)
      {
        return i;  
      }
    }
  }
  return -1;
}

void CDuelManager::UserDuelInfoReset(LPOBJ lpObj) 
{ 
  if(lpObj == NULL) 
  {  
    return;
  }
  lpObj->m_iDuelRoom = -1;
  lpObj->m_iDuelUser = -1;
  lpObj->m_iDuelUserRequested = -1;
  lpObj->m_iDuelUserReserved = -1;
  lpObj->m_btDuelScore = 0;
  gDarkSpirit[lpObj->m_Index].ReSetTarget(lpObj->m_Index);
}

void CDuelManager::RoomReset(int iRoom, bool dontMove, bool dontSendEnd)
{

  if(this->m_Rooms[iRoom].lpObj01 != NULL)
  {
    if(gObjIsConnected(this->m_Rooms[iRoom].lpObj01->m_Index))
    {
      if(dontSendEnd == false)
        this->SendEndDuel(this->m_Rooms[iRoom].lpObj01);
      if(this->m_Rooms[iRoom].lpObj01->MapNumber == MAP_INDEX_VULCANROOM)
      {
        if(dontMove == false)
          gObjMoveGate(this->m_Rooms[iRoom].lpObj01->m_Index, ExConfig.PvP.DuelGate);
      }
    }
    this->UserDuelInfoReset(this->m_Rooms[iRoom].lpObj01);
  }

  if(this->m_Rooms[iRoom].lpObj02 != NULL)
  {
    if(gObjIsConnected(this->m_Rooms[iRoom].lpObj02->m_Index))
    {
      if(dontSendEnd == false)
        this->SendEndDuel(this->m_Rooms[iRoom].lpObj02);
      if(this->m_Rooms[iRoom].lpObj02->MapNumber == MAP_INDEX_VULCANROOM)
      {
        if(dontMove == false)
          gObjMoveGate(this->m_Rooms[iRoom].lpObj02->m_Index, ExConfig.PvP.DuelGate);
      }
    }
    this->UserDuelInfoReset(this->m_Rooms[iRoom].lpObj02);
  }

  for(int i = 0; i < MAX_DUEL_LEARNERS; i++)
  {
    if(this->m_Rooms[iRoom].lpLearners[i] != NULL)
    {
      this->SendEndDuel(this->m_Rooms[iRoom].lpLearners[i]);
      GCStateInfoSend(this->m_Rooms[iRoom].lpLearners[i], 0, eVS_INVISIBLE);
      GCStateInfoSend(this->m_Rooms[iRoom].lpLearners[i], 0, eVS_TRANSPARENCY);
      GCStateInfoSend(this->m_Rooms[iRoom].lpLearners[i], 0, eVS_DUEL_INTERFACE);
      gObjMoveGate(this->m_Rooms[iRoom].lpLearners[i]->m_Index, ExConfig.PvP.DuelGate);
    }
    this->m_Rooms[iRoom].lpLearners[i] = NULL;
  }

  this->m_Rooms[iRoom].lpObj01 = NULL;
  this->m_Rooms[iRoom].btPoints01 = 0;

  this->m_Rooms[iRoom].lpObj02 = NULL;
  this->m_Rooms[iRoom].btPoints02 = 0;

  this->m_Rooms[iRoom].bFree = TRUE;
  this->m_Rooms[iRoom].bWaiting = FALSE;
  this->m_Rooms[iRoom].bHasWinner = FALSE;

  this->m_Rooms[iRoom].dwTickCount = 0;
  this->m_Rooms[iRoom].dwStartTime = 0;

  LogAddTD("[Duel Manager] Room Reset - Number: %d", iRoom + 1);

}

void CDuelManager::SendEndDuelNotification(LPOBJ lpObj, char* Winner, char* Looser)
{

  PMSG_DUEL_FINISH pMsg;
  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x0C;
  memcpy(pMsg.szWinner, Winner, 10);
  memcpy(pMsg.szLooser, Looser, 10);

  DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);

}

void CDuelManager::SendSpectatorAdd(int iSpecIndex, int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(iSpecIndex < 0 || iSpecIndex >= MAX_DUEL_LEARNERS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].lpLearners[iSpecIndex] == NULL) return;

  if(this->m_Rooms[iRoom].lpObj01 == NULL || 
    this->m_Rooms[iRoom].lpObj02 == NULL)
  {
    return;
  }

  PMSG_DUEL_SPEC_ADD pMsg;
  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x08;
  memcpy(pMsg.szName, this->m_Rooms[iRoom].lpLearners[iSpecIndex]->Name, 10);

  for(int i = 0; i < MAX_DUEL_LEARNERS; i++)
  {
    if(i == iSpecIndex) continue;
    if(this->m_Rooms[iRoom].lpLearners[i] != NULL)
    {
      DataSend(this->m_Rooms[iRoom].lpLearners[i]->m_Index, (BYTE*)&pMsg, pMsg.h.size);
    }
  }

}

void CDuelManager::SendSpectatorRemove(int iSpecIndex, int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(iSpecIndex < 0 || iSpecIndex >= MAX_DUEL_LEARNERS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].lpLearners[iSpecIndex] == NULL) return;

  if(this->m_Rooms[iRoom].lpObj01 == NULL || 
    this->m_Rooms[iRoom].lpObj02 == NULL)
  {
    return;
  }

  PMSG_DUEL_SPEC_ADD pMsg;
  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x0A;
  memcpy(pMsg.szName, this->m_Rooms[iRoom].lpLearners[iSpecIndex]->Name, 10);

  for(int i = 0; i < MAX_DUEL_LEARNERS; i++)
  {
    if(i == iSpecIndex) continue;
    if(this->m_Rooms[iRoom].lpLearners[i] != NULL)
    {
      DataSend(this->m_Rooms[iRoom].lpLearners[i]->m_Index, (BYTE*)&pMsg, pMsg.h.size);
    }
  }

}

void CDuelManager::SendSpectatorList(int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].bFree == FALSE)
  {
    for(int u = 0; u < MAX_DUEL_LEARNERS; u++)
    {
      if(this->m_Rooms[iRoom].lpLearners[u] != NULL)
      {
        this->SendSpectatorList(this->m_Rooms[iRoom].lpLearners[u], iRoom);
      }
    }
  }

}

void CDuelManager::SendSpectatorList(LPOBJ lpObj, int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].lpObj01 == NULL || 
    this->m_Rooms[iRoom].lpObj02 == NULL)
  {
    return;
  }

  PMSG_DUEL_SPEC_LIST pMsg;
  pMsg.h.c = 0xC1;
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x0B;
  pMsg.btCount = 0;

  if(this->m_Rooms[iRoom].bFree == FALSE)
  {
    for(int u = 0; u < MAX_DUEL_LEARNERS; u++)
    {
      if(this->m_Rooms[iRoom].lpLearners[u] != NULL)
      {
        memcpy(&pMsg.szName[pMsg.btCount++][0], this->m_Rooms[iRoom].lpLearners[u]->Name, 10);
      }
    }
  }

  pMsg.h.size = 5 + (pMsg.btCount * 10);

  DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);

}

void CDuelManager::SendLifebarStatus(int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].lpObj01 == NULL || 
    this->m_Rooms[iRoom].lpObj02 == NULL)
  {
    return;
  }

  if(this->m_Rooms[iRoom].bFree == FALSE)
  {
    for(int u = 0; u < MAX_DUEL_LEARNERS; u++)
    {
      if(this->m_Rooms[iRoom].lpLearners[u] != NULL)
      {
        this->SendLifebarStatus(this->m_Rooms[iRoom].lpLearners[u], iRoom);
      }
    }
  }

}

void CDuelManager::SendLifebarStatus(LPOBJ lpObj, int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].lpObj01 == NULL || 
    this->m_Rooms[iRoom].lpObj02 == NULL)
  {
    return;
  }

  PMSG_DUEL_LIFEBAR_REFILL pMsg;
  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x05;

  pMsg.btObjId01H = HIBYTE(this->m_Rooms[iRoom].lpObj01->m_Index);
  pMsg.btObjId01L = LOBYTE(this->m_Rooms[iRoom].lpObj01->m_Index);

  pMsg.btObjId02H = HIBYTE(this->m_Rooms[iRoom].lpObj02->m_Index);
  pMsg.btObjId02L = LOBYTE(this->m_Rooms[iRoom].lpObj02->m_Index);

  pMsg.btLife01 = (BYTE)(this->m_Rooms[iRoom].lpObj01->Life / ((this->m_Rooms[iRoom].lpObj01->MaxLife + this->m_Rooms[iRoom].lpObj01->AddLife) / 100));
  pMsg.btLife02 = (BYTE)(this->m_Rooms[iRoom].lpObj02->Life / ((this->m_Rooms[iRoom].lpObj02->MaxLife + this->m_Rooms[iRoom].lpObj02->AddLife) / 100));

  pMsg.btShield01 = this->m_Rooms[iRoom].lpObj01->iShield / ((this->m_Rooms[iRoom].lpObj01->iMaxShield + this->m_Rooms[iRoom].lpObj01->iAddShield) / 100);
  pMsg.btShield02 = this->m_Rooms[iRoom].lpObj02->iShield / ((this->m_Rooms[iRoom].lpObj02->iMaxShield + this->m_Rooms[iRoom].lpObj02->iAddShield) / 100);

  DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);

}

void CDuelManager::SendLifebarInit(LPOBJ lpObj, int iRoom)
{

  if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
  {
    return;
  }

  if(this->m_Rooms[iRoom].lpObj01 == NULL || 
    this->m_Rooms[iRoom].lpObj02 == NULL)
  {
    return;
  }

  PMSG_DUEL_LIFEBAR_NAME pMsg2;
  pMsg2.h.c = 0xC1;
  pMsg2.h.size = sizeof(pMsg2);
  pMsg2.h.headcode = 0xAA;
  pMsg2.h.subcode = 0x07;
  pMsg2.Type = 0x00;
  
  memcpy(pMsg2.szName1, this->m_Rooms[iRoom].lpObj01->Name, 10);
  memcpy(pMsg2.szName2, this->m_Rooms[iRoom].lpObj02->Name, 10);

  pMsg2.btObjId1H = HIBYTE(this->m_Rooms[iRoom].lpObj01->m_Index);
  pMsg2.btObjId1L = LOBYTE(this->m_Rooms[iRoom].lpObj01->m_Index);

  pMsg2.btObjId2H = HIBYTE(this->m_Rooms[iRoom].lpObj02->m_Index);
  pMsg2.btObjId2L = LOBYTE(this->m_Rooms[iRoom].lpObj02->m_Index);

  DataSend(lpObj->m_Index, (BYTE*)&pMsg2, pMsg2.h.size);

  PMSG_DUEL_LIFEBAR_INIT pMsg;
  pMsg.h.c = 0xC1;
  pMsg.h.size = sizeof(pMsg);
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x0D;

  DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);

}

void CDuelManager::KillUserProc(LPOBJ lpObj, LPOBJ lpTarget)
{ 
    
  if(!this->DuelCheck(lpObj, lpTarget)) return;
  
  int iDuelRoom = this->GetUserDuelRoom(lpObj);
  if(iDuelRoom == -1)
  {
    return;
  }

  lpTarget->KillerType = 3;

  int Points = ((lpObj == this->m_Rooms[iDuelRoom].lpObj01) ? this->m_Rooms[iDuelRoom].btPoints01 : this->m_Rooms[iDuelRoom].btPoints02);
  if(Points >= DUEL_WIN_POINT_COUNT)
  {

    this->m_Rooms[iDuelRoom].bHasWinner = TRUE;

    this->SendEndDuel(lpTarget);
    this->SendEndDuel(lpObj);

    this->SendEndDuelNotification(lpTarget, lpObj->Name, lpTarget->Name);
    this->SendEndDuelNotification(lpObj, lpObj->Name, lpTarget->Name);

    gDarkSpirit[lpObj->m_Index].ReSetTarget(lpTarget->m_Index);
    gDarkSpirit[lpTarget->m_Index].ReSetTarget(lpObj->m_Index);

    char szMsg[256];

    wsprintf(szMsg,lMsg.Get(1216),lpTarget->Name);
    GCServerMsgStringSend(szMsg,lpObj->m_Index,1);

    wsprintf(szMsg,lMsg.Get(1217),lpObj->Name);
    GCServerMsgStringSend(szMsg,lpTarget->m_Index,1);

    PMSG_SERVERCMD ServerCmd;

    PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
    ServerCmd.CmdType = 0;
    ServerCmd.X = lpObj->X;
    ServerCmd.Y = lpObj->Y;

    MsgSendV2(lpObj,(unsigned char *)&ServerCmd,sizeof(ServerCmd));
    DataSend(lpObj->m_Index,(unsigned char *)&ServerCmd,sizeof(ServerCmd));

   // gObjUseSkill.AddOrRemoveBuff(eVS_DUEL_MEDAL, lpObj->m_Index, TRUE);

    this->m_Rooms[iDuelRoom].dwTickCount = GetTickCount() + 10000;

    LogAdd("[Duel] [%s][%s] Win Duel, Loser [%s][%s]",lpObj->AccountID,lpObj->Name,lpTarget->AccountID,lpTarget->Name);

  }

}

void CDuelManager::ProtocolCore(LPOBJ lpObj, BYTE* lpPacket)
{
  PMSG_DEFAULT2* pMsg = (PMSG_DEFAULT2*)lpPacket;
  switch(pMsg->subcode)
  {
  case 0x01:
    this->RecvDuelRequest(lpObj, (PMSG_DUEL_REQUEST_START*)lpPacket);
    break;
  case 0x02:
    this->RecvDuelAnswer(lpObj, (PMSG_DUEL_ANSWER_START*)lpPacket);
    break;
  case 0x07:
    this->RecvWatchRequest(lpObj, (PMSG_DUEL_REQUEST_WATCH*)lpPacket);
    break;
  case 0x09:
    if(lpObj->MapNumber == MAP_INDEX_VULCANROOM)
    {
      gObjMoveGate(lpObj->m_Index, ExConfig.PvP.DuelGate); // vai pro vulcan map
    }
    break;
  }
}

void CDuelManager::RecvWatchRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_WATCH* lpMsg)
{

  if(lpObj->m_IfState.use == 0 || lpObj->m_IfState.type != 20) 
  {
    return;
  }

  lpObj->m_IfState.use = 0;
  lpObj->m_IfState.type = 0;

  if(lpMsg->btRoomIndex >= 0 && lpMsg->btRoomIndex < MAX_DUEL_ROOMS)
  {

    if(this->m_Rooms[lpMsg->btRoomIndex].bFree == TRUE) 
    {
      GCServerMsgStringSend("There is no one in the duel that you are trying to watch.", lpObj->m_Index, 1);
      LogAddC(2, "[Duel Manager] (%s)(%s) Watch request error: wrong duel state! (%d)", lpObj->AccountID, lpObj->Name, lpMsg->btRoomIndex);
      return;
    }

    for(int i = 0; i < MAX_DUEL_LEARNERS; i++)
    {
      if(this->m_Rooms[lpMsg->btRoomIndex].lpLearners[i] == NULL)
      {
        if(gObjMoveGate(lpObj->m_Index, g_DuelGates[lpMsg->btRoomIndex].LearnerGate))
        {
          this->m_Rooms[lpMsg->btRoomIndex].lpLearners[i] = lpObj;
          this->SendSpectatorList(lpObj, lpMsg->btRoomIndex);
          this->SendSpectatorAdd(i, lpMsg->btRoomIndex);
          GCServerMsgStringSend("You are now in room duel.", lpObj->m_Index, 1);
          GCStateInfoSend(lpObj, 1, eVS_DUEL_INTERFACE);
          GCStateInfoSend(lpObj, 1, eVS_TRANSPARENCY);
          //GCStateInfoSend(lpObj, 1, eVS_INVISIBLE, TRUE, TRUE);
          this->SendLifebarInit(lpObj, lpMsg->btRoomIndex);
          this->SendLifebarStatus(lpObj, lpMsg->btRoomIndex);
          this->UpdateDuelScore(lpMsg->btRoomIndex);
          return;
        }      
        GCServerMsgStringSend("Unable to move you.", lpObj->m_Index, 1);
        return;
      }
    }

    GCServerMsgStringSend("The duel that you are trying to watch is already full.", lpObj->m_Index, 1);
    LogAddC(2, "[Duel Manager] (%s)(%s) Watch request error: room is full! (%d)", lpObj->AccountID, lpObj->Name, lpMsg->btRoomIndex);

    return;

  }

  LogAddC(2, "[Duel Manager] (%s)(%s) Wrong room index! (%d)", lpObj->AccountID, lpObj->Name, lpMsg->btRoomIndex);

}

void CDuelManager::RecvDuelAnswer(LPOBJ lpObj, PMSG_DUEL_ANSWER_START* lpMsg)
{

  int iDuelIndex = -1;
  int iDuelRoom = lpObj->m_iDuelRoom;
  
  PMSG_DUEL_START pMsgSend;
  
  pMsgSend.h.c = 0xC1;
  pMsgSend.h.headcode = 0xAA;
  pMsgSend.h.subcode = 0x01;
  pMsgSend.bDuelStart = 0;
  pMsgSend.h.size = sizeof(pMsgSend);

  if(iDuelRoom < 0 || iDuelRoom > MAX_DUEL_ROOMS - 1) 
  {
    return;
  }

  if ( gObj[lpObj->m_Index].CloseType != -1 ) 
    return;
  
  iDuelIndex = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);

  if ( OBJMAX_RANGE(iDuelIndex) )
  {
    if ( !gObjIsConnected(iDuelIndex) )
      return;

    if ( gObj[iDuelIndex].Type == OBJ_MONSTER )
      return;

    if ( gObj[iDuelIndex].CloseCount >= 0 )
      return;

	if(gObj[iDuelIndex].m_DuleFix == false)
	{
		GCServerMsgStringSend("Duel User Switch", lpObj->m_Index, 1);
		return;
	}

    if ( lpMsg->bDuelOK )
    {
      if ( BC_MAP_RANGE(gObj[iDuelIndex].MapNumber) ||
         CC_MAP_RANGE(gObj[iDuelIndex].MapNumber) ||
         DS_MAP_RANGE(gObj[iDuelIndex].MapNumber) || 
		 IT_MAP_RANGE(gObj[iDuelIndex].MapNumber) )
      {

        GCServerMsgStringSend(lMsg.Get(MSGGET(4, 207)), lpObj->m_Index, 1);

        this->RoomReset(iDuelRoom, true, true);

        memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
        DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
        return;
      }
    }

    if ( OBJMAX_RANGE(lpObj->m_iDuelUser ) )
    {
      GCServerMsgStringSend(lMsg.Get(MSGGET(4, 160)), lpObj->m_Index, 1);
      GCServerMsgStringSend(lMsg.Get(MSGGET(4, 161)), lpObj->m_Index, 1);
      
      this->RoomReset(iDuelRoom, true, true);

      memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
      DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
      return;
    }

    if ( OBJMAX_RANGE(lpObj->m_iDuelUserReserved) )
    {
      GCServerMsgStringSend(lMsg.Get(MSGGET(4, 173)), lpObj->m_Index, 1);

      this->RoomReset(iDuelRoom, true, true);

      memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
      DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
      return;
    }

    if ( gObj[iDuelIndex].m_iDuelUserReserved == lpObj->m_Index )
    {

      char szDuelName[MAX_ACCOUNT_LEN+1]={0};
      char szDuelName2[MAX_ACCOUNT_LEN+1]={0};

      memcpy(szDuelName, gObj[iDuelIndex].Name, MAX_ACCOUNT_LEN);
      szDuelName[MAX_ACCOUNT_LEN] = 0;

      memcpy(szDuelName2, lpMsg->szName, MAX_ACCOUNT_LEN);
      szDuelName2[MAX_ACCOUNT_LEN] = 0;

      if ( !strcmp(szDuelName, szDuelName2))
      {
        if ( lpMsg->bDuelOK == false)
        {
          this->RoomReset(iDuelRoom, true, true);
          pMsgSend.bDuelStart = 0x0F;
          memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
          DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
        }
        else if ( lpMsg->bDuelOK == true )
        {

          if ( lpObj->Money < 30000 )
          {
            this->SendEndDuel(&gObj[iDuelIndex]);
            this->RoomReset(iDuelRoom, true);
            pMsgSend.bDuelStart = 0x0e;
            pMsgSend.h.size = sizeof(pMsgSend);
            DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
            return;
          }
          if(gObj[iDuelIndex].Money < 30000)
          {
            this->SendEndDuel(lpObj);
            this->RoomReset(iDuelRoom, true);
            pMsgSend.bDuelStart = 0x0e;
            pMsgSend.h.size = sizeof(pMsgSend);
            DataSend(iDuelIndex, (BYTE*)&pMsgSend, pMsgSend.h.size);
            return;
          }

          if(gObjMoveGate(lpObj->m_Index, g_DuelGates[iDuelRoom].UserGate01) == false)
          {
            this->RoomReset(iDuelRoom, true, true);
            return;
          }
          if(gObjMoveGate(iDuelIndex, g_DuelGates[iDuelRoom].UserGate02) == false)
          {
            this->RoomReset(iDuelRoom, true, true);
            return;
          }

          lpObj->Money -= 30000;
          GCMoneySend(lpObj->m_Index, lpObj->Money);

          gObj[iDuelIndex].Money -= 30000;
          GCMoneySend(iDuelIndex, gObj[iDuelIndex].Money);

          gObj[iDuelIndex].m_iDuelUserReserved = -1;
          gObj[iDuelIndex].m_btDuelScore = 0;
          gObj[iDuelIndex].m_iDuelUser = lpObj->m_Index;

          this->m_Rooms[iDuelRoom].dwStartTime = GetTickCount();
          this->m_Rooms[iDuelRoom].dwTickCount = GetTickCount() + (DUEL_TIME * 60000);

          lpObj->m_iDuelUserRequested = -1;
          lpObj->m_iDuelUserReserved = -1;

          lpObj->m_btDuelScore = 0;
          lpObj->m_iDuelUser = iDuelIndex;

          this->m_Rooms[iDuelRoom].bFree = FALSE;
          this->m_Rooms[iDuelRoom].bWaiting = FALSE;
          this->m_Rooms[iDuelRoom].bHasWinner = FALSE;

          pMsgSend.bDuelStart = 0;

          pMsgSend.NumberH = SET_NUMBERH(iDuelIndex);
          pMsgSend.NumberL = SET_NUMBERL(iDuelIndex);

          memcpy(pMsgSend.szName, szDuelName, sizeof(pMsgSend.szName));

          DataSend(lpObj->m_Index, (LPBYTE)&pMsgSend, pMsgSend.h.size);

          pMsgSend.NumberH = SET_NUMBERH(lpObj->m_Index);
          pMsgSend.NumberL = SET_NUMBERL(lpObj->m_Index);

          memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));

          DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);

          this->UpdateDuelScore(iDuelRoom);

          LogAddTD("[Duel] [%s][%s] Duel Started [%s][%s] on Room [%d]", lpObj->AccountID, lpObj->Name,
            gObj[iDuelIndex].AccountID, gObj[iDuelIndex].Name, iDuelRoom + 1);
        }
      }
      else
      {
        this->RoomReset(iDuelRoom);
        DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
        return;
      }
    }
    else
    {
      this->RoomReset(iDuelRoom);
      DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
      return;
    }
  }
}

void CDuelManager::RecvDuelRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_START* lpMsg)
{
	/*
  if(g_DuelSystemState != TRUE)
  {
    GCServerMsgStringSend("O duel foi desativado neste servidor!", lpObj->m_Index, 1);
    return;
  }
  */
  int iDuelIndex = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);

  if ( !OBJMAX_RANGE(iDuelIndex) )
  {
    LogAdd("error : %s %d (%d)", __FILE__, __LINE__, iDuelIndex);
    return;
  }

  if ( iDuelIndex == lpObj->m_Index )
    return;

  char szTempText[256];

  if ( lpObj->CloseType != -1 )
    return;
  
  if ( gNonPK ) 
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 174)), lpObj->m_Index, 1);
    return;
  }

  if ( !gPkLimitFree ) 
  {
    if ( lpObj->m_PK_Level >= 6 )
    {
      GCServerMsgStringSend(lMsg.Get(MSGGET(4, 175)), lpObj->m_Index, 1);
      return;
    }
    if ( gObj[iDuelIndex].m_PK_Level >= 6 )
    {
      GCServerMsgStringSend(lMsg.Get(MSGGET(4, 176)), lpObj->m_Index, 1);
      return;
    }
  }

  if ( OBJMAX_RANGE(lpObj->m_iDuelUserReserved) )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 159)), lpObj->m_Index, 1);
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 161)), lpObj->m_Index, 1);
    return;
  }

  if ( OBJMAX_RANGE( lpObj->m_iDuelUser ) )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 160)), lpObj->m_Index, 1);
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 161)), lpObj->m_Index, 1);
    return;
  }

  if ( DS_MAP_RANGE(gObj[iDuelIndex].MapNumber ) )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 180)), lpObj->m_Index, 1);
    return;
  }

  if ( BC_MAP_RANGE(lpObj->MapNumber) )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 166)), lpObj->m_Index, 1);
    return;
  }

  if ( CC_MAP_RANGE(lpObj->MapNumber) )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 207)), lpObj->m_Index, 1);
    return;
  }

  if ( IT_MAP_RANGE(lpObj->MapNumber) != FALSE )
  {
    ::GCServerMsgStringSend("Duels are not allowed in Illusion Temple.", lpObj->m_Index, 1);
    return;
  }

  if ( lpObj->Level < 30 || gObj[iDuelIndex].Level < 30)
  {
    PMSG_DUEL_START pMsgSend;
    pMsgSend.h.c = 0xC1;
    pMsgSend.h.headcode = 0xAA;
    pMsgSend.h.subcode = 0x01;
    pMsgSend.bDuelStart = 0x0C;
    pMsgSend.h.size = sizeof(pMsgSend);
    DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
    return;
  }

  if ( lpObj->Money < 30000 || gObj[iDuelIndex].Money < 30000 )
  {
    PMSG_DUEL_START pMsgSend;
    pMsgSend.h.c = 0xC1;
    pMsgSend.h.headcode = 0xAA;
    pMsgSend.h.subcode = 0x01;
    pMsgSend.bDuelStart = 0x1e;
    pMsgSend.h.size = sizeof(pMsgSend);
    DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
    return;
  }

  int iDuelRoom = this->GetFreeRoomIndex();
  if ( iDuelRoom == -1 )
  {
    PMSG_DUEL_START pMsgSend;
    pMsgSend.h.c = 0xC1;
    pMsgSend.h.headcode = 0xAA;
    pMsgSend.h.subcode = 0x01;
    pMsgSend.bDuelStart = 0x10;
    pMsgSend.h.size = sizeof(pMsgSend);
    DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
    return;
  }

  if ( ( GetTickCount() - lpObj->m_PacketCheckTime ) < 300 )
  {
    return;
  }
  lpObj->m_PacketCheckTime = GetTickCount();

  char szDuelName[MAX_ACCOUNT_LEN+1] = {0};
  char szDuelName2[MAX_ACCOUNT_LEN+1] = {0};

  memcpy(szDuelName, gObj[iDuelIndex].Name, MAX_ACCOUNT_LEN);
  szDuelName[MAX_ACCOUNT_LEN] = 0;

  memcpy(szDuelName2, lpMsg->szName, MAX_ACCOUNT_LEN);
  szDuelName2[MAX_ACCOUNT_LEN] = 0;

  if ( strcmp(szDuelName, szDuelName2) )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 162)), lpObj->m_Index, 1);
    return;
  }

  if ( this->IsDuelEnable(iDuelIndex) == FALSE )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 163)), lpObj->m_Index, 1);
    return;
  }

  if ( lpObj->lpGuild && lpObj->lpGuild->WarState == 1 )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 164)), lpObj->m_Index, 1);
    return;
  }

  if ( gObj[iDuelIndex].lpGuild && gObj[iDuelIndex].lpGuild->WarState == 1 )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 165)), lpObj->m_Index, 1);
    return;
  }

  if ( gObjIsConnected(iDuelIndex) == FALSE )
    return;

  if ( gObj[iDuelIndex].Type == OBJ_MONSTER )
    return;

  if ( gObj[iDuelIndex].CloseCount >= 0 )
    return;

  for (int n=0;n<MAX_SELF_DEFENSE;n++)
  {
    if ( lpObj->SelfDefense[n] >= 0 || gObj[iDuelIndex].SelfDefense[n] >= 0 )
    {
      GCServerMsgStringSend(lMsg.Get(MSGGET(4, 189)), lpObj->m_Index, 1);
      return;
    }
  }

  if ( lpObj->m_IfState.use > 0 )
  {
    GCServerMsgStringSend(lMsg.Get(MSGGET(4, 167)), lpObj->m_Index, 1);
    return;
  }

  if ( gObj[iDuelIndex].m_IfState.use > 0 )
  {
    wsprintf(szTempText, lMsg.Get(MSGGET(4, 168)), gObj[iDuelIndex].Name);
    GCServerMsgStringSend(szTempText, lpObj->m_Index, 1);
    return;
  }

  if ( OBJMAX_RANGE(gObj[iDuelIndex].m_iDuelUserRequested) )
  {
    wsprintf(szTempText, lMsg.Get(MSGGET(4, 169)), gObj[iDuelIndex].Name);
    GCServerMsgStringSend(szTempText, lpObj->m_Index, 1);
    return;
  }

  if ( OBJMAX_RANGE(gObj[iDuelIndex].m_iDuelUserReserved) )
  {
    wsprintf(szTempText, lMsg.Get(MSGGET(4, 170)), gObj[iDuelIndex].Name);
    GCServerMsgStringSend(szTempText, lpObj->m_Index, 1);
    return;
  }

  if ( OBJMAX_RANGE(gObj[iDuelIndex].m_iDuelUser) )
  {
    wsprintf(szTempText, lMsg.Get(MSGGET(4, 171)), gObj[iDuelIndex].Name);
    GCServerMsgStringSend(szTempText, lpObj->m_Index, 1);
    return;
  }

  lpObj->m_iDuelUser = -1;
  lpObj->m_iDuelUserReserved = iDuelIndex;
  gObj[iDuelIndex].m_iDuelUserRequested = lpObj->m_Index;
  lpObj->m_iDuelRoom = iDuelRoom;
  gObj[iDuelIndex].m_iDuelRoom = iDuelRoom;

  lpObj->m_DuleFix = true;

  this->m_Rooms[iDuelRoom].lpObj01 = lpObj;
  this->m_Rooms[iDuelRoom].lpObj02 = &gObj[iDuelIndex];
  this->m_Rooms[iDuelRoom].bWaiting = TRUE;

  PMSG_DUEL_QUESTION_START pMsg;

  pMsg.h.c = 0xC1;
  pMsg.h.headcode = 0xAA;
  pMsg.h.subcode = 0x02;
  pMsg.h.size = sizeof(pMsg);
  pMsg.NumberH = SET_NUMBERH(lpObj->m_Index);
  pMsg.NumberL = SET_NUMBERL(lpObj->m_Index);
  memcpy(pMsg.szName, lpObj->Name, sizeof(pMsg.szName));

  DataSend(iDuelIndex, (LPBYTE)&pMsg, pMsg.h.size);

  wsprintf(szTempText, lMsg.Get(MSGGET(4, 172)), gObj[iDuelIndex].Name);
  GCServerMsgStringSend(szTempText, lpObj->m_Index, 1);

  LogAddTD("[Duel Manager] [%s][%s] Requested to Start Duel to [%s][%s] on Room [%d]", lpObj->AccountID, lpObj->Name, gObj[iDuelIndex].AccountID, gObj[iDuelIndex].Name, iDuelRoom+1);

}

bool CDuelManager::IsDuelEnable(int aIndex)
{

  if ( OBJMAX_RANGE(aIndex ) == FALSE)
  {
    return false;
  }

  if ( gObjIsConnected(aIndex) == TRUE )
  {
    if ( ( gObj[aIndex].m_Option & 2 ) == 2 )
    {
      return true;
    }
  }

  return false;

}

void CDuelManager::SetDuelOption(int lpObj, BOOL bState) 
{
  if ( gObjIsConnected(lpObj) == TRUE )
  {
    if ( bState == 0 )
    {
      gObj[lpObj].m_Option = 0;
    }
    else
    {
      gObj[lpObj].m_Option |= 2;
    }
  }
}

bool CDuelManager::IsOnDuel(int lpObj) 
{ 

  for(int i = 0; i < MAX_DUEL_ROOMS; i++)
  {
    if(this->m_Rooms[i].lpObj01 == &gObj[lpObj])
    {
      return true;
    }
    if(this->m_Rooms[i].lpObj02 == &gObj[lpObj]) 
    {
      return true;
    }
  }

  return false;

}

bool CDuelManager::IsOnDuel(int lpObj, int lpObj2) 
{

  for(int i = 0; i < MAX_DUEL_ROOMS; i++)
  {

    if(this->m_Rooms[i].bFree == FALSE)
    {

      if(this->m_Rooms[i].lpObj01 == &gObj[lpObj] && 
        this->m_Rooms[i].lpObj02 == &gObj[lpObj2]) 
      {
        return true;
      }

      if(this->m_Rooms[i].lpObj01 == &gObj[lpObj2] && 
        this->m_Rooms[i].lpObj02 == &gObj[lpObj]) 
      {
        return true;
      }

    }

  }

  return false;

}