
#ifndef _DEVICE_MANAGER_H_
#define _DEVICE_MANAGER_H_

#include <list>
#include "TreeNode.h"
#include "RegionDeviceLog.h"
#include "DVR_NET_SDK.h"
#include "DDPublic.h"
#include "dvrprotocol.h"
#include "PTZ.h"

using namespace std;

typedef struct _dev_rgn_node
{
	DWORD		parentID;
	DWORD		selfID;
	TREE_NODE_TYPE		nodeType;
	char				devRgnName[64];
}DEV_RGN_NODE;

typedef struct _dev_link_info
{
	LONG				lLoginID;
	NET_SDK_DEVICEINFO	dvrDeviceInfo;
}DEV_LINK_INFO;

class CDeviceManager
{
	typedef struct _find_name_helper
	{
		TREE_NODE_TYPE	nodeType;
		const char		*pName;
		BOOL			bFound;
	}FIND_NAME_HELPER;

	typedef struct _find_netpos_helper
	{
		const char		*pDVRAddr;
		WORD			wPort;
		BOOL			bFound;
	}FIND_NETPOS_HELPER;

	typedef struct _get_deviceID
	{
		LONG			loginID;
		LONG			deviceID;
	}GET_DEVICEID;

	typedef struct _find_device_by_IpPort
	{
		const char		*deviceIp;
		WORD			port;
		LONG			deviceID;
	}FIND_DEV_BY_IP_PORT;
public:
	static CDeviceManager *Instance();
	BOOL Initial();
	void Quit();

	BOOL Start();
	void Stop();

//////////////////////////////////////////////////////////////////////////
//设备通道集管理
	//测试名称是否已存在
	BOOL RegionNameExist(const char *pRegionName);
	BOOL DeviceNameExist(const char *pDeviceName);
	BOOL GroupNameExist(const char *pGroupName);

	//测试网络设备节点是否已存在
	BOOL DeviceExist(const char *sDVRIP, WORD wDVRPort);

	//区域设备节点添加、删除、修改操作
	DWORD AddRegion(DWORD parentID, const char *pRegionName);
	DWORD AddDevice(DWORD parentID, const char *pDeviceName, char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword, int channelNum);
	BOOL RemoveRegion(DWORD regionID);
	BOOL RemoveDevice(DWORD deviceID);
	BOOL ModifyRegion(DWORD regionID, const char *pNewName);
	BOOL ModifyDevice(DWORD deviceID, const char *pDeviceName, char *sDVRIP,WORD wDVRPort,char *sUserName,char *sPassword);
	BOOL ModifyChannel(DWORD channelID, const char *pChannel);

	//对组的操作
	DWORD AddGroup(const char *pGroupName);
	BOOL AddChannelToGroup(BYTE channelID, DWORD groupID);
	BOOL RemoveGroup(DWORD groupID);
	BOOL RemoveChannelFromGroup(BYTE channelID, unsigned groupID);
	BOOL ModifyGroup(DWORD groupID, const char *pNewName);

	//查看节点类型
	TREE_NODE_TYPE GetNodeType(DWORD dwNodeID);

	//对区域设备的访问
	BOOL GetDevRgnNode(list<DEV_RGN_NODE> &listDevRgn);
	BOOL GetDeviceInfo(DWORD deviceID, DEVICE_INFO &deviceInfo);
	LONG GetDeviceChannel(DWORD deviceID, CHANNEL_INFO *pChannelInfo, LONG channelNum);
	BOOL GetChannelInfo(DWORD channelID, CHANNEL_INFO &channelInfo);

	//对分组的访问
	BOOL GetGroupNode(vector<GROUP_INFO> &groupInfo);
	LONG GetGroupChannelInfo(DWORD groupID, CHANNEL_INFO *pChannelInfo, LONG channelNum);
//设备通道集管理END
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//设备网络交互接口
	LONG StartLivePlay(DWORD channelID, LONG streamType, LIVE_DATA_CALLBACK fLiveDataCallBack = NULL, void* pUser = NULL);
	BOOL StopLivePlay(LONG lLiveHandle);

	LONG PlaybackByTime(LONG deviceID, LONG *pChannels, LONG channelNum, unsigned int startTime, unsigned int stopTime);
	BOOL StopPlayback(LONG lPlayHandle);

	LONG GetFileByTime(LONG deviceID, LONG channel, unsigned int startTime, unsigned int stopTime, char* fileName);
	LONG GetFilePos(LONG lHandle);
	BOOL StopDownLoad(LONG lHandle);

