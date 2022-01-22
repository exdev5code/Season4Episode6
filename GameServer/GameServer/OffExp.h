#ifndef _OFFEXP_H
#define _OFFEXP_H

#define OFF_EXP_DIR "..\\ExTeam\\OffExp.ini"

class cOffExp
{
public:
	int Enable;
	int KickFallen;
	int EnableTime;
	int TimeEnd;

	int OffAfkWcoin10min;

	int OffAfkPriceExPoint;
	int OffAfkPriceWCoin;
	int OffAfkPriceCredit;

	void LoadConfig();

	void OffExpStart(int aIndex);

	void MainFunction(int aIndex);

	void DarkKnightOff(LPOBJ lpObj);
	void DarkWizardOff(LPOBJ lpObj);
	void FairyElfOff(LPOBJ lpObj);
	void MagicGladiatorOff(LPOBJ lpObj);
	void DarkLordOff(LPOBJ lpObj);
	void SummonerOff(LPOBJ lpObj);
	void RageFighterOff(LPOBJ lpObj);

	void UseMana(int aIndex);

	int SearchTarget(LPOBJ lpObj);

	bool CheckTerrain(LPOBJ lpObj);

	//void TickTimes(int aIndex);
};
extern cOffExp OffExp;

#endif _OFFEXP_H