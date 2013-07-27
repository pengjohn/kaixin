/*!
* 
* \file   TFileDownloadMrg.c
* \author Huxianxiang@GoZone
* \date	  2011-1-28
* \brief  文件下载缓存的管理
* 
* \ref    CopyRight
*/

#include "TFileDownloadMrg.h"

//下载顺序,从队列尾部往前

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Type: TWebImagesMgr函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/** 构造函数
*
* \return 无
*/
TFileDownloadMgr::TFileDownloadMgr()
{
	//保证链表中一定有一个	
	pHeadNode = new  TAList;
	pHeadNode->pNext = NULL;
	pHeadNode->pTAListElement = NULL;

	//init the end node
	pEndNode = pHeadNode;

	nSize = 0;
	bDownLoad = FALSE;
}

/** 析构函数
*
* \return 无
*/
TFileDownloadMgr::~TFileDownloadMgr()
{
	TAList* pTemp = NULL;
	TAList* pDelete = NULL;

	for(pTemp = pHeadNode; pTemp != NULL; )
	{
		pDelete 	= pTemp;
		pTemp	= pDelete->pNext;

		if(pDelete->pTAListElement != NULL)
		{
			delete pDelete->pTAListElement;
			pDelete->pTAListElement = NULL;
		}
		delete pDelete;
	}
}

extern int KaiXinAPI_Download(Int32 in_nAccessType, char* pURL, const TUChar* pszFilePath, Int32 in_nHwndId,Int32 in_nCtrlId, Int32 in_nParam);

//启动下载
int TFileDownloadMgr::DownLoadStart(void)
{

	if(bDownLoad == FALSE)
	{
		if(nSize >0)
		{
			int iRet = eFailed;
			iRet = KaiXinAPI_Download(pEndNode->pTAListElement->accessType, 
				pEndNode->pTAListElement->pURL, 
				pEndNode->pTAListElement->pszFilePath,
				pEndNode->pTAListElement->nHwndId,
				pEndNode->pTAListElement->nCtrlId,
				pEndNode->pTAListElement->nParam
				);

			//如果Download调用失败,则直接移除Node
			if(iRet == eFailed)
			{
				DownLoadComplete(pEndNode->pTAListElement);
			}
			else
				bDownLoad = TRUE;
		}
	}
	return eSucceed;
}

//停止下载
int TFileDownloadMgr::DownLoadStop(void)
{

	bDownLoad = FALSE;

	return eSucceed;
}

//增加下载任务
int TFileDownloadMgr::Add(TAListElement* pElement)
{
	Boolean  bNeedDownload = TRUE;
	//如果已经有重复的下载,则不加到列表中,除了图片下载
	if(pElement->accessType != KX_PhotoDownload)
	{
		TAList* pTemp = NULL;

		for(pTemp = pHeadNode; pTemp != NULL; )
		{
			if(pTemp->pTAListElement != NULL)
			{
				if(pTemp->pTAListElement->accessType == pElement->accessType)
				{
					bNeedDownload = FALSE;
					break;
				}
			}
			pTemp	= pTemp->pNext;
		}
	}

	if(bNeedDownload == TRUE)
	{
		TAList* pAddNote = NULL;
		pAddNote = new TAList;
		//add new node
		pAddNote->pTAListElement = new TAListElement;
		memcpy(pAddNote->pTAListElement, pElement, sizeof(TAListElement));
		pAddNote->pNext          = NULL;
		pEndNode->pNext   = pAddNote;
		//move the end pointer to the new end node.
		pEndNode          = pAddNote;
		++nSize;
	}
	return eSucceed;
}

//插入下载任务
int TFileDownloadMgr::Insert(TAListElement* pElement, int nPosition)
{
	int	nCount  = 0;
	TAList* pFront  = NULL;
	TAList* pBack   = NULL;
	TAList* pInsert = NULL;

	if(NULL == pElement)
		return eFailed;

	//build the insert node!
	pInsert = new TAList;

	pInsert->pTAListElement = new TAListElement;
	memcpy(pInsert->pTAListElement, pElement, sizeof(TAListElement));

	//如果只有一个
	if(0 == nSize)
	{
		pHeadNode->pNext = pInsert;
		pInsert->pNext          = NULL;
		pEndNode         = pInsert;
		++nSize;
		return eSucceed;
	}

	//大于最后一个
	if(nPosition > (nSize - 1))
	{
		pEndNode->pNext = pInsert;
		pInsert->pNext         = NULL;

		//move the end pointer to the new end node.
		pEndNode        = pInsert;

		++nSize;
		return eSucceed;
	}

	//find the position that will insert!
	for(pFront = pHeadNode; nCount < nPosition; nCount++, pFront = pFront->pNext);

	pBack          = pFront->pNext;

	//insert the node
	pFront->pNext  = pInsert;
	pInsert->pNext = pBack;
	++nSize;


	return eSucceed;
}


