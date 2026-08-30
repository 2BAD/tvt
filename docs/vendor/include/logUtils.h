//
// Created by fujq on 2021/6/16.
//

#ifndef PROTOSDK_LOGUTILS_H
#define PROTOSDK_LOGUTILS_H

#if __APPLE__
	#include "TargetConditionals.h"
     	#define LOG_PRINT(level,fmt,...)
#elif __linux__
	#if defined(ANDROID)
		#include <android/log.h>
	#endif
#endif


#ifndef LOG_TAG
#define LOG_TAG "NVR_SDK_JNI"
#endif
#ifndef IS_DEBUG
#define IS_DEBUG  false
#endif

typedef enum LogPriority {
    LOG_UNKNOWN = 0,
    LOG_DEFAULT,
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_SILENT
} LogPriority;


#define LOG_NOOP (void) 0
//__FILE__ 输出文件名
//__LINE__ 输出行数
//__PRETTY_FUNCTION__  输出方法名
//可以按需选取 %s %u %s 分别与之对应

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

#if __linux__
	#define LOG_PRINT(level,fmt,...) __android_log_print(level,LOG_TAG,"(%s:%u:%s) " fmt,filename(__FILE__),__LINE__,__FUNCTION__,##__VA_ARGS__)

#elif __APPLE__
    #define LOG_PRINT(level,fmt,...) printf("(%s:%u:%s) \n" fmt,filename(__FILE__),__LINE__,__FUNCTION__,##__VA_ARGS__)
#endif

//通过IS_DEBUG来控制是否输出日志
#if IS_DEBUG
#define LOGI(fmt,...) LOG_PRINT(LOG_INFO,fmt,##__VA_ARGS__)
#else
#define LOGI(...) LOG_NOOP
#endif

#if IS_DEBUG
#define LOGW(fmt,...) LOG_PRINT(LOG_WARN,fmt ,##__VA_ARGS__)
#else
#define LOGW(...) LOG_NOOP
#endif

#if IS_DEBUG
#define LOGD(fmt,...) LOG_PRINT(LOG_DEBUG,fmt ,##__VA_ARGS__)
#else
#define LOGD(...) LOG_NOOP
#endif

#if IS_DEBUG
#define LOGE(fmt,...) LOG_PRINT(LOG_ERROR,fmt ,##__VA_ARGS__)
#else
#define LOGE(...) LOG_NOOP
#endif

#if IS_DEBUG
#define LOGF(fmt,...) LOG_PRINT(LOG_FATAL,fmt ,##__VA_ARGS__)
#else
#define LOGF(...) LOG_NOOP
#endif


#endif //PROTOSDK_ANDROID_ANDROIDUTILS_H
