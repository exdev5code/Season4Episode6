#include "StdAfx.h"

#ifdef _VOTER_


#define VOTER_DIR		"..\\ExTeam\\Voter.ini"
#define MMOTOP_FILE		"mmotop.txt"
#define QTOP_FILE		"qtop.txt"

#define QTOP_ENABLE		0


//#define VOTE_DEBUG	0

class Voter
{
private:

	bool MMOTOP_Enable;

	// ----

	bool MMOTOP_DeleteVoteFile;
	bool MMOTOP_DownloadFile;

	int MMOTOP_UPDATE_VOTER;

	char MMOTOP_FileName[200];

	int MMOTOP_BonusWcoinC;
	int MMOTOP_BonusWcoinP;
	int MMOTOP_BonusWcoinG;
	int MMOTOP_BonusExCred;

	int MMOTOP_BonusItemActive;
	int MMOTOP_BonusItemType;
	int MMOTOP_BonusItemIndex;
	int MMOTOP_BonusItemLevel;

	int MMOTOP_BonusChaosBank;
	int MMOTOP_BonusBlessBank;
	int MMOTOP_BonusSoulBank;
	int MMOTOP_BonusLifeBank;

	int MMOTOP_SMSBonusWcoinC;
	int MMOTOP_SMSBonusWcoinP;
	int MMOTOP_SMSBonusWcoinG;
	int MMOTOP_SMSBonusExCred;

	int MMOTOP_SMSBonusItemActive;
	int MMOTOP_SMSBonusItemType;
	int MMOTOP_SMSBonusItemIndex;
	int MMOTOP_SMSBonusItemLevel;

	int MMOTOP_SMSBonusChaosBank;
	int MMOTOP_SMSBonusBlessBank;
	int MMOTOP_SMSBonusSoulBank;
	int MMOTOP_SMSBonusLifeBank;

	//~~~~~~~~~~~~~~~~

	bool QTOP_Enable;

	bool QTOP_DeleteVoteFile;
	bool QTOP_DownloadFile;

	int QTOP_UPDATE_VOTER;

	char QTOP_FileName[200];

	int QTOP_BonusWcoinC;
	int QTOP_BonusWcoinP;
	int QTOP_BonusWcoinG;
	int QTOP_BonusExCred;

	int QTOP_BonusItemActive;
	int QTOP_BonusItemType;
	int QTOP_BonusItemIndex;
	int QTOP_BonusItemLevel;

	int QTOP_BonusChaosBank;
	int QTOP_BonusBlessBank;
	int QTOP_BonusSoulBank;
	int QTOP_BonusLifeBank;

	int QTOP_SMSBonusWcoinC;
	int QTOP_SMSBonusWcoinP;
	int QTOP_SMSBonusWcoinG;
	int QTOP_SMSBonusExCred;

	int QTOP_SMSBonusItemActive;
	int QTOP_SMSBonusItemType;
	int QTOP_SMSBonusItemIndex;
	int QTOP_SMSBonusItemLevel;

	int QTOP_SMSBonusChaosBank;
	int QTOP_SMSBonusBlessBank;
	int QTOP_SMSBonusSoulBank;
	int QTOP_SMSBonusLifeBank;

	// ----

public:
	void Init();
	// ----
	void Mootop();
	void MootopReed();
	// ----
	void Qtop();
	void QtopReed();

};
extern Voter gVoter;

#endif