
/*!
* 
* \file 
* \author HuangYin
* \date	  2010.3.10
* \brief  ȫ�ֱ��������������ͺ͹��ú궨��
* 
* \ref    CopyRight
*/

#include "TGlobal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>

// stl
using namespace std;


///////////////////////////////////////////////////////////////////////////
//                                                                       // 
//    ȫ�ֺ�������                                                       //
//                                                                       //
///////////////////////////////////////////////////////////////////////////


/** ���ַ���תΪ�Էָ����������ַ����б�
* 
* \param strInput Ҫ�ָ���ַ�����string
* \param strDelim �ָ�����string
* \param[out] tokenList �ָ�ɵ��ַ����б�
* \return  ��
*/ 
void TokenizeString(const string& strInput, const string& strDelim, list<string>& tokenList)
{
    // Clear the target list.
    tokenList.clear();

    // Check for empty input string.
    if ( strInput.empty() )
        return;

    // Check for empty delimiter.
    if ( strDelim.empty() && !strInput.empty() )
    {
        tokenList.push_back(strInput);
        return;
    }

    // Proceed with tokenizing.
    string currToken = "";
    UInt32 nInputLen = strInput.length();
    for(UInt32 i = 0; i < nInputLen; ++i)
    {
        // Check if there is a delimiter at position i.
        if ( i < (nInputLen - strDelim.length() + 1) &&
            strInput.substr(i, strDelim.length()).compare(strDelim) == 0 )
        {
            if ( !currToken.empty() )
            {
                tokenList.push_back(currToken);
            }
            currToken = "";

            i += (strDelim.length() - 1);
        } 
        else
        {
            currToken += strInput.at(i);
        }
    }
    if ( !currToken.empty() )
    {
        tokenList.push_back(currToken);
    }

}

/** ����ab|dc|aa����ʽ���ַ�����"|"�ָ��תΪ�ַ����б�
* 
* \param s             �ַ�����string
* \param[out] itemList �ָ�ɵ��ַ����б�
* \return  �Ƿ�ɹ�
*/ 
bool StringToItems(const string& s, std::list<string>& itemList)
{
    if ( s.empty() )
        return false;

    TokenizeString(s, "|", itemList);

    return true;
}

/** ���ַ���תΪ����ֵ
* 
* \param s         char*�ַ���
* \param[out] flag ת���ɵĲ���ֵ
* \return  �Ƿ�ɹ�
*/ 
bool StringToBool(const char* s, bool& flag)
{
    if ( s == NULL || *s == 0 )
        return false;

    //if ( cmp_nocase(s, "true") == 0 )
    if(_T_stricmp(s,"true") == 0)
        flag = true;
    else
        flag = false;

    return true;
}

/** ���ַ���תΪ�з�������
* 
* \param p         char*�ַ���
* \param[out] val ת���ɵ��з�������
* \return  �Ƿ�ɹ�
*/ 
bool StringToInteger(const char*  p, int& val)
{
    if ( p == NULL || *p == 0 )
        return false;

    val = atoi(p);

    return true;
}

/** ���ַ���תΪ�з�������
* 
* \param p         char*�ַ���
* \param[out] val ת���ɵ��з�������
* \return  �Ƿ�ɹ�
*/ 
bool StringToInteger(const char*  p, Int16& val)
{
    if ( p == NULL || *p == 0 )
        return false;

    val = atoi(p);

    return true;
}


/** ���ַ���תΪ�޷�������
* 
* \param p        char*�ַ���
* \param[out] val ת���ɵ��޷�������
* \param nRadix   ���� 
* \return  �Ƿ�ɹ�
*/ 
bool StringToUnsignedInt(const char*  p, UInt32& val, Int32 nRadix)
{
    if ( p == NULL || *p == 0 )
        return false;

    val = strtoul(p, NULL, nRadix);

    return true;
}

/** ���ַ���תΪ�޷���64λ����
* 
* \param p        char*�ַ���
* \param[out] val ת���ɵ��޷���64λ����
* \param nRadix   ���� 
* \return  �Ƿ�ɹ�
*/ 
bool StringToUInt64( const char*  p, STATUS_ID& val, Int32 nRadix)
{
    if ( p == NULL || *p == 0 )
        return false;

    val = strtoul(p, NULL, nRadix);

    return true;
}

