#include "StdAfx.h"

#ifdef CONSOLE

#include "windows.h"
#include <stdio.h>
// -----------------------------------------------------------------------
#define CONSOLETITLE "MMOTop Parser"
// -----------------------------------------------------------------------
enum CNSL_E
{
	RED			    = 1,	//Красный
	GREEN			= 2,	//Зеленый
	BLUE			= 3,	//Синий
	CYAN			= 4,	//Белый
	YELLOW			= 5,	//Жолтый
	MAGENTA			= 6,	//Фиолетовый
	GREY			= 7,	//Голубой
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