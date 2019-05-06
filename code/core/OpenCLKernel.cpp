/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLKernel.cpp
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
#include "OpenCLKernel.h"

OpenCLKernel::OpenCLKernel(KernelType Type, char* Name, char* Source, int SourceLen, OpenCLEnv* Env)
:isSchedulerEnabled(0)
,kernel(NULL)
{
	cl_int err = CL_DEVICE_NOT_FOUND;
	char* KernelBuf = NULL;
	size_t KernelLen = 0;
	cl_program curClProgram = NULL;
	
	memset(KenrelName, 0, sizeof(KenrelName));
	sprintf(KenrelName, "%s", Name);
	mEnv = Env;
	mOpenCLHandle = Env->GetHandle();
    mContext = Env->GetContext();
	mDeviceID = Env->GetDeviceID(); 
	memset(programBuildOptions, 0, sizeof(programBuildOptions));
	switch(Type)
	{
	    case KERNEL_BIN:
			ms_debug("OpenCLKernel [KERNEL_BIN]");
	 		KernelBuf = LoadProgramSource((const char *)Source, &KernelLen);
			curClProgram = CreateProgramWithBinary(&KernelBuf);
	        break;
	    
	    case KERNEL_FILE:
			ms_debug("OpenCLKernel [KERNEL_FILE]");
	 		KernelBuf = LoadProgramSource((const char *)Source, &KernelLen);	 
			curClProgram = CreateProgramWithSource(&KernelBuf);
	        break;
	    
	    case KERNEL_SOURCE:
			ms_debug("OpenCLKernel [KERNEL_SOURCE]");
			curClProgram = CreateProgramWithSource(&Source);
	        break;
	    
	    default:
	        break;
	}

	if(KernelBuf != NULL)
	{
		free(KernelBuf);
		KernelBuf = NULL;
	}

	if(curClProgram != NULL)
	{
		err = BuildProgram(curClProgram);
	}
}

OpenCLKernel::~OpenCLKernel()
{
	if(mOpenCLHandle->m_clReleaseKernel)
    {
    	mOpenCLHandle->m_clReleaseKernel(kernel);
    }
}

cl_program OpenCLKernel::CreateProgramWithSource(char** Source)
{
	cl_program curClProgram = NULL;
    cl_int err = CL_DEVICE_NOT_FOUND;

	if(mOpenCLHandle->m_clCreateProgramWithSource)
    {
        curClProgram = mOpenCLHandle->m_clCreateProgramWithSource(mContext, 1, (const char**)Source, NULL, &err);
        if(CL_SUCCESS != err)
        {
        	ms_error("clCreateProgramWithSource failed: error: %d\n", err);
        }
        else
        {
         	ms_message("clCreateProgramWithSource success: %d\n", err);
        }
    }

	return curClProgram;
}

cl_program OpenCLKernel::CreateProgramWithBinary(char** Source)
{
	cl_program curClProgram = NULL;
    cl_int err = CL_DEVICE_NOT_FOUND;
	size_t szKernelLength; 
	
	if(mOpenCLHandle->m_clCreateProgramWithSource)
    {
        curClProgram = mOpenCLHandle->m_clCreateProgramWithBinary(mContext, 1, &mDeviceID, (const size_t *)&szKernelLength, (const unsigned char**)Source, NULL, &err);
		
        if(CL_SUCCESS != err)
        {
        	ms_error("clCreateProgramWithSource failed: error: %d\n", err);
        }
        else
        {
         	ms_message("clCreateProgramWithSource success: %d\n", err);
        }
    }

	return curClProgram;
}

