/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLEnv.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-10-31
 Description: 		
 History: 			
 					
   1.Date:	 		2016-10-31
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _OPENCLENV_H_
#define _OPENCLENV_H_

#include "dlopenlib.h"
#include "OpenCLCore.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

class OpenCLEnv
{
public:
    OpenCLEnv();
    ~OpenCLEnv();
    OpenCLHandle * OpenCLGetHandle(){return &mOpenCLHandle;};
    cl_int Init();
    cl_context GetContext(){return mContext;};
    OpenCLHandle * GetHandle(){return &mOpenCLHandle;};
    cl_device_id GetDeviceID(){return mDeviceID;};
    cl_command_queue GetCmdQueue(){return mCmdueue;};

private:
    cl_int CreateContext();
    cl_int ReleaseContext();
    cl_int GetPlatformInfo();
    cl_int GetDevicesInfo(cl_int Devices, cl_int type);
private:
    cl_uint          mDevices;
    
    cl_uint          mDeviceGPU;
    cl_uint          mDeviceCPU;
    cl_platform_id   mPlatformID;
    cl_uint          mNumPlatform;
    cl_device_id     mDeviceID;
    cl_uint          mNumDevice;
    cl_context       mContext;
    cl_command_queue mCmdueue;
    DlOpenLib*       mDlOpenLib;
    OpenCLHandle     mOpenCLHandle;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _OPENCLENV_H_ Edit By Txl 2016-10-31 */

