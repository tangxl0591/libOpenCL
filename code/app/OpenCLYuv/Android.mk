#
# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

include $(LOCAL_PATH)/../../../jni/OpenCLConfig.mk

JPEG_PATH := $(LOCAL_PATH)/../../external/libjpeg-turbo


LOCAL_C_INCLUDES += \
	$(JNI_H_INCLUDE) \
	$(LOCAL_PATH)/../../include	\
	$(LOCAL_PATH)/../../include/utils	\
	$(LOCAL_PATH)/../../include/core	\
	$(JPEG_PATH)/include	\
	$(JPEG_PATH)/libjpeg-turbo\
	
include $(JPEG_PATH)/Cflags.mk

LOCAL_SRC_FILES := OpenCLYuv.cpp	\

LOCAL_SHARED_LIBRARIES := libmslog libOpenCL_Client libMsUtil 

LOCAL_LDLIBS := -llog 
 
LOCAL_CPPFLAGS := -fpermissive

LOCAL_CFLAGS += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE

LOCAL_MODULE := OpenCLYuv

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)


