//KaiXinAPI_MessageCenter.h
#ifndef  __KAIXINAPP_MESSAGECENTER_H__
#define  __KAIXINAPP_MESSAGECENTER_H__

#include "KaiXinAPI.h"

typedef enum
{
	KX_MESSAGE_SHORT_MESSAGE = 1,		//����Ϣ
	KX_MESSAGE_USER_COMMENT_RECEIVED,	//����
	KX_MESSAGE_COMMENT_RECEIVED,		//����
	KX_MESSAGE_SYSTEM_MESSAGE,			//ϵͳ��Ϣ
	KX_MESSAGE_USER_COMMENT_SENT,		//���Իظ�
	KX_MESSAGE_COMMENT_SENT,			//���ۻظ�
	KX_MESSAGE_END = KX_MESSAGE_COMMENT_SENT,
} KX_MessageType;

typedef struct
{
	int Type;
	int Num;
}MessageCenter_notices;

typedef struct
{
	int ret;
	int uid;
	int nCount;
	int nSize;
	MessageCenter_notices*  pNotices;
}tResponseMessageCenter;

extern void* KaiXinAPI_MessageCenter_JsonParse(char *text);

class TMessageCenterForm : public TWindow
{
public:
	TMessageCenterForm(TApplication* pApp, Boolean bNew = TRUE);
	virtual ~TMessageCenterForm(void);
	virtual Boolean EventHandler(TApplication * pApp, EventType * eventP);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
	Boolean UpdateEvent(TApplication * pApp);

	Int32	m_BackBtn;
};

#endif