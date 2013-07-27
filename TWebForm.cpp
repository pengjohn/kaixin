
/*!
* 
* \file   TWebForm.cpp
* \author yusz
* \date	  2010.6.21
* \brief  ����Ƕbrowser�İ�װ���������Ӧ��ʹ��
* 
* \ref    CopyRight
*/
#include "KaiXinAPICommon.h"
#include "App_KaiXinApp.h"
#include  "TWebForm.h"
#include "TCOM_TBrowser_WebClient_IIDs.h"


/** ���캯��
*
* \param pApp   TApplicationָ��
* \return ��
*/
TWebForm::TWebForm(TApplication * pApp, const TUChar* in_pszTitle, const char* in_pszURL):TWindow(pApp)
{
	m_pWebPanel = NULL;
	m_pWebPanelTComObj = NULL;	
	pszURL = NULL;
	pszTitle = NULL;

	//Url
	if(in_pszURL != NULL)
	{
		Int32 nLen = 0;
		nLen = strlen(in_pszURL) + 1;
		pszURL = new char[nLen];
		MemSet(pszURL, 0, nLen);
		strncpy(pszURL, in_pszURL, nLen);
	}
	//Ttile
	if(in_pszTitle != NULL)
	{
		Int32 nLen = 0;
		nLen = TUString::StrLen(in_pszTitle) + 1;
		pszTitle = new TUChar[nLen];
		MemSet(pszTitle, 0, nLen);
		TUString::StrNCopy(pszTitle, in_pszTitle, nLen);
	}

	Create(APP_KA_ID_WebForm);
}

/** ��������
*
* \return ��
*/
TWebForm::~TWebForm(void)
{
	if(pszURL != NULL)
	{
		delete pszURL;
		pszURL = NULL;
	}

	if(pszTitle != NULL)
	{
		delete pszTitle;
		pszTitle = NULL;
	}

	if(m_pWebPanelTComObj)
	{
		m_pWebPanelTComObj->resetGlobalDefaultWebViewEventHandler();
		m_pWebPanelTComObj->Release();
		m_pWebPanelTComObj = NULL;
	}

	if (m_pWebPanel)
	{
		//m_pWebPanel->stopLoad();
		m_pWebPanel->close();
		m_pWebPanel = NULL;
	}
}

/** ����ҳ����ʾ����
*
* \param pszTitle ����
* \param pURL     ����
* \param pDes     ����
* \return ��
*/
void TWebForm::SetText(const TUChar* pszTitle, const char* pURL, const char* pDes)
{
	TUChar    *pText;
#if 0
	TLabel* pTitle;

	pTitle = static_cast<TLabel*>(GetControlPtr(APP_RS_ID_formWeb_Label1047));
	if (pTitle && pszTitle)
	{
		pText = new TUChar[strlen(pszTitle)+1];
		TUString::StrUtf8ToStrUnicode(pText, (Char*)pszTitle);
		pTitle->SetCaption(pText, FALSE);

		delete [] pText;
		pText = NULL;
	}
#endif
	////���������
	//TCOM_WebBrowser_DataType_Obj*   dt = TCOM_WebBrowser_DataType_Obj::create();
	//if(dt != NULL) 
	//{
	//    //const TUChar *pszAddress = GetControlCaption(APP_ST_ID_FormSyetemStyleTest_Field1039);
	//    pText = new TUChar[strlen(pURL)+1];
	//    TUString::StrUtf8ToStrUnicode(pText, (Char*)pURL);
	//    dt->LoadUrl(pText);
	//    delete [] pText;
	//    pText = NULL;
	//    dt->Release();
	//}


	//�趨��ҳ��ʾ����ʼλ�ã����Ͻ����꣩
	TRectangle WebRet(0,0,0,0);
	WebRet.SetRect(0, TITLEBAR_H, SCR_W, SCR_H - STATUSBAR_H - TITLEBAR_H);

	m_pWebPanel = TBrowser::TWebPanel::create(this, WebRet, NULL);

	m_pWebPanelTComObj = m_pWebPanel->getParentClient();
	UInt32 ulAccountID = (UInt32)(static_cast<TApp_KaiXinApp*>(GetApplication()))->GetConnectID();
	m_pWebPanelTComObj->setNetAccountID(ulAccountID);
	m_pWebPanelTComObj->setAutoConnect(FALSE);
	m_pWebPanelTComObj->AddRef();

	//����һ��URL ���� ��������ָ������������ʾ
	pText = new TUChar[strlen(pURL)+1];
	if (pText)
	{
		m_pWebPanel->setAutoZoomSupport(TRUE);
		
		MemSet(pText, 0, (strlen(pURL)+1) * sizeof(TUChar));
		TUString::StrUtf8ToStrUnicode(pText, (Char*)pURL);
		m_pWebPanel->loadUrl(pText);

		delete [] pText;
		pText = NULL;
	}

}