	BOOL SearchRecDate(LONG deviceID, list<DD_DATE> &recDataList);
	BOOL SearchFile(LONG deviceID, LONG lChannel, unsigned int startTime, unsigned int stopTime, list<DD_REC_FILE> &recFileList);
	BOOL SearchEvent(LONG deviceID, LONG lChannel, DWORD dwRecType, unsigned int startTime, unsigned int stopTime, list<DD_REC_EVENT> &recEventList);
	BOOL SearchTime(LONG deviceID, LONG lChannel, unsigned int startTime, unsigned int stopTime, list<DD_REC_TIME> &recTimeList);
	BOOL LockFile(LONG deviceID, NET_SDK_REC_FILE* pRecFile, LONG fileNum);
	BOOL UnlockFile(LONG deviceID, NET_SDK_REC_FILE* pRecFile, LONG fileNum);
	BOOL DeleteFile(LONG deviceID, NET_SDK_REC_FILE* pRecFile, LONG fileNum);
	LONG EnterDVRConfig(LONG deviceID);
	BOOL SetDVRConfig(LONG deviceID, DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize);
	LONG GetDVRConfig(LONG deviceID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, BOOL bDefaultConfig = FALSE);
	BOOL ExitDVRConfig(LONG deviceID);
	LONG GetLoginIDToConfig();
	void SetDeviceID(LONG deviceID);
	LONG GetDeviceIDByLoginID(LONG LoginID);
	BOOL PTZControl(LONG deviceID, LONG channel, LONG command, LONG value, LONG speed);
	BOOL GetVideoColor(DWORD channelID,  LONG lChannel, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
	BOOL GetDefualtVideoColor(DWORD channelID, DWORD *pBrightValue, DWORD *pContrastValue, DWORD *pSaturationValue, DWORD *pHueValue);
	BOOL SetVideoColor(DWORD channelID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwpHueValue);
	BOOL SaveVideoColor(DWORD channelID, LONG lChannel, DWORD dwBrightValue, DWORD dwContrastValue, DWORD dwSaturationValue, DWORD dwpHueValue);

	BOOL PTZSetCruise(LONG deviceID, LONG channel, BYTE byCruiseIndex, DD_CRUISE_POINT_INFO *pCruisePoint, int pointNum);

	//capture JPEG data
	BOOL CaptureJPEGData(LONG lUserID, LONG lChannel, char *sJpegPicBuffer, DWORD dwPicSize,  LPDWORD lpSizeReturned);

	LONG StartTalk(LONG deviceID);
	void StopTalk(LONG talkHandle);


	LONG GetLoginID(LONG deviceID);
	BOOL GetNetTDvrDevice(LONG deviceID, LPNET_SDK_DEVICEINFO pdeviceInfo);
	DWORD GetLastError();
	LONG GetDeviceIDByIpPort(const char *sDVRIP, WORD wDVRPort);

	BOOL GetDeviceTime(LONG deviceID);
//设备网络交互接口END
//////////////////////////////////////////////////////////////////////////


private:
	CDeviceManager(void);
	~CDeviceManager(void);

	static int RemoveDeviceCall(CTreeNode *pNode, void *pUser);
	static int GetRgnDevNodeCall(CTreeNode *pNode, void *pUser);
	static int FindNameCall(CTreeNode *pNode, void *pUser);
	static int FindNetposCall(CTreeNode *pNode, void *pUser);

	static int GetDeviceID(CTreeNode *pNode, void *pUser);
	static int FileDeviceByIpPort(CTreeNode *pNode, void *pUser);

	static RESULT WINAPI ConnectThread(void *pParam);
	void ConnectProc();

	unsigned int NetTimeToDVRTime(const DD_TIME &netTime);
	void DVRTimeToNetTime(unsigned int dvrTime, DD_TIME &netTime);


private:
	CRegionDeviceLog		m_rgnDevLog;

	CTreeNode				*m_pRgnDevTree;
	vector<GROUP_INFO>		m_groupInfo;
	CHANNEL_INFO			m_channelInfo[MAX_CHANNEL_NUM];
	DWORD					m_nextID;

	//连接线程，程序启动时已保存在设备列表中的设备，及程序运行中新添加的设备都会在这里执行连接
	PUB_thread_t			m_threadID;
	bool					m_bConnecting;

	CPUB_Lock				m_deviceLock;
	LONG					m_deivceID;
};

#endif
