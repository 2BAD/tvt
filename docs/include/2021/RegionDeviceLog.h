

#ifndef _REGION_DEVICE_LOG_H_
#define _REGION_DEVICE_LOG_H_

#include "Typedef.h"
#include <stdio.h>
#include <string.h>

#ifdef __ENVIRONMENT_WIN32__
#include <Vfw.h>
#else
#include "lvfw.h"
#endif

#include <vector>
#include "TreeNode.h"

#ifdef __ENVIRONMENT_WIN32__
const char RGN_DEV_FILE_NAME[] = "..\\config\\rgn_dev.bin";
#else
const char RGN_DEV_FILE_NAME[] = "config/rgn_dev.bin";
#endif

using namespace std;

const unsigned int MAX_CHANNEL_NUM		= 255;
const unsigned int INVALID_CHANNEL_ID	= MAX_CHANNEL_NUM;
const unsigned int RGN_DEV_NAME_LEN	= 64;
const unsigned int SERVER_IP_DDNS_LEN	= 64;
const unsigned int RGN_DEV_LOG_VER		= 0x01;
const unsigned int	RGN_DEV_INVALID_ID	= 0;
const unsigned int RGN_DEV_FILE_FLAG	= mmioFOURCC('D', 'H', 'D', 'R');

typedef struct _region_info
{
	unsigned int	regionID;						//区域ID
	unsigned int	parentID;						//父区域ID
	char			regionName[RGN_DEV_NAME_LEN];	//区域名称
}REGION_INFO;

typedef struct _device_info
{
	unsigned int	deviceID;						//设备ID
	unsigned int	parentID;						//父区域ID
	unsigned short	serverPort;						//设备端口号
	unsigned short	channelNum;						//通道数目
	char			serverAddr[SERVER_IP_DDNS_LEN];	//设备网络地址
	char			userName[64];					//登录设备的用户名
	char			password[64];					//登录设备的密码
	char			deviceName[RGN_DEV_NAME_LEN];	//设备名称
}DEVICE_INFO;

typedef struct _channel_info
{
	unsigned int	deviceID;
	unsigned char	channel;
	unsigned char	channelID;
	unsigned char	reserved[2];
	char			channelName[RGN_DEV_NAME_LEN];
}CHANNEL_INFO;

typedef struct _group_info
{
	unsigned int	groupID;
	unsigned char	groupChannel[MAX_CHANNEL_NUM];
	char			groupName[RGN_DEV_NAME_LEN];
}GROUP_INFO;

typedef struct _rgn_dev_file_header
{
	unsigned int			fileFlag;	//always is "DHDR"
	unsigned int			fileVer;	//
	unsigned int			nameLen;
	unsigned int			channelNum;
	unsigned int			regionNum;
	unsigned int			deviceNum;
	unsigned int			groupNum;
}RGN_DEV_FILE_HEADER;

class CRegionDeviceLog
{
public:
	CRegionDeviceLog(void);
	~CRegionDeviceLog(void);

	BOOL GetLogInfo(CTreeNode *pRgnDevTree, vector<GROUP_INFO> &groupArray, CHANNEL_INFO *pChannelInfo, int channelNum, unsigned int &maxID);
	BOOL SetLogInfo(CTreeNode *pRgnDevTree, vector<GROUP_INFO> &groupArray, CHANNEL_INFO *pChannelInfo, int channelNum);

private:
	BOOL CreateLogFile();
	static int CaculateNodeNum(CTreeNode *pNode, void *pUser);
	void CaculateNodeNum(CTreeNode *pNode);
	static int WriteRegion(CTreeNode *pNode, void *pUser);
	static int WriteDevice(CTreeNode *pNode, void *pUser);

private:
	RGN_DEV_FILE_HEADER			m_fileHeader;
	FILE						*m_pFile;
};

#endif
