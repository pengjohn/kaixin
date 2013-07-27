/*!
*@FileName: KaiXinApp_AboutForm.h
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
#ifndef   __KAIXINAPI_AboutForm_H__
#define   __KAIXINAPI_AboutForm_H__

#include "KaiXinAPI.h"

class  TAboutForm :  public  TWindow
{
public:
	TAboutForm(TApplication  *  pApp);
	~TAboutForm(void);
	/*Override*/virtual Boolean EventHandler(TApplication * appP, EventType * eventP);
protected:
	virtual void OnWinCreate(void);
	virtual void OnClosed(void);
	virtual Boolean OnCtlSelect(TCtrl *Sender,EventType * eventP);
	virtual Boolean OnMenuSelect(Int32 MenuItemResID);
	virtual Boolean OnPopMenuSelect(Int32 MenuItemResID);
	virtual void OnBeforeMenuOpen(void);
	virtual Boolean OnCtlContextMenu(EventType* eventP);
protected:

private:
	Int32	m_BackBtn;
};


#endif

