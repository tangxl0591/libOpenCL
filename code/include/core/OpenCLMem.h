/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLMem.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-19
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-19
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _OPENCLMEM_H_
#define _OPENCLMEM_H_

#include "OpenCLEnv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

class OpenCLMem
{
public:
    OpenCLMem(int Size,int Flag, void* host, OpenCLEnv* Env);
    ~OpenCLMem();
    cl_mem GetOpenCLMem(){return mCLMem;};

    private:
        cl_mem  mCLMem;
        OpenCLEnv* mEnv;
        OpenCLHandle* mOpenCLHandle;
        cl_context   mContext;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _OPENCLMEM_H_ Edit By Txl 2016-11-19 */

