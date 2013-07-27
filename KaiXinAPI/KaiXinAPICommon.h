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
//�������ظ�������,����־�����Ȳ���ҪbNeedWaitingBox��
extern TFileDownloadMgr*  g_pFileDownEx;
extern IDownLoad *		g_pDownloadEx;

//����URL����
extern int Set_Url_Params(Kx_AccessType accessType, char* ParamName, char* ParamValue);
extern int Get_Url_Params(Kx_AccessType accessType, char* ParamName, char** ParamValue);
//���������URL��
extern int Url_Generate(Kx_AccessType accessType, char** ppURL);
//���Json�ļ���
extern char* KX_GetFileName(Kx_AccessType accessType);
//Json�ļ�����
extern int KaiXinAPI_JsonParse(Kx_AccessType accessType, void**Response);
//Json�ļ������Ƿ���ȷ(Json�е�Ret != 1Ҳ����FALSE)
extern Boolean KaiXinAPI_JsonParse_bSuccess(Kx_AccessType accessType, TUChar * errorinfo = NULL);
//��ȡ�û���¼����( �����ļ�->KaiXinUserInfo )
extern int KaiXinAPI_GetConfig(void);
//�����û���¼����( KaiXinUserInfo ->�����ļ�)
extern int KaiXinAPI_SetConfig(void);
//���ظ�API��Ӧ��Json
extern int KaiXinAPICommon_Download(Kx_AccessType  accessType, Int32 in_nHwndId = 0 , Int32 in_nCtrlId = 0, Int32 in_nParam = 0);
//����ͼƬ,�������ΪFormID��һ��nParam( ������ɺ�᷵�����nParam)
extern int KaiXinAPICommon_DownloadPhoto(char* pURL, Int32 in_nHwndId,Int32 in_nParam );
//������ɺ�,��Ҫ�������������ض����ж��õ����ݲ���ʼ��һ����
extern int KaiXinAPICommon_DownloadComplete(TAListElement*  pElement);
//ȡ��ָ�����͵�����
int KaiXinAPICommon_DownloadCancelByAccessType(Kx_AccessType  accessType);
int KaiXinAPICommon_DownloadCancelByHwndId(Int32 nHwndId);
//ȡ��ȫ������
int KaiXinAPICommon_DownloadCancelAll(void);
//�ϴ�ͼƬ
int KaiXinAPICommon_PostPhoto(const TUChar* pszFilePath, const TUChar* pszTitle, Int32 in_nHwndId);

//���ļ��ж�ȡTBitmap, ��������Ҫ�ֶ��ͷ�
extern TBitmap* LoadImgByPath(const TUChar* pszPath);
//����Url,�Ӵ���cache��ȡ�ļ�,���cacheû���򷵻�NULL
extern TBitmap* LoadImgByUrl(char* pURL);
//��ð�ť�Ĵ�С
extern int GetTitleButtonRect(Coord*  nX,  Coord*  nY,  Coord*  nWidth,  Coord*  nHeight );
//��ñ���Ĵ�С
extern int GetTitleLabelRect(const TUChar* pszTitle, Coord*  nX,  Coord*  nY,  Coord*  nWidth,  Coord*  nHeight );
//url��������Ϊ%xx��ʽ; �ɵ������ͷ�
extern char* urlEncode(char* pszText);
//Url���غ󱣴���ļ���(��·��), �ɵ������ͷ�
extern TUChar* FilePathFromUrl(char* pURL);
//���Api�Ƿ���ҪApp_Kaixinͳһ����(FALSE���ɸ�Form���д���)
extern Boolean GetApiHandle(Kx_AccessType accessType);
//��ȡAPI�Ƿ���Ҫ��ʾ�ȴ�����
Boolean GetApiNeedWaitingBox(Kx_AccessType accessType);

extern Int32 SetAppExitButton(TWindow * pWindow);
extern Int32 SetAppBackButton(TWindow * pWindow);
extern Int32 SetAppRefreshButton(TWindow * pWindow);
extern Int32 SetAppWriteButton(TWindow * pWindow);
extern Int32 SetAppLoginButton(TWindow * pWindow);
//���Html��ʽ���ݵ��ļ���, ��Ҫ�����ͷ�
char* KX_GetHtmlContentFileName(Kx_AccessType accessType);
//����Html�ļ�
extern int MakeHtmlFile(Kx_AccessType accessType, char* pszContent);
//����html�ļ���url��ʽ, �����ͷ�
extern TUChar* GetHtmlFileUrl(Kx_AccessType accessType);

extern Boolean CheckCacheIsEnough(void);

extern Int32 PopBox_UploadPhoto(TApplication* pApp, Int32 nHwndId);

extern Int32 KaiXin_Log_Init(void);
extern Int32 KaiXin_Log(char* logTxt);
#endif
