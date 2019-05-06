/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLMem.cpp
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-19
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-19
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "config.h"
#include "OpenCLMem.h"


OpenCLMem::OpenCLMem(int Size,int Flag, void* host, OpenCLEnv* Env)
{
	cl_int err;
	mEnv = Env;
	mOpenCLHandle = Env->GetHandle();
    mContext = Env->GetContext();
	mCLMem = mOpenCLHandle->m_clCreateBuffer(mContext, Flag, Size, host, &err);
}

OpenCLMem::~OpenCLMem()
{
	cl_int err;
	if(NULL != mOpenCLHandle && mOpenCLHandle->m_clReleaseMemObject)
    {
    	err = mOpenCLHandle->m_clReleaseMemObject(mCLMem);
    }
}
