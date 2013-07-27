/*!
* \file	 KaiXinAPI.cpp
* \author	 huxianxiang@GoZone
* \date	 2010-9-29
* \brief  开心应用的总框架、事件分发器
*
* \ref    CopyRight
* =======================================================================<br>
*          Copyright ? 2010-2012 GOZONE <br>
*                All Rights Reserved.<br>
* The file is generated for Tranzda Mobile Platform <br>
* =======================================================================<br>
*/

#include "KaiXinAPI.h"
#include "KaiXinAPICommon.h"

#include "ImageToolKit/IT_ImageLoader.h"
#include "ImageToolKit/ImageTools.h"
#include "TGlobal.h"

// Image
using namespace ImageToolKit;


//各API的参数数组
// 3.1
sUrlparams  Urlparam_InitalLogin[] = 
{
	{"login",	"force"},
	{"email",	"manyi1120@gmail.com"},
	{"password",	"123456"},	
	{"ctype",	"Tranzda"},
	{"from",	"Tranzda"},
};
// 3.2
sUrlparams  Urlparam_AutoLogin[] = 
{
	{"login",	"force"},
	{"uid",	"uid"},
	{"verify",	"codesdffveriy "},
	{"ctype",	"U502"},
	{"from",	"aaaa"},
};
// 3.3
sUrlparams  Urlparam_Logout[] =
{
	{"uid",	""},
	{"verify",	"code893hodfd"},
};

// 3.4
sUrlparams  Urlparam_Profile[] = //uid=&verify=&n=flag=before=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"0"},		//获取最大动态数
	/*
	{"type",	""},	//1：照片，2：日记，1018 记录，3：更新状态，1088：转贴（可选），1016：投票（可选） 。如为空返回所有类型的动态。	
	{"since",	""},	
	{"before",	""},
	{"start",	""},	
	{"fuid",	""},	
	{"flag",	""},
	{"format",	""},	//1：返回格式化过的动态数据，数据格式请查看文档 动态文本协议.txt    0：返回普通文本	
	*/
};

// 3.4
sUrlparams  Urlparam_GetStatus[] = //uid=&verify=&n=flag=before=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"0"},		//获取最大动态数
};


// 3.4 New Added 201009
sUrlparams  Urlparam_UpdateFriendsNews[] = //uid=&verify=&n=flag=before=
{
	{"uid",	""},
	{"v", "2.0"},		//如需要返回 转贴/投票 ，需要传入版本号：2.0		
	{"verify",	""},
	{"n",	"50"},		//获取最大动态数
	{"type",	""},	// 1：照片，2：日记，1018 记录，3：更新状态，1088：转贴（可选），1016：投票（可选） 。如为空返回所有类型的动态。	
	{"since",	""},	
	{"start",	""},	
	{"fuid",	""},	
	{"flag",	""},
	{"myself",	"1"},	//Myself=1为自己动态，暂时只有个人状态有效，其他类型无效
};

sUrlparams  Urlparam_RecentNews[] = //uid=&verify=&n=flag=before=
{
	{"uid",	""},
	{"v", "2.0"},		//如需要返回 转贴/投票 ，需要传入版本号：2.0		
	{"verify",	""},
	{"n",	"100"},		//获取最大动态数
	{"type",	""},	// 1：照片，2：日记，1018 记录，3：更新状态，1088：转贴（可选），1016：投票（可选） 。如为空返回所有类型的动态。	
	{"since",	""},	
	{"start",	""},	
	{"fuid",	""},	
	{"flag",	""},
	{"myself",	"1"},	//Myself=1为自己动态，暂时只有个人状态有效，其他类型无效
};

// 3.5
sUrlparams  Urlparam_FriendList[] = //uid=&verify=&n=flag=before=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"500"},
	{"start",	""},	
	{"type",	"0"},	
	{"lg",	"1"},	
};

sUrlparams  Urlparam_GetFriendCount[] = //uid=&verify=&n=flag=before=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"1"},
	{"start",	""},	
	{"type",	"0"},	
	{"lg",	"1"},	
};

// 3.5
sUrlparams  Urlparam_GetUserInfos[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"uids",	""},	
	{"ctime",	""},	
	{"n",	""},	
	{"start",	""},	
};

// 3.5
sUrlparams  Urlparam_GetProfileDetail[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"uids",	""},	
	{"ctime",	""},	
	{"n",	""},	
	{"start",	""},	
};


// 3.6
sUrlparams  Urlparam_FriendsPhoto[] = //uid=&verify=&n=&start=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"100"},
	{"start",	""},	
	{"fuid",	""},		
};

// 3.7
sUrlparams  Urlparam_AlbumList[] = //?uid=&verify=&n=&start=&fuid=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"100"},	
	{"start",	""},	
	{"fuid",	""},	
};

sUrlparams  Urlparam_GetAlbumCount[] = //?uid=&verify=&n=&start=&fuid=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"1024"},//获得所有的相册,如果为空 获取不到数据，只要先设置1024 
	{"start",	""},	
	{"fuid",	""},	
};


// 3.8
sUrlparams  Urlparam_AlbumPhoto[] = //?uid=&verify=&n=&start=&albumid=&fuid=&passwd=
{
	{"uid",	""},
	{"verify",	""},
	{"albumid",	""},	
	{"fuid",	""},
	{"passwd",	""},	
	{"n",	"200"},	
	{"start",	""},	
};

sUrlparams  Urlparam_AlbumPhotoFromNews[] = //?uid=&verify=&n=&start=&albumid=&fuid=&passwd=
{
	{"uid",	""},
	{"verify",	""},
	{"albumid",	""},	
	{"fuid",	""},
	{"passwd",	""},	
	{"n",	"100"},	
	{"start",	""},	
};

// 3.9
sUrlparams  Urlparam_UpdateStatus[] = //?uid=&verify=&state=
{
	{"uid",	""},
	{"verify",	""},
	{"state",	""},//新状态内容		
};


// 3.10
sUrlparams  Urlparam_UploadPhoto[] = //?uid=&verify=&title=&srcfilename=& location=&lat=&lon=
{
	{"uid",	""},
	{"verify",	""},
	{"title",	"photo"},
	{"srcfilename",	"photo.jpg"},
	//	{"",	""},			//Post 数据流(Unlimited)	
	{"albumid",	""},
	//{"location",	""},	
	//{"lat",	""},
	//{"lon",	""},	
};

// 3.11
sUrlparams  Urlparam_WriteRecord[] = //?uid=&verify=&privacy=&reccont=& location=&lat=&lon=
{
	{"uid",	""},
	{"verify",	""},	
	{"privacy",	"0"},//0：任何人可见 1：仅好友可见 2：隐藏
	{"reccont",	"ccc"},
	{"location",	""},
	{"lat",	""},
	{"lon",	""},	
};

// 3.12
sUrlparams  Urlparam_AcceptFriendRequest[] = //?uid=&verify=&fuid=&smid=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"smid",	""},//系统消息ID	
};

// 3.13
sUrlparams  Urlparam_RefuseFriendRequest[] = //?uid=&verify=&fuid=&smid=
{
	{"uid",	""},
	{"verify",	""},	
	{"smid",	""},//系统消息ID	
};


sUrlparams  Urlparam_Notice[] = //uid=&verify=&mtype=
{
	{"uid",		""},
	{"verify",	""},	
	{"mtype",	""},	
};

// 3.14
sUrlparams  Urlparam_MessageCenter[] = //uid=&verify=&mtype=
{
	{"uid",		""},
	{"verify",	""},	
	{"mtype",	""},	
};

// 3.15
sUrlparams  Urlparam_MessagesList[] = //uid=&verify=&n=
{
	{"uid",		""},
	{"verify",	""},	
	{"n",		"50"},
	{"since",	""},
	{"start",	""},
};

// 3.16
sUrlparams  Urlparam_SentMessagesList[] = //uid=&verify=&n=
{
	{"uid",		""},
	{"verify",	""},	
	{"n",		"50"},
	{"since",	""},
	{"start",	""},
};

// 3.17
sUrlparams  Urlparam_MessageDetail[] = //?uid=&mid=&verify=&n=
{
	{"uid",		""},
	{"verify",	""},	
	{"mid",	""},//消息主帖编号
	{"n",	"50"},
};

// 3.18
sUrlparams  Urlparam_SendAMessage[] = //uid=&verify=&n=
{
	{"uid",		""},
	{"verify",	""},	
	{"touid",	""},
	{"mid",		""},
	{"msgcont",	""},
};

// 3.19
sUrlparams  Urlparam_DeleteMessage[] = //?uid=&mid=&verify
{
	{"uid",		""},
	{"verify",	""},	
	{"mid",	""},//消息主帖编号
};

// 3.20
sUrlparams  Urlparam_ReceivedCommentsList[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"100"},	
	{"start",	""},	
};

// 3.21
sUrlparams  Urlparam_ReceivedAnObjectComments[] = //?uid=&verify=&id=&type=
{
	{"uid",		""},
	{"verify",	""},
	{"type",	""},	
	{"fuid",	""},//	14403848 //12599962
	{"id",		""},//285707450	
};


// 3.22
sUrlparams  Urlparam_CommentDetail[] = //?uid=&verify=&n=&thread_cid=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"50"},	
	{"thread_cid",	""},		
};

// 3.23
sUrlparams  Urlparam_PostComment[] = //?uid=&verify=&id=&ouid=&type=&content=
{
	{"uid",	""},
	{"verify",	""},
	{"type",	""},
	{"id",	""},	
	{"ouid",	""},
	{"hidden",	"0"},
	{"content",	""},	
};

// 3.24
sUrlparams  Urlparam_ReplyComment[] = //?uid=&verify=&thread_cid=&replycont=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"thread_cid",	""},
	{"replycont",	""},	
};

// 3.25
sUrlparams  Urlparam_SentCommentsList[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"100"},	
	{"start",	""},	
};

// 3.26
sUrlparams  Urlparam_SentCommentDetail[] = //?uid=&verify=&n=&thread_cid=
{
	{"uid",	""},
	{"fuid",	""},		
	{"verify",	""},	
	{"n",	"50"},	
	{"thread_cid",	""},		
};

// 3.27
sUrlparams  Urlparam_DeleteComment[] = //?uid=&verify=&thread_cid=&ouid=&ctime=
{
	{"uid",	""},
	{"verify",	""},	
	{"thread_cid",	""},		
	{"ouid",	""}, //owner id，评论对象的fuid		
	{"ctime",	""},	
};

// 3.28
sUrlparams  Urlparam_FriendsCommentList[] = //?uid=&verify=&thread_cid=&ouid=&ctime=
{
	{"uid",	""},
	{"verify",	""},	
	{"n",	"50"},		
	{"since",	"1284700000"},//	
};

// 3.29
sUrlparams  Urlparam_UserCommentsList[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"50"},	
	{"start",	""},		
};

// 3.30
sUrlparams  Urlparam_UserCommentDetail[] = //?uid=&verify=&n=&thread_cid=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"50"},	
	{"thread_cid",	""},		
};

// 3.31
sUrlparams  Urlparam_SentUserCommentsList[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"50"},		
};

// 3.32
sUrlparams  Urlparam_SentUserCommentDetail[] = //?uid=&verify=&n=&thread_cid=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"50"},	
	{"thread_cid",	""},		
};

// 3.33
sUrlparams  Urlparam_SystemMessage[] = //?uid=&verify=&n=
{
	{"uid",	""},
	{"verify",	""},
	{"n",	"50"},	
};

// 3.34
sUrlparams  Urlparam_BirthdayList[] = //?uid=&verify
{
	{"uid",	""},
	{"verify",	""},	
};

// 3.35
sUrlparams  Urlparam_SendBirthdayGift[] = //?uid=&verify=&fuid=&smid=&msg=
{
	{"uid",	""},
	{"verify",	""},
	{"fuid", ""},
	{"smid", ""},
	{"msg",	""},//附言
	{"quiet", ""},//是否悄悄话
	{"gid",	"2"},//礼物ID
};

