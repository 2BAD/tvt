
#ifndef _DVR_PROTOCOL_H_
#define _DVR_PROTOCOL_H_

#include "dvrdvstypedef.h"
#include "dvrdvsdefine.h"
#include "dvrdvsconfig.h"

const unsigned int			DVR_PROTOCOL_VER = 0x00040001;

const unsigned int			DD_FILE_NAME_LEN = 256;

typedef struct _dd_pack_cmd
{
	unsigned int		cmdType;
	unsigned int		paramLen;
	unsigned int		protocolVer;
}DD_PACK_CMD;

enum DD_PROTOCOL_CMD
{
	DD_CMD_LOGIN,
	DD_CMD_LOGOUT,

	DD_CMD_START_LIVE_STREAM,
	DD_CMD_STOP_LIVE_STREAM,
	DD_CMD_LIVE_STREAM_TYPE,
	DD_CMD_SET_LIVE_AUDIO,

	DD_CMD_SEARCH_REC_DATE,		//DD_DATE
	DD_CMD_SEARCH_REC_FILE,
	DD_CMD_SEARCH_REC_EVENT,
	DD_CMD_SEARCH_REC_TIME,

	DD_CMD_LOCK_FILE,
	DD_CMD_UNLOCK_FILE,
	DD_CMD_DELETE_FILE,

	DD_CMD_START_PLAYBACK,
	DD_CMD_STOP_PLAYBACK,
	DD_CMD_PLAYBACK_CTRL,
	DD_CMD_GET_PLAY_TIME,		//DD_TIME
	DD_CMD_SET_PLAYBACK_AUDIO,

	DD_CMD_START_BACKUP,
	DD_CMD_STOP_BACKUP,
	DD_CMD_GET_BACKUP_POS,

	DD_CMD_PTZ_CTRL,
	DD_CMD_PTZ_SET_CRUISE,

	DD_CMD_GET_VIDEO_COLOR,
	DD_CMD_SET_VIDEO_COLOR,
	DD_CMD_SAVE_VIDEO_COLOR,
	DD_CMD_GET_VIDEO_DEFAULT_COLOR,//DD_VIDEO_COLOR

	DD_CMD_CHANGE_DISPLAY_MODE,

	DD_CMD_GET_AUDIO_CHANNEL,   //获取可用音频通道
};

enum DD_RESULT_CODE
{
	DD_RESULT_SUCCESS,
	DD_RESULT_NOT_CONNECTED,
	DD_RESULT_PARAM_ERROR,
};

//DD_CMD_START_LIVE_STREAM
//DD_CMD_STOP_LIVE_STREAM
typedef struct _dd_param_live_stream
{
	int			channelId;		//通道ID
	int			streamType;		//数据流类型NET_SDK_STREAM_TYPE
	int			portIndex;		//绑定显示的区域
}DD_PARAM_LIVE_STREAM;

//DD_CMD_START_LIVE_STREAM返回参数
typedef struct _dd_param_live_stream_result
{
	int			result;		//DD_RESULT_CODE
}DD_PARAM_LIVE_STREAM_RESULT;

//DD_CMD_LIVE_STREAM_TYPE
typedef struct _dd_param_live_stream_type
{
	int			channelId;
	int			streamType;
}DD_PARAM_LIVE_STREAM_TYPE;

enum DD_AUDIO_SET_FLAG
{
	DD_AUDIO_SET_CHANNEL	= 0x01,
	DD_AUDIO_SET_VOLUME		= 0x02,
	DD_AUDIO_MUTE			= 0x04,
};

//DD_CMD_SET_LIVE_AUDIO
typedef struct _dd_param_live_audio_
{
	int			flag;		//DD_AUDIO_SET_FLAG
	int			deviceId;
	int			channel;
	int			volume;
	int			bSetMute;
}DD_PARAM_LIVE_AUDIO;

typedef struct _dd_sub_param_channel
{
	unsigned int			deviceID;
	unsigned int			channel;
}DD_SUB_PARAM_CHANNEL;

//DD_CMD_SEARCH_REC_DATE
//没有参数

//DD_CMD_SEARCH_REC_FILE
//DD_CMD_SEARCH_REC_EVENT
//DD_CMD_SEARCH_REC_TIME
typedef struct _dd_param_search_rec_data
{
	unsigned int			startTime;
	unsigned int			stopTime;
	unsigned int			recType;
	unsigned int			channelNum;
	DD_SUB_PARAM_CHANNEL	channels[1];
}DD_PARAM_SEARCH_REC_DATA;

