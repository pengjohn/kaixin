

#ifndef __TFILEDOWNLOADMRG_H__
#define __TFILEDOWNLOADMRG_H__
#include "TG3.h"
#include "KaiXinAPI.h"


typedef struct TAListElement TAListElement;
struct TAListElement
{
	Int32  accessType;
	Int32 nHwndId;
	Int32 nCtrlId;
	Int32 nParam;
	char pURL[4096];//TODO, 需要扩展大小
	TUChar pszFilePath[EOS_FILE_MAX_PATH]; 
};

typedef struct TAList TAList;
struct TAList{
	TAListElement* pTAListElement; 
	TAList*        pNext;       
};


class TFileDownloadMgr
{
public:

	TFileDownloadMgr();

	~TFileDownloadMgr();

public:
	int Add(TAListElement* pElement);
	int Insert(TAListElement* pElement, int nPosition);	//TODO::
	int CancelByAccessType(Kx_AccessType  accessType);			//TODO::	
	int CancelByHwndId(Int32 nHwndId);
	int CancelAll(void);							//TODO::
	int DownLoadStart(void);
	int DownLoadComplete(TAListElement*  pElement);
	int DownLoadStop(void);						//TODO::
	TAListElement* GetElement(int nPosition);
	int GetSize();
private:
	TAList* pHeadNode;    //head node pointer
	TAList* pEndNode;     	//head End pointer
	int nSize;			//
	bool bDownLoad;		//是否正在下载
};


#endif //__TWEBIMAGESMGR_H__
