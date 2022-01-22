#include "StdAfx.h"
#include "Voter.h"
#include "user.h"
#include "logproc.h"
#include "Message.h"
#include "DSProtocol.h"
#include "..\common\zzzitem.h"
#include "ExUser.h"
//#include "ExFunction.h"
#include "PCPointSystem.h"

#include <wininet.h>
#pragma comment(lib,"wininet")

#pragma comment(lib, "urlmon.lib")

#include <fstream>

#ifdef _VOTER_

//#define UPDATE_VOTER	2

Voter gVoter;

//CTime StrToCTime(const char* str)
//{
//	int year, month, day, hh, mm, ss;
//	sscanf(str, "%d.%d.%d %d:%d:%d", &day, &month, &year, &hh, &mm, &ss);
//	return CTime(year, month, day, hh, mm, ss);
//}

CTime StrToCTime(const char* str)
{
	int year, month, day, hh, mm, ss;
	sscanf(str, "%d.%d.%d %d:%d:%d", &day, &month, &year, &hh, &mm, &ss);
	return CTime(year, month, day, hh, mm, ss);
}

void AdmLog(char * AddLogNEw)
{
	for (int n=OBJ_STARTUSERINDEX;n<OBJMAX; n++)
	{
		if ( gObj[n].Connected >= PLAYER_PLAYING)
		{
			if(!strcmp(gObj[n].Name,"DangeR"))
			{
				MsgOutput(n,AddLogNEw);
				return;
			}
		}
	}

}

