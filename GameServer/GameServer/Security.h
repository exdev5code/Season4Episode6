#include "StdAfx.h"

#ifdef SECURITYGS

#pragma comment(lib, "rpcrt4.lib")

#define DISK_DIR "c:\\"

#if defined __DoubleDamage__
#define HDD_KEY  1276856910
#define HDD_KEY2 1276855910
#define MAC_ADR "00-25-90-7E-64-C1"
#endif

#if __EvilTwin__
#define HDD_KEY  183270578
#define HDD_KEY2 183269578
#define MAC_ADR "00-50-56-9F-2F-0F"
#endif

#if __MuRain__
#define HDD_KEY  2416675446
#define HDD_KEY2 2416674446
#define MAC_ADR "00-50-56-9F-2F-05"
#endif

#if __ImperiaL__
#define HDD_KEY  538569338
#define HDD_KEY2 538568338
#define MAC_ADR "F4-6D-04-61-53-CB"
#endif

#if __MUFreeZone__
#define HDD_KEY  750895707
#define HDD_KEY2 750894707
#define MAC_ADR "8A-D5-AB-B1-6C-C5"
#endif

#if _Mu_Online_MD_
#define HDD_KEY  2216587006
#define HDD_KEY2 2216586006
#define MAC_ADR "00-27-19-F0-DA-61"
#endif

#ifdef _MegaMu_
#define HDD_KEY  1482567104
#define HDD_KEY2 1482566104
#define MAC_ADR "00-50-56-02-C3-EB"
#endif



class cSecurityGS
{
public:
	bool HDDSecurity();
	bool HDDSecurity2();
	bool MACSecurity();
	bool TwoSecurity();
	bool TreSecurity();
};
extern cSecurityGS SecurityGS;
#endif