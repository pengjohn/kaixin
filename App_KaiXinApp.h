// Application application header file.

// Original file name: App_KaiXinApp.h
// Generated by TOPS Builder:Project wizard,Date:2010-8-24


#ifndef  __App_KaiXin_App_H__
#define  __App_KaiXin_App_H__
#include "TG3.h"
#include "TCOM_ConnectManager_Interface.h"
#include "TCOM_ConnectManager_DataType.h"

class  TApp_KaiXinApp  :  public  TApplication
{
public:
	TApp_KaiXinApp();
	~TApp_KaiXinApp();
	virtual Boolean EventHandler(EventType * pEvent);
	ULONG GetConnectID();
protected:
private:
	void ClosePanelForm(void);
	/** ���ӹ������ӿ�ָ�� */
	TCOM_ConnectManager_Interface *m_pConnectManger;
	/** ��������ID */
	ULONG m_uConnectID;
	CM_ACCOUNT_ID_t m_tAID;	
	
	/** ��ӭ����ȴ���ʱ�� */
	Int32 m_nTimerId;	

	//��ʱ��Ϣ��Ϣ�Ķ�ʱ��ID
	Int32 m_nMsgTimerId;

	/*��ʼ��Form ID*/
	Int32 gHwndId_Init;

	/*��¼Form ID*/
	Int32 gHwndId_Login;

	/*���صȴ�Form ID*/
	Int32 gHwndId_WaitingBox;
	
	//�Ƿ񲦺ųɹ���,��ʹ�ù����б��Ͽ���
	Boolean m_bReConnected;

	Boolean  m_bConnected;	//�Ƿ��Ѿ����ӳɹ�
	//��ӦAPI�Ĵ����Ƿ���Ч
	Boolean FormIsValid(Int32  nAccessType);

	/*��������Ϣ����*/
	int UpdateNoticeCount(void);
};


#endif
