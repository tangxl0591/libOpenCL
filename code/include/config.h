/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		config.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-10-8
 Description: 		
 History: 			
 					
   1.Date:	 		2015-10-8
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <dlfcn.h>

#include "Types.h"
#include "list.h"
#include "mslog.h"
#include <dlfcn.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define _BUILD_VERSION_     "V1.00.01"
#define _BUILD_TIME_        __DATE__ " " __TIME__

#define ms_malloc       malloc
#define ms_free         free


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _CONFIG_H_ Edit By Txl 2015-10-8 */

