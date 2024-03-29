/*!
* \file	 KaiXinAPI_MessageCenter.cpp
* \author	 huxianxiang@GoZone
* \date	 2010-11-8
* \brief  解析与UI: 消息中心
*
* \ref    CopyRight
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated by Kaixin_Component Wizard for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#include "KaiXinAPICommon.h"


void* KaiXinAPI_MessageCenter_JsonParse(char *text)
{
	cJSON *json;
	cJSON *tmp;
	tResponseMessageCenter*  Response = new tResponseMessageCenter;
	memset(Response, 0 , sizeof(tResponseMessageCenter));

	json=cJSON_Parse(text);

	tmp = cJSON_GetObjectItem(json,"ret");
	if (tmp)
	{
		Response->ret = tmp->valueint;	
	}

	if(Response->ret == 1)
	{
		tmp = cJSON_GetObjectItem(json, "uid");
		if(tmp)
		{
			Response->uid = tmp->valueint;
		}

		tmp = cJSON_GetObjectItem(json, "n");
		if(tmp)
		{
			Response->nCount = tmp->valueint;
		}

		tmp = cJSON_GetObjectItem(json, "notices");
		if(tmp)
		{
			int nSize = 0, i = 0;
			nSize = cJSON_GetArraySize(tmp);
			Response->nSize = nSize;
			if( nSize != 0 )
			{
				Response->pNotices = NULL;
				Response->pNotices = (MessageCenter_notices*) malloc(sizeof( MessageCenter_notices ) * nSize);
				memset(Response->pNotices, 0 , sizeof(MessageCenter_notices) * nSize );
			}
			while( i < nSize )
			{
				cJSON *Item = NULL, *pTemp = NULL;
				Item = cJSON_GetArrayItem(tmp,i);
				pTemp = cJSON_GetObjectItem(Item, "mtype");
				if(pTemp)
				{
					Response->pNotices[i].Type = pTemp->valueint;
				}
				pTemp = cJSON_GetObjectItem(Item, "n");
				if(pTemp)
				{
					Response->pNotices[i].Num = pTemp->valueint;
				}
				i++;
			}
		}
	}
	else
	{

	}
	cJSON_Delete(json);
	return Response;
}



// 构造函数
TMessageCenterForm::TMessageCenterForm(TApplication* pApp, Boolean bNew ):TWindow(pApp)
{
	Create(APP_KA_ID_MessageCenter_Form);
	if(bNew == TRUE)
		this->SetWindowMovieMode(TG3_WINDOW_MOVIE_MODE_DEFAULT, TG3_WINDOW_MOVIE_MODE_DEFAULT);
	else
		this->SetWindowMovieMode(TG3_WINDOW_MOVIE_MODE_NONE, TG3_WINDOW_MOVIE_MODE_DEFAULT);
}

// 析构函数
TMessageCenterForm::~TMessageCenterForm(void)
{

}

// 窗口事件处理
Boolean TMessageCenterForm::EventHandler(TApplication * pApp, EventType * pEvent)
{
	Boolean bHandled = FALSE;

	switch (pEvent->eType)
	{
	case EVENT_WinInit:
		{
			_OnWinInitEvent(pApp, pEvent);
			bHandled = TRUE;
			break;
		}

	case EVENT_WinClose:
		{
			_OnWinClose(pApp, pEvent);
			break;
		}

	case EVENT_WinEraseClient:
		{
			TDC 	   dc(this);
			WinEraseClientEventType *pEraseEvent = reinterpret_cast< WinEraseClientEventType* >( pEvent );
			TRectangle rc(pEraseEvent->rc);
			TRectangle rcBack(5, 142, 310, 314);
			this->GetBounds(&rcBack);

			dc.SetBackColor(RGB_COLOR_WHITE);
			dc.EraseRectangle(&rc, 0);
			dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_title_bg), 0, 0, SCR_W, GUI_API_STYLE_ALIGNMENT_LEFT);

			pEraseEvent->result = 1;				
			bHandled = TRUE;
		}
		break;
	case EVENT_CtrlSelect:
		{
			bHandled = _OnCtrlSelectEvent(pApp, pEvent);
			break;
		}
	case EVENT_KeyCommand: 
		{ 
			// 抓取右软键事件 
			if (pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_UP  
				|| pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_LONG) 
			{ 
				// 模拟退出按钮选中消息 
				HitControl(m_BackBtn); 
				bHandled = TRUE; 
			} 
		} 
		break; 	
	case MSG_FORM_UPDATE:
		{
			bHandled = TRUE;
			UpdateEvent(pApp);
		}
		break;		
	default:
		break;
	}

	if (!bHandled)
	{
		bHandled = TWindow::EventHandler(pApp, pEvent);
	}

	return bHandled;
}

// 窗口初始化
Boolean TMessageCenterForm::_OnWinInitEvent(TApplication * pApp, EventType * pEvent)
{
	int iRet =0, nIndex = 0;
	int nMsg[KX_MESSAGE_END] = {0};
	tResponseMessageCenter* Response = NULL;
	iRet = KaiXinAPI_JsonParse(KX_MessageCenter, (void **)&Response);

	m_BackBtn = SetAppBackButton(this);
	SetAppTilte(this,APP_KA_ID_STRING_MsgCenter);//消息中心
	if(iRet == 1)
	{
		TCoolBarList* pCoolBarList = static_cast<TCoolBarList*>(GetControlPtr(APP_KA_ID_MessageCenter_Form_MsgList));

		for(int i = 0; i < Response->nCount; i++ )
		{
			nMsg[ Response->pNotices[i].Type - 1 ] = Response->pNotices[i].Num;
		}

		KaiXinUserInfo.NoticeCount[0] = 0;
		for(int i = 0; i < KX_MESSAGE_END; i++ )
		{
			TUChar MsgInfo[32];
			TBarListItem* pListItem = NULL;

			pListItem = pCoolBarList->Rows()->FirstRow()->GetItem(i);
			KaiXinUserInfo.NoticeCount[i+1] = nMsg[i];
			KaiXinUserInfo.NoticeCount[0] += nMsg[i];
			//set the font color
			if( nMsg[i] > 0 )
			{
				pListItem->SetCaptionFontColor(COLOR_RED);
			}
			else
			{
				pListItem->SetCaptionFontColor(GRAY);
			}
			TUString::StrPrintF(MsgInfo, TResource::LoadConstString(APP_KA_ID_STRING_MessageCenter_Info),nMsg[i]);
			pListItem->SetCaption(MsgInfo);
		}		
	}
	if( Response )
	{
		delete Response;	
	}
	return TRUE;
}

// 关闭窗口时，保存设置信息
Boolean TMessageCenterForm::_OnWinClose(TApplication * pApp, EventType * pEvent)
{
	return TRUE;
}


// 控件点击事件处理
Boolean TMessageCenterForm::_OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent)
{
	Boolean bHandled = FALSE;

	if(m_BackBtn == pEvent->sParam1)
	{
		bHandled = TRUE; 
		this->CloseWindow();

		return bHandled;
	}

	switch(pEvent->sParam1)
	{
	case APP_KA_ID_MessageCenter_Form_MsgList:
		{ 
			TBarRow *pRow = reinterpret_cast< TBarRow* > ( pEvent->sParam2 ); 
			switch( pRow->GetIndex() ) 
			{ 
			case 0: 
				{ 
					TBarListItem *pItem = reinterpret_cast < TBarListItem* >( pEvent->lParam3 ); 
					int MsgType = pItem->GetIndex() + 1;

					switch(MsgType) 
					{ 
					case KX_MESSAGE_SHORT_MESSAGE:
						{
							KaiXinAPICommon_Download(KX_MessagesList, this->GetWindowHwndId());
							bHandled = TRUE;
						}
						break;

					case KX_MESSAGE_USER_COMMENT_RECEIVED:
						{
							KaiXinAPICommon_Download(KX_ReceivedUserCommentsList, this->GetWindowHwndId());
							bHandled = TRUE;					
						}
						break;

					case KX_MESSAGE_COMMENT_RECEIVED:
						{
							KaiXinAPICommon_Download(KX_ReceivedCommentsList, this->GetWindowHwndId());
							bHandled = TRUE;
						}
						break;

					case KX_MESSAGE_SYSTEM_MESSAGE:
						{
							KaiXinAPICommon_Download(KX_SystemMessage, this->GetWindowHwndId());
							bHandled = TRUE;
						}
						break;

					case KX_MESSAGE_USER_COMMENT_SENT:
						{
							KaiXinAPICommon_Download(KX_SentUserCommentsList, this->GetWindowHwndId());
							bHandled = TRUE;
						}
						break;

					case KX_MESSAGE_COMMENT_SENT:
						{
							KaiXinAPICommon_Download(KX_SentCommentsList, this->GetWindowHwndId());
							bHandled = TRUE;									
						}
						break;

					default:
						break;
					}
				} 
				break;

			default:
				break;
			} 
			bHandled = TRUE; 
		} 
		break;

	default:
		break;
	}

	return bHandled;
}

Boolean TMessageCenterForm::UpdateEvent(TApplication * pApp)
{
	int iRet =0, nIndex = 0;
	int nMsg[KX_MESSAGE_END] = {0};
	tResponseMessageCenter* Response = NULL;
	iRet = KaiXinAPI_JsonParse(KX_MessageCenter, (void **)&Response);

	if(iRet == 1)
	{
		TCoolBarList* pCoolBarList = static_cast<TCoolBarList*>(GetControlPtr(APP_KA_ID_MessageCenter_Form_MsgList));

		for(int i = 0; i < Response->nCount; i++ )
		{
			nMsg[ Response->pNotices[i].Type - 1 ] = Response->pNotices[i].Num;
		}

		KaiXinUserInfo.NoticeCount[0] = 0;
		for(int i = 0; i < KX_MESSAGE_END; i++ )
		{
			TUChar MsgInfo[32];
			TBarListItem* pListItem = NULL;

			pListItem = pCoolBarList->Rows()->FirstRow()->GetItem(i);
			KaiXinUserInfo.NoticeCount[i+1] = nMsg[i];
			KaiXinUserInfo.NoticeCount[0] += nMsg[i];
			//set the font color
			if( nMsg[i] > 0 )
			{
				pListItem->SetCaptionFontColor(COLOR_RED);
			}
			else
			{
				pListItem->SetCaptionFontColor(GRAY);
			}
			TUString::StrPrintF(MsgInfo, TResource::LoadConstString(APP_KA_ID_STRING_MessageCenter_Info),nMsg[i]);
			pListItem->SetCaption(MsgInfo);
		}		
	}
	if( Response )
	{
		delete Response;	
	}
	return TRUE;
}