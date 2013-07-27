
/*!
* 
* \file   TWebForm.h
* \author peng.John
* \date	  2010.11.20
* \brief  描述信息窗口
* 
* \ref    CopyRight
*/

#ifndef  __TDESFORM_H__
#define  __TDESFORM_H__

#include "TG3.h"
#include "TCOM_TBrowser_WebPanel.h"
//#include "TCOM_TBrowser_WebClient_EventHandler.h"

/** 描述信息窗口
*
*/
class TWebForm : public TWindow
{
public:

	TWebForm(TApplication * pApp, const TUChar* in_pszTitle, const char* in_pszURL);

	virtual ~TWebForm(void);

	virtual Boolean EventHandler(TApplication * pApp, EventType * pEvent);

	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtlSelectEvent(TApplication * pApp, EventType * pEvent);
	void SetText(const TUChar* pszTitle, const char* pURL, const char* pDes);

private:
	TUChar* pszTitle;
	char* pszURL;

	Int32	m_BackBtn;	
	TBrowser::TCOM_WebClient_Interface* m_pWebPanelTComObj;
	TBrowser::TWebPanel* m_pWebPanel;
};


#endif // __TDESFORM_H__

