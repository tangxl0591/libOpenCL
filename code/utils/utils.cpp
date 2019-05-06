/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		utils.cpp
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-11-17
 Description: 		
 History: 			
 					
   1.Date:	 		2016-11-17
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include <string.h>
#include <stdint.h>  
#include <string.h>
#include <fcntl.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "utils.h"

/*************************************************
 Function:		GetPlatformFromName
 Descroption:	 
 Input: 
	1.*name
 Output: 
 Return: 	
 Other:  
*************************************************/
PLATFORM_TYPE GetPlatformFromName(char *name)
{
	if(0 == strcmp(name, ADRENO_NAME))
	{
		return PLATFORM_ADRENO;
	}
	else if(0 == strcmp(name, MALI_NAME))
	{
		return PLATFORM_MAIL;
	}

	return PLATFORM_UNKNOW;
}

/*************************************************
 Function:		GetPlatformFromType
 Descroption:	 
 Input: 
	1.platform
 Output: 
 Return: 	
 Other:  
*************************************************/
char* GetPlatformFromType(PLATFORM_TYPE platform)
{
	if(platform == PLATFORM_ADRENO)
	{
		return (char*)ADRENO_NAME;
	}
	else if (platform == PLATFORM_MAIL)
	{
		return (char*)MALI_NAME;
	}

	return (char*)"Unknow";
}

/*************************************************
 Function:		get_file_size
 Descroption:	
 Input: 
	1.*path
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned long get_file_size(char *path)
{
    unsigned long filesize = 0;
    struct stat statbuff;

    if(stat(path, &statbuff) < 0)
    {
        return filesize;
    }
    else
    {
        filesize = statbuff.st_size;
    }

    return filesize;     
}

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
int ReadFile(char* filename, unsigned char** buf, int* len)
{
	*len = get_file_size(filename);

	if (*len == 0)
	{
		return -1;
	}

	FILE *fp = fopen(filename, "rb");
	if (fp == 0)
	{
		*len = 0;
		return -1;
	}
	*buf = (unsigned char*)malloc((*len)+1);
	fread(*buf, 1, *len, fp);
	fclose(fp);
	return 0;
}


