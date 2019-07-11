
# Make Command Goals
ifeq ($(MAKECMDGOALS),)
MAKECMDGOALS := all
endif

ifeq ($(MAKECMDGOALS), all)
$(error ** Sorry I need a specific Goal **, Option too generic..)
endif


## Platform/OS/Machine
ifndef PLATFORM
PLATFORM	:= $(if $(shell uname | egrep -Ei linux),linux,android)
ifeq ($(PLATFORM),linux)
$(info ** PLATFORM = $(PLATFORM)  **)
else ifeq ($(PLATFORM),android)
$(info ** PLATFORM = $(PLATFORM)  **)
else
$(error ** PLATFORM = $(PLATFORM) **,Invalid platform type..)
endif

LONG_BIT	:= $(shell getconf LONG_BIT)
$(info ** OS       = $(LONG_BIT)Bits **)
ifdef MACHINE
      MACHINE :=
      undefine MACHINE
endif
MACHINE		:= $(shell uname -m)
endif


# Compiller Options
CC		:= gcc

# Arch/Tune/ Linker Options
# ( Don't Give Compiler or OS too much freedom, .. you are the one in control! )
ifdef ARCH
override undefine ARCH
endif

ifeq ($(LONG_BIT),32)
ARCH		:=$(shell unset ARCH;${PWD}/aarch march)

ARCH		:=$(if $(findstring aarch64,$(MACHINE)),armv7-a,$(ARCH))
ARCH		:=$(if $(findstring android,$(MACHINE)),armv7,$(ARCH))
$(info ** ARCH     = $(ARCH) **)
TUNE		:=$(shell ${PWD}/aarch mtune)
TUNE		:=$(if $(findstring nil,$(TUNE)),,$(TUNE))

else ifeq ($(LONG_BIT),64)
ARCH		:=$(shell unset ARCH;${PWD}/aarch march)

ARCH		:=$(if $(findstring android,$(MACHINE)),armv7,$(ARCH))
$(info ** ARCH     = $(ARCH) **)
TUNE		:=$(shell ${PWD}/aarch mtune)
TUNE		:=$(if $(findstring nil,$(TUNE)),,$(TUNE))

else
$(warning ** ARCH     = $(ARCH) **,Unknown Arch type..)
$(info ** ARCH    = native **, Will be used..)
ARCH := native
endif


ifdef TUNE
$(info ** TUNE     = $(TUNE) **)
CFLAGS		:= -march=$(ARCH) -mtune=$(TUNE) -Wall -Werror -Ofast -finline-functions -foptimize-sibling-calls -foptimize-strlen -faggressive-loop-optimizations -fif-conversion -funroll-loops -fno-exceptions -ftree-vectorize # Compiler Flags

else
CFLAGS		:= -march=$(ARCH) -Wall -Werror -Ofast -finline-functions -foptimize-sibling-calls -foptimize-strlen -faggressive-loop-optimizations -fif-conversion -funroll-loops -fno-exceptions -ftree-vectorize # Compiler Flags

endif


## CRC32 source/headers.. Code Related
#
CRC32_SRCS	:= crc32.c
CRC32_HDRS	:= $(CRC32_SRCS:.c=.h)

# Objects
CRC32_OBJS	:= $(CRC32_SRCS:.c=.o)


# project c/h relative paths
SRCS_PATH	:= src
HDRS_PATH	:= include

# Project c/h relative paths.to/file.name
CRC32_SRCS	:= $(addprefix $(SRCS_PATH)/,$(CRC32_SRCS))
CRC32_HDRS	:= $(addprefix $(HDRS_PATH)/,$(CRC32_HDRS))

# TARGETs
.PHONY: crc32
crc32   : $(CRC32_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(CRC32_OBJS): $(CRC32_SRCS) $(CRC32_HDRS)
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY:	clean
clean:
	@if [ -f ${CRC32_OBJS} ];then		\
		rm -v ${CRC32_OBJS};		\
	fi
