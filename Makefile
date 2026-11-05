# Project Name
TARGET = arcade-pedal

# Optimization level
OPT = -O3

# QSPI boot type
APP_TYPE = BOOT_QSPI

# Sources
CPP_SOURCES = arcade-pedal.cpp \
              effects/ChorusEffect.cpp \
              effects/FlangerEffect.cpp

# Library Locations
LIBDAISY_DIR = dependencies/libDaisy/
DAISYSP_DIR = dependencies/DaisySP/

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
