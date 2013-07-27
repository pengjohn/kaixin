//KaiXinAPI_Profile.h
#ifndef  __KaiXinAPI_Profile_H__
#define  __KaiXinAPI_Profile_H__

#include "KaiXinAPI.h"

typedef struct
{
	char pid[32];
	char title[256];
	char thumbnail[256];
	char large[256];
	char privacy[8];
	char albumid[32];
	char albumtitle[256];
	char picnum[32];
	int pos;
	int ctime;
}Profile_imglist;

typedef struct
{
	int id;
	char title[1024];
}Profile_replist;

typedef struct
{
	char fuid[32];
	char fname[64];
	char flogo[256];
	char ntype[8];
	char ntypename[32];
	int ctime;
	char stime[32];
	char intro[128];
	char privacy[8];
	char thumbnail[256];
	int id;
	int star;
	char cnum[8];
	char upnum[8];
	char title[64];
	int commentflag;
	int  nSize_imglist;  //Save the array size by code_gen tools. 
	Profile_imglist*  imglist;
	int  nSize_replist;  //Save the array size by code_gen tools. 
	Profile_replist*  replist;
}Profile_news;

typedef struct
{
	char aid[32];
	char num[32];
}Profile_applist;

typedef struct
{
	int ret;
	char uid[32];
	int indexprivacy;
	char realname[32];
	char note[1024];
	int notetime;
	char stime[64];
	int online;
	int gender;
	int istar;
	int ismyfriend;
	char logo[128];
	char logo90[128];
	int n;
	int total;
	int vcount;
	char starintro[128];
	int  nSize_news;  //Save the array size by code_gen tools. 
	Profile_news*  news;
	int  nSize_applist;  //Save the array size by code_gen tools. 
	Profile_applist*  applist;
}tResponseProfile;

typedef struct
{
	int ret;
	char uid[32];
	char realname[32];
	char note[1024];
	int notetime;
	char stime[64];
}tResponseGetStatus;

extern void* KaiXinAPI_Profile_JsonParse(char *text);
extern void* KaiXinAPI_GetStatus_JsonParse(char *text);

//GetFriendCount
typedef struct
{
	int ret;
	int uid;
	int n;
	int total;
}tResponseGetFriendCount;

extern void* KaiXinAPI_GetFriendCount_JsonParse(char *text);

//GetAlbumCount
typedef struct
{
	//int picnum;
	char albumid[32];	
	char picnum[16];
}GetAlbumCount_albums;

typedef struct
{
	int ret;
	int uid;
	int n;
	int  nSize_albums;  //Save the array size by code_gen tools. 
	GetAlbumCount_albums*  albums;
}tResponseGetAlbumCount;
extern void* KaiXinAPI_GetAlbumCount_JsonParse(char *text);

//GetDiaryCount
typedef struct
{
	int ret;
	int uid;
	int n;
	char total[16];	
}tResponseGetDiaryCount;

extern void* KaiXinAPI_GetDiaryCount_JsonParse(char *text);

//GetRepasteCount
typedef struct
{
	int ret;
	int uid;
	int n;
	char total[16];
}tResponseGetRepasteCount;

extern void* KaiXinAPI_GetRepasteCount_JsonParse(char *text);

//GetRecordCount
typedef struct
{
	int ret;
	int uid;
	int n;
	char total[16];
}tResponseGetRecordCount;

extern void* KaiXinAPI_GetRecordCount_JsonParse(char *text);


class TProfileForm : public TWindow
{
public:
	TProfileForm( TApplication *pApp );
	virtual ~TProfileForm(void);
	virtual Boolean EventHandler( TApplication * pApp, EventType * pEvent );

private:
	// define private method here
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtlSelectEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlFocusEvent(TApplication* pApp, EventType* pEvent);	
	void _SetDataToCtrls(TApplication* pApp);	
	Int32 _CreateFunctionButtons(TApplication* pApp);
	Int32 _CreateTabButtons(TApplication* pApp);
	void _DownloadCountJason();		
	void _SetCountToCtrls(TApplication* pApp, Int32 accessType);
private:
	// define private data member here
	tResponseProfile* Response;

	//use to save function buttons ID
	Int32 m_nPhotosBtnID;//��Ƭ
	Int32 m_nDiarysBtnID;//�ռ�
	Int32 m_nRecordsBtnID;//��¼
	Int32 m_nRepastesBtnID;//ת��
	Int32 m_nRecentNewsBtnID;//���¶�̬
	Int32 m_nMessageCenterBtnID;//��Ϣ����
	Int32 m_nUploadPhotoBtnID;//����Ƭ
	Int32 m_nWriteDiaryBtnID;//д�ռ�
	Int32 m_nWriteRecordBtnID;//д��¼

	//use to save buttons ID
	Int32 m_nNewsBtnID;//��̬
	Int32 m_nFriendsBtnID;//����
	Int32 m_nInfosBtnID;//�ҵĵ���
	Int32 m_nAppsBtnID;//���
	Int32 m_nMoreBtnID;//����


	//�û�Сͼ��
	TBitmap* pUserImageBmp;

	//�˳���ťID
	Int32 m_ExitBtn;

	//ˢ�°�ťID
	Int32 m_RefreshBtn;

	Int32 m_StatusID;
	
};


#endif
