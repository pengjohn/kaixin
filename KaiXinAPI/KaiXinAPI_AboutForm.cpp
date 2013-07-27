/*!
* \file	 KaiXinAPI_AboutForm.cpp
* \author	 GoZone
* \date	
* \brief  UI: 关于，版本信息等
*
* \ref    CopyRight
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#include "KaiXinAPICommon.h"

#define KAIXIN_VERSION_STR "V2.90_20110803"

TAboutForm::TAboutForm(TApplication  *  pApp):TWindow(pApp)
{
	Create(APP_KA_ID_AboutForm);
}

TAboutForm::~TAboutForm()
{

}

/*响应窗口创建事件*/
void  TAboutForm::OnWinCreate(void)
{
	m_BackBtn = SetAppBackButton(this);	
	SetAppTilte(this, APP_KA_ID_STRING_About);	

	TCtrl*pAboutVersion = static_cast<TCtrl*>(GetControlPtr(APP_KA_ID_AboutForm_About2));
	
	TUChar  pszString[128] = {0};
	TUChar  pszVersion[128] = {0};
	
	TUString::StrCopy(pszString, TResource::LoadConstString(APP_KA_ID_STRING_VersionFormat));
	TUString::StrUtf8ToStrUnicode(pszVersion, (const Char *)KAIXIN_VERSION_STR);
	TUString::StrCat(pszString, pszVersion);
	pAboutVersion->SetCaption(pszString, FALSE);
		
}

/*响应菜单弹出前事件*/
void  TAboutForm::OnBeforeMenuOpen(void)
{
	return ;
}

/*响应控件上下文菜单弹出事件*/
Boolean  TAboutForm::OnCtlContextMenu(EventType*  eventP)
{
	return FALSE;
}

/*响应窗口关闭事件 - 仅仅是响应而已*/
void  TAboutForm::OnClosed()
{	
	// Stop the application if the main form(current form) has been closed
	// GetApplication()->SendStopEvent();
}

/*响应主菜单项点击*/
Boolean  TAboutForm::OnMenuSelect(Int32  MenuItemResID)
{
	return FALSE;
}

/*响应弹出菜单项点击事件*/
Boolean  TAboutForm::OnPopMenuSelect(Int32  MenuItemResID)
{
	return FALSE;
}

/*响应控件点击事件*/
Boolean  TAboutForm::OnCtlSelect(TCtrl  *Sender,EventType  *  pEvent)
{
	return FALSE;
}

Boolean  TAboutForm::EventHandler(TApplication  *  appP, EventType  *  eventP)
{
	Boolean     handled = FALSE;

	switch(eventP->eType)
	{
	case EVENT_WinPaint:
		{
			DrawWindow();
			handled = TRUE;
			break;
		}
	case EVENT_CtrlSelect:
		{
			if(m_BackBtn == eventP->sParam1)
			{
				handled = TRUE; 
				this->CloseWindow();

				return handled;
			}

			switch(eventP->sParam1)
			{
			case RES_SYSTEM_WINDOW_TITLE_BUTTON_ID:
				{
					handled = TRUE; 
					if(handled == TRUE)
					{
						handled = FALSE;
					}
					else
						handled = TRUE;
				}
				break;
			default:
				{	
					return OnCtlSelect(GetControlPtr(eventP->sParam1),eventP);
				}
				break;
			}
		}
		break;
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

	case EVENT_MenuSelect:
		{
			handled = OnMenuSelect(eventP->sParam1);			
		}
		break;
	case EVENT_CtrlContextMenu:
		{
			handled = OnCtlContextMenu(eventP);			
			break;
		}
	case EVENT_MenuOpen:
		{
			OnBeforeMenuOpen();
		}
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
		return TWindow::EventHandler(appP,eventP);

	return handled;
}
