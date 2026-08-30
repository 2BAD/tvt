/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       : YSW
** Date         : 2010-11-19
** Name         : dvrdvstypedef.h
** Version      : 1.0
** Description  :	描述DVR/DVS相关的一些基本特性
** Modify Record:
1:创建
***********************************************************************/
#ifndef __DVR_DVS_TYPEDEF_H__
#define __DVR_DVS_TYPEDEF_H__

#ifdef WIN32 ////////////////////如果是Windows平台
#include "stdafx.h"
typedef DWORD				THREAD_ID;
typedef long                POINTERHANDLE;

//定义PACKED 主要用于解决在Windows解决对奇一般使用#pragma pack(n)而Linux下一般使用__attribute__((packed))
//在此结构体要写入文件或者在跨平台之间访问时才需要以下定义，注意__attribute__((packed))只用于单字节对齐
#define PACKED
#else ////////////////////linux平台
#include <sys/types.h>
#include <stddef.h>

#define PACKED __attribute__((packed))

typedef pid_t				THREAD_ID;
typedef unsigned int       DWORD, *LPDWORD;
typedef unsigned int       ULONG;
//大概检查了内部LONG的使用，发现很多地方将指针直接转给LONG,且某些地方LONG值可能为负值，最稳妥的定义成long long
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef int                LONG;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               LONG;
    #else
        typedef long                LONG;
    #endif
#endif

//手机端handle用的long long，win，linux端用的LONG。现为了统一一套代码且不影响客户，定义POINTERHANDLE来兼容
#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef long long                POINTERHANDLE;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               POINTERHANDLE;
    #else
        typedef long                POINTERHANDLE;
    #endif
#endif


typedef unsigned long long  ULONGLONG;


//zld 2016/10/22
#ifdef __ENVIRONMENT_IOS__

#if (TARGET_OS_IPHONE && __LP64__)  ||  TARGET_OS_WATCH
#define OBJC_BOOL_IS_BOOL 1
typedef bool BOOL;
#else
#define OBJC_BOOL_IS_CHAR 1
typedef signed char BOOL;  //wyf
//typedef bool BOOL;
#endif

#else
typedef bool                BOOL;
#endif

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef int                 INT;
typedef unsigned int        UINT;
typedef long long           LONGLONG;
typedef void				*HWND, *HDC, *LPVOID;

#define CALLBACK
#define FALSE				false
#define TRUE				true
//#define NULL				0
#endif //WIN32

//视频制式定义
typedef enum _dd_video_format_
{
	DD_VIDEO_FORMAT_NTSC	= 0x01,
	DD_VIDEO_FORMAT_PAL		= 0x02
}DD_VIDEO_FORMAT;

typedef enum _dd_frame_type_
{
	DD_FRAME_TYPE_NONE				= 0x00,//空类型数据帧
	DD_FRAME_TYPE_VIDEO				= 0x01,//视频数据帧
	DD_FRAME_TYPE_AUDIO				= 0x02,//音频数据帧
	DD_FRAME_TYPE_TALK_AUDIO		= 0x03,//对讲音频数据帧
	DD_FRAME_TYPE_JPEG				= 0x04,//JPEG图片流数据帧

	DD_FRAME_TYPE_VIDEO_FORMAT		= 0x05,//视频格式帧
	DD_FRAME_TYPE_AUDIO_FORMAT		= 0x06,//音频格式帧
	DD_FRAME_TYPE_TALK_AUDIO_FORMAT	= 0x07,//对讲音频格式帧

	DD_FRAME_TYPE_RESV1				= 0x08,
	DD_FRAME_TYPE_RESV2				= 0x09,

	DD_FRAME_TYPE_END				= 0x0a,
}DD_FRAME_TYPE;

