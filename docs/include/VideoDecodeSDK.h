#include "FrameInfo.h"

#ifndef _VIDEO_DECODE_SDK_H_
#define _VIDEO_DECODE_SDK_H_

/************************************************************************
该解码器模块采用多线程解码，会根据CPU核心数自动产生相同数目的解码线程，以达
到充分利用CPU资源进行解码的能力。
/************************************************************************/

#define CALL_METHOD __stdcall

#ifdef VIDEO_DECODE_SDK_EXPORTS
#define DECODE_API __declspec(dllexport)
#else
//#define DECODE_API __declspec(dllimport)
#define DECODE_API
#endif

enum VIDEO_DECODE_RET
{
	DECODE_RET_SUCCESS,
	DECODE_RET_NOT_START,
	DECODE_RET_BUSY,
};


#ifdef __cplusplus
extern "C"
{
#endif

typedef void (CALL_METHOD *DecDataCallbackFun)(int threadID, int deviceID, unsigned short channel, int streamType, DECODE_FRAME_INFO frameData, void *pUser);

//初始化解码器，为解码器分配资源
DECODE_API BOOL CALL_METHOD DECODE_Initial();

//退出解码器，释放解码器资源
DECODE_API void CALL_METHOD DECODE_Quit();

//启动某个通道流的解码
DECODE_API BOOL CALL_METHOD DECODE_Start(int deviceID, int channel, int streamType);

//停止指定通道码流的解码
DECODE_API void CALL_METHOD DECODE_Stop(int deviceID, int channel, int streamType);

//设置指定通道码流的视频格式
DECODE_API BOOL CALL_METHOD DECODE_SetVideoFormat(int deviceID, int channel, int streamType, BITMAPINFOHEADER bmpInfoHeader);

//获取指定通道码流解码后的格式
DECODE_API BOOL CALL_METHOD DECODE_GetDecVideoFormat(int deviceID, int channel, int streamType, BITMAPINFOHEADER *pBmpInfoHeader);

//设置解码后是否为YUV(0不是，1是)
DECODE_API void CALL_METHOD DECODE_SetDecVideoFormat(BOOL enbaleYUV);

//解码一帧数据，返回结果见VIDEO_DECODE_RET
DECODE_API LONG CALL_METHOD DECODE_DecodeOneFrame(int deviceID, int channel, int streamType, ENCODE_FRAME_INFO encodeFrame);

//设置解码后的数据回调
DECODE_API BOOL CALL_METHOD DECODE_SetDecDataCallback(int deviceID, int channel, int streamType, DecDataCallbackFun fDecCBFun, void *pParam);

DECODE_API BOOL CALL_METHOD DECODE_CapturePictureJPEG(DWORD &dwPicSize,int deviceID,DWORD dwChannel,int streamType, BYTE *pUserBuf,DWORD dwUserSize);


#ifdef __cplusplus
};
#endif

#endif
