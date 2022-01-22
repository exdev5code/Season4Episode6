#include "StdAfx.h"
#include "CreditDonate.h"
#include "Functions.h"
#include "CreditDonate.h"
#include "user.h"
#include "DSProtocol.h"
#include "logproc.h"
#include "PCPointSystem.h"
#include "..\\include\\ReadScript.h"
#include "..\\common\zzzitem.h"

int SetCount(int Type)
{
	if( ItemAttribute[Type].RequireClass[0] == 0 && 
		ItemAttribute[Type].RequireClass[1] == 0 &&   
		ItemAttribute[Type].RequireClass[2] == 0 && 
		ItemAttribute[Type].RequireClass[4] == 0 &&
		ItemAttribute[Type].RequireClass[5] == 0 )
	{
		if( ItemAttribute[Type].RequireClass[3] > 0 )
		{
			return 4;
		}
	}

	return 5;
}

#if(_CREDIT_DONATE_)

cCreditDonate gCreditDonate;

void cCreditDonate::Load()
{
	//this->Enable = GetPrivateProfileInt("Common","Enable",0,CR_DONATE_DIR);
	//this->SellProcent = GetPrivateProfileInt("Common","SellProcent",0,CR_DONATE_DIR);

	for(int i=0;i<MAX_DONATE_ITEM;i++)
	{
		this->Donate[i].cmd[0]	= 0;
		this->Donate[i].Type	= 0;
		this->Donate[i].Index	= 0;
		this->Donate[i].Level	= 0;
		this->Donate[i].Skill	= 0;
		this->Donate[i].Luck	= 0;
		this->Donate[i].Opt		= 0;
		this->Donate[i].Exl		= 0;
		this->Donate[i].Anc		= 0;
		this->Donate[i].CrPrice	= 0;
	}

	//FILE *file = fopen(CR_DONATE_DIR,"r");

	//if(file == NULL)
	//{
	//	this->Enable = 0;
	//	return;
	//}

	//char Buff[256];
	//int Flag = 0;
	//this->Count = 0;

	//while(!feof(file))
	//{
	//	fgets(Buff,256,file);	
	//	if(Ex_IsBadFileLine(Buff, Flag))	
	//		continue;

	//	if(Flag == 1)
	//	{
	//		int n[9];
	//		char mes[100];

	//		sscanf(Buff,"\"%[^\"]\" %d %d %d %d %d %d %d %d %d",&mes,&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8]);

	//		sprintf(this->Donate[this->Count].cmd,"%s",mes);

	//		this->Donate[this->Count].Type		= n[0];
	//		this->Donate[this->Count].Index		= n[1];
	//		this->Donate[this->Count].Level		= n[2];
	//		this->Donate[this->Count].Skill		= n[3];
	//		this->Donate[this->Count].Luck		= n[4];
	//		this->Donate[this->Count].Opt		= n[5];
	//		this->Donate[this->Count].Exl		= n[6];
	//		this->Donate[this->Count].Anc		= n[7];

	//		this->Donate[this->Count].CrPrice	= n[8];

	//		this->Count++;
	//	}
	//}
	//fclose(file);

	SMDFile = fopen(CR_DONATE_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,CR_DONATE_DIR,"CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	int Token;
	int Category = -1;

	this->Count = 0;

	while ( true )
	{
	    Token = GetToken();

        if( Token == END)
		{
            break;
		}

		Category = (int)TokenNumber;

		while ( true )
		{
			if ( Category == 0 )	//Config
			{
				Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					break;
				}

				this->Enable = TokenNumber;

				Token = GetToken();
				this->SellProcent = TokenNumber;
			}
			if ( Category == 1 )	//Item List
			{
				Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					break;
				}

				strcpy(this->Donate[this->Count].cmd,TokenString);
				Token = GetToken();
				this->Donate[this->Count].Type		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Index		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Level		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Skill		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Luck		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Opt		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Exl		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].Anc		= TokenNumber;
				Token = GetToken();
				this->Donate[this->Count].CrPrice	= TokenNumber;

				this->Count++;
			}
		}
    }

	fclose(SMDFile);
}

void cCreditDonate::Chat(int aIndex,LPBYTE Protocol)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	for(int i=0;i<this->Count;i++)
	{
		if(!memcmp(&Protocol[13],this->Donate[i].cmd,strlen(this->Donate[i].cmd)))
		{
			if ( CheckInventoryEmptySpace(lpObj,4,8) == false )
			{
				GCServerMsgStringSend("[Credit Donate]: Need to make space in the inventory (4x8)",aIndex,1);
				return;
			}

			if(this->Donate[i].CrPrice > lpObj->ExCred)
			{
				MsgOutput(aIndex,"[Credit Donate]: Need %d Credits",this->Donate[i].CrPrice);
				return;
			}

			lpObj->ExCred -= this->Donate[i].CrPrice;
			ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);

			if(this->Donate[i].Type == -1)
			{
				ItemSerialCreateSend(aIndex,236,1,1,ITEMGET(7,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
				ItemSerialCreateSend(aIndex,236,1,1,ITEMGET(8,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
				ItemSerialCreateSend(aIndex,236,1,1,ITEMGET(9,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
				ItemSerialCreateSend(aIndex,236,1,1,ITEMGET(10,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
				ItemSerialCreateSend(aIndex,236,1,1,ITEMGET(11,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
			}
			else
			{
				ItemSerialCreateSend(aIndex,236,1,1,ITEMGET(this->Donate[i].Type,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
			}

			LogAdd("[CREDIT DONATE][%s] Type: %d, Index: %d, Level: %d, Skill: %d, Luck: %d, Opt: %d, Exellent: %d, Ancent: %d",
				lpObj->AccountID,this->Donate[i].Type,this->Donate[i].Index,this->Donate[i].Level,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,this->Donate[i].Exl,this->Donate[i].Anc);

			
			return;
		}
	}
}

void cCreditDonate::Sell(int aIndex, int Pos, int &iAddZen)
{
	if(!this->Enable) return;


	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->pInventory[Pos].m_Number != 1)
	{
		return;
	}

	for(int i=0;i<this->Count;i++)
	{
		if( lpObj->pInventory[Pos].m_Type == ITEMGET(this->Donate[i].Type,this->Donate[i].Index) && lpObj->pInventory[Pos].m_Level == this->Donate[i].Level )
		{
			int CrSell = this->Donate[i].CrPrice - ( ( this->Donate[i].CrPrice * this->SellProcent ) / 100 );
			lpObj->ExCred += CrSell;
			ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);
			MsgOutput(aIndex,"[Credit Donate]: Sell %d Credits",CrSell);
			iAddZen = 0;
			return;
		}
		else if( this->Donate[i].Type == -1 && lpObj->pInventory[Pos].m_Type % 512 == this->Donate[i].Index && lpObj->pInventory[Pos].m_Level == this->Donate[i].Level  )
		{
			int NewPrice = this->Donate[i].CrPrice / SetCount(lpObj->pInventory[Pos].m_Type);

			int CrSell = NewPrice - ( ( NewPrice * this->SellProcent ) / 100 );
			lpObj->ExCred += CrSell;
			ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);
			MsgOutput(aIndex,"[Credit Donate]: Sell %d Credits",CrSell);
			iAddZen = 0;
			return;
		}
	}
}


#endif