typedef enum _dd_frame_attrib_
{
	DD_PLAY_FRAME_NO_SHOW			= 0x01,		//此帧不显示
	DD_PLAY_FRAME_SHOW				= 0x02,		//此帧可显示
	DD_PLAY_FRAME_ALL_END			= 0x04,		//数据读取结束了，后面再没有数据
	DD_PLAY_FRAME_SEC_END			= 0x08,		//此事件段结束了
	DD_PLAY_FRAME_NO_TIME_STAMP		= 0x10,		//此帧数据有时间戳，抓图的时候注意要屏蔽打时间的功能
	DD_PLAY_FRAME_FF				= 0x20,		//当前帧用于快进

	DD_LIVE_FRAME_FIRST_STREAM		= 0x40,		//此帧为现场主码流
	DD_LIVE_FRAME_SECOND_STREAM		= 0x80,		//此帧为现场子码流
	DD_LIVE_FRAME_JPEG				= 0x100,	//此帧为JPEG图片
	DD_LIVE_FRAME_TALK				= 0x200,		//此帧为对讲语音数据
    DD_LIVE_FRAME_THIRD_STREAM		= 0x400,		//此帧为现场第三码流
    DD_LIVE_FRAME_FOURTH_STREAM		= 0x800,		//此帧为现场第四码流
}DD_FRAME_ATTRIB;

//按位保存。最多不能超过32个
typedef enum _dd_video_size_
{
	DD_VIDEO_SIZE_QCIF	= 0x0001,	//QCIF
	DD_VIDEO_SIZE_CIF	= 0x0002,	//CIF
	DD_VIDEO_SIZE_HD1	= 0x0004,	//HD1
	DD_VIDEO_SIZE_D1	= 0x0008,	//D1

	DD_VIDEO_SIZE_QVGA	= 0x0010,	//QVGA
	DD_VIDEO_SIZE_VGA	= 0x0020,	//VGA
	DD_VIDEO_SIZE_XVGA	= 0x0040,	//XVGA
	DD_VIDEO_SIZE_QQVGA	= 0x0080,	//QQVGA

	DD_VIDEO_SIZE_480P	= 0x0100,	//480P
	DD_VIDEO_SIZE_720P	= 0x0200,	//720P
	DD_VIDEO_SIZE_1080P	= 0x0400,	//1080P
	DD_VIDEO_SIZE_960H  = 0x0800,   //960H

	DD_VIDEO_SIZE_960P   = 0x01000,	//(1280 X 960)
	DD_VIDEO_SIZE_SXGA   = 0x02000,	//(1280 X 1024)
	DD_VIDEO_SIZE_3M     = 0x04000,	//(2048 X 1536)

	DD_VIDEO_SIZE_16_9_3M     = 0x10000,	//(2304 X 1296)
	DD_VIDEO_SIZE_2K          = 0x20000,	//(2560 X 1440)
	DD_VIDEO_SIZE_HDLITE      = 0x40000,	//(960 X 1080)
}DD_VIDEO_SIZE;

//按位保存，最多只能为32个。
typedef enum _dd_video_encode_mode_
{
	DD_VIDEO_ENCODE_MODE_VBR	=	0x01,	//变码流
	DD_VIDEO_ENCODE_MODE_CBR	=	0x02	//固定码流
}DD_VIDEO_ENCODE_MODE;

typedef enum _dd_video_encode_format_
{
    DD_VIDEO_ENCODE_FORMAT_H264	=	0x0,
    DD_VIDEO_ENCODE_FORMAT_H265	=	0x01,
    DD_VIDEO_ENCODE_FORMAT_MJPEG=	0x02,
    DD_VIDEO_ENCODE_FORMAT_H264PLUS=	0x03,
    DD_VIDEO_ENCODE_FORMAT_H265PLUS=	0x04,
}DD_VIDEO_ENCODE_FORMAT;

typedef enum _dd_image_quality_
{
	DD_IMAGE_QUALITY_LOWEST		= 0x01,
	DD_IMAGE_QUALITY_LOWER		= 0x02,
	DD_IMAGE_QUALITY_LOW		= 0x03,
	DD_IMAGE_QUALITY_MEDIUM		= 0x04,
	DD_IMAGE_QUALITY_HEIGHTER	= 0x05,
	DD_IMAGE_QUALITY_HEIGHTEST	= 0x06
}DD_IMAGE_QUALITY;

