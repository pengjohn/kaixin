
/*!
* 
* \file 
* \author HuangYin
* \date	  2010.3.22
* \brief  ͼƬ������
* 
* \ref    CopyRight
*/

#include "TImgData.h"
#include "TGlobal.h"
#include "ImageToolKit/ImageTools.h"
#include <string>

// Image
using namespace ImageToolKit;

// std
using namespace std;


///////////////////////////////////////////////////////////////////////////
//                                                                       // 
//     TImgData     ��������                                             //
//                                                                       //
///////////////////////////////////////////////////////////////////////////


/** ���캯��
*
* \return ��
*/
TImgData::TImgData()
{
    m_pBmp       = NULL;
    m_eDwnStatus = NoData;
    m_pszURL     = NULL;
    m_pszPath    = NULL;
    m_bIsPng     = FALSE;

    m_nWidth = 0;
    m_nHeight = 0;
    m_bKeepRatio = FALSE;
}

/** ���캯��
*
* \param nW ���ź�ͼƬ�Ŀ��
* \param nH ���ź�ͼƬ�Ŀ��
* \return 
*/
TImgData::TImgData( Int32 nW, Int32 nH, Boolean bKeepRatio)
{
    m_pBmp       = NULL;
    m_eDwnStatus = NoData;
    m_pszURL     = NULL;
    m_pszPath    = NULL;
    m_bIsPng     = FALSE;

    m_nWidth = nW;
    m_nHeight = nH;
    m_bKeepRatio = bKeepRatio;
}

/** ��������
*
* \return ��
*/
TImgData::~TImgData()
{
    _ClearData();
}

/** ������Ʒ����ͼƬ


/** ����������Ʒ����ͼƬ
*
* \return �����Ƿ�ɹ�
*/
bool TImgData::ReLoadDataImg()
{
    bool   bRes;

    bRes = false;

    //// ������������
    //m_objImg.clearImage();
    //if (NULL != m_pBmp)
    //{
    //    if(m_bIsPng)
    //    {
    //        m_pBmp->Destroy();
    //        m_bIsPng = FALSE;
    //    }
    //    m_pBmp = NULL;
    //}

    // ͼƬ�ȴ����ز��ұ�����URL��ַ
    if (TImgData::DownloadingStart == m_eDwnStatus && m_pszPath != NULL)
    {
        bRes = _LoadImgByPath(m_pszPath);

        if (bRes)
        {
            delete [] m_pszURL;
            m_pszURL = NULL;

            delete [] m_pszPath;
            m_pszPath = NULL;

            m_eDwnStatus = TImgData::DownloadingFinish;  
        }
        else
        {
            m_eDwnStatus = TImgData::DownloadingError;  
        }
    }

    return bRes;
}

/** ��ȡͼƬ�� TBitmap ָ��
*
* \return ͼƬ�� TBitmap ָ��
*/
const TBitmap* TImgData::GetBitmap() const
{
    return m_pBmp;
}

/** ����ͼƬURL��ַ
*
* \return ͼƬURL��ַ��char�ַ���
*/
const char* TImgData::GetURL()
{
    return m_pszURL;
}

/** ����ͼƬ������״̬
*
* \return ͼƬ������״̬
*/
TImgData::ImgDwnStatus TImgData::GetDwnStatus()
{
    return m_eDwnStatus;
}

/** ����ͼƬ��ʼ����
*
* \return ��
*/
void TImgData::SetImgStartDownloading()
{
    m_eDwnStatus = TImgData::DownloadingStart;  
}

