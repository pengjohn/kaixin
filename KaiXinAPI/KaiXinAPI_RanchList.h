/*!
*@FileName: KaiXinApp_RanchList.h
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

#ifndef  __KAIXINAPI_RANCHLIST_H__
#define  __KAIXINAPI_RANCHLIST_H__

#include "KaiXinAPI.h"

typedef struct
{
	char flogo[256];
	int fuid;
	char fname[32];
	char mature[8];
	char mtime[32];
}RanchList_friends;

typedef struct
{
	char uid[32];
	int ret;
	int n;
	int  nSize_friends;  //Save the array size by code_gen tools. 
	RanchList_friends*  friends;
}tResponseRanchList;


extern void* KaiXinAPI_RanchList_JsonParse(char *text);

class TRanchListForm : public TWindow
{
public:
	TRanchListForm(TApplication* pApp);
	virtual ~TRanchListForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);

private:
	tResponseRanchList* Response;

	Int32 nListItems;     //�洢�������
	Int32 nFriendNameId[10000];//�洢��������
	Int32	m_BackBtn;
};

#endif