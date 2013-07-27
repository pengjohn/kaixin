
/*!
* 
* \file 
* \author HuangYin
* \date	  2010.3.22
* \brief  ͼƬ������
* 
* \ref    CopyRight
*/

#ifndef __TIMGDATA_H__
#define __TIMGDATA_H__

#include "ImageToolKit/IT_ImageLoader.h"

/** ͼƬ�����࣬char*�ַ���ΪUTF8����
* 
* \ingroup UIBuilder
*/
class TImgData
{
public:

    /** ͼƬ������״̬ */
    enum ImgDwnStatus
    {
        /** ��û������ */
        NoData            = -1,

        /** ����Ҫ���� */
        NoNeedDownloading = 0,

        /** �ȴ����� */
        WaitForDownloading = 1,

        /** ��ʼ���� */
        DownloadingStart = 2,

        /** ������� */
        DownloadingFinish = 3,

        /** ���ش��� */
        DownloadingError  =4
    };

    TImgData();

    TImgData(Int32 nW, Int32 nH, Boolean bKeepRatio);

    ~TImgData();

public:

    bool           ReLoadDataImg();

    const TBitmap* GetBitmap() const;

    const char*    GetURL();

    const TUChar*  GetFilePath();

    ImgDwnStatus   GetDwnStatus();

    void           SetImgStartDownloading();

    static ImageToolKit::IT_LoadableImageFormat GetImageFormat(const TUChar* pszExtName);

    bool           _LoadImgByPath(const TUChar* pszPath);

private:

    void           _ClearData();

private:

     /** Image���󣬱�����ļ������ͼƬ */
    ImageToolKit::Image m_objImg;

    /** ��Imageת����TBitmapָ�� */
    TBitmap             *m_pBmp;

    /** ͼƬ������״̬ */
    ImgDwnStatus        m_eDwnStatus;

    /** ͼƬ��URL��ַ */
    char                *m_pszURL;

    /** ͼƬ��·�� */
    TUChar              *m_pszPath;

    /** ��PNGͼƬ�� */
    Boolean             m_bIsPng;

    /** ���ź�ͼƬ�Ŀ�� */
    Int32 m_nWidth;

    /** ���ź�ͼƬ�ĸ߶� */
    Int32 m_nHeight;

    /** ���ź�ͼƬ�Ƿ�Ҫ���ֱ��� */
    Boolean m_bKeepRatio;
};


#endif //__TIMGDATA_H__
