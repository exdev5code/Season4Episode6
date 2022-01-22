#include "StdAfx.h"
#include "ExSecurity.h"
#include "VMProtectSDK.h"

#ifdef exSECURITY



exSecurity gSecurity;

void exSecurity::Main()
{
#ifdef exSECURITY
	if()
#endif

}

bool exSecurity::HDD()
{
	unsigned long PCSerialNumber;
	GetVolumeInformationA(DISK_DIR,0,0,&PCSerialNumber,0,0,0,0); 
	if(PCSerialNumber == HDD_KEY) return true;
	else return false;
}



bool exSecurity::MAC()
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

//void License::GetAdapter()
//{
//	VMBEGIN
//	DWORD	BufferLength	= 0;
//	LPBYTE	Buffer			= 0;
//	// ----
//	if( ERROR_BUFFER_OVERFLOW == GetAdaptersInfo(0, &BufferLength) )
//	{
//		Buffer = new BYTE[BufferLength];
//	}
//	// ----
//	PIP_ADAPTER_INFO AdapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(Buffer);
//	GetAdaptersInfo(AdapterInfo, &BufferLength);
//	// ----
//	if( AdapterInfo )
//	{
//		for( int i = 0; i < MAX_ADAPTER_ADDRESS_LENGTH; i++ )
//		{
//			this->m_Data.Adapter[i] = AdapterInfo->Address[i];
//		}
//	}
//	else
//	{
//		MessageBoxA(NULL, GetText("@scjs1fnu`;17"), GetText("Ihr`ob`!tws~w"), ERROR);
//		this->SendAlert(2, 2);
//		ExitProcess(0);
//	}
//	// ----
//	delete[] Buffer;
//	VMEND
//}

//LPSTR License::GetText(LPSTR EncodedChar)
//{
//	VMBEGIN
//	BYTE XorKey[] = { 0x05, 0x01, 0x11 };
//	LPSTR Line = new char[strlen(EncodedChar)+1];
//	// ----
//	for( int i = 0; i < strlen(EncodedChar); i++ )
//	{
//		Line[i] = char(EncodedChar[i] ^ XorKey[i % 3]);
//	}
//	// ----
//	VMEND
//	return Line;
//}

#endif