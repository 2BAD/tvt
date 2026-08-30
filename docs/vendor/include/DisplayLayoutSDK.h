
#ifndef _DISPLAY_LAYOUT_SDK_H_
#define _DISPLAY_LAYOUT_SDK_H_

#include "DisplayDefine.h"

#ifdef WIN32

#define CALL_METHOD __stdcall

#ifdef LAYOUT_SDK_EXPORTS
#define LAYOUT_API __declspec(dllexport)
#else
//#define LAYOUT_API __declspec(dllimport)
#define LAYOUT_API
#endif

#else

#define CALL_METHOD
#define LAYOUT_API
#endif

enum
{
	LAYOUT_RET_SUCCESS,
	LAYOUT_RET_CHANNEL_BINDED,
	LAYOUT_RET_PORT_BINDED,
	LAYOUT_RET_PORT_EXCEED,
};

#ifdef __cplusplus
extern "C"
{
#endif

//maxPortNum,最多设置的分割画面数，不包含画中画的个数
LAYOUT_API bool CALL_METHOD LAYOUT_Init(unsigned short maxPortNum);
LAYOUT_API void CALL_METHOD LAYOUT_Cleanup();

//设置总显示区域大小
LAYOUT_API void CALL_METHOD LAYOUT_SetDisplayArea(unsigned short x, unsigned short y, unsigned short width, unsigned short height);

//设置标准层的分割画面,bAutoNext表示在设置与上次相同分割模式时是否要跳到下一个页面
LAYOUT_API void CALL_METHOD LAYOUT_SetSplitMode(unsigned int splitMode, bool bAutoNext, unsigned int firstVisiblePort=0);

//合并显示窗口，变成局部大窗口
LAYOUT_API void CALL_METHOD LAYOUT_CombinePort(unsigned short startPort, unsigned short horizSpan, unsigned short vertSpan);

//根据点击的位置得到区域，返回点击到的区域编号，如果没有点击到任何区域，返回-1
LAYOUT_API int CALL_METHOD LAYOUT_GetHitPort(unsigned short x, unsigned short y, DISPLAY_PORT *pHitPort);

//绑定设备通道的指定流到显示窗口
LAYOUT_API int CALL_METHOD LAYOUT_BindPortVideoStream(unsigned short portIndex, int deviceID, short channel, short streamType);

//设置画中画通道
LAYOUT_API int CALL_METHOD LAYOUT_BindPIPVideoStream(LAYOUT_PIP_POSITION pipPosition, int deviceID, short channel, short streamType);

//解绑某个设备通道流
LAYOUT_API void CALL_METHOD LAYOUT_UnbindVideoStream(int deviceID, short channel, short streamType);

//解绑某个显示窗口，如果portIndex为0xffff，则解绑所有显示窗口,包括画中画窗口
LAYOUT_API void CALL_METHOD LAYOUT_UnbindPort(unsigned short portIndex);

//解绑某个画中画窗口
LAYOUT_API void CALL_METHOD LAYOUT_UnbindPIPPort(LAYOUT_PIP_POSITION pipPosition);

//返回当前所有显示区域的信息
LAYOUT_API int CALL_METHOD LAYOUT_GetLayoutInfo(DISPLAY_PORT *pDisplayPort, int portNum);

#ifdef __cplusplus
};
#endif

#endif
