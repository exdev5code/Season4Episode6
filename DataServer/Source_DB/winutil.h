#ifndef __WINUTIL_H__
#define __WINUTIL_H__



// ���� �ѵ��� �˻��Ѵ�. max���� ������ 0 ���� ������ 1�̴�.
#define CHECK_LIMIT(C_VALUE, C_MAX) (C_VALUE<0?FALSE:C_VALUE>(C_MAX-1)?FALSE:TRUE)



extern void BuxConvert(char *buf, int size);
extern BOOL SQLSyntexCheck(char *SQLString);
extern BOOL SQLSyntexCheckConvert(char *SQLString);
extern BOOL SpaceSyntexCheck(char *string);
extern BOOL StrHangulCheck(char * str);
extern void FileSaveString(char *filename, char * string);
extern BOOL IsFile(char *fileName);

#endif

