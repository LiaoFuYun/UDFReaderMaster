APP_ABI := armeabi-v7a
APP_PLATFORM := android-23
APP_STL := stlport_static

ifeq ($(NDK_DEBUG), 1)
    APP_OPTIM = debug
    APP_CFLAGS = -g -O0
else
    APP_OPTIM = release
    APP_CFLAGS = -O3
endif
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1  -std=c++0x
APP_CPPFLAGS += -fexceptions