// 3.36
sUrlparams  Urlparam_PokesList[] = //?uid=&verify
{
	{"uid",	""},
	{"verify",	""},	
};

// 3.37
sUrlparams  Urlparam_SendPoke[] = //?uid=&verify
{
	{"uid",	""},
	{"verify",	""},
	{"action", ""},//动作ID
	{"touid",	""},
	{"private", ""},//是否私密
};

// 3.38
sUrlparams  Urlparam_PostUp[] = //?uid=&verify=&id=&touid=&appid=
{
	{"uid",	""},
	{"verify",	""},
	{"appid",	"1"},//diary 的appid 怎么获得呢
	{"id",	""},
	{"touid",	""},			
};

// 3.39
sUrlparams  Urlparam_AppNews[] = //?uid=&verify=&ctype=fish&start=0&n=10
{
	{"uid",	""},
	{"verify",	""},
	{"ctype",	"garden"},//garden, fish	
	{"start",	""},
	{"n",	"50"},			
};

// 3.40
sUrlparams  Urlparam_VoteDetail[] = //?vid=&uid=&verify=
{
	{"uid",	""},
	{"verify",	""},
	{"vid",	""},
};

// 3.41
sUrlparams  Urlparam_PostVote[] = //?uid=&verify=&vid=&vote=
{
	{"uid",	""},
	{"verify",	""},
	{"vid",	""},
	{"vote", ""},
};

// 3.42
sUrlparams  Urlparam_DiaryDetail[] = //?did=&fuid=&uid=&verify=
{
	{"uid",	""},
	{"verify",	""},
	{"did",	""},
	{"fuid",	""},	
};

// 3.43
sUrlparams  Urlparam_PostDiary[] = //?title=&content=&did=&uid=&verify=& location=&lat=&lon=
{
	{"title",	"aaa"},
	{"content",	"ccc"},
	{"did",	""},
	{"uid",	""},
	{"verify",	""},	
	{"location",	""},
	{"lat",	""},
	{"lon",	""},	
};

// 3.44
sUrlparams  Urlparam_UploadDiarysPhoto[] = //?uid=&verify=&srcfilename=
{
	{"uid",	""},
	{"verify",	""},	
	{"srcfilename",	""},
	{"",	""},	
};

// 3.45
sUrlparams  Urlparam_RepasteDetail[] = //?urpid=&fuid=&uid=&verify=
{
	{"uid",	""},
	{"verify",	""},	
	{"urpid",	""},//转贴ID 从动态接口的对象ID 字段获取
	{"fuid",	""},	
	{"flag",	"1"},	//0 -- 文本格式; 1--html格式
};

// 3.46
sUrlparams  Urlparam_PostRepaste[] = //?uid=&verify=&fuid=&urpid=&reptype=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"urpid",	""},
	{"reptype",	""},	
};

// 3.47
sUrlparams  Urlparam_PostRepastesVote[] = //?uid=&verify=&urpid=&voteuid=&surpid=&answernum=
{
	{"uid",	""},
	{"verify",	""},

	{"urpid",	""},//转贴ID, 从转贴详细接口的urpid 字段获取
	{"voteuid",	""},//源转贴用户ID,从转贴详细接口的voteuid 字段获取	
	{"suid",	""},//转贴用户ID, 从转贴详细接口的suid 字段获取，如传入repflag=1 参数，必须把suid 也传入。
	{"surpid",	""},//源转贴ID, 从转贴详细接口的surpid 字段获取	
	{"answernum",	""},//答案序号, 序号最小为1，往上递增
	{"repflag",	""},// 1：发表标签成功后转贴 0：不转贴	
};

// 3.48
sUrlparams  Urlparam_PostTag[] = //?uid=&verify=&urpid=&suid=&repflag=&tagid=
{
	{"uid",	""},
	{"verify",	""},

	{"urpid",	""},//转贴ID, 从转贴详细接口的urpid 字段获取
	{"suid",	""},//转贴用户ID, 从转贴详细接口的suid 字段获取，如传入repflag=1 参数，必须把suid 也传入。
	{"tagid",	""},//标签ID, 从转贴详细接口的taglist[id]字段获取
	{"tag",	""},//新标签内容,发表新标签时需要传入此参数
	{"repflag",	""},// 1：发表标签成功后转贴 0：不转贴	
};

// 3.49
sUrlparams  Urlparam_InviteCode[] = //?uid=&verify
{
	{"uid",	""},
	{"verify",	""},		
};


// 3.51
sUrlparams  Urlparam_RepasteIndex[] = //?uid=&verify=&fuid=&lasturpid=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"lasturpid",	""},	
};

sUrlparams  Urlparam_GetRepasteCount[] = //?uid=&verify=&fuid=&lasturpid=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"lasturpid",	""},	
	{"n",	"1"},	
};

// 3.52
sUrlparams  Urlparam_ApplicationList[] = //uid=&verify=
{
	{"uid",		""},
	{"verify",	""},	
};

// 3.53
sUrlparams  Urlparam_TruthDetail[] = //?uid=&verify=&fuid=&tid=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"tid",	""},//真心话ID	
};

// 3.54
sUrlparams  Urlparam_ExchangeTruth[] = //uid=&verify=
{
	{"uid",		""},
	{"verify",	""},
	{"privacy", 	""},//隐私,0：任何人交换1：仅与主人交换
	{"truth",	""},//真心话内容
	{"fuid",	""},
	{"tid",	""},//真心话ID		
};

// 3.55
sUrlparams  Urlparam_FaceList[] = //?uid=&verify=
{
	{"uid",	""},
	{"verify",	""},			
};

// 3.56
sUrlparams  Urlparam_GiftList[] = //uid=&verify=
{
	{"uid",		""},
	{"verify",	""},	
};

// 3.57
sUrlparams  Urlparam_RecordList[] = //uid=&verify=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},	
	{"start",	""},
	{"n",	"50"},	//最大条数
};

sUrlparams  Urlparam_GetRecordCount[] = //uid=&verify=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},	
	{"start",	""},
	{"n",	"1"},	
};

// 3.58
sUrlparams  Urlparam_DiaryList[] = //?uid=&verify=&fuid=&n=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"start",	""},	
	{"n",	"100"},	
};

sUrlparams  Urlparam_GetDiaryCount[] = //?uid=&verify=&fuid=&n=
{
	{"uid",	""},
	{"verify",	""},	
	{"fuid",	""},
	{"start",	""},	
	{"n",	"1"},	
};

// 3.59
sUrlparams  Urlparam_UpgradeInfo[] = //uid=&verify=
{
	{"uid",		""},
	{"verify",	""},	
};

// 3.60
sUrlparams  Urlparam_Init[] = //imei=&from=&ctype=
{
	{"uid",		""},
	{"verify",	""},	
	{"imei",		""},
	{"from",		""},
	{"ctype",	""},	
};

// 3.61
sUrlparams  Urlparam_AddFriends[] = //uid=&verify=&touid=&content=
{
	{"uid",		""},
	{"verify",	""},	
	{"touid",		""},
	{"content",		""},	
};

//游戏接口
// 4.1
sUrlparams  Urlparam_GardenDetail[] = //uid=&verify=&fuid
{
	{"uid",		""},
	{"verify",	""},	
	{"fuid",		""},
};

// 4.2
sUrlparams  Urlparam_GardenList[] = //?uid=&verify=&n=
{
	{"uid",		""},
	{"verify",	""},	
	{"n",		"100"},
};

// 4.3
sUrlparams  Urlparam_GardenHarvest[] = //?uid=&farmnum=&fuid=&verify=
{
	{"uid",		""},
	{"verify",	""},
	{"farmnum",	""},//作物所属地编号
	{"fuid",		""},
};

// 4.4
sUrlparams  Urlparam_RanchDetail[] = //uid=&verify=&fuid
{
	{"uid",		""},
	{"verify",	""},	
	{"fuid",		""},
};

// 4.5
sUrlparams  Urlparam_RanchList[] = //uid=&verify=&n
{
	{"uid",		""},
	{"verify",	""},	
	{"n",		"100"},
};

// 4.6
sUrlparams  Urlparam_RanchHarvest[] = //uid=&verify=&fuid
{
	{"uid",		""},
	{"verify",	""},
	{"animalsid", 	""},//动物编号
	{"skey",	""},//产品关键词,动物为空
	{"type",	""},//产品类型,动物为空	
	{"fuid",		""},
};

// 4.7 动物生产
sUrlparams  Urlparam_Product[] = //uid=&verify=&fuid
{
	{"uid",		""},
	{"verify",	""},
	{"animalsid",	""},//动物编号
	{"fuid",		""},
};

