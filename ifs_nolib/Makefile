# Set verbosity
ifeq ($(V), 1)
Q =
else
Q = @
endif

# Commands
CC      = $(Q)arm-none-eabi-gcc
AS      = $(Q)arm-none-eabi-as
LD      = $(Q)arm-none-eabi-ld
AR      = $(Q)arm-none-eabi-ar
RM      = $(Q)rm
CPP     = $(Q)arm-none-eabi-cpp
SIZE    = $(Q)arm-none-eabi-size
STRIP   = $(Q)arm-none-eabi-strip -s
OBJCOPY = $(Q)arm-none-eabi-objcopy
OBJDUMP = $(Q)arm-none-eabi-objdump
GDB 	= $(Q)arm-none-eabi-gdb
PYTHON  = $(Q)python
MKDFU   = micropython/tools/dfu.py
PYDFU   = $(Q)../usr/pydfu.py
MKDIR   = $(Q)mkdir
ECHO    = $(Q)@echo
MAKE    = $(Q)make
CAT     = $(Q)cat
FLASH  	= $(Q)st-flash

#vpath %.S 
#vpath %.c component arch arch/$(CPU_DIR)/bsp/ arch/$(CPU_DIR)/hal_lib/src arch/$(CPU_DIR)/cmsis/src/st
#vpath %.h component arch arch/$(CPU_DIR)/bsp/ arch/$(CPU_DIR)/hal_lib/inc/ arch/$(CPU_DIR)/cmsis/inc/ arch/$(CPU_DIR)/cmsis/inc/st/

include Makefile.config

DEFS += -DUSE_HAL_DRIVER
DEFS += -D$(MCU)
DEFS += -D__FPU_PRESENT=1 -D__VFP_FP__ 

INCS += -Icomponent -Iarch 

include user/Makefile.config
include arch/$(CPU_DIR)/Makefile.config


OBJS += arch/ifs.o
OBJS += component/drv_led.o

CFLAGS += -g -O3 -std=gnu99 -Warray-bounds -nostartfiles -fdata-sections -ffunction-sections 
CFLAGS += -mcpu=$(CPU) -fsingle-precision-constant -Wdouble-promotion -mtune=$(CPU) -mthumb -Wall -mfpu=$(FPU) -mfloat-abi=hard 
LFLAGS += -specs=nosys.specs -mcpu=$(CPU) -mthumb -Wl,--gc-sections -mfpu=$(FPU) -mfloat-abi=hard 

.PHONY:all clean
all:$(TARGET).bin


clean:
	$(RM) -f $(OBJS) $(TARGET).bin $(TARGET).elf

debug:$(TARGET).elf
	$(GDB) $<

flash:$(TARGET).bin
	$(FLASH) write $< 0x08000000

$(TARGET).bin:$(TARGET).elf
	$(OBJCOPY) -O binary -S $< $@

$(TARGET).elf:$(OBJS)
	$(CC) $(LFLAGS) $^ -Wl,-Tuser/stm32fxxx.ld -o $@
	$(SIZE) $@

%.o:%.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(DEFS) $(CFLAGS) $(INCS) -c $< -o $@

