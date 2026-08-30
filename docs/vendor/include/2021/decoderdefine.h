/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       : WZY
** Date         : 2011-03-12
** Name         : decoderconfig.h
** Version      : 1.0
1:创建
***********************************************************************/

#ifndef _DECODER_DEFINE_H_
#define _DECODER_DEFINE_H_

const unsigned int MSG_USER_NAME_LEN = 36;
const unsigned int MSG_PASSWD_LEN = 36;
const unsigned char	COMPUTER_NAME_LEN = 36;
const unsigned int DEC_MAX_CHNN_NUM = 64;

typedef enum _dec_cfg_item_id
{
	//此范围ID存储系统基本配置的杂项
	DEC_NCFG_ITEM_SYSTEM_BASE = 0,

	DEC_NCFG_ITEM_DEVICE_ID,				//设备ID，unsigned int
	DEC_NCFG_ITEM_DEVICE_NAME,				//设备名称，NCFG_INFO_SHORT_NAME

	//添加的配置选项zhouhb
	DEC_NCFG_ITEM_SOFT_VERSION,			//软件版本号	unsigned int
	DEC_NCFG_ITEM_MAX_CHANNAL,	//解码器通道总数	unsigned int
	DEC_NCFG_ITEM_PRODUCT_ID,		//产品ID号(也就是所谓的产品类型)	unsigned int
	DEC_NCFG_ITEM_PRODUCT_SUB_ID,	//产品子ID号	unsigned int
	DEC_NCFG_ITEM_HARDWARE_VERSION,	//硬件版本	char[VERSION_LEN]
	DEC_NCFG_ITEM_MCU_VERSION,		//MCU版本	char[VERSION_LEN]
	DEC_NCFG_ITEM_KERNEL_VERSION,	//内核版本	char[VERSION_LEN]


	DEC_NCFG_ITEM_LIVE_AUDIO_VOLUME,		//系统音量unsigned int
	DEC_NCFG_ITEM_DATE_FORMAT,				//日期格式，unsigned int
	DEC_NCFG_ITEM_HOUR_FORMAT,				//时间格式：H或者H。unsigned int

	//NCFG_ITEM_LANGUAGE,					//语言，unsigned int
	DEC_NCFG_ITEM_TIME_ZONE,				//时区，int
	DEC_NCFG_ITEM_TIME_SYNC,				//是否网络时间同步，unsigned int
	DEC_NCFG_ITEM_TIME_SERVER,		//网络时间同步服务器地址，NCFG_INFO_LONG_NAME
	DEC_NCFG_ITEM_VGA_RESOLUTION,	//显示器分辨率，unsigned int，

	//NCFG_ITEM_VGA_REFRESH,			 //显示器屏幕刷新率,VGA_SUPPORT_REFRSHHZ[n]
	DEC_NCFG_ITEM_USER,					//用户信息，NCFG_INFO_USER [MAX_USER_NUM]
	DEC_NCFG_ITEM_DAYLIGHT_INFO,		//夏令时信息，DAYLIGHT_INFO
	DEC_NCFG_ITEM_MAX_CLIENT_NUM,   	//最大网络用户数目unsigned int
	DEC_NCFG_ITEM_TVWALL_CONFIG_INFO,	//解码器连接前端设备的信息，后跟的数据部分是：TVWALL_SWITCH_T[MAX_CHNN_NUM]

	DEC_NCFG_ITEM_SYSTEM_END,


	//网络部分
	DEC_NCFG_ITEM_NET_BASE = 0x0100,
	//NCFG_ITEM_UPNP_ENABLE,			//是否启动UPNP功能, unsigned int
	//NCFG_ITEM_UPNP_FRIENDLY_NAME,	//UPNP设备显示的名字, NCFG_INFO_LONG_NAME
	DEC_NCFG_ITEM_HTTP_PORT,				//HTTP 端口, unsigned int
	DEC_NCFG_ITEM_SERVER_PORT,				//网络服务端口，unsigned int
	DEC_NCFG_ITEM_NETWORK_ADDR_INFO,		//网络地址相关信息，NETWORK_ADDR_INFO

	DEC_NCFG_ITEM_DNS_1,					//unsigned int
	DEC_NCFG_ITEM_DNS_2,					//unsigned int
	//NCFG_ITEM_DDNS_INFO,				//DDNS信息，DDNS_INFO
	DEC_NCFG_ITEM_PPPOE_INFO,				//PPPoE的相关信息，PPPOE_INFO

	DEC_NCFG_ITEM_NETINFO_END
}DEC_NCFG_ITEM_ID;

