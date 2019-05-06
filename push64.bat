adb remount
adb push cl/VectorAdd.cl /data/
adb push libs/arm64-v8a/libMsUtil.so /system/lib64/
adb push libs/arm64-v8a/libOpenCL_Client.so /system/lib64/
adb push libs/arm64-v8a/libmslog.so /system/lib64/
adb push libs/arm64-v8a/OpenCLRun /system/bin 