//VGA分辨率，既可以用于保存也可以用于支持功能参数,'
//注意：要按位表示
typedef enum _dd_vga_resolution_
{
	DD_VGA_640X480		= 0x0001,
	DD_VGA_720X480		= 0x0002,
	DD_VGA_720X576		= 0x0004,
	DD_VGA_800X600		= 0x0008,
	DD_VGA_1024X768		= 0x0010,
	DD_VGA_1280X960		= 0x0020,
	DD_VGA_1280X1024	= 0x0040,
	DD_VGA_1920X1080	= 0x0080,
	DD_VGA_320X240		= 0x0100,
	DD_VGA_352X240		= 0x0200,
	DD_VGA_480X240		= 0x0400,
	DD_VGA_704X480		= 0x0800,
	DD_VGA_704X576		= 0x1000,
	DD_VGA_960X480		= 0x2000,
	DD_VGA_960X576		= 0x4000,
	DD_VGA_960X1080		= 0x8000,
	DD_VGA_1280X720		= 0x00010000,
	DD_VGA_1600X1200	= 0x00020000,
	DD_VGA_1920X1536	= 0x00040000,
	DD_VGA_2048X1536	= 0x00080000,
	DD_VGA_2304X1296	= 0x00100000,
	DD_VGA_2560X1440	= 0x00200000,
	DD_VGA_2592X1520	= 0x00400000,
	DD_VGA_2592X1944	= 0x00800000,
	DD_VGA_3840X2160	= 0x01000000,
}DD_VGA_RESOLUTION;

//显示年月日的模式
typedef enum _dd_date_mode_
{
	DD_DATE_MODE_YMD	= 0x01,		//年月日模式
	DD_DATE_MODE_MDY	= 0x02,		//月日年模式
	DD_DATE_MODE_DMY	= 0x03		//日月年模式
}DD_DATE_MODE;

typedef enum _dd_time_zone_name_
{
	DD_TIME_ZONE_GMT_D12	= 0,
	DD_TIME_ZONE_GMT_D11,
	DD_TIME_ZONE_GMT_D10,
	DD_TIME_ZONE_GMT_D9,
	DD_TIME_ZONE_GMT_D8,
	DD_TIME_ZONE_GMT_D7,
	DD_TIME_ZONE_GMT_D6,
	DD_TIME_ZONE_GMT_D5,
	DD_TIME_ZONE_GMT_D4_30,
	DD_TIME_ZONE_GMT_D4,
	DD_TIME_ZONE_GMT_D3_30,
	DD_TIME_ZONE_GMT_D3,
	DD_TIME_ZONE_GMT_D2,
	DD_TIME_ZONE_GMT_D1,
	DD_TIME_ZONE_GMT,
	DD_TIME_ZONE_GMT_A1,
	DD_TIME_ZONE_GMT_A2,
	DD_TIME_ZONE_GMT_A3,
	DD_TIME_ZONE_GMT_A3_30,
	DD_TIME_ZONE_GMT_A4,
	DD_TIME_ZONE_GMT_A4_30,
	DD_TIME_ZONE_GMT_A5,
	DD_TIME_ZONE_GMT_A5_30,
	DD_TIME_ZONE_GMT_A5_45,
	DD_TIME_ZONE_GMT_A6,
	DD_TIME_ZONE_GMT_A6_30,
	DD_TIME_ZONE_GMT_A7,
	DD_TIME_ZONE_GMT_A8,
	DD_TIME_ZONE_GMT_A9,
	DD_TIME_ZONE_GMT_A9_30,
	DD_TIME_ZONE_GMT_A10,
	DD_TIME_ZONE_GMT_A11,
	DD_TIME_ZONE_GMT_A12,
	DD_TIME_ZONE_GMT_A13,
	DD_TIME_ZONE_NUM,
}DD_TIME_ZOME_NAME;

