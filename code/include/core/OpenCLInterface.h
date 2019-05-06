/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLInterface.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-19
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-19
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _OPENCLINTERFACE_H_
#define _OPENCLINTERFACE_H_

#include "config.h"
#include "OpenCLEnv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

class OpenCLInterface
{
public: 
    OpenCLInterface(OpenCLEnv* Env);
    ~OpenCLInterface();
   
    cl_int OpenCLEnqueueBuf(PEnqueueBuffer Buffer);
    cl_int OpenCLSetKernelArg(cl_kernel kernel, cl_uint index, size_t size, const void * arg);
    cl_int OpenClEnqueueNDRangeKernel(POpenCLKernelNDR KernelNDR);

private:
    cl_command_queue mCmdueue;

    OpenCLEnv* mEnv;
    OpenCLHandle* mOpenCLHandle;    
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _OPENCLINTERFACE_H_ Edit By Txl 2016-11-19 */

