/*!
* 
* \file   TDownload.h
* \author Yusz
* \date	  2010.7.8
* \brief  
* 
* \ref    CopyRight
*/
#pragma once

#include "TG3.h"
#include "curl.h"

/** ����״̬��
* 
*/
typedef enum
{
	DLC_IDLE,                   //����
	DLC_HEADER,                 //��ȡ��Header
	DLC_NONEEDUPFATE,           //û�и���
	DLC_DOWNLOADING,            //������������
	DLC_ABORT,                  //��ֹ
	DLC_FINISHED                //�������
}DownloadCode;

typedef enum
{
	ERR_NONE = 0,               //û�д���
	ERR_INVALID_URL,            //URL��Ч
	ERR_INVALID_FILEPATH,       //�ļ�·����Ч
	ERR_INVALID_GTID_HANDLE,    //GTID�����Ч
	ERR_FAILED_NEW_DLP,         //new����ʧ��
	ERR_FAILED_CREATE_THREAD    //�����̳߳���
}DownloadError;

/** �����̷߳�������Ϣ
* 
*/
typedef enum
{
	MSG_DL_THREAD_NOTIFY = EVENT_FirstUser + 100,
	MSG_DL_THREAD_NEWTASK,
	MSG_DL_THREAD_PROCESS,
	MSG_DL_THREAD_START,
	MSG_DL_THREAD_END,
}DownloadThreadMsg;


/** ���������̵߳Ĳ���
*/
class IDownLoad
{
public:
	IDownLoad(void);
	~IDownLoad(void);

	DownloadError DownloadStart(const char* pszUrl, const TUChar* pszFilepath, Int32 in_nAccessType, Int32 nHwndId, Int32 nCtrlId, Int32 in_nParam, Int32 nTimeout, Boolean bNoProNotify, void* pThisHandle, Boolean bPost);
	DownloadError DownloadAbort(Int32   in_nAccessType);

private:
	/** ֻ�е�Ҫ�ͷ�szFileName��szUrl��szProxyUrlָ����ڴ�ʱ���� */
	void clearMem();	
	static Int32 DownLoadProductProc(const TUChar * pAppID, UInt32 uCmd, void * puCmd);
	static Int32 PostProductProc(const TUChar * pAppID, UInt32 uCmd, void * puCmd);	

	static int ProgressNotifyFunc(void *clientp, double dltotal,double dlnow,double ultotal,double ulnow);
	static size_t WriteProductData (void *ptr, size_t size, size_t nmemb, void *data);
	static size_t GetHeadForLength (void *ptr, size_t size, size_t nmemb, void *stream);
	Int32 NotifyToMain(DownloadCode eDLCode);

	//Curl
	CURL                *gCurl;
	/** �߳����� ,����ID�Ĺؼ��ֶ�*/
	Int32           nAccessType;

	/** ������GTID */
	SS_GTID			gtidMain;

	/** ������Ĵ���ID */
	Int32			nHwndId;

	/** ������Ŀؼ�ID */
	Int32			nCtrlId;

	//����
	Int32 			nParam;

	/** �Ƿ������Ϣ */
	Boolean			bCheckMsg;

	/** ���������ļ����� */
	TUChar*			szFileName;

	/** ��Ҫ���ص�URL */
	char*			szUrl;

	/** �Ƿ���Ҫʹ�ô��� */
	Boolean			bUseProxy;

	/** ����URL */
	char*			szProxyUrl;

	/** ����˿� */
	Int32			nProxyPort;

	/** �����ļ���������ʱ�� */
	//DateTimeType    dtFileModified; 

	/** �Ƿ���Ҫ������ */
	Boolean			bCheckModifity;

	/** ��ʱʱ������ */
	Int32           nTimeout;

	//�Ƿ���ҪProgress��Ϣ
	Boolean bNoProNotify;

	//����Ӧ��new����ָ��,���ڷ�����Ӧ��delete
	void* pThisHandle;
};

/** ֪ͨ��������ȵ���Ϣ�ṹ */
struct NotifyMsgDataType
{
	Int32           	nAccessType;	//��������,��ӦKx_AccessType
	Int32		nHwndId;		//������Ĵ���ID
	Int32		nCtrlId;			// ������Ŀؼ�ID
	Int32		nParam;			//����
	DownloadCode      eDLCode;	//״̬
	Int32		nCurSize;		//�����ش�С
	Int32		nTotalSize;		//�ܵ���Ҫ���صĴ�С
	TUChar         pszFilePath[256];//�����ļ���
	void* 		pThisHandle;	//����Ӧ��new IDownLoad����ָ��,���ڷ�����Ӧ��delete
};

/** �ص������Ĳ��� */
struct WriteFunArg
{
	/** �����߳�����ֵ */
	Int32           nAccessType;

	/** ������GTID */
	SS_GTID			objGtidMain;

	/** ������Ĵ���ID */
	Int32			nHwndId;

	/** ������Ŀؼ�ID */
	Int32			nCtrlId;

	/** �Ѿ����صĴ�С */
	Int32			nCurrentSize;

	/** ��Ҫ���صĴ�С */
	Int32			nTotalSize;

	/** ��Ҫд����ļ���� */
	Handle          hFile;

	/** �Ѵ��ڵ��ļ���С */
	//Int32          nLocalFileSize;
};

