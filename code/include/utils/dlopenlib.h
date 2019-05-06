/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		dlopenlib.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-10-30
 Description: 		
 History: 			
 					
   1.Date:	 		2016-10-30
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _DLOPENLIB_H_
#define _DLOPENLIB_H_

#include "config.h"
#include "utils.h"
#include "OpenCLCore.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct
{
    TARGET mTarget;
    PLATFORM_TYPE mPlatform;
    char *filepath;
    struct list_head __list;
}LibPath,*PLibPath;

class DlOpenLib
{
public:
    DlOpenLib();
    ~DlOpenLib();
    void* openlib();
    int addlib(const char* filepath, TARGET target, PLATFORM_TYPE platform);
    TARGET gettarget(){return mTarget;};
    PLATFORM_TYPE getplatform(){return mPlatform;};
private:
    void *mLib = NULL;
    TARGET mTarget;
    PLATFORM_TYPE mPlatform;
    struct list_head mDLFile;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _DLOPEN_H_ Edit By Txl 2016-10-30 */