//三级用户权限，每级用户具有默认权限，但是可以向下调节具体权限（不能向上调节）。
typedef enum _dd_user_group_
{
	DD_USER_GROUP_NONE		= 0x00,	//
	DD_USER_GROUP_ADMIN		= 0x01,	//管理员，拥有所有的权限
	DD_USER_GROUP_ADVANCE	= 0x02,	//高级用户，默认具有：基本、录像、配置、回放、备份、数据管理、磁盘管理，云台控制，远程登录，及全通道权限
	DD_USER_GROUP_NORMAL	= 0x04	//一般用户，默认具有：基本、录像、回放、备份、云台控制、远程登录，及全通道权限
}DD_USER_GROUP;

typedef enum _dd_operate_type_
{
	DD_OPERATE_ADD = 0x01,
	DD_OPERATE_EDIT = 0x02,
	DD_OPERATE_DELETE = 0x03,
}DD_OPERATE_TYPE;

typedef enum _dd_record_type_
{
	DD_RECORD_TYPE_NONE		= 0x0000,			//无录像类型

	DD_RECORD_TYPE_MANUAL	= 0x0001,			//手动录像
	DD_RECORD_TYPE_SCHEDULE	= 0x0002,			//定时录像
	DD_RECORD_TYPE_MOTION	= 0x0004,			//移动侦测录像
	DD_RECORD_TYPE_SENSOR	= 0x0008,			//传感器报警录像

	DD_RECORD_TYPE_BEHAVIOR = 0x0010,			//行为分析报警录像
    DD_RECORD_TYPE_SHELTER     = 0x20,		//遮挡报警
    DD_RECORD_TYPE_OVERSPEED   = 0x40,		//超速
    DD_RECORD_TYPE_OVERBOUND   = 0x80,		//越界
    DD_RECORD_TYPE_OSC         = 0x0100,     //物品看护侦测录像
    DD_RECORD_TYPE_AVD         = 0x0200,     //异常侦测
    DD_RECORD_TYPE_TRIPWIRE    = 0x0400,     //越界侦测
    DD_RECORD_TYPE_PERIMETER   = 0x0800,     //区域入侵侦测
    DD_RECORD_TYPE_VFD         = 0x1000,     //人脸识别
    DD_RECORD_TYPE_POS         = 0x2000,     //POS
	DD_RECORD_TYPE_PIR         = 0x4000,	 //C12 IPC的pir报警录像
    DD_RECORD_TYPE_INTELLIGENT = DD_RECORD_TYPE_OSC | DD_RECORD_TYPE_AVD | DD_RECORD_TYPE_TRIPWIRE | DD_RECORD_TYPE_PERIMETER | DD_RECORD_TYPE_VFD,
    DD_RECORD_TYPE_ALL         = 0xFFFFFFFF, //所有的录像类型
}DD_RECORD_TYPE;
typedef enum _dd_record_status_
{
	DD_RECORD_STATUS_OFF = 0,     //停止录像
	DD_RECORD_STATUS_ON,		  //录像中
	DD_RECORD_STATUS_ABNORMAL 	  //录像异常
}DD_RECORD_STATUS;

typedef enum _dd_event_type_
{
	DD_EVENT_TYPE_MOTION    = 0x00000001,		//移动侦测
	DD_EVENT_TYPE_SENSOR    = 0x00000002,		//传感器报警
	DD_EVENT_TYPE_V_LOSS    = 0x00000004,		//视频丢失
	DD_EVENT_TYPE_V_COVER   = 0x00000008,		//视频遮挡
}DD_EVENT_TYPE;

