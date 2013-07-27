
/*!
* 
* \file 
* \author HuangYin
* \date	  2010.3.10
* \brief  ȫ�ֱ��������������ͺ͹��ú궨��
* 
* \ref    CopyRight
*/

#ifndef __TGLOBAL_H__
#define __TGLOBAL_H__

#include "TG3.h"
#include <string>
#include <list>

typedef UInt32 STATUS_ID;

/** һ����ʾ����Ŀ���� */
#define  ITEM_COUNTS_PAGE 20

/** _T_stricmp�꣬���ִ�Сд���ַ����Ƚ� */
#ifdef WIN32
#  define _T_stricmp _stricmp
#else
#  define _T_stricmp strcasecmp
#endif

enum CharType
{
    ControlChar,

    DigestChar,

    LetterChar,

    SpecialSign,

    OtherChar
};


/** ���ַ���תΪ�Էָ����������ַ����б� */
void TokenizeString(const std::string& strInput, const std::string& strDelim, std::list<std::string>& tokenList);

/** ����ab|dc|aa����ʽ���ַ�����"|"�ָ��תΪ�ַ����б� */
bool StringToItems(const std::string& s, std::list<std::string>& itemList);


/** ���ַ���תΪ����ֵ */
bool StringToBool(const char* s, bool& flag);

/** ���ַ���תΪ�з������� */
bool StringToInteger(const char*  p, int& val);

/** ���ַ���תΪ�з������� */
bool StringToInteger(const char*  p, Int16& val);

/** ���ַ���תΪ�޷������� */
bool StringToUnsignedInt(const char*  p, UInt32& val, Int32 nRadix);

/** ���ַ���תΪ�޷���64λ���� */
bool StringToUInt64(const char*  p, STATUS_ID& val, Int32 nRadix);

/** ���ַ���תΪ�з��������� */
bool StringToIntPair(const char* s1, const char* s2, Int32& nInt1, Int32& nInt2);

/** ���ַ���תΪTRectangle */
bool StringToRect(const char* x, const char*  y, const char*  w, const char*  h, TRectangle& rc);


bool StringToDateTime(const char* pszText, DateTimeType &dt);


Boolean IsFileVaild(const char* pszFilePath, Boolean bIsUtf8 = FALSE);

Boolean IsFileVaild(const TUChar* pszFilePath);

Boolean IsImageFileVaild(const char* pszFilePath, Boolean bIsUtf8 = FALSE);

Boolean IsImageFileVaild(const TUChar* pszFilePath);


char *ustrncat (char * dst, const char * src, int nCount);

char *ustrncat_utf8 (char * dst, const TUChar * src, int nCount);

TUChar *ustrncat_utf8 (TUChar * dst, const char * src, int nCount);

TUChar *ustrncat_gb (TUChar * dst, const char * src, int nCount);

char *ustrncpy_utf8 (char * dst, const TUChar * src, int n);

TUChar *ustrncpy_utf8 (TUChar * dst, const char * src, int n);

void LogoutError(const TUChar* pszErrorU);

void LogoutError(const char* pszError, ...);


std::string char2hex( char dec );

std::string urlencode(const std::string &c);


CharType TestCharType(char c);

#endif //__TGLOBAL_H__

