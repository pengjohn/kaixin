/*!
* 
* \file   TestForm.cpp
* \author GoZone
* \date	  2011-1-28
* \brief  用于做内部功能测试
* 
* \ref    CopyRight
*/
#include "TestForm.h"

#include  "TDownload.h"
#include "KaiXinAPICommon.h"

TestForm::TestForm(TApplication * pApp):TWindow(pApp)
{
	Create(APP_KA_ID_TestForm);
}

Boolean TestForm::EventHandler( TApplication * pApp, EventType *pEvent )
{
	Boolean bHandled = FALSE;
	switch( pEvent->eType )
	{
#if 1
		case EVENT_WinInit:
			{
				// Do initialization here
				_OnWinInitEvent(pApp, pEvent);
				bHandled = TRUE;
			}
			break;
		case EVENT_CtrlSelect:
			{

				// 处理控件点击事件或响应事件
				bHandled = _OnCtlSelectEvent( pApp, pEvent );

			}
			break;		
		case EVENT_WinClose:
			{
				// Do uninitialization here
			}
			break;

		case EVENT_WinEraseClient:
			{
				TDC 	   dc(this);
				WinEraseClientEventType *pEraseEvent = reinterpret_cast< WinEraseClientEventType* >( pEvent );
				TRectangle rc(pEraseEvent->rc);
				TRectangle rcBack(5, 142, 310, 314);
				GetBounds(&rcBack);

				// 擦除
				dc.EraseRectangle(&rc, 0);

				dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_title_bg), 0, 0, SCR_W,
					GUI_API_STYLE_ALIGNMENT_LEFT);

				//dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_bottom_bg), 0, rcBack.Bottom()-44, 
				//320, GUI_API_STYLE_ALIGNMENT_LEFT|GUI_API_STYLE_ALIGNMENT_TOP); 


				pEraseEvent->result = 1;				
				bHandled = TRUE;
			}
			break;		
		case MSG_POST_THREAD_NOTIFY:
			{
#if 0
				PostNotifyMsgDataType notifyData;
				Sys_GetMessageBody((MESSAGE_t *)pEvent, &notifyData, sizeof(PostNotifyMsgDataType));

				if(notifyData.nEditType == NewDiaryEdit)
				{
					const TUChar *pTUCharEditTitle = notifyData.PostMsgData.diarydata.pszEditTitle; //保存编辑标题 UEString(128)    
					const TUChar *pTUCharEditContent = notifyData.PostMsgData.diarydata.pszEditContent;
					Char pszEditTitle[128];
					Char pszEditContent[4096];						
					TUString::StrUnicodeToStrUtf8( pszEditTitle, pTUCharEditTitle);
					TUString::StrUnicodeToStrUtf8( pszEditContent, pTUCharEditContent);			

					Set_Url_Params(KX_PostDiary, "title", (char*)pszEditTitle);
					Set_Url_Params(KX_PostDiary, "content", (char*)pszEditContent);


					KaiXinAPICommon_Download(KX_PostDiary);			
				}
				else if(notifyData.nEditType == NewRecordEdit)
				{  
					const TUChar *pTUCharRecordContent = notifyData.PostMsgData.recorddata.pszRecordContent;
					Char pszRecordContent[280];						

					TUString::StrUnicodeToStrUtf8( pszRecordContent, pTUCharRecordContent);			

					Set_Url_Params(KX_WriteRecord, "privacy", "0");
					Set_Url_Params(KX_WriteRecord, "reccont", (char*)pszRecordContent);


					KaiXinAPICommon_Download(KX_WriteRecord);				
				}

#endif
				bHandled = TRUE;
			}
			break;
			//下载完成消息在给各自form中处理模板
		case MSG_DL_THREAD_NOTIFY:
			{
				NotifyMsgDataType notifyData;
				Sys_GetMessageBody((MESSAGE_t *)pEvent, &notifyData, sizeof(NotifyMsgDataType));						

				bHandled = TRUE;
				switch(notifyData.nAccessType)
				{
				case KX_PhotoDownload:
					{

						break;
					}
				case KX_FaceList:
					{

						break;
					}				
				}

			}
			break;
