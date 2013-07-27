
/*!
* 
* \file   App_KaiXinInitForm.cpp
* \author John.Peng
* \date	  2010.11.18
* \brief  应用启动界面
* 
* \ref    CopyRight
*/
#include "KaiXinAPICommon.h"
#include "App_KaiXinInitForm.h"


#define LOADING_FORM_MAX_COUNT	(30)	//拨号的最大次数

/** 构造函数
*
* \param pApp   TApplication指针
* \return 无
*/
TInitForm::TInitForm(TApplication * pApp):TWindow(pApp)
{
	nLoadStep = 0;
	m_nTimerId = -1;
	Create(APP_KA_ID_Entrance_Form);
}

/** 析构函数
*
* \return 无
*/
TInitForm::~TInitForm(void)
{
	//TODO::停止短消息读取定时器
	TIMER_Release(m_nTimerId);
	m_nTimerId = -1;
}


/** 事件处理函数
*
* \param pApp   TApplication指针
* \param pEvent EventType指针
* \return 是否已处理
*/
Boolean TInitForm::EventHandler(TApplication * pApp, EventType * pEvent)
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
		}
		break;

	case EVENT_WinClose:
		{
			// Stop the application since the main form has been closed

		}
		break;

	case EVENT_KeyCommand: 
		{ 
			// 抓取右软键事件 
			if (pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_UP  
				|| pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_LONG) 
			{ 
				// 模拟退出按钮选中消息 
				//pApp->CloseAllWindows();
				pApp->SendStopEvent();	
				bHandled = TRUE; 
			} 
		} 

	case EVENT_WinEraseClient:
		{
			TDC 	   dc(this);
			WinEraseClientEventType *pEraseEvent = reinterpret_cast< WinEraseClientEventType* >( pEvent );
			TRectangle rc(pEraseEvent->rc);
			TRectangle rcBack(5, 142, 310, 314);
			this->GetBounds(&rcBack);

			// 擦除
			dc.EraseRectangle(&rc, 0);

			dc.DrawBitmapsH(TResource::LoadConstBitmap(APP_KA_ID_BITMAP_Loading_bg), 0, 0, SCR_W, GUI_API_STYLE_ALIGNMENT_LEFT); 

			pEraseEvent->result = 1;				
			bHandled = TRUE;
		}
		break;	
	case MESSAGE_TIMER:
		{
			//容错,如果TimerID == 0, 则直接忽略
			if(pEvent->sParam1 == 0)
				break;		
			if (pEvent->sParam1 == m_nTimerId)
			{
				nLoadStep ++;
				if(nLoadStep > LOADING_FORM_MAX_COUNT)
				{
					TIMER_Release(m_nTimerId);
					m_nTimerId = -1;			
					pApp->MessageBox(TResource::LoadConstString(APP_KA_ID_STRING_DialupFail), TUSTR_Kx_NULL, WMB_OK);
					pApp->SendStopEvent();				
				}
				else
				{
					_DrawDot(pApp, nLoadStep%LOADING_FORM_DOT_NUM);
				}
			}
			bHandled = TRUE;
			break;
		}
	}
	if (bHandled == FALSE)
	{
		return TWindow::EventHandler(pApp,pEvent);
	}
	return bHandled;
}

/** 窗口初始化
*
* \param pApp   TApplication指针
* \param pEvent EventType指针
* \return 是否已处理
*/
#if(LCD_SIZE == LCD_HVGA )
#define DOT_X	90
#define DOT_Y	300
#elif(LCD_SIZE == LCD_WVGA )
#define DOT_X	90
#define DOT_Y	500
#endif
#define DOT_W	14
#define DOT_H	14
Boolean TInitForm::_OnWinInitEvent(TApplication * pApp, EventType * pEvent)
{
	for(int i=0; i<LOADING_FORM_DOT_NUM; i++)
	{
		TImage* pTImage = new TImage;
		if(pTImage->Create(this))
		{
			TRectangle obBtnRec(DOT_X+((SCR_W - DOT_X*2)/LOADING_FORM_DOT_NUM)*i, DOT_Y, DOT_W, DOT_H);
			nDotID[i] = pTImage->GetId();//save button ID
			pTImage->SetBounds(&obBtnRec); 	
			pTImage->SetBitmapByResId (APP_KA_ID_BITMAP_Loading_dot); 
		}
	}

	_DrawDot(pApp, nLoadStep);
	m_nTimerId = TIMER_Create(1000, TIMER_MODE_AUTORUN | TIMER_MODE_PERIOD, NULL, 0, 0);	
	return TRUE;
}

/**
 * 显示连接的动画
 *
 * \param pApp
 * \param nStep 	连接第几步
 */
void TInitForm::_DrawDot(TApplication * pApp, int nStep)
{

	for(int i=0; i<LOADING_FORM_DOT_NUM; i++)
	{
		TImage* pTImage = NULL;
		pTImage = static_cast< TImage* >(this->GetControlPtr(nDotID[i]));
		if(pTImage!= NULL)
		{
			if(i<=nStep)
				pTImage->SetBitmapByResId (APP_KA_ID_BITMAP_Loading_dot_hl);
			else
				pTImage->SetBitmapByResId (APP_KA_ID_BITMAP_Loading_dot);
		}
	}	
	return;
}

