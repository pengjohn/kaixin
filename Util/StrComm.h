//StrComm.h
#ifndef  __StrComm_H__
#define  __StrComm_H__

#include "TG3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Char����,��Ҫ�����ͷ�
extern char* StrDump(char* pszSrc);
//�滻�ַ�
char* StrReplaceAtoB(char* pSrc, int size, char* strA, char* strB);
//TUChar����, ��Ҫ�����ͷ�
extern TUChar* WStrDump(TUChar* pszSrc);
//�ص������ؼ�������ַ���(�����ؼ���)
extern char* StrRemoveAtoB(char* pSrc, int size, char* strA, char* strB);

extern char* DoubleToChar(double n, char* c);

extern Boolean IsNullString(char* c);
#endif