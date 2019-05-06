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
    ms_message("**********************************************************");
    ms_message("*                        OpenCL Core                     *");
    ms_message("*Version:    %s                                    *",_BUILD_VERSION_);
    ms_message("*Build Time: %s                        *",_BUILD_TIME_);
    ms_message("**********************************************************");

	OpenCLEnv* mOpenCLEnv = new OpenCLEnv();
	if(mOpenCLEnv == NULL)	
	{
		ms_error("OpenCL Env Error");
	}
	
	mOpenCLEnv->Init();
	OpenCLKernel* mOpenCLKernel = new OpenCLKernel(KERNEL_FILE, (char*)"VectorAdd", (char*)"/data/VectorAdd.cl", strlen("/data/VectorAdd.cl"), mOpenCLEnv);
	
	const int ARRAY_SIZE = 20000;      
    float result[ARRAY_SIZE];  
    float a[ARRAY_SIZE];  
    float b[ARRAY_SIZE];  
    for(i=0; i<ARRAY_SIZE; i++)  
    {  
        a[i] = i*1.0;  
        b[i] = i*2.0; 
        result[i] = 0;
    }  

	OpenCLMem* mOpenCLMem1 = new OpenCLMem(ARRAY_SIZE*sizeof(float), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, a, mOpenCLEnv);
	OpenCLMem* mOpenCLMem2 = new OpenCLMem(ARRAY_SIZE*sizeof(float), CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, b, mOpenCLEnv);
	OpenCLMem* mOpenCLMem3 = new OpenCLMem(ARRAY_SIZE*sizeof(float), CL_MEM_READ_WRITE, NULL, mOpenCLEnv);

	OpenCLInterface* mOpenCLInterface = new OpenCLInterface(mOpenCLEnv);
	
	cl_mem mCLMem[3];
	mCLMem[0] = mOpenCLMem1->GetOpenCLMem();
	mCLMem[1] = mOpenCLMem2->GetOpenCLMem();
	mCLMem[2] = mOpenCLMem3->GetOpenCLMem();
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  0, sizeof(cl_mem), &(mCLMem[0]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  1, sizeof(cl_mem), &(mCLMem[1]));
	mOpenCLInterface->OpenCLSetKernelArg(mOpenCLKernel->GetKernel(),  2, sizeof(cl_mem), &(mCLMem[2]));

	OpenCLKernelNDR mKernelNDR;
    size_t globalWorkSize[2] = { 200, 100  };  
    size_t localWorkSize[2] = { 8, 8 };  

    mKernelNDR.kernel = mOpenCLKernel->GetKernel();
    mKernelNDR.workdim = 1;
    mKernelNDR.global_work_offset = NULL;
    mKernelNDR.global_work_size = (const size_t *)globalWorkSize;
    mKernelNDR.local_work_size = (const size_t *)localWorkSize;
    mKernelNDR.num_events_in_wait_list = 0;
    mKernelNDR.event_wait_list = NULL;
    mKernelNDR.event = NULL;

    EnqueueBuffer Buffer;

    Buffer.mMem = mOpenCLMem3->GetOpenCLMem();
    Buffer.blocking_read = CL_TRUE;
    Buffer.offsetsize = 0;
    Buffer.size = ARRAY_SIZE * sizeof(float);
    Buffer.ptr = result;
    Buffer.num_events_in_wait_list = 0;
    Buffer.event_wait_list = NULL;
    Buffer.event = NULL;

	mOpenCLInterface->OpenClEnqueueNDRangeKernel(&mKernelNDR);
    mOpenCLInterface->OpenCLEnqueueBuf(&Buffer);
    
    for (i = 0 ; i < 32; i++)
    {
        ms_message("result[%d] = [%f]",i,result[i]);
    }

	delete mOpenCLInterface;
	delete mOpenCLMem1;
	delete mOpenCLMem2;
	delete mOpenCLMem3;
	delete mOpenCLKernel;
	delete mOpenCLEnv;
		
    return 0;
}


