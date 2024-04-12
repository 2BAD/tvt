/***********************************************************************
** 日期         : 2022-04-22
** 版本号		: 1.2.1.035
** 描述			:
** 修改记录		:
***********************************************************************/
#ifndef _DVR_NET_SDK_H_
#define _DVR_NET_SDK_H_

#include "dvrdvstypedef.h"
#include "dvrdvsconfig.h"
#include "dvrdvsdefine.h"
#include "FrameInfo.h"
#include "DisplayDefine.h"

#ifdef WIN32

#define CALL_METHOD __stdcall

#ifdef __cplusplus
#define __EXTERN_C extern "C"
#else
#define __EXTERN_C extern
#endif

#ifdef DVR_NET_SDK_EXPORTS
#define NET_SDK_API __EXTERN_C __declspec(dllexport)
#else
#ifndef __STATIC__
#define NET_SDK_API __EXTERN_C __declspec(dllimport)
#else
#define NET_SDK_API
#endif
#endif

#else

#define CALL_METHOD
#define NET_SDK_API __attribute__ ((visibility("default")))

#endif

#if __cplusplus
extern "C"{
#endif

//#define gettid() syscall(__NR_gettid)

//LastError定义
typedef enum
{
	NET_SDK_SUCCESS,
	NET_SDK_PASSWORD_ERROR,
	NET_SDK_NOENOUGH_AUTH,
	NET_SDK_NOINIT,
	NET_SDK_CHANNEL_ERROR,
	NET_SDK_OVER_MAXLINK,
	NET_SDK_LOGIN_REFUSED,
	NET_SDK_VERSION_NOMATCH,
	NET_SDK_NETWORK_FAIL_CONNECT,
	NET_SDK_NETWORK_NOT_CONNECT,
	NET_SDK_NETWORK_SEND_ERROR,
	NET_SDK_NETWORK_RECV_ERROR,
	NET_SDK_NETWORK_RECV_TIMEOUT,
	NET_SDK_NETWORK_ERRORDATA,
	NET_SDK_ORDER_ERROR,
	NET_SDK_OPER_BY_OTHER,
	NET_SDK_OPER_NOPERMIT,
	NET_SDK_COMMAND_TIMEOUT,
	NET_SDK_ERROR_SERIALPORT,
	NET_SDK_ERROR_ALARMPORT,
	NET_SDK_PARAMETER_ERROR,
	NET_SDK_CHAN_EXCEPTION,
	NET_SDK_NODISK,
	NET_SDK_ERROR_DISKNUM,
	NET_SDK_DISK_FULL,
	NET_SDK_DISK_ERROR,
	NET_SDK_NOSUPPORT,
	NET_SDK_BUSY,
	NET_SDK_MODIFY_FAIL,
	NET_SDK_PASSWORD_FORMAT_ERROR,
	NET_SDK_DISK_FORMATING,
	NET_SDK_DVR_NORESOURCE,
	NET_SDK_DVR_OPRATE_FAILED,
	NET_SDK_OPEN_HOSTSOUND_FAIL,
	NET_SDK_DVR_VOICEOPENED,
	NET_SDK_TIME_INPUTERROR,
	NET_SDK_NOSPECFILE,
	NET_SDK_CREATEFILE_ERROR,
	NET_SDK_FILEOPENFAIL,
	NET_SDK_OPERNOTFINISH,
	NET_SDK_GETPLAYTIMEFAIL,
	NET_SDK_PLAYFAIL,
	NET_SDK_FILEFORMAT_ERROR,
	NET_SDK_DIR_ERROR,
	NET_SDK_ALLOC_RESOURCE_ERROR,
	NET_SDK_AUDIO_MODE_ERROR,
	NET_SDK_NOENOUGH_BUF,
	NET_SDK_CREATESOCKET_ERROR,
	NET_SDK_SETSOCKET_ERROR,
	NET_SDK_MAX_NUM,
	NET_SDK_USERNOTEXIST,
	NET_SDK_WRITEFLASHERROR,
	NET_SDK_UPGRADEFAIL,
	NET_SDK_CARDHAVEINIT,
	NET_SDK_PLAYERFAILED,
	NET_SDK_MAX_USERNUM,
	NET_SDK_GETLOCALIPANDMACFAIL,
	NET_SDK_NOENCODEING,
	NET_SDK_IPMISMATCH,
	NET_SDK_MACMISMATCH,
	NET_SDK_UPGRADELANGMISMATCH,
	NET_SDK_MAX_PLAYERPORT,
	NET_SDK_NOSPACEBACKUP,
	NET_SDK_NODEVICEBACKUP,
	NET_SDK_PICTURE_BITS_ERROR,
	NET_SDK_PICTURE_DIMENSION_ERROR,
	NET_SDK_PICTURE_SIZ_ERROR,
	NET_SDK_LOADPLAYERSDKFAILED,
	NET_SDK_LOADPLAYERSDKPROC_ERROR,
	NET_SDK_LOADDSSDKFAILED,
	NET_SDK_LOADDSSDKPROC_ERROR,
	NET_SDK_DSSDK_ERROR,
	NET_SDK_VOICEMONOPOLIZE,
	NET_SDK_JOINMULTICASTFAILED,
	NET_SDK_CREATEDIR_ERROR,
	NET_SDK_BINDSOCKET_ERROR,
	NET_SDK_SOCKETCLOSE_ERROR,
	NET_SDK_USERID_ISUSING,
	NET_SDK_PROGRAM_EXCEPTION,
	NET_SDK_WRITEFILE_FAILED,
	NET_SDK_FORMAT_READONLY,
	NET_SDK_WITHSAMEUSERNAME,
	NET_SDK_DEVICETYPE_ERROR,
	NET_SDK_LANGUAGE_ERROR,
	NET_SDK_PARAVERSION_ERROR,
	NET_SDK_FILE_SUCCESS,
	NET_SDK_FILE_NOFIND,
	NET_SDK_NOMOREFILE,
	NET_SDK_FILE_EXCEPTION,
	NET_SDK_TRY_LATER,
	NET_SDK_DEVICE_OFFLINE,
	NET_SDK_CREATEJPEGSTREAM_FAIL,
    NET_SDK_USER_ERROR_NO_USER,
    NET_SDK_USER_ERROR_USER_OR_PASSWORD_IS_NULL,
    NET_SDK_USER_ERROR_ALREDAY_LOGIN,
    NET_SDK_USER_ERROR_SYSTEM_BUSY,
    NET_SDK_DEVICE_NOT_SUPPROT,////DEVICE不支持
	NET_SDK_USER_ERROR_SYSTEM_NO_READY,//N9K设备还没有准备好 刚刚登录获取预置点巡航线list还未成功
	NET_SDK_CHANNEL_OFFLINE,//预览N9K设备时通道不在线
	NET_SDK_GETREADYINFO_FAIL,//获取N9K能力集失败
	NET_SDK_NORESOURCE,//SDK资源不足
	NET_SDK_DEVICE_QUERYSYSTEMCAPS_FAIL,
	NET_SDK_INBUFFER_TOSMALL,//输入BUF不足
	NET_SDK_NO_PASSWORD_STRENGTH,//密码强度错误
	NET_SDK_FILE_NOT_MATCH_PRODUCT,//产品型号与升级文件不匹配
}NET_SDK_ERROR;

enum NET_DEVICE_STATUS
{
	NET_DEVICE_STATUS_CONNECTED,
	NET_DEVICE_STATUS_DISCONNECT,
};

enum NET_SDK_STREAM_TYPE
{
	NET_SDK_MAIN_STREAM = 0,
	NET_SDK_SUB_STREAM,
    NET_SDK_THIRD_STREAM,
    NET_SDK_FOURTH_STREAM,
};

enum NET_SDK_PLAYCTRL_TYPE
{
	NET_SDK_PLAYCTRL_PAUSE,
	NET_SDK_PLAYCTRL_FF,
	NET_SDK_PLAYCTRL_REW,
	NET_SDK_PLAYCTRL_RESUME,
	NET_SDK_PLAYCTRL_STOP,
	NET_SDK_PLAYCTRL_FRAME,
	NET_SDK_PLAYCTRL_NORMAL,
	NET_SDK_PLAYCTRL_STARTAUDIO,	//该控制类型及以下两个控制类型只有在SDK内部解码显示时才会起作用
	NET_SDK_PLAYCTRL_STOPAUDIO,
	NET_SDK_PLAYCTRL_AUDIOVOLUME,
	NET_SDK_PLAYCTRL_SETPOS,
};

enum NET_SDK_RPB_SPEED
{
	NET_SDK_RPB_SPEED_1_32X = 1,
	NET_SDK_RPB_SPEED_1_16X,
	NET_SDK_RPB_SPEED_1_8X,		//1/8
	NET_SDK_RPB_SPEED_1_4X,		//1/4
	NET_SDK_RPB_SPEED_1_2X,		//1/2
	NET_SDK_RPB_SPEED_1X,		//1
	NET_SDK_RPB_SPEED_2X,
	NET_SDK_RPB_SPEED_4X,
	NET_SDK_RPB_SPEED_8X,
	NET_SDK_RPB_SPEED_16X,
	NET_SDK_RPB_SPEED_32X,
};

const int MAX_NAMELEN			= 36;
const int MAX_CONTENTLEN		= 512;

#pragma pack(4)
//对应NET_SDK_DEVICEINFO中function
typedef struct _net_sdk_devicefunction_ipc
{
	unsigned int intelist_enable:1;          // 表示该结构体是否包含智能能力集列表(后面31位)，1表示支持, 0表示不支持
	unsigned int intelist_Perimeter:1;       // 是否支持区域入侵, 1表示支持, 0表示不支持
	unsigned int intelist_Tripwire:1;        // 是否支持绊线侦测, 1表示支持, 0表示不支持
	unsigned int intelist_Osc:1;             // 是否支持物品看护, 1表示支持, 0表示不支持
	unsigned int intelist_Avd:1;             // 是否支持异常侦测, 1表示支持, 0表示不支持
	unsigned int intelist_Cpc:1;             // 是否支持人流量统计, 1表示支持, 0表示不支持
	unsigned int intelist_Cdd:1;             // 是否支持人群密度检测, 1表示支持, 0表示不支持
	unsigned int intelist_Ipd:1;             // 是否支持人员入侵侦测, 1表示支持, 0表示不支持
	unsigned int intelist_Vfd:1;             // 是否支持人脸抓拍, 1表示支持, 0表示不支持
	unsigned int intelist_Vfd_Match:1;       // 是否支持人脸比对, 1表示支持, 0表示不支持
	unsigned int intelist_Vehice:1;          // 是否支持车牌检测, 1表示支持, 0表示不支持
	unsigned int intelist_AoiEntry:1;        // 是否支持进入区域, 1表示支持, 0表示不支持
	unsigned int intelist_AoiLeave:1;        // 是否支持离开区域, 1表示支持, 0表示不支持
	unsigned int intelist_PassLineCount:1;   // 是否支持过线统计, 1表示支持, 0表示不支持
	unsigned int intelist_Vfd_Detect:1;      // 是否支持人脸侦测, 1表示支持, 0表示不支持
	unsigned int intelist_Traffic:1;         // 是否支持流量统计, 1表示支持, 0表示不支持
	unsigned int intelist_Thermal:1;			// 是否支持热成像测温, 1表示支持, 0表示不支持
	unsigned int intelist_reserver:15;			// 预留智能功能

	unsigned int	resvFunction[7];			//预留功能描述
}NET_SDK_DEVICE_FUNC_IPC;
//登录结构定义
typedef struct _net_sdk_deviceinfo
{
	unsigned char	localVideoInputNum;		//本地视频输入通道数目
	unsigned char	audioInputNum;			//音频输入通道数目
	unsigned char	sensorInputNum;			//传感器输入通道数目
	unsigned char	sensorOutputNum;		//继电器输出数目
	unsigned int   displayResolutionMask;  //监视器可选择的分辨率

	unsigned char	videoOuputNum;			//视频输出数目（及支持回放最大通道数）
	unsigned char	netVideoOutputNum;		//网络回放最大通道数目
	unsigned char	netVideoInputNum;		//数字信号接入通道数目
	unsigned char	IVSNum;					//智能分析通道数目

	unsigned char	presetNumOneCH;			//每个通道预置点数目
	unsigned char	cruiseNumOneCH;			//每个通道巡航线数目
	unsigned char	presetNumOneCruise;		//每个巡航线的预置点数目
	unsigned char	trackNumOneCH;			//每个通道轨迹数目

	unsigned char	userNum;				//用户数目
	unsigned char	netClientNum;			//最多客户端数目
	unsigned char	netFirstStreamNum;		//主码流传输的通道最大数目，即同时可以有几个客户端查看主码流
	unsigned char	deviceType;				// NET_SDK_DEVICE_TYPE

	unsigned char	doblueStream;			//是否有提供双码流
	unsigned char	audioStream;			//是否有提供音频流
	unsigned char	talkAudio;				//是否有对讲功能: 1表示有对讲功能;0表示没有
	unsigned char	bPasswordCheck;			//操作是否要输入密码

	unsigned char	defBrightness;			//缺省亮度
	unsigned char	defContrast;			//缺省对比度
	unsigned char	defSaturation;			//缺省饱和度
	unsigned char	defHue;					//缺省色调

	unsigned short	videoInputNum;			//视频输入通道数目（本地加网络）
	unsigned short  deviceID;				//设备ID号
	unsigned int   videoFormat;            //系统当前制式

	//假如是FUNC_REMOTE_UPGRADE对应的功能，那么第FUNC_REMOTE_UPGRADE个比特为1，否则为零。
	unsigned int	function[8];			//功能描述

	unsigned int	deviceIP;				//设备网络地址
	unsigned char	deviceMAC[6];			//设备物理地址
	unsigned short	devicePort;				//设备端口

	unsigned int	buildDate;				//创建日期:year<<16 + month<<8 + mday
	unsigned int	buildTime;				//创建时间:hour<<16 + min<<8 + sec

	char			deviceName[36];			//设备名称

	char	firmwareVersion[36];			//固件版本
	char	kernelVersion[64];				//内核版本
	char	hardwareVersion[36];			//硬件版本
	char	MCUVersion[36];					//单片机版本
    char	firmwareVersionEx[64];			//固件版本扩展，主要针对新产品
    unsigned int	softwareVer;//软件协议版本，目前用于IPC的版本兼容
    char	szSN[32];			//sn
    char	deviceProduct[28];			//设备型号
}NET_SDK_DEVICEINFO, *LPNET_SDK_DEVICEINFO;

typedef struct _net_sdk_dev_support_
{
	unsigned int	supportThermometry:1;				//支持口罩跟体温
	unsigned int	supportVfd:1;				//人脸检测
	unsigned int	supportVfdMatch:1;				//人脸比对
    unsigned int	supportThermal:1;				//热成像
    unsigned int	supportPassLine:1;				//过线统计
    unsigned int	supportresv:27;				//待填入
	unsigned int	resv[15];				//暂时未用上

}NET_SDK_DEV_SUPPORT;

//数据帧头定义
typedef struct _net_sdk_frame_info
{
	unsigned int		deviceID;
	unsigned int       channel;
	unsigned int		frameType;	//参考DD_FRAME_TYPE
	unsigned int		length;
	unsigned int		keyFrame;	//0：非关键帧 1：关键帧
	unsigned int       width;
	unsigned int       height;
	unsigned int		frameIndex;
	unsigned int		frameAttrib;//参考DD_FRAME_ATTRIB
	unsigned int		streamID;
	LONGLONG			time;	   //从1970年1月1日0点0分0秒开始的绝对时间，单位微秒
	LONGLONG			relativeTime;//相对时间，单位微秒
}NET_SDK_FRAME_INFO;

//录像时间信息定义
typedef struct _net_sdk_rec_time
{
	DWORD			dwChannel;	//通道号
	DD_TIME			startTime;	//该段录像开始时间
	DD_TIME			stopTime;	//该段录像结束时间
}NET_SDK_REC_TIME;

typedef struct _net_sdk_rec_file
{
	DWORD			dwChannel;
	DWORD			bFileLocked;
	DD_TIME			startTime;
	DD_TIME			stopTime;
	DWORD			dwRecType;
	DWORD			dwPartition;
	DWORD			dwFileIndex;
}NET_SDK_REC_FILE;

typedef struct _net_sdk_rec_event
{
	DWORD			dwChannel;
	DD_TIME			startTime;
	DD_TIME			stopTime;
	DWORD			dwRecType;	//DD_RECORD_TYPE
}NET_SDK_REC_EVENT;

//日志信息定义
typedef struct _net_sdk_log
{
	DD_TIME			strLogTime;
	DWORD			dwMajorType;
	DWORD			dwMinorType;
	char			sNetUser[MAX_NAMELEN];
	DWORD			dwRemoteHostAddr;
	char			sContent[MAX_CONTENTLEN];
}NET_SDK_LOG,*LPNET_SDK_LOG;

typedef struct _net_sdk_event
{
	unsigned short chnn;			//事件对应的通道
	unsigned short type;			//事件类型：DD_EVENT_TYPE
	DD_TIME        startTime;		//事件产生的开始时间
	DD_TIME        endTime;			//事件的结束时间
}NET_SDK_EVENT,*LPNET_SDK_EVENT;

typedef struct _net_sdk_clientinfo
{
	LONG    lChannel;
	LONG    streamType;
	HWND    hPlayWnd;
    int     bNoDecode; //0:解码， 1：不解码 仅针对win平台，默认0

}NET_SDK_CLIENTINFO, *LPNET_SDK_CLIENTINFO;

//设备上传信息类型
enum NET_SDK_DEVICE_MSG_TYPE
{
	NET_SDK_ALARM,		//设备报警消息
	NET_SDK_RECORD,		//设备录像信息
	NET_SDK_IVM_RULE,	//智能行为分析信息(暂时保留)
	NET_SDK_TRADEINFO,	//ATM交易信息(暂时保留)
	NET_SDK_IPCCFG,		//混合型DVR的IPC信息变更(暂时保留)
};

//以前NET_SDK_ALARM_TYPE和NET_SDK_N9000_ALARM_TYPE报警类型都是混着用的,现在统一用NET_SDK_N9000_ALARM_TYPE报警类型(IPC和NVR均用NET_SDK_N9000_ALARM_TYPE这个)
//原NET_SDK_ALARM_TYPE报警类型作废
//设备上传信息为报警类型时的具体报警类型
//enum NET_SDK_ALARM_TYPE
//{
//	NET_SDK_ALARM_TYPE_MOTION,		//移动侦测
//	NET_SDK_ALARM_TYPE_SENSOR,		//信号量报警
//	NET_SDK_ALARM_TYPE_VLOSS,		//信号丢失
//	NET_SDK_ALARM_TYPE_SHELTER,		//遮挡报警
//	NET_SDK_ALARM_TYPE_DISK_FULL,	//硬盘满
//	NET_SDK_ALARM_TYPE_DISK_UNFORMATTED,//硬盘未格式化
//	NET_SDK_ALARM_TYPE_DISK_WRITE_FAIL,	//读写硬盘出错
//	NET_SDK_ALARM_TYPE_EXCEPTION,
//	NET_SDK_ALARM_TYPE_OSC,           ////物品看护侦测报警
//	NET_SDK_ALARM_TYPE_AVD,           ////视频异常侦测报警
//	NET_SDK_ALARM_TYPE_AVD_SCENE,
//	NET_SDK_ALARM_TYPE_AVD_CLARITY,
//	NET_SDK_ALARM_TYPE_AVD_COLOR,
//	NET_SDK_ALARM_TYPE_PEA_TRIPWIRE,  ////越界侦测报警
//	NET_SDK_ALARM_TYPE_PEA_PERIMETER, ////区域入侵侦测报警
//	NET_SDK_ALARM_TYPE_FRONT_OFFLINE,///前端通道离线
//};


//设备上传信息为智能报警的事件类型
enum NET_SDK_IVM_RULE_TYPE
{
    NET_SDK_IVM_RULE_TYPE_VFD, //人脸识别报警  NET_SDK_IVM_STATUS_INFO
    NET_SDK_IVM_RULE_TYPE_AVD_SCENE, //视频异常诊断场景变化  NET_SDK_IVM_STATUS_INFO
    NET_SDK_IVM_RULE_TYPE_AVD_CLARITY, //视频异常诊断视频模糊  NET_SDK_IVM_STATUS_INFO
    NET_SDK_IVM_RULE_TYPE_AVD_COLOR, //视频异常诊断视频偏色  NET_SDK_IVM_STATUS_INFO
};


/************************************************************************/
    /*  定义报警输入和输出的资源    在很多地方使用这个枚举值的时候定义的变量都是BYTE的所以这里
    要小心定义*/
    /************************************************************************/

enum NET_SDK_N9000_ALARM_TYPE
{
    NET_SDK_N9000_ALARM_TYPE_RANGE_BEGIN,
    NET_SDK_N9000_ALARM_TYPE_MOTION=0x01,/////移动侦测报警输入
    NET_SDK_N9000_ALARM_TYPE_SENSOR,/////传感器报警输入
    NET_SDK_N9000_ALARM_TYPE_VLOSS,////视频丢失报警输入
    NET_SDK_N9000_ALARM_TYPE_FRONT_OFFLINE, //////前端设备掉线报警
    NET_SDK_N9000_ALARM_TYPE_OSC,           ////物品看护侦测报警
    NET_SDK_N9000_ALARM_TYPE_AVD,           ////视频异常侦测报警
    NET_SDK_N9000_ALARM_TYPE_AVD_SCENE,//only IPC
    NET_SDK_N9000_ALARM_TYPE_AVD_CLARITY,//only IPC
    NET_SDK_N9000_ALARM_TYPE_AVD_COLOR,//only IPC
    NET_SDK_N9000_ALARM_TYPE_PEA_TRIPWIRE,  ////越界侦测报警
    NET_SDK_N9000_ALARM_TYPE_PEA_PERIMETER, ////区域入侵侦测报警
    NET_SDK_N9000_ALARM_TYPE_VFD,           ////人脸侦测（目前仅IPC）
    NET_SDK_N9000_ALARM_TYPE_CDD,           ////Crowdy density
    NET_SDK_N9000_ALARM_TYPE_IPD,           ////people intrusion
    NET_SDK_N9000_ALARM_TYPE_CPC,           ////people counting
    NET_SDK_N9000_ALARM_TYPE_FACE_MATCH,    ////人脸比对报警 for nvr 9000
    NET_SDK_N9000_ALARM_TYPE_FACE_MATCH_FOR_IPC,    ////人脸比对报警 for ipc
    NET_SDK_N9000_ALARM_TYPE_PEA_FOR_IPC,           ////越界侦测与区域入侵侦测
	NET_SDK_N9000_ALARM_TYPE_TRAJECT,  ////目标跟踪轨迹(Event事件)
	NET_SDK_N9000_ALARM_TYPE_VEHICE,	///车牌for ipc(Event事件)
	NET_SDK_N9000_ALARM_TYPE_AOIENTRY,//进入区域for ipc
	NET_SDK_N9000_ALARM_TYPE_AOILEAVE,//离开区域for ipc
	NET_SDK_N9000_ALARM_TYPE_PASSLINE,//passline counting for ipc(Event事件)
	NET_SDK_N9000_ALARM_TYPE_TRAFFIC,//traffic
	NET_SDK_N9000_ALARM_TYPE_DOOR_BELL,//按门铃报警 only IPC

	NET_SDK_N9000_ALARM_TYPE_GPS_SPEED_OVER=0x21,    //和车载有关的报警，超速
	NET_SDK_N9000_ALARM_TYPE_GPS_CROSS_BOADER,       //越界
	NET_SDK_N9000_ALARM_TYPE_GPS_TEMPERATURE_OVER,   //温度报警
	NET_SDK_N9000_ALARM_TYPE_GPS_GSENSOR_X,          //GSENSOR报警
	NET_SDK_N9000_ALARM_TYPE_GPS_GSENSOR_Y,
	NET_SDK_N9000_ALARM_TYPE_GPS_GSENSOR_Z,

    NET_SDK_N9000_ALARM_TYPE_EXCEPTION = 0x41,
    NET_SDK_N9000_ALARM_TYPE_IP_CONFLICT,   /////IP地址冲突
    NET_SDK_N9000_ALARM_TYPE_DISK_IO_ERROR, /////磁盘IO错误
    NET_SDK_N9000_ALARM_TYPE_DISK_FULL,	   /////磁盘满
    NET_SDK_N9000_ALARM_TYPE_RAID_SUBHEALTH, //阵列亚健康
    NET_SDK_N9000_ALARM_TYPE_RAID_UNAVAILABLE, //阵列不可用
    NET_SDK_N9000_ALARM_TYPE_ILLEIGAL_ACCESS,  /////非法访问
    NET_SDK_N9000_ALARM_TYPE_NET_DISCONNECT,  /////网络断开
    NET_SDK_N9000_ALARM_TYPE_NO_DISK,		////盘组下没有磁盘
    NET_SDK_N9000_ALARM_TYPE_SIGNAL_SHELTER, //信号遮挡
    NET_SDK_N9000_ALARM_TYPE_HDD_PULL_OUT, //前面板硬盘拔出

    NET_SDK_N9000_ALARM_TYPE_ALARM_OUT = 0x51,  /////报警输出的类型，报警输出也有状态需要管理

    NET_SDK_N9000_ALARM_TYPE_RANGE_END = 0xFF,////不能超过这个值  否则会出错
};

//智能事件定义
//智能事件以下枚举值和报警的枚举数值和一样 新版本智能事件都改为用NET_SDK_SMART_EVENT_TYPE该类型(和报警区分开来,否则会有歧义)
//由于枚举值和之前一样,旧版本demo里直接用之前的报警的值仍是可以用的
enum NET_SDK_SMART_EVENT_TYPE
{
	NET_SDK_SMART_EVENT_TYPE_RANGE_BEGIN,
	NET_SDK_SMART_EVENT_TYPE_OSC=0x05,           ////物品看护侦测事件
	NET_SDK_SMART_EVENT_TYPE_AVD=0x06,           ////视频异常侦测事件
	NET_SDK_SMART_EVENT_TYPE_VFD=0x0C,           ////人脸侦测（目前仅IPC）
	NET_SDK_SMART_EVENT_TYPE_CDD,           ////Crowdy density
	NET_SDK_SMART_EVENT_TYPE_IPD,           ////people intrusion
	NET_SDK_SMART_EVENT_TYPE_CPC,           ////people counting
	NET_SDK_SMART_EVENT_TYPE_FACE_MATCH,    ////人脸比对 for nvr 9000
	NET_SDK_SMART_EVENT_TYPE_FACE_MATCH_FOR_IPC,    ////人脸比对 for ipc
	NET_SDK_SMART_EVENT_TYPE_PEA_FOR_IPC=0x12,           ////越界侦测与区域入侵侦测
	NET_SDK_SMART_EVENT_TYPE_TRAJECT,  ////目标跟踪轨迹
	NET_SDK_SMART_EVENT_TYPE_VEHICLE,	///车牌for ipc
	NET_SDK_SMART_EVENT_TYPE_AOIENTRY,//进入区域for ipc
	NET_SDK_SMART_EVENT_TYPE_AOILEAVE,//离开区域for ipc
	NET_SDK_SMART_EVENT_TYPE_PASSLINE=0x17,//passline counting for ipc
	NET_SDK_SMART_EVENT_TYPE_TRAFFIC,//traffic
	NET_SDK_SMART_EVENT_TYPE_PEA_TARGET,//越界侦测与区域入侵侦测,带有目标抓图相关信息
};

//设备上传信息为报警类型时的上传信息结构
typedef struct _net_sdk_alarminfo
{
	DWORD		dwAlarmType;
	DWORD		dwSensorIn;		//传感器报警输入端口号
    DWORD		dwChannel;		//在报警与通道相关时，表示报警的通道号;（当报警类型为NET_SDK_N9000_ALARM_TYPE_SENSOR时，可作为pop video，>=0生效）
	DWORD		dwDisk;			//在磁盘报警时，表示产生报警的磁盘号
}NET_SDK_ALARMINFO;
typedef struct _net_sdk_alarminfo_ex
{
	DWORD		dwAlarmType;
	DWORD		dwSensorIn;		//传感器报警输入端口号
	DWORD		dwChannel;		//在报警与通道相关时，表示报警的通道号;（当报警类型为NET_SDK_N9000_ALARM_TYPE_SENSOR时，可作为pop video，>=0生效）
	DWORD		dwDisk;			//在磁盘报警时，表示产生报警的磁盘号
	char		sensorName[36]; //在传感器报警时，传感器的名称
	char        alarmTime[20];  //报警触发时间
	char		resv[128];      //预留
}NET_SDK_ALARMINFO_EX;
typedef struct _net_sdk_record_status
{
	DWORD		dwRecordType;		//DD_RECORD_TYPE
	DWORD		dwChannel;
}NET_SDK_RECORD_STATUS;
typedef struct _net_sdk_record_status_ex
{
	DWORD		dwRecordType;		//DD_RECORD_TYPE
	DWORD		dwChannel;
	DWORD		dwRecordStatus;
}NET_SDK_RECORD_STATUS_EX;
typedef struct _net_sdk_IVM_rule_status
{
    DWORD		dwIVMType;		//NET_SDK_IVM_RULE_TYPE
    DWORD		dwIVMSize;      //NET_SDK_IVM_RULE_TYPE中事件对应的结构体大小
}
NET_SDK_IVM_RULE_STATUS;

//人脸检测告警上报
typedef struct _net_sdk_IVM_status_info
{
    DWORD		dwAlarmType;    //NET_SDK_IVM_RULE_TYPE
    DWORD		dwChannel;		//告警通道号

}NET_SDK_IVM_STATUS_INFO;


typedef enum _net_sdk_disk_status
{
	NET_SDK_DISK_NORMAL,				//正常
	NET_SDK_DISK_NO_FORMAT,				//未格式化
    NET_SDK_DISK_FORMATTING,				//正在格式化
    NET_SDK_DISK_EXCEPTION,				//  exception
}NET_SDK_DISK_STATUS;

typedef enum _net_sdkdisk_property
{
	NET_SDK_DISK_READ_WRITE = 0,			//可正常读写
	NET_SDK_DISK_ONLY_READ,					//只能读，不能写
	NET_SDK_DISK_REDUNDANCY					//冗余
}NET_SDK_DISK_PROPERTY;

typedef enum _net_sdk_connect_type
{
	NET_SDK_CONNECT_TCP		= 0,			//TCP方式登陆
	NET_SDK_CONNECT_NAT		= 1,			//NAT方式登陆
    NET_SDK_CONNECT_NAT20	= 2,			//NAT2方式登陆

	NET_SDK_CONNECT_END
}NET_SDK_CONNECT_TYPE;

typedef enum _net_sdk_camera_type
{
	NET_SDK_NOT_SUPPORT_PTZ		= 0,		//不支持云台的枪机
	NET_SDK_DOME_SUPPORT_PTZ	= 1,		//支持云台的枪机
	NET_SDK_SUPPORT_PTZ			= 2,		//支持云台的球机
	NET_SDK_PTZ_END
}NET_SDK_CAMERA_TYPE;

typedef struct _net_sdk_disk_info
{
	LONG		diskIndex;			//磁盘编号
	short		diskStatus;			//磁盘状态，参考NET_SDK_DISK_STATUS
	short		diskProperty;		//磁盘状态，参考NET_SDK_DISK_PROPERTY
	DWORD		diskTotalSpace;		//磁盘总空间，单位MB
	DWORD		diskFreeSpace;		//磁盘剩余空间，单位MB
}NET_SDK_DISK_INFO;

typedef struct
{
	WORD     wPicSize;
	WORD     wPicQuality;
}NET_SDK_JPEGPARA,*LPNET_SDK_JPEGPARA;

typedef enum _net_sdk_exception_type
{
	NETWORK_DISCONNECT = 0,//设备下线
	NETWORK_RECONNECT,//设备上线
	NETWORK_CH_DISCONNECT,	//通道掉线
	NETWORK_CH_RECONNECT,	//通道上线
}NET_SDK_EXCEPTION_TYPE;

enum NET_SDK_DEVICE_TYPE
{
	NET_SDK_DVR,
	NET_SDK_DVS,
	NET_SDK_IPCAMERA,
	NET_SDK_NVR,
	NET_SDK_SUPERDVR,
	NET_SDK_DECODER,
    NET_SDK_N_DVR,//N9000的DVR
};

typedef enum _net_sdk_device_firmware_type
{
	NET_SDK_DEVICE_FIRMWARE_V3,
	NET_SDK_DEVICE_FIRMWARE_IPC,
	NET_SDK_DEVICE_FIRMWARE_NVMS_V1,
	NET_SDK_DEVICE_FIRMWARE_OTHER,
}NET_SDK_DEVICE_FIRMWARE_TYPE;

typedef struct _net_sdk_device_discovery_info
{
	unsigned int		deviceType;		//NET_SDK_DEVICE_TYPE
	char				productType[32];
	char				strIP[16];
	char				strNetMask[16];
	char				strGateWay[16];
	unsigned char		byMac[8];
	unsigned short		netPort;
	unsigned short		httpPort;
	unsigned int		softVer;
	unsigned int		softBuildDate;
	unsigned char		ucIPMode;			//0 静态IP 1 dhcp
	char				dwSecondIP[16];
	char				dwSecondMask[16];
    char                deviceActivated;    //设备激活状态 1:未激活 0:已激活
	char                pwdLevel;
    char				nocName[16];
}NET_SDK_DEVICE_DISCOVERY_INFO;

typedef struct _net_sdk_device_ip_info_
{
	char szMac[36];					//设备当前mac地址
	char szIpAddr[64];				//要修改成的ip
	char szMark[36];
	char szGateway[36];
	char szPassword[64];			//admin用户的密码
	char szDdns1[36];
	char szDdns2[36];
	char ucIPMode;					//0为静态IP, 1为DHCP
}NET_SDK_DEVICE_IP_INFO;

typedef struct _net_sdk_ipc_device_info_
{
	unsigned int	deviceID;				//设备ID(暂时未用上)
	unsigned short	channel;				//该网络设备在本地分配的通道(从0开始)
	unsigned char	guid[48];               //通道的GUID
	unsigned short	status;					//连接状态（0代表离线，1表示在线）
	char			szEtherName[16];		//如果为空，默认为eth0
	char			szServer[64];			//网络设备IP地址
	unsigned short	nPort;					//网络设备端口号
	unsigned short	nHttpPort;				//HTTP端口
	unsigned short	nCtrlPort;				//控制端口，一般与nPort相同
	char			szID[64];				//网络设备标识(或是MAC地址)
	char			username[36];			//用户名

	unsigned int	manufacturerId;			//设备厂商ID(暂时未用上)
	char			manufacturerName[36];	//设备厂商名(暂时未用上)
	char			productModel[36];		//产品型号(暂时未用上)
	unsigned char	bUseDefaultCfg;			//暂时未用上
	unsigned char	bPOEDevice;				//暂时未用上
	unsigned char	resv[2];				//暂时未用上
	char			szChlname[36];			//通道名称
}NET_SDK_IPC_DEVICE_INFO;

//抓图类型
enum IMAGE_EVENT_TYPE
{
    IMAGE_TYPE_ALARM,
    IMAGE_TYPE_MANUAL,
};
//返回排列顺序
enum IMAGE_SORT_TYPE
{
    IMAGE_SORT_ASC,
    IMAGE_SORT_DESC,
};


typedef struct _net_sdk_image_
{
    DWORD			dwChannel; //抓图通道
    DWORD			dwImageType; //抓图类型 IMAGE_EVENT_TYPE
    DD_TIME_EX			captureTime;//时间
    DWORD			totalNum;//图片总数
    unsigned char	resv[8];
}NET_SDK_IMAGE;

typedef struct _net_sdk_image_sreach
{
    DWORD			dwChannel;//抓图通道
    DD_TIME_EX			StartTime; //时间
    DD_TIME_EX			StopTime; //时间
    DWORD			pageIndex;//第几页
    DWORD			pageSize;//每页数
    unsigned int sort; //返回排列顺序 //IMAGE_SORT_TYPE
    unsigned char	resv[8];
}NET_SDK_IMAGE_SREACH;


//图片类型
enum IMAGE_MODE
{
    IMAGE_MODE_JPG,
    IMAGE_MODE_PNG,
    IMAGE_MODE_BMP,
};
typedef struct _net_sdk_image_info
{
    unsigned int	imageSize;
    unsigned int		imageMode; //IMAGE_MODE 图片格式
    unsigned char	resv[8];
}NET_SDK_IMAGE_INFO;

typedef enum __Channel_type__
{
    E_NULL_CHL_TYPE,
    E_DIGITAL_CHL_TYPE,     //数字通道
    E_ANALOG_CHL_TYPE,      //模拟通道
    E_ALARMOUT_CHL_TYPE,	  //报警输出通道
    E_SENSOR_CHL_TYPE,	  //传感器通道
}CHANNEL_TYPE;

typedef struct _net_sdk_channel_ptz
{
    unsigned int	dwChannel;
    unsigned int      eChanneltype;//CHANNEL_TYPE
    unsigned char	resv[8];
}NET_SDK_CHANNEL_PTZ;

typedef enum __IVM_rule_config_type__
{
    IVM_RULE_VFD_CONFIG, //人脸识别配置
    IVM_RULE_VFD_TRIGGER_CONFIG, //人脸识别联动配置
    IVM_RULE_VFD_SCHEDULE_CONFIG, //人脸识别排程
    IVM_RULE_AVD_CONFIG, //异常视频配置

}IVM_RULE_CONFIG_TYPE;

typedef struct _rectangle_
{
    unsigned int X1;
    unsigned int Y1;
    unsigned int X2;
    unsigned int Y2;
}RECTANGLE;
//IVM_RULE_VFD_CONFIG
typedef struct _net_sdk_Vfd_Config
{
    unsigned int      bSwitch; //使能，0 or 1
    unsigned int      alarmHoldTime;//报警持续时间
    unsigned int      saveFacePicture;//保存人脸检测脸图片
    unsigned int      saveSourcePicture;//保存人脸检测源图片
    unsigned int      rectangleNum;
    RECTANGLE	rectangle;
    unsigned char	resv[40];
}NET_SDK_VFD_CONFIG;

//IVM_RULE_VFD_TRIGGER_CONFIG
typedef struct _net_sdk_Vfd_trigger_Config
{
    unsigned short    snapCHNum ; //支持最大抓图通道数
    unsigned char     snapChannelId;//抓图通道
    unsigned char     snapBswitch ;//抓图使能
    unsigned short    recordCHNum ; //支持最大录像通道数
    unsigned char     recordChannelId;//录像通道
    unsigned char     recordBswitch ;//录像使能
    unsigned short    alarmOutCHNum ; //支持最大报警输出数
    unsigned char     alarmOutChannelId;//报警输出通道
    unsigned char     alarmOutBswitch ;//报警输出使能
    unsigned char     Resv[256];//保留，将来用于扩展多通道

}NET_SDK_VFD_TRIGGER_CONFIG;

typedef struct
{
    unsigned char    byStartHour;
    unsigned char    byStartMin;
    unsigned char    byStopHour;
    unsigned char    byStopMin;
}NET_DVR_SCHEDTIME, *LPNET_DVR_SCHEDTIME;

typedef struct
{
    unsigned char    mounth;
    unsigned char    day;
    unsigned char    Resv[2];
    NET_DVR_SCHEDTIME sScheduleTime;

}NET_DVR_SCHEDDATE, *LPNET_DVR_SCHEDDATE; //按特定日期订的排程

typedef struct
{
    unsigned int    wDay; //在星期中的天数，周天为0，，，周六为6
    NET_DVR_SCHEDTIME sScheduleTime;

}NET_DVR_SCHEDWEEK, *LPNET_DVR_SCHEDWEEK;//根据星期数订的排程

//IVM_RULE_VFD_SCHEDULE_CONFIG
typedef struct
{
    unsigned int wDayCount; //sScheduleWeek有效个数
    unsigned int dayCount;  //sScheduleDate 有效个数
    NET_DVR_SCHEDWEEK sScheduleWeek[70]; //最多可以订70个
    NET_DVR_SCHEDDATE sScheduleDate[31]; //最多可以订31个  值大小来自ipc的协议

}NET_SDK_VFD_SCHEDULE_CONFIG;

//与备份相关
typedef enum _net_sdk_backup_data_type
{
    NET_DVR_BACKUP_DATA_TYPE_DVR,
    NET_DVR_BACKUP_DATA_TYPE_AVI,
    NET_DVR_BACKUP_DATA_TYPE_NULL,
}NET_DVR_BACKUP_DATA_TYPE;

typedef struct _download_sdk_frame_info
{
    unsigned int		nLength;	//帧数据长度
    unsigned short		frameType;	//参考DD_FRAME_TYPE
    unsigned short		keyFrame;	//0：非关键帧 1：关键帧
    unsigned short		nWidth;		//画面宽, 单位像素, 如果是音频数据则为0
    unsigned short		nHeight;	//画面高, 如果是音频数据则为0
    LONGLONG			nStamp;		//帧时间, 单位毫秒, 从1970年1月1日0点0分0秒开始的绝对时间
}NET_DVR_DOWNlOAD_FRAME_INFO;

typedef enum _net_sdk_backup_status
{
    NET_DVR_BACKUP_STOP,
    NET_DVR_BACKUP_END,

}NET_DVR_BACKUP_STATUS;

typedef struct
{
    char                            serverAddress[256];             // 订阅标识 后期的续订和退订使用
    long long                          currentTime;                    // 当前时间
    long long                          terminationTime;                // 终止时间
    char                            resv[64];                       // 后期扩展用
}NET_DVR_SUBSCRIBE_REPLY;


// 智能事件类型
typedef enum
{
    NET_DVR_SMART_AVD = 0,            // 视频异常诊断功能检测
    NET_DVR_SMART_VFD,            // 人脸检测
    NET_DVR_SMART_VFD_MATCH,    //人脸比对
    NET_DVR_SMART_PEA,                  // 区域入侵
    NET_DVR_SMART_OSC,                  // 物品遗留及丢失
    NET_DVR_SMART_CPC,                  // 人流量统计
    NET_DVR_SMART_CDD,                  // 人群密度检测
    NET_DVR_SMART_IPD,                  // 人员入侵侦测
	NET_IPC_SMART_VIHICLE,				//车牌识别
	NET_IPC_SMART_AOIENTRY,             //进入区域
	NET_IPC_SMART_AOILEAVE,             //离开区域
	NET_DVR_SMART_VFD_MATCH_FAILED,    //人脸比对失败。针对陌生人
	NET_IPC_SMART_PASSLINE,             //过线统计
	NET_IPC_SMART_TRAFFIC,				//流量统计

}NET_DVR_SMART_TYPE;

typedef struct
{
    int X;
    int Y;
}NET_DVR_IVE_POINT_T;
typedef struct
{
    LONGLONG      time;            //检测源数据当前时间 /* 微秒级 */
    LONGLONG      relativeTime;    //检测源数据相对时间 /* 微秒级 */
    unsigned int     detectDataLen;   //检测源数据长度
    unsigned int     softwareVersion; //软件版本号, 0xABCDEFGH,AB：厂家 CD：主版本 EFGH：子版本 厂商 1:欧姆龙 版本:V5.00
    unsigned int     softwareBuildDate;//软件生成日期,0xYYYYMMDD
    unsigned int     faceCnt;         //人脸的个数，最大40个
    unsigned int     faceDataLen[40]; //每个人脸的长度
}NET_DVR_IVE_VFD_RESULT_HEAD_T;

typedef struct
{
    unsigned int     type;  ///<: 0, JPG; 1, YUV
    unsigned int     status; ///<:0, INVALID; 1, VALID; 2, SAVED
    unsigned int     width;
    unsigned int     height;
    unsigned int     dataLen;
}NET_DVR_IVE_VFD_RESULT_DATA_INFO_T;

typedef struct
{
    int                      faceId;         /* face ID Number */
    unsigned int                     ptWidth;        /*坐标比例宽*/
    unsigned int                     ptHeight;       /*坐标比例高*/
    NET_DVR_IVE_POINT_T                 ptLeftTop;      /* Left-Top     Face Coordinates    */
    NET_DVR_IVE_POINT_T                 ptRightTop;     /* Right-Top    Face Coordinates    */
    NET_DVR_IVE_POINT_T                 ptLeftBottom;   /* Left-Bottom  Face Coordinates    */
    NET_DVR_IVE_POINT_T                 ptRightBottom;  /* Right-Bottom Face Coordinates    */
    int                      nPose;          /* Face Pose                        */
    int                      nConfidence;    /* Confidence Degree                */
    int                      age;
    int                      sex;
    int                      dtFrames;
    int                         featureSize;
    NET_DVR_IVE_POINT_T                 stPosFaceImg;  //人脸左上角坐标(在检测源图片的位置)

	//begin 新增算法部分给的参数
	float                       feature_score;      // 特征值判断人脸可信度0~100

	/*以下变量为IFaceDetectorEx接口支持，为负数时为无效状态*/
	short                       eye_dist;           // 双眼距离
	short                       blur;               // 模糊度

	char                        pose_est_score;     // 人脸姿态评估分数0~100
	char                        detect_score;       // 检测算法判断人脸可信度0~100
	char                        illumination;       // 抠图区域平均亮度
	char                        faceliveness;       // 活体0~100

	char                        completeness;       // 遮挡0~100
	char                        glasses;            // 是否戴眼镜
	char                        wearmask;           // 是否戴口罩:0是未检测，1是未戴口罩 2是戴口罩
	char                        reserved1[1];

	float                       comprehensive_score;   // 综合评分 [90,100)是优秀， [80,90)是良好，[70,80)是一般，[60,70)是合格，[50,60)可选，[0,50)差。
	//end 新增算法部分给的参数
	int                      temperature;        //体温

	int                      foreheadX;          //额头坐标（临时添加）
	int                      foreheadY;          //额头坐标（临时添加）

	NET_DVR_IVE_POINT_T      stHotLeftTop;       //热成像人脸左上坐标
	NET_DVR_IVE_POINT_T      stHotRightBottom;   //热成像人脸右下坐标
	char                     cTemperatureMode;   //热成像测温模式，0表示正常测温模式，1表示温度矫正模式
	char                     tempUnitsType;      //温度单位，0摄氏度，1华氏度
	char                     cTemperatureStatus; //体温状态，0体温正常，1低温异常，2高温异常

	char                      reserved[5];
    NET_DVR_IVE_VFD_RESULT_DATA_INFO_T  stFaceImgData;
}NET_DVR_IVE_VFD_RESULT_FACE_DATA_INFO_T;


//IVM_RULE_AVD_CONFIG
typedef struct _net_sdk_AVD_Config
{
    unsigned int      alarmHoldTime; //报警持续时间
    unsigned int      sceneChangeSwitch;//场景变更使能，0 or 1
    unsigned int      clarityAbnormalSwitch;//视频模糊使能，0 or 1
    unsigned int      colorAbnormalSwitch;//视频偏色使能，0 or 1
    unsigned int      sensitivity;
    unsigned int      maxSensitivity;
    unsigned int      minSensitivity;
    char              resv[40];

}NET_SDK_AVD_CONFIG;

typedef struct
{
    unsigned int      eventId;               // 事件ID
    unsigned int      status;                // 报警状态,0:none 1:start 2:end 3:procedure
    unsigned int      type;                  // 报警类型,0:none 1:Scene 2:Clarity 3:Color
}NET_SDK_IVE_AVD_INFO_T;

typedef struct
{
    unsigned int          count;             // 个数
    NET_SDK_IVE_AVD_INFO_T   avdInfo[32];       // 异常侦测信息
}NET_SDK_IVE_AVD_T;

typedef struct
{
    unsigned int X1;   // 左上角x坐标
    unsigned int Y1;   // 左上角y坐标
    unsigned int X2;   // 右下角x坐标
    unsigned int Y2;   // 右下角y坐标
}NET_SDK_IVE_RECT_T;

typedef struct
{
    unsigned int X1;   // 起点x坐标
    unsigned int Y1;   // 起点y坐标
    unsigned int X2;   // 终点x坐标
    unsigned int Y2;   // 终点y坐标
}NET_SDK_IVE_LINE_T;

typedef struct
{
    int X;
    int Y;
}NET_SDK_IVE_POINT_T;

typedef struct
{
	unsigned int 			   type;				 //0, JPG; 1, YUV
	unsigned int			status;			     //0, INVALID; 1, VALID; 2, SAVED
	unsigned int			width;
	unsigned int			height;
	unsigned int			dataLen;              //原图长度
	unsigned int         targetCnt;            //目标个数
	unsigned int         targetDataLen[40];    //每个目标的长度
	LONGLONG             releativePts;         //相对时间戳
	unsigned char 		extendFlag;	 //0 表示旧协议，不支持全局计数器，1表示支持全局计数器
	unsigned char			reserve1[3]; 		 //预留
	unsigned int 			globalEnterCarCounter;//总进入车辆数，一直累计
	unsigned int 			globalEnterPersonCounter;//总进入人数，一直累计
	unsigned int 			globalEnterBikeCounter;//总进入非数，一直累计
	unsigned int			globalLeaveCarCounter;//总离开车辆数，一直累计
	unsigned int 			globalLeavePersonCounter;//总离开车辆数，一直累计
	unsigned int 			globalLeaveBikeCounter;//总离开车辆数，一直累计
	unsigned char			reserve[36]; 		 //预留
}NET_SDK_IVE_EventData_T;

typedef struct
{
	int					targetId;
	unsigned int 			type;				//0, JPG; 1, YUV
	unsigned int			status;			    //0, INVALID; 1, VALID; 2, SAVED
	unsigned int			width;
	unsigned int			height;
	NET_SDK_IVE_RECT_T    pos;
	unsigned int			dataLen;
	unsigned char        targetType;
	unsigned char        reserved[3];
	LONGLONG             absolutePts;         //绝对时间戳
	unsigned char        reserved1[44];
}NET_SDK_IVE_EvenTargetData_T;

typedef struct
{
    unsigned int       length;               // 轨迹长度，即个数
    NET_SDK_IVE_POINT_T   points[32];           // 中心点坐标
}NET_SDK_IVE_TRAJECT_T;

typedef struct
{
    unsigned int          targetId;          // 目标ID
    NET_SDK_IVE_POINT_T      point;             // 当前位置中心点坐标
    NET_SDK_IVE_RECT_T       rect;              // 目标轮廓矩形框
    unsigned int           velocity;          // 速度
    unsigned int           direction;         // 方向
    NET_SDK_IVE_TRAJECT_T    traject;           // 轨迹
}NET_SDK_IVE_TGT_INFO_T;

typedef struct
{
    unsigned int         targetNum;          // 个数
    NET_SDK_IVE_TGT_INFO_T  targetInfo[32];
}NET_SDK_IVE_TARGET_T;                          // 目标信息，即轨迹

typedef struct
{
    unsigned int      pointNum;              // 区域包含点的个数（0或3到8）
    NET_SDK_IVE_POINT_T  point[32];             // 点的坐标信息
}NET_SDK_IVE_RULE_BOUNDARY_T;

typedef struct
{
    unsigned int                eventId;     // 事件ID
    unsigned int                status;      // 报警状态,0:none 1:start 2:end 3:procedure
    unsigned int                targetId;    // 目标ID
    NET_SDK_IVE_RULE_BOUNDARY_T    boundary;    // 区域入域规则信息
    NET_SDK_IVE_RECT_T             rect;        // 目标矩形框
}NET_SDK_IVE_PER_INFO_T;

typedef struct
{
    unsigned int          count;             // 个数
    NET_SDK_IVE_PER_INFO_T   perInfo[32];       // 区域入侵分析结果信息
}NET_SDK_IVE_PERIMETER_T;

typedef struct
{
    unsigned int         eventId;            // 事件ID
    unsigned int         status;             // 报警状态,0:none 1:start 2:end 3:procedure
    unsigned int         targetId;           // 目标ID
    NET_SDK_IVE_LINE_T      line;               // 绊线规则信息
    NET_SDK_IVE_RECT_T      rect;               // 目标矩形框
}NET_SDK_IVE_TRIP_INFO_T;

typedef struct
{
    unsigned int          count;             // 个数
    NET_SDK_IVE_TRIP_INFO_T  tripInfo[32];      // 绊线分析结果信息
}NET_SDK_IVE_TRIPWIRE_T;

typedef struct
{
    NET_SDK_IVE_PERIMETER_T   perimeter;        // 区域入侵
    NET_SDK_IVE_TRIPWIRE_T    tripwire;         // 绊线检测
}NET_SDK_IVE_PEA_T;
typedef struct
{
    unsigned int      eventId;               // 事件ID
    unsigned int      status;                // 0:none 1:start 2:end 3:procedure
    unsigned int      targetId;              // 目标ID
    NET_SDK_IVE_RECT_T   rect;                  // 目标矩形框
}NET_SDK_IVE_OSC_INFO_T;

typedef struct
{
    unsigned int          count;             // 个数
    NET_SDK_IVE_OSC_INFO_T   oscInfo[32];       // 物品看护信息
}NET_SDK_IVE_OSC_T;

typedef struct
{
    NET_SDK_IVE_RECT_T              stRectInfo;                     // 目标矩形框
    unsigned char                  iCrossLineType;                 // 跨线类型
}NET_SDK_IVE_CPC_INFO_T;

typedef struct
{
    unsigned long long                  iRelativeTick;                  // 时间戳
//    IVE_RECT_T              stRectInfo;                     // 目标矩形框
//    IVE_LINE_T              stLineInfo;                     // 线段信息
    unsigned int                 iCrossInNum;                    // 跨线类型I的人数
    unsigned int                 iCrossOutNum;                   // 跨线类型II的人数
}NET_SDK_IVE_CPC_HEAD_INFO_T;

typedef struct
{
    unsigned int                 iRatio;                         // 人群密度等级
    NET_SDK_IVE_RECT_T              rect;                           // 目标矩形框
}NET_SDK_IVE_CDD_INFO_T;

typedef struct
{
    unsigned int                 iTargerId;                      // 目标ID号
    NET_SDK_IVE_RECT_T              rect;                           // 目标矩形框
}NET_SDK_IVE_IPD_INFO_T;

typedef struct
{
    unsigned long long                  iRelativeTick;                  // 时间戳
    bool                    bTriggerAlarm;                  // 是否触发了报警
//    IVE_RECT_T              stRectInfo;                     // 目标矩形框
}NET_SDK_IVE_IPD_HEAD_INFO_T;

typedef struct
{
    DD_TIME_EX  frameTime;   //帧时间
	unsigned int dwRealFaceID;  //抓拍人脸ID
	unsigned int dwGrpID;       //特征组ID
	unsigned int dwLibFaceID;   //特征库人脸ID
	unsigned int dwSimilar;     //相似度
	unsigned char byName[32]; //姓名
    unsigned int Channel;         //通道ID
	#ifdef __CHONGQING_ZHONGRAN__
	char    szCredential[DD_MAX_CERTIFICATE_NUM];  //证件号码, '\0' 结束,具有唯一性
	char    serialNumber[32];  //序列号

	#endif
	unsigned int imgLen;      //人脸数据长度
	#ifdef __CHONGQING_ZHONGRAN__
	unsigned int BackLen;     //背景大图数据长度
	#endif
}NET_SDK_IVE_FACE_MATCH_T;
//人脸特征库摘要信息
typedef struct _net_sdk_tag_avp_store_face_abstract_info
{
	char szName[32];                                    //名称
	unsigned int dwBirth;                    //出生日期,如19991234
	char szNativePlace[16];             //籍贯
	char szNote[16];                  //备注
	unsigned char byPicNum;                    //图片数量，最大5张
	unsigned char byTypeCredential;            //证件类型
	unsigned char bySex;                       //性别 0 male      1 female
	unsigned char byGroupCount;                //所属组ID
	unsigned char byGroupID[4];
	union
	{
		struct
		{
			unsigned int dwStartTime;
			unsigned int dwReserve[3];
			unsigned int dwEndTime;
			unsigned char  byReserve[11];
			unsigned char  byContentType;/////0=V1,1=V2......
		}PeriodV1;

		struct
		{
			unsigned int  byWeekOrDate;////everyday  date,   1  2   3  4   5   6  7
			unsigned int  dwReserve[3];
			unsigned short  wStartTime;
			unsigned short  wEndTime;
			unsigned short  wReserve[5];
			unsigned char   byMode;////byWeek   byDate
			unsigned char   byContentType;/////0=V1,1=V2......
		}PeriodV2;

		struct
		{
			unsigned char  dwReserve[31];
			unsigned char  byContentType;/////0=V1,1=V2......
		}PlaceHolder;
	}TimeCycle;////

	char szCredential[32];              //证件号码, '\0' 结束     具有唯一性
	unsigned char   byPhoneNum[16];            //手机号码
	unsigned char   byIDParam[16];             /////具有唯一性
}NET_SDK_AVPSTORE_FACE_ABSTRACT_INFO;

typedef struct _net_sdk_tag_TLV_buffer_description
{
	unsigned char ucID;                        //1B,数据ID,由应用方定义
	unsigned char ucVersion;        //1B,数据版本,由应用方定义
	unsigned short usNumber;        //2B,单位数量,最多65535
	unsigned int dwSize;            //4B,单个信息大小, 总长度=usNumber*dwSize
}NET_SDK_TLV_BUFFER_DESC;
typedef struct
{
	unsigned short usPureFeatureSize; //不包含本结构体
	unsigned char byAlgVersion1;
	unsigned char byFeatureType; //Feature_Type

	unsigned char byManufactory;//Feature_Manufactory
	unsigned char byHeaderSize;
	unsigned char byAlgVersion2;
	unsigned char byReserved; //set it to be zero
}NET_SDK_FEATURE_DATA_HEADER; //此头长度不得超过 NVMS_DEFINE::SERIALIZED_FEATUR_HEADER_MAX_SIZE

typedef struct
{
    unsigned int          minValue;             // 最小值
    unsigned int          maxValue;             // 最大值
    unsigned int          curValue;             // 当前值
    unsigned int          defaultValue;             // 默认值

}NET_SDK_IMAGE_EFFECT_T;

typedef struct _net_sdk_ch_device_status_
{
    unsigned short	channel;				//通道(从0开始)
    unsigned short	status;					//连接状态（0:offline，videoloss. 1: online,signal）
    unsigned int    chlType;               //E_DIGITAL_CHL_TYPE,数字通道 E_ANALOG_CHL_TYPE,模拟通道
    char	         name [DD_MAX_CAMERA_NAME_BUF_LEN];
    unsigned char	resv[32];				//暂时未用上
}NET_SDK_CH_DEVICE_STATUS;

typedef struct _net_sdk_ch_device_support_
{
	unsigned short	channel;				//通道(从0开始)
	unsigned char	supportFisheye;				//是否支持鱼眼

	unsigned char	resv[33];				//暂时未用上

}NET_SDK_CH_DEVICE_SUPPORT;


//人脸对比
typedef enum _net_sdk_face_info_group__property_type
{
    NET_SDK_FACE_INFO_GROUP_PROPERTY_ALLOW,
    NET_SDK_FACE_INFO_GROUP_PROPERTY_REJECT,
    NET_SDK_FACE_INFO_GROUP_PROPERTY_LIMITED,

}NET_SDK_FACE_INFO_GROUP_PROPERTY_TYPE;

typedef struct _net_sdk_face_info_group_item_
{
    unsigned char	guid[48];				//GROUP GUID
    char	         name[DD_MAX_NAME_LEN];//GROUP NAME
    unsigned int	property;		//NET_SDK_FACE_INFO_GROUP_PROPERTY_TYPE
    unsigned int    groupId;               //
    unsigned int    enableAlarmSwitch;

}NET_SDK_FACE_INFO_GROUP_ITEM;

typedef struct _net_sdk_face_info_group_add_
{
    char	         name[DD_MAX_NAME_LEN];//GROUP NAME
    unsigned int	property;		//NET_SDK_FACE_INFO_GROUP_PROPERTY_TYPE
}NET_SDK_FACE_INFO_GROUP_ADD;

typedef struct _net_sdk_face_info_group_del_
{
    unsigned char	guid[48];				//GROUP GUID
}NET_SDK_FACE_INFO_GROUP_DEL;

//两者可任选其一
typedef struct _net_sdk_face_info_group_del_ex_
{
    unsigned int	groupId;				//GROUP ID 国内定制版本用此参数
    unsigned char   guid[48];				//GROUP GUID 通用版本用此参数
}NET_SDK_FACE_INFO_GROUP_DEL_EX;

typedef struct _net_sdk_face_info_list_get_
{
    unsigned int	pageIndex;		//必填1、2、3...
    unsigned int    pageSize;   //必填
    unsigned int    groupId;//必填 1、2、3....

    char	        name[DD_MAX_NAME_LEN];//不填时清空 NET_SDK_FACE_INFO_LIST_ITEM中的name
    unsigned int    itemId;				//不填时清零 NET_SDK_FACE_INFO_LIST_ITEM中的itemId
    #ifdef __CHONGQING_ZHONGRAN__
    char	        certificateNum[DD_MAX_CERTIFICATE_NUM];		//
    #endif
}NET_SDK_FACE_INFO_LIST_GET;

typedef struct _net_sdk_face_info_list_item_groups_
{
    unsigned int    groupId;        //GROUP id 获取目标list返回的时候没有 guid
    unsigned char	guid[48];				//GROUP GUID 增加，编辑目标必须要用 guid
    DD_TIME_EX    validStartTime;//property为limited时才有validStartTime，validEndTime
    DD_TIME_EX    validEndTime;//property为limited时才有validStartTime，validEndTime
}NET_SDK_FACE_INFO_LIST_ITEM_GROUPS;

typedef struct _net_sdk_face_info_list_item_
{
    unsigned int    itemId;				//id
    char	        name[DD_MAX_NAME_LEN];		//必填
    unsigned int    sex; //0:male 1:female
    unsigned int    birthday;//eg:19900707
    char	        nativePlace[DD_MAX_NAME_LEN];		//
    unsigned int    certificateType; //0:idCard
    char	        certificateNum[DD_MAX_CERTIFICATE_NUM];		//
    char	        mobile[20];		//
    char	        number[20];		//
    unsigned int    faceImgCount;
    NET_SDK_FACE_INFO_LIST_ITEM_GROUPS    groups[DD_MAX_FACE_INFO_GROUPS];

}NET_SDK_FACE_INFO_LIST_ITEM;

typedef struct _net_sdk_face_info_list_
{
    unsigned int    totalNum;				//
    unsigned int    listNum;//return NET_SDK_FACE_INFO_LIST_ITEM num
    NET_SDK_FACE_INFO_LIST_ITEM *pFaceInfoListItem;
}NET_SDK_FACE_INFO_LIST;

typedef struct _net_sdk_face_img_info_ch_
{
    DD_TIME_EX         frameTime;
    unsigned int    snapImgId;//抓拍图片id
	unsigned int    targetImgId;//目标图片id
    unsigned int    chl; //返回值 255 表示已经删除的通道
	unsigned char   isPanorama;//0表示抓拍图片，1表示全景图
    unsigned char   resv[7];//保留

}NET_SDK_FACE_IMG_INFO_CH;

typedef struct _net_sdk_face_info_add_
{

    NET_SDK_FACE_INFO_LIST_ITEM sFaceInfoItem;
    unsigned int                imgNum;
    NET_SDK_FACE_IMG_INFO_CH       sFaceImgInfo[DD_MAX_FACE_INFO_IMG];//最大5张
    unsigned int                haveImgData;//0、1
    unsigned int                imgWidth;//haveImgData ==1 有效
    unsigned int                imgHeight;//haveImgData ==1 有效
    unsigned int                imgLen;//haveImgData ==1 有效
    unsigned char               *imgData;//haveImgData ==1 有效
}NET_SDK_FACE_INFO_ADD;

typedef struct _net_sdk_face_info_edit_
{
    unsigned int            delFaceImgs[DD_MAX_FACE_INFO_IMG];
    NET_SDK_FACE_INFO_ADD   sFaceInfoItem;

}NET_SDK_FACE_INFO_EDIT;
typedef struct _net_sdk_face_info_copy_
{

	unsigned int    itemId;				//id   通过此id去获取图片
	char	        name[DD_MAX_NAME_LEN];		//必填
	unsigned int    sex; //0:male 1:female
	unsigned int    birthday;//eg:19900707
	char	        nativePlace[DD_MAX_NAME_LEN];		//
	unsigned int    certificateType; //0:idCard
	char	        certificateNum[DD_MAX_CERTIFICATE_NUM];		//
	char	        mobile[20];		//
	char	        number[20];		//

	//NET_SDK_FACE_INFO_LIST_ITEM_GROUPS    groups【0】.guid
	unsigned char	guid[48];				//GROUP GUID 增加，编辑目标必须要用 guid     目标库的guid



}NET_SDK_FACE_INFO_COPY;

typedef struct _net_sdk_face_info_del_
{
    unsigned int    faceInfoListItemId;//NET_SDK_FACE_INFO_LIST_ITEM中的itemId
    unsigned int    groupsId[DD_MAX_FACE_INFO_GROUPS];//NET_SDK_FACE_INFO_LIST_ITEM中的itemId-->groups-->groupId

}NET_SDK_FACE_INFO_DEL;

typedef struct _net_sdk_face_match_alarm_trigger_
{
    unsigned char	guid[48];	//GROUP GUID
    unsigned int    groupId;    //组ID
    unsigned char    groupSwitch;//启用
    unsigned char    alarmOutSwitch;//联动报警输出
    unsigned char    alarmOut[16];//联动报警输出默认最多16个 下标从1开始
    unsigned char    recSwitch;//录像
    unsigned int    recCH[128];//联动录像通道 下标从1开始
    unsigned char    snapSwitch;//抓图
    unsigned int    snapCH[128];//联动抓图通道 下标从1开始
    unsigned int    popVideo;//视频弹出
    unsigned char    msgPushSwitch;
    unsigned char    buzzerSwitch;
    unsigned char    popMsgSwitch;
    unsigned char    emailSwitch;

}NET_SDK_FACE_MATCH_ALARM_TRIGGER;

typedef struct _net_sdk_face_match_chan_group_
{
	unsigned int    faceFeatureGroupsNum;  //通道拥有的目标组个数
    unsigned int    pfaceFeatureGroupIDs[16]; //通道拥有的目标组ID列表,有效个数为faceFeatureGroupsNum
}NET_SDK_FACE_MATCH_CHAN_GROUP;

typedef struct _net_sdk_face_match_alarm_
{
    unsigned int    similarity;//相似度
    unsigned int    enableCH[128];//【开启通道】 通道下标从1开始
	#ifdef __CHONGQING_ZHONGRAN__
	NET_SDK_FACE_MATCH_CHAN_GROUP FaceMatchChanGroup[128]; //与【开启通道】严格对应
	#endif
    unsigned int    faceFeatureGroupsNum;//目标组个数
    NET_SDK_FACE_MATCH_ALARM_TRIGGER *pFaceMatchAlarmTrigger;

}NET_SDK_FACE_MATCH_ALARM;

typedef struct _net_sdk_face_info_img_get_
{

    unsigned int    itemId;	//目标id
    unsigned int    index;//faceImgCount中的index 1开始

}NET_SDK_FACE_INFO_IMG_GET;

typedef struct _net_sdk_face_info_img_data_
{
    unsigned int                imgLen;//目标图片长度
	unsigned int				grade;//人脸评分
    unsigned char               *imgData;//目标图片数据

}NET_SDK_FACE_INFO_IMG_DATA;

typedef enum _net_sdk_search_image_by_image_type_
{
    SEARCH_IMAGE_BY_FACE_FEATURES,//通过人脸特征搜索
    SEARCH_IMAGE_BY_FACE_IMAGES,//通过人脸图片搜索
    SEARCH_IMAGE_BY_FACE_FEATURE_GROUPS,//通过人脸特征分组搜索
    SEARCH_IMAGE_BY_RECONGNIZED_FILTER,//通过与指定人脸特征分组比对是否识别进行过滤
    SEARCH_IMAGE_BY_FACE_IMAGE_DATA,//通过图片数据进行搜索

}NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE;


typedef struct _net_sdk_search_image_by_image_
{
    unsigned int	pageIndex;		//必填1、2、3...
    unsigned int    pageSize;   //必填
    unsigned int    similarity;		//相似度
    unsigned int    resultCountLimit;		//结果个数限制
    DD_TIME_EX    startTime;
    DD_TIME_EX    endTime;
    unsigned int searchType;//NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE
    struct
    {
       unsigned int itemId;	//目标id
    } sfaceFeatures;//SEARCH_IMAGE_BY_FACE_FEATURES
    NET_SDK_FACE_IMG_INFO_CH sfaceImgs;//SEARCH_IMAGE_BY_FACE_IMAGES

    struct
    {
       unsigned int	groupsId;				//GROUP Id
    }sfaceFeatureGroups ;//SEARCH_IMAGE_BY_FACE_FEATURE_GROUPS

    struct
    {
       unsigned int     isContainRecognized; //0 or 1
       unsigned int     isContainNotRecognized; //0 or 1
       unsigned int     groupsId;				//GROUP Id
    }srecognizedFilter ;//SEARCH_IMAGE_BY_RECONGNIZED_FILTER
    struct
    {
        unsigned int                imgWidth;//
        unsigned int                imgHeight;//
        unsigned int                imgLen;//
        unsigned char               *imgData;//
    }sfaceImgData;//SEARCH_IMAGE_BY_FACE_IMAGE_DATA

}NET_SDK_SEARCH_IMAGE_BY_IMAGE;

typedef struct _net_sdk_search_image_by_image_v2
{
	unsigned int    limitNum;   //必填
	DD_TIME_EX    startTime;
	DD_TIME_EX    endTime;

	unsigned int    similarity;		//相似度
	unsigned int searchType;//NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE_V2
	unsigned int imgSourceType;//图片来源，当searchType为SEARCH_IMAGE_BY_IMAGE时用到，NET_SDK_SEARCH_IMAGE_SOURCE_V2

	unsigned int imgNum;//图片id数量，当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_ALBUM用到
	unsigned int *imgId;//图片id，当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_ALBUM用到
	unsigned int eventType;//当searchType为SEARCH_IMAGE_BY_EVENT时用到，NET_SDK_SEARCH_IMAGE_BY_EVENT_TYPE_V2

	unsigned int groupsNum;//目标库数量，当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_GROUP用到
	unsigned int *groupsId;	//目标库Id，当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_GROUP用到

	unsigned int sfaceImgsNum;//图片数量，当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_SNAP用到
	NET_SDK_FACE_IMG_INFO_CH *sfaceImgs;//SEARCH_IMAGE_BY_FACE_IMAGES,当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_SNAP用到

	struct
	{
		unsigned int                imgWidth;//
		unsigned int                imgHeight;//
		unsigned int                imgLen;//
		unsigned char               *imgData;//
	}sfaceImgData;//当searchType为SEARCH_IMAGE_BY_IMAGE时,imgSourceType为FROM_EXTERNAL用到

}NET_SDK_SEARCH_IMAGE_BY_IMAGE_V2;
typedef enum _net_sdk_search_image_by_image_type_v2
{
	SEARCH_IMAGE_BY_IMAGE,//通过人脸图片搜索
	SEARCH_IMAGE_BY_EVENT,//通过事件搜索

}NET_SDK_SEARCH_IMAGE_BY_IMAGE_TYPE_V2;
typedef enum _net_sdk_search_image_by_event_v2
{
	BY_ALL,//搜索“所有” byAll
	BY_WHITELIST,//搜索“常规” byWhiteList
	BY_STRANGERLIST,//搜索“陌生人”byStrangerList
	BY_BLACKLIST,//搜索“黑名单”byBlackList
}NET_SDK_SEARCH_IMAGE_BY_EVENT_TYPE_V2;
typedef enum _net_sdk_search_image_source_v2
{
	FROM_ALBUM,//图片来自目标库
	FROM_SNAP,//图片来自抓拍
	FROM_GROUP,//图片来自整个目标库所有目标
	FROM_EXTERNAL,//图片来自自选图片仅支持一张，大小不能超过200KB
}NET_SDK_SEARCH_IMAGE_SOURCE_V2;

typedef struct _net_sdk_search_image_item_
{
    DD_TIME_EX     recStartTime;
    DD_TIME_EX     recEndTime;
    unsigned int    similarity;		//相似度
    unsigned int    faceFeatureId; //通过人脸特征搜索时，和哪个特征匹配
    NET_SDK_FACE_IMG_INFO_CH sfaceImg; //通过人脸图片搜索时，和哪个图片匹配
    unsigned char       resv[4];//保留

}NET_SDK_SEARCH_IMAGE_ITEM;

typedef struct _net_sdk_search_image_by_image_list_
{
    unsigned int    bEnd; //为1表述搜图个数已结束， 0表示后面还有
    unsigned int    listNum;//return NET_SDK_SEARCH_IMAGE_ITEM num
    NET_SDK_SEARCH_IMAGE_ITEM *pSearchImageItem;
}NET_SDK_SEARCH_IMAGE_BY_IMAGE_LIST;


typedef struct _net_sdk_ch_snap_face_img_list_
{
    unsigned int    bEnd; //为1表述搜图个数已结束， 0表示后面还有
    unsigned int    listNum;//return NET_SDK_FACE_IMG_INFO_CH num
    NET_SDK_FACE_IMG_INFO_CH *pCHFaceImgItem;
}NET_SDK_CH_SNAP_FACE_IMG_LIST;

typedef struct _net_sdk_ch_snap_face_img_list_sreach_
{
    DWORD			dwChannel;//抓图通道
    DD_TIME_EX			startTime; //时间
    DD_TIME_EX			endTime; //时间
    DWORD			pageIndex;//第几页
    DWORD			pageSize;//每页数

    unsigned char	resv[8];
}NET_SDK_CH_SNAP_FACE_IMG_LIST_SEARCH;
typedef struct _net_sdk_search_smart_target
{
	unsigned int    limitNum;   //必填
	DD_TIME_EX    startTime;
	DD_TIME_EX    endTime;
	unsigned char faceDetection;
	unsigned char faceMatchWhiteList;
	unsigned char faceMatchBlackList;
	unsigned char faceMatchStrangerList;
	unsigned char intrusion;
	unsigned char tripwire;
	unsigned char car;
	unsigned char motor;
	unsigned char male;
	unsigned char female;
	unsigned char	resv[22];

}NET_SDK_SEARCH_SMART_TARGET;
typedef struct _net_sdk_smart_target_snap_img_
{
	DD_TIME_EX         frameTime;
	unsigned int    imgId;
	unsigned int    chl; //返回值 255 表示已经删除的通道
	unsigned char	pathGUID[48];//数据所在的存储GUID
	unsigned int	sectionNo;
	unsigned int	fileIndex;
	unsigned int	blockNo;
	unsigned int	offset;
	unsigned int	eventType;
	unsigned char   isPanorama;//0表示抓拍图片，1表示全景图
	unsigned char   resv[7];//保留

}NET_SDK_SMART_TARGET_SNAP_IMG;
typedef struct _net_sdk_smart_target_snap_img_list_
{
	unsigned int    bEnd; //为1表述搜图个数已结束， 0表示后面还有
	unsigned int    listNum;//return NET_SDK_SMART_TARGET_SNAP_IMG num
	NET_SDK_SMART_TARGET_SNAP_IMG *pImgItem;
}NET_SDK_SMART_TARGET_SNAP_IMG_LIST;
typedef enum _net_sdk_timequantum_type
{
	ONE_DAY,
	ONE_WEEK,
	ONE_MONTH,
	ONE_SEASON,
}NET_SDK_TIMEQUANTUM_TYPE;
typedef struct _net_sdk_face_img_statistic_v2
{
	unsigned int    limitNum;   //
	DD_TIME_EX    startTime;
	DD_TIME_EX    endTime;
	unsigned int  timeQuantum;//NET_SDK_TIMEQUANTUM_TYPE
	unsigned char faceDetection;
	unsigned char faceMatchWhiteList;
	unsigned char faceMatchBlackList;
	unsigned char faceMatchStranger;
	unsigned char intrusion;
	unsigned char tripwire;
	unsigned char car;
	unsigned char motor;
	unsigned char male;
	unsigned char female;
	unsigned char	resv[22];

}NET_SDK_FACE_IMG_STATISTIC_V2;

typedef struct _net_sdk_face_img_statistic_result_chl
{
	unsigned int chlId;//
	unsigned int imageNum;

}NET_SDK_FACE_IMG_STATISTIC_RESULT_CHL;
typedef struct _net_sdk_face_img_statistic_result
{
	unsigned int imageTotalNum;
	unsigned int chlNum;
	NET_SDK_FACE_IMG_STATISTIC_RESULT_CHL *pItem;

}NET_SDK_FACE_IMG_STATISTIC_RESULT;
typedef struct _net_sdk_face_img_statistic_result_list
{
	unsigned int    resNum;//return NET_SDK_FACE_IMG_STATISTIC_RESULT num
	NET_SDK_FACE_IMG_STATISTIC_RESULT *pItem;
}NET_SDK_FACE_IMG_STATISTIC_RESULT_LIST;
//人脸库相关
typedef enum _net_sdk_face_match_operate_type
{
    NET_SDK_GET_FACE_MATCH_SUPPORT=0x01,//in:NULL, out:DWORD
    //目标组
    NET_SDK_GET_FACE_INFO_GROUP_LIST,//queryFacePersonnalInfoGroupList in:NULL, out:NET_SDK_FACE_INFO_GROUP_ITEM list
    NET_SDK_ADD_FACE_INFO_GROUP,//createFacePersonnalInfoGroup in:NET_SDK_FACE_INFO_GROUP_ADD out:NULL
    NET_SDK_SET_FACE_INFO_GROUP,//editFacePersonnalInfoGroup in:NET_SDK_FACE_INFO_GROUP_ITEM  out:NULL
    NET_SDK_DEL_FACE_INFO_GROUP,//delFacePersonnalInfoGroups in:NET_SDK_FACE_INFO_GROUP_DEL  out:NULL
    //目标
    NET_SDK_GET_FACE_INFO_LIST,//queryFacePersonnalInfoList in:NET_SDK_FACE_INFO_LIST_GET, out:NET_SDK_FACE_INFO_LIST
    NET_SDK_ADD_FACE_INFO,//createFacePersonnalInfo in:NET_SDK_FACE_INFO_ADD out:DWORD
    NET_SDK_SET_FACE_INFO,//editFacePersonnalInfo in:NET_SDK_FACE_INFO_EDIT out:NULL
    NET_SDK_DEL_FACE_INFO,//delFacePersonnalInfo in:NET_SDK_FACE_INFO_DEL  out:NULL
    //对比报警配置
    NET_SDK_GET_FACE_MATCH_ALARM,//queryFaceMatchAlarm  in:NULL out:NET_SDK_FACE_MATCH_ALARM
    NET_SDK_SET_FACE_MATCH_ALARM,//editFaceMatchAlarm in:NET_SDK_FACE_MATCH_ALARM out:NULL
    //请求人脸目标图片
    NET_SDK_GET_FACE_INFO_IMG,//requestFacePersonnalInfoImage in:NET_SDK_FACE_INFO_IMG_GET out:NET_SDK_FACE_INFO_IMG_DATA
    //以图搜图 searchImageByImage
    NET_SDK_SEARCH_IMAGE_BY_IMG, //searchImageByImage in:NET_SDK_SEARCH_IMAGE_BY_IMAGE out:NET_SDK_SEARCH_IMAGE_BY_IMAGE_LIST
    //查询通道人脸图片
    NET_SDK_SEARCH_CH_SNAP_FACE_IMG_LIST,//queryChSnapFaceImageList in:NET_SDK_CH_SNAP_FACE_IMG_LIST_SEARCH out:NET_SDK_CH_SNAP_FACE_IMG_LIST
    //请求通道人脸图片数据
    NET_SDK_SEARCH_CH_SNAP_FACE_IMG,//requestChSnapFaceImage in:NET_SDK_FACE_IMG_INFO_CH out:NET_SDK_FACE_INFO_IMG_DATA
    //For IPC，目标
//    -----------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO_T		|
//    -----------------------------------------
//    |	图片数据							|
//    -----------------------------------------
    NET_SDK_ADD_FACE_IPC, //in:NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO out: NET_SDK_NET_REPLY_RESULT
    NET_SDK_DEL_FACE_IPC,//in:NET_SDK_IVE_FACE_MATCH_DELE_ALBUM_INFO out: NET_SDK_NET_REPLY_RESULT
//    -----------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO_T		|
//    ---------------------------------------------
//    |	图片数据(如果未修改图片, 则没有此部分)	|
    NET_SDK_EDIT_FACE_IPC, //in:NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO out: NET_SDK_NET_REPLY_RESULT

//    请求:
//    ---------------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO		|
//    ---------------------------------------------
//    回复:
//    -------------------------------------------------
//    |	int32	符合查询条件的总数目				|
//    -------------------------------------------------
//    |	int32	当前次返回的结果条目数				|
//    -------------------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO		|
//    -------------------------------------------------
//    |	图片数据									|
//    -------------------------------------------------
//    |	NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO		|
//    -------------------------------------------------
//    |	图片数据									|
//    -------------------------------------------------
//    |	...											|
//    -------------------------------------------------
 //   附加说明: 数据段前1-4个字节(int32)表示符合条件的总条目数, 失败返回<=0，固定存在; 数据段5-8个字节(int32)表示当前次返回的条目数, 固定存在。
    NET_SDK_GET_FACE_IPC_LIST, //in:NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO out:见上注释

	NET_SDK_COPY_FACE_INFO,//
	NET_SDK_SEARCH_IMAGE_BY_IMG_V2,//
	NET_SDK_SEARCH_SMART_TARGET_LIST,//搜索目标
	NET_SDK_SEARCH_SMART_TARGET_IMG,//搜索目标图片
	NET_SDK_GET_FACE_IMG_STATISTIC_V2,//请求统计
	NET_SDK_GET_FACE_INFO,//获取指定id的人脸目标图片信息

}NET_SDK_FACE_MATCH_OPERATE_TYPE;



typedef struct NET_SDK_IVE_BASE_INFO_T
{
	long long            i64SnapTime;               // 抓拍时间.
	unsigned int             iSnapPicId;                // 抓拍ID.

	int                 iSimilarity;               // 人脸比对相似度.(0-100)
	int                 iPersonId;                 // 人员ID.
	int                 iType;                     // 名单类型 0:陌生人 1:白名单 2:黑名单.
	char                szName[128];               // 姓名.
	int                 iMale;                     // 性别 1:male 0:female.
	int                 iAge;                      // 年龄.
	char                szIdentifyNum[128];        // 身份识别号.
	char                szTel[64];                 // 电话.
	char                szRes[128];                // reserve

	int                 iSnapPicQuality;           // 抓拍人脸质量.
	int                 iSnapPicAge;               // 抓拍人脸年龄.
	int                 iSnapPicSex;               // 抓拍人脸性别.

	char                livingBody;                     // 是否是活体 1活体,0非活
	char                comparisonRes;                  // 比对结果 1成功,0失败
    char                wearmask;                  // 是否戴口罩:0是未检测，1是未戴口罩 2是戴口罩
    char                tempUnitsType;             // 温度单位 0摄氏度 1华氏度
	int                 temperature;                    // 体温

	char                keyID[36];                  //人脸库主键
	char                szReserve[20];

}NET_SDK_IVE_BASE_INFO;


typedef struct NET_SDK_IVE_PICTURE_INFO_T
{
	int                 iWidth;                    // 图片宽.
	int                 iHeight;                   // 图片高.
	int                 iPicFormat;                // 图片格式.
	int                 iPicSize;                  // 图片大小.

}NET_SDK_IVE_PICTURE_INFO;

typedef struct NET_SDK_PASSLINE_PICTURE_INFO_T
{
	int                 iWidth;                    // 图片宽.
	int                 iHeight;                   // 图片高.
	int                 iPicFormat;                // 图片格式.
	int                 iPicSize;                  // 图片大小.

}NET_SDK_PASSLINE_PICTURE_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO_T
{
    int                 iType;                     // 名单类型 0:陌生人 1:白名单 2:黑名单.
    char                szName[128];               // 姓名.
    int                 iMale;                     // 性别 1:male 0:female.
    int                 iAge;                      // 年龄.
    char                szIdentifyNum[128];        // 身份识别号.
    char                szTel[64];                 // 电话.
    int                 iWidth;                    // 图片宽.
    int                 iHeight;                   // 图片高.
    int                 iPicFormat;                // 图片格式.
    int                 iPicSize;                  // 图片大小.
    char                szRes[128];                // reserve

}NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO;
typedef struct _net_sdk_net_reply
{
    unsigned int dwResult;
}NET_SDK_NET_REPLY_RESULT;

typedef struct _net_sdk_ive_face_match_add_face_reply_t
{
	unsigned int             dwResult;
	int                 iPersonId;                 // 人员ID.
	char                szRes[32];
}NET_SDK_IVE_FACE_MATCH_ADD_FACE_REPLY_T;


typedef struct NET_SDK_IVE_FACE_MATCH_DELE_ALBUM_INFO_T
{
    bool                bUseKeyFilter;             // 使用键值过滤删除.
    int              iKey;                      // 键值.
    bool                bUseTypeFilter;            // 使用黑白名单过滤删除.
    int              iType;                     // 名单类型 0:陌生人 1:白名单 2:黑名单.
    bool                bUseSexFilter;             // 使用性别过滤删除.
    int              iMale;                     // 性别 1:male 0:female.
    bool                bUseName;                  // 使用姓名模糊查询.
    char                szName[128];
    bool                bUseIdentify;              // 使用ID匹配.
    char                szIdentifyNum[128];
    /* 可依据需求扩展过滤条件, 进行模糊删除 */
}NET_SDK_IVE_FACE_MATCH_DELE_ALBUM_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO_T
{
    int              				iKey;      // 键值.
    NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO		stBaseInfo;// 基本信息.
}NET_SDK_IVE_FACE_MATCH_MODIFY_ALBUM_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO_T
{
    int				iPageNum;				   // 页码(从0开始).
    int				iPageSize;				   // 每页条目数.(范围1-10)
    bool                bUseKeyFilter;             // 使用键值过滤删除.
    int              iKey;                      // 键值.
    bool                bUseNameFilter;            // 使用姓名过滤查询.
    char                szName[128];               // 姓名.
    bool                bUseTypeFilter;            // 使用黑白名单过滤查询.
    int              iType;                     // 名单类型 0:陌生人 1:白名单 2:黑名单.
    bool                bUseSexFilter;             // 使用性别过滤查询.
    int              iMale;                     // 性别 1:male 0:female.
    bool                bUseIdentify;              // 使用ID匹配.
    char                szIdentifyNum[128];
    /* 可依据需求扩展过滤条件, 进行模糊查询 */
    /* 若没有过滤条件则按顺序返回相册库信息 */
}NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_INFO;

typedef struct NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO_T
{
    int              				iKey;      // 键值.
    NET_SDK_IVE_FACE_MATCH_ADD_ALBUM_INFO		stBaseInfo;// 基本信息.
}NET_SDK_IVE_FACE_MATCH_QUERY_ALBUM_REPLY_INFO;
typedef enum upgrade_file_type
{
	SOFTWARE = 0,//软件升级
	KERNEL,//内核升级
	UBOOT,//uboot升级
	AILIB,//智能库升级
}UPGRADE_FILE_TYPE;

typedef struct _usb_backup_process
{
	int process;//备份进度0-100, the process of the backup 0-100
	int status;//备份状态，见usb_backup_status,
}NET_SDK_USB_BACKUP_PROCESS;

typedef struct _usb_backup_process_ex
{
	DD_TIME_EX			startTime; //备份录像开始时间 the start time of the record
	DD_TIME_EX			endTime; //备份录像结束时间 the end time of the record
	unsigned int        dataSize;//备份文件大小MB  the size of the record
	unsigned char       backupPath[64]; //备份路径 the usb path of the backup
	unsigned char       creator[36];//备份任务创建者 the creator of the backup task
	unsigned int        progress;//备份进度0-100, the process of the backup 0-100
	unsigned int        backupFileFormat;//refer to usb_backup_format
	unsigned int        status;//备份状态，见refer to usb_backup_status,
	unsigned int        eventType;//备份录像文件类型  the record type, refer to usb_backup_record_type
	unsigned char		chls[64];//备份通道 the channel of the backup
	unsigned int        chlNum;//实际备份通道数量 the actual number of the channels

}NET_SDK_USB_BACKUP_PROCESS_EX;
typedef enum usb_backup_status
{
	ONGOING = 0,//ongoing
	COMPLETE,//complete
}USB_BACKUP_STATUS;
typedef enum usb_backup_format
{
	AVI = 0,
	PRIVATE,
}USB_BACKUP_FORMAT;

// 车牌相机协议
typedef struct
{
	unsigned int begin_flag;       //开始标识，0x5a5a5a5a
	unsigned int item_cnt;         /// NET_SDK_IVE_VEHICE_ITEM_INFO的个数
	unsigned int plate_cnt;        /// 检测到车牌个数
	long long  relativeTime;     /// 检测源数据相对时间,相对时间
	long long  absoluteTime;     /// 检测源数据当前时间,绝对时间
	unsigned int softwareVersion;  /// 软件版本号, 0xABCDEFGH,AB：厂家 CD：主版本 EFGH：子版本 厂商 1:欧姆龙 版本:V5.00
	unsigned int softwareBuildDate;/// 软件生成日期,0xYYYYMMDD
	unsigned int resver[2];
	unsigned int end_flag;         //结束标识，0xa5a5a5a5
}NET_SDK_IVE_VEHICE_HEAD_INFO;

typedef struct
{
	unsigned int     begin_flag;         //开始标识，0x5a5a5a5

	unsigned int     data_type;          //0：JPG,1:YUV
	unsigned int     image_type;         //0:原图，1：车牌

	// 车牌, 车牌坐标, 车牌置信度
	unsigned int     plateId;            /// ID，作为标识用（可参考人脸ID的实现方式）

	unsigned int     plateCharCount;     // 车牌字符个数
	char       plate[32];	        // 车牌号码, utf8编码
	char       plateCharConfid[32];   // 车牌字符置信度
	NET_SDK_IVE_RECT_T  ptPlateCharRect[32]; // 车牌字符左上角坐标

	unsigned int		ptWidth;            // 坐标比例宽（用于画车牌跟踪框，或在画面中圈出车牌的位置）
	unsigned int		ptHeight;           // 坐标比例高
	NET_SDK_IVE_POINT_T	ptLeftTop;          // 车牌左上角坐标
	NET_SDK_IVE_POINT_T	ptRightTop;         // 车牌右上角坐标
	NET_SDK_IVE_POINT_T	ptLeftBottom;       // 车牌左下角坐标
	NET_SDK_IVE_POINT_T	ptRightBottom;      // 车牌右下角坐标

	unsigned short     plateWidth;            //车牌抓拍图片宽度
	unsigned short     plateHeight;           //车牌抓拍图片高度

	unsigned int     plateConfidence;       //置信度

	unsigned int     plateIntensity;     //车牌亮度
	unsigned char      plateColor;         // 车牌颜色 // 0-蓝色 1-黑色 2-黄色 3-白色 4-绿色 5-红色 6-灰色 7-紫色(KISE)
	unsigned char      plateStyle;         // 车辆类型
	unsigned char      PlateColorRate;     // 颜色匹配程度；
	unsigned char      vehicleColor;       // 车身颜色
	unsigned int     plateAngleH;        //车牌水平倾斜角度
	unsigned int     plateAngleV;        //车牌竖直倾斜角度

	unsigned int     jpeg_len;           //Jpeg图片实际长度
	unsigned int     jpeg_vir_len;       //Jpeg图片数据按32个字节对齐的总长度
	char        owner[32];          //车主名
	int         listType;           //名单类型,0-未比对成功，1-陌生车辆，2-白名单，3-黑名单，产生比对类型【1-24】，每个分类预留8个空间,未比对【0,25-31】，未比对空间扩展到8
	unsigned long long     beginTime;           //开始时间
	unsigned long long     endTime;             //结束时间
	unsigned char      iVehicleDirect;    //车辆行驶方向，1未知 2靠近  3远离
	unsigned char      resrv[11];
	unsigned int     end_flag;           //结束标识，0ax5a5a5a5
}NET_SDK_IVE_VEHICE_ITEM_INFO;

typedef struct
{
	unsigned int          eventId;             // 事件ID
	unsigned char         status;              // 报警状态,0:none 1:start 2:end 3:procedure
	unsigned char         eventDirection;		// 事件方向 1 进入，2 离开
	unsigned char         reserve[2];          // 预留
	unsigned int          targetId;            // 目标ID
	NET_SDK_IVE_RULE_BOUNDARY_T   boundary;            // 区域入域规则信息
	NET_SDK_IVE_RECT_T           rect;              // 目标矩形框
}NET_SDK_IVE_TRAFFIC_INFO_T;

typedef struct
{
	int          enterCarCount;
	int          enterPersonCount;
	int          enterBikeCount;
	int          leaveCarCount;
	int          leavePersonCount;
	int          leaveBikeCount;
	int          existCarCount;
	int          existPersonCount;
	int          existBikeCount;
	unsigned int  count;             // 个数
	NET_SDK_IVE_TRAFFIC_INFO_T   aoiInfo[32];       // 区域入侵分析结果信息
}NET_SDK_IVE_TRAFFIC_T;

typedef struct
{
	unsigned int         eventId;            // 事件ID
	unsigned char          status;             // 报警状态,0:none 1:start 2:end 3:procedure
	unsigned char          reserve[3];         // 预留
	unsigned int         targetId;           // 目标ID
	NET_SDK_IVE_LINE_T      line;               // 绊线规则信息
	NET_SDK_IVE_RECT_T      rect;               // 目标矩形框
}NET_SDK_IVE_PASSLINECOUNT_INFO_T;

//NET_SDK_N9000_ALARM_TYPE_PASSLINE
typedef struct
{

	unsigned int           enterCarCount; //进入车辆数
	unsigned int           enterPersonCount;//进入人数
	unsigned int           enterBikeCount;//进入自行车数
	unsigned int           leaveCarCount; //离开车辆数，如果单向计数，此字段值为0
	unsigned int           leavePersonCount;//离开人数，如果单向计数，此字段值为0
	unsigned int           leaveBikeCount;//离开自行车数，如果单向计数，此字段值为0
	unsigned int           existCarCount;//留存车辆数，如果单向计数，此字段值为0
	unsigned int           existPersonCount;//留存人数，如果单向计数，此字段值为0
	int						existBikeCount;//留存自行车数，如果单向计数，此字段值为0
	unsigned int          count;         //分析结果个数
	NET_SDK_IVE_PASSLINECOUNT_INFO_T  passLineInfo[32];      // 绊线分析结果信息
}NET_SDK_IVE_PASSLINECOUNT_T;

typedef struct _searched_deviceInfo
{
	char			series[64];
	char			devName[64];
	char	        deviceType[16];
	char			szproductModel[16];
	char			szVersion[32];
	char			szFactoryName[16];
	char            szEthName[16];
	unsigned short	netport;
	unsigned short	nHttpPort;
	unsigned int			ipaddr;
	unsigned int			gateway;
	unsigned int			netmask;
	unsigned int			dns1;
	unsigned int			dns2;
	unsigned short  nChannelCount;  //NVR 通道数
	unsigned int	dwSecondIP;
	unsigned int	dwSecondMask;
}SEARCHED_DEVICE_INFO;

typedef struct _net_sdk_nvr_diskrec_date_item
{
	unsigned int    diskCount;
	unsigned int    diskIndex;
	char            szDiskSizeGB[16];
	char	        szStartDate[32];
	char	        szEndDate[32];
}NET_SDK_NVR_DISKREC_DATE_ITEM;

typedef enum
{
	_SEARCH_STANDARD	=0x001,
	_SEARCH_ONVIF		=0x002,
	_SEARCH_UPNP			=0x004,
	_SEARCH_AIPSTAR		=0x008,
	_SEARCH_DAHUA		=0x010,
	_SEARCH_HIK			=0x020,
	_SEARCH_UNIVIEW		=0x040,
	_SEARCH_YCX          =0x080,
	_SEARCH_SPECO		=0x100,
	_SEARCH_ALL          =0xffff//全部设备类型
}SEARCH_DEVICE_TYPE;
typedef enum
{ //日志级别
	YLOG_FATAL   = 0,    //严重错误
	YLOG_ERROR   = 1,    //错误
	YLOG_WARN    = 2,    //警告
	YLOG_INFO    = 3,    //信息
	YLOG_DEBUG   = 4,    //调试
	YLOG_BUFF    = 5,    //码流
}YLOG_LEVEL;
typedef struct _reg_login_info
{
	unsigned int deviceId;//注册设备id
	char m_szUserName[36];//注册设备用户名
	char m_szPasswd[36];//注册设备密码
}REG_LOGIN_INFO;
typedef struct _net_sdk_vehicle_pic_info
{
	unsigned int     vehicleId;
	char       plate[32];	        // 车牌号码
	unsigned long long     lTime;           //时间
}NET_SDK_VEHICLE_PIC_INFO;

typedef struct _net_sdk_user_group
{
	char szGroupGuid[48];
	char szGroupName[128];
}NET_SDK_USER_GROUP;

#pragma pack()

////////////////////////////////////////回调函数定义////////////////////////////////////////
typedef void (CALLBACK *EXCEPTION_CALLBACK)(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
typedef void (CALLBACK *DRAW_FUN_CALLBACK)(POINTERHANDLE lLiveHandle, HDC hDC, void *pUser);
typedef void (CALLBACK *LIVE_DATA_CALLBACK)(POINTERHANDLE lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser);
typedef void (CALLBACK *YUV_DATA_CALLBACK)(POINTERHANDLE lLiveHandle, DECODE_FRAME_INFO frameInfo, void *pUser);
typedef void (CALLBACK *LIVE_DATA_CALLBACK_EX)(POINTERHANDLE lLiveHandle, UINT dataType, BYTE *pBuffer, UINT dataLen, void *pUser);
typedef BOOL (CALLBACK *NET_MESSAGE_CALLBACK)(LONG lCommand, LONG lUserID, char *pBuf, DWORD dwBufLen, void *pUser);
typedef BOOL (CALLBACK *NET_MESSAGE_CALLBACK_EX)(LONG lCommand, LONG lUserID, char *pBuf, DWORD dwBufLen, void *pUser);
typedef void (CALLBACK *PLAY_DATA_CALLBACK)(POINTERHANDLE lPlayHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser);
typedef void (CALLBACK *PLAY_YUV_DATA_CALLBACK)(POINTERHANDLE lPlayHandle, DECODE_FRAME_INFO frameInfo, void *pUser);
typedef void (CALLBACK *TALK_DATA_CALLBACK)(POINTERHANDLE lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag, void *pUser);
typedef void (CALLBACK *ACCEPT_REGISTER_CALLBACK)(LONG lUserID, LONG lRegisterID, LPNET_SDK_DEVICEINFO pDeviceInfo, void *pUser);
typedef void (CALLBACK *ACCEPT_UNREGISTER_CALLBACK)(LONG lUserID, LONG lRegisterID, LPNET_SDK_DEVICEINFO pDeviceInfo, void *pUser);
typedef void (CALLBACK *BACKUP_DATA_CALLBACK)(POINTERHANDLE lFileHandle, UINT dataType, BYTE *pBuffer, UINT dataLen, void *pUser);

typedef void (CALLBACK *IPTool_SearchDataCallBack)(char* hwaddr, char *szDevIP, int opt, const char* szXmlData, void *pParam, const char *szRecvFromNIC);
typedef void (CALLBACK *IPTool_SearchDataCallBackEx)(char* hwaddr, char *szDevIP, int opt, const SEARCHED_DEVICE_INFO *pData, void *pParam, const char *szRecvFromNIC);

////////////////////////////////////////////////////////////////////////////////
/********************************SDK接口函数声明*********************************/
////////////////////////////////////////基本信息及登录设备////////////////////////////////////////
//SDK初始化及退出
NET_SDK_API BOOL CALL_METHOD NET_SDK_Init();
NET_SDK_API BOOL CALL_METHOD NET_SDK_Cleanup();
//设置重连参数
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetConnectTime(DWORD dwWaitTime = 5000, DWORD dwTryTimes = 3);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetReconnect(DWORD dwInterval = 5000, BOOL bEnableRecon = TRUE);
//局域网前端设备发现
NET_SDK_API int CALL_METHOD NET_SDK_DiscoverDevice(NET_SDK_DEVICE_DISCOVERY_INFO *pDeviceInfo, int bufNum, int waitSeconds = 3);
//SDK被动接收DVR注册 的本地端口号
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetRegisterPort(WORD wRegisterPort,REG_LOGIN_INFO* pLoginInfo = NULL, unsigned int deviceNum = 0);
NET_SDK_API BOOL CALL_METHOD NET_SDK_AddRegisterDeviceInfo(REG_LOGIN_INFO* pLoginInfo, unsigned int deviceNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetRegisterCallback(ACCEPT_REGISTER_CALLBACK fRegisterCBFun, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetUnRegisterCallback(ACCEPT_UNREGISTER_CALLBACK fUnRegisterCBFun, void *pUser);
//异常消息回调函数
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetSDKMessageCallBack(UINT nMessage, HWND hWnd, EXCEPTION_CALLBACK fExceptionCallBack, void *pUser);
//版本信息
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetSDKVersion();
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetSDKBuildVersion();
//错误查询
NET_SDK_API DWORD CALL_METHOD NET_SDK_GetLastError();

//登录登出设备
NET_SDK_API LONG CALL_METHOD NET_SDK_Login(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_SDK_DEVICEINFO lpDeviceInfo);
NET_SDK_API LONG CALL_METHOD NET_SDK_LoginEx(char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword,LPNET_SDK_DEVICEINFO lpDeviceInfo, NET_SDK_CONNECT_TYPE eConnectType, const char *sDevSN = NULL);
NET_SDK_API BOOL CALL_METHOD NET_SDK_Logout(LONG lUserID);

//设置p2p2.0的服务地址与端口
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetNat2Addr(char *sServerAddr,WORD wDVRPort);
////////////////////////////////////////设备报警信息////////////////////////////////////////
//设备报警或状态回调
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRMessageCallBack(NET_MESSAGE_CALLBACK fMessageCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRMessageCallBackEx(NET_MESSAGE_CALLBACK_EX fMessageCallBack, void *pUser);
NET_SDK_API LONG CALL_METHOD NET_SDK_SetupAlarmChan(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseAlarmChan(LONG lAlarmHandle);
//主动查询当前报警信息：N9000当前报警， IPC，3.0设备主动上报的报警
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAlarmStatus(LONG lUserID, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//DD_ALARM_STATUS_INFO_Ex*n+DD_ALARM_STATUS_INFO*m  [n,m >= 0]
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAlarmStatusEx(LONG lUserID, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, int *exStructNum);
//手动开启\关闭报警
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDeviceManualAlarm(LONG lUserID, LONG *pAramChannel, LONG *pValue, LONG lAramChannelCount, BOOL bAlarmOpen);


////////////////////////////////////////获取设备信息////////////////////////////////////////
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceInfo(LONG lUserID, LPNET_SDK_DEVICEINFO pdecviceInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceTime(LONG lUserID,DD_TIME *pTime);//获取设备当前时间
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceIPCInfo(LONG lUserID, NET_SDK_IPC_DEVICE_INFO* pDeviceIPCInfo, LONG lBuffSize, LONG* pIPCCount);//获取NVR的IPC通道信息
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceCHStatus(LONG lUserID, NET_SDK_CH_DEVICE_STATUS* pDeviceCHStatus, LONG lBuffSize, LONG* pCHCount);//获取NVR的通道状态

NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceCHSupportFunction(LONG lUserID, NET_SDK_CH_DEVICE_SUPPORT* pDeviceCHSupport, LONG lBuffSize, LONG* pCHCount);//获取ipc/NVR支持功能

////////////////////////////////////////预览相关接口////////////////////////////////////////
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_LivePlay(LONG lUserID, LPNET_SDK_CLIENTINFO lpClientInfo, LIVE_DATA_CALLBACK fLiveDataCallBack = NULL, void* pUser = NULL);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_LivePlayEx(LONG lUserID, LPNET_SDK_CLIENTINFO lpClientInfo, LIVE_DATA_CALLBACK_EX fLiveDataCallBack = NULL, void* pUser = NULL);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopLivePlay(POINTERHANDLE lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLiveDataCallBack(POINTERHANDLE lLiveHandle, LIVE_DATA_CALLBACK fLiveDataCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLiveDataCallBackEx(POINTERHANDLE lLiveHandle, LIVE_DATA_CALLBACK_EX fLiveDataCallBack, void *pUser);
//预览支持码流数
NET_SDK_API unsigned int CALL_METHOD NET_SDK_SupportStreamNum(LONG lUserID, LONG lChannel);

// 设置YUV回调后，可在回调处接收YUV数据，处理需尽快返回，否则会阻塞底层解码线程。（无需SDK显示时，调用NET_SDK_LivePlay时，窗口句柄传NULL即可）
// 注意：该功能目前仅在windows版本有效
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetYUVCallBack(POINTERHANDLE lLiveHandle, YUV_DATA_CALLBACK fYuvCallBack, void *pUser);

//动态生成I帧
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrame(LONG lUserID, LONG lChannel);//主码流
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrameSub(LONG lUserID, LONG lChannel);//子码流
NET_SDK_API BOOL CALL_METHOD NET_SDK_MakeKeyFrameEx(LONG lUserID, LONG lChannel, unsigned int streamType);//
//预览时解码效果的控制参数
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayerBufNumber(POINTERHANDLE lLiveHandle, DWORD dwBufNum);
//画面叠加字符和图像
NET_SDK_API BOOL CALL_METHOD NET_SDK_RegisterDrawFun(POINTERHANDLE lLiveHandle, DRAW_FUN_CALLBACK fDrawFun, void *pUser);
//监听
NET_SDK_API BOOL CALL_METHOD NET_SDK_OpenSound(POINTERHANDLE lLiveHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseSound();
NET_SDK_API BOOL CALL_METHOD NET_SDK_Volume(POINTERHANDLE lLiveHandle, WORD wVolume);
//保存本地录像
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveLiveData(POINTERHANDLE lLiveHandle, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopSaveLiveData(POINTERHANDLE lLiveHandle);
//预览显示参数配置
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVideoEffect_Ex(LONG lUserID, LONG lChannel, NET_SDK_IMAGE_EFFECT_T *pBrightValue, NET_SDK_IMAGE_EFFECT_T *pContrastValue, NET_SDK_IMAGE_EFFECT_T *pSaturationValue, NET_SDK_IMAGE_EFFECT_T *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVideoEffect_Ex(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);


////////////////////////////////////////视频抓图
//JPEG抓图到内存
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGData_V2(LONG lUserID, LONG lChannel, char *sJpegPicBuffer, DWORD dwPicSize, LPDWORD lpSizeReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGFile_V2(LONG lUserID, LONG lChannel, char *sPicFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJPEGPicture(LONG lUserID, LONG lChannel, LPNET_SDK_JPEGPARA lpJpegPara, char *sJpegPicBuffer, DWORD dwPicSize, LPDWORD lpSizeReturned);
//设备上的图片，N9000支持
NET_SDK_API BOOL CALL_METHOD NET_SDK_SearchPictures(LONG lUserID, NET_SDK_IMAGE_SREACH sInSreachImage, LONG lInImageBufferSize, NET_SDK_IMAGE *pOutImageInfo, LONG *pOutImageNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_RemoteSnap(LONG lUserID, int lChannel);//远程抓图
NET_SDK_API BOOL CALL_METHOD NET_SDK_DownLoadPicture(LONG lUserID, NET_SDK_IMAGE captureImage, NET_SDK_IMAGE_INFO *pOutImageInfo, char* pOutBuffer, int outBufferSize);


////////////////////////////////////////设备录像文件回放、下载和锁定////////////////////////////////////////
//根据文件时间查找录像文件
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindFile(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextFile(POINTERHANDLE lFindHandle, NET_SDK_REC_FILE *lpFindData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindClose(POINTERHANDLE lFindHandle);
//根据日期查找录像文件
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindRecDate(LONG lUserID);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextRecDate(POINTERHANDLE lFindHandle, DD_DATE *lpRecDate);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindRecDateClose(POINTERHANDLE lFindHandle);
//根据事件查找录像文件
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindEvent(LONG lUserID, LONG lChannel, DWORD dwRecType, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextEvent(POINTERHANDLE lFindHandle, NET_SDK_REC_EVENT *lpRecEvent);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindEventClose(POINTERHANDLE lFindHandle);
//根据时间查找录像文件
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindTime(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextTime(POINTERHANDLE lFindHandle, NET_SDK_REC_TIME *lpRecTime);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindTimeClose(POINTERHANDLE lFindHandle);
//按时间回放录像文件
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_PlayBackByTime(LONG lUserID, LONG *pChannels, LONG channelNum, DD_TIME *lpStartTime, DD_TIME *lpStopTime, HWND *hWnds);//main stream
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_PlayBackByTimeEx(LONG lUserID, LONG *pChannels, LONG channelNum, DD_TIME *lpStartTime, DD_TIME *lpStopTime, HWND *hWnds, BOOL bFirstStream);
NET_SDK_API int CALL_METHOD NET_SDK_PlayBackByTimeSync(LONG lUserID, LONG *pChannels, LONG channelNum, DD_TIME *lpStartTime, DD_TIME *lpStopTime, HWND *hWnds, BOOL bFirstStream);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackControl(POINTERHANDLE lPlayHandle, DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackControlSync(DWORD dwControlCode, DWORD dwInValue, DWORD *lpOutValue);

NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBack(POINTERHANDLE lPlayHandle);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBackSync();
//注册回调函数，捕获录像数据
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayDataCallBack(POINTERHANDLE lPlayHandle, PLAY_DATA_CALLBACK fPlayDataCallBack, void *pUser);

// 设置YUV回调后，可在回调处接收YUV数据，处理需尽快返回，否则会阻塞底层解码线程。（无需SDK显示时，调用NET_SDK_PlayBackByTime时，窗口句柄传NULL即可）
// 注意：该功能目前仅在windows版本有效
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetPlayYUVCallBack(POINTERHANDLE lPlayHandle, PLAY_YUV_DATA_CALLBACK fYuvCallBack, void *pUser);

//捕获回放的录像数据，并保存成文件
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackSaveData(POINTERHANDLE lPlayHandle, LONG lChannel, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopPlayBackSave(POINTERHANDLE lPlayHandle, LONG lChannel);
//回放的其它操作
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPlayBackOsdTime(POINTERHANDLE lPlayHandle, DD_TIME *lpOsdTime);//获取录像回放时显示的OSD时间
NET_SDK_API BOOL CALL_METHOD NET_SDK_PlayBackCaptureFile(POINTERHANDLE lPlayHandle, LONG lChannel, char *sFileName);//录像回放时抓图，并保存在文件中
NET_SDK_API BOOL CALL_METHOD NET_SDK_RefreshPlay(POINTERHANDLE lPlayHandle);//刷新显示回放窗口
//下载录像文件
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_GetFileByTime(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime, char *sSavedFileName);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_GetFileByTimeEx(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime, char *sSavedFileName, BOOL bCustomFormat, BOOL bUseCallBack=false, BACKUP_DATA_CALLBACK fBackupDataCallBack= NULL, void* pUser = NULL); //bCustomFormat：是否使用私有文件格式
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_GetFileByTimeExV2(LONG lUserID,LONG lChannel, DD_TIME * lpStartTime, DD_TIME * lpStopTime, char *sSavedFileName, char recFormat, BOOL bFirstStream, BOOL bUseCallBack=false, BACKUP_DATA_CALLBACK fBackupDataCallBack= NULL, void* pUser = NULL); //bCustomFormat：是否使用私有文件格式

NET_SDK_API BOOL CALL_METHOD NET_SDK_StopGetFile(POINTERHANDLE lFileHandle);
NET_SDK_API int CALL_METHOD NET_SDK_GetDownloadPos(POINTERHANDLE lFileHandle);
//录像文件锁定、解锁、删除
NET_SDK_API BOOL CALL_METHOD NET_SDK_LockFile(LONG lUserID, NET_SDK_REC_FILE *pFileToLock, LONG fileNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_UnlockFile(LONG lUserID, NET_SDK_REC_FILE *pFileToUnlock, LONG fileNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_DeleteRecFile(LONG lUserID, NET_SDK_REC_FILE *pFileToUnlock, LONG fileNum);
//远程控制设备端手动录像
NET_SDK_API BOOL CALL_METHOD NET_SDK_StartDVRRecord(LONG lUserID, LONG lChannel, LONG lRecordType);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopDVRRecord(LONG lUserID, LONG lChannel);


////////////////////////////////////////云台控制相关接口////////////////////////////////////////
//云台控制
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl(POINTERHANDLE lLiveHandle, DWORD dwPTZCommand, DWORD dwSpeed);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCommand, DWORD dwSpeed);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_3D(POINTERHANDLE lLiveHandle, LONG lChannel, PTZ_3D_POINT_INFO *pPtz3DInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZControl_3D_Ex(LONG lUserID, LONG lChannel, PTZ_3D_POINT_INFO *pPtz3DInfo);//不预览3D控制，仅支持球机云台
//预置点
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZPreset(POINTERHANDLE lLiveHandle, DWORD dwPTZPresetCmd, DWORD dwPresetIndex);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZPreset_Other(LONG lUserID, LONG lChannel, DWORD dwPTZPresetCmd, DWORD dwPresetIndex);
//巡航线
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZCruise(POINTERHANDLE lLiveHandle, DWORD dwPTZCruiseCmd, BYTE byCruiseRoute);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZCruise_Other(LONG lUserID, LONG lChannel, DWORD dwPTZCruiseCmd, BYTE byCruiseRoute);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZSetCruise(POINTERHANDLE lLiveHandle, BYTE byCruiseRoute, DD_CRUISE_POINT_INFO *pCruisePoint, WORD pointNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZSetCruise_Other(LONG lUserID, LONG lChannel, BYTE byCruiseRoute, DD_CRUISE_POINT_INFO *pCruisePoint, WORD pointNum);
//轨迹
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZTrack(POINTERHANDLE lLiveHandle, DWORD dwPTZTrackCmd);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZTrack_Other(LONG lUserID, LONG lChannel, DWORD dwPTZTrackCmd);
//自动扫描和随机扫描都这个接口,bIsAutoScan = true,自动扫描。
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZAutoScan(POINTERHANDLE lLiveHandle, DWORD dwPTZAutoScanCmd, DWORD dwSpeed, BOOL bIsAutoScan = TRUE);
NET_SDK_API BOOL CALL_METHOD NET_SDK_PTZAutoScan_Other(LONG lUserID, LONG lChannel, DWORD dwPTZAutoScanCmd);
//获取云台信息：获取预置点和巡航线get Preset or Cruise
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPTZConfig(LONG lUserID, LONG lChannel, DWORD dwPTZCmd,LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//获取通道支持PTZ的列表
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetSupportPtzList(LONG lUserID, int listNum, NET_SDK_CHANNEL_PTZ* pOutChannelPtz, int *returnListNum);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetPTZCameraType(LONG lUserID, NET_SDK_CAMERA_TYPE *pCameraType);


////////////////////////////////////////语音对讲和转发////////////////////////////////////////
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_StartVoiceCom(LONG lUserID, BOOL bNeedCBNoEncData, TALK_DATA_CALLBACK fVoiceDataCallBack, void* pUser, LONG lChannel = -1);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetAudioInfo(POINTERHANDLE lVoiceComHandle, void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVoiceComClientVolume(POINTERHANDLE lVoiceComHandle, WORD wVolume);
NET_SDK_API BOOL CALL_METHOD NET_SDK_StopVoiceCom(POINTERHANDLE lVoiceComHandle);
//语音转发
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_StartVoiceCom_MR(LONG lUserID, BOOL bNeedNoEncodeData, TALK_DATA_CALLBACK fVoiceDataCallBack, void* pUser, LONG lChannel = -1);
NET_SDK_API BOOL CALL_METHOD NET_SDK_VoiceComSendData(POINTERHANDLE lVoiceComHandle, char *pSendBuf, DWORD dwBufSize);
//音频解码
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_InitAudioDecoder(void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_DecodeAudioFrame(POINTERHANDLE lDecHandle, unsigned char *pInBuffer, LONG inLen, unsigned char *pOutBuffer, int *pOutLen);
NET_SDK_API void CALL_METHOD NET_SDK_ReleaseAudioDecoder(POINTERHANDLE lDecHandle);
//音频编码
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_InitAudioEncoder(void *pAudioInfo, LONG infoLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_EncodeAudioFrame(POINTERHANDLE lEncodeHandle, unsigned char *pInBuffer, LONG inLen, unsigned char *pOutBuffer, int *pOutLen);
NET_SDK_API void CALL_METHOD NET_SDK_ReleaseAudioEncoder(POINTERHANDLE lEncodeHandle);


////////////////////////////////////////设备维护管理////////////////////////////////////////
//升级
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_Upgrade(LONG lUserID, char *sFileName);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_UpgradeEx(LONG lUserID, char *sFileName);
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_UpgradeIPC(LONG lUserID, char *sFileName, unsigned int fileType);
NET_SDK_API int CALL_METHOD NET_SDK_GetUpgradeState(POINTERHANDLE lUpgradeHandle);
NET_SDK_API int CALL_METHOD NET_SDK_GetUpgradeProgress(POINTERHANDLE lUpgradeHandle, int *pError = NULL);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseUpgradeHandle(POINTERHANDLE lUpgradeHandle);
//日志查找
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindDVRLog(LONG lUserID, DWORD dwType, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextLog(POINTERHANDLE lLogHandle, LPNET_SDK_LOG lpLogData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindLogClose(POINTERHANDLE lLogHandle);
//事件搜索
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindEventInfo(LONG lUserID, DWORD dwType, ULONGLONG channlMask, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextEventInfo(POINTERHANDLE lEventHandle, LPNET_SDK_EVENT lpEventData);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindEventInfoClose(POINTERHANDLE lEventHandle);
//恢复默认值
NET_SDK_API BOOL CALL_METHOD NET_SDK_RestoreConfig(LONG lUserID);
//配置文件导出导入
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetConfigFile(LONG lUserID, char *sFileName);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetConfigFile(LONG lUserID, char *sFileName);
//关机和重启
NET_SDK_API BOOL CALL_METHOD NET_SDK_ShutDownDVR(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_RebootDVR(LONG lUserID);
//远程查询硬盘
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindDisk(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetNextDiskInfo(POINTERHANDLE lDiskHandle, NET_SDK_DISK_INFO *pDiskInfo);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FindDiskClose(POINTERHANDLE lDiskHandle);
//格式化硬盘
NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FormatDisk(LONG lUserID, LONG lDiskNumber);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetFormatProgress(POINTERHANDLE lFormatHandle, LONG *pCurrentFormatDisk, LONG *pCurrentDiskPos, LONG *pFormatStatic);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CloseFormatHandle(POINTERHANDLE lFormatHandle);


////////////////////////////////////////设备参数配置////////////////////////////////////////
NET_SDK_API LONG CALL_METHOD NET_SDK_EnterDVRConfig(LONG lUserID);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);
NET_SDK_API BOOL CALL_METHOD NET_SDK_ExitDVRConfig(LONG lUserID);

NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig_SubStreamEncodeInfo(LONG lUserID, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);	//For N9000
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetDVRConfig_SubStreamEncodeInfo(LONG lUserID, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);													//For N9000
//相对NET_SDK_GetDVRConfig_SubStreamEncodeInfo，返回结构体中多了支持的码率选项; 返回的是支持的编码信息
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDVRConfig_SubStreamEncodeInfo_Ex(LONG lUserID, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, BOOL bDefautlConfig);	//For N9000
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveConfig(LONG lUserID);//保存参数
NET_SDK_API BOOL CALL_METHOD NET_SDK_ChangTime(LONG lUserID, unsigned int time);//修改设备系统时间
//NET_SDK_API BOOL CALL_METHOD NET_SDK_ModifyDeviceNetInfo(NET_SDK_DEVICE_IP_INFO *pDeviceIPInfo);//修改设备IP
NET_SDK_API void CALL_METHOD NET_SDK_FormatTime(LONGLONG intTime, DD_TIME *pFormatTime);//整型时间转换为格式化的时间

//NVR可用，IPC无效
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetUserGroups(LONG lUserID, NET_SDK_USER_GROUP *pUserGroup, DWORD &groupNum);
//groupGuid和groupName通过NET_SDK_GetUserGroups获取，NVR可用，IPC无效
NET_SDK_API BOOL CALL_METHOD NET_SDK_ManageUser(LONG lUserID, DD_OPERATE_TYPE dwCommand, char *userName, char *groupGuid, char *groupName, char *password, char* email, BOOL allowModifyPwd, char *newName=NULL, BOOL closePermissionCtrl=FALSE);
NET_SDK_API BOOL CALL_METHOD NET_SDK_UserManage(LONG lUserID, DD_OPERATE_TYPE dwCommand, char *userName, DD_USER_GROUP userType, char *password, char* email, BOOL allowModifyPwd, char *newName=NULL, BOOL closePermissionCtrl=FALSE);

////////////////////////////////////////智能报警（只针对智能IPC）////////////////////////////////////////
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetIVMRuleConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetIVMRuleConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer,  DWORD dwInBufferSize);
//dwCommand NET_DVR_SMART_TYPE
//NET_DVR_IVE_VFD_RESULT_HEAD_T+[NET_DVR_IVE_VFD_RESULT_DATA_INFO_T+源数据]+[NET_DVR_IVE_VFD_RESULT_FACE_DATA_INFO_T+人脸数据+人脸目标值]+...+[NET_DVR_IVE_VFD_RESULT_FACE_DATA_INFO_T+人脸数据+人脸目标值]
typedef void (CALLBACK *SUBSCRIBE_CALLBACK)(LONG lUserID, DWORD dwCommand, char *pBuf, DWORD dwBufLen, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetSubscribCallBack(SUBSCRIBE_CALLBACK fSubscribCallBack, void *pUser);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SmartSubscrib(LONG lUserID, DWORD dwCommand, LONG lChannel, NET_DVR_SUBSCRIBE_REPLY *pOutBuffer);
NET_SDK_API BOOL CALL_METHOD NET_SDK_UnSmartSubscrib(LONG lUserID, DWORD dwCommand, LONG lChannel, char *pInServerAddress, int *dwResult);
NET_SDK_API BOOL CALL_METHOD NET_SDK_EnableShowVFD(BOOL bEnable);

//FaceMatch NET_SDK_FACE_MATCH_OPERATE_TYPE
NET_SDK_API BOOL CALL_METHOD NET_SDK_FaceMatchOperate(LONG lUserID, DWORD dwCommand,LPVOID lpInBuffer, DWORD dwInBufferSize,LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//透传API接口函数，实现与设备端直接xml互通
NET_SDK_API BOOL CALL_METHOD NET_SDK_ApiInterface(LONG lUserID, char *sendXML, char *strUrl, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);
//透传接口函数，
NET_SDK_API BOOL CALL_METHOD NET_SDK_TransparentConfig(LONG lUserID, char *sendXML, char *strUrl, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);

NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveFileToUsbByTime(LONG lUserID,NET_SDK_REC_FILE* recordFile, USB_BACKUP_FORMAT recFormat);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetSaveFileToUsbProcess(LONG lUserID, NET_SDK_USB_BACKUP_PROCESS_EX* pUsbBackProcess, unsigned int lBuffSize, unsigned int* taskCount);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceSupportFunction(LONG lUserID, NET_SDK_DEV_SUPPORT* pDevSupport);//获取ipc支持功能
#ifdef WIN32
#ifdef DVR_NET_SDK_EXPORTS
//开始搜索设备 SearchTypeMask please refer to SEARCH_DEVICE_TYPE
NET_SDK_API unsigned int CALL_METHOD NET_SDK_DiscoverDeviceStart(IPTool_SearchDataCallBack SearchCallBack,IPTool_SearchDataCallBackEx SearchCallBackEx, void *pParam, unsigned int SearchTypeMask, int nMaxRecordCount);
//停止搜索设备
NET_SDK_API void CALL_METHOD NET_SDK_DiscoverDeviceStop(unsigned int hSearch);
#endif
#endif // WIN32

NET_SDK_API int CALL_METHOD NET_SDK_GetSha1Encrypt(LONG lUserID,const void *pIn, int iLenIn, void *szOut, int outLen, int *lpBytesReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetRtspUrl(LONG lUserID,LONG lChannel,LONG lStreamType,char *sRtspUrl);
//根据文件时间查找录像文件
//NET_SDK_API POINTERHANDLE CALL_METHOD NET_SDK_FindVehiclePic(LONG lUserID, LONG lChannel, DD_TIME *lpStartTime, DD_TIME *lpStopTime);
//NET_SDK_API LONG CALL_METHOD NET_SDK_FindNextVehiclePic(POINTERHANDLE lFindHandle, NET_SDK_VEHICLE_PIC_INFO *lpFindData);
//NET_SDK_API BOOL CALL_METHOD NET_SDK_FindVehiclePicClose(POINTERHANDLE lFindHandle);

////////////////////The following interfaces will stop updating, they are not recommended.
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceFirmwareType(LONG lUserID, NET_SDK_DEVICE_FIRMWARE_TYPE *pFirmwareType);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDeviceIPByName(char *sSerIP,DWORD wSerPort,char *sDvrName,char *sDvrIP);//通过设备名称获取IP地址
NET_SDK_API LONG CALL_METHOD NET_SDK_GetProductSubID(char *sDVRIP,WORD wDVRPort);
NET_SDK_API char* CALL_METHOD NET_SDK_GetErrorMsg(LONG *pErrorNo = NULL);
NET_SDK_API LONG CALL_METHOD NET_SDK_GetDeviceTypeName(LONG lUserID, char *pNameBuffer, int bufferLen);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetLogToFile(BOOL bLogEnable = FALSE, char *strLogDir = NULL, BOOL bAutoDel = TRUE,int logLevel = YLOG_DEBUG);//启用日志文件写入接口
NET_SDK_API BOOL CALL_METHOD NET_SDK_ChangeDiskProperty(LONG lUserID, LONG lDiskNumber, short newProperty);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVideoEffect(LONG lUserID, LONG lChannel, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetVideoEffect(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetDefaultVideoEffect(LONG lUserID, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_SaveVideoEffect(LONG lUserID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwHueValue);
NET_SDK_API BOOL CALL_METHOD NET_SDK_CapturePicture(POINTERHANDLE lLiveHandle, char *sPicFileName);//bmp
NET_SDK_API BOOL CALL_METHOD NET_SDK_CapturePicture_Other(LONG lUserID, LONG lChannel,char *sPicFileName);//bmp
NET_SDK_API BOOL CALL_METHOD NET_SDK_CaptureJpeg(LONG lUserID, LONG lChannel, LONG dwResolution, char *sJpegPicBuffer, DWORD dwPicBufSize, LPDWORD lpSizeReturned);
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetVehicleConfig(LONG lUserID);

#ifdef WIN32
//设置鱼眼校正模式，进入鱼眼校正模式与退出鱼眼校正模式都需要调用此接口,仅单窗口模式使用
//输入参数：
//lPlayHandle： 播放句柄
//fishEyeMode：安装模式+校正模式
NET_SDK_API BOOL CALL_METHOD NET_SDK_SetFishEyeAdjust(POINTERHANDLE lPlayHandle, FISHEYE_MODE fishEyeMode);

//设置焦点，用于判断当前操作作用于鱼眼校正的哪个分割区域
//输入参数：
//lPlayHandle： 播放句柄
//nX：当前焦点的X坐标值，相对于当前播放窗口坐标系
//nY：当前焦点的Y坐标值，相对于当前播放窗口坐标系
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustFocus(POINTERHANDLE lPlayHandle, int nX, int nY);
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustFocusEx(POINTERHANDLE lPlayHandle, int nX, int nY, int &nIndex);
//电子云台移动，只有进入鱼眼校正模式下，属于电子云台的分割才可以移动
//输入参数：
//lPlayHandle： 播放句柄
//nMoveX：鼠标左键拖拽时相对于起点之X坐标轴上的水平偏移量，向右为正，向左为负，以起点为原点
//nMoveY：鼠标左键拖拽时相对于起点之Y坐标轴上的垂直偏移量，向上为正，向下为负，以起点为原点
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustMove(POINTERHANDLE lPlayHandle, int nMoveX, int nMoveY);

//获取当前焦点所在的校正区域位置
//输入参数：
//lPlayHandle： 播放句柄
//输出参数
//AreaRect：当前焦点所在校正区域的位置，相对于当前播放窗口坐标系
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustGetArea(POINTERHANDLE lPlayHandle, RECT &AreaRect);

//电子云台放大，只有进入鱼眼校正模式下，属于电子云台的分割才可以放大
//输入参数：
//lPlayHandle： 播放句柄
//ZoomRect： 指定要放大的区域位置信息，相对于当前播放窗口坐标系
NET_SDK_API BOOL CALL_METHOD NET_SDK_FishEyeAdjustZoom(POINTERHANDLE lPlayHandle, const RECT &ZoomRect);
#endif

//查询NVR的录像天数接口
//输入参数:
//lUserID 设备ID
NET_SDK_API BOOL CALL_METHOD NET_SDK_GetNvrRecordDays(LONG lUserID, NET_SDK_NVR_DISKREC_DATE_ITEM* pDiskRecDateInfo, LONG lBuffSize, LONG* pDISKCount);

//激活设备
NET_SDK_API BOOL CALL_METHOD NET_SDK_ActiveDevice(char * pIp,int iPort,char *password);
NET_SDK_API BOOL CALL_METHOD NET_SDK_ActiveDeviceByMac(char * pMac,char *password);

//预览画线
NET_SDK_API BOOL CALL_METHOD NET_SDK_ShowRect(POINTERHANDLE lPlayHandle,int x1,int x2,int y1,int y2 );
NET_SDK_API BOOL CALL_METHOD NET_SDK_ShowRectList(POINTERHANDLE lPlayHandle, const unsigned char* pVFDRectData, int nBufLen);
#ifdef __cplusplus
}
#endif

#endif
