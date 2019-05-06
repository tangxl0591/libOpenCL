/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLRun.cpp
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-1
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-1
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "config.h"
#include "OpenCLEnv.h"
#include "OpenCLKernel.h"
#include "OpenCLMem.h"
#include "OpenCLInterface.h"
#include "jpeg.h"
#include "bmp.h"

#define  WIDTH_SIZE		752
#define  HEIGHT_SIZE	480
#define  YUV_FILE		"/data/1.yuv"
#define  KERNEL_PATH	"/data/cvtcolor.cl"

/*************************************************
 Function:		main
 Descroption:	Ö÷³ÌÐò
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
int main(void)
{   
	int i;
	unsigned char * YuvBuf = (unsigned char*)malloc(WIDTH_SIZE*HEIGHT_SIZE);
	unsigned int YuvBufLen;
	unsigned char* RgbBuf = (unsigned char*)malloc(WIDTH_SIZE*HEIGHT_SIZE*4);
    ms_message("**********************************************************");
    ms_message("*                        OpenCL Yuv                      *");
    ms_message("*Version:    %s                                    *",_BUILD_VERSION_);
    ms_message("*Build Time: %s                        *",_BUILD_TIME_);
    ms_message("**********************************************************");
	OpenCLEnv* mOpenCLEnv = new OpenCLEnv();
	if(mOpenCLEnv == NULL)	
	{
		ms_error("OpenCL Env Error");
	}
	
	mOpenCLEnv->Init();

	FILE *fp = fopen(YUV_FILE, "rb");
	if (fp == 0)
	{
		return -1;
	}
	fread(YuvBuf, 1, WIDTH_SIZE*HEIGHT_SIZE, fp);
	fclose(fp);


	OpenCLKernel* mOpenCLKernel = new OpenCLKernel(KERNEL_FILE, (char*)"Gray2RGB", (char*)KERNEL_PATH, strlen(KERNEL_PATH), mOpenCLEnv);

	int dst_step = 0;
	int dst_offset = 0;
	int src_step = 0;
	int src_offset = 0;

	OpenCLMem* mOpenCLMem1 = new OpenCLMem(YuvBufLen, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, YuvBuf, mOpenCLEnv);
	OpenCLMem* mOpenCLMem2 = new OpenCLMem(sizeof(int), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &src_step, mOpenCLEnv);
	OpenCLMem* mOpenCLMem3 = new OpenCLMem(sizeof(int), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &src_offset, mOpenCLEnv);
	OpenCLMem* mOpenCLMem4 = new OpenCLMem(sizeof(int), CL_MEM_READ_WRITE , NULL, mOpenCLEnv);
	OpenCLMem* mOpenCLMem5 = new OpenCLMem(sizeof(int), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &dst_step, mOpenCLEnv);
	OpenCLMem* mOpenCLMem6 = new OpenCLMem(sizeof(int), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, &dst_offset, mOpenCLEnv);

	OpenCLInterface* mOpenCLInterface = new OpenCLInterface(mOpenCLEnv);
	
	cl_mem mCLMem[6];
	mCLMem[0] = mOpenCLMem1->GetOpenCLMem();
	mCLMem[1] = mOpenCLMem2->GetOpenCLMem();
	mCLMem[2] = mOpenCLMem3->GetOpenCLMem();
	mCLMem[3] = mOpenCLMem3->GetOpenCLMem();
	mCLMem[4] = mOpenCLMem3->GetOpenCLMem();
	mCLMem[5] = mOpenCLMem3->GetOpenCLMem();
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  0, sizeof(cl_mem), &(mCLMem[0]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  1, sizeof(cl_mem), &(mCLMem[1]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  2, sizeof(cl_mem), &(mCLMem[2]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  3, sizeof(cl_mem), &(mCLMem[3]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  4, sizeof(cl_mem), &(mCLMem[4]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  5, sizeof(cl_mem), &(mCLMem[5]));

	OpenCLKernelNDR mKernelNDR;
    size_t globalWorkSize[2] = { WIDTH_SIZE, HEIGHT_SIZE };  
    size_t localWorkSize[2] = { 8, 8 };  

    mKernelNDR.kernel = mOpenCLKernel->GetKernel();
    mKernelNDR.workdim = 2;
    mKernelNDR.global_work_offset = NULL;
    mKernelNDR.global_work_size = (const size_t *)globalWorkSize;
    mKernelNDR.local_work_size = (const size_t *)localWorkSize;
    mKernelNDR.num_events_in_wait_list = 0;
    mKernelNDR.event_wait_list = NULL;
    mKernelNDR.event = NULL;

    EnqueueBuffer Buffer;

    Buffer.mMem = mOpenCLMem4->GetOpenCLMem();
    Buffer.blocking_read = CL_TRUE;
    Buffer.offsetsize = 0;
    Buffer.size =(WIDTH_SIZE*HEIGHT_SIZE*3);
    Buffer.ptr = RgbBuf;
    Buffer.num_events_in_wait_list = 0;
    Buffer.event_wait_list = NULL;
    Buffer.event = NULL;

	mOpenCLInterface->OpenClEnqueueNDRangeKernel(&mKernelNDR);
    mOpenCLInterface->OpenCLEnqueueBuf(&Buffer);
    
	delete mOpenCLInterface;
	delete mOpenCLMem1;
	delete mOpenCLMem2;
	delete mOpenCLMem3;
	delete mOpenCLKernel;
	delete mOpenCLEnv;

	if(YuvBuf)
	{
		free(YuvBuf);
		YuvBuf = NULL;
	}

	if(RgbBuf)
	{
		free(RgbBuf);
		RgbBuf = NULL;
	}
    return 0;
}


