#include "StdAfx.h"
#include "Connect.h"
#include "ToolKit.h"
#include "Security.h"



void Ip() 
{
	int *IpAddress = (int*)0x008C2FC4;

#ifdef _IP_NEW_
	char szIPAddress[20] = _IP_NEW_;
	memset(&IpAddress[0], 0x00, sizeof(szIPAddress));
	memcpy(&IpAddress[0], szIPAddress, sizeof(szIPAddress)); 
	return;
#endif

//#if defined __LOCAL__
//	char rIpAddress[] = "192.168.0.100";
//#endif
#if __ExGames__
	//char rIpAddress[] = "91.213.8.230";
#endif
#ifdef __EvilTwin__
	char rIpAddress[] = "91.213.8.78";
#endif
#ifdef __MuRain__
	//char rIpAddress[] = "91.213.8.80";
#endif
#ifdef __MUFreeZone__
	char rIpAddress[] = "81.163.119.74";
#endif

	char rIpAddress[20] = _IP_;

#ifdef aMUnra 
	//GetPrivateProfileStringA("Connect","ip","127.0.0.1",rIpAddress,sizeof(rIpAddress),".\\Connect.ini");

	//WritePrivateProfileStringA("Connect","ip","127.0.0.2",".\\Connect.ini");
#endif 

	memset(&IpAddress[0], 0x00, sizeof(rIpAddress));
	memcpy(&IpAddress[0], rIpAddress, sizeof(rIpAddress)); 
}

void Version() 
{
#ifdef _GS_5_
	
	char rVersion[] = "2266:";	//22656
	int *Version = (int*)(0x008D7D2C);
	memset(&Version[0], 0x00, sizeof(rVersion));
	memcpy(&Version[0], rVersion, sizeof(rVersion)); 
#else
	char rVersion[] = "22656";	//22656
	int *Version = (int*)(0x008D7D2C);
	memset(&Version[0], 0x00, sizeof(rVersion));
	memcpy(&Version[0], rVersion, sizeof(rVersion)); 
#endif
}

void SerialNumber() 
{
	int *SerialNumber = (int*)(0x008D7D34);	

#ifdef _SERIAL_NEW_
	char szSerialNumber[] = _SERIAL_NEW_;
	memset(&SerialNumber[0], 0x00, sizeof(szSerialNumber));
	memcpy(&SerialNumber[0], szSerialNumber, sizeof(szSerialNumber)); 
	return;
#endif

#ifdef _GS_5_
	memset(&SerialNumber[0], 0x00, sizeof("1qve7Lcvdhk3Rysq"));
	memcpy(&SerialNumber[0], "1qve7Lcvdhk3Rysq", sizeof("1qve7Lcvdhk3Rysq")); 
#else
	memset(&SerialNumber[0], 0x00, sizeof(Security.RealSerial));
	memcpy(&SerialNumber[0], Security.RealSerial, sizeof(Security.RealSerial)); 
#endif
}