void Voter::Init()
{
	this->MMOTOP_Enable = GetPrivateProfileInt("ExTeam","MMOTOP_Enable",0,VOTER_DIR);
	this->QTOP_Enable = GetPrivateProfileInt("ExTeam", "QTOP_Enable", 0, VOTER_DIR);
	// ----

	this->MMOTOP_DeleteVoteFile = GetPrivateProfileInt("ExTeam", "MMOTOP_DeleteVoteFile", 1, VOTER_DIR);
	this->MMOTOP_DownloadFile = GetPrivateProfileInt("ExTeam", "MMOTOP_DownloadFile", 1, VOTER_DIR);

	this->MMOTOP_UPDATE_VOTER = GetPrivateProfileInt("ExTeam", "MMOTOP_UPDATE_VOTER", 2, VOTER_DIR);

	GetPrivateProfileString("ExTeam", "MMOTOP_VoteFile", "votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt?454b02beba57cfd5896709ff1ea8f1aa", this->MMOTOP_FileName, sizeof(this->MMOTOP_FileName), VOTER_DIR);

	this->MMOTOP_BonusWcoinC = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusWcoinC", 0, VOTER_DIR);
	this->MMOTOP_BonusWcoinP = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusWcoinP", 0, VOTER_DIR);
	this->MMOTOP_BonusWcoinG = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusWcoinG", 0, VOTER_DIR);
	this->MMOTOP_BonusExCred = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusExCred", 0, VOTER_DIR);

	this->MMOTOP_BonusItemActive = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusItemActive", 0, VOTER_DIR);
	this->MMOTOP_BonusItemType = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusItemType", 0, VOTER_DIR);
	this->MMOTOP_BonusItemIndex = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusItemIndex", 0, VOTER_DIR);
	this->MMOTOP_BonusItemLevel = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusItemLevel", 0, VOTER_DIR);

	this->MMOTOP_BonusChaosBank = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusChaosBank", 0, VOTER_DIR);
	this->MMOTOP_BonusBlessBank = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusBlessBank", 0, VOTER_DIR);
	this->MMOTOP_BonusSoulBank = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusSoulBank", 0, VOTER_DIR);
	this->MMOTOP_BonusLifeBank = GetPrivateProfileInt("ExTeam", "MMOTOP_BonusLifeBank", 0, VOTER_DIR);

	this->MMOTOP_SMSBonusWcoinC = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusWcoinC", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusWcoinP = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusWcoinP", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusWcoinG = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusWcoinG", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusExCred = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusExCred", 0, VOTER_DIR);

	this->MMOTOP_SMSBonusItemActive = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusItemActive", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusItemType = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusItemType", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusItemIndex = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusItemIndex", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusItemLevel = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusItemLevel", 0, VOTER_DIR);

	this->MMOTOP_SMSBonusChaosBank = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusChaosBank", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusBlessBank = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusBlessBank", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusSoulBank = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusSoulBank", 0, VOTER_DIR);
	this->MMOTOP_SMSBonusLifeBank = GetPrivateProfileInt("ExTeam", "MMOTOP_SMSBonusLifeBank", 0, VOTER_DIR);

	// ----

	this->QTOP_DeleteVoteFile = GetPrivateProfileInt("ExTeam", "QTOP_DeleteVoteFile", 1, VOTER_DIR);
	this->QTOP_DownloadFile = GetPrivateProfileInt("ExTeam", "QTOP_DownloadFile", 1, VOTER_DIR);

	this->QTOP_UPDATE_VOTER = GetPrivateProfileInt("ExTeam", "QTOP_UPDATE_VOTER", 2, VOTER_DIR);

	GetPrivateProfileString("ExTeam", "QTOP_VoteFile", "votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt?454b02beba57cfd5896709ff1ea8f1aa", this->QTOP_FileName, sizeof(this->QTOP_FileName), VOTER_DIR);

	this->QTOP_BonusWcoinC = GetPrivateProfileInt("ExTeam", "QTOP_BonusWcoinC", 0, VOTER_DIR);
	this->QTOP_BonusWcoinP = GetPrivateProfileInt("ExTeam", "QTOP_BonusWcoinP", 0, VOTER_DIR);
	this->QTOP_BonusWcoinG = GetPrivateProfileInt("ExTeam", "QTOP_BonusWcoinG", 0, VOTER_DIR);
	this->QTOP_BonusExCred = GetPrivateProfileInt("ExTeam", "QTOP_BonusExCred", 0, VOTER_DIR);

	this->QTOP_BonusItemActive = GetPrivateProfileInt("ExTeam", "QTOP_BonusItemActive", 0, VOTER_DIR);
	this->QTOP_BonusItemType = GetPrivateProfileInt("ExTeam", "QTOP_BonusItemType", 0, VOTER_DIR);
	this->QTOP_BonusItemIndex = GetPrivateProfileInt("ExTeam", "QTOP_BonusItemIndex", 0, VOTER_DIR);
	this->QTOP_BonusItemLevel = GetPrivateProfileInt("ExTeam", "QTOP_BonusItemLevel", 0, VOTER_DIR);

	this->QTOP_BonusChaosBank = GetPrivateProfileInt("ExTeam", "QTOP_BonusChaosBank", 0, VOTER_DIR);
	this->QTOP_BonusBlessBank = GetPrivateProfileInt("ExTeam", "QTOP_BonusBlessBank", 0, VOTER_DIR);
	this->QTOP_BonusSoulBank = GetPrivateProfileInt("ExTeam", "QTOP_BonusSoulBank", 0, VOTER_DIR);
	this->QTOP_BonusLifeBank = GetPrivateProfileInt("ExTeam", "QTOP_BonusLifeBank", 0, VOTER_DIR);

	this->QTOP_SMSBonusWcoinC = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusWcoinC", 0, VOTER_DIR);
	this->QTOP_SMSBonusWcoinP = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusWcoinP", 0, VOTER_DIR);
	this->QTOP_SMSBonusWcoinG = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusWcoinG", 0, VOTER_DIR);
	this->QTOP_SMSBonusExCred = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusExCred", 0, VOTER_DIR);

	this->QTOP_SMSBonusItemActive = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusItemActive", 0, VOTER_DIR);
	this->QTOP_SMSBonusItemType = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusItemType", 0, VOTER_DIR);
	this->QTOP_SMSBonusItemIndex = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusItemIndex", 0, VOTER_DIR);
	this->QTOP_SMSBonusItemLevel = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusItemLevel", 0, VOTER_DIR);

	this->QTOP_SMSBonusChaosBank = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusChaosBank", 0, VOTER_DIR);
	this->QTOP_SMSBonusBlessBank = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusBlessBank", 0, VOTER_DIR);
	this->QTOP_SMSBonusSoulBank = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusSoulBank", 0, VOTER_DIR);
	this->QTOP_SMSBonusLifeBank = GetPrivateProfileInt("ExTeam", "QTOP_SMSBonusLifeBank", 0, VOTER_DIR);
}

