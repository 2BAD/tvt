/***********************************************************************
** Copyright (C) Tongwei Video Technology Co.,Ltd. All rights reserved.
** Author       :	袁石维
** Date         : 2010-12-17
** Name         : DDRecordLog.h
** Version      : 1.0
** Description  :
** Modify Record:
***********************************************************************/
#ifndef _DD_RECORD_LOG_H_
#define _DD_RECORD_LOG_H_

typedef struct  _dd_record_log_file_head_info_
{
	unsigned int	headFlag;				//文件头部标识
	unsigned int	version;				//该文件的版本号

	unsigned int	recordChnnNum;			//记录的通道数目
	unsigned int	recordFileNum;			//记录的文件数目

	unsigned int	recordFileLen;			//录像文件大小
	unsigned int	recordFileStart;		//录像文件的起始位置（分区内）
	unsigned int	recordFileEnd;			//录像文件的结束位置（分区内）

	unsigned int	diskInfoOffset;			//磁盘信息区域偏移（每个录像文件对应一段）
	unsigned int	diskInfoLen;			//磁盘信息区域总长度

	unsigned int	recordFileLogNum;		//预留存储空间可写的记录数目
	unsigned int	recordFileInfoOffset;	//录像文件信息偏移（文件记录偏移）
	unsigned int	recordFileInfoLen;		//录像文件信息区域总长度

	unsigned int	fileLen;				//本文将长度

	unsigned int	checkBit;				//校验位
}DD_RECORD_LOG_FILE_HEAD_INFO;

typedef struct _dd_disk_index_info_
{
	unsigned int	channel;	//通道号
	unsigned int	flag;		//标记（正常为0XFFFF)

	unsigned int	recv[6];	//保留区
}DD_DISK_INDEX_INFO;

typedef struct _dd_file_file_info_
{
	unsigned short		deviceID;		//设备号
	unsigned short		cameraID;		//摄像机编号
	unsigned int		channel;		//通道号

	unsigned int		startTime;		//起始时间
	unsigned int		endTime;		//结束时间

	unsigned int		checkBit;		//校验位
}DD_FILE_FILE_INFO;

typedef struct _dd_file_log_info_
{
	unsigned char	bLocked;		//0表示未锁定，1表示锁定
	unsigned char	bUnofficial;	//0表示正式记录，1表示非正式记录（即修改时间后的重叠记录）
	unsigned char	enableCard;		//是否使用卡号
	unsigned char	recv;			//保留字节

	unsigned int	type;			//录像类型
	unsigned int	startTime;		//起始时间
	unsigned int	endTime;		//结束时间
	unsigned int	size;			//该段录像数据长度

	char			cardNo[32];		//卡号

	unsigned char	recv[8];		//保留区

	unsigned int	checkBit;		//校验位
}DD_FILE_LOG_INFO;

typedef struct _dd_date_info_
{
	DD_DATE		date;						//日期信息
	std::list<unsigned short> *pFileList;	//数组（通道）
}DD_DATE_INFO, *P_DD_DATE_INFO;

const unsigned int	MAX_RECORD_LOG_NUM = 256;

class CDDRecordLog
{
public:
	CDDRecordLog();
	~CDDRecordLog();

	//创建一个新的数据库文件
	static bool CreateLogFile(const char *pFilePath, unsigned int fileNum, unsigned char videoInputNum, unsigned int maxLogNum);

	//初始化和反初始化一个已有的数据库文件
	bool Initial(unsigned char diskIndex, const char *pFilePath = NULL);
	void Quit();
	bool CreateDateList();

	//
	unsigned int WriteLogStart(unsigned int type, unsigned int startTime, bool bCardNo = false, const char *pCardNo = NULL);
	unsigned int WriteLogEnd(unsigned int type, unsigned int endTime, unsigned int size);

	//一些查询的方法
	unsigned int GetDateList(std::list<DD_DATE> & list);
	unsigned int GetRecordLog(const std::list<unsigned short> & chnn, unsigned int startTime, unsigned int endTime, \
		unsigned int type, std::list<DD_RECORD_LOG> *pLogList);

	//
	unsigned int Lock(const std::list<DD_RECORD_LOG> &logList);
	unsigned int UnLock(const std::list<DD_RECORD_LOG> &logList);
protected:
private:
};
