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
	MSG_SWITCHFORM_UPDATE_FRIENDS_NEWS,	//��̬
	MSG_SWITCHFORM_FRIEND_LIST,	//�����б�
	MSG_SWITCHFORM_PROFILE,		//�ҵĵ���
	MSG_SWITCHFORM_APPLIST,		//���
	MSG_SWITCHFORM_MORE,		//����
	MSG_LOGOUT,					//�ǳ�
	MSG_EXIT,						//�˳�
	MSG_FORM_UPDATE,				//����form
	MSG_SWITCHFORM_MESSAGE_CENTER,		//��Ϣ����
};

//#define assert(bCondition) if (!(bCondition)) *(int*)NULL=0
#define assert(bCondition)


#define KAIXIN_SKEY			"bppvzyg2jpqnjLBvnHhjN1Ko5PaFDf4d"
#define KAIXIN_FOLDER		"kaixin/"

#define KAIXIN_URLPATH_LENGTH		(1024)
#define KAIXIN_STATUS_LENTH		(1024)



//��������
#define FRIEND_MAX_NUM			(500)		

//
#define ERROR_INFO_LEN			(100)

//AppID (keynumber)
typedef enum
{
	KX_AccessTypeStart = 0,

	KX_InitialLogin,			//Initial Login	
	KX_AutoLogin,				//Auto Login
	/*��APIȡ��*/	KX_Logout,					//Logout
	KX_Profile,					//Profile
	KX_GetStatus,				//GetStatus(Profile����)

	KX_UpdateFriendsNews, 		// Update Friends News
	KX_RecentNews,				//��ȡ���������̬(Update Friends News ����)

	KX_FriendList,       		//Friend list
	KX_GetFriendCount,			//��ȡ��������(Friend list ����)

	KX_GetUserInfos,			//Get usr infos
	KX_GetProfileDetail,		//Get usr infos �������GetProfileDetail

	KX_FriendsPhoto,			//Friends Photo

	KX_AlbumList,				//Album list
	KX_GetAlbumCount,			//��ȡ�����������Album list �������KX_GetAlbumCount 
	KX_AlbumPhoto,				//Album Photo
	KX_AlbumPhotoFromNews,		//�Ӷ�̬�б��л�ȡר����Ƭ����Album Photo �������KX_AlbumPhotoFromNews

	KX_UpdateStatus,			//Update Status
	KX_UploadPhoto,				//Upload Photo
	KX_WriteRecord,				//Write Record	

	KX_AcceptFriendRequest,		//Accept friend request
	KX_RefuseFriendRequest,		//Resuse friend request

	KX_Notice,					//����Ϣ����(Message Center����)
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
	/*��APIȡ��*/	KX_PostVote,				//Post vote

	KX_DiaryDetail,				//Diary detail
	/*��APIȡ��*/	KX_PostDiary,				//Post diary
	/*��APIȡ��*/	KX_EditDiary,				//Edit diary
	/*��APIȡ��*/	KX_UploadDiarysPhoto,		//Upload diarys' photo

	KX_RepasteDetail,			//repaste detail//��ȡת����Ϣ
	KX_RefreshVote,			//repaste detail//��ȡ�������ת����Ϣ
	KX_RefreshTag,			//repaste detail//��ȡ�������ת����Ϣ
	/*��APIȡ��*/	KX_PostRepaste,				//post repaste
	/*��APIȡ��*/	KX_PostRepastesVote,		//Post repaste's vote//����ת�������۵�

	/*��APIȡ��*/	KX_PostTag,					//post tag
	KX_InviteCode,				//invite code

	/*��APIȡ��*/	KX_RepasteIndex,			//Repaste index
	/*��APIȡ��*/	KX_RepasteIndexMore,			//Repaste index
	
	/*��APIȡ��*/	KX_GetRepasteCount,			//��ȡת����������Repaste index �������KX_GetRepasteCount 

	/*��APIȡ��*/	KX_ApplicationList,			//application list
	/*��APIȡ��*/	KX_TruthDetail,				//truth detail
	/*��APIȡ��*/	KX_ExchangeTruth,			//exchange truth

	/*��APIȡ��*/	KX_FaceList,				//״̬��������б�
	KX_GiftList,				//gift list

	KX_RecordList,				//record list
	KX_GetRecordCount,			//��ȡ��¼��������Record list �������KX_GetRecordCount 

	KX_DiaryList,				//diary list
	KX_GetDiaryCount,			//��ȡ�ռ���������Diary list �������KX_GetDiaryCount 

	/*��APIȡ��*/	KX_UpgradeInfos,			//��ȡ�ͻ�������Ϣ
	/*��APIȡ��*/	KX_Init,					//����ͻ���
	/*��APIȡ��*/	KX_AddFriends,				//��Ӻ�������

	//��Ϸ�ӿ�
	KX_GardenDetail,			//Garden's detail
	KX_GardenList,				//Garden list
	KX_GardenHarvest,			//harvest plants //�ջ�͵����
	KX_RanchDetail,				//Ranch's detail
	KX_RanchList,				//Ranch lsit //�п�͵��Ʒ�ĺ����б�
	KX_RanchHarvest,			//harvest animal//�ջ�͵ ����/��Ʒ
	KX_Product,					//product //����

	KX_More, 				//more  app û�ж�Ӧ��api

	/*need to add more type here*/
	KX_AccessTypeEnd,

	KX_PhotoDownload,			//ר������ͼƬ����
} Kx_AccessType;

typedef struct
{
	char paramName[32]; //������Ҫ����һ���ַ�
	char paramValue[4096]; //TODO, ��Ҫ��չ��С
}sUrlparams;


#define WAITING_BOX_TRUE	(TRUE)
#define WAITING_BOX_FALSE	(FALSE)


typedef struct
{
	Kx_AccessType	nType;
	Boolean			bHandle;			//�Ƿ���ҪApp_Kaixinͳһ����
	Boolean			bNeedWaitingBox;	//�Ƿ���Ҫ�ȴ�����
	char			FilePath[32];
	char			Address[KAIXIN_URLPATH_LENGTH];
	sUrlparams		*Params;
	int 				nParamsNum;

}sKxAppUrl;

#define NOTICE_TYPE_ALL					(0)	//ȫ��
#define NOTICE_TYPE_MESSAGE			(1)	//����Ϣ
#define NOTICE_TYPE_USER_COMMENT		(2)	//����
#define NOTICE_TYPE_POST_COMMENT		(3)	//����
#define NOTICE_TYPE_SYS_MESSAGE		(4)	//ϵͳ��Ϣ
#define NOTICE_TYPE_REPLY_USER_COMMENT	(5)	//���Իظ�
#define NOTICE_TYPE_REPLY_POST_COMMENT	(6)	//���ۻظ�

//�û���Ϣ,��Ҫ���������Զ���¼
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
	char logoPath[256];//ͷ���ļ�·��
	char status[KAIXIN_STATUS_LENTH];//״̬����	
	int	NoticeCount[7];
	Boolean  bLoadImage;
}tUserInfo;


extern tUserInfo	KaiXinUserInfo;
extern Int32		gHwndId_KaiXinApp[KX_AccessTypeEnd];//���濪�����������ڵ�ID
extern char* KX_GetFileName(Kx_AccessType accessType);
#endif