/** ���ַ���תΪ�з���������
* 
* \param s1         char*�ַ���1
* \param s2         char*�ַ���2
* \param[out] nInt1 ת���ɵ��з�������1
* \param[out] nInt2 ת���ɵ��з�������2
* \return  �Ƿ�ɹ�
*/ 
bool StringToIntPair(const char* s1, const char* s2, Int32& nInt1, Int32& nInt2)
{
    if ( s1 == NULL || *s1 == 0 || s2 == NULL || *s2 == 0)
        return false;


    nInt1 = atoi(s1);

    nInt2 = atoi(s2);

    return true;
}

/** ���ַ���תΪTRectangle
* 
* \param x         char*�ַ�����Left���ꡣ
* \param y         char*�ַ�����Right���ꡣ
* \param w         char*�ַ��������W��
* \param h         char*�ַ������߶�H��
* \param[out] rc ת���ɵ�TRectangle
* \return  �Ƿ�ɹ�
*/ 
bool StringToRect(const char* x, const char*  y, const char*  w, const char*  h, TRectangle& rc)
{
    if ( x == NULL || x == 0 || y == NULL || y == 0|| w == NULL || w== 0|| h == NULL || h== 0)
        return false;


    rc.SetX(atoi(x));

    rc.SetY(atoi(y));

    rc.SetWidth(atoi(w));

    rc.SetHeight(atoi(h));

    return true;
}

