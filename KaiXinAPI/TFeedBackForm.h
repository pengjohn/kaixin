/**************************************************************************/
/*                                                                        */
/* Copyright (c) 2005-2006 Tranzda Technologies Co.,Ltd.                  */
/*                    ������ȫ�Ǵ�Ƽ����޹�˾  ��Ȩ���� 2005-2010        */
/*                                                                        */
/*  PROPRIETARY RIGHTS of Tranzda Technologies Co.,Ltd. are involved in   */
/*  the subject matter of this material. All manufacturing, reproduction, */
/*  use, and sales rights pertaining to this subject matter are governed  */
/*  by the license agreement.  The recipient of this software implicitly  */
/*  accepts the terms of the license.                                     */
/*  �������ĵ�������������ȫ�Ǵ�Ƽ����޹�˾�ĺϷ��ʲ����κ���ʿ�Ķ���ʹ  */
/*  �ñ����ϱ�������Ӧ��������Ȩ,�е��������κͽ�����Ӧ�ķ���Լ����     */
/*                                                                        */
/**************************************************************************/
// Application form file.

// Original file name: TFeedBackForm.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-11-26

#ifndef   __APP_KA_ID_FeedBackForm_H__
#define   __APP_KA_ID_FeedBackForm_H__
#include "KaiXinAPI.h"

#ifndef VAR
#define VAR 
#endif

class  TFeedBackForm :  public  TWindow
{
public:
	TFeedBackForm(TApplication  *  pApp);
	~TFeedBackForm(void);
	/*Override*/virtual Boolean EventHandler(TApplication * appP, EventType * eventP);
protected:
	virtual void OnWinCreate(void);
	virtual void OnClosed(void);
	virtual Boolean OnCtlSelect(TApplication*  pApp,EventType * eventP);
	virtual Boolean OnMenuSelect(Int32 MenuItemResID);
	virtual Boolean OnPopMenuSelect(Int32 MenuItemResID);
	virtual void OnBeforeMenuOpen(void);
	virtual Boolean OnCtlContextMenu(EventType* eventP);
	virtual void OnCloseQuery (VAR Boolean &CanClose) ;
	Boolean _OnCtrlSetFocusEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlKillFocusEvent(TApplication * pApp, EventType * pEvent);	
protected:
	/*crtl  call  back*/Boolean  OnSubmitButtonClick(TCtrl  *Sender,EventType  *  eventP) ;
private:
	Int32	m_BackBtn;
	Int32	m_nPublishBtnID;
};


#endif