typedef enum _dd_view_split_mode_
{
	DD_VIEW_SPLIT_1X1	= 0x00010000,	//1X1

	DD_VIEW_SPLIT_2X2	= 0x00020000,	//2X2

	DD_VIEW_SPLIT_1A2	= 0x00040000,	//2X3
	DD_VIEW_SPLIT_2X3,

	DD_VIEW_SPLIT_1A5	= 0x00080000,	//3X3
	DD_VIEW_SPLIT_3X3,

	DD_VIEW_SPLIT_1A7	= 0x00100000,	//4X4
	DD_VIEW_SPLIT_1A12,
	DD_VIEW_SPLIT_4X4,

	DD_VIEW_SPLIT_2A6	= 0x00200000,	//4X6
	DD_VIEW_SPLIT_4X6,

	DD_VIEW_SPLIT_1A9	= 0x00400000,	//5X5
	DD_VIEW_SPLIT_4A9,
	DD_VIEW_SPLIT_1A16,
	DD_VIEW_SPLIT_4A16,
	DD_VIEW_SPLIT_5X5,

	DD_VIEW_SPLIT_1A11	= 0x00800000,	//6X6
	DD_VIEW_SPLIT_1A20,
	DD_VIEW_SPLIT_4A20,
	DD_VIEW_SPLIT_6X6,
}DD_VIEW_SPLIT_MODE;

inline unsigned char DDSplitModeToNum(DD_VIEW_SPLIT_MODE mode)
{
	unsigned char num = 1;
	switch(mode)
	{
	case DD_VIEW_SPLIT_2X2:
		num = 4;
		break;
	case DD_VIEW_SPLIT_2X3:
		num = 6;
		break;
	case DD_VIEW_SPLIT_3X3:
		num = 9;
		break;
	case DD_VIEW_SPLIT_4X4:
		num = 16;
		break;
	case DD_VIEW_SPLIT_5X5:
		num = 25;
		break;
	case DD_VIEW_SPLIT_6X6:
		num = 36;
		break;
	default:
		num = 1;
		break;
	}

	return num;
}

//////////////////////////////////////////////////////////////////////////
//以下为N9000相关类型
typedef enum _n9000_log_type
{
	//全部类型
	//	LOG_ALL,

	//报警日志
	//	LOG_ALARM_ALL,
	LOG_ALARM_MOTION = 0x100,			//移动侦测报警
	LOG_ALARM_SENSOR,					//传感器报警
	LOG_ALARM_ALARMOUTPUT,				//报警输出
	LOG_ALARM_OCCLUSION,
	LOG_ALARM_VLOSS,
	LOG_ALARM_VEHICLE_PLATE_MATCH,
	LOG_ALARM_INTELLIGENT,
	LOG_ALARM_FACE_MATCH,
	LOG_ALARM_COMBINED,

	//操作日志
	//	LOG_OPERATE_ALL,
	LOG_OPERATE_RECORD_SPB,				//录像检索/回放/备份
	LOG_OPERATE_MANUAL_RECORD,			//手动录像
	LOG_OPERATE_MANUAL_ALARM,			//手动报警
	LOG_OPERATE_SYSTEM_MAINTENANCE,		//系统维护
	LOG_OPERATE_PTZ_CONTROL,			//云台控制
	LOG_OPERATE_AUDIO_TALK,				//语音对讲
	LOG_OPERATE_SYSTEM_SCR,				//开关机
	LOG_OPERATE_LOGIN_LOGOUT,			//登录/登出
	LOG_OPERATE_SNAPSHOT_MSPB,			//图片
	LOG_OPERATE_FORMAT_HD,				//格式化磁盘
	LOG_OPERATE_HDD_INSERT,
	LOG_OPERATE_FEATURELIBRARY,

	//设置日志
	//	LOG_CONFIG_ALL,
	LOG_CONFIG_CHANNEL,					//通道参数
	LOG_CONFIG_RECORD,					//录像参数
	LOG_CONFIG_ALARM,					//报警参数
	LOG_CONFIG_DISK,					//磁盘参数
	LOG_CONFIG_NETWORK,					//网络参数
	LOG_CONFIG_SCHEDULE,				//排程参数
	LOG_CONFIG_USER,					//用户参数
	LOG_CONFIG_BASIC,					//基本配置

	//异常日志
	//	LOG_EXCEPTION_ALL,
	LOG_EXCEPTION_UNLAWFUL_ACCESS,		//非法访问
	LOG_EXCEPTION_DISK_FULL,			//磁盘满
	LOG_EXCEPTION_DISK_IO_ERROR,		//磁盘读写出错
	LOG_EXCEPTION_IP_COLLISION,			//IP地址冲突
	LOG_EXCEPTION_INTERNET_DISCONNECT,	//网络断开
	LOG_EXCEPTION_IPC_DISCONNECT,		//前端掉线
	LOG_EXCEPTION_ABNORMAL_SHUTDOWN,	//系统异常关机
	LOG_EXCEPTION_NO_DISK,				//无磁盘
	LOG_EXCEPTION_VIDEO_LOSS,			//视频丢失
}N9000_LOG_TYPE;

