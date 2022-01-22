#include "StdAfx.h"
#ifdef CONSOLE
#include <stdio.h>
#include "windows.h"
#include "Console.h"


// -----------------------------------------------------------------------
cConsole Console;
// -----------------------------------------------------------------------
DWORD PiD;
// -----------------------------------------------------------------------
void cConsole::InitCore()
{
	AllocConsole();
	SetConsoleTitleA("TEST");
	this->ConsoleOutput(BLUE,"###################################################################");
	this->ConsoleOutput(YELLOW,"\t\t\tClient 1.03k");
	this->ConsoleOutput(YELLOW,"\t\t\tDeveloper: DangeR");
	this->ConsoleOutput(YELLOW,"\t\t\tSkype: muonline.bk");
	this->ConsoleOutput(BLUE,"###################################################################");
}
// -----------------------------------------------------------------------
void cConsole::ConsoleOutput(int Color , const char* Format, ...)
{
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	// ----
	char Message[1024];
	char MessageOutPut[2048];
	DWORD dwBytes;
	// ----
	HANDLE Handle		 = GetStdHandle(STD_OUTPUT_HANDLE);
	char CorrectDate[11] = {0};
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message , Format , pArguments);
	va_end(pArguments);
	// ----
	sprintf_s(CorrectDate , "[%02d:%02d:%02d]" , Time.wHour , Time.wMinute , Time.wSecond);
	// ----
	sprintf_s(MessageOutPut , "%s %s\n" , CorrectDate , Message);
	// ----
	switch(Color)
	{
		// Color Red Console.
		case CNSL_E::RED:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		break;
		// Color Green Console.
		case CNSL_E::GREEN:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		break;
		// Color Blue Console.
		case CNSL_E::BLUE:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		break;
		// Color Cyan Console.
		case CNSL_E::CYAN:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		break;
		// Color Yellow Console.
		case CNSL_E::YELLOW:
		{
			SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		break;
		case MAGENTA: 
			SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
		case 7:
			SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;

	}
	// ----
	WriteFile(Handle , MessageOutPut , strlen(MessageOutPut) , &dwBytes , NULL);
}
// -----------------------------------------------------------------------
HANDLE cConsole::Handle(BOOL gImput)
{
	if(gImput == TRUE)
	{
		return GetStdHandle(STD_INPUT_HANDLE);
	}
	// ----
	else
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
}
// -----------------------------------------------------------------------
extern cConsole Console;
// -----------------------------------------------------------------------

#endif