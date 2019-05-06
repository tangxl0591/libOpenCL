/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLInterface.cpp
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-19
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-19
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "OpenCLInterface.h"

OpenCLInterface::OpenCLInterface(OpenCLEnv* Env)
{
	mEnv = Env;
	mCmdueue = Env->GetCmdQueue();
	mOpenCLHandle = Env->GetHandle();
}

OpenCLInterface::~OpenCLInterface()
{

}

cl_int OpenCLInterface::OpenCLEnqueueBuf(PEnqueueBuffer Buffer)
{
    cl_int err = CL_DEVICE_NOT_FOUND;
    if(mOpenCLHandle == NULL || NULL == Buffer)
    {
		return CL_DEVICE_NOT_FOUND;
    }

    if(mOpenCLHandle->m_clEnqueueReadBuffer)
	{
        err = mOpenCLHandle->m_clEnqueueReadBuffer(mCmdueue,Buffer->mMem,Buffer->blocking_read,Buffer->offsetsize,
                                                               Buffer->size,Buffer->ptr,Buffer->num_events_in_wait_list,Buffer->event_wait_list,Buffer->event);

        switch(err)
        {
	        case CL_INVALID_COMMAND_QUEUE:
	                ms_message("%s CL_INVALID_COMMAND_QUEUE",__func__);
	                break;
	        case CL_INVALID_CONTEXT:
	                ms_message("%s CL_INVALID_CONTEXT",__func__);
	                break;
	        case CL_INVALID_MEM_OBJECT:
	                ms_message("%s CL_INVALID_MEM_OBJECT",__func__);
	                break;
	        case CL_INVALID_VALUE:
	                ms_message("%s CL_INVALID_VALUE",__func__);
	                break;
	        case CL_INVALID_EVENT_WAIT_LIST:
	                ms_message("%s CL_INVALID_EVENT_WAIT_LIST",__func__);
	                break;
	        case CL_MISALIGNED_SUB_BUFFER_OFFSET:
	                ms_message("%s CL_MISALIGNED_SUB_BUFFER_OFFSET",__func__);
	                break;
	        case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
	                ms_message("%s CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST",__func__);
	                break;
	        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
	                ms_message("%s CL_MEM_OBJECT_ALLOCATION_FAILURE",__func__);
	                break;
	        case CL_OUT_OF_RESOURCES:
	                ms_message("%s CL_OUT_OF_RESOURCES",__func__);
	                break;
	        case CL_OUT_OF_HOST_MEMORY:
	                ms_message("%s CL_OUT_OF_HOST_MEMORY",__func__);
	                break;
	        default:
	                break;
        }
	}

	return CL_SUCCESS;
}

cl_int OpenCLInterface::OpenCLSetKernelArg(cl_kernel kernel, cl_uint index, size_t size, const void * arg)
{
    cl_int err = CL_DEVICE_NOT_FOUND;

    if(mOpenCLHandle == NULL)
    {
    	return CL_DEVICE_NOT_FOUND;
    }

    if(mOpenCLHandle->m_clSetKernelArg)
	{
        err = mOpenCLHandle->m_clSetKernelArg(kernel,index,size,arg);
        if(CL_SUCCESS != err)
        {
        	 ms_error("clSetKernelArg failed: error: %d\n", err);
        }
	}

    return err;
}

cl_int OpenCLInterface::OpenClEnqueueNDRangeKernel(POpenCLKernelNDR KernelNDR)
{
    cl_int err = CL_DEVICE_NOT_FOUND;

    if(mOpenCLHandle == NULL || NULL == KernelNDR)
    {
            return CL_DEVICE_NOT_FOUND;
    }

    if(mOpenCLHandle->m_clEnqueueNDRangeKernel)
	{
        err = mOpenCLHandle->m_clEnqueueNDRangeKernel(mCmdueue,KernelNDR->kernel,KernelNDR->workdim,
                                                                  KernelNDR->global_work_offset,KernelNDR->global_work_size,KernelNDR->local_work_size,
                                                                  KernelNDR->num_events_in_wait_list,KernelNDR->event_wait_list,KernelNDR->event);
        if(CL_SUCCESS != err)
        {
            ms_error("clEnqueueNDRangeKernel failed: error: %d\n", err);
        }
	}

    return err;
}

