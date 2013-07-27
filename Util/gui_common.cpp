
#include "gui_common.h"
#include  "App_KaiXinUnicodeScript_str.h"

//��������������ʾ�����ִ����������
//Todo::WordWrapNoLF������, �����һ���ֽ�Ϊ�ո�,���ص�nShowLen���������⣬��Ҫ��ȥͷ�ո���
Int32 GetShowAllStringWidth(TUChar* pCaptionString, TFont objFontType)
{
	Int32 Width = 1;
	Int32 tempWidth = 0;//������0��ʼ
	Int32 nStringLen = TUString::StrLen(pCaptionString);
	Int32 nShowLen = 0;
	do
	{
		tempWidth ++;
		nShowLen = objFontType.WordWrapNoLF(TUString::StrTrimUnVisible(pCaptionString), tempWidth);
		
	}while(nShowLen < nStringLen);

	return tempWidth + 4;//�ոպõĳ�����ʾ�ִ�ʱ�����⣬���ټ���������
}

Int32 GetShowAllStringWidthEx(TUChar* pCaptionString, Int32 FontSize)
{
	TFont objFontType;
	objFontType.Create(FontSize, FontSize);
	return GetShowAllStringWidth(pCaptionString, objFontType);
}

//�������̫����ʾ��������ʡ�Ժű�ʾ
void  ShowAsShort(TCtrl *pTCtrl, TUChar* pCaptionString, TFont objFontType)
{
	TRectangle Rc_TCtrl;
	pTCtrl->GetBounds(&Rc_TCtrl);
	
	int nStrLen = TUString::StrLen(TUString::StrTrimUnVisible(pCaptionString));
	//int nShortWidth = GetShowAllStringWidth((TUChar*)L"...",objFontType);
	int nShortWidth = GetShowAllStringWidth((TUChar*)TUSTR_Kx_Ellipsis,objFontType);	
	int nShowLen = objFontType.WordWrapNoLF(TUString::StrTrimUnVisible(pCaptionString), Rc_TCtrl.Width()- nShortWidth*2);

	if (nShowLen < nStrLen)
	{
		//Add one more label to show
		
		TUChar* pszTemp = new TUChar[nShowLen + 10];
		MemSet( (void *)pszTemp, 0x0, sizeof(TUChar) * (nShowLen + 10) );
		TUString::StrNCopy(pszTemp,TUString::StrTrimUnVisible(pCaptionString),nShowLen);
		TUString::StrCat(pszTemp,TUSTR_Kx_Ellipsis);//(const TUChar*)L"..."
		pTCtrl->SetCaption(pszTemp,FALSE);
		delete pszTemp;	
	}
	else
	{
		pTCtrl->SetCaption(TUString::StrTrimUnVisible(pCaptionString),FALSE);//StrTrim
	}	
}


//����Ӧ�ñ���Ĭ�Ͼ���
//pApp --Ӧ��ָ��
//TitleStringResId --�����ִ�ID, Ĭ��Ϊ0
//TitleString --�����ִ���Ĭ��Ϊ��NULL
//color--������ɫ��Ĭ��Ϊ��:RGB_COLOR_WHITE
//nFontSize �����С
//���ؿؼ�ID
Int32 SetAppTilte(TWindow * pWindow, Int32 nTitleStringResId, TUChar* pTitleString, ColorRefType Color, Int32 nFontSize)
{
	Int32 m_TitleCtlID = 0;

	TCtrl *m_TitleContrl;
	TRectangle TitleRC(0,0,0,0);
	TRectangle WindowRC(0, 0, 0, 0);
	TFont tFont;
	Int32 nTitleWidth = 0;
	Boolean bNeedShort = FALSE;
	TUChar sTitleString[128] ={0};

	if(nTitleStringResId == 0)//˵�����������ִ�
	{
		if(pTitleString)
		{
			TUString::StrNCopy(sTitleString, pTitleString, sizeof(sTitleString));
		}
	}
	else
	{
		TUString::StrNCopy(sTitleString, TResource::LoadConstString(nTitleStringResId), sizeof(sTitleString));
	}
	
	tFont.Create(nFontSize, nFontSize,  FONT_STYLE_BOLD);
	nTitleWidth = GetShowAllStringWidth(sTitleString,tFont);
	if(nTitleWidth > SCR_W - (TITLE_BUTTON_X + TITLE_BUTTON_W)*2 )
	{
		bNeedShort = TRUE;
		nTitleWidth = SCR_W - (TITLE_BUTTON_X + TITLE_BUTTON_W)*2 - 10;
	}
	
	pWindow->GetBounds(&WindowRC);	
	TitleRC.SetRect((WindowRC.Width()-nTitleWidth)/2, (TITLEBAR_H- nFontSize)/2, nTitleWidth, nFontSize);
	
	m_TitleContrl = new TLabel;
	
	if(m_TitleContrl->Create(pWindow))
	{		
		m_TitleContrl->SetBounds(&TitleRC);	
		m_TitleCtlID = m_TitleContrl->GetId();	

		m_TitleContrl->SetFont(tFont);
		m_TitleContrl->SetColor(CTL_COLOR_TYPE_FORE,Color);
		m_TitleContrl->SetEnabled(FALSE);
		m_TitleContrl->SetCaption(sTitleString,FALSE);
		if(bNeedShort)
			ShowAsShort(m_TitleContrl, sTitleString, tFont);
		m_TitleContrl->Show(TRUE);
	}

	return m_TitleCtlID;
}

