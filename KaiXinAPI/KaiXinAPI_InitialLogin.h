//KaiXinAPI_InitialLogin.h
#ifndef  __KaiXinAPI_InitialLogin_H__
#define  __KaiXinAPI_InitialLogin_H__

#include "KaiXinAPI.h"



typedef struct
{
	int ret;
	char msg[64];
	char uid[32];
	char verify[128];
	char wapverify[128];	
}tResponseInitialLogin;



extern void* KaiXinAPI_InitialLogin_JsonParse(char *text);


class TInitialLoginForm : public TWindow
{
public:
	TInitialLoginForm(TApplication* pApp);
	virtual ~TInitialLoginForm(void);
	virtual Boolean EventHandler(TApplication * appP, EventType * eventP);

private:
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinClose(TApplication * pApp, EventType * pEvent);
	Boolean _OnCtrlSelectEvent(TApplication * pApp, EventType * pEvent);
};

#endif