//eSucceed -- 
//eFailed -- 链表中没有找到对应的节点, 可能是已经被Cancel了
int TFileDownloadMgr::DownLoadComplete(TAListElement*  in_pElement)
{
	TAList* pFront  = NULL;
	TAList* pRemove = NULL;
	int iRect = eFailed;

	//if(nSize <1)
	//	return eFailed;

	pFront = pHeadNode;
	while(pFront->pNext != NULL)
	{
		if(pFront->pNext->pTAListElement == NULL)
			break;

		if( (pFront->pNext->pTAListElement->accessType == in_pElement->accessType) &&
			(pFront->pNext->pTAListElement->nHwndId == in_pElement->nHwndId) &&
			(pFront->pNext->pTAListElement->nCtrlId == in_pElement->nCtrlId) &&
			(pFront->pNext->pTAListElement->nParam == in_pElement->nParam) )
		{
			pRemove = pFront->pNext;
			pFront->pNext = pFront->pNext->pNext;

			if(pEndNode == pRemove)
				pEndNode =  pFront;

			if(pRemove->pTAListElement != NULL)
			{
				delete pRemove->pTAListElement;
				pRemove->pTAListElement = NULL;
			}
			delete pRemove;
			--nSize;

			iRect = eSucceed;
			break;
		}
		pFront = pFront->pNext;
	};


	if(bDownLoad == TRUE)
	{
		if(nSize >0)
		{
			KaiXinAPI_Download(pEndNode->pTAListElement->accessType, 
				pEndNode->pTAListElement->pURL, 
				pEndNode->pTAListElement->pszFilePath,
				pEndNode->pTAListElement->nHwndId,
				pEndNode->pTAListElement->nCtrlId,
				pEndNode->pTAListElement->nParam
				);
		}
		else
		{
			bDownLoad = FALSE;
		}
	}

	return iRect;
}

//取消accessType相同的下载任务
int TFileDownloadMgr::CancelByAccessType(Kx_AccessType  accessType)
{
	TAList* pFront  = NULL;
	TAList* pRemove = NULL;

	if(nSize <1)
		return eFailed;

	pFront = pHeadNode;
	while(pFront->pNext != NULL)
	{
		if(pFront->pNext->pTAListElement == NULL)
			break;

		if(pFront->pNext->pTAListElement->accessType == accessType)
		{
			pRemove = pFront->pNext;
			pFront->pNext = pFront->pNext->pNext;

			if(pEndNode == pRemove)
				pEndNode =  pFront;

			if(pRemove->pTAListElement != NULL)
			{
				delete pRemove->pTAListElement;
				pRemove->pTAListElement = NULL;
			}
			delete pRemove;
			--nSize;

			continue;
		}
		pFront = pFront->pNext;
	};

	return eSucceed;
}

//取消nHwndId相同的下载任务
int TFileDownloadMgr::CancelByHwndId(Int32 nHwndId)
{
	TAList* pFront  = NULL;
	TAList* pRemove = NULL;

	if(nSize <1)
		return eFailed;

	pFront = pHeadNode;
	while(pFront->pNext != NULL)
	{
		if(pFront->pNext->pTAListElement == NULL)
			break;

		if(pFront->pNext->pTAListElement->nHwndId == nHwndId)
		{
			pRemove = pFront->pNext;
			pFront->pNext = pFront->pNext->pNext;

			if(pEndNode == pRemove)
				pEndNode =  pFront;

			if(pRemove->pTAListElement != NULL)
			{
				delete pRemove->pTAListElement;
				pRemove->pTAListElement = NULL;
			}
			delete pRemove;
			--nSize;

			continue;
		}
		pFront = pFront->pNext;
	};

	return eSucceed;
}

//取消所有下载任务
int TFileDownloadMgr::CancelAll(void)
{
	TAList* pRemove = NULL;
	TAList* pTemp   = NULL;
	if(nSize <1)
		return eFailed;

	for(pTemp = pHeadNode->pNext; pTemp != NULL; )
	{
		pRemove = pTemp;
		pTemp   = pRemove->pNext;

		if(pRemove->pTAListElement != NULL)
		{
			delete pRemove->pTAListElement;
			pRemove->pTAListElement = NULL;
		}
		delete pRemove;
	}

	pHeadNode->pNext = NULL;
	pEndNode         = pHeadNode;
	nSize            = 0;
	return eSucceed;
}

// 1 --> nSize
TAListElement* TFileDownloadMgr::GetElement(int nPosition)
{
	if(nSize < 1)
		return NULL;

	if( (nPosition < 1) || (nPosition > nSize) )
		return NULL;
	
	TAList* pTemp  = pHeadNode;
	for(int i=1; i<=nPosition; i++ )
	{
		if(pTemp == NULL)
		{
			return NULL;
		}	
		pTemp = pTemp->pNext;
	}

	return pTemp->pTAListElement;
}

int TFileDownloadMgr::GetSize()
{
	return nSize;
}
	