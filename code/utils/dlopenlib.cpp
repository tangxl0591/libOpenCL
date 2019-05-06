/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		dlopenlib.cpp
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
#include "dlopenlib.h"
#include <CL/opencl.h>

/*************************************************
 Function:		DlOpenLib.DlOpenLib
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
DlOpenLib::DlOpenLib()
{
	mDLFile.next = &mDLFile;
	mDLFile.prev = &mDLFile;
}

/*************************************************
 Function:		DlOpenLib.~DlOpenLib
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
DlOpenLib::~DlOpenLib()
{
	struct list_head *codenode,*pnode;  
    LibPath* mLibPath = NULL;
	if(!list_empty(&mDLFile))
    {
    	list_for_each_safe(codenode, pnode, &mDLFile)
	    {            
	        mLibPath = container_of(codenode, LibPath,__list);    
	        list_del(&mLibPath->__list);
	        if(NULL != mLibPath->filepath)
			{
				ms_free(mLibPath->filepath);
				mLibPath->filepath = NULL;
			}

			if(NULL != mLibPath )
			{
				ms_free(mLibPath );
				mLibPath  = NULL;
			}
	    }
    }
}

/*************************************************
 Function:		DlOpenLib.openlib
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void* DlOpenLib::openlib()
{
	struct list_head *codenode,*pnode;  
    LibPath* mLibPath = NULL;

	if(NULL != mLib)
	{
		return mLib;
	}
	
	if(list_empty(&mDLFile))
    {
    	return NULL;
    }

	list_for_each_safe(codenode, pnode, &mDLFile)
    {            
        mLibPath = node_to_item(codenode, LibPath,__list);   
		if(mLibPath == NULL)
		{
			break;
		}

        mLib = dlopen(mLibPath->filepath, RTLD_LAZY);  
		if(mLib != NULL)
		{
			mTarget = mLibPath->mTarget;
			mPlatform = mLibPath->mPlatform;
			break;
		}
    }
	
	ms_message("Found Library [%s]",mLibPath->filepath);
	return mLib;
}

/*************************************************
 Function:		DlOpenLib.addlib
 Descroption:	 
 Input: 
	1.char* filepath
	2.target
	3.platform
 Output: 
 Return: 	
 Other:  
*************************************************/
int DlOpenLib::addlib(const char* filepath, TARGET target, PLATFORM_TYPE platform)
{
	int ret = CL_SUCCESS;
	if(NULL == filepath)
	{
		return CL_DEVICE_NOT_FOUND;
	}

	int len = strlen((const char*)filepath);

	PLibPath mPLibPath = (PLibPath)ms_malloc(sizeof(LibPath));
	if(NULL == mPLibPath)
	{
		ret = CL_DEVICE_NOT_FOUND;
		goto Error;
	}

	mPLibPath->filepath = (char*)ms_malloc(len+1);
	if(NULL == mPLibPath->filepath)
	{
		ret = CL_DEVICE_NOT_FOUND;
		goto Error;
	}
	memcpy(mPLibPath->filepath,filepath,len);
	mPLibPath->mTarget = target;
	mPLibPath->mPlatform = platform;
	ms_debug("%s [%d] [%s]",__func__,mPLibPath->mTarget ,mPLibPath->filepath);
	list_add(&mPLibPath->__list, &mDLFile);

	return ret;
Error:
	if(NULL != mPLibPath->filepath)
	{
		ms_free(mPLibPath->filepath);
		mPLibPath->filepath = NULL;
	}

	if(NULL != mPLibPath )
	{
		ms_free(mPLibPath );
		mPLibPath  = NULL;
	}

	return ret;
}