//App的主结构体
sKxAppUrl   KxAppUrl[] =
{
	{KX_InitialLogin, 				TRUE,	WAITING_BOX_TRUE, "InitalLogin.jso", 	"http://ksa2.kaixin001.com/login/login.php", Urlparam_InitalLogin, ARR_SIZE(Urlparam_InitalLogin)},	
	{KX_AutoLogin, 				TRUE,	WAITING_BOX_TRUE, "AutoLogin.jso", 	"http://ksa2.kaixin001.com/login/login.php", Urlparam_AutoLogin, ARR_SIZE(Urlparam_AutoLogin)},
	{KX_Logout, 					TRUE,	WAITING_BOX_TRUE, "Logout.jso",		"http://ksa2.kaixin002.com/kxapi/login/loginout.php", Urlparam_Logout, ARR_SIZE(Urlparam_Logout)},	
	{KX_Profile, 					TRUE,	WAITING_BOX_TRUE, "Profile.jso", 		"http://ksa2.kaixin001.com/home/index.php", Urlparam_Profile, ARR_SIZE(Urlparam_Profile)},
	{KX_GetStatus,				FALSE,	WAITING_BOX_FALSE, "GetStatus.jso",		"http://ksa2.kaixin001.com/home/index.php", Urlparam_GetStatus, ARR_SIZE(Urlparam_GetStatus)},
	{KX_UpdateFriendsNews,		TRUE,	WAITING_BOX_TRUE, "UpdateFriendsNews.jso",		"http://ksa2.kaixin001.com/home/get_news2.php", Urlparam_UpdateFriendsNews, ARR_SIZE(Urlparam_UpdateFriendsNews)},
	{KX_RecentNews,				TRUE,	WAITING_BOX_TRUE, "RecentNews.jso",		"http://ksa2.kaixin001.com/home/get_news2.php", Urlparam_RecentNews, ARR_SIZE(Urlparam_RecentNews)},

	/*the following need to modify to correct in future*/	
	{KX_FriendList, 				TRUE,	WAITING_BOX_TRUE, "FriendList.jso", 	"http://ksa2.kaixin002.com/kxapi/friend/friendlist_kx.php", Urlparam_FriendList, ARR_SIZE(Urlparam_FriendList)},
	{KX_GetFriendCount, 			FALSE,	WAITING_BOX_FALSE, "GetFriendCount.jso",	"http://ksa2.kaixin002.com/kxapi/friend/friendlist_kx.php", Urlparam_GetFriendCount, ARR_SIZE(Urlparam_GetFriendCount)},
	{KX_GetUserInfos, 			TRUE,	WAITING_BOX_TRUE, "GetUserInfos.jso",	"http://ksa2.kaixin001.com/friend/getuserinfos.php", Urlparam_GetUserInfos, ARR_SIZE(Urlparam_GetUserInfos)},
	{KX_GetProfileDetail, 			TRUE,	WAITING_BOX_TRUE, "GetProfileDetail.jso",	"http://ksa2.kaixin001.com/friend/getuserinfos.php", Urlparam_GetProfileDetail, ARR_SIZE(Urlparam_GetProfileDetail)},

	{KX_FriendsPhoto, 				TRUE,	WAITING_BOX_TRUE, "FriendsPhoto.jso",	"http://ksa2.kaixin001.com/photo/friendphotos.php", Urlparam_FriendsPhoto, ARR_SIZE(Urlparam_FriendsPhoto)},

	{KX_AlbumList, 				TRUE,	WAITING_BOX_TRUE, "AlbumList.jso", 	"http://ksa2.kaixin001.com/photo/albumlist.php", Urlparam_AlbumList, ARR_SIZE(Urlparam_AlbumList)},
	{KX_GetAlbumCount,			FALSE,	WAITING_BOX_FALSE, "GetAlbumCount.jso",	"http://ksa2.kaixin001.com/photo/albumlist.php", Urlparam_GetAlbumCount, ARR_SIZE(Urlparam_GetAlbumCount)},

	{KX_AlbumPhoto, 				TRUE,	WAITING_BOX_TRUE, "AlbumPhoto.jso", 	"http://ksa2.kaixin001.com/photo/albumphotos.php", Urlparam_AlbumPhoto, ARR_SIZE(Urlparam_AlbumPhoto)},
	{KX_AlbumPhotoFromNews, 		FALSE,	WAITING_BOX_TRUE, "AlbumPhotoFromNews.jso",	"http://ksa2.kaixin001.com/photo/albumphotos.php", Urlparam_AlbumPhotoFromNews, ARR_SIZE(Urlparam_AlbumPhotoFromNews)},

	{KX_UpdateStatus, 			FALSE,	WAITING_BOX_TRUE, "UpdateStatus.jso","http://ksa2.kaixin001.com/home/update_status.php", Urlparam_UpdateStatus, ARR_SIZE(Urlparam_UpdateStatus)},
	{KX_UploadPhoto, 				FALSE,	WAITING_BOX_TRUE, "UploadPhoto.jso",	"http://ksa2.kaixin001.com/photo/post.php", Urlparam_UploadPhoto, ARR_SIZE(Urlparam_UploadPhoto)},

	{KX_WriteRecord, 				FALSE,	WAITING_BOX_TRUE, "WriteRecord.jso",	"http://ksa2.kaixin001.com/record/post.php", Urlparam_WriteRecord, ARR_SIZE(Urlparam_WriteRecord)},

	/**/	{KX_AcceptFriendRequest,	FALSE,	WAITING_BOX_TRUE, "AcceptFriendRequest.jso",	"http://ksa2.kaixin001.com/friend/acceptfriend.php", Urlparam_AcceptFriendRequest, ARR_SIZE(Urlparam_AcceptFriendRequest)},
	/**/	{KX_RefuseFriendRequest, 	FALSE,	WAITING_BOX_TRUE, "RefuseFriendRequest.jso",	"http://ksa2.kaixin001.com/friend/refusefriend.php", Urlparam_RefuseFriendRequest, ARR_SIZE(Urlparam_RefuseFriendRequest)},

	{KX_Notice, 					FALSE,	WAITING_BOX_FALSE, "Notice.jso",	"http://ksa2.kaixin001.com/msg/index.php", Urlparam_Notice, ARR_SIZE(Urlparam_Notice)},
	{KX_MessageCenter, 			FALSE,	WAITING_BOX_FALSE, "MessageCenter.jso",	"http://ksa2.kaixin001.com/msg/index.php", Urlparam_MessageCenter, ARR_SIZE(Urlparam_MessageCenter)},
	{KX_MessagesList, 			TRUE,	WAITING_BOX_TRUE, "MessagesList.jso",	"http://ksa2.kaixin001.com/msg/inbox2.php", Urlparam_MessagesList, ARR_SIZE(Urlparam_MessagesList)},
	{KX_SentMessagesList, 			TRUE,	WAITING_BOX_TRUE, "SentMessagesList.jso",	"http://ksa2.kaixin001.com/msg/sendbox.php", Urlparam_SentMessagesList, ARR_SIZE(Urlparam_SentMessagesList)},
	{KX_MessageDetail, 			FALSE,	WAITING_BOX_TRUE, "MessageDetail.jso",	"http://ksa2.kaixin001.com/msg/view.php", Urlparam_MessageDetail, ARR_SIZE(Urlparam_MessageDetail)},

	/**/	{KX_SendAMessage, 		FALSE,	WAITING_BOX_TRUE, "SendAMessage.jso",	"http://ksa2.kaixin001.com/msg/post.php", Urlparam_SendAMessage, ARR_SIZE(Urlparam_SendAMessage)},
	{KX_DeleteMessage, 			FALSE,	WAITING_BOX_TRUE, "DeleteMessage.jso",	"http://ksa2.kaixin001.com/msg/delthread.php", Urlparam_DeleteMessage, ARR_SIZE(Urlparam_DeleteMessage)},

	{KX_ReceivedCommentsList, 	TRUE,	WAITING_BOX_TRUE, "ReceivedCommentsList.jso", "http://ksa2.kaixin001.com/comment/index.php", Urlparam_ReceivedCommentsList, ARR_SIZE(Urlparam_ReceivedCommentsList)},
	{KX_RepasteCommentsList, 	TRUE,	WAITING_BOX_TRUE, "ReceivedCommentsList.jso", "http://ksa2.kaixin001.com/comment/index.php", Urlparam_ReceivedCommentsList, ARR_SIZE(Urlparam_ReceivedCommentsList)},
	{KX_ReceivedAnObjectComments, TRUE,	WAITING_BOX_TRUE, "ReceivedAnObjectComments.jso", "http://ksa2.kaixin001.com/comment/app.php", Urlparam_ReceivedAnObjectComments, ARR_SIZE(Urlparam_ReceivedAnObjectComments)},
	{KX_ReceivedRepasteComments, TRUE,	WAITING_BOX_TRUE, "ReceivedRepasteComments.jso", "http://ksa2.kaixin001.com/comment/app.php", Urlparam_ReceivedAnObjectComments, ARR_SIZE(Urlparam_ReceivedAnObjectComments)},
	{KX_ReceivedDiaryComments, TRUE,	WAITING_BOX_TRUE, "ReceivedDiaryComments.jso", "http://ksa2.kaixin001.com/comment/app.php", Urlparam_ReceivedAnObjectComments, ARR_SIZE(Urlparam_ReceivedAnObjectComments)},
	{KX_ReceivedRecordComments, TRUE,	WAITING_BOX_TRUE, "ReceivedRecordComments.jso", "http://ksa2.kaixin001.com/comment/app.php", Urlparam_ReceivedAnObjectComments, ARR_SIZE(Urlparam_ReceivedAnObjectComments)},
	{KX_ReceivedStateComments, TRUE,	WAITING_BOX_TRUE, "ReceivedStateComments.jso", "http://ksa2.kaixin001.com/comment/app.php", Urlparam_ReceivedAnObjectComments, ARR_SIZE(Urlparam_ReceivedAnObjectComments)},
	{KX_CommentDetail, 			FALSE,	WAITING_BOX_TRUE, "CommentDetail.jso", "http://ksa2.kaixin001.com/comment/index_view.php", Urlparam_CommentDetail, ARR_SIZE(Urlparam_CommentDetail)},
	/**/	{KX_PostComment,		FALSE,	WAITING_BOX_TRUE, "PostComment.jso", "http://ksa2.kaixin001.com/comment/post.php", Urlparam_PostComment, ARR_SIZE(Urlparam_PostComment)},
	/**/	{KX_ReplyComment, 		FALSE,	WAITING_BOX_TRUE, "ReplyComment.jso", "http://ksa2.kaixin001.com/comment/reply.php", Urlparam_ReplyComment, ARR_SIZE(Urlparam_ReplyComment)},

	//pengjohn debug, KX_SentCommentsList很特殊,WAITING_BOX_TRUE事件会到WaitingBox, 待查
	{KX_SentCommentsList,		TRUE,	WAITING_BOX_TRUE, "SentCommentsList.jso", "http://ksa2.kaixin001.com/comment/send.php", Urlparam_SentCommentsList, ARR_SIZE(Urlparam_SentCommentsList)},
	{KX_SentCommentDetail,		FALSE,	WAITING_BOX_TRUE, "SentCommentDetail.jso", "http://ksa2.kaixin001.com/comment/send_view.php", Urlparam_SentCommentDetail, ARR_SIZE(Urlparam_SentCommentDetail)},
	/**/	{KX_DeleteComment,		FALSE,	WAITING_BOX_TRUE, "DeleteComment.jso", "http://ksa2.kaixin001.com/comment/del.php", Urlparam_DeleteComment, ARR_SIZE(Urlparam_DeleteComment)},
	{KX_FriendsCommentList,		TRUE,	WAITING_BOX_TRUE, "FriendsCommentList.jso", "http://ksa2.kaixin001.com/comment/mflist.php", Urlparam_FriendsCommentList, ARR_SIZE(Urlparam_FriendsCommentList)},

	{KX_ReceivedUserCommentsList, TRUE,	WAITING_BOX_TRUE, "ReceivedUserCommentsList.jso",	"http://ksa2.kaixin001.com/comment/uindex.php", Urlparam_UserCommentsList, ARR_SIZE(Urlparam_UserCommentsList)},
	{KX_UserCommentDetail,		FALSE,	WAITING_BOX_TRUE, "UserCommentDetail.jso", "http://ksa2.kaixin001.com/comment/uindex_view.php", Urlparam_UserCommentDetail, ARR_SIZE(Urlparam_UserCommentDetail)},
	{KX_SentUserCommentsList,		TRUE,	WAITING_BOX_TRUE, "SentUserCommentsList.jso", "http://ksa2.kaixin001.com/comment/usend.php", Urlparam_SentUserCommentsList, ARR_SIZE(Urlparam_SentUserCommentsList)},
	{KX_SentUserCommentDetail,	FALSE,	WAITING_BOX_TRUE, "SentUserCommentDetail.jso", "http://ksa2.kaixin001.com/comment/usend_view.php", Urlparam_SentUserCommentDetail, ARR_SIZE(Urlparam_SentUserCommentDetail)},

	{KX_SystemMessage,			TRUE,	WAITING_BOX_TRUE, "SystemMessage.jso", "http://ksa2.kaixin001.com/msg/sys2.php", Urlparam_SystemMessage, ARR_SIZE(Urlparam_SystemMessage)},

	{KX_BirthdayList,				TRUE,	WAITING_BOX_TRUE, "BirthdayList.jso", "http://ksa2.kaixin001.com/msg/birthday.php", Urlparam_BirthdayList, ARR_SIZE(Urlparam_BirthdayList)},
	/**/	{KX_SendBirthdayGift,		FALSE,	WAITING_BOX_TRUE, "SendBirthdayGift.jso", "http://ksa2.kaixin001.com/msg/send_gift.php", Urlparam_SendBirthdayGift, ARR_SIZE(Urlparam_SendBirthdayGift)},

	{KX_PokesList,				FALSE,	WAITING_BOX_TRUE, "PokesList.jso", "http://ksa2.kaixin001.com/dongta/getpokes.php", Urlparam_PokesList, ARR_SIZE(Urlparam_PokesList)},
	{KX_SendPoke,				FALSE,	WAITING_BOX_TRUE, "SendPoke.jso", "http://ksa2.kaixin001.com/dongta/poke.php", Urlparam_SendPoke, ARR_SIZE(Urlparam_SendPoke)},

	/**/	{KX_PostUp, 				FALSE,	WAITING_BOX_TRUE, "PostUp.jso", "http://ksa2.kaixin001.com/common/up.php", Urlparam_PostUp, ARR_SIZE(Urlparam_PostUp)},
	/**/	{KX_AppNews, 			TRUE,	WAITING_BOX_TRUE, "AppNews.jso", "http://ksa2.kaixin001.com/home/get_appnews.php", Urlparam_AppNews, ARR_SIZE(Urlparam_AppNews)},

	{KX_VoteDetail, 				TRUE,	WAITING_BOX_TRUE, "VoteDetail.jso", "http://ksa2.kaixin001.com/vote/detail.php", Urlparam_VoteDetail, ARR_SIZE(Urlparam_VoteDetail)},	
	{KX_PostVote, 				FALSE,	WAITING_BOX_TRUE, "PostVote.jso", "http://ksa2.kaixin002.com/vote/submit.php", Urlparam_PostVote, ARR_SIZE(Urlparam_PostVote)}, 

	{KX_DiaryDetail, 				TRUE,	WAITING_BOX_TRUE, "DiaryDetail.jso", "http://ksa2.kaixin001.com/diary/view.php", Urlparam_DiaryDetail, ARR_SIZE(Urlparam_DiaryDetail)},
	/**/	{KX_PostDiary, 			FALSE,	WAITING_BOX_TRUE, "PostDiary.jso", "http://ksa2.kaixin002.com/diary/post.php", Urlparam_PostDiary, ARR_SIZE(Urlparam_PostDiary)},
	{KX_UploadDiarysPhoto, 		FALSE,	WAITING_BOX_TRUE, "UploadDiarysPhoto.jso", "http://ksa2.kaixin002.com/photo/getimg.php", Urlparam_UploadDiarysPhoto, ARR_SIZE(Urlparam_UploadDiarysPhoto)},

	{KX_RepasteDetail,			TRUE,	 WAITING_BOX_TRUE, "RepasteDetail.jso", "http://ksa2.kaixin001.com/repaste/detail.php", Urlparam_RepasteDetail, ARR_SIZE(Urlparam_RepasteDetail)},	
	{KX_RefreshVote,			TRUE,	 WAITING_BOX_TRUE, "RefreshVote.jso", "http://ksa2.kaixin001.com/repaste/detail.php", Urlparam_RepasteDetail, ARR_SIZE(Urlparam_RepasteDetail)},	
	{KX_RefreshTag,				TRUE,	 WAITING_BOX_TRUE, "RefreshTag.jso", "http://ksa2.kaixin001.com/repaste/detail.php", Urlparam_RepasteDetail, ARR_SIZE(Urlparam_RepasteDetail)},	
	/**/	{KX_PostRepaste, 			FALSE,	WAITING_BOX_TRUE, "PostRepaste.jso", "http://ksa2.kaixin002.com/repaste/repaste_submit.php", Urlparam_PostRepaste, ARR_SIZE(Urlparam_PostRepaste)},
	/**/	{KX_PostRepastesVote, 	FALSE,	WAITING_BOX_TRUE, "PostRepastesVote.jso", "http://ksa2.kaixin002.com/repaste/vote_submit.php", Urlparam_PostRepastesVote, ARR_SIZE(Urlparam_PostRepastesVote)},

	{KX_PostTag, 					FALSE,	WAITING_BOX_TRUE, "PostTag.jso", "http://ksa2.kaixin002.com/repaste/tag_submit.php", Urlparam_PostTag, ARR_SIZE(Urlparam_PostTag)},
	{KX_InviteCode, 				FALSE,	WAITING_BOX_TRUE, "InviteCode.jso",	"http://ksa2.kaixin002.com/home/invitecode.php", Urlparam_InviteCode, ARR_SIZE(Urlparam_InviteCode)},

	{KX_RepasteIndex, 			TRUE,	WAITING_BOX_TRUE, "RepasteIndex.jso", "http://ksa2.kaixin002.com/repaste/index.php", Urlparam_RepasteIndex, ARR_SIZE(Urlparam_RepasteIndex)},	
	{KX_RepasteIndexMore, 		FALSE,	WAITING_BOX_TRUE, "RepasteIndexMore.jso", "http://ksa2.kaixin002.com/repaste/index.php", Urlparam_RepasteIndex, ARR_SIZE(Urlparam_RepasteIndex)},	

	{KX_GetRepasteCount,			FALSE,	WAITING_BOX_FALSE, "GetRepasteCount.jso", "http://ksa2.kaixin002.com/repaste/index.php", Urlparam_GetRepasteCount, ARR_SIZE(Urlparam_GetRepasteCount)}, 
	{KX_ApplicationList, 			TRUE,	WAITING_BOX_TRUE, "ApplicationList.jso",	"http://ksa2.kaixin002.com/kxapi/applist.php", Urlparam_ApplicationList, ARR_SIZE(Urlparam_ApplicationList)},

	{KX_TruthDetail, 				TRUE,	WAITING_BOX_TRUE, "TruthDetail.jso", "http://ksa2.kaixin002.com/truth/detail.php", Urlparam_TruthDetail, ARR_SIZE(Urlparam_TruthDetail)},
	{KX_ExchangeTruth, 			TRUE,	WAITING_BOX_TRUE, "ExchangeTruth.jso", "http://ksa2.kaixin002.com/truth/exchange_submit.php", Urlparam_ExchangeTruth, ARR_SIZE(Urlparam_ExchangeTruth)},

	/**/	{KX_FaceList, 				FALSE,	WAITING_BOX_TRUE, "FaceList.jso", "http://ksa2.kaixin002.com/kxapi/home/face.php", Urlparam_FaceList, ARR_SIZE(Urlparam_FaceList)},
	{KX_GiftList, 					TRUE,	WAITING_BOX_TRUE, "GiftList.jso", "http://ksa2.kaixin001.com/msg/giftlist.php", Urlparam_GiftList, ARR_SIZE(Urlparam_GiftList)},

	{KX_RecordList, 				TRUE,	WAITING_BOX_TRUE, "RecordList.jso",		"http://ksa2.kaixin001.com/record/list.php", Urlparam_RecordList, ARR_SIZE(Urlparam_RecordList)},
	{KX_GetRecordCount, 			FALSE,	WAITING_BOX_FALSE, "GetRecordCount.jso",		"http://ksa2.kaixin001.com/record/list.php", Urlparam_GetRecordCount, ARR_SIZE(Urlparam_GetRecordCount)},

	{KX_DiaryList, 				TRUE,	WAITING_BOX_TRUE, "DiaryList.jso",		"http://ksa2.kaixin001.com/diary/list.php", Urlparam_DiaryList, ARR_SIZE(Urlparam_DiaryList)},
	{KX_GetDiaryCount,			FALSE,	WAITING_BOX_FALSE, "GetDiaryCount.jso",		"http://ksa2.kaixin001.com/diary/list.php", Urlparam_GetDiaryCount, ARR_SIZE(Urlparam_GetDiaryCount)},

	{KX_UpgradeInfos, 			FALSE,	WAITING_BOX_TRUE, "UpgradeInfos.jso",	"http://ksa2.kaixin002.com/kxapi/upgrade.php", Urlparam_UpgradeInfo, ARR_SIZE(Urlparam_UpgradeInfo)},
	{KX_Init, 					TRUE,	WAITING_BOX_TRUE, "Init.jso",			"http://ksa2.kaixin002.com/common/init.php", Urlparam_Init, ARR_SIZE(Urlparam_Init)},
	{KX_AddFriends, 				FALSE,	WAITING_BOX_TRUE, "AddFriends.jso",		"http://ksa2.kaixin002.com/friend/addverify.php", Urlparam_AddFriends, ARR_SIZE(Urlparam_AddFriends)},	

	//游戏接口
	{KX_GardenDetail, 			TRUE,	WAITING_BOX_TRUE, "GardenDetail.jso",		"http://ksa2.kaixin001.com/house/garden/index.php", Urlparam_GardenDetail, ARR_SIZE(Urlparam_GardenDetail)},	
	{KX_GardenList, 				TRUE,	WAITING_BOX_TRUE, "GardenList.jso",		"http://ksa2.kaixin001.com/house/garden/getfriendmature.php", Urlparam_GardenList, ARR_SIZE(Urlparam_GardenList)},	
	{KX_GardenHarvest, 			FALSE,	WAITING_BOX_TRUE, "GardenHarvest.jso", 	"http://ksa2.kaixin001.com/house/garden/havest.php", Urlparam_GardenHarvest, ARR_SIZE(Urlparam_GardenHarvest)},	
	{KX_RanchDetail, 				TRUE,	WAITING_BOX_TRUE, "RanchDetail.jso",		"http://ksa2.kaixin001.com/house/ranch/index.php", Urlparam_RanchDetail, ARR_SIZE(Urlparam_RanchDetail)},	
	{KX_RanchList, 				TRUE,	WAITING_BOX_TRUE, "RanchList.jso", 			"http://ksa2.kaixin001.com/house/ranch/getfriendproduct2.php", Urlparam_RanchList, ARR_SIZE(Urlparam_RanchList)},	
	{KX_RanchHarvest, 			FALSE,	WAITING_BOX_TRUE, "RanchHarvest.jso",		"http://ksa2.kaixin001.com/house/ranch/havest.php", Urlparam_RanchHarvest, ARR_SIZE(Urlparam_RanchHarvest)},	
	{KX_Product, 					FALSE,	WAITING_BOX_TRUE, "Product.jso",			"http://ksa2.kaixin001.com/house/ranch/product.php", Urlparam_Product, ARR_SIZE(Urlparam_Product)},	

	//只是为了打印log
	{KX_PhotoDownload, 			FALSE,	WAITING_BOX_FALSE, "PhotoDownload.jso",	"http://ksa2.kaixin001.com/house/ranch/product.php", Urlparam_Product, ARR_SIZE(Urlparam_Product)},	
};


