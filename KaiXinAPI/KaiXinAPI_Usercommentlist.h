//KaiXinApp_InitialLogin.h
#ifndef  __KAIXINAPP_USERCOMMENTLIST_H__
#define  __KAIXINAPP_USERCOMMENTLIST_H__

#include "KaiXinAPI.h"


//显示的最大条数
#define COMMENTLSIT_MAXITEM		200
#define CreateCtl_MAX		20

typedef struct

{

	char flogo[128];
	char thread_cid[32];
	char fuid[32];
	int fuidInt;//KX_ReceivedAnObjectComments 得到的fuid是整形
	char fname[32];//TUChar
	char mtype[32];
	int cnum;
	int unread;
	char abscont[60*2];
	int ctime;
	char strctime[32];
	int fuid_last;
	char fname_last[32];
	char abscont_last[60*2];
	int ctime_last;
	char strctime_last[32];

	//new added
	char title[128];
	char thumbnail[256];
	char appid[32];
	char id[32];  //Object ID	
	int mainthread;

}UserCommentList_comments;





typedef struct

{

	int ret;
	char uid[32];
	int n;
	int total; //new added	
	char upcnt[12];
	int selfup;
	char zan_string[64];
	int nCommentCount;
	char oid[16+1];
	char type[16];
	char ouid[16+1];
	UserCommentList_comments*  comments;


}tResponseUserCommentList;

typedef enum
{
	AppUserComment=0,
	AppUserCommentReply,

	AppStateEnd
}AppState;

typedef enum
{
	ReceivedUserCommentList=0,
	SentUserCommentList,

	ReceivedCommentList,
	SentCommentList,

	FriendCommentList,	
	ReceivedAnObjectCommentList,
	AppCommentListTypeEnd
}AppCommentListType;

extern void* KaiXinApp_UserCommentList_JsonParse(char *text);


class TUserCommentListForm : public TWindow
{
public:
	TUserCommentListForm(TApplication* pApp);
	TUserCommentListForm(TApplication* pApp, AppCommentListType appCommentListType);

	virtual ~TUserCommentListForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * event);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	virtual Int32 _OnCommentReplyWinCreateControl(TApplication * pApp);	
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnLstPreDrawEvent(EventType * pEvent);	
	Boolean _OnCoolListViewCustomDrawEvent(TApplication * pApp, EventType * pEvent);
	void SetCoolListNum(AppCommentListType appCommentListType);
	void SetTitleString(AppCommentListType appCommentListType);
	void ShowCommentDetail(AppCommentListType appCommentListType, Int32 nRowIndex);	
private:
	int m_nCommentListNum;
	tResponseUserCommentList* m_pResponse;	
	AppCommentListType m_appCommentListType;

	Int32 m_nAppState;

	//control 
	Int32 m_iaCreateCtlID[CreateCtl_MAX];
	TCtrl *m_obContrl[CreateCtl_MAX];
	Int32 m_nCtlIDCount;

	Int32 m_nReplyBtnID; //记录回复按钮ID	

	//TPanel ID
	Int32 m_iaTPanelID[2];
	Int32 m_iaTImageID[2];

	//Current Select Row
	Int32 m_CurrSelRow;

	TBitmap* pBmp[COMMENTLSIT_MAXITEM];//For user photo	

	Int32	m_BackBtn;
};

#endif
