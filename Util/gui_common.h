//gui_common.h
#ifndef  __gui_common_H__
#define  __gui_common_H__

#include "TG3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TResolution.h"


#define RGB_COLOR_GRAY					   (RGB(150, 150, 150))
#define RGB_COLOR_BLACK 				   (RGB(1, 1, 1))
#define RGB_COLOR_YELLOW				   (RGB(255, 255, 0))
#define RGB_COLOR_BLUE					   (RGB(0, 0, 255))
#define RGB_COLOR_LIGHTBLUE				(RGB(67, 67, 135))
#define RGB_COLOR_GREEN 				   (RGB(0, 128, 0))
#define RGB_COLOR_RED					   (RGB(255, 0, 0))
#define RGB_COLOR_PURPLE					(RGB(128, 0, 255))
#define RGB_COLOR_LIGHT_PURPLE			(RGB(128, 128, 255))
#define RGB_COLOR_AQUA					   (RGB(0, 255, 255))
#define RGB_COLOR_DISABLE				   (RGB(150, 150, 150))
#define RGB_COLOR_WHITE				   (RGB(254, 254, 254))
#define RGB_COLOR_ORANGE				   (RGB(255, 68, 1))
#define RGB_COLOR_LIGHTGRAY                      (RGB(204, 204, 204))
//
#define RGB_COLOR_INFO_BACKGROUND         (RGB(253, 255, 206))
#define RGB_COLOR_FORM_BACKGROUND         (RGB(254, 254, 254))

#define LCD_HVGA   	0  //LCD(320*480)
#define LCD_WVGA   	1  //LCD(480*800)

#if defined(UPHONE_HVGA)  
#define LCD_SIZE		LCD_HVGA
#elif defined(UPHONE_WVGA)  
#define LCD_SIZE		LCD_WVGA
#else  
#error resolution  
#endif 

#if(LCD_SIZE == LCD_HVGA )
#elif(LCD_SIZE == LCD_WVGA )
#endif

#if(LCD_SIZE == LCD_HVGA )
#define SCR_W		(320)
#define SCR_H		(480)
#define STATUSBAR_H	(24)
#define TITLEBAR_H	(44)
#define TOP_TAB_H	(44)
#define BOTTOM_TAB_H	(44)

#define BUTTON_X	(5)
#define BUTTON_Y	(5)
#define BUTTON_W	(53)
#define BUTTON_H	(35)

#define BUTTON_MIDDLE_W	(98)
#define BUTTON_MIDDLE_H	(36)

#define PHOTO_MASK_W		(58)
#define PHOTO_MASK_H		(58)
#define PHOTO_W		(50)
#define PHOTO_H		(50)

#define KEYBOARD_H  (208)

//title button
#define TITLE_BUTTON_X	(5)
#define TITLE_BUTTON_W	(60)
#define TITLE_BUTTON_H	(30)
#define TITLE_BUTTON_Y	((TITLEBAR_H - TITLE_BUTTON_H)/2)

//字体大小
#define FONT_LARGE		(18)
#define FONT_NORMAL	(16)
#define FONT_MIDDLE		(14)
#define FONT_SMALL		(12)

#elif(LCD_SIZE == LCD_WVGA )
#define SCR_W		(480)
#define SCR_H		(800)
#define STATUSBAR_H	(36)
#define TITLEBAR_H	(66)
#define TOP_TAB_H	(66)
#define BOTTOM_TAB_H	(66)

#define BUTTON_X	(5)
#define BUTTON_Y	(5)
#define BUTTON_W	(80)
#define BUTTON_H	(52)

#define BUTTON_MIDDLE_W	(147)
#define BUTTON_MIDDLE_H	(54)

#define PHOTO_MASK_W		(87)
#define PHOTO_MASK_H		(87)
#define PHOTO_W		(75)
#define PHOTO_H		(75)

#define KEYBOARD_H  (312)

//title button
#define TITLE_BUTTON_X	(5)
#define TITLE_BUTTON_W	(90)
#define TITLE_BUTTON_H	(45)
#define TITLE_BUTTON_Y	((TITLEBAR_H - TITLE_BUTTON_H)/2)

//字体大小
#define FONT_LARGE		(28)
#define FONT_NORMAL	(24)
#define FONT_MIDDLE		(20)
#define FONT_SMALL		(16)
#endif

#define BOTTOM_TAB_NUM	(5)
#define BOTTOM_TAB_W	(SCR_W/BOTTOM_TAB_NUM)


//时间颜色
#define COLOR_DATE_TIME			RGB_COLOR_GRAY

#if(LCD_SIZE == LCD_HVGA )
//coolbailist位置
#define RC_LIST_LARGE					(&TRectangle(-5,-3,330,46))
#define RC_LIST_NORMAL					(&TRectangle(10,0,300,46))
#define RC_LIST_SMALL					(&TRectangle(20,0,280,46))

//coolbar list 高度
#define COOLBAR_LIST_HEIGHT			(36)

#elif(LCD_SIZE == LCD_WVGA )
//coolbailist位置
#define RC_LIST_LARGE					(&TRectangle(-5, -3, 490, 46))
#define RC_LIST_NORMAL					(&TRectangle(10, 0, 460, 46))
#define RC_LIST_SMALL					(&TRectangle(20, 0, 440, 46))

//coolbar list 高度
#define COOLBAR_LIST_HEIGHT			(54)

#endif

#define FONT_APP_TITLE					(FONT_LARGE)
#define FONT_LARGE_NAME				(FONT_LARGE)

