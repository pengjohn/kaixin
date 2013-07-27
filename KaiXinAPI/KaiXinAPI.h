//KaiXinAPI.h
#ifndef  __KaiXinAPI_H__
#define  __KaiXinAPI_H__
#include "TG3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "TResolution.h"


#define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))
#define STRCPY_Ex(des, soure)\
	do\
			{\
			memset(des, 0, sizeof(des));\
			if(soure == NULL)	\
			strcpy(des, "");\
				else	\
				strncpy(des, soure, sizeof(des)-1);\
			}\
			while(0)

enum
{
	eSucceed = 1,
	eFailed = -1,
};


enum
{
	MSG_POST_THREAD_NOTIFY = EVENT_FirstUser + 1000,
	MSG_SWITCHFORM_UPDATE_FRIENDS_NEWS,	//动态
	MSG_SWITCHFORM_FRIEND_LIST,	//好友列表
	MSG_SWITCHFORM_PROFILE,		//我的地盘
	MSG_SWITCHFORM_APPLIST,		//组件
	MSG_SWITCHFORM_MORE,		//更多
	MSG_LOGOUT,					//登出
	MSG_EXIT,						//退出
	MSG_FORM_UPDATE,				//更新form
	MSG_SWITCHFORM_MESSAGE_CENTER,		//消息中心
};

//#define assert(bCondition) if (!(bCondition)) *(int*)NULL=0
#define assert(bCondition)


#define KAIXIN_SKEY			"bppvzyg2jpqnjLBvnHhjN1Ko5PaFDf4d"
#define KAIXIN_FOLDER		"kaixin/"

#define KAIXIN_URLPATH_LENGTH		(1024)
#define KAIXIN_STATUS_LENTH		(1024)



//最大好友数
#define FRIEND_MAX_NUM			(500)		

//
#define ERROR_INFO_LEN			(100)

//AppID (keynumber)
typedef enum
{
	KX_AccessTypeStart = 0,

	KX_InitialLogin,			//Initial Login	
	KX_AutoLogin,				//Auto Login
	/*新API取消*/	KX_Logout,					//Logout
	KX_Profile,					//Profile
	KX_GetStatus,				//GetStatus(Profile引申)

	KX_UpdateFriendsNews, 		// Update Friends News
	KX_RecentNews,				//获取个人最近动态(Update Friends News 引申)

	KX_FriendList,       		//Friend list
	KX_GetFriendCount,			//获取好友数量(Friend list 引申)

	KX_GetUserInfos,			//Get usr infos
	KX_GetProfileDetail,		//Get usr infos 引申出的GetProfileDetail

	KX_FriendsPhoto,			//Friends Photo

	KX_AlbumList,				//Album list
	KX_GetAlbumCount,			//获取相册数量，由Album list 引申出的KX_GetAlbumCount 
	KX_AlbumPhoto,				//Album Photo
	KX_AlbumPhotoFromNews,		//从动态列表中获取专辑照片，由Album Photo 引申出的KX_AlbumPhotoFromNews

	KX_UpdateStatus,			//Update Status
	KX_UploadPhoto,				//Upload Photo
	KX_WriteRecord,				//Write Record	

	KX_AcceptFriendRequest,		//Accept friend request
	KX_RefuseFriendRequest,		//Resuse friend request

	KX_Notice,					//新消息数据(Message Center引申)
	KX_MessageCenter,			//Message Center
	KX_MessagesList,			//Messages'list
	KX_SentMessagesList,		//Sended Messages'list
	KX_MessageDetail,			//Message detail
	//	KX_ReplyAMessage,			//Reply a message
	KX_SendAMessage,			//Send a message
	KX_DeleteMessage,			//Delete message

	KX_ReceivedCommentsList,	//Received comments' List
	KX_RepasteCommentsList,	//Received comments' List
	KX_ReceivedAnObjectComments,	//Received an Object's comments
	KX_ReceivedRepasteComments,	//Received Repaste's comments
	KX_ReceivedDiaryComments,	//Received Diary's comments
	KX_ReceivedRecordComments,	//Received Record's comments
	KX_ReceivedStateComments,	//Received State's comments
	KX_CommentDetail,			//Comment detail
	KX_PostComment,				//post comment
	KX_ReplyComment,			//Reply comment
	KX_SentCommentsList,		//Sent comments' list
	KX_SentCommentDetail,		//Sent comment detail
	KX_DeleteComment,			//Delete comment
	KX_FriendsCommentList,		//Friends comment list
	KX_ReceivedUserCommentsList,//Received user comments's list
	KX_UserCommentDetail,		//User comment detail
	KX_SentUserCommentsList,	//Sent user comments' list
	KX_SentUserCommentDetail,	//Sent user comment detail

	KX_SystemMessage,			//System messages

	KX_BirthdayList,			//BirthdayList
	KX_SendBirthdayGift,		//Send birthday gift

	KX_PokesList,				//Pokes list
	KX_SendPoke,				//Send poke
	KX_PostUp,					//Post up
	KX_AppNews,					//App news
	KX_VoteDetail,				//Vote detail
	/*新API取消*/	KX_PostVote,				//Post vote

	KX_DiaryDetail,				//Diary detail
	/*新API取消*/	KX_PostDiary,				//Post diary
	/*新API取消*/	KX_EditDiary,				//Edit diary
	/*新API取消*/	KX_UploadDiarysPhoto,		//Upload diarys' photo

	KX_RepasteDetail,			//repaste detail//获取转贴信息
	KX_RefreshVote,			//repaste detail//获取操作后的转贴信息
	KX_RefreshTag,			//repaste detail//获取操作后的转贴信息
	/*新API取消*/	KX_PostRepaste,				//post repaste
	/*新API取消*/	KX_PostRepastesVote,		//Post repaste's vote//发表转贴互动观点

	/*新API取消*/	KX_PostTag,					//post tag
	KX_InviteCode,				//invite code

	/*新API取消*/	KX_RepasteIndex,			//Repaste index
	/*新API取消*/	KX_RepasteIndexMore,			//Repaste index
	
	/*新API取消*/	KX_GetRepasteCount,			//获取转帖数量，由Repaste index 引申出的KX_GetRepasteCount 

	/*新API取消*/	KX_ApplicationList,			//application list
	/*新API取消*/	KX_TruthDetail,				//truth detail
	/*新API取消*/	KX_ExchangeTruth,			//exchange truth

	/*新API取消*/	KX_FaceList,				//状态表情更新列表
	KX_GiftList,				//gift list

	KX_RecordList,				//record list
	KX_GetRecordCount,			//获取记录数量，由Record list 引申出的KX_GetRecordCount 

	KX_DiaryList,				//diary list
	KX_GetDiaryCount,			//获取日记数量，由Diary list 引申出的KX_GetDiaryCount 

	/*新API取消*/	KX_UpgradeInfos,			//获取客户升级信息
	/*新API取消*/	KX_Init,					//激活客户端
	/*新API取消*/	KX_AddFriends,				//添加好友请求

	//游戏接口
	KX_GardenDetail,			//Garden's detail
	KX_GardenList,				//Garden list
	KX_GardenHarvest,			//harvest plants //收获，偷作物
	KX_RanchDetail,				//Ranch's detail
	KX_RanchList,				//Ranch lsit //有可偷产品的好友列表
	KX_RanchHarvest,			//harvest animal//收获，偷 动物/产品
	KX_Product,					//product //生产

	KX_More, 				//more  app 没有对应的api

	/*need to add more type here*/
	KX_AccessTypeEnd,

	KX_PhotoDownload,			//专门用于图片下载
} Kx_AccessType;