typedef enum _n9000_log_major_type
{
	LOG_ALL		= 0x01,//全部类型
	LOG_ALARM_ALL,		//报警日志
	LOG_OPERATE_ALL,	//操作日志
	LOG_CONFIG_ALL,		//设置日志
	LOG_EXCEPTION_ALL,	//异常日志
	LOG_INFOR_ALL,		//其它日志
	LOG_MAJOR_TYPE_END,
}N9000_LOG_MAJOR_TYPE;

//按位保存。最多不能超过32个
typedef enum _dd_video_size_n9000_
{
	DD_VIDEO_SIZE_640X480		= 0x0001,
	DD_VIDEO_SIZE_720X480		= 0x0002,
	DD_VIDEO_SIZE_720X576		= 0x0004,
	DD_VIDEO_SIZE_800X600		= 0x0008,
	DD_VIDEO_SIZE_1024X768		= 0x0010,
	DD_VIDEO_SIZE_1280X960		= 0x0020,
	DD_VIDEO_SIZE_1280X1024		= 0x0040,
	DD_VIDEO_SIZE_1920X1080		= 0x0080,
	DD_VIDEO_SIZE_320X240		= 0x0100,
	DD_VIDEO_SIZE_352X240		= 0x0200,
	DD_VIDEO_SIZE_480X240		= 0x0400,
	DD_VIDEO_SIZE_704X480		= 0x0800,
	DD_VIDEO_SIZE_704X576		= 0x1000,
	DD_VIDEO_SIZE_960X480		= 0x2000,
	DD_VIDEO_SIZE_960X576		= 0x4000,
	DD_VIDEO_SIZE_960X1080		= 0x8000,
	DD_VIDEO_SIZE_1280X720		= 0x00010000,
	DD_VIDEO_SIZE_1600X1200		= 0x00020000,
	DD_VIDEO_SIZE_1920X1536		= 0x00040000,
	DD_VIDEO_SIZE_2048X1536		= 0x00080000,
	DD_VIDEO_SIZE_2304X1296		= 0x00100000,
	DD_VIDEO_SIZE_2560X1440		= 0x00200000,
	DD_VIDEO_SIZE_2592X1520		= 0x00400000,
	DD_VIDEO_SIZE_2592X1944		= 0x00800000,
	DD_VIDEO_SIZE_3840X2160		= 0x01000000,
    DD_VIDEO_SIZE_352x288		= 0x02000000,
}DD_VIDEO_SIZE_N9000;

const unsigned int DD_INVALID_CLIENT_ID	= (~0x0);
const unsigned int DD_LOCAL_CLIENT_ID		= 0;
//const unsigned int DD_LOCAL_DEVICE_ID		= 0;


typedef enum _dd_ptz_config_e_
{
    DD_PTZ_CONFIG_PRESET    = 0x1,
    DD_PTZ_CONFIG_CRUISE,
    DD_PTZ_CONFIG_CRUISE_POINT,
}DD_PTZ_CONFIG_E;

#ifdef __CHONGQING_ZHONGRAN__

const unsigned int DD_MAX_CERTIFICATE_NUM = 64;
#else
const unsigned int DD_MAX_CERTIFICATE_NUM = 20;
#endif
#endif //__DVR_DVS_TYPEDEF_H__
//end
