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

/** 下载状态码
* 
*/
typedef enum
{
	DLC_IDLE,                   //空闲
	DLC_HEADER,                 //获取到Header
	DLC_NONEEDUPFATE,           //没有更新
	DLC_DOWNLOADING,            //正在下载数据
	DLC_ABORT,                  //中止
	DLC_FINISHED                //下载完成
}DownloadCode;

typedef enum
{
	ERR_NONE = 0,               //没有错误
	ERR_INVALID_URL,            //URL无效
	ERR_INVALID_FILEPATH,       //文件路径无效
	ERR_INVALID_GTID_HANDLE,    //GTID句柄无效
	ERR_FAILED_NEW_DLP,         //new操作失败
	ERR_FAILED_CREATE_THREAD    //创建线程出错
}DownloadError;

/** 下载线程发出的消息
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


/** 启动下载线程的参数
*/
class IDownLoad
{
public:
	IDownLoad(void);
	~IDownLoad(void);

	DownloadError DownloadStart(const char* pszUrl, const TUChar* pszFilepath, Int32 in_nAccessType, Int32 nHwndId, Int32 nCtrlId, Int32 in_nParam, Int32 nTimeout, Boolean bNoProNotify, void* pThisHandle, Boolean bPost);
	DownloadError DownloadAbort(Int32   in_nAccessType);

private:
	/** 只有当要释放szFileName、szUrl、szProxyUrl指向的内存时调用 */
	void clearMem();	
	static Int32 DownLoadProductProc(const TUChar * pAppID, UInt32 uCmd, void * puCmd);
	static Int32 PostProductProc(const TUChar * pAppID, UInt32 uCmd, void * puCmd);	

	static int ProgressNotifyFunc(void *clientp, double dltotal,double dlnow,double ultotal,double ulnow);
	static size_t WriteProductData (void *ptr, size_t size, size_t nmemb, void *data);
	static size_t GetHeadForLength (void *ptr, size_t size, size_t nmemb, void *stream);
	Int32 NotifyToMain(DownloadCode eDLCode);

	//Curl
	CURL                *gCurl;
	/** 线程索引 ,下载ID的关键字段*/
	Int32           nAccessType;

	/** 主程序GTID */
	SS_GTID			gtidMain;

	/** 主程序的窗口ID */
	Int32			nHwndId;

	/** 主程序的控件ID */
	Int32			nCtrlId;

	//参数
	Int32 			nParam;

	/** 是否接收消息 */
	Boolean			bCheckMsg;

	/** 保存结果的文件名字 */
	TUChar*			szFileName;

	/** 需要下载的URL */
	char*			szUrl;

	/** 是否需要使用代理 */
	Boolean			bUseProxy;

	/** 代理URL */
	char*			szProxyUrl;

	/** 代理端口 */
	Int32			nProxyPort;

	/** 缓存文件的最后更新时间 */
	//DateTimeType    dtFileModified; 

	/** 是否需要检查更新 */
	Boolean			bCheckModifity;

	/** 超时时间设置 */
	Int32           nTimeout;

	//是否需要Progress消息
	Boolean bNoProNotify;

	//保存应用new的类指针,用于返给给应用delete
	void* pThisHandle;
};

/** 通知主程序进度的消息结构 */
struct NotifyMsgDataType
{
	Int32           	nAccessType;	//下载类型,对应Kx_AccessType
	Int32		nHwndId;		//主程序的窗口ID
	Int32		nCtrlId;			// 主程序的控件ID
	Int32		nParam;			//参数
	DownloadCode      eDLCode;	//状态
	Int32		nCurSize;		//已下载大小
	Int32		nTotalSize;		//总的需要下载的大小
	TUChar         pszFilePath[256];//保存文件名
	void* 		pThisHandle;	//保存应用new IDownLoad的类指针,用于返给给应用delete
};

/** 回调函数的参数 */
struct WriteFunArg
{
	/** 下载线程索引值 */
	Int32           nAccessType;

	/** 主程序GTID */
	SS_GTID			objGtidMain;

	/** 主程序的窗口ID */
	Int32			nHwndId;

	/** 主程序的控件ID */
	Int32			nCtrlId;

	/** 已经下载的大小 */
	Int32			nCurrentSize;

	/** 需要下载的大小 */
	Int32			nTotalSize;

	/** 需要写入的文件句柄 */
	Handle          hFile;

	/** 已存在的文件大小 */
	//Int32          nLocalFileSize;
};