//需要保存的全局信息
tUserInfo	KaiXinUserInfo = 
{
	FALSE,
	TRUE,
	FALSE,
	"",	//账号
	"",	//密码
	"",
	"",
	"",
	"/My_Projects/App_KaiXin/Res/Photos/Default.png",	//默认为default.png
	"",	//默认为空	,进profile后进行，保存最新内容
	{0,0,0,0,0,0},
	TRUE
};

//保存开心网各个窗口的ID，初始为0
Int32	gHwndId_KaiXinApp[KX_AccessTypeEnd] = {0};

//配置文件
#define KAIXIN_CONFIG_FILE		"kaixin.cfg"



/**
 * 获得App对应的URL 
 * 调用者需释放ppURL
 * \param accessType:   api id    
 * \param ppURL:        返回对用的api接口url
 *
 * \return 
 */
int Url_Generate(Kx_AccessType accessType, char** ppURL)
{	
	int result = eFailed;

	sKxAppUrl kxAppUrl;

	int arrSize = 0; //KX_Url_Params_Num[accessType];
	int i = 0;
	int nUrlLen = 0;

	//-------------------------------------------------------------

	if(ppURL == NULL)
	{
		return eFailed;		
	}
	if(accessType >= KX_AccessTypeEnd || accessType <= KX_AccessTypeStart)
	{
		return eFailed;
	}

	//查找对应的结构体
	for(i=0; i<ARR_SIZE(KxAppUrl);i++)
	{
		if(KxAppUrl[i].nType == accessType)
		{
			kxAppUrl = KxAppUrl[i];
			result = eSucceed;
		}
	}
	//未发现对应的结构体
	if(result == eFailed)
		return eFailed;

	arrSize = kxAppUrl.nParamsNum;

	//calulate the url lenght
	nUrlLen = strlen(kxAppUrl.Address) + strlen("?");

	for(i=0;i<arrSize;i++)
	{
		if( kxAppUrl.Params[i].paramName != NULL && kxAppUrl.Params[i].paramValue != NULL )
		{
			if(0 != i) //not the first param
			{
				nUrlLen += strlen("&");
			}
			nUrlLen += strlen(kxAppUrl.Params[i].paramName);
			nUrlLen += strlen("=");
			nUrlLen += strlen(kxAppUrl.Params[i].paramValue);
		}
	}
	nUrlLen = nUrlLen + 1;

	*ppURL = (char*)malloc(nUrlLen);

	if(*ppURL)
	{
		memset(*ppURL, 0, nUrlLen);	
		memcpy(*ppURL,kxAppUrl.Address,nUrlLen);//strcpy(*ppURL, KX_Access_Adr[accessType])//, strlen(KX_Access_Adr[accessType]);

		//link the adress and params togother	
		strcat(*ppURL, "?");

		for(i=0;i<arrSize;i++)
		{		
			if( kxAppUrl.Params[i].paramName != NULL && kxAppUrl.Params[i].paramValue != NULL )
			{
				if( 0 != i )
				{
					strcat(*ppURL, "&");
				}

				strcat(*ppURL, kxAppUrl.Params[i].paramName);
				strcat(*ppURL, "=");
				strcat(*ppURL, kxAppUrl.Params[i].paramValue);
			}
			else
			{
				result= eFailed;
				break;
			}
		}
	}
	else
	{
		result= eFailed;
	}

	return result;
}