//����Ӧ�ñ༭��ť
//pApp --Ӧ��ָ��
//���ؿؼ�ID

Int32 SetAppBitmapButton(TWindow * pWindow, Int32 NomalBtnID, Int32 OverBtnID)
{
	Int32 m_BtnID = 0;
	TButton *pBtn;
	TRectangle BtnRC(TITLE_BUTTON_X, TITLE_BUTTON_Y, TITLE_BUTTON_W, TITLE_BUTTON_H);

	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(NomalBtnID);//APP_RE_ID_BITMAP_write_but
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(OverBtnID);//APP_RE_ID_BITMAP_write_but_over
		
	pBtn = new TButton;	
	if(pBtn->Create(pWindow))
	{		
		pBtn->SetBounds(&BtnRC);	
		m_BtnID = pBtn->GetId();	
		
		pBtn->SetCaption(TUSTR_Kx_NULL,FALSE);
		pBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pBtn->SetImage(pNormalBmp,0);
		pBtn->SetImage(pOverBmp,1);		
		pBtn->Show(TRUE);
	}
	return m_BtnID;
}

//����Ӧ�ñ�������ť
Int32 SetAppTitleButton(TWindow * pWindow, Int32 nResId, int ButtonPosition)
{
	Int32 m_BtnID = 0;
	TButton *pBtn;
	TRectangle BtnRC_Left(TITLE_BUTTON_X, TITLE_BUTTON_Y, TITLE_BUTTON_W, TITLE_BUTTON_H);	
	TRectangle BtnRC_Right(SCR_W-TITLE_BUTTON_X-TITLE_BUTTON_W, TITLE_BUTTON_Y, TITLE_BUTTON_W, TITLE_BUTTON_H);
	TFont tFont;

	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53_over);

	if(TUString::StrLen(TResource::LoadConstString(nResId)) <= 2)
		tFont.Create(FONT_NORMAL, FONT_NORMAL, FONT_STYLE_BOLD);
	else
		tFont.Create(FONT_MIDDLE, FONT_MIDDLE, FONT_STYLE_BOLD);
	pBtn = new TButton;	
	if(pBtn->Create(pWindow))
	{		
		if(ButtonPosition == TITLE_BUTTON_LEFT)
			pBtn->SetBounds(&BtnRC_Left);	
		else
			pBtn->SetBounds(&BtnRC_Right);	
		m_BtnID = pBtn->GetId();	

		pBtn->SetFont(tFont);
		pBtn->SetColor(CTL_COLOR_TYPE_FORE,RGB_COLOR_WHITE);
		pBtn->SetColor(CTL_COLOR_TYPE_BACK,RGB_COLOR_WHITE);
		pBtn->SetColor(CTL_COLOR_TYPE_FOCUS_FORE,RGB_COLOR_WHITE);
		pBtn->SetColor(CTL_COLOR_TYPE_FOCUS_BACK,RGB_COLOR_WHITE);
		
		pBtn->SetCaption(TResource::LoadConstString(nResId),FALSE);
		pBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pBtn->SetImage(pNormalBmp,0);
		pBtn->SetImage(pOverBmp,1);		
		pBtn->Show(TRUE);
	}

	return m_BtnID;
}