//DD_CMD_SEARCH_REC_TIME
//录像时间信息定义
typedef struct _dd_rec_time
{
	unsigned int	deviceID;
	unsigned int	dwChannel;	//通道号
	unsigned int	startTime;	//该段录像开始时间
	unsigned int	stopTime;	//该段录像结束时间
}DD_REC_TIME;

//DD_CMD_SEARCH_REC_FILE
typedef struct _dd_rec_file
{
	unsigned int	deviceID;
	unsigned int	dwChannel;
	unsigned int	bFileLocked;
	unsigned int	startTime;
	unsigned int	stopTime;
	unsigned int	dwPartition;
	unsigned int	dwFileIndex;
}DD_REC_FILE;

//DD_CMD_SEARCH_REC_EVENT
typedef struct _dd_rec_event
{
	unsigned int	deviceID;
	unsigned int	dwChannel;
	unsigned int	startTime;
	unsigned int	stopTime;
	unsigned int	dwRecType;
}DD_REC_EVENT;

//DD_CMD_START_PLAYBACK
//DD_CMD_STOP_PLAYBACK
typedef struct _dd_param_playback
{
	int					portIndex;
	unsigned int			startTime;
	unsigned int			stopTime;
	unsigned int			deviceID;
	unsigned int			channelNum;
	DD_SUB_PARAM_CHANNEL	channels[1];
}DD_PARAM_PLAYBACK;

//DD_CMD_PLAYBACK_CTRL
typedef struct _dd_param_playback_ctrl
{
	unsigned int			deviceID;
	unsigned int			ctrlCommand;	//NET_SDK_PLAYCTRL_TYPE
	unsigned int			ctrlValue;
}DD_PARAM_PLAYBACK_CTRL;

//DD_CMD_START_BACKUP
typedef struct _dd_param_backup
{
	char					backupPath[DD_FILE_NAME_LEN];
	int					fileIndex;
	unsigned int			startTime;
	unsigned int			stopTime;
	unsigned int			deviceID;
	unsigned int			channel;
}DD_PARAM_BACKUP;

//DD_CMD_START_BACKUP 返回值
typedef struct _dd_param_backup_ret
{
	int		result;		//DD_RESULT_CODE
}DD_PARAM_BACKUP_RET;

//DD_CMD_GET_BACKUP_POS返回值
typedef struct _dd_param_backup_pos
{
	int					fileIndex;
	int					filePosPercent;
	int					totalPosPercent;
}DD_PARAM_BACKUP_POS;

//DD_CMD_PTZ_CTRL
typedef struct _dd_param_ptz_ctrl
{
	unsigned int			dwDeviceID;
	unsigned int			dwChannel;
	unsigned int			dwPtzCommand;
	unsigned int			dwCmdValue;
	unsigned int			dwSpeed;
}DD_PARAM_PTZ_CTRL;

//DD_CMD_PTZ_SET_CRUISE
typedef struct _dd_param_ptz_set_cruise
{
	unsigned int			dwDeviceID;
	unsigned int			dwChannel;
	unsigned int			dwCruiseIndex;
	unsigned int			dwPointNum;
	DD_CRUISE_POINT_INFO	cruisePointInfo[1];
}DD_PARAM_PTZ_SET_CRUISE;

//DD_CMD_GET_VIDEO_COLOR(IN, OUT)
//DD_CMD_SET_VIDEO_COLOR(IN)
//DD_CMD_SAVE_VIDEO_COLOR(IN)
typedef struct _dd_param_video_color
{
	unsigned int			channel;
	DD_VIDEO_COLOR			videoColor;
}DD_PARAM_VIDEO_COLOR;

//DD_CMD_PTZ_CTRL
//DD_CMD_PTZ_SET_CRUISE
typedef struct _dd_param_ptz_ret
{
	int					result;
}DD_PARAM_PTZ_RET;

//DD_CMD_CHANGE_DISPLAY_MODE
typedef struct _dd_param_display_mode
{
	unsigned int		displayMode;		// DD_VIEW_SPLIT_MODE;
	unsigned int		autoNextPage;		//是否自动翻页(true时firstVisiblePort为0时下一页不为0时上一页)
	unsigned int		firstVisiblePort;   //第一个可见通道
}DD_PARAM_DISPLAY_MODE;

#endif
