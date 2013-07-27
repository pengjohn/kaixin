#ifndef  __KaiXinAPICommon_H__
#define  __KaiXinAPICommon_H__
#include "TG3.h"
#include "TDownload.h"
#include "TFileDownloadMrg.h"
#include "TImgData.h"
#include "TResolution.h"
#include "App_KaiXinUnicodeScript_str.h"//include for show string
#include "cUnixTime.h"
#include "TWebForm.h"
#include "gui_common.h"
#include "StrComm.h"

#include "KaiXinAPI_InitialLogin.h"
#include "KaiXinAPI_Profile.h"
#include "KaiXinAPI_FriendList.h"
#include "KaiXinAPI_ApplicationList.h"
#include "KaiXinAPI_Usercommentlist.h"
#include "KaiXinAPI_MessageCenter.h"
#include "KaiXinAPI_MessagesList.h"
#include "KaiXinAPI_GetUserInfos.h"
#include "KaiXinAPI_RecordList.h"
#include "KaiXinAPI_Edit.h"
#include "KaiXinAPI_StatusFaceList.h"
#include "KaiXinAPI_ListView.h"
#include "KaiXinAPI_DiaryList.h"
#include "KaiXinAPI_RepasteIndex.h"
#include "KaiXinAPI_CommentDetail.h"
#include "KaiXinAPI_DiaryDetail.h"
#include "KaiXinAPI_SystemMessages.h"
#include "KaiXinAPI_SendBirthdayGift.h"
#include "KaiXinAPI_BirthdayList.h"
#include "KaiXinAPI_GardenDetail.h"
#include "KaiXinAPI_More.h"
#include "KaiXinAPI_RepasteDetail.h"
#include "KaiXinAPI_Repaste_Vote.h"
#include "KaiXinAPI_WaitingBox.h"
#include "KaiXinAPI_UserInfoDetail.h"
#include "KaiXinAPI_Comment.h"
#include "KaiXinAPI_GetProfileDetail.h"
#include "KaiXinAPI_UpdateFriendsNews.h"
#include "KaiXinAPI_VoteDetail.h"
#include "KaiXinAPI_AlbumList.h"
#include "KaiXinAPI_AlbumPhoto.h"
#include "KaiXinAPI_PhotoDetail.h"
#include "KaiXinAPI_RecentNews.h"
#include "KaiXinAPI_Notice.h"
#include "KaiXinAPI_RanchDetail.h"
#include "KaiXinAPI_Comment_Detail.h"
#include "KaiXinAPI_MessageDetail.h"
#include "KaiXinAPI_OtherDetail.h"
#include "KaiXinAPI_PokeList.h"
#include "KaiXinAPI_SettingsForm.h"
#include "KaiXinAPI_GardenList.h"
#include "KaiXinAPI_RanchList.h"
#include "TFeedBackForm.h"
#include "KaiXinAPI_AboutForm.h"

extern TFileDownloadMgr*  g_pFileDown;
extern IDownLoad *		g_pDownload;
//用于下载辅助数据,如日志数量等不需要bNeedWaitingBox的
extern TFileDownloadMgr*  g_pFileDownEx;
extern IDownLoad *		g_pDownloadEx;

//设置URL参数
extern int Set_Url_Params(Kx_AccessType accessType, char* ParamName, char* ParamValue);
extern int Get_Url_Params(Kx_AccessType accessType, char* ParamName, char** ParamValue);
//获得完整的URL串
extern int Url_Generate(Kx_AccessType accessType, char** ppURL);
//获得Json文件名
extern char* KX_GetFileName(Kx_AccessType accessType);
//Json文件解析
extern int KaiXinAPI_JsonParse(Kx_AccessType accessType, void**Response);
//Json文件解析是否正确(Json中的Ret != 1也返回FALSE)
extern Boolean KaiXinAPI_JsonParse_bSuccess(Kx_AccessType accessType, TUChar * errorinfo = NULL);
//获取用户登录设置( 配置文件->KaiXinUserInfo )
extern int KaiXinAPI_GetConfig(void);
//保存用户登录设置( KaiXinUserInfo ->配置文件)
extern int KaiXinAPI_SetConfig(void);
//下载各API对应的Json
extern int KaiXinAPICommon_Download(Kx_AccessType  accessType, Int32 in_nHwndId = 0 , Int32 in_nCtrlId = 0, Int32 in_nParam = 0);
//下载图片,输入参数为FormID及一个nParam( 下载完成后会返回这个nParam)
extern int KaiXinAPICommon_DownloadPhoto(char* pURL, Int32 in_nHwndId,Int32 in_nParam );
//下载完成后,需要调用这个清除下载队列中对用的数据并开始下一下载
extern int KaiXinAPICommon_DownloadComplete(TAListElement*  pElement);
//取消指定类型的下载
int KaiXinAPICommon_DownloadCancelByAccessType(Kx_AccessType  accessType);
int KaiXinAPICommon_DownloadCancelByHwndId(Int32 nHwndId);
//取消全部下载
int KaiXinAPICommon_DownloadCancelAll(void);
//上传图片
int KaiXinAPICommon_PostPhoto(const TUChar* pszFilePath, const TUChar* pszTitle, Int32 in_nHwndId);

//从文件中读取TBitmap, 调用者需要手动释放
extern TBitmap* LoadImgByPath(const TUChar* pszPath);
//传入Url,从磁盘cache读取文件,如果cache没有则返回NULL
extern TBitmap* LoadImgByUrl(char* pURL);
//获得按钮的大小
extern int GetTitleButtonRect(Coord*  nX,  Coord*  nY,  Coord*  nWidth,  Coord*  nHeight );
//获得标题的大小
extern int GetTitleLabelRect(const TUChar* pszTitle, Coord*  nX,  Coord*  nY,  Coord*  nWidth,  Coord*  nHeight );
//url参数编码为%xx格式; 由调用者释放
extern char* urlEncode(char* pszText);
//Url下载后保存的文件名(带路径), 由调用者释放
extern TUChar* FilePathFromUrl(char* pURL);
//获得Api是否需要App_Kaixin统一处理(FALSE即由各Form自行处理)
extern Boolean GetApiHandle(Kx_AccessType accessType);
//获取API是否需要显示等待动画
Boolean GetApiNeedWaitingBox(Kx_AccessType accessType);

extern Int32 SetAppExitButton(TWindow * pWindow);
extern Int32 SetAppBackButton(TWindow * pWindow);
extern Int32 SetAppRefreshButton(TWindow * pWindow);
extern Int32 SetAppWriteButton(TWindow * pWindow);
extern Int32 SetAppLoginButton(TWindow * pWindow);
//获得Html格式数据的文件名, 需要调用释放
char* KX_GetHtmlContentFileName(Kx_AccessType accessType);
//生成Html文件
extern int MakeHtmlFile(Kx_AccessType accessType, char* pszContent);
//本地html文件的url格式, 调用释放
extern TUChar* GetHtmlFileUrl(Kx_AccessType accessType);

extern Boolean CheckCacheIsEnough(void);

extern Int32 PopBox_UploadPhoto(TApplication* pApp, Int32 nHwndId);

extern Int32 KaiXin_Log_Init(void);
extern Int32 KaiXin_Log(char* logTxt);
#endif
