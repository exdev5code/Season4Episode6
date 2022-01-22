#pragma once
#include "StdAfx.h"
#ifdef exSECURITY

#define DISK_DIR "c:\\"

class exSecurity
{
	void Main();
	bool HDD();
	bool MAC();
	//PSTR GetText(LPSTR EncodedChar);
};
extern exSecurity gSecurity;

#endif