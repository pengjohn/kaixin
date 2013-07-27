//KaiXinAPI_ApplicationList.h
#ifndef  __KAIXINAPI_APPLICATIONLIST_H__
#define  __KAIXINAPI_APPLICATIONLIST_H__

#include "KaiXinAPI.h"

#define KX_APPLIST_ITEM_X_START		(10)
#define KX_APPLIST_ITEM_Y_START		(70)
#define KX_APPLIST_ITEM_WIDTH		(145)
#define KX_APPLIST_ITEM_HEIGHT		(30)
#define KX_APPLIST_ITEM_COL			(2)
#define KX_APPLIST_ITEM_LINE_SPACE	(5)

#if 0
//Application List Object ID 
typedef enum
{
	KX_APPLICATION_FARM = 0,
	KX_APPLICATION_GARDEN,
	KX_APPLICATION_RANCH,
	KX_APPLICATION_PARKING,
	KX_APPLICATION_FISH,
	KX_APPLICATION_RICH,
	KX_APPLICATION_CAFE,
	KX_APPLICATION_LUCKY,
	KX_APPLICATION_SPIDERMAN,
	KX_APPLICATION_FILM,
	KX_APPLICATION_VOTE,
	KX_APPLICATION_PHOTO,
	KX_APPLICATION_DIARY,
	KX_APPLICATION_REPASTE,
	KX_APPLICATION_RECORD,

	/*need to add more type here*/

	KX_APPLICATION_END,
} KX_ApplicationType;

#endif

typedef struct
{
	char name[32];
	char url[128];
}applistItem;

typedef struct
{
	int ret;
	int n;
	applistItem*  applist;
}tResponseApplicationList;

extern void* KaiXinAPI_ApplicationList_JsonParse(char *text);


class TApplicationListForm : public TWindow
{
public:
	TApplicationListForm(TApplication* pApp);
	virtual ~TApplicationListForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
	Boolean _HandleApplicationListCtlClick(TApplication * pApp,Int32 iCtlID);
	Int32 _CreateTabButtons(TApplication* pApp);	

protected:
	Int32 	ItemIndex[128];
	TBarListItem* 	pListItem[64];
	char 	ItemUrl[64][128];
	char 	ItemName[64][32];
	Int32 	ItemCount;

	Int32 m_nNewsBtnID;//动态
	Int32 m_nFriendsBtnID;//好友
	Int32 m_nInfosBtnID;//我的地盘
	Int32 m_nAppsBtnID;//组件
	Int32 m_nMoreBtnID;//更多

	//退出按钮ID
	Int32 m_ExitBtn;
	//刷新按钮ID
	Int32 m_RefreshBtn;
};

#endif
