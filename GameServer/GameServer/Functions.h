unsigned char GetRandomExeOption(unsigned char MaxOption);
bool Ex_IsBadFileLine(char *FileLine, int &Flag);
int GetNumberByPercent(int Proc, int Min, int Max);
int GenExcOpt(int amount);
int gObjGetItemCountInInventory(int aIndex, int ItemID,int ItemLevel);
int gObjDeleteItemsCount(int aIndex, short Type, short Level, int dCount);
void ExFireCracker(int aIndex, BYTE X, BYTE Y);
bool ItemMoveBlockExlOpt(int exlopt_num);
#ifdef _MuReal_
void TimeTickWCoin(int aIndex);
#endif
BYTE GetExcOptionCount(BYTE ExcellentOption);
int EmptyPointInventory(int aIndex);