//CMS的权限定义
typedef enum _cms_authority
{
	CMS_AUTH_BASIC				= 0x0001,		//基本权限

	CMS_AUTH_PARA_SET			= 0x0002,		//参数设置(写)
	CMS_AUTH_READ_PARA			= 0x0004,		//系统参数获取(读)
	CMS_AUTH_CTL_SERIAL_PORT	= 0x0008,		//串口参数设置
	CMS_AUTH_SHUTDOWN_SYS		= 0x0010,		//关机或者重启
	CMS_AUTH_VOICE_TALK			= 0x0020,		//对讲
	CMS_AUTH_REMOTE_VIEW		= 0x0040,		//远程预览

	CMS_AUTH_ALL				= 0xffffffff	//全部权限
}CMS_AUTHORITY;

typedef struct _decoder_info
{
	bool getStreamStatus;		//注意:这个选项为true, 下面的信息才有效
	unsigned int encIp;		//前端设备IP
	unsigned int encPort;		//前端设备的端口号
	int encCh; 					//前端设备的通道号注意从开始计数
	char computerName[COMPUTER_NAME_LEN];		//前端设备的计算机名称
	unsigned char   MAC[6];					//网卡Mac地址

}DECODER_INFO;

// zhouhb_changed
//用于客户端登陆的结构体：CMD_MSG_LOGIN
typedef struct _net_login
{
	//下面是客户端登陆解码器时的信息部分
	char			userName[36];
	char			userPwd[36];

	//CMS权限见: CMS_AUTHORITY的定义
	unsigned int	authority;			//用户权限
	unsigned int	connectType;		//连接类型,ENUM_CONNECT_TYPE
	unsigned int   IP;					//客户端用来连接的IP地址
	char			computerName[36];	//计算机名称
	unsigned char   MAC[6];				//网卡Mac地址
	unsigned int	netprotocolver;		//客户端目前使用的网络协议版本
	DECODER_INFO 	decoderInfo[4]; //解码器各个通道的信息

	unsigned char	resv[16];		//保留字节，对齐用

}NET_LOGIN;

typedef struct __tvwall_switch_t
{
	//以下是前端设备的信息部分
	unsigned int encIp;//前端设备IP
	unsigned int encPort;//前端设备的端口号
	int encCh; //前端设备的通道号注意从1开始计数

	int channelProtocol;// 协议类型	  1tcp,2Udp,3mcast
	int channelStreamtype;//码流类型
	unsigned char  primaryStream; //主码流为

	int encNum;//前端设备的通道总数
	int encKeepAlive; //是否断线重连		启用，不启用


	//以下是解码器的信息部分
	unsigned char  decChannel; //这是解码器的通道号
	int channelKeepAlive;//设定解码器某通道的工作状态：处于引流状态， :处于非引流状态

	//前端设备的这个视频，显示在解码器的那个具体位置。
	int displayMode;		//解码器的分屏模式
	int displayChannel;		//在具体分屏模式中的哪一个通道从0开始计数


	//下面的信息用于登陆前端设备
	char encUserName[MSG_USER_NAME_LEN];	//登陆的用户名和密码
	char encUserPwd[MSG_PASSWD_LEN];
	char			computerName[28];		//前端设备的计算机名称
	unsigned char   MAC[6];					//网卡Mac地址
	unsigned int	netprotocolver;		//客户端目前使用的网络协议版本
	unsigned int	connectType;			//连接类型,ENUM_CONNECT_TYPE

	char reserv[12]; //以备后用

} TVWALL_SWITCH_T;

//用户管理包括查询用户信息, 删除用户信息, 增加用户信息, 更改用户信息。
const unsigned int  	MAX_DEC_USER_NUM				= 16;

typedef struct _dec_ncfg_info_user
{
	unsigned int   bindMac;	//0 不绑定1绑定
	unsigned int   authority;	//用户权限
	unsigned int   group;

	char            name[MSG_USER_NAME_LEN];
	char            password[MSG_PASSWD_LEN];
	unsigned char   MAC[8];
}DEC_NCFG_INFO_USER;


//解码器协议
typedef	struct _message_data
{
	unsigned int	clientID; //客户端的ID号，在用户管理那里用的到
	unsigned int	deviceID;
	char*			pData;	  //整个消息包存储在这里（包括消息头和数据部分）
	int				dataLen;
}MESSAGE_DATA;

typedef struct __MSG_HEAD_t
{
	unsigned	int	clientID; //客户端的ID号，在用户管理那里用的到
	unsigned	int	cmdType;	//命令类型
	unsigned	int	cmdSubtype;	//命令子类型
	unsigned	int	cmdVer;		//命令版本
	unsigned	int		dateSize;	// msgData指向的数据部分的长度

	unsigned	int	ackFlag;	//用于返回的标志
}MSG_HEAD;

typedef struct __net_msg_t
{
	MSG_HEAD			msgHead;		//消息头
	char				*msgData;		//消息数据
}NET_MSG;