/**设置URL的参数
* 参数: 
*	ParamName: 参数名
*	ParamValue: 参数值
*/
int Set_Url_Params(Kx_AccessType accessType, char* ParamName, char* ParamValue)
{
	sKxAppUrl kxAppUrl;

	int i = 0;
	int arrSize = 0;

	int result = eFailed;
	//---------------------------------

	if(ParamName == NULL || ParamValue == NULL)
	{
		return eFailed;		
	}

	if(accessType >= KX_AccessTypeEnd || accessType <= KX_AccessTypeStart)
	{
		return eFailed;
	}

	//查找对应的结构体
	for(i=0; i<ARR_SIZE(KxAppUrl);i++)
	{
		if(KxAppUrl[i].nType == accessType)
		{
			kxAppUrl = KxAppUrl[i];
			result = eSucceed;
		}
	}
	//未发现对应的结构体
	if(result == eFailed)
		return eFailed;

	arrSize = kxAppUrl.nParamsNum;

	for(i=0; i<arrSize; i++)
	{	if( kxAppUrl.Params[i].paramName != NULL && kxAppUrl.Params[i].paramValue != NULL )
	{		
		if(strcmp(kxAppUrl.Params[i].paramName, ParamName)==0)
		{
			memset(kxAppUrl.Params[i].paramValue, 0, sizeof(kxAppUrl.Params[i].paramValue));
			strcpy(kxAppUrl.Params[i].paramValue, ParamValue);				
			result= eSucceed;
			break;
		}
	}
	else
	{
		result= eFailed;
		break;		
	}
	}

	return result;
}

/**获取URL的参数
* 参数: 
*	ParamName: 参数名
*	ParamValue: 返回参数值,不需要释放
*/
int Get_Url_Params(Kx_AccessType accessType, char* ParamName, char** ParamValue)
{
	sKxAppUrl kxAppUrl;

	int i = 0;
	int arrSize = 0;

	int result = eFailed;
	//---------------------------------

	if(ParamName == NULL)
	{
		return eFailed;		
	}

	if(ParamValue == NULL)
	{
		return eFailed;		
	}

	if(accessType >= KX_AccessTypeEnd || accessType <= KX_AccessTypeStart)
	{
		return eFailed;
	}

	//查找对应的结构体
	for(i=0; i<ARR_SIZE(KxAppUrl);i++)
	{
		if(KxAppUrl[i].nType == accessType)
		{
			kxAppUrl = KxAppUrl[i];
			result = eSucceed;
		}
	}
	//未发现对应的结构体
	if(result == eFailed)
		return eFailed;

	arrSize = kxAppUrl.nParamsNum;

	for(i=0; i<arrSize; i++)
	{	if( kxAppUrl.Params[i].paramName != NULL && kxAppUrl.Params[i].paramValue != NULL )
	{		
		if(strcmp(kxAppUrl.Params[i].paramName, ParamName)==0)
		{
			strcpy(*ParamValue, kxAppUrl.Params[i].paramValue);				
			result= eSucceed;
			break;
		}
	}
	else
	{
		result= eFailed;
		break;		
	}
	}

	return result;
}



/**
 * 获得保存数据的文件名 
 * 若无对应的则返回NULL
 * 返回的是全局变量,调用者不需要释放
 * \param accessType
 *
 * \return 
 */
char* KX_GetFileName(Kx_AccessType accessType)
{
	int i = 0;

	//查找对应的结构体
	for(i=0; i<ARR_SIZE(KxAppUrl);i++)
	{
		if(KxAppUrl[i].nType == accessType)
		{
			if(strlen(KxAppUrl[i].FilePath) ==0)
				return NULL;
			else
				return KxAppUrl[i].FilePath;
		}
	}
	//未发现对应的结构体
	return NULL;
}

/**
 * 返回解析后的数据结构, 使用者需要类型强转 
 * 正确时返回(eSucceed) ,注意: 调用者需要释放
 * 失败时返回错误errorCode , 调用者不需要释放
 * \param accessType
 * \param Response
 *
 * \return 
 */
int KaiXinAPI_JsonParse(Kx_AccessType accessType, void**Response)
{
	int iRet = eFailed;
	//void* Response = NULL;
	char* FilePath = NULL;

	*Response = NULL;
	FilePath = KX_GetFileName(accessType);
	if(FilePath == NULL)
		return eFailed;

	TUChar pszFilePath[EOS_FILE_MAX_PATH];
	TUChar pszTemp[EOS_FILE_MAX_FNAME];
	//TUString::StrCopy(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
	//TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
	//TUString::StrCat(pszFilePath,pszTemp);
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_CACHE, pszFilePath);
	
	TUString::StrGBToUnicode(pszTemp,(Char*)FilePath);
	TUString::StrCat(pszFilePath,pszTemp);

	if (EOS_IsFileExist(pszFilePath))
	{
		Handle hFile = NULL;			// file handle
		Int32 nFileSize = 0;			// 文件大小
		Int32 nReadByte = 0;			// 具体读出的字节数
		void * szReadContent = NULL;

		hFile = EOS_Open(pszFilePath,PO_RDONLY|PO_BINARY,PS_IREAD);
		if (hFile < 0)
		{
			return eFailed;
		}	                    		

		// 获得文件大小
		nFileSize = EOS_GetFileSize(hFile);
		szReadContent = malloc(nFileSize+1);
		memset(szReadContent, 0, nFileSize+1);
		nReadByte= EOS_Read(hFile, szReadContent, nFileSize);	
		EOS_Close(hFile);

		//统一判断空串的情况
		if(*((char*)szReadContent) == 0)
		{
			free(szReadContent);
			return eFailed;
		}

		//统一判断非正常json的情况(判断"ret")
		cJSON *json;
		cJSON *tmp;
		json=cJSON_Parse((const char *)szReadContent);
		if(json == NULL)
		{
			cJSON_Delete(json);
			free(szReadContent);
			return eFailed;
		}		
		tmp = cJSON_GetObjectItem(json,"ret");
		if (tmp = NULL)
		{
			cJSON_Delete(json);
			free(szReadContent);
			return eFailed;
		}
		cJSON_Delete(json);

		//各API Json的解析
		switch(accessType)
		{
		case KX_InitialLogin:
			{
				*Response = KaiXinAPI_InitialLogin_JsonParse((char*)szReadContent);
				iRet = ((tResponseInitialLogin*)*Response)->ret;
				break;
			}
		case KX_Profile:
			{
				*Response = KaiXinAPI_Profile_JsonParse((char*)szReadContent);
				iRet = ((tResponseProfile*)*Response)->ret;
				break;
			}
		case KX_GetStatus:
			{
				*Response = KaiXinAPI_GetStatus_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetStatus*)*Response)->ret;
				break;
			}
		case KX_UpdateFriendsNews:
			{
				*Response = KaiXinAPI_UpdateFriendsNews_JsonParse((char*)szReadContent);
				iRet = ((tResponseUpdateFriendsNews*)*Response)->ret;
				break;
			}			
		case KX_RecentNews:
			{
				*Response = KaiXinAPI_RecentNews_JsonParse((char*)szReadContent);
				iRet = ((tResponseRecentNews*)*Response)->ret;
				break;
			}
		case KX_FriendList:
			{
				*Response = KaiXinAPI_FriendList_JsonParse((char*)szReadContent);
				iRet = ((tResponseFriendList*)*Response)->ret;
				break;				
			}	
		case KX_GetFriendCount:
			{
				*Response = KaiXinAPI_GetFriendCount_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetFriendCount*)*Response)->ret;
				break;				
			}
		case KX_AlbumList:
			{
				*Response = KaiXinAPI_AlbumList_JsonParse((char*)szReadContent);
				iRet = ((tResponseAlbumList*)*Response)->ret;
				break;				
			}			
		case KX_GetAlbumCount:
			{
				*Response = KaiXinAPI_GetAlbumCount_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetAlbumCount*)*Response)->ret;
				break;				
			}
		case KX_AlbumPhoto:
			{
				*Response = KaiXinAPI_AlbumPhoto_JsonParse((char*)szReadContent);
				iRet = ((tResponseAlbumPhoto*)*Response)->ret;
				break;				
			}
		case KX_AlbumPhotoFromNews:
			{
				*Response = KaiXinAPI_AlbumPhoto_JsonParse((char*)szReadContent);
				iRet = ((tResponseAlbumPhoto*)*Response)->ret;
				break;				
			}			
		case KX_ApplicationList:
			{
				*Response = KaiXinAPI_ApplicationList_JsonParse((char*)szReadContent);
				iRet = ((tResponseApplicationList*)*Response)->ret;
				break;				
			}
		case KX_SendAMessage:
			{
				*Response = KaiXinAPI_SendAMessage_JsonParse((char*)szReadContent);
				iRet = ((tResponseSendAMessage*)*Response)->ret;
				break;				
			}
		case KX_ReplyComment:
			{
				*Response = KaiXinAPI_ReplyComment_JsonParse((char*)szReadContent);
				iRet = ((tResponseReplyComment*)*Response)->ret;
				break;				
			}
		case KX_ReceivedUserCommentsList:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}
		case KX_ReceivedCommentsList:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}
		case KX_RepasteCommentsList:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}
		case KX_SentCommentsList:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}
		case KX_FriendsCommentList:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}		
		case KX_ReceivedAnObjectComments:
		case KX_ReceivedRepasteComments:
		case KX_ReceivedRecordComments:
		case KX_ReceivedDiaryComments:
		case KX_ReceivedStateComments:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}		
		case KX_SentUserCommentsList:
			{
				*Response = KaiXinApp_UserCommentList_JsonParse((char*)szReadContent);
				iRet = ((tResponseUserCommentList*)*Response)->ret;
				break;				
			}
		case KX_SentCommentDetail:
			{
				*Response = KaiXinAPI_CommentDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseCommentDetail*)*Response)->ret;
				break;				
			}			
		case KX_UserCommentDetail:
			{
				*Response = KaiXinAPI_CommentDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseCommentDetail*)*Response)->ret;
				break;				
			}
		case KX_CommentDetail:
			{
				*Response = KaiXinAPI_CommentDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseCommentDetail*)*Response)->ret;
				break;				
			}		
		case KX_SentUserCommentDetail:
			{
				*Response = KaiXinAPI_CommentDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseCommentDetail*)*Response)->ret;
				break;				
			}			
		case KX_MessageCenter:
			{
				*Response = KaiXinAPI_MessageCenter_JsonParse((char*)szReadContent);
				iRet = ((tResponseMessageCenter*)*Response)->ret;
				break;				
			}
		case KX_GetUserInfos:
			{
				*Response = KaiXinAPI_GetUserInfos_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetUserInfos*)*Response)->ret;
				break;				
			}
		case KX_GetProfileDetail:
			{
				*Response = KaiXinAPI_GetProfileDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetProfileDetail*)*Response)->ret;
				break;				
			}
		case KX_RecordList:
			{
				*Response = KaiXinAPI_RecordList_JsonParse((char*)szReadContent);
				iRet = ((tResponseRecordList*)*Response)->ret;
				break;				
			}
		case KX_GetRecordCount:
			{
				*Response = KaiXinAPI_GetRecordCount_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetRecordCount*)*Response)->ret;
				break;				
			}			
		case KX_FaceList:
			{
				*Response = KaiXinAPI_StatusFaceList_JsonParse((char*)szReadContent);
				iRet = ((tResponseStatusFaceList*)*Response)->ret;
				break;				
			}
		case KX_RepasteIndex:
		case KX_RepasteIndexMore:
			{
				*Response = KaiXinAPI_RepasteIndex_JsonParse((char*)szReadContent);
				iRet = ((tResponseRepasteIndex*)*Response)->ret;
				break;				
			}
		case KX_GetRepasteCount:
			{
				*Response = KaiXinAPI_GetRepasteCount_JsonParse((char*)szReadContent);
				iRet = ((tResponseRepasteIndex*)*Response)->ret;
				break;				
			}
		case KX_DiaryList:
			{
				*Response = KaiXinAPI_DiaryList_JsonParse((char*)szReadContent);
				iRet = ((tResponseDiaryList*)*Response)->ret;
				break;				
			}
		case KX_GetDiaryCount:
			{
				*Response = KaiXinAPI_GetDiaryCount_JsonParse((char*)szReadContent);
				iRet = ((tResponseGetDiaryCount*)*Response)->ret;
				break;				
			}
		case KX_DiaryDetail:
			{
				*Response = KaiXinAPI_DiaryDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseDiaryDetail*)*Response)->ret;
				break;				
			}			
		case KX_MessagesList:
			{
				*Response = KaiXinAPI_MessagesList_JsonParse((char*)szReadContent);
				iRet = ((tResponseMessagesList*)*Response)->ret;
				break;				
			}
		case KX_SentMessagesList:
			{
				*Response = KaiXinAPI_MessagesList_JsonParse((char*)szReadContent);
				iRet = ((tResponseMessagesList*)*Response)->ret;
				break;				
			}
		case KX_SystemMessage:
			{
				*Response = KaiXinAPI_SystemMessages_JsonParse((char*)szReadContent);
				iRet = ((tResponseSystemMessages*)*Response)->ret;
				break;				
			}
		case KX_MessageDetail:
			{
				*Response = KaiXinAPI_MessageDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseMessageDetail*)*Response)->ret;
				break;				
			}
		case KX_SendBirthdayGift:
			{
				*Response = KaiXinAPI_SendBirthdayGift_JsonParse((char*)szReadContent);
				iRet = eSucceed; //需要显示错误信息
				break;				
			}
		case KX_AcceptFriendRequest:
			{
				*Response = KaiXinAPI_SendBirthdayGift_JsonParse((char*)szReadContent);
				iRet = ((tResponseFriendRequest*)*Response)->ret;
				break;				
			}
		case KX_RefuseFriendRequest:
			{
				*Response = KaiXinAPI_SendBirthdayGift_JsonParse((char*)szReadContent);
				iRet = ((tResponseFriendRequest*)*Response)->ret;
				break;				
			}
		case KX_BirthdayList:
			{
				*Response = KaiXinAPI_BirthdayList_JsonParse((char*)szReadContent);
				iRet = ((tResponseBirthdayList*)*Response)->ret;
				break;				
			}
		case KX_GardenDetail:
			{
				*Response = KaiXinAPI_GardenDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseGardenDetail*)*Response)->ret;
				break;				
			}
		case KX_GardenHarvest:
			{
				*Response = KaiXinAPI_GardenHarvest_JsonParse((char*)szReadContent);
				iRet = ((tResponseGardenHarvest*)*Response)->ret;
				break;				
			}
		case KX_RanchDetail:
			{
				*Response = KaiXinAPI_RanchDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseRanchDetail*)*Response)->ret;
				break;				
			}			
		case KX_RanchHarvest:
			{
				*Response = KaiXinAPI_RanchHarvest_JsonParse((char*)szReadContent);
				iRet = ((tResponseRanchHarvest*)*Response)->ret;
				break;				
			}			
		case KX_Product:
			{
				*Response = KaiXinAPI_RanchProduct_JsonParse((char*)szReadContent);
				iRet = ((tResponseRanchProduct*)*Response)->ret;
				break;				
			}
		case KX_GardenList:
			{
				*Response = KaiXinAPI_GardenList_JsonParse((char*)szReadContent);
				iRet = ((tResponseGardenList*)*Response)->ret;
				break;				
			}
		case KX_RanchList:
			{
				*Response = KaiXinAPI_RanchList_JsonParse((char*)szReadContent);
				iRet = ((tResponseRanchList*)*Response)->ret;
				break;				
			}
		case KX_RepasteDetail:
		case KX_RefreshVote:
		case KX_RefreshTag:
			{
				*Response = KaiXinAPI_RepasteDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseRepasteDetail*)*Response)->ret;
				break;				
			}
		case KX_DeleteComment:
			{
				*Response = KaiXinAPI_DeleteComment_JsonParse((char*)szReadContent);
				iRet = ((tResponseDeleteComment*)*Response)->ret;
				break;				
			}
		case KX_DeleteMessage:
			{
				*Response = KaiXinAPI_DeleteMessage_JsonParse((char*)szReadContent);
				iRet = ((tResponseDeleteMessage*)*Response)->ret;
				break;				
			}
		case KX_VoteDetail:
			{
				*Response = KaiXinAPI_VoteDetail_JsonParse((char*)szReadContent);
				iRet = ((tResponseVoteDetail*)*Response)->ret;
				break;				
			}			
		case KX_PostRepastesVote:
		case KX_PostTag:
		case KX_PostVote:			
			{
				*Response = KaiXinAPI_PostVote_JsonParse((char*)szReadContent);
				iRet = eSucceed; //需要显示错误信息
				break;				
			}
		case KX_PostRepaste:			
			{
				*Response = KaiXinAPI_PostRepaste_JsonParse((char*)szReadContent);
				iRet = ((tResponsePostRepaste*)*Response)->ret;
				break;				
			}
		case KX_Notice:
			{
				*Response = KaiXinAPI_Notice_JsonParse((char*)szReadContent);
				iRet = ((tResponseNotice*)*Response)->ret;
				break;
			}
		case KX_PokesList:
			{
				*Response = KaiXinAPI_PokeList_JsonParse((char*)szReadContent);
				iRet = ((tResponsePokeList*)*Response)->ret;
				break;
			}			
		case KX_SendPoke:
			{
				*Response = KaiXinAPI_SendPoke_JsonParse((char*)szReadContent);
				iRet = ((tResponseSendPoke*)*Response)->ret;
				break;
			}
		case KX_PostComment:
			{
				*Response = KaiXinAPI_PostComment_JsonParse((char*)szReadContent);
				iRet = ((tResponsePostComment*)*Response)->ret;
				break;
			}
		default:
			{
				//未实现的
				free(szReadContent);
				return eFailed;				
			}
		}

		free(szReadContent);

		if(iRet != eSucceed)
		{
			delete (*Response);
			*Response = NULL;
		}
		return iRet;
	}

	return eFailed;
}

