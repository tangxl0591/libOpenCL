/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		jpeg.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-12-9
 Description: 		
 History: 			
 					
   1.Date:	 		2016-12-9
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _JPEG_H_
#define _JPEG_H_

#include "config.h"
#include "jpeglib.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************************************
 Function:		CreateJPEG
 Descroption:	  
 Input: 
	1.char* data
	2.w
	3.h
	4.quality
	5.char* outfilename
	6.char optimize
	7.int Component
 Output: 
 Return: 	
 Other:  
*************************************************/
int CreateJPEG(unsigned char* data, int w, int h, int quality, const char* outfilename, unsigned char optimize, unsigned int Component);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _JPEG_H_ Edit By Txl 2016-12-9 */