cl_int OpenCLKernel::BuildProgram(cl_program curClProgram)
{
	cl_int err = CL_DEVICE_NOT_AVAILABLE;
	cl_int buildStatus;
	
    if(mOpenCLHandle->m_clBuildProgram)
    {
        err = mOpenCLHandle->m_clBuildProgram(curClProgram, 0, NULL, programBuildOptions, NULL, NULL);
        if(CL_SUCCESS != err)
        {
            char programLog[2048];
            if(mOpenCLHandle->m_clGetProgramBuildInfo)
            {
            	mOpenCLHandle->m_clGetProgramBuildInfo(curClProgram, mDeviceID, CL_PROGRAM_BUILD_LOG, sizeof(programLog), programLog, 0);
            }
            ms_error("clBuildProgram error [%d] [%s]",err,programLog);
            goto error;
        }
    }

    if(mOpenCLHandle->m_clGetProgramBuildInfo)
    {
        mOpenCLHandle->m_clGetProgramBuildInfo(curClProgram, mDeviceID, CL_PROGRAM_BUILD_STATUS, sizeof(buildStatus), &buildStatus, NULL);
    }

    if(buildStatus != CL_BUILD_SUCCESS)
    {
        ms_error("The program is not built (buildStatus) [%d], Line %u in file %s !!!\n", buildStatus, __LINE__, __FILE__);
        goto error;
    }

    kernel = 0;
    localMemory = 0;
    WGsize = 0;
    compiler_WGsize[0] = 0;
    compiler_WGsize[1] = 0;
    compiler_WGsize[2] = 0;

	if(mOpenCLHandle->m_clCreateKernel)
    {
        kernel = mOpenCLHandle->m_clCreateKernel(curClProgram, KenrelName, &err);
        if(CL_SUCCESS != err)
        {
            switch(err)
            {
                case CL_INVALID_PROGRAM:
                        ms_error("CL_INVALID_PROGRAM");
                        break;
                case CL_INVALID_PROGRAM_EXECUTABLE:
                        ms_error("CL_INVALID_PROGRAM_EXECUTABLE");
                        break;
                case CL_INVALID_KERNEL_NAME:
                        ms_error("CL_INVALID_KERNEL_NAME");
                        break;
                case CL_INVALID_KERNEL_DEFINITION:
                        ms_error("CL_INVALID_KERNEL_DEFINITION");
                        break;
                case CL_INVALID_VALUE:
                        ms_error("CL_INVALID_VALUE");
                        break;
                case CL_OUT_OF_RESOURCES:
                        ms_error("CL_OUT_OF_RESOURCES");
                        break;
                case CL_OUT_OF_HOST_MEMORY:
                        ms_error("CL_OUT_OF_HOST_MEMORY");
                        break;

                default:
                        break;
            }
            ms_error("clCreateKernel error [%d]",err);
        }
    }

    if(mOpenCLHandle->m_clGetKernelWorkGroupInfo)
    {
        err = mOpenCLHandle->m_clGetKernelWorkGroupInfo(kernel,
                                                                mDeviceID,
                                                                CL_KERNEL_WORK_GROUP_SIZE,
                                                                sizeof( WGsize ),
                                                                &(WGsize), NULL );
    }

    if(mOpenCLHandle->m_clGetKernelWorkGroupInfo)
    {
        err = mOpenCLHandle->m_clGetKernelWorkGroupInfo(kernel,
                                                                mDeviceID,
                                                                CL_KERNEL_LOCAL_MEM_SIZE,
                                                                sizeof(localMemory ),
                                                                &(localMemory), NULL );
    }

    if(mOpenCLHandle->m_clGetKernelWorkGroupInfo)
    {
        err = mOpenCLHandle->m_clGetKernelWorkGroupInfo(kernel,
                                                                mDeviceID,
                                                                CL_KERNEL_COMPILE_WORK_GROUP_SIZE,
                                                                3 * sizeof(size_t),
                                                                &(compiler_WGsize), NULL );
    }

error:
	return err;
}


char * OpenCLKernel::LoadProgramSource(const char *cFilename, size_t *finalLength)
{
    FILE* pFileStream = NULL;
    size_t sourceLength;

    if((pFileStream = fopen(cFilename, "rb")) == NULL)
    {
            return NULL;
    }

    fseek(pFileStream, 0, SEEK_END);
    sourceLength = ftell(pFileStream);
    fseek(pFileStream, 0, SEEK_SET);

    char* cSourceString = (char *)malloc(sourceLength + 1);

    if(NULL == cSourceString)
    {
            fclose(pFileStream);
            return 0;
    }
    if (fread((cSourceString), sourceLength, 1, pFileStream) != 1)
    {
            fclose(pFileStream);
            free(cSourceString);
            return 0;
    }

    fclose(pFileStream);
    if(finalLength != 0)
    {
            *finalLength = sourceLength;
    }
    cSourceString[sourceLength] = '\0';

    return cSourceString;
}
