/*!
*@FileName: KaiXinApp_UserInfoDetail.h
*@Author: pengzhixiong@GoZone
*@Date: 2010-10-7
*@Log: 	Author 			Date 		Description
*
*@section Copyright
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#ifndef  __KAIXINAPI_USERINFODETAIL_H__
#define  __KAIXINAPI_USERINFODETAIL_H__

#include "KaiXinAPI.h"


class TUserInfoDetailForm : public TWindow
{
public:
	TUserInfoDetailForm(TApplication* pApp);
	virtual ~TUserInfoDetailForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:	
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);

	void _SetDataToCtrls(TApplication* pApp);	
	Int32 _SetCoolBarList(TApplication* pApp);

private:	
	tResponseGetUserInfos* Response;	

	//�û�ͼ��
	TBitmap* pPhotoBmp;	
	Int32	m_BackBtn;		
};

#endif