#define FONT_NAME						(FONT_NORMAL)
#define FONT_TITLE						(FONT_NORMAL)
#define FONT_CONTENT					(FONT_NORMAL)
#define FONT_CONTENT_DETAIL			(FONT_MIDDLE)
#define FONT_STATE						(FONT_MIDDLE)
#define FONT_MENU_ITEM					(FONT_MIDDLE)
#define FONT_OTHER_INFO				(FONT_SMALL)

#define FONT_LARGE_BUTTON_CAPTION		(FONT_LARGE)
#define FONT_BUTTON_CAPTION				(FONT_MIDDLE)
#define FONT_SMALL_BUTTON_CAPTION		(FONT_SMALL)

enum
{
	TITLE_BUTTON_LEFT = 0,
	TITLE_BUTTON_RIGHT,
};

//底部Tab的项个数
#define BOTTOM_TAB_NUM	(5)
typedef struct
{
	Int32  nCtrID[BOTTOM_TAB_NUM];
}sBottomTabCtrID;

typedef struct
{
	Int32 ResID_Normal;
	Int32 ResID_Down;
	Int32 ResID_Title;
}sTabButtonItem;

//底部Option的项个数(最大)
#define BOTTOM_OPTION_NUM	(5)
typedef struct
{
	Int32  nCtrID[BOTTOM_OPTION_NUM];
}sBottomOptionCtrID;

typedef struct
{
	Int32 ResID_Button_Normal;
	Int32 ResID_Button_Selected;
	Int32 ResID_Icon_Normal;
	Int32 ResID_Icon_Selected;
	Int32 ResID_Title;
}sBottomOptionItem;

typedef struct
{
	TUChar pszName[32];			//名字
	TUChar pszContent[40960];	//内容
	TUChar pszTime[64];			//时间
	Int32    OptionButtonResID;	//按钮文本资源ID
	Int32    FlagIconResID;		//小图标资源ID
	Coord   nY;					//起始Y坐标
	Boolean bLeft;				//是否头像靠左
	TBitmap * pImage;			//头像Image	
}tBubbleDialogItemData;

extern Int32 GetShowAllStringWidth(TUChar* pCaptionString, TFont objFontType);
extern Int32 GetShowAllStringWidthEx(TUChar* pCaptionString, Int32 FontSize);
extern void  ShowAsShort(TCtrl *pTCtrl, TUChar* pCaptionString, TFont objFontType);
extern Int32 SetAppTilte(TWindow * pWindow, Int32 TitleStringResId = 0,  TUChar* pTitleString = NULL, ColorRefType Color = RGB_COLOR_WHITE, Int32 nFontSize = FONT_APP_TITLE);
extern Int32 SetAppBitmapButton(TWindow * pWindow, Int32 NomalBtnID, Int32 OverBtnID);
extern Int32 SetAppTitleButton(TWindow * pWindow, Int32 nResId, int ButtonPosition);
extern Int32 SetAppTitleButton(TWindow * pWindow, const TUChar* pszResTxt, int ButtonPosition);

extern TFont CtrlSetFont(TCtrl *pCtrl, Int32 nFontSize, ColorRefType nColor = RGB_COLOR_BLACK);

extern Int32 CtrlAddItemToCoolBarList_Lable(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Int32 FontSize, TUChar* pszString, ColorRefType Color = RGB_COLOR_BLACK);
extern Int32 CtrlAddItemToCoolBarList_RichView(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Coord* nHeight, Int32 FontSize, TUChar* pszString, ColorRefType Color = RGB_COLOR_BLACK, Boolean bEnable = FALSE);
extern Int32 CtrlAddItemToCoolBarList_MaskButton(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pImage, TBitmap * pBackImage);
extern Int32 CtrlAddItemToCoolBarList_Button(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Int32 nHeight, TUChar* pszString);
extern Int32 CtrlAddItemToCoolBarList_Image(TWindow*pWin,  TBarListItem* pListItem, Coord nX, Coord nY, Coord nWidth, Int32 nHeight, TBitmap * pBmp);

extern Int32 CtrlAddItemToPanel_Edit(TWindow*pWin, TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord nHeight);
extern Int32 CtrlAddItemToPanel_MaskButton(TWindow*pWin, TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pImage, TBitmap * pImageSel, TBitmap * pBackImage);
extern Int32 CtrlAddItemToPanel_Label(TWindow*pWin,  TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Int32 FontSize, TUChar* pszString, ColorRefType Color = RGB_COLOR_BLACK);
extern Int32 CtrlAddItemToPanel_RichView(TWindow*pWin,  TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord* nHeight, Int32 FontSize, TUChar* pszString, ColorRefType Color = RGB_COLOR_BLACK);
extern Int32 CtrlAddItemToPanel_Image(TWindow*pWin, TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pBmp);
extern Int32 CtrlAddItemToPanel_Button(TWindow*pWin,  TPanel* pPanel, Coord nX, Coord nY, Coord nWidth, Int32 nHeight, TUChar* pszString);

extern Int32 CtrlAddItemToWin_MaskButton(TWindow*pWin,  Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pImage, TBitmap * pImageSel);
extern Int32 CtrlAddItemToWin_Label(TWindow*pWin, Coord nX, Coord nY, Coord nWidth, Int32 FontSize, TUChar* pszString, ColorRefType Color = RGB_COLOR_BLACK);
extern Int32 CtrlAddItemToWin_Edit(TWindow*pWin,  Coord nX, Coord nY, Coord nWidth, Coord nHeight);
extern Int32 CtrlAddItemToWin_Image(TWindow*pWin, Coord nX, Coord nY, Coord nWidth, Coord nHeight, TBitmap * pBmp);

extern void Image_ScaleXY(Int32 OrigX, Int32 OrigY, Int32 *pdx , Int32 *pdy);
#endif
