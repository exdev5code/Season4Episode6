#define Main_PrintGlobal 00515180H; //1.03k

void Message_Glob(int ColorId, char* Message)
{
	_asm
        {    
        Mov Edi,Main_PrintGlobal
        Push ColorId
        Push Message
        Call Edi
		Add Esp,0x8
        }
}