Int32 SetAppTitleButton(TWindow * pWindow, const TUChar* pszResTxt, int ButtonPosition)
{
	Int32 m_BtnID = 0;
	
	TRectangle BtnRC_Left(TITLE_BUTTON_X, TITLE_BUTTON_Y, TITLE_BUTTON_W, TITLE_BUTTON_H);
	TRectangle BtnRC_Right(SCR_W-TITLE_BUTTON_X-TITLE_BUTTON_W, TITLE_BUTTON_Y, TITLE_BUTTON_W, TITLE_BUTTON_H);
	
	Coord  nWidth = 0;
	Int32 nResIDNormal = 0;
	Int32 nResIDOver = 0;
	int nFontSize = 0;

	//������ʾ�ı��ĳ�������ͼ�꼰���ִ�С
	switch( TUString::StrLen(pszResTxt) )
	{
		case 2:
			{
			 nWidth = TITLE_BUTTON_W;
			nFontSize = FONT_NORMAL;
			nResIDNormal = APP_KA_ID_BITMAP_button53;
			nResIDOver = APP_KA_ID_BITMAP_button53_over;				
			}
			break;
		case 3:
			{
			 nWidth = TITLE_BUTTON_W;
			nFontSize = FONT_NORMAL;
			nResIDNormal = APP_KA_ID_BITMAP_button53;
			nResIDOver = APP_KA_ID_BITMAP_button53_over;				
			}
			break;
		case 4:
			{
			 nWidth = TITLE_BUTTON_W;
			nFontSize = FONT_NORMAL;
			nResIDNormal = APP_KA_ID_BITMAP_button53;
			nResIDOver = APP_KA_ID_BITMAP_button53_over;				
			}
			break;
		case 5:
			{
			 nWidth = TITLE_BUTTON_W;
			nFontSize = FONT_MIDDLE;
			nResIDNormal = APP_KA_ID_BITMAP_button53;
			nResIDOver = APP_KA_ID_BITMAP_button53_over;				
			}
			break;
		case 6:
		default:
			{
			 nWidth = TITLE_BUTTON_W;
			nFontSize = FONT_SMALL;
			nResIDNormal = APP_KA_ID_BITMAP_button53;
			nResIDOver = APP_KA_ID_BITMAP_button53_over;				
			}
			break;

	}

	TFont tFont;	
	const TBitmap* pNormalBmp = TResource::LoadConstBitmap(nResIDNormal);
	const TBitmap* pOverBmp = TResource::LoadConstBitmap(nResIDOver);
	tFont.Create(nFontSize, nFontSize, FONT_STYLE_BOLD);
	
	TButton* pBtn = new TButton;	
	if(pBtn->Create(pWindow))
	{		
		BtnRC_Left.SetWidth(nWidth);
		BtnRC_Right.SetWidth(nWidth);
		BtnRC_Right.SetX(SCR_W-TITLE_BUTTON_X-nWidth);
			
		if(ButtonPosition == TITLE_BUTTON_LEFT)
			pBtn->SetBounds(&BtnRC_Left);	
		else
			pBtn->SetBounds(&BtnRC_Right);
		
		m_BtnID = pBtn->GetId();	

		pBtn->SetFont(tFont);
		pBtn->SetColor(CTL_COLOR_TYPE_FORE,RGB_COLOR_WHITE);
		pBtn->SetColor(CTL_COLOR_TYPE_BACK,RGB_COLOR_WHITE);
		pBtn->SetColor(CTL_COLOR_TYPE_FOCUS_FORE,RGB_COLOR_WHITE);
		pBtn->SetColor(CTL_COLOR_TYPE_FOCUS_BACK,RGB_COLOR_WHITE);
		
		pBtn->SetCaption(pszResTxt,FALSE);
		pBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pBtn->SetImage(pNormalBmp,0);
		pBtn->SetImage(pOverBmp,1);		
		pBtn->Show(TRUE);
	}

	return m_BtnID;
}

