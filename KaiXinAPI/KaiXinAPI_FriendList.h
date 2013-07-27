//KaiXinAPI_FriendList.h
#ifndef  __KaiXinAPI_FriendList_H__
#define  __KaiXinAPI_FriendList_H__

#include "KaiXinAPI.h"

typedef struct
{
	char py[32];
}FriendList_py;

typedef struct
{
	char fpy[8];
}FriendList_fpy;

typedef struct
{
	char fuid[32];
	char fname[32*2];
	int gender;
	char state[1024];
	int online;
	int  py_nSize;  //Save the array size by code_gen tools. 
	FriendList_py*  py;
	int  fpy_nSize;  //Save the array size by code_gen tools. 
	FriendList_fpy*  fpy;
	char flogo[128];
}FriendList_friends;


typedef struct
{
	char fuid[32];
	char fname[32*2];
	int gender;
	int online;
	int  py_nSize;  //Save the array size by code_gen tools. 
	FriendList_py*  py;
	int  fpy_nSize;  //Save the array size by code_gen tools. 
	FriendList_fpy*  fpy;
	int vtime;
	char strvtime[32];
	char flogo[128];
}FriendList_visitors;


typedef struct
{
	char fuid[32];
	char fname[32*2];
	int gender;
	int online;	
	char state[1024];
	int  py_nSize;  //Save the array size by code_gen tools. 
	FriendList_py*  py;
	int  fpy_nSize;  //Save the array size by code_gen tools. 
	FriendList_fpy*  fpy;
	char flogo[128];
}FriendList_onlines;

typedef struct
{
	char fuid[32];
	char fname[32*2];
	int gender;
	char state[128];
	int  py_nSize;  //Save the array size by code_gen tools. 
	FriendList_py*  py;
	int  fpy_nSize;  //Save the array size by code_gen tools. 
	FriendList_fpy*  fpy;
	char flogo[128];
}FriendList_starfriends;

typedef struct
{
	char fuid[32];
	char flogo[128];
	char fname[32*2];
	char birthday[32];
	char birthdisplay[32];
	int send;
}FriendList_birthlist;

typedef struct
{
	int aid;
	int num;
}FriendList_applist;

typedef struct
{
	int ret;
	char uid[32];
	int n;
	int total;
	int onlinetotal;
	int vtotal;
	int stotal;
	int  friends_nSize;  //Save the array size by code_gen tools. 
	FriendList_friends*  friends;
	int  visitors_nSize;  //Save the array size by code_gen tools. 
	FriendList_visitors*  visitors;
	int  onlines_nSize;  //Save the array size by code_gen tools. 
	FriendList_onlines*  onlines;
	int  starfriends_nSize;  //Save the array size by code_gen tools. 
	FriendList_starfriends*  starfriends;
	int  birthlist_nSize;  //Save the array size by code_gen tools. 
	FriendList_birthlist*  birthlist;
	int  applist_nSize;  //Save the array size by code_gen tools. 
	FriendList_applist*  applist;
}tResponseFriendList;


extern void* KaiXinAPI_FriendList_JsonParse(char *text);


enum
{
	FRIENDLIST_TYPE_START = 0,
	FRIENDLIST_TYPE_FRIEND = FRIENDLIST_TYPE_START,	//����
	FRIENDLIST_TYPE_VISITOR,		//������
	FRIENDLIST_TYPE_STAR,			//����
	FRIENDLIST_TYPE_ONLINE,		//����
	FRIENDLIST_TYPE_BIRTHDAY,		//����
	FRIENDLIST_TYPE_END = FRIENDLIST_TYPE_BIRTHDAY,
};

//��ʾ���������
#define FRIENDLIST_MAXITEM		FRIEND_MAX_NUM
//��������������ַ���
#define FRIENDLIST_MAXINPUT	16

typedef struct
{
	char fuidList[32];			//fuid
	TBitmap* pBmp;			//Bmp
	Int32 ActionButtonID;		//ButtonID
	Int32 ResultID;			//ResultID
	Boolean  bBirthGiftSent;	//Sent birthay gift, only for birthday list
}tFriendList_ItemData;

class TFriendListForm : public TWindow
{
public:
	TFriendListForm(TApplication* pApp, int inFriendListType = FRIENDLIST_TYPE_FRIEND);
	virtual ~TFriendListForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:
	tFriendList_ItemData gItemData[FRIENDLIST_MAXITEM];
	Int32  	nActionIndex;
	char sFpyInput[FRIENDLIST_MAXINPUT];
	int 	iListType;

	//use to selection buttons ID
	Int32 m_nAllBtnID;//ȫ��
	Int32 m_nOnlineBtnID;//����
	Int32 m_nVisitorBtnID;//�ÿ�
	Int32 m_nStarBtnID;//����
	Int32 m_nBirthdayBtnID;//����

	//use to save buttons ID
	Int32 m_nNewsBtnID;//��̬
	Int32 m_nFriendsBtnID;//����
	Int32 m_nInfosBtnID;//�ҵĵ���
	Int32 m_nAppsBtnID;//���
	Int32 m_nMoreBtnID;//����

	//�˳���ťID
	Int32 m_ExitBtn;
	//ˢ�°�ťID
	Int32 m_RefreshBtn;	
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnFldChangedEvent(TApplication * pApp, EventType* pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSetFocusEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlKillFocusEvent(TApplication * pApp, EventType * pEvent);		
	int SetFriendListType(TApplication * pApp, int eFriendListType, Boolean bClearInput);

	Int32 _CreateSelectionButtons(TApplication* pApp);
	Int32 _ChangeBtnImage(int eFriendListType);
	int SetTilteLabel(TApplication * pApp, TUChar* pszTitleLabel, Int32 nResId);
	Int32 m_TitleButtonCtlID;	
	int SetTilteButton(TApplication * pApp);
	Int32 _CreateTabButtons(TApplication* pApp);
};

#endif
