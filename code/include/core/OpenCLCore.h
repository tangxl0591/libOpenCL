/*********************************************************
 Copyright (C),2013-2019,Electronic Technology Co.,Ltd.
 File name: 		OpenCLCore.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2016-10-31
 Description: 		
 History: 			
 					
   1.Date:	 		2016-10-31
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _OPENCLCORE_H_
#define _OPENCLCORE_H_

#include <CL/cl.h>
#include <CL/opencl.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define ADRENO_NAME                     "QUALCOMM"
#define MALI_NAME                       "ARM"

#define _CL_GETPLATFORMIDS_             "clGetPlatformIDs"
#define _CL_GETPLATFORMINFO_            "clGetPlatformInfo"
#define _CL_GETDEVICEIDS_               "clGetDeviceIDs"
#define _CL_GETDEVICEINFO_              "clGetDeviceInfo"
#define _CL_CREATECONTEXT_              "clCreateContext"
#define _CL_RELEASECONTEXT_             "clReleaseContext"
#define _CL_CREATECOMMANDQUEUE_         "clCreateCommandQueue"
#define _CL_RELEASECOMMANDQUEUE_        "clReleaseCommandQueue"
#define _CL_CREATEPROGRAMWITHSOURCE_    "clCreateProgramWithSource"
#define _CL_CREATEPROGRAMWITHBIN_       "clCreateProgramWithBinary"
#define _CL_RELEASEPROGRAM_             "clReleaseProgram"
#define _CL_GETPROGRAMINFO_             "clGetProgramBuildInfo"
#define _CL_BUILDPROGRAM_               "clBuildProgram"
#define _CL_CREATEKERNEL_               "clCreateKernel"
#define _CL_RELEASEKERNEL_              "clReleaseKernel"
#define _CL_GETKERNELWORKGROUP_         "clGetKernelWorkGroupInfo"
#define _CL_SETKERNELARG_               "clSetKernelArg"
#define _CL_SETKERNELINFO_              "clGetKernelInfo"
#define _CL_CREATEBUFFER_               "clCreateBuffer"
#define _CL_RELEASEMEMOBJ_              "clReleaseMemObject"
#define _CL_ENQUEUENDRKERNEL_           "clEnqueueNDRangeKernel"
#define _CL_ENQUEUEREADBUFFER_          "clEnqueueReadBuffer"
#define _CL_CREATECONTEXTFORMTYPE_      "clCreateContextFromType"

typedef enum
{
    PLATFORM_UNKNOW = 0x00,
    PLATFORM_ADRENO = 0x01,    
    PLATFORM_MAIL   = 0x02,
}PLATFORM_TYPE;

typedef enum
{
    TARGET_UNKNOW  = 0,
    TARGET_BIT32   = 32,
    TARGET_BIT64   = 64,
}TARGET;

typedef enum
{
    KERNEL_BIN      = 0x00,
    KERNEL_FILE     = 0x01,    
    KERNEL_SOURCE   = 0x02,
}KernelType;

typedef struct
{
    void* mHandle;
    cl_int (*m_clGetPlatformIDs)(cl_uint          /* num_entries */,
                                 cl_platform_id * /* platforms */,
                                 cl_uint *        /* num_platforms */)CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clGetPlatformInfo)(cl_platform_id   /* platform */, 
                                  cl_platform_info /* param_name */,
                                  size_t           /* param_value_size */, 
                                  void *           /* param_value */,
                                  size_t *         /* param_value_size_ret */)CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clGetDeviceIDs)(cl_platform_id   /* platform */,
                               cl_device_type   /* device_type */, 
                               cl_uint          /* num_entries */, 
                               cl_device_id *   /* devices */, 
                               cl_uint *        /* num_devices */);

    cl_int (*m_clGetDeviceInfo)(cl_device_id    /* device */,
                                cl_device_info  /* param_name */, 
                                size_t          /* param_value_size */, 
                                void *          /* param_value */,
                                size_t *        /* param_value_size_ret */)CL_API_SUFFIX__VERSION_1_0;

    cl_context (*m_clCreateContext)(const cl_context_properties * /* properties */,
                                    cl_uint                 /* num_devices */,
                                    const cl_device_id *    /* devices */,
                                    void (CL_CALLBACK * /* pfn_notify */)(const char *, const void *, size_t, void *),
                                    void *                  /* user_data */,
                                    cl_int *                /* errcode_ret */)CL_API_SUFFIX__VERSION_1_0;

    cl_context (*m_clCreateContextFromType)(const cl_context_properties * /* properties */,
                        cl_device_type          /* device_type */,
                        void (CL_CALLBACK *     /* pfn_notify*/ )(const char *, const void *, size_t, void *),
                        void *                  /* user_data */,
                        cl_int *                /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clReleaseContext)(cl_context /* context */);

    cl_command_queue (*m_clCreateCommandQueue)(cl_context                     /* context */, 
                                               cl_device_id                   /* device */, 
                                               cl_command_queue_properties    /* properties */,
                                               cl_int *                       /* errcode_ret */)CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clReleaseCommandQueue)(cl_command_queue /* command_queue */);

    cl_program (*m_clCreateProgramWithSource)(cl_context        /* context */,
                                              cl_uint           /* count */,
                                              const char **     /* strings */,
                                              const size_t *    /* lengths */,
                                              cl_int *          /* errcode_ret */)CL_API_SUFFIX__VERSION_1_0;

    cl_program (*m_clCreateProgramWithBinary)(cl_context                     /* context */,
                                              cl_uint                        /* num_devices */,
                                              const cl_device_id *           /* device_list */,
                                              const size_t *                 /* lengths */,
                                              const unsigned char **         /* binaries */,
                                              cl_int *                       /* binary_status */,
                                              cl_int *                       /* errcode_ret */)CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clReleaseProgram)(cl_program /* program */)CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clGetProgramBuildInfo)(cl_program            /* program */,
                                      cl_device_id          /* device */,
                                      cl_program_build_info /* param_name */,
                                      size_t                /* param_value_size */,
                                      void *                /* param_value */,
                                      size_t *              /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clBuildProgram)(cl_program           /* program */,
                               cl_uint              /* num_devices */,
                               const cl_device_id * /* device_list */,
                               const char *         /* options */, 
                               void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
                               void *               /* user_data */) CL_API_SUFFIX__VERSION_1_0;
    
    cl_kernel (*m_clCreateKernel)(cl_program      /* program */,
                                  const char *    /* kernel_name */,
                                  cl_int *        /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clReleaseKernel)(cl_kernel   /* kernel */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clGetKernelWorkGroupInfo)(cl_kernel                  /* kernel */,
                                         cl_device_id               /* device */,
                                         cl_kernel_work_group_info  /* param_name */,
                                         size_t                     /* param_value_size */,
                                         void *                     /* param_value */,
                                         size_t *                   /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clSetKernelArg)(cl_kernel    /* kernel */,
                               cl_uint      /* arg_index */,
                               size_t       /* arg_size */,
                               const void * /* arg_value */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clGetKernelInfo)(cl_kernel       /* kernel */,
                                cl_kernel_info  /* param_name */,
                                size_t          /* param_value_size */,
                                void *          /* param_value */,
                                size_t *        /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;   

    cl_mem (*m_clCreateBuffer)(cl_context   /* context */,
                               cl_mem_flags /* flags */,
                               size_t       /* size */,
                               void *       /* host_ptr */,
                               cl_int *     /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clReleaseMemObject)(cl_mem /* memobj */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clEnqueueNDRangeKernel)(cl_command_queue /* command_queue */,
                                       cl_kernel        /* kernel */,
                                       cl_uint          /* work_dim */,
                                       const size_t *   /* global_work_offset */,
                                       const size_t *   /* global_work_size */,
                                       const size_t *   /* local_work_size */,
                                       cl_uint          /* num_events_in_wait_list */,
                                       const cl_event * /* event_wait_list */,
                                       cl_event *       /* event */) CL_API_SUFFIX__VERSION_1_0;

    cl_int (*m_clEnqueueReadBuffer)(cl_command_queue    /* command_queue */,
                                    cl_mem              /* buffer */,
                                    cl_bool             /* blocking_read */,
                                    size_t              /* offset */,
                                    size_t              /* size */, 
                                    void *              /* ptr */,
                                    cl_uint             /* num_events_in_wait_list */,
                                    const cl_event *    /* event_wait_list */,
                                    cl_event *          /* event */) CL_API_SUFFIX__VERSION_1_0;

    
}OpenCLHandle,*POpenCLHandle;

typedef struct
{
    unsigned int Type;
    unsigned int ID;
    const char *Name;
}CLDeviceInfo;

typedef struct
{
    cl_kernel kernel;
    int workdim;
    const size_t * global_work_offset;
    const size_t * global_work_size;
    const size_t * local_work_size;
    cl_uint        num_events_in_wait_list;
    const cl_event * event_wait_list;
    cl_event * event;
}OpenCLKernelNDR,*POpenCLKernelNDR;

typedef struct
{
    cl_mem   mMem;
    cl_bool  blocking_read;
    size_t   offsetsize;
    size_t   size;
    void *   ptr;
    cl_uint  num_events_in_wait_list;
    const cl_event * event_wait_list;
    cl_event * event;
}EnqueueBuffer,*PEnqueueBuffer;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _OPENCLCORE_H_ Edit By Txl 2016-10-31 */