//----------------------------------------------------------------------------

//���ÿؼ��ı���С��ɫ
TFont CtrlSetFont(TCtrl *pCtrl, Int32 nFontSize, ColorRefType nColor)
{
	TFont tFont;
	tFont.Create(nFontSize, nFontSize);
	pCtrl->SetColor(CTL_COLOR_TYPE_FORE, nColor);
	return pCtrl->SetFont(tFont);
}

//���Label�ؼ���CoolBarList, 
// pszString�����Ƕ�̬��(��Static)
// nWidth Ϊ0 -- �Զ�����
Int32 CtrlAddItemToCoolBarList_Lable(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Int32 FontSize, TUChar* pszString, ColorRefType Color)
{
	TRectangle obBtnRec(0,0,0,0);
	Int32 nLabelNameId = pListItem->AddCtrl(CTL_CLASS_LABEL, 0, 0);
	TLabel* pLabelName = static_cast<TLabel*>(pWin->GetControlPtr(nLabelNameId));
	if(nWidth == 0)
	{
		nWidth = 80;
		obBtnRec.SetRect(nX, nY, nWidth, FontSize);
		pLabelName->SetBounds(&obBtnRec);
		pLabelName->SetAutoSize(TRUE);

		CtrlSetFont((TCtrl*)pLabelName, FontSize, Color);
		pLabelName->SetCaption(pszString,FALSE);
	}
	else
	{
		obBtnRec.SetRect(nX, nY, nWidth, FontSize+6);	//�����߶�,��ֹ����ײ����ض�
		pLabelName->SetBounds(&obBtnRec);
		pLabelName->SetAutoSize(FALSE);
		pLabelName->SetScrollMode(lsmNone);

		TFont tFont;
		tFont.Create(FontSize, FontSize);
		ShowAsShort((TCtrl *)pLabelName, pszString, tFont);
		pLabelName->SetFont(tFont);
		pLabelName->SetColor(CTL_COLOR_TYPE_FORE, Color);
	}

	pLabelName->SetEnabled(FALSE);
	
	return nLabelNameId;
}


//���Button�ؼ���CoolBarList, 
// pszString�����Ƕ�̬��(��Static)
// nWidth Ϊ0 -- �Զ�����
Int32 CtrlAddItemToCoolBarList_Button(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Int32 nHeight, TUChar* pszString)
{
	TRectangle obBtnRec(0,0,0,0);
	Int32 nButtonId = pListItem->AddCtrl(CTL_CLASS_BUTTON, 20, 5);
	TButton* pButton = static_cast<TButton*>(pWin->GetControlPtr(nButtonId));

	obBtnRec.SetRect(nX, nY, nWidth, nHeight);
	pButton->SetBounds(&obBtnRec);
	pButton->SetEnabled(TRUE);
	pButton->SetCaption(pszString,FALSE);
	return nButtonId;
}

//���Image�ؼ���CoolBarList, 
// pszString�����Ƕ�̬��(��Static)
// nWidth Ϊ0 -- �Զ�����
Int32 CtrlAddItemToCoolBarList_Image(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Int32 nHeight, TBitmap * pBmp)
{
	TRectangle obBtnRec(0,0,0,0);
	Int32 nImageId = pListItem->AddCtrl(CTL_CLASS_IMAGE, 0, 0);
	TImage* pImage = static_cast<TImage*>(pWin->GetControlPtr(nImageId));

	obBtnRec.SetRect(nX, nY, nWidth, nHeight);
	pImage->SetBounds(&obBtnRec);
	pImage->SetBitmap(pBmp);
	pImage->SetEnabled(TRUE);
	return nImageId;
}

