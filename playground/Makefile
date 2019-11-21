#!/usr/bin/make -f

# ------------------ README ------------------
# As input this Makefile is configured with:
#
# - PROJECT_NAME:
#   The project name
#   e.g "mini_project_1"
#
# - PROJECT_ROOT_DIR:
#   A project 'root' directory (logically the directory storing the mini
#   projects)
#   e.g "EMPR"
#
# - PROJECT_SRC_DIRS:
#   A list of source directories relative to PROJECT_ROOT_DIR
#   e.g $(PROJECT_ROOT_DIR)/$(PROJECT_NAME)/src/my_sub_dir
#
# ...with the prerequisite that the project has the following structure:
#
# PROJECT_ROOT_DIR
# |-- [nested source directories]
# |-- bin
# |-- build
# MakeFile
#
# For help with configuring these variables, use the `make print-VARIABLE_NAME`
# rule defined below.
#
# To use the Makefile to update the project:
# 1. Make sure the MBED board is mounted at /media/$(USER)/MBED
# 2. Run `make complete`
#    This removes all old object files from the `build` directory, recompiles
#    any changed source code, leaving the output in the `bin` directory and
#    drops the final .bin file onto the MBED board.

# CONFIGURE
# ==============================================================================
# Name of the current project
PROJECT_NAME := playground

# 'EMPR' directory
PROJECT_ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))../

# Source directories for this project, relative to the PROJECT_ROOT_DIR
PROJECT_SRC_DIRS := \
	$(PROJECT_ROOT_DIR)$(PROJECT_NAME)/src/ \
	$(PROJECT_ROOT_DIR)common_utils/ \
# ==============================================================================





# Build (object) directory for this project relative to the PROJECT_ROOT_DIR
BUILD_DIR := $(PROJECT_ROOT_DIR)$(PROJECT_NAME)/build/

# Ouptut binary directory for this project relative to the PROJECT_ROOT_DIR
BIN_OUTPUT_DIR := $(PROJECT_ROOT_DIR)$(PROJECT_NAME)/bin/

# Ensure consistent environment
SHELL := /bin/bash
PATH := /opt/york/cs/net/bin:$(PATH)

# Path to the GCC toolbox
PKG=/opt/york/cs/net

# Specify the commands needed from the tool chain, CC is the C-compiler,
# OBJCOPY converts the resulting program binary into a format we can load
# into the MBED board
ARCH=arm-none-eabi
CC=$(ARCH)-gcc
OBJCOPY=$(ARCH)-objcopy

# Due to a change in 2012 Linux, we now need to set a user name variable in the
# Makefile so the output path the make install users is right, this is done as
# follows
# USER:=$(shell whoami)

SOURCERY=$(PKG)/sourcery-g++-lite-arm-eabi-2010.09.51-i686-1
GNU_VERSION=4.5.0
THUMB2GNULIB=$(SOURCERY)/$(ARCH)/lib/$(GNU_VERSION)/thumb2
THUMB2GNULIB2=$(SOURCERY)/$(ARCH)/lib/thumb2

# "Cortex Microcontroller Software Interface Standard" Startup files, also the
# flags passed to the C compiler, and linker
CMSIS=$(PKG)/lpc1700-cmsis-lite-2011.01.26-i686-1
CMSISINCLUDES=-I$(CMSIS)/include
CMSISFL=$(CMSIS)/lib/core_cm3.o \
	$(CMSIS)/lib/system_LPC17xx.o \
	$(CMSIS)/lib/startup_LPC17xx.o
LDSCRIPT = $(CMSIS)/lib/ldscript_rom_gnu.ld

CFLAGS=-mcpu=cortex-m3  -mthumb  -Wall  -O0  -mapcs-frame  -D__thumb2__=1 \
  -msoft-float  -gdwarf-2  -mno-sched-prolog  -fno-hosted  -mtune=cortex-m3 \
  -march=armv7-m  -mfix-cortex-m3-ldrd   -ffunction-sections  -fdata-sections \
          -D__RAM_MODE__=0 $(CMSISINCLUDES) -I$(PROJECT_ROOT_DIR)

LDFLAGS=$(CMSISFL) -static -mcpu=cortex-m3 -mthumb -mthumb-interwork \
	   -Wl,--start-group -L$(THUMB2GNULIB) -L$(THUMB2GNULIB2) \
           -lc -lg -lstdc++ -lsupc++  -lgcc -lm  -Wl,--end-group \
	   -Xlinker -Map -Xlinker bin/lpc1700.map -Xlinker -T $(LDSCRIPT)

LDFLAGS+=-L$(CMSIS)/lib -lDriversLPC17xxgnu

# Path to the output binary to be built
EXECNAME = $(BIN_OUTPUT_DIR)$(PROJECT_NAME)

# Source files provided by the user to build the project
SOURCE_FILES = $(shell find $(PROJECT_ROOT_DIR) -name "*.c")
VPATH := $(sort $(dir $(PROJECT_SRC_DIRS)))
OBJECTS = $(patsubst %.c, $(BUILD_DIR)%.o, $(notdir $(SOURCE_FILES)))

# Debug print function to output the value of Makefile variables e.g
# make print-EXECNAME
print-%  : ; @echo $* = $($*)

# make
all: $(EXECNAME)
	@mkdir -p ./src
	@$(OBJCOPY) -I elf32-little -O binary $(EXECNAME) $(EXECNAME).bin

$(BUILD_DIR)%.o: %.c
	@mkdir -p ./build
	@echo Compiling $(notdir $<)...
	@$(CC) $(CFLAGS) -o $@ -c $<

$(EXECNAME): $(OBJECTS)
	@mkdir -p ./bin
	@$(CC) $^ -o $@ $(LDFLAGS)

# make clean - Clean out the source tree ready to re-build the project
clean:
	@echo Cleaning old..._copy
	@rm -f `find . | grep \~`
	@rm -f *.swp *.o */*.o */*/*.o  *.log
	@rm -f *.d */*.d *.srec */*.a bin/*.map
	@rm -f *.elf *.wrn bin/*.bin log *.hex
	@rm -f $(EXECNAME)

complete: | clean all install

# make install - Installs the resulting binary file to the MBED board, remember
# to sync the file systems, so the copy finishes
# need to know user to install into correct directory
USER:=$(shell whoami)

install:
	@echo "Copying " $(PROJECT_NAME) "to the MBED file system (press reset \
	button)"
	@cp $(EXECNAME).bin /media/$(USER)/MBED &
	@sync
