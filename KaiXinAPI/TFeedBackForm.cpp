/*!
* \file	 TFeedBackForm.cpp
* \author	 GoZone
* \date	
* \brief  UI: 用户反馈
*
* \ref    CopyRight
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#include "KaiXinAPICommon.h"

/*   调用例子：
TApplication *pApp = GetApplication();
if(papp)
{
TFeedBackForm *pWin   = new   TFeedBackForm(papp);
if (pWin)
{
papp->SetActiveWindow(pWin);
}
else
{
papp->SendStopEvent();
}
}
*/
TFeedBackForm::TFeedBackForm(TApplication  *  pApp):TWindow(pApp)
{
	Create(APP_KA_ID_FeedBackForm);
}

TFeedBackForm::~TFeedBackForm()
{

}

/*响应窗口创建事件*/
void  TFeedBackForm::OnWinCreate(void)
{
	TFont objFontType;
	objFontType.Create(FONT_CONTENT, FONT_CONTENT);

	m_BackBtn = SetAppBackButton(this);	
	SetAppTilte(this, APP_KA_ID_STRING_UserFeedback);

	//Open Input Method
	ImeOpenIme( IME_MODE_VOLITANT,  IME_CLASS_CHINESE);

	//提交按钮
	TButton* pPublishBtn =new TButton ;
	TRectangle obBtnRec(0,0,0,0);	//初始(left, top, w, h)
	TFont tFont;

	obBtnRec.SetRect(BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H);
	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53_over); 
	if(pPublishBtn->Create(this))
	{
		pPublishBtn->SetBounds(&obBtnRec);	
		m_nPublishBtnID= pPublishBtn->GetId();//Save Publish Button ID.
		pPublishBtn->SetCaption(TResource::LoadConstString(APP_KA_ID_STRING_PostFeedback),TRUE);
		tFont = pPublishBtn->GetFont();
		tFont.Create(FONT_LARGE_BUTTON_CAPTION, FONT_LARGE_BUTTON_CAPTION);
		pPublishBtn->SetFont(tFont);
		pPublishBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pPublishBtn->SetColor(CTL_COLOR_TYPE_FORE,RGB_COLOR_WHITE);
		pPublishBtn->SetColor(CTL_COLOR_TYPE_BACK,RGB_COLOR_WHITE);
		pPublishBtn->SetColor(CTL_COLOR_TYPE_FOCUS_FORE,RGB_COLOR_WHITE);
		pPublishBtn->SetColor(CTL_COLOR_TYPE_FOCUS_BACK,RGB_COLOR_WHITE);
		pPublishBtn->SetImage(pNormalBmp,0);
		pPublishBtn->SetImage(pOverBmp,1);	
		pPublishBtn->Show(TRUE);		
	}

	TRichView *pFeedBakNoteRichView = static_cast<TRichView*>(GetControlPtr(APP_KA_ID_FeedBackForm_FeedBakNoteRichView));
	if(pFeedBakNoteRichView)
	{	
		pFeedBakNoteRichView->SetFont(objFontType);
		pFeedBakNoteRichView->SetMaxVisibleLines(pFeedBakNoteRichView->GetLinesCount(), TRUE);
	}

	TLabel *pFeedBackContentLabel = static_cast<TLabel*>(GetControlPtr(APP_KA_ID_FeedBackForm_FeedBackContentLabel));
	if(pFeedBackContentLabel)
	{		
		pFeedBackContentLabel->SetFont(objFontType); 		
	}

	TEdit *pFeedBackContentField = static_cast<TEdit*>(GetControlPtr(APP_KA_ID_FeedBackForm_FeedBackContentField));
	if(pFeedBackContentField)
	{		
		pFeedBackContentField->SetFont(objFontType); 		
	}	
}

//1991, SubmitButton - "提交"
Boolean  TFeedBackForm::OnSubmitButtonClick(TCtrl  *Sender,EventType  *  eventP)
{
	return FALSE;
}

/*响应菜单弹出前事件*/
void  TFeedBackForm::OnBeforeMenuOpen(void)
{
	return ;
}

/*响应控件上下文菜单弹出事件*/
Boolean  TFeedBackForm::OnCtlContextMenu(EventType*  eventP)
{
	return FALSE;
}

/*响应窗口关闭前事件 - 决定是否可以关闭窗口*/
void  TFeedBackForm::OnCloseQuery(VAR  Boolean  &CanClose)
{
	return ;
}

/*响应窗口关闭事件 - 仅仅是响应而已*/
void  TFeedBackForm::OnClosed()
{	
	// Stop the application if the main form(current form) has been closed
	// GetApplication()->SendStopEvent();
}

/*响应主菜单项点击*/
Boolean  TFeedBackForm::OnMenuSelect(Int32  MenuItemResID)
{
	return FALSE;
}