typedef struct
{
	char paramName[32]; //至少需要多留一个字符
	char paramValue[4096]; //TODO, 需要扩展大小
}sUrlparams;


#define WAITING_BOX_TRUE	(TRUE)
#define WAITING_BOX_FALSE	(FALSE)


typedef struct
{
	Kx_AccessType	nType;
	Boolean			bHandle;			//是否需要App_Kaixin统一处理
	Boolean			bNeedWaitingBox;	//是否需要等待动画
	char			FilePath[32];
	char			Address[KAIXIN_URLPATH_LENGTH];
	sUrlparams		*Params;
	int 				nParamsNum;

}sKxAppUrl;

#define NOTICE_TYPE_ALL					(0)	//全部
#define NOTICE_TYPE_MESSAGE			(1)	//短消息
#define NOTICE_TYPE_USER_COMMENT		(2)	//留言
#define NOTICE_TYPE_POST_COMMENT		(3)	//评论
#define NOTICE_TYPE_SYS_MESSAGE		(4)	//系统消息
#define NOTICE_TYPE_REPLY_USER_COMMENT	(5)	//留言回复
#define NOTICE_TYPE_REPLY_POST_COMMENT	(6)	//评论回复

//用户信息,需要保存用于自动登录
typedef struct
{
	Boolean	bAutoLogin;
	Boolean	bSavePwd;
	Boolean	bShowPwd;
	char email[128];
	char password[32];
	char uid[16];
	char verify[128];
	char wapverify[128];
	char logoPath[256];//头像文件路径
	char status[KAIXIN_STATUS_LENTH];//状态内容	
	int	NoticeCount[7];
	Boolean  bLoadImage;
}tUserInfo;


extern tUserInfo	KaiXinUserInfo;
extern Int32		gHwndId_KaiXinApp[KX_AccessTypeEnd];//保存开心网各个窗口的ID
extern char* KX_GetFileName(Kx_AccessType accessType);
#endif
