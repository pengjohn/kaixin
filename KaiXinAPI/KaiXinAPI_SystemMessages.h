/*!
*@FileName: KaiXinApp_SystemMessages.h
*@Author: huxianxiang@GoZone
*@Date: 2010-9-27
*@Log: 	Author 			Date 		Description
*
*@section Copyright
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#ifndef  __KAIXINAPI_SYSTEMMESSAGES_H__
#define  __KAIXINAPI_SYSTEMMESSAGES_H__

#include "KaiXinAPI.h"

#define KX_SYSMSGS_ITEM_COUNT_MAX		(200)



typedef struct
{
	char fuid[16];
	char flogo[128*3 + 1];
	int appid;
	char real_name[32*3 + 1];
	char msgtype[32*3 + 1];
	char content[256*3 + 1];
	char smid[16*3+1];
	int actions;
	int result;
	int ctime;
	char strctime[32*3 + 1];
	int id;
}SystemMessages_Sysmsgs;

typedef struct
{
	int ret;
	int uid;
	int nNum;
	int More;
	int  nSize_Sysmsgs;  //Save the array size by code_gen tools. 
	SystemMessages_Sysmsgs*  Sysmsgs;
}tResponseSystemMessages;

typedef struct
{
	int ret;
	int uid;
}tResponseFriendRequest;

typedef enum
{
	KX_SYSTEM_MESSAGE_SYSTEM = 1,
	KX_SYSTEM_MESSAGE_BIRTHDAY,
	KX_SYSTEM_MESSAGE_FRIEND,
} KX_SystemMessageType;


extern void* KaiXinAPI_SystemMessages_JsonParse(char *text);

class TSystemMessagesForm : public TWindow
{
public:
	TSystemMessagesForm(TApplication* pApp);
	virtual ~TSystemMessagesForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
protected:

	Int32 	ItemCount;
	TImage* pLogo[KX_SYSMSGS_ITEM_COUNT_MAX];
	Int32 	pLogoID[KX_SYSMSGS_ITEM_COUNT_MAX];
	Int32 	ActionButID1[KX_SYSMSGS_ITEM_COUNT_MAX];
	Int32 	ActionButID2[KX_SYSMSGS_ITEM_COUNT_MAX];
	Int32 	ResultID[KX_SYSMSGS_ITEM_COUNT_MAX];
	char 	pUid[KX_SYSMSGS_ITEM_COUNT_MAX][16];
	char 	Smid[KX_SYSMSGS_ITEM_COUNT_MAX][16];
	Int32 	pType[KX_SYSMSGS_ITEM_COUNT_MAX];
	char 	pActionURL[KX_SYSMSGS_ITEM_COUNT_MAX][128];
	Int32  	nActionIndex;
	TBitmap* pBmp[KX_SYSMSGS_ITEM_COUNT_MAX];//For user photo
	Boolean 	bNeedRefresh;
	Int32	m_BackBtn;
};

#endif