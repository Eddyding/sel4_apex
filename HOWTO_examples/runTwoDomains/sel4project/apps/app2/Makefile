# Targets
TARGETS := $(notdir $(SOURCE_DIR)).bin

# Set custom entry point as we are a rootserver and will not be
# started in a standard way

LDFLAGS += -u __vsyscall_ptr

# Source files required to build the target
CFILES   := $(patsubst $(SOURCE_DIR)/%,%,$(wildcard $(SOURCE_DIR)/src/*.c))

# Libraries required to build the target
LIBS := c sel4 sel4muslcsys utils

# extra cflags 
CFLAGS += -Werror -g

include $(SEL4_COMMON)/common.mk


