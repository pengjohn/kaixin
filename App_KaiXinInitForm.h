
/*!
* 
* \file   App_KaiXinInit.h
* \author John.Peng
* \date	  2010.11.18
* \brief  描述信息窗口
* 
* \ref    CopyRight
*/

#ifndef  __TKAIXIN_INIT_H__
#define  __TKAIXIN_INIT_H__

#include "TG3.h"

/** 描述信息窗口
*
*/
#define LOADING_FORM_DOT_NUM		(5)

class TInitForm : public TWindow
{
public:
	TInitForm(TApplication * pApp);
	virtual ~TInitForm(void);
	virtual Boolean EventHandler(TApplication * pApp, EventType * pEvent);
	Boolean _OnWinInitEvent(TApplication * pApp, EventType * pEvent);
	void _DrawDot(TApplication * pApp, int nStep);
private:
	int	nLoadStep;
	Int32 nDotID[LOADING_FORM_DOT_NUM];
	Int32 m_nTimerId;
};


#endif // __TDESFORM_H__

