
include(../../QSanguosha.pri)
CONFIG(systemlua): TEMPLATE = aux
else {
CONFIG -= qt

TEMPLATE = lib
winrt|ios: CONFIG += staticlib

win32-msvc* { # seems like only msvc support LUA pch....
    CONFIG += precompiled_header
    PRECOMPILED_HEADER = src/lua.hpp
}

!CONFIG(staticlib): DEFINES += LUA_BUILD_AS_DLL

linux {
    DEFINES += LUA_USE_LINUX
    LIBS += -ldl -lreadline
} else: osx {
    DEFINES += LUA_USE_MACOSX
    LIBS += -ldl
} else: win32|winrt {
    win32-g++: QMAKE_LINK = gcc
} else {
    DEFINES += LUA_USE_POSIX LUA_USE_DLOPEN
}

TARGET = lua

HEADERS += \
    src/lapi.h \
    src/lauxlib.h \
    src/lcode.h \
    src/lctype.h \
    src/ldebug.h \
    src/ldo.h \
    src/lfunc.h \
    src/lgc.h \
    src/llex.h \
    src/llimits.h \
    src/lmem.h \
    src/lobject.h \
    src/lopcodes.h \
    src/lparser.h \
    src/lprefix.h \
    src/lstate.h \
    src/lstring.h \
    src/ltable.h \
    src/ltm.h \
    src/lua.h \
    src/lua.hpp \
    src/luaconf.h \
    src/lualib.h \
    src/lundump.h \
    src/lvm.h \
    src/lzio.h

SOURCES += \
    src/lapi.c \
    src/lauxlib.c \
    src/lbaselib.c \
    src/lbitlib.c \
    src/lcode.c \
    src/lcorolib.c \
    src/lctype.c \
    src/ldblib.c \
    src/ldebug.c \
    src/ldo.c \
    src/ldump.c \
    src/lfunc.c \
    src/lgc.c \
    src/linit.c \
    src/liolib.c \
    src/llex.c \
    src/lmathlib.c \
    src/lmem.c \
    src/loadlib.c \
    src/lobject.c \
    src/lopcodes.c \
    src/loslib.c \
    src/lparser.c \
    src/lstate.c \
    src/lstring.c \
    src/lstrlib.c \
    src/ltable.c \
    src/ltablib.c \
    src/ltm.c \
    src/lundump.c \
    src/lutf8lib.c \
    src/lvm.c \
    src/lzio.c


DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

}