/**
 * \统一判断返回的Json是否正确 
 *
 * \param accessType
 * \param errorinfo
 *
 * \return 
 */
Boolean KaiXinAPI_JsonParse_bSuccess(Kx_AccessType accessType, TUChar * errorinfo)
{
	int bRet = FALSE;
	char* FilePath = NULL;

	FilePath = KX_GetFileName(accessType);
	if(FilePath == NULL)
		return FALSE;

	TUChar pszFilePath[EOS_FILE_MAX_PATH];
	TUChar pszTemp[EOS_FILE_MAX_FNAME];
//	TUString::StrCopy(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
//	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
//	TUString::StrCat(pszFilePath,pszTemp);
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_CACHE, pszFilePath);
	TUString::StrGBToUnicode(pszTemp,(Char*)FilePath);
	TUString::StrCat(pszFilePath,pszTemp);

	if (EOS_IsFileExist(pszFilePath))
	{
		Handle hFile = NULL;			// file handle
		Int32 nFileSize = 0;			// 文件大小
		Int32 nReadByte = 0;			// 具体读出的字节数
		void * szReadContent = NULL;

		hFile = EOS_Open(pszFilePath,PO_RDONLY|PO_BINARY,PS_IREAD);
		if (hFile < 0)
		{
			return FALSE;
		}	                    		

		// 获得文件大小
		nFileSize = EOS_GetFileSize(hFile);
		szReadContent = malloc(nFileSize+1);
		memset(szReadContent, 0, nFileSize+1);
		nReadByte= EOS_Read(hFile, szReadContent, nFileSize);	
		EOS_Close(hFile);

		//空文件判断
		if(*((char*)szReadContent) == 0)
		{
			free(szReadContent);
			return FALSE;
		}

		//统一判断"ret"
		cJSON *json;
		cJSON *tmpRet;
		cJSON *tmpMsg;
		json=cJSON_Parse((const char *)szReadContent);
		if(json == NULL)
		{
			cJSON_Delete(json);
			free(szReadContent);
			return FALSE;
		}

		tmpRet = cJSON_GetObjectItem(json,"ret");
		if (tmpRet)
		{
			if(tmpRet->valueint == 1)
				bRet = TRUE;
			else
			{
				bRet = FALSE;
			}

			if(errorinfo != NULL)
			{
				tmpMsg = cJSON_GetObjectItem(json,"msg");
				if (tmpMsg)
				{
					if( strlen(tmpMsg->valuestring) > 0)
					{
						char errorstring[ERROR_INFO_LEN] = {0};
						STRCPY_Ex(errorstring, tmpMsg->valuestring);
						TUString::StrUtf8ToStrUnicode (errorinfo, (const Char *)errorstring);
					}
				}
				else
				{
					//增加花园&牧场未添加组件的错误提示
					if( ((accessType == KX_RanchDetail) || (accessType == KX_GardenDetail))&&
						(tmpRet->valueint == -7) )
					{
						TUString::StrCopy(errorinfo, TResource::LoadConstString(APP_KA_ID_STRING_HaveNotApp));
					}	
				}
			}
		}

		cJSON_Delete(json);

		free(szReadContent);
	}

	return bRet;
}

/**
 * 获取设置 
 *
 * \return 
 */
int KaiXinAPI_GetConfig(void)
{
	int iRet = eFailed;
	TUChar pszFilePath[EOS_FILE_MAX_PATH];
	TUChar pszFolderPath[EOS_FILE_MAX_PATH];
	TUChar pszTemp[EOS_FILE_MAX_FNAME];

//	TUString::StrCopy(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
//	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
//	TUString::StrCat(pszFilePath,pszTemp);
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_DATA, pszFilePath);
	
	TUString::StrCopy(pszFolderPath,pszFilePath);
	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_CONFIG_FILE);
	TUString::StrCat(pszFilePath,pszTemp);
	if (EOS_IsFileExist(pszFilePath))
	{
		Handle hFile = NULL;			// file handle
		Int32 nFileSize = 0;			// 文件大小
		Int32 nReadByte = 0;			// 具体读出的字节数

		hFile = EOS_Open(pszFilePath,PO_RDONLY|PO_BINARY,PS_IREAD);
		if (hFile < 0)
		{
			return eFailed;
		}	                    		

		nFileSize = EOS_GetFileSize(hFile);

		//如果设置文件和结构体大小不一致,则直接返回
		if(nFileSize != sizeof(tUserInfo))
		{
			iRet = eFailed;
		}
		else
		{
			nReadByte= EOS_Read(hFile, (void*)&KaiXinUserInfo, sizeof(tUserInfo));
			//这些不需要保存,以后需要分开到不同结构体里
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_ALL] = 0;
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_MESSAGE] = 0;
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_USER_COMMENT] = 0;
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_POST_COMMENT] = 0;
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_SYS_MESSAGE] = 0;
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_REPLY_USER_COMMENT] = 0;
			KaiXinUserInfo.NoticeCount[NOTICE_TYPE_REPLY_POST_COMMENT] = 0;
			memset(KaiXinUserInfo.status, 0x0, sizeof(KaiXinUserInfo.status));
			memset(KaiXinUserInfo.logoPath, 0x0, sizeof(KaiXinUserInfo.logoPath));

			iRet = eSucceed;
		}
		EOS_Close(hFile);
	}
	else if(EOS_IsFileExist(pszFolderPath) == FALSE )
	{
		//目录不存在的话先创建目录
		if(EOS_MakeDir(pszFolderPath))
		{
			iRet = eSucceed;
		}
	}

	return iRet;
}

