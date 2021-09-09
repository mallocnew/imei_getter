LOCAL_PATH:= $(call my-dir)
LOCAL_CPPFLAGS += -std=c++11
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= ../src/hello.cpp
LOCAL_MODULE:= hello
include $(BUILD_EXECUTABLE)