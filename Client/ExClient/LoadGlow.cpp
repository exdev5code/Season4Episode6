#include "stdafx.h"
#include "readscript.h"
#include "LoadGlow.h"

#if(_LOAD_GLOW_)

cLoadGlow gLoadGlow;

void cLoadGlow::Load()
{
	for(int i=0;i<MAX_LOAD_GLOW;i++)
	{
		this->ILoad[i].Type	= 0;
		this->ILoad[i].Index	= 0;
		this->ILoad[i].Red	= 0;
		this->ILoad[i].Green	= 0;
		this->ILoad[i].Blue	= 0;
	}

	SMDFile = fopen(LOAD_GLOW_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,LOAD_GLOW_DIR,"CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	int Token;
	int Category = -1;

	this->Count = 0;

	while ( true )
	{
	    Token = GetToken();

        if( Token == END)
		{
            break;
		}

		Category = (int)TokenNumber;

		while ( true )
		{

			if ( Category == 0 )	//Item List
			{
				Token = GetToken();

				if ( strcmp("end", TokenString ) == 0)
				{
					break;
				}

				this->ILoad[this->Count].Type		= TokenNumber;

				Token = GetToken();
				this->ILoad[this->Count].Index		= TokenNumber;

				Token = GetToken();
				this->ILoad[this->Count].Red		= TokenNumber;

				Token = GetToken();
				this->ILoad[this->Count].Green		= TokenNumber;

				Token = GetToken();
				this->ILoad[this->Count].Blue		= TokenNumber;

				this->Count++;
			}
		}
    }

	fclose(SMDFile);
}
#endif