typedef enum  CMS_DEC_NET_PROTOCOL_H_
{

	//第一部分是: 与前端设备的通信

	//客户端登录
	CMD_BASE_LOGIN		= 0x0100,
	CMD_REQUEST_LOGIN_DECODER,			//请求登录前端设备
	CMD_REQUEST_LOGOUT_DECODER,			//请求登出前端设备
	CMD_END_NUM_LOGIN,

	// 对前端设备引流进行控制
	CMD_BASE_ENCODER		= 0x0300,
	CMD_STREAM_START,		//请求前端设备码流
	CMD_STREAM_SWITCH,		//请求切换前端设备码流
	CMD_STREAM_STOP,			//请求停止前端设备码流
	CMD_KEYFRAME,				//请求通道关键帧，可以是任意通道的组合，快慢码流的组合
	CMD_END_NUM_ENCODER,

	//第二部分是: 与CMS进行消息交互

	//参数配置（设置参数或获取参数）
	CMD_BASE_NUM_CFG			= 0x010000,
	CMD_CONFIG_GET,		//请求配置
	CMD_CONFIG_SET,		//保存配置

	// iVMS控制解码器的引流机制
	CMD_BASE_NUM_CMS_CONTROL_ENC	= 0x020000,
	CMD_SWITCH_ENC, 		//对解码器的某一个通道切换前端设备
	CMD_STOP_DECODE, 		//停止解码
	CMD_START_DECODE, 	//开始解码

	//客户端信息交互类
	CMD_BASE_NUM_CTRL		= 0x030000,
	CMD_MSG_LOGIN,			//CMS请求登录
	CMD_MSG_LOGOUT,		//CMS请求登出
	CMD_MSG_REBOOT,		//CMS请求重启系统
	CMD_MSG_SHUTDOWN,		//CMS请求关机
	CMD_MSG_EXFACTORY_SETUP,	//请求恢复出厂设置
	CMD_CHANGE_TIME,	//修改系统时间
	CMD_Exception_Set, 		//设备异常方面的设置
	CMD_GET_VERSION_INFO, 	//获取版本信息
	MSG_GET_DEVICE_INFO, 		//获取设备信息
	CMD_NET_DEVICE_SEARCH, 	//局域网内广播搜索设备

	//用户管理部分
	CMD_GET_ALL_USERINFO,		//查询设备的所有用户信息
	CMD_SET_ALL_USERINFO,		//设置用户信息

	//远程软件升级
	CMD_UPDATE_START,			//远程软件升级--->开启
	CMD_UPDATE_DATA			//接收到的远程上传软件升级包
};

//下面的返回码，主要是返回给CMS的。
enum NET_REPLY_CLIENT
{
	ACK_SUCCESS 	= 	0,  //成功
	ACK_ERROR_NAME,		//用户名错误
	ACK_ERROR_PWD,			//密码错误
	ACK_ERROR_RIGHT,		//权限不够

	ACK_LONGIN_SUCC,		//允许登录，附带设备信息
	ACK_LONGIN_FAIL,		//拒绝登录，或者登录失败

	ACK_CFG_DEFAULT,		//回复默认配置
	ACK_CFG_DATA,			//回复配置数据
	//ACK_CFG_DEFAULT,		//回复恢复默认配置信息
	ACK_CFG_FAIL,			//回复配置失败，附带失败码

	//下面是网络方面
	NETERR_PARAMCHECK_OK	,			//信息通过服务器验证
	NETERR_PARAMCHECK_ENAMEPWD,			//用户名或者密码错误
	NETERR_PARAMCHECK_EHOSTDOMAIN,		//dydnds.com的用户名、密码或主机域名错误
	NETERR_PARAMCHECK_ETIMEOUT,			//超时。
	NETERR_PARAMCHECK_ECONNECT,			//网络未连接,未插网线
	NETERR_PARMACHECK_ENETUNREACHD,		//网络不可达
	NETERR_PARMACHECK_EHOSTDOMAIN_EMPTY,	//主机域名为空
	NETERR_PARAMCHECK_EUNKNOWN,			//未知错误
	NETERR_PARAMCHECK_ABUSE,				//dyndns.com上注册的域名被block
	NETERR_PARAMCHECK_NOHOST,			//dyndns.com上找不到相关域名
	NETERR_PARAMCHECK_NOTFQDN,			//dyndns.com上主机域名不符合规则
	NETERR_PARAMCHECK_NUMHOST,			//dyndns.com上太多的主机在update
	NETERR_PARAMCHECK_REGISTER_SUCC,		//向dynamic.visionica.com注册成功
	NETERR_PARAMCHECK_REGISTER_FAIL,		//向dynamic.visionica.com注册失败

	NETERR_PARAMCHECK_EIPCONFLICT,	//静态设置的IP冲突
	NETERR_PARAMCHECK_EIPORSUBMASK,		//ip地址不可用,或者网络掩码错误
	NETERR_PARAMCHECK_ENONICDEVICE,		//没有指定的NIC设备
	NETERR_PARAMCHECK_EUSERNAMEEMPTY,	//用户名为空

	ACK_UPDATE_FILE_ERR,

	ACK_ERROR_OTHER = 0xffff 		//其他错误
};
#endif
