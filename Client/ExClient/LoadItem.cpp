#include "stdafx.h"
#include "readscript.h"
#include "LoadItem.h"

#if(_ITEM_LOAD_)

cLoadItem gLoadItem;

void cLoadItem::Load()
{
	for(int i=0;i<MAX_LOAD_ITEM;i++)
	{
		this->ILoad[i].Type	= 0;
		this->ILoad[i].Index	= 0;
		this->ILoad[i].BMD[0]	= 0;
		this->ILoad[i].Dir1[0]	= 0;
		this->ILoad[i].Dir2[0]	= 0;
	}

	SMDFile = fopen(LOAD_ITEM_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,LOAD_ITEM_DIR,"CRITICAL ERROR",0);
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
				strcpy(this->ILoad[this->Count].BMD,TokenString);

				Token = GetToken();
				strcpy(this->ILoad[this->Count].Dir1,TokenString);

				Token = GetToken();
				strcpy(this->ILoad[this->Count].Dir2,TokenString);

				this->Count++;
			}
		}
    }

	fclose(SMDFile);
}
#endif