#include "StdAfx.h"

#ifdef SECURITYGS

#include "Security.h"

cSecurityGS SecurityGS;

bool cSecurityGS::HDDSecurity()
{
	unsigned long PCSerialNumber;
	GetVolumeInformationA(DISK_DIR,0,0,&PCSerialNumber,0,0,0,0); 
	if(PCSerialNumber == HDD_KEY) return true;
	else return false;
}

bool cSecurityGS::HDDSecurity2()
{
	unsigned long PCSerialNumber;
	GetVolumeInformationA(DISK_DIR,0,0,&PCSerialNumber,0,0,0,0); 
	//PCSerialNumber += 1000;
	if(PCSerialNumber == (HDD_KEY2+1000)) return true;
	else return false;
}

bool cSecurityGS::MACSecurity()
{
	unsigned char MACData[6];
	UUID uuid;
	UuidCreateSequential( &uuid );

	for (int i=2; i<8; i++) 
		MACData[i - 2] = uuid.Data4[i];

	char MACADDR[18];
	sprintf(MACADDR, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);

	if(!strcmp(MACADDR,MAC_ADR)) return true;
	else return false;
}

bool cSecurityGS::TwoSecurity()
{
	if(HDDSecurity() == true && MACSecurity() == true) return true;
	else return false;
}

bool cSecurityGS::TreSecurity()
{
	if(HDDSecurity() == true && MACSecurity() == true && HDDSecurity2() == true) return true;
	return false;
}

#endif