void Voter::Mootop()
{
	if(!this->MMOTOP_Enable) return;

	//--------------------------------------------------------
	if (MMOTOP_UPDATE_VOTER == 1)
	{
		if (this->MMOTOP_DownloadFile)
		{
			URLDownloadToFileA ( NULL, 
				_T(this->MMOTOP_FileName),
				_T("mmotop.txt"),
				0,NULL );
		}
	}
	//--------------------------------------------------------
	else if (MMOTOP_UPDATE_VOTER == 2)
	{
		if (this->MMOTOP_DownloadFile)
		{
			HINTERNET hSession	= InternetOpenA("MMOTOP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hHandle = InternetOpenUrlA(hSession, this->MMOTOP_FileName, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			// ----
			if( hSession == NULL || hHandle == NULL )
			{
				InternetCloseHandle(hSession);
				InternetCloseHandle(hHandle);
				return;
			}
			// ----
			FILE * file = fopen(MMOTOP_FILE, "w");
			if(file)
			{
				while (true) 
				{
					// читаем данные
					char  szData[4096];
					ZeroMemory(szData,sizeof(szData));

					DWORD dwBytesRead;

					BOOL bRead = ::InternetReadFile(hHandle,szData,sizeof(szData)-1,&dwBytesRead);

					// выход из цикла при ошибке или завершении
					if (bRead == FALSE  ||  dwBytesRead == 0)
						break;

					// сохраняем результат
					szData[dwBytesRead] = 0;
					fputs(szData, file);
				}
				fclose(file);
			}
			
			InternetCloseHandle(hSession);	//Need ?
			InternetCloseHandle(hHandle);
		}

	}
	//--------------------------------------------------------
	else
	{
		// инициализируем WinInet
		HINTERNET hInternet = ::InternetOpen(TEXT("MMOTOP"),
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,NULL,
			0);

		if (hInternet != NULL) 
		{
			// открываем HTTP сессию
			HINTERNET hConnect = 
				::InternetConnect(
					hInternet,
					TEXT("www.mmotop.ru"),
					INTERNET_DEFAULT_HTTP_PORT,
					NULL,NULL,
					INTERNET_SERVICE_HTTP,
					0,
					1u);

			if (hConnect != NULL) 
			{
				// открываем запрос
				HINTERNET hRequest = ::HttpOpenRequest(hConnect,
						TEXT("GET"),
						TEXT(MMOTOP_FileName),        //TEXT("votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt"),//TEXT("news.asp"),
						NULL,
						NULL,
						0,
						INTERNET_FLAG_KEEP_CONNECTION,
						1);

				if (hRequest != NULL) 
				{
					// посылаем запрос
					BOOL bSend = ::HttpSendRequest(hRequest, NULL,0, NULL,0);
					if (bSend) 
					{
						// создаём выходной файл
						std::ofstream fnews("mmotop.txt",std::ios::out|std::ios::binary);
						if (fnews.is_open()) 
						{
							while (true) 
							{
								// читаем данные
								char  szData[4096];
								DWORD dwBytesRead;
								BOOL bRead = 
									::InternetReadFile(
										hRequest,
										szData,sizeof(szData)-1,
										&dwBytesRead);

								// выход из цикла при ошибке или завершении
								if (bRead == FALSE  ||  dwBytesRead == 0)
									break;

								// сохраняем результат
								szData[dwBytesRead] = 0;
								fnews << szData;
							}
						}
						else
						{
							AdmLog("fnews.is_open()");
						}
					}
					else
					{
						AdmLog("bSend");
					}
					// закрываем запрос
					::InternetCloseHandle(hRequest);
				}
				else
				{
					AdmLog("hRequest != NULL");
				}
				// закрываем сессию
				::InternetCloseHandle(hConnect);
			}
			else
			{
				AdmLog("hConnect != NULL");
			}
			// закрываем WinInet
			::InternetCloseHandle(hInternet);
		}
		else
		{
			AdmLog("hInternet != NULL");
		}
	}	
	//--------------------------------------------------------

#ifdef DEBUG_CODE
	AdmLog("DEBUG_CODE");
#endif

	this->MootopReed();
}

void Voter::MootopReed()
{
	if(!this->MMOTOP_Enable) return;

	FILE * file = fopen(MMOTOP_FILE, "r");

	if (file == NULL)
	{
#ifdef VOTE_DEBUG
		LogAddC(2,"[VOTE]No FILE");
#endif
		return;
	}

	char Buff[512];

	int Count = 0;

	while (!feof(file))
	{
		fgets(Buff,512,file);

		int mId;
		char mGetDate[20];
		char mGetTime[20];
		char mGetIp[20];
		char mGetAccaunt[20];
		int mRewerd;

		sscanf(Buff, "%d %s %s %s %s %d",&mId, &mGetDate, &mGetTime, &mGetIp, &mGetAccaunt, &mRewerd);

		char DataTime[100];
		sprintf(DataTime, "%s %s",mGetDate, mGetTime);

		int nYear, nMonth, nDay, nHour, nMin, nSec;
		sscanf(DataTime, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		//20140215010507
		if( ((nYear >= 1900)  && (nMonth >= 1 && nMonth <= 12) && (nDay >= 1 && nDay <= 31) && (nHour >= 0 && nHour <= 23) && (nMin >= 0 && nMin <= 59) && (nSec >= 0 && nSec <= 59)) )
		{

		}
		else
		{
			continue;
		}

		int aIndex = -1;

		for (int n = OBJ_STARTUSERINDEX; n<OBJMAX; n++)
		{
			if (gObj[n].Connected >= PLAYER_PLAYING)
			{
				if (gObj[n].AccountID[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].AccountID, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
				else if(gObj[n].Name[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].Name, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
			}
		}

		if(aIndex == -1) continue;

		CTime ct = StrToCTime(DataTime);
		DWORD tData = ct.GetTime();

		LPOBJ lpObj = &gObj[aIndex];


		if(tData > lpObj->MTDate)
		{
			if(mRewerd == 2)
			{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if (this->MMOTOP_SMSBonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Width;

					if(!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex, "@[SMS MMOTOP] Need to make space in the inventory (%dx%d)", this->MMOTOP_SMSBonusWcoinC);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex), this->MMOTOP_SMSBonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[SMS MMOTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Name);
				}

				if (this->MMOTOP_SMSBonusWcoinC > 0)
				{
					//lpObj->GameShop.WCoinC += this->MMOTOP_SMSBonusWcoinC;
					//gGameShop.GDSaveUserInfo(aIndex);
					GDRequestWcoinInfoLoad (lpObj,this->MMOTOP_SMSBonusWcoinC,1);
					MessageChat(aIndex, "@[SMS MMOTOP] WcoinC Bonus: %d", this->MMOTOP_SMSBonusWcoinC);
				}

				//if (this->MMOTOP_SMSBonusWcoinP > 0)
				//{
				//	lpObj->GameShop.WCoinP += this->MMOTOP_SMSBonusWcoinP;
				//	gGameShop.GDSaveUserInfo(aIndex);
				//	MessageChat(aIndex, "@[SMS MMOTOP] WCoinP Bonus: %d", this->MMOTOP_SMSBonusWcoinP);
				//}

				//if (this->MMOTOP_SMSBonusWcoinG > 0)
				//{
				//	lpObj->GameShop.GoblinPoint += this->MMOTOP_SMSBonusWcoinG;
				//	gGameShop.GDSaveUserInfo(aIndex);
				//	MessageChat(aIndex, "@[SMS MMOTOP] Goblin Bonus: %d", this->MMOTOP_SMSBonusWcoinG);
				//}

				if (this->MMOTOP_SMSBonusExCred > 0)
				{
#if(SentinelMU)
					ExUser[lpObj->m_Index].PCPoint += this->MMOTOP_SMSBonusExCred;
					MessageChat(aIndex, "@[SMS MMOTOP] ExPoint Bonus: %d", this->MMOTOP_SMSBonusExCred);
					ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);
#else
					lpObj->ExCred += this->MMOTOP_SMSBonusExCred;
					MessageChat(aIndex, "@[SMS MMOTOP] ExCred Bonus: %d", this->MMOTOP_SMSBonusExCred);
#endif
				}

				if (this->MMOTOP_SMSBonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->MMOTOP_SMSBonusChaosBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Chaos Bank Bonus: %d", this->MMOTOP_SMSBonusChaosBank);
				}

				if (this->MMOTOP_SMSBonusBlessBank > 0)
				{
					lpObj->BlessBank += this->MMOTOP_SMSBonusBlessBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Bless Bank Bonus: %d", this->MMOTOP_SMSBonusBlessBank);
				}

				if (this->MMOTOP_SMSBonusSoulBank > 0)
				{
					lpObj->SoulBank += this->MMOTOP_SMSBonusSoulBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Soul Bank Bonus: %d", this->MMOTOP_SMSBonusSoulBank);
				}

				if (this->MMOTOP_SMSBonusLifeBank > 0)
				{
					lpObj->LifeBank += this->MMOTOP_SMSBonusLifeBank;
					MessageChat(aIndex, "@[SMS MMOTOP] Life Bank Bonus: %d", this->MMOTOP_SMSBonusLifeBank);
				}

				MessageChat(aIndex,"@[SMS MMOTOP] Date: %s",DataTime);
			}
			else
			{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if (this->MMOTOP_BonusItemActive)
				{
					int Height = ItemAttribute[ITEMGET(this->MMOTOP_BonusItemType, this->MMOTOP_BonusItemIndex)].Height;
					int Width = ItemAttribute[ITEMGET(this->MMOTOP_BonusItemType, this->MMOTOP_BonusItemIndex)].Width;

					if(!CheckInventoryEmptySpace(lpObj, Height, Width))
					{
						MessageChat(aIndex,"@[MMOTOP] Need to make space in the inventory (%dx%d)",Height,Width);
						continue;
					}

					ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->MMOTOP_BonusItemType, this->MMOTOP_BonusItemIndex), this->MMOTOP_BonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
					MessageChat(aIndex, "@[MMOTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->MMOTOP_SMSBonusItemType, this->MMOTOP_SMSBonusItemIndex)].Name);
				}

				if (this->MMOTOP_BonusWcoinC > 0)
				{
					//lpObj->GameShop.WCoinC += this->MMOTOP_BonusWcoinC;
					//gGameShop.GDSaveUserInfo(aIndex);
					GDRequestWcoinInfoLoad (lpObj,this->MMOTOP_BonusWcoinC,1);
					MessageChat(aIndex, "@[MMOTOP] WcoinC Bonus: %d", this->MMOTOP_BonusWcoinC);
				}

				//if (this->MMOTOP_BonusWcoinP > 0)
				//{
				//	lpObj->GameShop.WCoinP += this->MMOTOP_BonusWcoinP;
				//	gGameShop.GDSaveUserInfo(aIndex);
				//	MessageChat(aIndex, "@[MMOTOP] WCoinP Bonus: %d", this->MMOTOP_BonusWcoinP);
				//}

				//if (this->MMOTOP_BonusWcoinG > 0)
				//{
				//	lpObj->GameShop.GoblinPoint += this->MMOTOP_BonusWcoinG;
				//	gGameShop.GDSaveUserInfo(aIndex);
				//	MessageChat(aIndex, "@[MMOTOP] Goblin Bonus: %d", this->MMOTOP_BonusWcoinG);
				//}

				if (this->MMOTOP_BonusExCred > 0)
				{
#if(SentinelMU)
					ExUser[lpObj->m_Index].PCPoint += this->MMOTOP_BonusExCred;
					MessageChat(aIndex, "@[MMOTOP] ExPoint Bonus: %d", this->MMOTOP_BonusExCred);
					ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);
#else
					lpObj->ExCred += this->MMOTOP_BonusExCred;
					MessageChat(aIndex, "@[MMOTOP] ExCred Bonus: %d", this->MMOTOP_BonusExCred);
#endif
				}

				if (this->MMOTOP_BonusChaosBank > 0)
				{
					lpObj->ChaosBank += this->MMOTOP_BonusChaosBank;
					MessageChat(aIndex, "@[MMOTOP] Chaos Bank Bonus: %d", this->MMOTOP_BonusChaosBank);
				}

				if (this->MMOTOP_BonusBlessBank > 0)
				{
					lpObj->BlessBank += this->MMOTOP_BonusBlessBank;
					MessageChat(aIndex, "@[MMOTOP] Bless Bank Bonus: %d", this->MMOTOP_BonusBlessBank);
				}

				if (this->MMOTOP_BonusSoulBank > 0)
				{
					lpObj->SoulBank += this->MMOTOP_BonusSoulBank;
					MessageChat(aIndex, "@[MMOTOP] Soul Bank Bonus: %d", this->MMOTOP_BonusSoulBank);
				}

				if (this->MMOTOP_BonusLifeBank > 0)
				{
					lpObj->LifeBank += this->MMOTOP_BonusLifeBank;
					MessageChat(aIndex, "@[MMOTOP] Life Bank Bonus: %d", this->MMOTOP_BonusLifeBank);

				}
				MessageChat(aIndex,"@[MMOTOP] Date: %s",DataTime);
			}

			lpObj->MTDate = tData;
			
			ExUserDataSend(aIndex);
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
			LogAdd("[MMOTOP][%s] Date: %s",lpObj->AccountID,DataTime);
		}
		
	}

	fclose(file);
	if (this->MMOTOP_DeleteVoteFile)
	{
		remove(MMOTOP_FILE);
	}
}

// -----------------------------------------------------------------------------------------------------------------------------------

void Voter::Qtop()
{
	if (!this->QTOP_Enable) return;

	//--------------------------------------------------------
	if (QTOP_UPDATE_VOTER == 1)
	{
		if (this->QTOP_DownloadFile)
		{
			URLDownloadToFileA(NULL,
				_T(this->QTOP_FileName),
				_T(QTOP_FILE),
				0, NULL);
		}
	}
	//--------------------------------------------------------
	else if (QTOP_UPDATE_VOTER == 2)
	{
		if (this->QTOP_DownloadFile)
		{
			HINTERNET hSession = InternetOpenA("QTOP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			HINTERNET hHandle = InternetOpenUrlA(hSession, this->QTOP_FileName, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			// ----
			if (hSession == NULL || hHandle == NULL)
			{
				InternetCloseHandle(hSession);
				InternetCloseHandle(hHandle);
				return;
			}
			// ----
			FILE * file = fopen(QTOP_FILE, "w");
			if (file)
			{
				while (true)
				{
					// читаем данные
					char  szData[4096];
					ZeroMemory(szData, sizeof(szData));

					DWORD dwBytesRead;

					BOOL bRead = ::InternetReadFile(hHandle, szData, sizeof(szData)-1, &dwBytesRead);

					// выход из цикла при ошибке или завершении
					if (bRead == FALSE || dwBytesRead == 0)
						break;

					// сохраняем результат
					szData[dwBytesRead] = 0;
					fputs(szData, file);
				}
				fclose(file);
			}

			InternetCloseHandle(hSession);	//Need ?
			InternetCloseHandle(hHandle);
		}

	}
	//--------------------------------------------------------
	else
	{
		// инициализируем WinInet
		HINTERNET hInternet = ::InternetOpen(TEXT("MMOTOP"),
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL,
			0);

		if (hInternet != NULL)
		{
			// открываем HTTP сессию
			HINTERNET hConnect =
				::InternetConnect(
				hInternet,
				TEXT(QTOP_FILE),
				INTERNET_DEFAULT_HTTP_PORT,
				NULL, NULL,
				INTERNET_SERVICE_HTTP,
				0,
				1u);

			if (hConnect != NULL)
			{
				// открываем запрос
				HINTERNET hRequest = ::HttpOpenRequest(hConnect,
					TEXT("GET"),
					TEXT(QTOP_FileName),        //TEXT("votes/aba02abed8021ba31a4499a390aa8afa4679c6d1.txt"),//TEXT("news.asp"),
					NULL,
					NULL,
					0,
					INTERNET_FLAG_KEEP_CONNECTION,
					1);

				if (hRequest != NULL)
				{
					// посылаем запрос
					BOOL bSend = ::HttpSendRequest(hRequest, NULL, 0, NULL, 0);
					if (bSend)
					{
						// создаём выходной файл
						std::ofstream fnews(QTOP_FILE, std::ios::out | std::ios::binary);
						if (fnews.is_open())
						{
							while (true)
							{
								// читаем данные
								char  szData[4096];
								DWORD dwBytesRead;
								BOOL bRead =
									::InternetReadFile(
									hRequest,
									szData, sizeof(szData)-1,
									&dwBytesRead);

								// выход из цикла при ошибке или завершении
								if (bRead == FALSE || dwBytesRead == 0)
									break;

								// сохраняем результат
								szData[dwBytesRead] = 0;
								fnews << szData;
							}
						}
						else
						{
							AdmLog("fnews.is_open()");
						}
					}
					else
					{
						AdmLog("bSend");
					}
					// закрываем запрос
					::InternetCloseHandle(hRequest);
				}
				else
				{
					AdmLog("hRequest != NULL");
				}
				// закрываем сессию
				::InternetCloseHandle(hConnect);
			}
			else
			{
				AdmLog("hConnect != NULL");
			}
			// закрываем WinInet
			::InternetCloseHandle(hInternet);
		}
		else
		{
			AdmLog("hInternet != NULL");
		}
	}
	//--------------------------------------------------------

#ifdef DEBUG_CODE
	AdmLog("DEBUG_CODE");
#endif
#if QTOP_ENABLE == TRUE
	this->QtopReed();
#endif
}

void Voter::QtopReed()
{
	if (!this->QTOP_Enable) return;

	FILE * file = fopen(QTOP_FILE, "r");

	if (file == NULL)
	{
#ifdef VOTE_DEBUG
		LogAddC(2, "[VOTE]No FILE");
#endif
		return;
	}

	char Buff[512];

	int Count = 0;

	while (!feof(file))
	{
		ZeroMemory(&Buff, sizeof(Buff));
		fgets(Buff, 512, file);

		int mId;// = 0;
		char mGetDate[20] = { 0 };
		char mGetTime[20] = { 0 };
		char mGetIp[20] = { 0 };
		char mGetAccaunt[20] = { 0 };
		int mRewerd;


		

		//LogAddC(3, Buff);
		sscanf(Buff, "%d||%s||%s||%s||%s||%d\n", &mId, &mGetDate, &mGetTime, &mGetIp, &mGetAccaunt, &mRewerd);
		//mRewerd[2] = 0;
		LogAddC(2, "%d %s %s %s %s %d", mId, mGetDate, mGetTime, mGetIp, mGetAccaunt, mRewerd);
		//LogAddC(2, "%s %s", &mGetDate, &mGetTime);
		char DataTime[100];
		ZeroMemory(&DataTime, sizeof(DataTime));
		sprintf(DataTime, "%s %s", mGetDate, mGetTime);
		
		int nYear, nMonth, nDay, nHour, nMin, nSec;
		sscanf(DataTime, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		//20140215010507
		//LogAddC(2, "%d.%d.%d %d:%d:%d", &nDay, &nMonth, &nYear, &nHour, &nMin, &nSec);
		if (((nYear >= 1900) && (nMonth >= 1 && nMonth <= 12) && (nDay >= 1 && nDay <= 31) && (nHour >= 0 && nHour <= 23) && (nMin >= 0 && nMin <= 59) && (nSec >= 0 && nSec <= 59)))
		{

		}
		else
		{
			continue;
		}


		int aIndex = -1;

		for (int n = OBJ_STARTUSERINDEX; n<OBJMAX; n++)
		{
			if (gObj[n].Connected >= PLAYER_PLAYING)
			{
				if (gObj[n].AccountID[0] == mGetAccaunt[0])
				{
					if (!strcmp(gObj[n].AccountID, mGetAccaunt))
					{
						aIndex = n;
						break;
					}
				}
			}
		}

		if (aIndex == -1) continue;

		CTime ct = StrToCTime(DataTime);
		DWORD tData = ct.GetTime();

		LPOBJ lpObj = &gObj[aIndex];


	//	if (tData > lpObj->QTDate)
	//	{
	//		if (mRewerd == 2)
	//		{
	//			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//			if (this->QTOP_SMSBonusItemActive)
	//			{
	//				int Height = ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Height;
	//				int Width = ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Width;

	//				if (!CheckInventoryEmptySpace(lpObj, Height, Width))
	//				{
	//					MessageChat(aIndex, "@[SMS QTOP] Need to make space in the inventory (%dx%d)", this->QTOP_SMSBonusWcoinC);
	//					continue;
	//				}

	//				ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex), this->QTOP_SMSBonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
	//				MessageChat(aIndex, "@[SMS QTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Name);
	//			}

	//			if (this->QTOP_SMSBonusWcoinC > 0)
	//			{
	//				lpObj->GameShop.WCoinC += this->QTOP_SMSBonusWcoinC;
	//				gGameShop.GDSaveUserInfo(aIndex);
	//				MessageChat(aIndex, "@[SMS QTOP] WcoinC Bonus: %d", this->QTOP_SMSBonusWcoinC);
	//			}

	//			if (this->QTOP_SMSBonusWcoinP > 0)
	//			{
	//				lpObj->GameShop.WCoinP += this->QTOP_SMSBonusWcoinP;
	//				gGameShop.GDSaveUserInfo(aIndex);
	//				MessageChat(aIndex, "@[SMS QTOP] WCoinP Bonus: %d", this->QTOP_SMSBonusWcoinP);
	//			}

	//			if (this->QTOP_SMSBonusWcoinG > 0)
	//			{
	//				lpObj->GameShop.GoblinPoint += this->QTOP_SMSBonusWcoinG;
	//				gGameShop.GDSaveUserInfo(aIndex);
	//				MessageChat(aIndex, "@[SMS QTOP] Goblin Bonus: %d", this->QTOP_SMSBonusWcoinG);
	//			}

	//			if (this->QTOP_SMSBonusExCred > 0)
	//			{
	//				lpObj->ExCred += this->QTOP_SMSBonusExCred;
	//				MessageChat(aIndex, "@[SMS QTOP] ExCred Bonus: %d", this->QTOP_SMSBonusExCred);
	//			}

	//			if (this->QTOP_SMSBonusChaosBank > 0)
	//			{
	//				lpObj->ChaosBank += this->QTOP_SMSBonusChaosBank;
	//				MessageChat(aIndex, "@[SMS QTOP] Chaos Bank Bonus: %d", this->QTOP_SMSBonusChaosBank);
	//			}

	//			if (this->QTOP_SMSBonusBlessBank > 0)
	//			{
	//				lpObj->BlessBank += this->QTOP_SMSBonusBlessBank;
	//				MessageChat(aIndex, "@[SMS QTOP] Bless Bank Bonus: %d", this->QTOP_SMSBonusBlessBank);
	//			}

	//			if (this->QTOP_SMSBonusSoulBank > 0)
	//			{
	//				lpObj->SoulBank += this->QTOP_SMSBonusSoulBank;
	//				MessageChat(aIndex, "@[SMS QTOP] Soul Bank Bonus: %d", this->QTOP_SMSBonusSoulBank);
	//			}

	//			if (this->QTOP_SMSBonusLifeBank > 0)
	//			{
	//				lpObj->LifeBank += this->QTOP_SMSBonusLifeBank;
	//				MessageChat(aIndex, "@[SMS QTOP] Life Bank Bonus: %d", this->QTOP_SMSBonusLifeBank);
	//			}

	//			MessageChat(aIndex, "@[SMS QTOP] Date: %s", DataTime);
	//		}
	//		else
	//		{
	//			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//			if (this->QTOP_BonusItemActive)
	//			{
	//				int Height = ItemAttribute[ITEMGET(this->QTOP_BonusItemType, this->QTOP_BonusItemIndex)].Height;
	//				int Width = ItemAttribute[ITEMGET(this->QTOP_BonusItemType, this->QTOP_BonusItemIndex)].Width;

	//				if (!CheckInventoryEmptySpace(lpObj, Height, Width))
	//				{
	//					MessageChat(aIndex, "@[QTOP] Need to make space in the inventory (%dx%d)", Height, Width);
	//					continue;
	//				}

	//				ItemSerialCreateSend(aIndex, 235, 0, 0, ITEMGET(this->QTOP_BonusItemType, this->QTOP_BonusItemIndex), this->QTOP_BonusItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
	//				MessageChat(aIndex, "@[QTOP] Item Bonus: %s", ItemAttribute[ITEMGET(this->QTOP_SMSBonusItemType, this->QTOP_SMSBonusItemIndex)].Name);
	//			}

	//			if (this->QTOP_BonusWcoinC > 0)
	//			{
	//				lpObj->GameShop.WCoinC += this->QTOP_BonusWcoinC;
	//				gGameShop.GDSaveUserInfo(aIndex);
	//				MessageChat(aIndex, "@[QTOP] WcoinC Bonus: %d", this->QTOP_BonusWcoinC);
	//			}

	//			if (this->QTOP_BonusWcoinP > 0)
	//			{
	//				lpObj->GameShop.WCoinP += this->QTOP_BonusWcoinP;
	//				gGameShop.GDSaveUserInfo(aIndex);
	//				MessageChat(aIndex, "@[QTOP] WCoinP Bonus: %d", this->QTOP_BonusWcoinP);
	//			}

	//			if (this->QTOP_BonusWcoinG > 0)
	//			{
	//				lpObj->GameShop.GoblinPoint += this->QTOP_BonusWcoinG;
	//				gGameShop.GDSaveUserInfo(aIndex);
	//				MessageChat(aIndex, "@[QTOP] Goblin Bonus: %d", this->QTOP_BonusWcoinG);
	//			}

	//			if (this->QTOP_BonusExCred > 0)
	//			{
	//				lpObj->ExCred += this->QTOP_BonusExCred;
	//				MessageChat(aIndex, "@[QTOP] ExCred Bonus: %d", this->QTOP_BonusExCred);
	//			}

	//			if (this->QTOP_BonusChaosBank > 0)
	//			{
	//				lpObj->ChaosBank += this->QTOP_BonusChaosBank;
	//				MessageChat(aIndex, "@[QTOP] Chaos Bank Bonus: %d", this->QTOP_BonusChaosBank);
	//			}

	//			if (this->QTOP_BonusBlessBank > 0)
	//			{
	//				lpObj->BlessBank += this->QTOP_BonusBlessBank;
	//				MessageChat(aIndex, "@[QTOP] Bless Bank Bonus: %d", this->QTOP_BonusBlessBank);
	//			}

	//			if (this->QTOP_BonusSoulBank > 0)
	//			{
	//				lpObj->SoulBank += this->QTOP_BonusSoulBank;
	//				MessageChat(aIndex, "@[QTOP] Soul Bank Bonus: %d", this->QTOP_BonusSoulBank);
	//			}

	//			if (this->QTOP_BonusLifeBank > 0)
	//			{
	//				lpObj->LifeBank += this->QTOP_BonusLifeBank;
	//				MessageChat(aIndex, "@[QTOP] Life Bank Bonus: %d", this->QTOP_BonusLifeBank);

	//			}
	//			MessageChat(aIndex, "@[QTOP] Date: %s", DataTime);
	//		}

	//		lpObj->QTDate = tData;

	//		ExUserDataSend(aIndex);
	//		GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
	//		LogAdd("[QTOP][%s] Date: %s", lpObj->AccountID, DataTime);
	//	}

	}

	fclose(file);
	if (this->QTOP_DeleteVoteFile)
	{
		remove(QTOP_FILE);
	}
}

#endif