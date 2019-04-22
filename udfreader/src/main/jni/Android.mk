LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := udfread
LOCAL_SRC_FILES := udfclip.c default_blockinput.c ecma167.c udfread.c udfread-version.c

LOCAL_LDLIBS    += -llog

LOCAL_C_INCLUDES += $(LOCAL_PATH)

include $(BUILD_SHARED_LIBRARY)