//���RichView�ؼ���CoolBarList
//nHeight -- ��������,RichView�ؼ��ĸ߶�
Int32 CtrlAddItemToCoolBarList_RichView(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Coord* nHeight, Int32 FontSize, TUChar* pszString, ColorRefType Color, Boolean bEnable )
{
	TRectangle Rc_Temp;
	TRectangle obBtnRec(0,0,0,0);
	Int32 nRichViewId = pListItem->AddCtrl(CTL_CLASS_RICHVIEW, 0, 0);
	TRichView* pRichView = static_cast<TRichView*>(pWin->GetControlPtr(nRichViewId));
	obBtnRec.SetRect(nX, nY, nWidth, *nHeight);
	pRichView->SetBounds(&obBtnRec);
	pRichView->SetFrameWidth(0);
	CtrlSetFont((TCtrl*)pRichView, FontSize, Color);

	
	//��ʱ�ɵ����ֻ�����е�
	if(bEnable == TRUE)
		{
		pRichView->SetEnabled(TRUE);
		pRichView->SetMaxVisibleLines(1, TRUE);
		pRichView->SetWordWrapAttr(TRUE);
		pRichView->SetColor(CTL_COLOR_TYPE_BACK, LTBLUE);
		pRichView->SetCaption(pszString,FALSE);
		}
	else
		{
		pRichView->SetCaption(pszString,FALSE);
		pRichView->SetEnabled(FALSE);
		pRichView->SetMaxVisibleLines(pRichView->GetLinesCount(), TRUE);
		pRichView->SetWordWrapAttr(TRUE);
		}
	
	pRichView->SetTransparent(TRUE);
	pRichView->SetScrollBarMode(CTL_SCL_MODE_NONE);
	pRichView->GetBounds(&Rc_Temp);
	
	*nHeight = Rc_Temp.Height();

	return nRichViewId;
}

//���Mask_Button�ؼ���CoolBarList
Int32 CtrlAddItemToCoolBarList_MaskButton(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pImage, TBitmap * pBackImage)
{
	TRectangle obBtnRec(0,0,0,0);
	Int32 nMaskButtonId = pListItem->AddCtrl(CTL_CLASS_MASK_BUTTON, 0, 0);
	TMaskButton* pMaskButton = static_cast<TMaskButton*>(pWin->GetControlPtr(nMaskButtonId));
	
	obBtnRec.SetRect(nX, nY, nWidth, nHeight);
	pMaskButton->SetBounds(&obBtnRec);

	pMaskButton->SetImage(pImage, (nWidth - pImage->GetWidth())/2, (nHeight - pImage->GetHeight())/2 );
	pMaskButton->SetBackImage(pBackImage, (nWidth - pBackImage->GetWidth())/2, (nHeight - pBackImage->GetHeight())/2 );

	return nMaskButtonId;
}


//���Mask_Button�ؼ���Win
Int32 CtrlAddItemToWin_MaskButton(TWindow*pWin, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pImage, TBitmap * pImageSel)
{
	TMaskButton* pMaskButton = new TMaskButton();
	Int32 nMaskButtonId = 0;
	
	if(pMaskButton->Create(pWin))
	{
		TRectangle obBtnRec(0,0,0,0);

		nMaskButtonId=pMaskButton->GetId();
		obBtnRec.SetRect(nX, nY, nWidth,  nHeight);
		pMaskButton->SetBounds(&obBtnRec);
		pMaskButton->SetImage(pImage, (nWidth - pImage->GetWidth())/2, (nHeight - pImage->GetHeight())/2 );
		pMaskButton->SetSelImage(pImageSel,(nWidth - pImageSel->GetWidth())/2,(nHeight - pImageSel->GetHeight())/2);		
		pMaskButton->SetEnabled(TRUE);
	}
	
	return nMaskButtonId;
}

Int32 CtrlAddItemToWin_Edit(TWindow*pWin, Coord nX, Coord nY, Coord nWidth, Coord nHeight)
{
	TEdit* pEdit = new TEdit();
	Int32 nEditId = 0;
	
	if(pEdit->Create(pWin))
	{
		TRectangle obBtnRec(0,0,0,0);

		nEditId=pEdit->GetId();
		obBtnRec.SetRect(nX, nY, nWidth,  nHeight);
		pEdit->SetBounds(&obBtnRec);

		pEdit->SetMaxChars(20);
		pEdit->SetUnderline(TRUE);
	}
	
	return nEditId;
}