/**
 * 保存设置 
 *
 * \return 
 */
int KaiXinAPI_SetConfig(void)
{
	int iRet = eFailed;
	TUChar pszFilePath[EOS_FILE_MAX_PATH];
	TUChar pszTemp[EOS_FILE_MAX_FNAME];

//	TUString::StrCopy(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
//	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
//	TUString::StrCat(pszFilePath,pszTemp);
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_DATA, pszFilePath);
	
	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_CONFIG_FILE);
	TUString::StrCat(pszFilePath,pszTemp);
	if (EOS_IsFileExist(pszFilePath))
		EOS_Delete(pszFilePath);

	Handle hFile = NULL;			// file handle
	Int32 nFileSize = 0;			// 文件大小
	Int32 nReadByte = 0;			// 具体读出的字节数

	hFile = EOS_Open(pszFilePath, PO_TRUNC|PO_BINARY|PO_CREAT|PO_RDWR, PS_IWRITE);
	if (hFile < 0)
	{
		return eFailed;
	}	                    		

	EOS_Write(hFile, (void*)&KaiXinUserInfo, sizeof(tUserInfo));
	EOS_Close(hFile);
	return eSucceed;
}

/**
 * 获取图片文件的格式 
 *
 * \param pszExtName
 *
 * \return 
 */
IT_LoadableImageFormat GetImageFormatEx(const TUChar* pszExtName)
{
	IT_LoadableImageFormat Format;
	char szExt[20];

	Format = IT_LOAD_FMT_UNKNOWN;
	if (pszExtName == NULL || TUString::StrLen(pszExtName) >= 20 || TUString::StrLen(pszExtName) == 0)
	{
		return Format;
	}

	ustrncpy_utf8(szExt, pszExtName, 20-1);

	if (_T_stricmp(szExt, ".png") == 0)
	{
		Format = IT_LOAD_FMT_PNG;
	} 
	else if (_T_stricmp(szExt, ".gif") == 0)
	{
		Format = IT_LOAD_FMT_GIF;
	}
	else if (_T_stricmp(szExt, ".jpg") == 0)
	{
		Format = IT_LOAD_FMT_JPG;
	}
	else if (_T_stricmp(szExt, ".jpeg") == 0)
	{
		Format = IT_LOAD_FMT_JPG;
	}
	else if (_T_stricmp(szExt, ".bmp") == 0)
	{
		Format = IT_LOAD_FMT_BMP;
	}
	else if (_T_stricmp(szExt, ".tif") == 0)
	{
		Format = IT_LOAD_FMT_TIF;
	}
	else if (_T_stricmp(szExt, ".ebp") == 0)
	{
		Format = IT_LOAD_FMT_EBP;
	}
	else if (_T_stricmp(szExt, ".wbmp") == 0)
	{
		Format = IT_LOAD_FMT_WBMP;
	}

	return Format;
}

/**
 * 获取本地图片文件的TBitmap 
 *
 * \param pszPath
 *
 * \return 
 */
TBitmap* LoadImgByPath(const TUChar* pszPath)
{
	bool                   bRes;
	IT_LoadableImageFormat fm;
	Image m_objImg;

	ImageLoader            objImgLoader;
	/** Image对象，保存从文件载入的图片 */
	/** 由Image转化的TBitmap指针 */
	TBitmap             *m_pBmp = NULL;
	TBitmap             *m_pRetBmp = NULL;
	/** 是PNG图片吗？ */
	Boolean             m_bIsPng = FALSE;

	bRes = FALSE;
	fm   = IT_LOAD_FMT_UNKNOWN;

	m_objImg.clearImage();	

	if (pszPath && *pszPath
		&& IsImageFileVaild(pszPath) 
		&& (fm = GetImageFormatEx(TUString::StrRChr(pszPath, '.'))) != IT_LOAD_FMT_UNKNOWN)
	{   
		if (fm == IT_LOAD_FMT_PNG)
		{
			bRes = IT_LoadPngFileToTBitmap(pszPath, &m_pBmp) >= 0;
			if(bRes)
			{
				m_bIsPng = TRUE;
			}
			else
			{
				m_pBmp = NULL;
				m_bIsPng = FALSE;
			}
		}
		else
		{
			bRes = objImgLoader.loadImage(m_objImg, pszPath, fm);      
		}
	}  

	if (bRes && !m_bIsPng)
	{
		m_pBmp = const_cast<TBitmap *>(m_objImg.GetTBitmap());
	}

	if(m_pBmp != NULL)
	{
		m_pRetBmp = m_pBmp->Clone();
		//PNG需要手动释放
		if(m_bIsPng == TRUE)
			m_pBmp->Destroy();
	}

	return m_pRetBmp;
}

/**
 * 通过URL获取TBitmap
 *
 * \param pURL
 *
 * \return 
 */
TBitmap* LoadImgByUrl(char* pURL)
{
	TBitmap             *m_pRetBmp = NULL;

	if(pURL!=NULL && *pURL != 0)
	{
		TUChar* pszFilePath = NULL;

		pszFilePath = FilePathFromUrl(pURL);
		if(pszFilePath != NULL)
		{
			m_pRetBmp = LoadImgByPath(pszFilePath);
			free(pszFilePath);
		}
	}	

	return m_pRetBmp;
}


/**
 * 获取标题栏按钮的位置
 * 此函数需要淘汰
 * \param nX
 * \param nY
 * \param nWidth
 * \param nHeight
 *
 * \return 
 */
int GetTitleButtonRect(Coord*  nX,  Coord*  nY,  Coord*  nWidth,  Coord*  nHeight )  
{
	*nX = 5;
	*nY = 6;
	*nWidth = 80;
	*nHeight = 35;

	return eSucceed;
}

/**
 * 获取标题栏的位置
 * 此函数需要淘汰
 * \param pszTitle
 * \param nX
 * \param nY
 * \param nWidth
 * \param nHeight
 *
 * \return 
 */
int GetTitleLabelRect(const TUChar* pszTitle, Coord*  nX,  Coord*  nY,  Coord*  nWidth,  Coord*  nHeight )  
{

	*nX = 120;
	*nY = 10;
	*nWidth = 220;
	*nHeight = 30;

	return eSucceed;
}


/**
 * url编码 
 *
 * \param pszText
 *
 * \return 
 */
char* urlEncode(char* pszText)
{
	char* pszTextEncode = NULL;
	int nLen = 0;
	if(pszText == NULL || *pszText == 0)
		return NULL;

	nLen = strlen((char*)pszText);
	pszTextEncode = (char*)malloc(nLen*3 + 1);
	MemSet(pszTextEncode, 0, nLen*3 + 1);
	for(int i=0;i <nLen; i++)
	{
		if( (pszText[i] >= 'a' && pszText[i] <= 'z') || 
			(pszText[i] >= 'A' && pszText[i] <= 'Z') || 
			(pszText[i] >= '0' && pszText[i] <= '9') )
			sprintf( pszTextEncode, "%s%c", pszTextEncode, pszText[i] );
		else
			sprintf( pszTextEncode, "%s%%%02x", pszTextEncode, (UInt8)(pszText[i]) );
	}

	return pszTextEncode;
}


/**
 * Url下载后保存的文件名(带路径), 
 * 由调用者释放
 * \param pURL
 *
 * \return 
 */
TUChar* FilePathFromUrl(char* pURL)
{
	if(pURL==NULL && *pURL == 0)
		return NULL;

	char* FilePath1 = NULL;	
	char FilePath2[256];	
	char* FilePath3 = NULL;

	//获得'/'之后的字符串
	FilePath1 = strrchr(pURL, '/');
	if(FilePath1 == NULL)
		return NULL;
	*FilePath1 ++;

	//加强带验证码url的处理,如http://wap.kaixin001.com/123.jpg?234253245435
	strcpy(FilePath2, FilePath1);
	FilePath3 = strchr(FilePath2, '?');
	if(FilePath3 != NULL)
		*FilePath3 = '\0';

	TUChar* pszFilePath = NULL;
	TUChar pszTemp[EOS_FILE_MAX_FNAME];

	pszFilePath = (TUChar*)malloc(EOS_FILE_MAX_PATH*sizeof(TUChar));
	memset(pszFilePath, 0, EOS_FILE_MAX_PATH*sizeof(TUChar));

//	TUString::StrCopy(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
//	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
//	TUString::StrCat(pszFilePath,pszTemp);
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_CACHE, pszFilePath);
	TUString::StrGBToUnicode(pszTemp,(Char*)FilePath2);
	TUString::StrCat(pszFilePath,pszTemp);

	return pszFilePath;
}

/**
 * API是否需要统一处理 
 *
 * \param accessType
 *
 * \return 
 */
Boolean GetApiHandle(Kx_AccessType accessType)
{
	Boolean bHandle = FALSE;
	for(int i=0; i<ARR_SIZE(KxAppUrl); i++)
	{
		if(accessType == KxAppUrl[i].nType)
		{
			bHandle = KxAppUrl[i].bHandle;
			break;
		}
	}

	return bHandle;
}

/**
 * API是否有等待界面
 *
 * \param accessType
 *
 * \return 
 */
Boolean GetApiNeedWaitingBox(Kx_AccessType accessType)
{
	Boolean bNeedWaitingBox = FALSE;
	for(int i=0; i<ARR_SIZE(KxAppUrl); i++)
	{
		if(accessType == KxAppUrl[i].nType)
		{
			bNeedWaitingBox = KxAppUrl[i].bNeedWaitingBox;
			break;
		}
	}

	return bNeedWaitingBox;
}


/**
 * 创建应用退出按钮
 *
 * \param pWindow
 *
 * \return 
 */
//
Int32 SetAppExitButton(TWindow * pWindow)
{
	TButton *pExitBtn;
	Int32 m_ExitBtnID = 0;
	TRectangle BtnRC(SCR_W-BUTTON_X-BUTTON_W, BUTTON_Y, BUTTON_W, BUTTON_H);
	TFont tFont;

	TUChar sTitleString[128] ={0};
	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53_over); 

	tFont.Create(FONT_LARGE_BUTTON_CAPTION, FONT_LARGE_BUTTON_CAPTION, FONT_STYLE_BOLD);	

	pExitBtn = new TButton;	
	if(pExitBtn->Create(pWindow))
	{		
		pExitBtn->SetBounds(&BtnRC);	
		m_ExitBtnID = pExitBtn->GetId();	

		pExitBtn->SetFont(tFont);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FORE,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_BACK,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FOCUS_FORE,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FOCUS_BACK,RGB_COLOR_WHITE);

		pExitBtn->SetCaption(TResource::LoadConstString(APP_KA_ID_STRING_Exit),FALSE);
		pExitBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pExitBtn->SetImage(pNormalBmp,0);
		pExitBtn->SetImage(pOverBmp,1);		
		pExitBtn->Show(TRUE);
	}

	return m_ExitBtnID;
}


/**
 * 创建返回按钮
 *
 * \param pWindow
 *
 * \return 
 */
Int32 SetAppBackButton(TWindow * pWindow)
{
	TButton *pExitBtn;
	Int32 m_ExitBtnID = 0;
	TRectangle BtnRC(SCR_W-BUTTON_X-BUTTON_W, BUTTON_Y, BUTTON_W, BUTTON_H);
	TFont tFont;

	TUChar sTitleString[128] ={0};
	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53_over); 

	tFont.Create(FONT_LARGE_BUTTON_CAPTION, FONT_LARGE_BUTTON_CAPTION, FONT_STYLE_BOLD);	

	pExitBtn = new TButton;	
	if(pExitBtn->Create(pWindow))
	{		
		pExitBtn->SetBounds(&BtnRC);	
		m_ExitBtnID = pExitBtn->GetId();	

		pExitBtn->SetFont(tFont);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FORE,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_BACK,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FOCUS_FORE,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FOCUS_BACK,RGB_COLOR_WHITE);

		pExitBtn->SetCaption(TResource::LoadConstString(APP_KA_ID_STRING_Back),FALSE);
		pExitBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pExitBtn->SetImage(pNormalBmp,0);
		pExitBtn->SetImage(pOverBmp,1);	
		pExitBtn->SetEnabled(TRUE);
		pExitBtn->Show(TRUE);
	}

	return m_ExitBtnID;
}

