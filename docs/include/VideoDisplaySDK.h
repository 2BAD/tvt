
#ifndef _VIDEO_DISPLAY_SDK_H_
#define _VIDEO_DISPLAY_SDK_H_

#include "DisplayDefine.h"

#define CALL_METHOD __stdcall

#ifdef VIDEO_DISPLAY_SDK_EXPORTS
#define DISPLAY_API __declspec(dllexport)
#else
//#ifdef WIN32
//#define DISPLAY_API __declspec(dllimport)
//#else
#define DISPLAY_API
#endif
//#endif

#ifdef __cplusplus
extern "C"
{
#endif

//初始化视频显示（初始化directdraw对象）
DISPLAY_API BOOL CALL_METHOD DISPLAY_Init(HWND hWnd, int maxPortNum, RENDER_TYPE eRenderType);

//释放资源
DISPLAY_API void CALL_METHOD DISPLAY_Quit(HWND hWnd);

//
DISPLAY_API void CALL_METHOD DISPLAY_SetDisplayPort(HWND hWnd, DISPLAY_PORT *pDisplayPort, int portNum);

//
DISPLAY_API BOOL CALL_METHOD DISPLAY_SetVideoInfo(HWND hWnd, unsigned int deviceID, unsigned short channel, unsigned short streamType, BITMAPINFOHEADER videoInfo);

//显示数据
DISPLAY_API void CALL_METHOD DISPLAY_VideoOut(HWND hWnd, unsigned int deviceID, unsigned short channel, unsigned short streamType, unsigned char *pData, int dataLen, LONGLONG llTime);

DISPLAY_API void CALL_METHOD DISPLAY_Start(HWND hWnd, int deviceID, int channel, int streamType);

DISPLAY_API void CALL_METHOD DISPLAY_Stop(HWND hWnd, int deviceID, int channel, int streamType);

DISPLAY_API void CALL_METHOD DISPLAY_HighLightWindow(HWND hWnd, int portIndex);
DISPLAY_API void CALL_METHOD DISPLAY_Refresh(HWND hWnd);

DISPLAY_API BOOL CALL_METHOD DISPLAY_TextOut(HWND hWnd, int deviceID, int channel, int streamType, short x, short y, const char *pText);

DISPLAY_API void CALL_METHOD DISPLAY_RegisterDrawFun(unsigned int deviceID, unsigned short channel, unsigned short streamType, HWND hWnd, DRAW_FUN_CALLBACK fDrawFun, void *pUser);

DISPLAY_API void CALL_METHOD DISPLAY_IsSupportYUV(HWND hWnd,BOOL *pSupport);

DISPLAY_API void CALL_METHOD DISPLAY_SetChannelStatus(HWND hWnd, LONG lDeviceID, int nChannel, CH_STATUS StatusIndex, bool IsSet);

//设置SDK内部显示对象是否每次重复创建，如果不是复复创建需要在程序结束时调用DISPLAY_ClearUp，默认为重复创建
DISPLAY_API void CALL_METHOD DISPLAY_SetDisplayObjCreateMode(BOOL bReCreate);

DISPLAY_API void CALL_METHOD DISPLAY_ClearUp();

//设置鱼眼校正模式，进入鱼眼校正模式与退出鱼眼校正模式都需要调用此接口,仅单窗口模式使用
//输入参数：
//lPort： 播放端口
//fishEyeMode：安装模式+校正模式
DISPLAY_API BOOL CALL_METHOD DISPLAY_SetFishEyeAdjust(HWND hWnd, FISHEYE_MODE fishEyeMode);

//设置焦点，用于判断当前操作作用于鱼眼校正的哪个分割区域
//输入参数：
//lPort： 播放端口
//nX：当前焦点的X坐标值，相对于当前播放窗口坐标系
//nY：当前焦点的Y坐标值，相对于当前播放窗口坐标系
DISPLAY_API BOOL CALL_METHOD DISPLAY_FishEyeAdjustFocus(HWND hWnd, int nX, int nY);
DISPLAY_API BOOL CALL_METHOD DISPLAY_FishEyeAdjustFocusEx(HWND hWnd, int nX, int nY, int &nIndex);
//电子云台移动，只有进入鱼眼校正模式下，属于电子云台的分割才可以移动
//输入参数：
//lPort： 播放端口
//nMoveX：鼠标左键拖拽时相对于起点之X坐标轴上的水平偏移量，向右为正，向左为负，以起点为原点
//nMoveY：鼠标左键拖拽时相对于起点之Y坐标轴上的垂直偏移量，向上为正，向下为负，以起点为原点
DISPLAY_API BOOL CALL_METHOD DISPLAY_FishEyeAdjustMove(HWND hWnd, int nMoveX, int nMoveY);

//获取当前焦点所在的校正区域位置
//输入参数：
//lPort： 播放端口
//输出参数
//AreaRect：当前焦点所在校正区域的位置，相对于当前播放窗口坐标系
DISPLAY_API BOOL CALL_METHOD DISPLAY_FishEyeAdjustGetArea(HWND hWnd, RECT &AreaRect);

//电子云台放大，只有进入鱼眼校正模式下，属于电子云台的分割才可以放大
//输入参数：
//lPort： 播放端口
//ZoomRect： 指定要放大的区域位置信息，相对于当前播放窗口坐标系
DISPLAY_API BOOL CALL_METHOD DISPLAY_FishEyeAdjustZoom(HWND hWnd, const RECT &ZoomRect);

//画线
DISPLAY_API BOOL CALL_METHOD DISPLAY_ShowRect(HWND hWnd, int x1Div100, int y1Div100, int x2Div100, int y2Div100, bool isShow);
DISPLAY_API BOOL CALL_METHOD DISPLAY_ShowRectList(HWND hWnd, const unsigned char* pVFDRectData, int nBufLen);
#ifdef __cplusplus
};
#endif

#endif