/** �¼�������
*
* \param pApp   TApplicationָ��
* \param pEvent EventTypeָ��
* \return �Ƿ��Ѵ���
*/
Boolean TWebForm::EventHandler(TApplication * pApp, EventType * pEvent)
{
	Boolean     bHandled = FALSE;

	switch(pEvent->eType)
	{
	case EVENT_WinInit:
		{
			bHandled = _OnWinInitEvent(pApp, pEvent);
		}
		break;

	case EVENT_WinPaint:
		{
			DrawWindow();
			bHandled = TRUE;
			break;
		}

	case EVENT_CtrlSelect:
		{
			bHandled = _OnCtlSelectEvent( pApp, pEvent );
		}
		break;

	case EVENT_WinClose:
		{
			// Stop the application since the main form has been closed

		}
		break;
	case EVENT_KeyCommand: 
		{ 
			// ץȡ������¼� 
			if (pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_UP  
				|| pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_LONG) 
			{ 
				// ģ���˳���ťѡ����Ϣ 
				HitControl(m_BackBtn); 
				bHandled = TRUE; 
			}
		}
		break;
	case EVENT_WinEraseClient:
		{
			TDC 	   dc(this);
			WinEraseClientEventType *pEraseEvent = reinterpret_cast< WinEraseClientEventType* >( pEvent );
			TRectangle rc(pEraseEvent->rc);
			TRectangle rcBack(5, 142, 310, 314);
			this->GetBounds(&rcBack);

			// ����
			dc.EraseRectangle(&rc, 0);

			dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_title_bg), 0, 0, SCR_W,GUI_API_STYLE_ALIGNMENT_LEFT);

			//dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_bottom_bg), 0, rcBack.Bottom()-68, 
			//320, GUI_API_STYLE_ALIGNMENT_LEFT|GUI_API_STYLE_ALIGNMENT_TOP); 


			pEraseEvent->result = 1;				
			bHandled = TRUE;
		}
		break;		
	}
	if (bHandled == FALSE)
	{
		return TWindow::EventHandler(pApp,pEvent);
	}
	return bHandled;
}

/** ���ڳ�ʼ��
*
* \param pApp   TApplicationָ��
* \param pEvent EventTypeָ��
* \return �Ƿ��Ѵ���
*/
Boolean TWebForm::_OnWinInitEvent(TApplication * pApp, EventType * pEvent)
{

	// ���ñ�������
	SetText(pszTitle, pszURL, "sina");
	m_BackBtn = SetAppBackButton(this);
	SetAppTilte(this, 0, pszTitle);
	return TRUE;
}

Boolean TWebForm::_OnCtlSelectEvent(TApplication * pApp, EventType * pEvent)
{
	Boolean     bHandled = FALSE;

	if(m_BackBtn == pEvent->sParam1)
	{
		bHandled = TRUE; 
		this->CloseWindow();

		return bHandled;
	}

	return bHandled;
}