/*响应弹出菜单项点击事件*/
Boolean  TFeedBackForm::OnPopMenuSelect(Int32  MenuItemResID)
{
	return FALSE;
}

/*响应控件点击事件*/
Boolean  TFeedBackForm::OnCtlSelect(TApplication*  pApp, EventType  *  eventP)
{
	if(eventP->sParam1 == m_nPublishBtnID )
	{
		TEdit* tContentEdit =static_cast< TEdit* >(GetControlPtr(APP_KA_ID_FeedBackForm_FeedBackContentField));
		if(TUString::StrLen(tContentEdit->GetCaption()) > 0)
		{
			pApp->MessageBox(TResource::LoadConstString(APP_KA_ID_STRING_Success),TResource::LoadConstString(APP_KA_ID_STRING_PostFeedback),WMB_OK);
			this->CloseWindow();
		}
		else
		{
			pApp->MessageBox(TResource::LoadConstString(APP_KA_ID_STRING_ContentShouldNotBeEmpty),TResource::LoadConstString(APP_KA_ID_STRING_PostFeedback),WMB_OK);			
		}
		return TRUE;
	}
	else if(eventP->sParam1 == m_BackBtn)
	{
		this->CloseWindow();
		return TRUE;
	}
#if 0	
	switch(eventP->sParam1)
	{
	}
#endif	
	return FALSE;
}

Boolean  TFeedBackForm::EventHandler(TApplication  *  pApp, EventType  *  eventP)
{
	Boolean     handled = FALSE;

	switch(eventP->eType)
	{
	case EVENT_CtrlSelect:
		handled = OnCtlSelect(pApp,eventP);
		break;
	case EVENT_WinInit:
		{
			OnWinCreate();
		}
		break;
	case EVENT_WinClose:
		{
			handled = TRUE; 
			OnClosed();
			if(handled)
				handled = FALSE;
			else 
				handled = TRUE;
		}
		break;
	case EVENT_CtrlSetFocus:
		{
			handled = _OnCtrlSetFocusEvent(pApp, eventP);
			break;
		}
	case EVENT_CtrlKillFocus:
		{
			handled = _OnCtrlKillFocusEvent(pApp, eventP);
			break;
		}
	case EVENT_WinEraseClient:
		{
			TDC 	   dc(this);
			WinEraseClientEventType *pEraseEvent = reinterpret_cast< WinEraseClientEventType* >( eventP );
			TRectangle rc(pEraseEvent->rc);
			TRectangle rcBack(5, 142, 310, 314);
			this->GetBounds(&rcBack);

			// 刷主窗口背景色
			dc.SetBackColor(RGB_COLOR_WHITE);

			// 擦除
			dc.EraseRectangle(&rc, 0);
			dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_title_bg), 0, 0, SCR_W, GUI_API_STYLE_ALIGNMENT_LEFT);

			//dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_bottom_bg), 0, rcBack.Bottom()-68, 
			//320, GUI_API_STYLE_ALIGNMENT_LEFT|GUI_API_STYLE_ALIGNMENT_TOP); 


			pEraseEvent->result = 1;				
			handled = TRUE;
		}
		break;
	case EVENT_KeyCommand: 
		{ 
			// 抓取右软键事件 
			if (eventP->sParam1 == SYS_KEY_SOFTKEY_RIGHT_UP  
				|| eventP->sParam1 == SYS_KEY_SOFTKEY_RIGHT_LONG) 
			{ 
				// 模拟退出按钮选中消息 
				HitControl(m_BackBtn); 
				handled = TRUE; 
			} 
		} 
		break;

	}
	if (handled == FALSE)
		return TWindow::EventHandler(pApp,eventP);

	return handled;
}

Boolean TFeedBackForm::_OnCtrlSetFocusEvent(TApplication * pApp, EventType * pEvent)
{
	Boolean     bHandled = FALSE;
#if 0
	Int32 CtrlID = pEvent->sParam1; 
	if(CtrlID == APP_KA_ID_FeedBackForm_FeedBackContentField)
	{	
		ImeOpenIme( IME_MODE_VOLITANT,	IME_CLASS_CHINESE);
		bHandled = TRUE;
	}	
#endif				
	return bHandled;	

}
Boolean TFeedBackForm::_OnCtrlKillFocusEvent(TApplication * pApp, EventType * pEvent)
{
	Boolean     bHandled = FALSE;
#if 0
	Int32 CtrlID = pEvent->sParam1; 

	if(CtrlID == APP_KA_ID_FeedBackForm_FeedBackContentField)
	{
		//close input method
		ImeCloseIme();
		bHandled = TRUE;
	}
#endif	
	return bHandled;
}