Int32 CtrlAddItemToWin_Image(TWindow*pWin, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pBmp)
{
	TImage* pImage = new TImage();
	Int32 nImageId = 0;
	
	if(pImage->Create(pWin))
	{
		TRectangle obBtnRec(0,0,0,0);

		nImageId=pImage->GetId();
		obBtnRec.SetRect(nX, nY, nWidth, nHeight);
		pImage->SetBounds(&obBtnRec);
		pImage->SetBitmap(pBmp);
		pImage->SetEnabled(TRUE);
	}
	
	return nImageId;
}

Int32 CtrlAddItemToWin_Label(TWindow*pWin, Coord nX, Coord nY, Coord nWidth, Int32 FontSize, TUChar* pszString, ColorRefType Color)
{
	TLabel* pLabel = new TLabel();
	Int32  nLabelID = 0;

	if(pLabel->Create(pWin))	
	{
		TRectangle obBtnRec(0,0,0,0);
		if(nWidth == 0)
		{
			nWidth = 80;
			obBtnRec.SetRect(nX, nY, nWidth, FontSize);
			pLabel->SetBounds(&obBtnRec);
			pLabel->SetAutoSize(TRUE);

			CtrlSetFont((TCtrl*)pLabel, FontSize, Color);
			pLabel->SetCaption(pszString,FALSE);
		}
		else
		{
			obBtnRec.SetRect(nX, nY, nWidth, FontSize);
			pLabel->SetBounds(&obBtnRec);
			pLabel->SetAutoSize(FALSE);
			pLabel->SetScrollMode(lsmNone);

			TFont tFont;
			tFont.Create(FontSize, FontSize);
			ShowAsShort((TCtrl *)pLabel, pszString, tFont);
			pLabel->SetFont(tFont);
			pLabel->SetColor(CTL_COLOR_TYPE_FORE, Color);
		}
	}
	return nLabelID;
}

Int32 CtrlAddItemToPanel_MaskButton(TWindow*pWin, TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pImage, TBitmap * pImageSel, TBitmap * pBackImage)
{
	TMaskButton* pMaskButton = new TMaskButton();
	Int32 nMaskButtonId = 0;
	
	if(pMaskButton->Create(pPanel))
	{
		TRectangle obBtnRec(0,0,0,0);

		nMaskButtonId=pMaskButton->GetId();
		obBtnRec.SetRect(nX, nY, nWidth,  nHeight);
		pMaskButton->SetBounds(&obBtnRec);
		pMaskButton->SetImage(pImage, (nWidth - pImage->GetWidth())/2, (nHeight - pImage->GetHeight())/2 );
		pMaskButton->SetSelImage(pImageSel,(nWidth - pImageSel->GetWidth())/2,(nHeight - pImageSel->GetHeight())/2);		
		pMaskButton->SetBackImage(pBackImage, (nWidth - pBackImage->GetWidth())/2, (nHeight - pBackImage->GetHeight())/2 );
		pMaskButton->SetEnabled(TRUE);
	}
	
	return nMaskButtonId;
}

Int32 CtrlAddItemToPanel_Edit(TWindow*pWin, TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord nHeight)
{
	TEdit* pEdit = new TEdit();
	Int32 nEditId = 0;
	
	if(pEdit->Create(pPanel))
	{
		TRectangle obBtnRec(0,0,0,0);

		nEditId=pEdit->GetId();
		obBtnRec.SetRect(nX, nY, nWidth,  nHeight);
		pEdit->SetBounds(&obBtnRec);

		pEdit->SetMaxChars(20);
		pEdit->SetUnderline(TRUE);
	}
	
	return nEditId;
}

