/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		utils.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-17
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-17
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _UTILS_H_
#define _UTILS_H_

#include "dlopenlib.h"
#include "OpenCLCore.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************************************
 Function:		GetPlatformFromName
 Descroption:	 
 Input: 
	1.*name
 Output: 
 Return: 	
 Other:  
*************************************************/
PLATFORM_TYPE GetPlatformFromName(char *name);

/*************************************************
 Function:		GetPlatformFromType
 Descroption:	 
 Input: 
	1.platform
 Output: 
 Return: 	
 Other:  
*************************************************/
char *GetPlatformFromType(PLATFORM_TYPE platform);

/*************************************************
 Function:		ReadFile
 Descroption:	 
 Input: 
	1.filename
	2.char** buf
	3.len
 Output: 
 Return: 	
 Other:  
*************************************************/
int ReadFile(char* filename, unsigned char** buf, int* len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _UTILS_H_ Edit By Txl 2016-11-17 */