#endif

	}
	return bHandled;

}

Boolean TestForm::_OnWinInitEvent(TApplication * pApp, EventType * pEvent)
{

	return TRUE;
}
Boolean TestForm::_OnCtlSelectEvent(TApplication * pApp, EventType * pEvent)
{
	Boolean     bHandled = FALSE;

	switch(pEvent->sParam1)
	{
	case APP_KA_ID_TestForm_ProfileBtn:
		{
			//KaiXinAPICommon_Download(KX_Profile);
			KaiXinAPICommon_Download(KX_UpdateFriendsNews);			
			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_FriendListBtn:
		{
			//Add your code here
			KaiXinAPICommon_Download(KX_FriendList);
			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_FriendPhotoBtn:
		{
			//Add your code here

			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_AlbumListBtn:
		{
			//Add your code here

			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_AlbumPhotoBtn:
		{
			//Add your code here

			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_UpdateStatusBtn:
		{
			//Add your code here

			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_UploadPhotoBtn:
		{
			//Add your code here

			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_WriteRecordBtn:
		{
			PostNotifyMsgDataType in_msgData;
			MemSet(&in_msgData, 0, sizeof(PostNotifyMsgDataType));

			in_msgData.nCtrlId = 0;
			in_msgData.nHwndId = this->GetWindowHwndId();
			in_msgData.nEditType = NewRecordEdit;

			TAppEditForm *pComm1 = new TAppEditForm( pApp, in_msgData);

			bHandled = TRUE;
		}
		break;	

	case APP_KA_ID_TestForm_ApplicationListBtn:
		{
			KaiXinAPICommon_Download(KX_ApplicationList);
			bHandled = TRUE;
		}
		break;	

	case APP_KA_ID_TestForm_MessageCenterBtn:
		{
			KaiXinAPICommon_Download(KX_MessageCenter);
			bHandled = TRUE;
		}
		break;	

	case APP_KA_ID_TestForm_MessagesListBtn:
		{
			KaiXinAPICommon_Download(KX_MessagesList);
			bHandled = TRUE;
		}
		break;	

	case APP_KA_ID_TestForm_GardenInfoBtn:
		{
			KaiXinAPICommon_Download(KX_GardenDetail);
			bHandled = TRUE;
		}
		break;	
	case APP_KA_ID_TestForm_FriendCommentFormBtn:
		{
			//Add your code here
			KaiXinAPICommon_Download(KX_FriendsCommentList);		
			bHandled = TRUE;
		}
		break;

		break;	
	case APP_KA_ID_TestForm_Test2Btn://好友最新评论
		{
			//Add your code here

			//KaiXinAPICommon_Download(KX_ReceivedAnObjectComments);
			//KaiXinAPICommon_Download(KX_ReceivedCommentsList);

			//KaiXinAPICommon_Download(KX_VoteDetail);
			//KaiXinAPICommon_Download(KX_PostVote);

			//KaiXinAPICommon_Download(KX_InviteCode);
			//KaiXinAPICommon_Download(KX_UpgradeInfos);

			//KaiXinAPICommon_Download(KX_Init);

			/*

			Set_Url_Params(KX_GardenDetail, "fuid", KaiXinUserInfo.uid);
			KaiXinAPICommon_Download(KX_GardenDetail);
			KaiXinAPICommon_Download(KX_GardenList);
			*/


			Set_Url_Params(KX_RanchDetail, "fuid", KaiXinUserInfo.uid);

			KaiXinAPICommon_Download(KX_RanchDetail);
			KaiXinAPICommon_Download(KX_RanchList);	


			bHandled = TRUE;
		}
		break;		
	case APP_KA_ID_TestForm_Test3Btn:
		{
			KaiXinAPICommon_Download(KX_SystemMessage);
			bHandled = TRUE;
		}
		break;	
	case APP_KA_ID_TestForm_Test4Btn:
		{
			//KaiXinAPICommon_Download(KX_BirthdayList);

			extern TUChar   g_PostFilePath[EOS_FILE_MAX_PATH];
			TUChar pszTemp[EOS_FILE_MAX_FNAME];
			TUString::StrCopy(g_PostFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
			TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
			TUString::StrCat(g_PostFilePath,pszTemp);	
			TUString::StrGBToUnicode(pszTemp,(Char*)"photo.jpg");
			TUString::StrCat(g_PostFilePath,pszTemp);			

			Set_Url_Params(KX_UploadPhoto, "title", "FromuPhone");
			KaiXinAPICommon_Download(KX_UploadPhoto);
			bHandled = TRUE;
		}
		break;		

	case APP_KA_ID_TestForm_AppNewsBtn:
		{
			bHandled = TRUE;
		}
		break;	
	case APP_KA_ID_TestForm_KxEditBtn:
		{	
			KaiXinAPICommon_Download(KX_FaceList);//下载应在解析之前

#if 0
			PostNotifyMsgDataType in_msgData;
			MemSet(&in_msgData, 0, sizeof(PostNotifyMsgDataType));

			in_msgData.nCtrlId = 0;
			in_msgData.nHwndId = this->GetWindowHwndId();
			in_msgData.nEditType = NewDiaryEdit;

			TAppEditForm *pComm1 = new TAppEditForm( pApp, in_msgData);
#endif


#if 0
			in_msgData.nEditType = RecordEdit;
			TAppEditForm *pComm2 = new TAppEditForm( pApp, in_msgData);

			in_msgData.nEditType = StatusUpdateEdit;
			TAppEditForm *pComm3 = new TAppEditForm( pApp, in_msgData);

			in_msgData.nEditType = NewMessageEdit;
			TAppEditForm *pComm4 = new TAppEditForm( pApp, in_msgData);
			in_msgData.nEditType = NewTagEdit;
			TAppEditForm *pComm6 = new TAppEditForm( pApp, in_msgData);


			in_msgData.nEditType = NewUserCommentEdit;
			TAppEditForm *pComm5 = new TAppEditForm( pApp, in_msgData);

			in_msgData.nEditType = ReplyUserCommentEdit;
			TAppEditForm *pComm51 = new TAppEditForm( pApp, in_msgData);

			in_msgData.nEditType = NewCommentEdit;
			TAppEditForm *pComm52 = new TAppEditForm( pApp, in_msgData);

			in_msgData.nEditType = ReplyFriendCommentEdit;
			TAppEditForm *pComm53 = new TAppEditForm( pApp, in_msgData);

#endif
			bHandled = TRUE;
		}
		break;		

	case APP_KA_ID_TestForm_LogoutBtn:
		{

			KaiXinAPICommon_Download(KX_Logout);
			//CloseWindow();
			bHandled = TRUE;
		}
		break;

	case APP_KA_ID_TestForm_RecordListBtn:
		{
			//获取自己的RecordList也需要传fuid , 和API文档有差异
			Set_Url_Params(KX_RecordList, "fuid", KaiXinUserInfo.uid);
			KaiXinAPICommon_Download(KX_RecordList);
			bHandled = TRUE;
		}
		break;
	case APP_KA_ID_TestForm_DiaryFormBtn:
		{
			Set_Url_Params(KX_DiaryList, "fuid", KaiXinUserInfo.uid);
			KaiXinAPICommon_Download(KX_DiaryList);

			bHandled = TRUE;
		}
		break;	
	case APP_KA_ID_TestForm_Test5Btn://转贴
		{
			Set_Url_Params(KX_RepasteIndex, "fuid", KaiXinUserInfo.uid);
			KaiXinAPICommon_Download(KX_RepasteIndex);

			bHandled = TRUE;
		}
		break;		
	default:

		//ImeCloseIme();
		break;		

	}
	return bHandled;
}

