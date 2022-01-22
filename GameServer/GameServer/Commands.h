#include "StdAfx.h"

void ChatDataSend(DWORD gObjId,LPBYTE Protocol);
void PostMessage (int aIndex,char* szMsg);
void Ex_AddStr (int aIndex,char* msg);
void Ex_AddAgi (int aIndex,char* msg);
void Ex_AddVit (int aIndex,char* msg);
void Ex_AddEne (int aIndex,char* msg);
void Ex_AddCmd (int aIndex,char* msg);
void Ex_PkClear(int aIndex);
#if __ExGames__
void BanChatingFunction(int aIndex, char *msg);
#endif