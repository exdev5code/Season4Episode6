#include "StdAfx.h"

#ifdef CONSOLE

#include "windows.h"
#include <stdio.h>
// -----------------------------------------------------------------------
#define CONSOLETITLE "MMOTop Parser"
// -----------------------------------------------------------------------
enum CNSL_E
{
	RED			    = 1,	//�������
	GREEN			= 2,	//�������
	BLUE			= 3,	//�����
	CYAN			= 4,	//�����
	YELLOW			= 5,	//������
	MAGENTA			= 6,	//����������
	GREY			= 7,	//�������
};
class cConsole
{
public:
	void InitCore();
	void ConsoleOutput(int Color, const char* Format, ...);
	HANDLE Handle(BOOL Input);
};
// -----------------------------------------------------------------------
extern cConsole Console;
// -----------------------------------------------------------------------

#endif