Int32 CtrlAddItemToPanel_Label(TWindow*pWin,  TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Int32 FontSize, TUChar* pszString, ColorRefType Color)
{
	TLabel* pLabel = new TLabel();
	Int32  nLabelID = 0;

	if(pLabel->Create(pPanel))	
	{
		TRectangle obBtnRec(0,0,0,0);

		nLabelID = pLabel->GetId();
		if(nWidth == 0)
		{
			nWidth = 80;
			obBtnRec.SetRect(nX, nY, nWidth, FontSize);
			pLabel->SetBounds(&obBtnRec);
			pLabel->SetAutoSize(TRUE);

			CtrlSetFont((TCtrl*)pLabel, FontSize, Color);
			pLabel->SetCaption(pszString,FALSE);
		}
		else
		{
			obBtnRec.SetRect(nX, nY, nWidth, FontSize);
			pLabel->SetBounds(&obBtnRec);
			pLabel->SetAutoSize(FALSE);
			pLabel->SetScrollMode(lsmNone);

			TFont tFont;
			tFont.Create(FontSize, FontSize);
			ShowAsShort((TCtrl *)pLabel, pszString, tFont);
			pLabel->SetFont(tFont);
			pLabel->SetColor(CTL_COLOR_TYPE_FORE, Color);
		}
	}
	return nLabelID;
}

Int32 CtrlAddItemToPanel_RichView(TWindow*pWin,  TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord* nHeight, Int32 FontSize, TUChar* pszString, ColorRefType Color)
{
	TRichView* pRichView = new TRichView();
	Int32 nRichViewId = 0;

	if(pRichView->Create(pPanel))	
	{
		nRichViewId = pRichView->GetId();
			
		TRectangle Rc_Temp;
		TRectangle obBtnRec(0,0,0,0);
		obBtnRec.SetRect(nX, nY, nWidth, *nHeight);
		pRichView->SetBounds(&obBtnRec);
		CtrlSetFont((TCtrl*)pRichView, FontSize, Color);
		pRichView->SetCaption(pszString,FALSE);

		pRichView->SetEnabled(FALSE);
		pRichView->SetWordWrapAttr(TRUE);
		pRichView->SetTransparent(TRUE);
		pRichView->SetScrollBarMode(CTL_SCL_MODE_NONE);
		pRichView->SetMaxVisibleLines(pRichView->GetLinesCount(), TRUE);
		pRichView->GetBounds(&Rc_Temp);
		
		*nHeight = Rc_Temp.Height();
	}
	return nRichViewId;
}

Int32 CtrlAddItemToPanel_Image(TWindow*pWin, TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pBmp)
{
	TImage* pImage = new TImage();
	Int32 nImageId = 0;
	
	if(pImage->Create(pPanel))
	{
		TRectangle obBtnRec(0,0,0,0);

		nImageId=pImage->GetId();
		obBtnRec.SetRect(nX, nY, nWidth, nHeight);
		pImage->SetBounds(&obBtnRec);
		pImage->SetBitmap(pBmp);
		pImage->SetEnabled(TRUE);
	}
	
	return nImageId;
}


Int32 CtrlAddItemToPanel_Button(TWindow*pWin,  TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Int32 nHeight, TUChar* pszString)
{
	TRectangle obBtnRec(0,0,0,0);
	TButton* pButton = new TButton();
	Int32 nButtonId = -1;
	if(pButton->Create(pPanel))
	{
		 nButtonId = pButton->GetId();

		obBtnRec.SetRect(nX, nY, nWidth, nHeight);
		pButton->SetBounds(&obBtnRec);
		pButton->SetEnabled(TRUE);
		pButton->SetCaption(pszString,FALSE);
	}
	return nButtonId;
}

//ͼƬ��С����,����ԭʼ����,
//OrigX/OrigY  -- ͼƬ��С
//pdx/pdy -- ��Ҫ��ʾ�������С,ͬʱ������Ĵ�С��ֵ�ڴ�
void Image_ScaleXY(Int32 OrigX, Int32 OrigY, Int32 *pdx , Int32 *pdy)
{
	if (OrigX>0 && OrigY>0 && *pdx > 0 && *pdy > 0)
	{
		if (OrigX > *pdx || OrigY > *pdy)
		{
			float rateX = (float)*pdx/OrigX;
			float rateY = (float)*pdy/OrigY;
			if(rateX < rateY)
			{
				*pdx = *pdx;
				*pdy = ((*pdx) * OrigY) /OrigX;
			}
			else
			{
				*pdx = ((*pdy) * OrigX) /OrigY;
				*pdy = *pdy;
			}
		}
		else
		{
			*pdx = OrigX;
			*pdy = OrigY;
		}
	}
}