/** ���ַ���ת��Ϊ����ʱ�䣬�ַ�����ʽ���磺Wed Jul 28 13:58:41 +0800 2010
*
* \param pszText ����ʱ���ַ���
* \param[out] dt ����ʱ��    
* \return �Ƿ�ɹ�
*/
bool StringToDateTime( const char* pszText, DateTimeType &dt )
{
    if (!pszText || !*pszText)
    {
        return false;
    }

    char *pszWord;
    char *pszSpace;
    char  *pszBuf;
    Int32 nLen;
    Int32 nDay;
    Int32 nHour;
    Int32 nMinute;
    Int32 nSecond;
    Int32 nYear;
    Int32 nTimeZone;

    nLen = strlen(pszText);
    pszBuf = new char[nLen + 1];
    MemSet(pszBuf, 0, nLen+1);
    strncpy(pszBuf, pszText, nLen);

    pszWord = pszBuf;
    pszSpace = NULL;
    nTimeZone = 0;
    nDay = 0;
    nHour = 0;
    nMinute = 0;
    nSecond = 0;
    nYear = 0;

    pszSpace = strstr(pszWord, " ");
    if (!pszSpace)
    {
        return false;
    }

    *pszSpace = 0;
    if (_T_stricmp(pszWord, "Mon") == 0)
    {
        dt.weekDay = 1;
    }
    else if (_T_stricmp(pszWord, "Tue") == 0)
    {
        dt.weekDay = 2;
    }
    else if (_T_stricmp(pszWord, "Wed") == 0)
    {
        dt.weekDay = 3;
    }
    else if (_T_stricmp(pszWord, "Thu") == 0)
    {
        dt.weekDay = 4;
    }
    else if (_T_stricmp(pszWord, "Fri") == 0)
    {
        dt.weekDay = 5;
    }
    else if (_T_stricmp(pszWord, "Sat") == 0)
    {
        dt.weekDay = 6;
    }
    else if (_T_stricmp(pszWord, "Sun") == 0)
    {
        dt.weekDay = 7;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    pszSpace = strstr(pszWord, " ");
    if (!pszSpace)
    {
        return false;
    }

    *pszSpace = 0;
    if (_T_stricmp(pszWord, "Jan") == 0)
    {
        dt.month = 1;
    }
    else if (_T_stricmp(pszWord, "Feb") == 0)
    {
        dt.month = 2;
    }
    else if (_T_stricmp(pszWord, "Mar") == 0)
    {
        dt.month = 3;
    }
    else if (_T_stricmp(pszWord, "Apr") == 0)
    {
        dt.month = 4;
    }
    else if (_T_stricmp(pszWord, "May") == 0)
    {
        dt.month = 5;
    }
    else if (_T_stricmp(pszWord, "Jun") == 0)
    {
        dt.month = 6;
    }
    else if (_T_stricmp(pszWord, "Jul") == 0)
    {
        dt.month = 7;
    }
    else if (_T_stricmp(pszWord, "Aug") == 0)
    {
        dt.month = 8;
    }
    else if (_T_stricmp(pszWord, "Sep") == 0)
    {
        dt.month = 9;
    }
    else if (_T_stricmp(pszWord, "Oct") == 0)
    {
        dt.month = 10;
    }
    else if (_T_stricmp(pszWord, "Nov") == 0)
    {
        dt.month = 11;
    }
    else if (_T_stricmp(pszWord, "Dec") == 0)
    {
        dt.month = 12;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    pszSpace = strstr(pszWord, " ");
    if (!pszSpace)
    {
        return false;
    }

    *pszSpace = 0;
    if (!StringToInteger(pszWord, dt.day))
    {
        return false;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    pszSpace = strstr(pszWord, ":");
    if (!pszSpace)
    {
        return false;
    }

    *pszSpace = 0;
    if (!StringToInteger(pszWord, dt.hour))
    {
        return false;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    pszSpace = strstr(pszWord, ":");
    if (!pszSpace)
    {
        return false;
    }

    *pszSpace = 0;
    if (!StringToInteger(pszWord, dt.minute))
    {
        return false;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    pszSpace = strstr(pszWord, " ");
    if (!pszSpace)
    {
        return false;
    }

    *pszSpace = 0;
    if (!StringToInteger(pszWord, dt.second))
    {
        return false;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    pszSpace = strstr(pszWord, " ");
    if (!pszSpace)
    {
        return false;
    }

    pszWord = pszSpace+1;
    if (!*pszWord)
    {
        return false;
    }

    if (!StringToInteger(pszWord, dt.year))
    {
        return false;
    }

    delete pszBuf;
    return true;
}

/** �ļ��Ƿ����
* 
* \param pszFilePath char*�ַ������ļ�·��
* \param bIsUtf8     pszFilePath�Ƿ�ΪUTF8�����
* \return  ���÷���True�������÷���FALSE
*/ 
Boolean IsFileVaild(const char* pszFilePath, Boolean bIsUtf8)
{
    if (NULL == pszFilePath)
    {
        return FALSE;
    }

    TUChar      szTemp[EOS_FILE_MAX_PATH] = {0}; 

    if (bIsUtf8)
    {
        TUString::StrUtf8ToStrUnicode(szTemp, (Char*)pszFilePath);
    }
    else
    {
        ustrncpy_utf8(szTemp, pszFilePath, EOS_FILE_MAX_PATH-1);
    }

    return IsFileVaild(szTemp);
}

/** �ļ��Ƿ����
* 
* \param pszFilePath TUChar*�ַ������ļ�·��
* \return  ���÷���True�������÷���FALSE
*/ 
Boolean IsFileVaild(const TUChar* pszFilePath)
{
    if (NULL == pszFilePath)
    {
        return FALSE;
    }
    if(*pszFilePath == 0)
        return FALSE;

    Boolean     bVaild;
    Handle      hFile;
    Int32       nLen;

    /*bVaild = EOS_IsFileExist(pszFilePath);
    if (!bVaild)
    {
    return FALSE;
    }*/

    hFile = EOS_Open(pszFilePath, PO_RDONLY|PO_BINARY, PS_IREAD);
    if( hFile>0 )
    {
        nLen = EOS_GetFileSize(hFile);
        if(nLen <= 0)
        {
            // ͼƬ��С��С�������ǷǷ��ļ�
            bVaild = FALSE;
        }
        else
        {
            bVaild = TRUE;
        }

        EOS_Close(hFile);
    }
    else
    {
        bVaild = FALSE;
    }

    return bVaild;
}

/** ͼƬ�ļ��Ƿ����
* 
* \param pszFilePath char*�ַ������ļ�·��
* \param bIsUtf8     pszFilePath�Ƿ�ΪUTF8�����
* \return  ���÷���True�������÷���FALSE
*/ 
Boolean IsImageFileVaild(const char* pszFilePath, Boolean bIsUtf8)
{
    if (NULL == pszFilePath)
    {
        return FALSE;
    }

    TUChar      szTemp[EOS_FILE_MAX_PATH] = {0}; 

    if (bIsUtf8)
    {
        TUString::StrUtf8ToStrUnicode(szTemp, (Char*)pszFilePath);
    }
    else
    {
        ustrncpy_utf8(szTemp, pszFilePath, EOS_FILE_MAX_PATH-1);
    }

    return IsImageFileVaild(szTemp);
}

/** ͼƬ�ļ��Ƿ����
* 
* \param pszFilePath TUChar*�ַ������ļ�·��
* \return  ���÷���True�������÷���FALSE
*/ 

Boolean IsImageFileVaild(const TUChar* pszFilePath)
{
    if (NULL == pszFilePath)
    {
        return FALSE;
    }
    if(*pszFilePath == 0)
        return FALSE;

    Boolean     bVaild;
    Handle      hFile;
    Int32       nLen;

    /*bVaild = EOS_IsFileExist(pszFilePath);
    if (!bVaild)
    {
    return FALSE;
    }*/

    hFile = EOS_Open(pszFilePath, PO_RDONLY|PO_BINARY, PS_IREAD);
    if( hFile>0 )
    {
        nLen = EOS_GetFileSize(hFile);
        if(nLen <= 512)
        {
            // ͼƬ��С��С�������ǷǷ��ļ�
            bVaild = FALSE;

            /*LogoutError("\nFile:");
            LogoutError(pszFilePath); */
            //SS_printf(" Size:%d, Invaild\n", nLen);
        }
        else
        {
            bVaild = TRUE;

            /*LogoutError("\nFile:");
            LogoutError(pszFilePath);*/ 
            //SS_printf(" Size:%d, vaild\n", nLen);
        }

        EOS_Close(hFile);
    }
    else
    {
        bVaild = FALSE;

        /*LogoutError("\nFile:");
        LogoutError(pszFilePath); */
        //SS_printf(", Not Exist\n");
    }

    return bVaild;
}

/** �ַ�������
* 
* \param dst Ŀ�ĵأ�char*
* \param src Դ��char*
* \param n   ��Ҫ���ӵ��ַ�����
* \return    ���Ӻ���ַ���
*/ 
char *ustrncat (char * dst, const char * src, int n)
{
    if (NULL == src || 0 == *src || n == 0)
    {
        return dst;
    }

    char *d = dst;   
    const char *s = src;   

    while (*d != 0)   
        d++;    

    do 
    {   
        if ((*d = *s++) == 0)   
            break;   

        d++;   
    }
    while (--n != 0);

    *d = 0;

    return dst; 
}

/** �ַ�������
* 
* \param dst Ŀ�ĵأ�char*
* \param src Դ��TUChar*
* \param n   ��Ҫ���ӵ��ַ�����
* \return    ���Ӻ���ַ���
*/ char *ustrncat_utf8 (char * dst, const TUChar * src, int n)
{
    if (NULL == src || 0 == *src || n == 0)
    {
        return dst;
    }

    char  *pszStr = dst;
    char  *pszTemp;
    char  *pszTempHead;
    Int32 len;

    len = TUString::StrLen(src);
    len = len << 2;

    pszTemp = new char[len+1];
    if (pszTemp)
    {
        pszTempHead = pszTemp;

        TUString::StrUnicodeToStrUtf8((Char*)pszTemp, src);

        while (*pszStr != 0)   
            pszStr++;    

        do 
        {   
            if ((*pszStr = *pszTemp++) == 0)   
                break;   

            pszStr++;   
        }
        while (--n != 0);

        *pszStr = 0;

        delete [] pszTempHead;
    }

    return( dst );                  /* return dst */
}

/** �ַ�������
* 
* \param dst Ŀ�ĵأ�TUChar*
* \param src Դ��char*
* \param n   ��Ҫ���ӵ��ַ�����
* \return    ���Ӻ���ַ���
*/ 
TUChar *ustrncat_utf8 (TUChar * dst, const char * src, int n)
{
    if (NULL == src || 0 == *src || n == 0)
    {
        return dst;
    }

    TUChar  *pszStr = dst;
    TUChar  *pszTemp;
    TUChar  *pszTempHead;
    Int32   len;

    len = strlen(src);
    pszTemp = new TUChar[len+1];
    if (pszTemp)
    {
        pszTempHead = pszTemp;

        TUString::StrUtf8ToStrUnicode(pszTemp, (Char*)src);

        while (*pszStr != 0)   
            pszStr++;    

        do 
        {   
            if ((*pszStr = *pszTemp++) == 0)   
                break;   

            pszStr++;   
        }
        while (--n != 0);

        *pszStr = 0;

        delete [] pszTempHead;
    }

    return( dst );                  /* return dst */
}

/** �ַ�������
* 
* \param dst Ŀ�ĵأ�TUChar*
* \param src Դ��char*
* \param n   ��Ҫ���ӵ��ַ�����
* \return    ���Ӻ���ַ���
*/ 
TUChar *ustrncat_gb (TUChar * dst, const char * src, int n)
{
    if (NULL == src || 0 == *src || n == 0)
    {
        return dst;
    }

    TUChar  *pszStr = dst;
    TUChar  *pszTemp;
    TUChar  *pszTempHead;
    Int32   len;

    len = strlen(src);
    pszTemp = new TUChar[len+1];
    if (pszTemp)
    {
        pszTempHead = pszTemp;

        TUString::StrGBToUnicode(pszTemp, (Char*)src);

        while (*pszStr != 0)   
            pszStr++;    

        do 
        {   
            if ((*pszStr = *pszTemp++) == 0)   
                break;   

            pszStr++;   
        }
        while (--n != 0);

        *pszStr = 0;

        delete [] pszTempHead;
    }

    return( dst );                  /* return dst */
}

/** �ַ�������
* 
* \param dst Ŀ�ĵأ�char*
* \param src Դ��TUChar*
* \param n   ��Ҫ�������ַ�����
* \return    ��������ַ���
*/ 
char *ustrncpy_utf8 (char * dst, const TUChar * src, int n)
{
    if (NULL == src || 0 == *src)
    {
        return dst;
    }

    char  *pszTemp;
    Int32 len;

    len = TUString::StrLen(src);
    len = len << 2;

    pszTemp = new char[len+1];
    if (pszTemp)
    {
        TUString::StrUnicodeToStrUtf8((Char*)pszTemp, src);
        strncpy(dst, pszTemp, n);

        delete [] pszTemp;
    }    

    return( dst );                  /* return dst */
}

/** �ַ�������
* 
* \param dst Ŀ�ĵأ�TUChar*
* \param src Դ��char*
* \param n   ��Ҫ�������ַ�����
* \return    ��������ַ���
*/ 
TUChar *ustrncpy_utf8 (TUChar * dst, const char * src, int n)
{
    if (NULL == src || 0 == *src)
    {
        return dst;
    }

    TUChar  *pszTemp;
    Int32   len;

    len = strlen(src);
    pszTemp = new TUChar[len+1];
    if (pszTemp)
    {
        TUString::StrUtf8ToStrUnicode(pszTemp, (Char*)src);
        TUString::StrNCopy(dst, pszTemp, n);

        delete [] pszTemp;
    }    

    return( dst );                  /* return dst */
}

/** Log���������Ϣ
* 
* \param pszErrorU ������Ϣ��
* \return ��
*/
void LogoutError(const TUChar* pszErrorU)
{
    char        *pszError;

    if(!pszErrorU || !*pszErrorU)
        return;

    pszError = new char[TUString::StrLen(pszErrorU)*3+1];
    if (NULL == pszError)
    {
        return ;
    }

    TUString::StrUnicodeToStrUtf8((Char*)pszError, pszErrorU);
    SS_printf("%s", pszError);

    if(pszError)
    {
        delete pszError;
        pszError = NULL;
    }
}

/** Log ���������Ϣ
* 
* \param pszError ������Ϣ��
* \return ��
*/
void LogoutError(const char* pszError, ...)
{
    if ( !pszError || !*pszError )
    {
        return;
    }

    va_list ap;
    va_start( ap, pszError );

    SS_vprintf(pszError, ap);

    va_end(ap);
}

string char2hex( char dec )
{
    char dig1 = (dec&0xF0)>>4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
    if (10<= dig1 && dig1<=15) dig1+=65-10; //a,97inascii
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=65-10;

    string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

string urlencode(const string &c)
{
    string escaped="";
    int max = c.length();
    for(int i=0; i<max; i++)
    {
        if ( (48 <= c[i] && c[i] <= 57) ||//0-9
            (65 <= c[i] && c[i] <= 90) ||//abc...xyz
            (97 <= c[i] && c[i] <= 122) || //ABC...XYZ
            (c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\'') //~!*()'
            )
        {
            escaped.append( &c[i], 1);
        }
        else
        {
            escaped.append("%");
            escaped.append( char2hex(c[i]) );//converts char 255 to string "ff"
        }
    }
    return escaped;
}

/** 
*
* \param c 
* \return 
*/
CharType TestCharType( char c )
{
    if (c >=9 && c <=13)
    {
        return ControlChar;
    }

    if (c >= 48 && c <= 57)
    {
        return DigestChar;
    }

    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return LetterChar;
    }

    if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
    {
        return SpecialSign;
    }

    return OtherChar;
}
