
struct EXINFO_UPDATE
{
	PBMSG_HEAD2 h;
	int PremiumTime;
	int Chaos;
	int Bless;
	int Soul;
	int Life;
	float ExCred;
};

void ExUserVieweport(int aIndex);
void ExUserDataSend(int aIndex);