//定义数据类型，为跨平台开发服务服务
#ifndef _DVRTYPEDEFINE_
#define _DVRTYPEDEFINE_

#ifdef __ENVIRONMENT_WIN32__ ////////////////////如果是Windows平台
#include "stdafx.h"

//定义PACKED 主要用于解决在Windows解决对奇一般使用#pragma pack(n)而Linux下一般使用__attribute__((packed))
//在此结构体要写入文件或者在跨平台之间访问时才需要以下定义，注意__attribute__((packed))只用于单字节对齐
#define PACKED
typedef DWORD				THREAD_ID;
#else ////////////////////linux平台
#include <sys/types.h>
#include <unistd.h>

#define PACKED __attribute__((packed))
typedef pid_t				THREAD_ID;

typedef unsigned int       DWORD;
typedef DWORD				*LPDWORD;
typedef unsigned int       ULONG;

#if defined (__ENVIRONMENT_LINUX_ANDROID__) || defined (__ENVIRONMENT_IOS__)
    typedef int                LONG;
#else
    #if defined(OS_IS_64BIT)
        typedef long long               LONG;
    #else
        typedef long                LONG;
    #endif
#endif

typedef short				SHORT;
typedef unsigned short      WORD;

typedef int                 INT;
typedef unsigned int        UINT;

typedef long long           LONGLONG;
typedef unsigned long long  ULONGLONG;

//以下是为了驱动库的定义使用方便
typedef	signed char			SBYTE;

typedef signed char			CHAR;
typedef unsigned char       BYTE;

typedef bool				BOOL;
#include <sys/time.h>
typedef timeval				DVRDATETIME;

typedef void *				LPVOID;

typedef void *				HWND;
typedef void *				HDC;

#define TRUE				true
#define FALSE				false

#define CALLBACK

#endif ////////#ifdef __ENVIRONMENT_WIN32__ //如果是Windows平台

#endif ////////#ifndef _DVRTYPEDEFINE_
