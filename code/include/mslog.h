/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		mslog.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-10-30
 Description: 		
 History: 			
 					
   1.Date:	 		2016-10-30
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _MSLOG_H_
#define _MSLOG_H_

#include <stdio.h>
#include <string.h>

#ifdef _ANDROID_
#include <android/log.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#undef   LOG_TAG  
#define  LOG_TAG        "OpenCL"

#define LOG_BUF_SIZE     1024

typedef enum
{
    LOG_DEBUG     = 1,
    LOG_MESSAGE   = 1<<2,    
    LOG_ERROR     = 1<<3,
    LOG_WARING    = 1<<4,
    LOG_FILE      = 1<<5,
}LogLevel;

typedef void (*MSLogFunc)(LogLevel lev, const char *fmt, va_list args);

typedef struct
{
    LogLevel mCLLogMask;
    MSLogFunc mCLLogFunc;
    int mCLLogFile;
}MSLog,*PMSLog;

/*************************************************
 Function:		ms_log_open
 Descroption:	 
 Input: 
	1.level
	2.Func
	3.filepath
 Output: 
 Return: 	
 Other:  
*************************************************/
void ms_log_open(LogLevel level, MSLogFunc Func, char* filepath);

/*************************************************
 Function:		ms_log_close
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void ms_log_close(void);

/*************************************************
 Function:		ms_log_setlevel
 Descroption:	 
 Input: 
	1.level
 Output: 
 Return: 	
 Other:  
*************************************************/
void ms_log_setlevel(LogLevel level);

/*************************************************
 Function:		ms_log_getlevel
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
LogLevel ms_log_getlevel(void);

/*************************************************
 Function:		ms_log_file
 Descroption:	 
 Input: 
	1.level
	2.char *fmt
	3.
 Output: 
 Return: 	
 Other:  
*************************************************/
void ms_log_file(LogLevel level,const char *fmt, ...);

#ifdef _LINUX_
#define cl_message(...) \
        ms_log_file(LOG_MESSAGE,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_MESSAGE)  {printf("["LOG_TAG"]: "__VA_ARGS__);printf("\n");}

#define cl_debug(...) \
        ms_log_file(LOG_DEBUG,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_DEBUG)  {printf("["LOG_TAG"]: "__VA_ARGS__);printf("\n");}      

#define cl_waring(...) \
        ms_log_file(LOG_WARING,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_WARING)  {printf("["LOG_TAG"]: "__VA_ARGS__);printf("\n");}           

#define cl_error(...) \
        ms_log_file(LOG_ERROR,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_ERROR)  {printf("["LOG_TAG"]: "__VA_ARGS__);printf("\n");}     
#endif

#ifdef _ANDROID_   
#define ms_message(...) \
        ms_log_file(LOG_MESSAGE,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_MESSAGE) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define ms_debug(...) \
        ms_log_file(LOG_DEBUG,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_DEBUG) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)        

#define ms_waring(...) \
        ms_log_file(LOG_WARING,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_WARING) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)            

#define ms_error(...) \
        ms_log_file(LOG_ERROR,__VA_ARGS__);\
        if(ms_log_getlevel()&LOG_ERROR) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)            
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _LOGUTILS_H_ Edit By Txl 2016-10-30 */

