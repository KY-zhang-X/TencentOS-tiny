BUILD = build

include ../py/mkenv.mk

MICROPY_ROM_TEXT_COMPRESSION ?= 1

include $(TOP)/py/py.mk

# Select the cross compile prefix
CROSS_COMPILE ?= arm-none-eabi-

# Set CFLAGS and libraries.	
INC = $(addprefix -I,\
	. \
	./modules \
	$(TOP) \
	$(BUILD) \
	)

DEF_C = -DMP_GEN_HDR=1

CFLAGS = $(INC) $(DEF_C)

# Set SRC_QSTR
SHARED_SRC_C = $(addprefix $(TOP)/shared/,\
	readline/readline.c \
	runtime/sys_stdio_mphal.c \
	runtime/pyexec.c \
	runtime/stdout_helpers.c \
	)

PORT_MODULE_SRC_C = \
	$(wildcard ./modules/*.c) \

SRC_QSTR += $(SHARED_SRC_C) $(PORT_MODULE_SRC_C)

# Target genhdr directory
TARGET_GENHDR_DIR = ./genhdr/

# Generate header
genhdr: $(HEADER_BUILD)/mpversion.h $(HEADER_BUILD)/qstrdefs.generated.h $(HEADER_BUILD)/moduledefs.h
	$(CP) $^ $(TARGET_GENHDR_DIR)

clean-build:
	$(ECHO) "REMOVE $(BUILD)"
	$(Q)$(RM) -rf $(BUILD)

# $(TARGET_GENHDR_DIR): 
# 	$(MKDIR) -p $@

include $(TOP)/py/mkrules.mk
