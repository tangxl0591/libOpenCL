/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		mslog.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-10-30
 Description: 		
 History: 			
 					
   1.Date:	 		2016-10-30
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "config.h"
#include "mslog.h"

static MSLog mMSLog = 
{
    .mCLLogMask = LOG_MESSAGE|LOG_DEBUG|LOG_ERROR|LOG_WARING,
    .mCLLogFunc = NULL,
    .mCLLogFile = 0,
};

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
void ms_log_open(LogLevel level, MSLogFunc Func, char* filepath)
{
    mMSLog.mCLLogMask = level;
    mMSLog.mCLLogFunc = Func;
    if(NULL != filepath)
    {
        #ifdef _ANDROID_
        mMSLog.mCLLogFile = open(filepath, O_CREAT|O_RDWR|O_APPEND,0666);
        mMSLog.mCLLogMask |= LOG_FILE;
        #endif
    }
}

/*************************************************
 Function:		ms_log_close
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void ms_log_close(void)
{
    if(mMSLog.mCLLogFile)
    {
        close(mMSLog.mCLLogFile);
        mMSLog.mCLLogFile = 0;
    }

    mMSLog.mCLLogFunc = 0;
}

/*************************************************
 Function:		ms_log_setlevel
 Descroption:	 
 Input: 
	1.level
 Output: 
 Return: 	
 Other:  
*************************************************/
void ms_log_setlevel(LogLevel level)
{
    mMSLog.mCLLogMask = level;
}

/*************************************************
 Function:		ms_log_getlevel
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
LogLevel ms_log_getlevel(void)
{
    return mMSLog.mCLLogMask;
}

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
void ms_log_file(LogLevel level,const char *fmt, ...)
{
    if((level&mMSLog.mCLLogMask) && (LOG_FILE&mMSLog.mCLLogMask))
    {
        va_list ap;
        char buf[LOG_BUF_SIZE];
        int len = 0;

        va_start(ap, fmt);
        vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);
        len = strlen(buf);
        if(buf[len-1] != '\n')
        {
            buf[len++] = '\n';
        }
        va_end(ap);
        if(mMSLog.mCLLogFile != 0)
        {
            write(mMSLog.mCLLogFile, buf, len);
        }
    }
}
