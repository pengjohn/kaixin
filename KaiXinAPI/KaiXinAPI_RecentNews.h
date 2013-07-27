/*!
*@FileName: KaiXinApp_RecentNews.h
*@Author: GoZone
*@Date:
*@Log: 	Author 			Date 		Description
*
*@section Copyright
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#ifndef  __KAIXINAPI_RECENTNEWS_H__
#define  __KAIXINAPI_RECENTNEWS_H__

#include "KaiXinAPI.h"
#include "KaiXinAPI_UpdateFriendsNews.h"

typedef struct
{
	char pid[32];
	char title[256];
	char thumbnail[256];
	char large[256];
	char privacy[8];
	char albumid[32];
	char albumtitle[256];
	char picnum[16];
	int pos;
	int ctime;
}RecentNews_imglist;

typedef struct
{
	char id[32];
	char title[256];
	char type[32];
}RecentNews_replist;

typedef struct
{
	char fuid[32];
	char fname[64];
	char flogo[256];
	char ntype[8];
	char ntypename[32];
	char intro[512];
	int ctime;
	char stime[64];
	char thumbnail[256];
	double id;
	char idString[32];//add because vote's id return as string		
	int star;
	char cnum[8];
	char upnum[8];
	int  nSize_imglist;  //Save the array size by code_gen tools. 
	RecentNews_imglist*  imglist;
	int  nSize_replist;  //Save the array size by code_gen tools. 
	RecentNews_replist*  replist;
}RecentNews_news;

typedef struct
{
	char uid[32];
	int ret;
	int n;
	int  nSize_news;  //Save the array size by code_gen tools. 
	RecentNews_news*  news;
}tResponseRecentNews;


extern void* KaiXinAPI_RecentNews_JsonParse(char *text);

class TRecentNewsForm : public TWindow
{
public:
	TRecentNewsForm(TApplication* pApp);
	virtual ~TRecentNewsForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
	Int32 _SetFormTilte(TApplication * pApp);
	Boolean _OnCoolCtrlSelected(TApplication * pApp, Int32 nCtrlID);
	Int32 _SetNewsCoolBarList(TApplication* pApp, KX_NewsShowType ShowType = KX_NewsShowAll);//默认全部显示
	Boolean _IsShow(Int32 nIndex, KX_NewsShowType ShowType);
	void SaveCtrlIDByType(Int32 nType,Int32 Id,Int32 ItemIndex, Int32 CtlType = 0);//CtlType = 0 代表TitleCtrl，CtlType = 1 代表内容contentCtrl
	Int32 _AddMoreLabel(TBarListItem* lpItem, TLabel* pIntroLabel, TFont objFontType,TUChar* pChar,Int32 ItemHeight,Int32 CoolBarDiffTop, TRectangle Rc_Temp);	

private:
	// define private data member here
	tResponseRecentNews* Response;

	//记录动态条数
	Int32	m_nNewsItemCount;

	//用户小图标
	TBitmap* pUserImageBmp;

	//缩略图
	Int32 nThumbnailImage[KX_News_THUMBNAIL_TOTAL_COUNT_MAX];//每条最多显示6个缩略图
	TImage* pThumbnailImage[KX_News_THUMBNAIL_TOTAL_COUNT_MAX];
	TBitmap* pThumbnailBmp[KX_News_THUMBNAIL_TOTAL_COUNT_MAX];
	Int32 nThumImgIndex;
	tPhotoDetail m_photodata;//用于保存被点击图片的相应数据

	Int32 nItemNewsIndex[KX_News_ITEM_COUNT_MAX];//记录每个item对应的Jason news index

	//Fname Ctrls
	Int32 NewsFnameCtrlID[KX_News_ITEM_COUNT_MAX];

	//Record content Ctrls
	Int32 NewsRecordCtrlID[KX_News_ITEM_COUNT_MAX];

	//Diary title Ctrls
	Int32 NewsDiaryTitleCtrlID[KX_News_ITEM_COUNT_MAX];
	//Diary content Ctrls
	Int32 NewsDiaryContCtrlID[KX_News_ITEM_COUNT_MAX];

	//Vote title Ctrls
	Int32 NewsVoteTitleCtrlID[KX_News_ITEM_COUNT_MAX];

	//Status content Ctrls
	Int32 NewsStatusContCtrlID[KX_News_ITEM_COUNT_MAX];

	//Repaste Ctrls
	Int32 NewsRepasteCtrlID[KX_News_ITEM_COUNT_MAX][KX_News_ITEM_REPASTE_COUNT_MAX];

	//Thumbnail Ctrls
	Int32 NewsThumbnailCtrlID[KX_News_ITEM_COUNT_MAX][KX_News_ITEM_THUMBNAIL_COUNT_MAX];	

	Int32 PreSelectRichViewID;

	Int32	m_BackBtn;
};

#endif
