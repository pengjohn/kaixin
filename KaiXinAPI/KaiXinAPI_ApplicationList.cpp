/*!
* \file	 KaiXinAPI_ApplicationList.cpp
* \author	 huxianxiang@GoZone
* \date	 2010-9-29
* \brief  UI: 功能入口界面
*
* \ref    CopyRight
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#include "KaiXinAPICommon.h"


void* KaiXinAPI_ApplicationList_JsonParse(char *text)
{
	cJSON *json;
	cJSON *tmp;
	tResponseApplicationList*  Response = new tResponseApplicationList;
	memset(Response, 0 , sizeof(tResponseApplicationList));

	json=cJSON_Parse(text);

	tmp = cJSON_GetObjectItem(json,"ret");
	if (tmp)
	{
		Response->ret = tmp->valueint;	
	}

	//Success
	if(Response->ret == 1)
	{
		tmp = cJSON_GetObjectItem(json, "applist");
		if(tmp)
		{
			int nSize = 0, i = 0;
			nSize = cJSON_GetArraySize(tmp);
			Response->n = nSize;
			if( nSize > 0 )
			{
				Response->applist = NULL;
				Response->applist = (applistItem*) malloc(sizeof( applistItem ) * nSize);
				memset(Response->applist, 0 , sizeof(applistItem) * nSize );
			}
			while( i < nSize )
			{
				cJSON *Item = NULL, *pTemp = NULL;
				Item = cJSON_GetArrayItem(tmp,i);
				pTemp = cJSON_GetObjectItem(Item, "name");
				if(pTemp)
				{
					STRCPY_Ex(Response->applist[i].name, pTemp->valuestring);
				}
				pTemp = cJSON_GetObjectItem(Item, "url");
				if(pTemp)
				{
					STRCPY_Ex(Response->applist[i].url, pTemp->valuestring);
				}
				i++;
			}
		}

	}
	//Failue
	else
	{
		//tmp = cJSON_GetObjectItem(json,"msg");
		//if (tmp)
		//{
		//	strcpy(Response->msg, tmp->valuestring);	
		//}
	}
	cJSON_Delete(json);
	return Response;
}



// 构造函数
TApplicationListForm::TApplicationListForm(TApplication* pApp):TWindow(pApp)
{
	m_ExitBtn = -1;
	Create(APP_KA_ID_ApplicationList_Form);
}

// 析构函数
TApplicationListForm::~TApplicationListForm(void)
{

}

// 窗口事件处理
Boolean TApplicationListForm::EventHandler(TApplication * pApp, EventType * pEvent)
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

			// 刷主窗口背景色
			dc.SetBackColor(RGB_COLOR_WHITE);

			// 擦除
			dc.EraseRectangle(&rc, 0);

			dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_title_bg), 0, 0, SCR_W,GUI_API_STYLE_ALIGNMENT_LEFT);

			//dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_bottom_bg), 0, rcBack.Bottom()-68, 
			//320, GUI_API_STYLE_ALIGNMENT_LEFT|GUI_API_STYLE_ALIGNMENT_TOP); 


			pEraseEvent->result = 1;				
			bHandled = TRUE;
		}
		break;
	case MSG_DL_THREAD_NOTIFY:
		{
			NotifyMsgDataType notifyData;
			Sys_GetMessageBody((MESSAGE_t *)pEvent, &notifyData, sizeof(NotifyMsgDataType));						

			bHandled = TRUE;
			switch(notifyData.nAccessType)
			{
			case KX_GardenDetail:				
				{				
					break;
				}
			case KX_RanchDetail:				
				{					
					break;
				}				
			}
			break;
		}		
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
				HitControl(m_ExitBtn); 
				bHandled = TRUE; 
			} 
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


Boolean TApplicationListForm::_OnWinInitEvent(TApplication * pApp, EventType * pEvent)
{
	//m_RefreshBtn = SetAppRefreshButton(this);
	m_ExitBtn = SetAppExitButton(this);

	SetAppTilte(this,APP_KA_ID_STRING_More_AppList);	
	_CreateTabButtons(pApp);

#if 0
	int iRet =0, nIndex = 0;
	tResponseApplicationList* Response = NULL;
	iRet = KaiXinAPI_JsonParse(KX_ApplicationList, (void **)&Response);

	if(iRet == 1)
	{
		TCoolBarList* pCoolBarList = static_cast<TCoolBarList*>(GetControlPtr(APP_KA_ID_ApplicationList_Form_AppListForm_CoolBarList));
		if (pCoolBarList)
		{
			pCoolBarList->SetBounds(RC_LIST_NORMAL);	

			TBarRow* pBarRow = NULL;
			TBarRowList* pRowList = NULL;			

			pRowList = pCoolBarList->Rows();
			if (pRowList)
			{
				pRowList->BeginUpdate();
				pRowList->Clear();

				pBarRow = pRowList->AppendRow();

				int iCount = Response->n;
				ItemCount = 0;
				for ( nIndex = 0; nIndex < iCount; nIndex++)
				{
					Int32 bnRetCode = 0;	
					pListItem[nIndex] = pBarRow->AppendItem();
					if( pListItem[nIndex] != NULL )
					{
						TUChar pszString[32];
						if( NULL != Response->applist[nIndex].name )
						{
							STRCPY_Ex(ItemName[nIndex], Response->applist[nIndex].name);
							TUString::StrUtf8ToStrUnicode(pszString, (const Char*)Response->applist[nIndex].name);
						}

						if( NULL != Response->applist[nIndex].url )
						{
							STRCPY_Ex(ItemUrl[nIndex], Response->applist[nIndex].url);
						}

						pListItem[nIndex]->SetCaption(pszString);
						pListItem[nIndex]->SetCaptionFontColor(RGB_COLOR_BLACK);
						pListItem[nIndex]->SetCaptionAlign(tasLeftJustify);
						pListItem[nIndex]->SetIndicatorType(itDefault);
						ItemIndex[nIndex] = pListItem[nIndex]->GetIndex();
					}
					else
					{
						bnRetCode = 1;
						break;
					}
					ItemCount++;
				}
				pRowList->EndUpdate();
			}
		}		
	}

	if(Response)
	{
		delete Response;
	}
#endif
	return TRUE;
}


Boolean TApplicationListForm::_OnWinClose(TApplication * pApp, EventType * pEvent)
{
	return TRUE;
}


Boolean TApplicationListForm:: _HandleApplicationListCtlClick(TApplication * pApp,Int32 iCtlID)
{
	Boolean bIsHandle = FALSE;

	return bIsHandle;
}


Boolean TApplicationListForm::_OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent)
{
	Boolean bHandled = FALSE;
	SS_GTID			gtidMain;
	SS_GetCurrentGTID(&gtidMain);

	switch(pEvent->sParam1)
	{
	case APP_KA_ID_ApplicationList_Form_AppListForm_CoolBarList:
		{ 
			TBarRow *pRow = reinterpret_cast< TBarRow* > ( pEvent->sParam2 ); 
			switch( pRow->GetIndex() ) 
			{ 
			case 0: 
				{ 
					TBarListItem *pItem = reinterpret_cast < TBarListItem* >( pEvent->lParam3 ); 
					int nIndex = pItem->GetIndex();

					switch(nIndex)
					{
					case 0:
						{
//							Set_Url_Params(KX_GardenDetail, "fuid", "");
//							KaiXinAPICommon_Download(KX_GardenDetail, this->GetWindowHwndId());

							char tmpUrl[256] = {0};
							strcat(tmpUrl, "http://wap.kaixin001.com/house/garden/?uid=");
							strcat(tmpUrl, KaiXinUserInfo.uid);
							strcat(tmpUrl, "&verify=");
							strcat(tmpUrl, KaiXinUserInfo.wapverify);
							TWebForm *pWin = new TWebForm(pApp, TResource::LoadConstString(APP_KA_ID_STRING_Garden), tmpUrl);
							bHandled = TRUE;
							break;
						}
					case 1:
						{
							//Set_Url_Params(KX_RanchDetail, "fuid", "");
							//KaiXinAPICommon_Download(KX_RanchDetail, this->GetWindowHwndId());

							char tmpUrl[256] = {0};
							strcat(tmpUrl, "http://wap.kaixin001.com/house/ranch/?uid=");
							strcat(tmpUrl, KaiXinUserInfo.uid);
							strcat(tmpUrl, "&verify=");
							strcat(tmpUrl, KaiXinUserInfo.wapverify);
							TWebForm *pWin = new TWebForm(pApp, TResource::LoadConstString(APP_KA_ID_STRING_Ranch), tmpUrl);

							bHandled = TRUE;
							break;
						}
						//开心餐厅
					case 2:
						{

							char tmpUrl[256] = {0};
							strcat(tmpUrl, "http://wap.kaixin001.com/app.php?aid=1136&id=uphone&uid=");
							strcat(tmpUrl, KaiXinUserInfo.uid);
							strcat(tmpUrl, "&verify=");
							strcat(tmpUrl, KaiXinUserInfo.wapverify);
							TWebForm *pWin = new TWebForm(pApp, TResource::LoadConstString(APP_KA_ID_STRING_Happy_Restaurant), tmpUrl);
							bHandled = TRUE;
							break;
						}
						//争车位
					case 3:
						{
							char tmpUrl[256] = {0};
							strcat(tmpUrl, "http://wap.kaixin001.com/app.php?aid=1040&id=uphone&uid=");
							strcat(tmpUrl, KaiXinUserInfo.uid);
							strcat(tmpUrl, "&verify=");
							strcat(tmpUrl, KaiXinUserInfo.wapverify);
							TWebForm *pWin = new TWebForm(pApp, TResource::LoadConstString(APP_KA_ID_STRING_Parking), tmpUrl);
							bHandled = TRUE;
							break;
						}
						//买房子
					case 4:
						{
							char tmpUrl[256] = {0};
							strcat(tmpUrl, "http://wap.kaixin001.com/app.php?aid=1062&id=uphone&uid=");
							strcat(tmpUrl, KaiXinUserInfo.uid);
							strcat(tmpUrl, "&verify=");
							strcat(tmpUrl, KaiXinUserInfo.wapverify);
							TWebForm *pWin = new TWebForm(pApp, TResource::LoadConstString(APP_KA_ID_STRING_House), tmpUrl);
							bHandled = TRUE;
							break;
						}
						//运势
					case 5:
						{
							char tmpUrl[256] = {0};
							strcat(tmpUrl, "http://wap.kaixin001.com/app.php?aid=1022&id=uphone&uid=");
							strcat(tmpUrl, KaiXinUserInfo.uid);
							strcat(tmpUrl, "&verify=");
							strcat(tmpUrl, KaiXinUserInfo.wapverify);
							TWebForm *pWin = new TWebForm(pApp, TResource::LoadConstString(APP_KA_ID_STRING_Transport_Potential), tmpUrl);
							bHandled = TRUE;
							break;
						}
					default:

						break;
					}
#if 0
					if(!bHandled)
					{
						for(int i=0;i<ItemCount;i++)
						{							
							if (nIndex == ItemIndex[i])
							{
								TUChar pszUrl[128];
								TUChar pszName[32];
								if( NULL != ItemUrl[i] )
								{
									TUString::StrUtf8ToStrUnicode(pszUrl, (const Char*)ItemUrl[i]);
								}

								if( NULL != ItemName[i] )
								{
									TUString::StrUtf8ToStrUnicode(pszName, (const Char*)ItemName[i]);
								}

								//pengjohn debug
								//pApp->MessageBox(pszUrl,pszName,WMB_OK);
								char pUrl[256] = {0};
								strcpy(pUrl,  ItemUrl[i]);
								strcat(pUrl, "?");
								strcat(pUrl, "uid=");
								strcat(pUrl, KaiXinUserInfo.uid);
								strcat(pUrl, "&wapverify=");
								strcat(pUrl, KaiXinUserInfo.wapverify);
								TWebForm*pWin = new TWebForm( pApp, pszName, pUrl);
								bHandled = TRUE;
								break;
							}

						}
					}
#endif
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

	if(!bHandled)
	{
		if(pEvent->sParam1 == this->m_nNewsBtnID)//动态
		{
			KaiXinAPICommon_Download(KX_UpdateFriendsNews, this->GetWindowHwndId());
			bHandled = TRUE;
		}
		else if(pEvent->sParam1 == this->m_nFriendsBtnID)//好友
		{
			KaiXinAPICommon_Download(KX_FriendList, this->GetWindowHwndId());
			bHandled = TRUE;
		}
		else if(pEvent->sParam1 == this->m_nInfosBtnID)//我的地盘
		{
			KaiXinAPICommon_Download(KX_Profile, this->GetWindowHwndId());
			bHandled = TRUE;
		}
		else if(pEvent->sParam1 == this->m_nAppsBtnID)//组件
		{
			//App_PostMessageEx(&gtidMain, MSG_SWITCHFORM_APPLIST, NULL, 0, 0, 0);			
			//KaiXinAPICommon_Download(KX_ApplicationList, this->GetWindowHwndId());//自己 什么都不做
			bHandled = TRUE;
		}	
		else if(pEvent->sParam1 == this->m_nMoreBtnID)//更多
		{
			App_PostMessageEx(&gtidMain, MSG_SWITCHFORM_MORE, NULL, 0, 0, 0);			
			bHandled = TRUE;
		}
		else if(pEvent->sParam1 == m_ExitBtn)//退出
		{
			App_PostMessageEx(&gtidMain, MSG_EXIT, NULL, 0, 0, 0);	
			bHandled = TRUE;
		}
		else if(pEvent->sParam1 == m_RefreshBtn)//刷新
		{
			//KaiXinAPICommon_Download(KX_ApplicationList, this->GetWindowHwndId());
			bHandled = TRUE;
		}
	}

	return bHandled;
}

//创建页面下方Tab Button部分，必须有5个成员变量来保存ButtonID, 
/*
Int32 m_nNewsBtnID;//动态
Int32 m_nFriendsBtnID;//好友
Int32 m_nInfosBtnID;//我的地盘
Int32 m_nAppsBtnID;//组件
Int32 m_nMoreBtnID;//更多

*/
Int32 TApplicationListForm::_CreateTabButtons(TApplication* pApp)
{
	Int32 bnRetCod = 0; 
	TRectangle obBtnRec(100,50,150,30); //初始(left, top, w, h)
	TFont tFont;

	//control 
	Int32 m_iaCreateCtlID[56] = {0};
	TCtrl *m_obContrl[56] = {NULL};
	Int32 m_nCtlIDCount = 0;

	//use to save buttons ID
	m_nNewsBtnID = 0;//动态
	m_nFriendsBtnID = 0;//好友
	m_nInfosBtnID = 0;//我的地盘
	m_nAppsBtnID = 0;//组件
	m_nMoreBtnID = 0;//更多


	//创建5个页面对应的按钮
	const TBitmap * pImgBG = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_bottom_btn_bg);

	//动态	
	const TBitmap * pImgNormal1 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_news);
	const TBitmap * pImgDown1 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_news_over);	
	obBtnRec.SetRect(0, (SCR_H - STATUSBAR_H - BOTTOM_TAB_H), BOTTOM_TAB_W, BOTTOM_TAB_H);

	TMaskButton* pNewsBtn =new TMaskButton;;
	if(pNewsBtn->Create(this))
	{
		pNewsBtn->SetBounds(&obBtnRec);		
		m_nNewsBtnID = pNewsBtn->GetId();//save button ID
		pNewsBtn->SetMaskImage(pImgBG,pImgBG,pImgBG);
		pNewsBtn->SetImage(pImgNormal1, (BOTTOM_TAB_W-pImgNormal1->GetWidth())/2, (BOTTOM_TAB_H-pImgNormal1->GetHeight())/2);	
		pNewsBtn->SetSelImage(pImgDown1, (BOTTOM_TAB_W-pImgDown1->GetWidth())/2, (BOTTOM_TAB_H-pImgDown1->GetHeight())/2);	
	}
	else
	{
		bnRetCod ++;
	}

	//好友	
	const TBitmap * pImgNormal2 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_friend);
	const TBitmap * pImgDown2 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_friend_over);	
	obBtnRec.SetRect(BOTTOM_TAB_W, (SCR_H - STATUSBAR_H - BOTTOM_TAB_H), BOTTOM_TAB_W, BOTTOM_TAB_H);

	TMaskButton* pFriendsBtn =new TMaskButton;;
	if(pFriendsBtn->Create(this))
	{
		pFriendsBtn->SetBounds(&obBtnRec);		
		m_nFriendsBtnID = pFriendsBtn->GetId();//save button ID
		pFriendsBtn->SetMaskImage(pImgBG,pImgBG,pImgBG);
		pFriendsBtn->SetImage(pImgNormal2,(BOTTOM_TAB_W-pImgNormal2->GetWidth())/2,(BOTTOM_TAB_H-pImgNormal2->GetHeight())/2);	
		pFriendsBtn->SetSelImage(pImgDown2,(BOTTOM_TAB_W-pImgDown2->GetWidth())/2,(BOTTOM_TAB_H-pImgDown2->GetHeight())/2);					
	}
	else
	{
		bnRetCod ++;
	}


	//我的地盘

	//当前form为我的地盘，所以图标都是选中图片			
	const TBitmap * pImgNormal3 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_info);//APP_KA_ID_BITMAP_info
	const TBitmap * pImgDown3 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_info_over);	
	obBtnRec.SetRect(BOTTOM_TAB_W*2, (SCR_H - STATUSBAR_H - BOTTOM_TAB_H), BOTTOM_TAB_W, BOTTOM_TAB_H);
	TMaskButton* pInfosBtn =new TMaskButton;;
	if(pInfosBtn->Create(this))
	{
		pInfosBtn->SetBounds(&obBtnRec);		
		m_nInfosBtnID = pInfosBtn->GetId();//save button ID
		pInfosBtn->SetMaskImage(pImgBG,pImgBG,pImgBG);
		pInfosBtn->SetImage(pImgNormal3,(BOTTOM_TAB_W-pImgNormal3->GetWidth())/2,(BOTTOM_TAB_H-pImgNormal3->GetHeight())/2);	
		pInfosBtn->SetSelImage(pImgDown3,(BOTTOM_TAB_W-pImgDown3->GetWidth())/2,(BOTTOM_TAB_H-pImgDown3->GetHeight())/2);					
	}
	else
	{
		bnRetCod ++;
	}

	//组件
	const TBitmap * pImgNormal4 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_module_over);
	const TBitmap * pImgDown4 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_module_over);
	obBtnRec.SetRect(BOTTOM_TAB_W*3, (SCR_H - STATUSBAR_H - BOTTOM_TAB_H),BOTTOM_TAB_W, BOTTOM_TAB_H);
	TMaskButton* pAppsBtn =new TMaskButton;;
	if(pAppsBtn->Create(this))
	{
		pAppsBtn->SetBounds(&obBtnRec);		
		m_nAppsBtnID = pAppsBtn->GetId();//save button ID
		pAppsBtn->SetMaskImage(pImgBG,pImgBG,pImgBG);
		pAppsBtn->SetImage(pImgNormal4,(BOTTOM_TAB_W-pImgNormal4->GetWidth())/2,(BOTTOM_TAB_H-pImgNormal4->GetHeight())/2);	
		pAppsBtn->SetSelImage(pImgDown4,(BOTTOM_TAB_W-pImgDown4->GetWidth())/2,(BOTTOM_TAB_H-pImgDown4->GetHeight())/2);					
	}
	else
	{
		bnRetCod ++;
	}

	//更多
	const TBitmap * pImgNormal5 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_more);
	const TBitmap * pImgDown5 = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_more_over);	
	obBtnRec.SetRect(BOTTOM_TAB_W*4, (SCR_H - STATUSBAR_H - BOTTOM_TAB_H), BOTTOM_TAB_W, BOTTOM_TAB_H);

	TMaskButton* pMoreBtn =new TMaskButton;;
	if(pMoreBtn->Create(this))
	{
		pMoreBtn->SetBounds(&obBtnRec);		
		m_nMoreBtnID = pMoreBtn->GetId();//save button ID
		pMoreBtn->SetMaskImage(pImgBG,pImgBG,pImgBG);
		pMoreBtn->SetImage(pImgNormal5,(BOTTOM_TAB_W-pImgNormal5->GetWidth())/2,(BOTTOM_TAB_H-pImgNormal5->GetHeight())/2);	
		pMoreBtn->SetSelImage(pImgDown5,(BOTTOM_TAB_W-pImgDown5->GetWidth())/2,(BOTTOM_TAB_H-pImgDown5->GetHeight())/2);					
	}
	else
	{
		bnRetCod ++;
	}			

	return bnRetCod;
}