/**
 * 创建登录按钮
 *
 * \param pWindow
 *
 * \return 
 */
Int32 SetAppLoginButton(TWindow * pWindow)
{
	TButton *pExitBtn;
	Int32 m_ExitBtnID = 0;
	TRectangle BtnRC(BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H);
	TFont tFont;

	TUChar sTitleString[128] ={0};
	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_button53_over); 

	tFont.Create(FONT_LARGE_BUTTON_CAPTION, FONT_LARGE_BUTTON_CAPTION, FONT_STYLE_BOLD);	

	pExitBtn = new TButton;	
	if(pExitBtn->Create(pWindow))
	{		
		pExitBtn->SetBounds(&BtnRC);	
		m_ExitBtnID = pExitBtn->GetId();	

		pExitBtn->SetFont(tFont);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FORE,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_BACK,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FOCUS_FORE,RGB_COLOR_WHITE);
		pExitBtn->SetColor(CTL_COLOR_TYPE_FOCUS_BACK,RGB_COLOR_WHITE);

		pExitBtn->SetCaption(TResource::LoadConstString(APP_KA_ID_STRING_Login),FALSE);
		pExitBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pExitBtn->SetImage(pNormalBmp,0);
		pExitBtn->SetImage(pOverBmp,1);		
		pExitBtn->Show(TRUE);
	}

	return m_ExitBtnID;
}

/**
 * 创建应用刷新按钮
 *
 * \param pWindow
 *
 * \return 
 */
Int32 SetAppRefreshButton(TWindow * pWindow)
{
	TButton *pRefreshBtn;
	Int32 m_RefreshBtnID = 0;
	TRectangle BtnRC(BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H);

	TUChar sTitleString[128] ={0};
	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_but_refresh1);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_but_refresh1_over); 

	pRefreshBtn = new TButton;	
	if(pRefreshBtn->Create(pWindow))
	{		
		pRefreshBtn->SetBounds(&BtnRC);	
		m_RefreshBtnID = pRefreshBtn->GetId();	

		pRefreshBtn->SetCaption(TUSTR_Kx_NULL,FALSE);
		pRefreshBtn->SetStyles(BTN_STYLES_GRAPGICS);
		pRefreshBtn->SetImage(pNormalBmp,0);
		pRefreshBtn->SetImage(pOverBmp,1);		
		pRefreshBtn->Show(TRUE);
	}

	return m_RefreshBtnID;
}

/**
 * 创建应用编辑按钮
 *
 * \param pWindow
 *
 * \return 
 */
Int32 SetAppWriteButton(TWindow * pWindow)
{
	TButton *pBtn;
	Int32 m_BtnID = 0;
	TRectangle BtnRC(BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H);

	TUChar sTitleString[128] ={0};
	const TBitmap * pNormalBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_write_but);
	const TBitmap * pOverBmp = TResource::LoadConstBitmap(APP_KA_ID_BITMAP_write_but_over);

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


/**
 * 获得Html格式数据的文件名 
 * 需要调用释放
 * \param accessType
 *
 * \return 
 */
char* KX_GetHtmlContentFileName(Kx_AccessType accessType)
{
	int i = 0;
	char* pszDes = NULL;

	//查找对应的结构体
	for(i=0; i<ARR_SIZE(KxAppUrl);i++)
	{
		if(KxAppUrl[i].nType == accessType)
		{
			if(strlen(KxAppUrl[i].FilePath) ==0)
				return NULL;
			else
			{
				int nLen = 0;
				pszDes = StrDump(KxAppUrl[i].FilePath);
				nLen = strlen(pszDes);
				strcpy(&pszDes[nLen - 3], "htm");
				return pszDes;
			}
		}
	}
	//未发现对应的结构体
	return NULL;
}


/**
 * 生成Html文件
 *
 * \param accessType
 * \param pszContent
 *
 * \return 
 */
int MakeHtmlFile(Kx_AccessType accessType, char* pszContent)
{
	char* pszUrl = NULL;
	char* pszFilename = NULL;
	TUChar pszFilePath[EOS_FILE_MAX_PATH];    // 文件路径 
	TUChar pszTemp[EOS_FILE_MAX_FNAME];

	if (!pszContent)
	{
		return eFailed;
	}

	pszFilename = KX_GetHtmlContentFileName(accessType);
	MemSet(pszFilePath, 0, EOS_FILE_MAX_PATH * sizeof(TUChar));

//	TUString::StrCopy(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
//	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
//	TUString::StrCat(pszFilePath,pszTemp);
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_CACHE, pszFilePath);
	
	TUString::StrGBToUnicode(pszTemp,(Char*)pszFilename);
	TUString::StrCat(pszFilePath,pszTemp);

	delete pszFilename;
	pszFilename = NULL;

	if (EOS_IsFileExist(pszFilePath))
		EOS_Delete(pszFilePath);

	Handle hHtmlFile = EOS_Open(pszFilePath, PO_CREAT | PO_BINARY | PO_WRONLY | PO_TRUNC, PS_IWRITE);
	if(hHtmlFile < 0)
	{
		return eFailed;
	}
	else
	{
		//增加UTF-8的文件头
		EOS_Write(hHtmlFile, "\xEF\xBB\xBF", 3);
		EOS_Write(hHtmlFile, pszContent, strlen(pszContent));
		EOS_Close(hHtmlFile);
	}

	return eSucceed;
}

/**
 * 本地html文件的url格式 
 * 调用释放
 * \param accessType
 *
 * \return 
 */

TUChar* GetHtmlFileUrl(Kx_AccessType accessType)
{
	char* pszFilename = NULL;
	TUChar* pszFilePath = NULL;
	TUChar pszTemp[EOS_FILE_MAX_FNAME];
	char pszUrlHead[EOS_FILE_MAX_PATH];

	pszFilePath = new TUChar[EOS_FILE_MAX_PATH];
	MemSet(pszFilePath, 0, EOS_FILE_MAX_PATH * sizeof(TUChar));

	pszFilename = KX_GetHtmlContentFileName(accessType);

	memset(pszUrlHead, 0, EOS_FILE_MAX_PATH*sizeof(char));
#ifdef _TRANZDA_VM_
	strcpy(pszUrlHead, "file://");
	//TUString::StrCopy(pszFilePath,(TUChar*)L"file://");
#else
	strcpy(pszUrlHead, "file:///");
#endif

	TUString::StrGBToUnicode(pszTemp,(Char*)pszUrlHead);
	TUString::StrCopy(pszFilePath,pszTemp);

//	TUString::StrCat(pszFilePath,EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_LOCAL_DATA));
//	TUString::StrGBToUnicode(pszTemp,(Char*)KAIXIN_FOLDER);
//	
	SS_GetApplicationPath(AppName_App_KaiXin, SS_APP_PATH_TYPE_CACHE, pszTemp);
	TUString::StrCat(pszFilePath,pszTemp);
	
	TUString::StrGBToUnicode(pszTemp,(Char*)pszFilename);
	TUString::StrCat(pszFilePath,pszTemp);

	delete pszFilename;
	pszFilename = NULL;	

	return pszFilePath;
}

#define NAPPNEEDSIZE	2048	//kByte

/**
 * 检查Cache空间是否足够 
 *
 * \return 
 */
Boolean CheckCacheIsEnough(void)
{
    Int32 nSectorsPerClusterP;
    Int32 nBytesPerSectorP;
    Int32 nNumberOfFreeClustersP;
    Int32 nTotalNumberOfClustersP;
    Int64 nStorageFreeSize;
    TUChar        szFilePath[EOS_FILE_MAX_FNAME] = {0};    // 文件路径
    Boolean       bResult;

    bResult = FALSE;
    nSectorsPerClusterP=0;
    nBytesPerSectorP=0;
    nNumberOfFreeClustersP=0;
    nTotalNumberOfClustersP=0;
    nStorageFreeSize = 0;

    // 获得缓存目录
    TUString::StrNCopy(szFilePath, EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_CACHE),EOS_FILE_MAX_FNAME-1);
    //获得目录存储空间情况
    EOS_GetDiskFreeSpace(szFilePath,&nSectorsPerClusterP,&nBytesPerSectorP,  &nNumberOfFreeClustersP,&nTotalNumberOfClustersP);
    //计算可用空间
    nStorageFreeSize = nNumberOfFreeClustersP*nSectorsPerClusterP;
    nStorageFreeSize *= nBytesPerSectorP;
    //单位换算成KB
    nStorageFreeSize /= 1024;

    //判断是否空闲目录是否达到应用需要。NAPPNEEDSIZE为商城运行需要的Cache大小(KB) 
    if (nStorageFreeSize > NAPPNEEDSIZE)
    {
        bResult = TRUE;
    }
    else
    {
        //否则首先删除自己Cache目录下的文件。
        TUChar        szSelfCachePath[EOS_FILE_MAX_PATH] = {0};
        DSTAT         objStat;
        Boolean       bFindResult;

        // 填写查找文件名
        bFindResult = FALSE;
        SS_GetApplicationPath(AppName_App_KaiXin,SS_APP_PATH_TYPE_CACHE,szSelfCachePath);
	TUString::StrCat(szSelfCachePath, TUSTR_Kx_AllFileFilter);
	
        //ustrncat_utf8(szSelfCachePath, "*.*", EOS_FILE_MAX_PATH-1-TUString::StrLen(szSelfCachePath));

        // 查找删除文件
        bFindResult = EOS_FindFirst(&objStat, szSelfCachePath);
        while (bFindResult)
        {
            // 判断不是.和..和cfg文件才删除
            if (TUString::StrCompare(objStat.lfname, TUSTR_Kx_Dot) != 0
                && TUString::StrCompare(objStat.lfname, TUSTR_Kx_DDot) != 0
                && TUString::StrCompare(objStat.lfname, TUSTR_Kx_Cfg) != 0
                )
            {
                MemSet(szSelfCachePath,0,EOS_FILE_MAX_PATH);
                SS_GetApplicationPath(AppName_App_KaiXin,SS_APP_PATH_TYPE_CACHE,szSelfCachePath);
                TUString::StrNCat(szSelfCachePath, objStat.lfname, 
                    EOS_FILE_MAX_PATH-1-TUString::StrLen(szSelfCachePath));
                EOS_Delete(szSelfCachePath);
            }                               

            bFindResult = EOS_FindNext(&objStat);
        }
        EOS_FindDone(&objStat);

        //获得目录存储空间情况
        EOS_GetDiskFreeSpace(szFilePath,&nSectorsPerClusterP,&nBytesPerSectorP, &nNumberOfFreeClustersP,&nTotalNumberOfClustersP);
        //计算可用空间
        nStorageFreeSize = nNumberOfFreeClustersP*nSectorsPerClusterP;
        nStorageFreeSize *= nBytesPerSectorP;
        //单位换算成KB
        nStorageFreeSize /= 1024;

        //判断是否空闲目录是否达到应用需要。NAPPNEEDSIZE为商城运行需要的Cache大小(KB) 
        if (nStorageFreeSize > NAPPNEEDSIZE)
        {
            bResult = TRUE;
        }
        else
        {
            Int32 hHandle;
            hHandle=EOS_RequestMoreCacheRoom(AppName_App_KaiXin, NAPPNEEDSIZE);
            if (EOS_RequestMoreCacheRoomCheck(hHandle)>=0)
            {
                bResult = TRUE;
            }
        }

    }
    return bResult;
}

