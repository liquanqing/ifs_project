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
PYTHON  = $(Q)python
MKDFU   = micropython/tools/dfu.py
PYDFU   = $(Q)../usr/pydfu.py
MKDIR   = $(Q)mkdir
ECHO    = $(Q)@echo
MAKE    = $(Q)make
CAT     = $(Q)cat
FLASH  	= $(Q)st-flash

vpath %.S user
vpath %.c user component arch arch/$(CPU_DIR)/bsp/ arch/$(CPU_DIR)/hal_lib/src arch/$(CPU_DIR)/cmsis/src/st
vpath %.h user component arch arch/$(CPU_DIR)/bsp/ arch/$(CPU_DIR)/hal_lib/inc/ arch/$(CPU_DIR)/cmsis/inc/ arch/$(CPU_DIR)/cmsis/inc/st/

include Makefile.config

DEFS += -DUSE_HAL_DRIVER
DEFS += -D$(MCU)
DEFS += -D__FPU_PRESENT=1 -D__VFP_FP__ 

INCS += -Iuser -Icomponent -Iarch -Iarch/$(CPU_DIR)/bsp -Iarch/$(CPU_DIR)/hal_lib/inc -Iarch/$(CPU_DIR)/cmsis/inc -Iarch/$(CPU_DIR)/cmsis/inc/st

OBJS += user/startup_stm32f769xx.o
OBJS += user/main.o user/stm32f7xx_hal_msp.o
OBJS += user/stm32f7xx_it.o

OBJS += arch/$(CPU_DIR)/cmsis/src/st/system_stm32f7xx.o
OBJS += arch/$(CPU_DIR)/cmsis/src/st/system_stm32f7xx.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal_rcc.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal_rcc_ex.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal_pwr.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal_pwr_ex.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal_gpio.o
OBJS += arch/$(CPU_DIR)/hal_lib/src/stm32f7xx_hal_cortex.o

OBJS += component/drv_led.o
OBJS += arch/$(CPU_DIR)/bsp/gpio.o
OBJS += arch/$(CPU_DIR)/bsp/usart.o
OBJS += arch/ifs.o

CFLAGS += -g -O3 -std=gnu99 -Warray-bounds -nostartfiles -fdata-sections -ffunction-sections 
CFLAGS += -mcpu=$(CPU) -mthumb -Wall -mfpu=$(FPU) 
LFLAGS += -specs=nosys.specs -mcpu=$(CPU) -mthumb 

.PHONY:all clean
all:$(TARGET).bin


clean:
	$(RM) -f $(OBJS) $(TARGET).bin $(TARGET).elf

flash:$(TARGET).bin
	$(FLASH) write $< 0x08000000

$(TARGET).bin:$(TARGET).elf
	$(OBJCOPY) -O binary -S $< $@

$(TARGET).elf:$(OBJS)
	$(CC) $(LFLAGS) $^ -Tuser/stm32fxxx.ld -o $@
	$(SIZE) $@

%.o:%.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(DEFS) $(CFLAGS) $(INCS) -c $< -o $@