/** ����·������ͼƬ
*
* \param pszPath ͼƬ·����TUChar�ַ���
* \return �����Ƿ�ɹ�
*/
bool TImgData::_LoadImgByPath(const TUChar* pszPath)
{
    bool                   bRes;
    IT_LoadableImageFormat fm;
    ImageLoader            objImgLoader;

    bRes = FALSE;
    fm   = IT_LOAD_FMT_UNKNOWN;

    // ���ԭ����ͼƬ
    m_objImg.clearImage();
    if (NULL != m_pBmp)
    {
        if(m_bIsPng)
        {
            m_pBmp->Destroy();
            m_bIsPng = FALSE;
        }
        m_pBmp = NULL;
    }

    if (pszPath && *pszPath
        && IsImageFileVaild(pszPath)
        && (fm = GetImageFormat(TUString::StrRChr(pszPath, '.'))) != IT_LOAD_FMT_UNKNOWN)
    {   
        if (fm == IT_LOAD_FMT_PNG)
        {
            bRes = IT_LoadPngFileToTBitmap(pszPath, &m_pBmp) >= 0;
            if(bRes)
            {
                m_bIsPng = TRUE;
            }
            else
            {
                m_pBmp = NULL;
                m_bIsPng = FALSE;
            }
        }
        else
        {
            if (m_nHeight > 0 && m_nWidth > 0)
            {
                bRes = objImgLoader.loadImageAndScaleEx(m_objImg, pszPath, m_nWidth, m_nHeight, fm,
                    m_bKeepRatio ? ImageProcessTool::KEEP_RATIO : ImageProcessTool::ACTUAL_SIZE);
            }
            else
            {
                bRes = objImgLoader.loadImage(m_objImg, pszPath, fm);
            }            
        }
    }  

    if (bRes && !m_bIsPng)
    {
        m_pBmp = const_cast<TBitmap *>(m_objImg.GetTBitmap());
    }

    return bRes;
}

/** ��ȡͼ���ļ���չ����Ӧ��IT_LoadableImageFormatö��ֵ
* 
* \param pszExtName TUChar�ַ������ļ���չ��
* \return  IT_LoadableImageFormatö��ֵ
*/ 
IT_LoadableImageFormat TImgData::GetImageFormat(const TUChar* pszExtName)
{
    IT_LoadableImageFormat Format;
    char szExt[20];

    Format = IT_LOAD_FMT_UNKNOWN;
    if (pszExtName == NULL || TUString::StrLen(pszExtName) >= 20 || TUString::StrLen(pszExtName) == 0)
    {
        return Format;
    }

    ustrncpy_utf8(szExt, pszExtName, 20-1);

    if (_T_stricmp(szExt, ".png") == 0)
    {
        Format = IT_LOAD_FMT_PNG;
    } 
    else if (_T_stricmp(szExt, ".gif") == 0)
    {
        Format = IT_LOAD_FMT_GIF;
    }
    else if (_T_stricmp(szExt, ".jpg") == 0)
    {
        Format = IT_LOAD_FMT_JPG;
    }
    else if (_T_stricmp(szExt, ".bmp") == 0)
    {
        Format = IT_LOAD_FMT_BMP;
    }
    else if (_T_stricmp(szExt, ".tif") == 0)
    {
        Format = IT_LOAD_FMT_TIF;
    }
    else if (_T_stricmp(szExt, ".ebp") == 0)
    {
        Format = IT_LOAD_FMT_EBP;
    }
    else if (_T_stricmp(szExt, ".wbmp") == 0)
    {
        Format = IT_LOAD_FMT_WBMP;
    }

    return Format;
}

/** ��������
*
* \return ��
*/
void TImgData::_ClearData()
{
    m_eDwnStatus = NoData;
    m_objImg.clearImage();
    if (NULL != m_pBmp)
    {
        if(m_bIsPng)
        {
            m_pBmp->Destroy();
            m_bIsPng = FALSE;
        }
        m_pBmp = NULL;
    }

    if (m_pszURL)
    {
        delete [] m_pszURL;
        m_pszURL = NULL;
    }

    if (m_pszPath)
    {
        delete [] m_pszPath;
        m_pszPath = NULL;
    }
}

/** ����ͼƬ�ļ�·����ͼƬ�ļ�δ�ɹ�����ǰ��ΪNULL
*
* \return ͼƬ�ļ�·�� TUChar*�ַ���
*/
const TUChar* TImgData::GetFilePath()
{
    return m_pszPath;
}
