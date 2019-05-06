/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		jpeg.cpp
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-12-7
 Description: 		
 History: 			
 					
   1.Date:	 		2016-12-7
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "jpeg.h"

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
int CreateJPEG(unsigned char* data, int w, int h, int quality, const char* outfilename, unsigned char optimize, unsigned int Component) 
{
    int nComponent = Component;
    struct jpeg_compress_struct jcs;
	struct jpeg_error_mgr jerr;
	
	jcs.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&jcs);

	FILE* f = fopen(outfilename, "wb");
    if (f == NULL) {
        return -1;
    }

    jpeg_stdio_dest(&jcs, f);
    jcs.image_width = w;
    jcs.image_height = h;
    jcs.arith_code = false;
    jcs.input_components = nComponent;
    if (nComponent == 1)
    {
    	jcs.in_color_space = JCS_GRAYSCALE;
	}
    else
    {
    	jcs.in_color_space = JCS_EXT_RGBA;
	}
    jpeg_set_defaults(&jcs);
    jcs.optimize_coding = optimize;
    jpeg_set_quality(&jcs, quality, true);
    jpeg_start_compress(&jcs, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride;
    row_stride = jcs.image_width * nComponent;
    while (jcs.next_scanline < jcs.image_height) {
        row_pointer[0] = &data[jcs.next_scanline * row_stride];
        jpeg_write_scanlines(&jcs, row_pointer, 1);
    }

    jpeg_finish_compress(&jcs);
    jpeg_destroy_compress(&jcs);
    fclose(f);
    return 0;
}
