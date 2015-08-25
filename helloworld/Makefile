PROJECT = hello

EXECUTABLE = $(PROJECT).elf
BIN_IMAGE = $(PROJECT).bin
HEX_IMAGE = $(PROJECT).hex

# set the path to STM32F429I-Discovery firmware package
STDP ?= ../STM32F429I-Discovery_FW_V1.0.1

# Toolchain configurations
CROSS_COMPILE ?= /usr/local/gcc-arm-none-eabi-4_8-2014q1/bin/arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE = $(CROSS_COMPILE)size

# Cortex-M4 implements the ARMv7E-M architecture
CPU = cortex-m4
CFLAGS = -mcpu=$(CPU) -march=armv7e-m -mtune=cortex-m4
CFLAGS += -mlittle-endian -mthumb
# FPU
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#CFLAGS += -specs=nosys.specs -specs=rdimon.specs

LDFLAGS =
define get_library_path
    $(shell dirname $(shell $(CC) $(CFLAGS) -print-file-name=$(1)))
endef
LDFLAGS += -L $(call get_library_path,libc.a)
LDFLAGS += -L $(call get_library_path,libgcc.a)

# Basic configurations
CFLAGS += -g -std=c99
CFLAGS += -Wall

# Optimizations
CFLAGS += -O3 -ffast-math
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections
CFLAGS += -fno-common
CFLAGS += --param max-inline-insns-single=1000

# FPU
CFLAGS += -DARM_MATH_CM4 -D__FPU_PRESENT

# specify STM32F429
CFLAGS += -DSTM32F429_439xx

# to run from FLASH
CFLAGS += -DVECT_TAB_FLASH
LDFLAGS += -T stm32f429zi_flash.ld

# project starts here
CFLAGS += -I.
OBJS = \
    main.o \
    stm32f4xx_it.o 
#    system_stm32f4xx.o

CFLAGS += -I$(STDP)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/
OBJS += $(STDP)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.o

# LIB tm_stm32f4_ili9341_ltdc 
CFLAGS += -I libs/tm_stm32f4_ili9341_ltdc/
OBJS += libs/tm_stm32f4_ili9341_ltdc/tm_stm32f4_ili9341_ltdc.o

# LIB tm_stm32f4_fonts 
CFLAGS += -I libs/tm_stm32f4_fonts/
OBJS += libs/tm_stm32f4_fonts/tm_stm32f4_fonts.o

# LIB tm_stm32f4_spi 
CFLAGS += -I libs/tm_stm32f4_spi/
OBJS += libs/tm_stm32f4_spi/tm_stm32f4_spi.o

# LIB tm_stm32f4_sdram 
CFLAGS += -I libs/tm_stm32f4_sdram/
OBJS += libs/tm_stm32f4_sdram/tm_stm32f4_sdram.o

# LIB tm_stm32f4_delay 
CFLAGS += -I libs/tm_stm32f4_delay/
OBJS += libs/tm_stm32f4_delay/tm_stm32f4_delay.o

# LIB tm_stm32f4_usart 
CFLAGS += -I libs/tm_stm32f4_usart/
OBJS += libs/tm_stm32f4_usart/tm_stm32f4_usart.o

# LIB tm_stm32f4_gpio 
CFLAGS += -I libs/tm_stm32f4_gpio/
OBJS += libs/tm_stm32f4_gpio/tm_stm32f4_gpio.o

# STARTUP FILE
OBJS += startup_stm32f429_439xx.o

# CMSIS
CFLAGS += -I$(STDP)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS += -I$(STDP)/Libraries/CMSIS/Include
CFLAGS += -I$(STDP)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Template
LIBS += $(STDP)/Libraries/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a

# STemWinLibrary522_4x9i
CFLAGS += -I$(STDP)/Libraries/STemWinLibrary522_4x9i/inc
LIBS += \
    $(STDP)/Libraries/STemWinLibrary522_4x9i/Lib/STemWin522_4x9i_CM4_OS_GCC.a

# STM32F4xx_StdPeriph_Driver
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -I$(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/inc
#CFLAGS += -D"assert_param(expr)=((void)0)"
OBJS += \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.o \
    $(STDP)/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.o

# STM32F429I-Discovery Utilities
CFLAGS += -I$(STDP)/Utilities/STM32F429I-Discovery
OBJS += $(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery.o
OBJS += $(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_l3gd20.o
OBJS += $(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.o
OBJS += $(STDP)/Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.o

all: $(BIN_IMAGE)

$(BIN_IMAGE): $(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@
	$(OBJCOPY) -O ihex $^ $(HEX_IMAGE)
	$(OBJDUMP) -h -S -D $(EXECUTABLE) > $(PROJECT).lst
	$(SIZE) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJS)
	$(LD) -o $@ $(OBJS) \
		--start-group $(LIBS) --end-group \
		$(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)
	rm -rf $(HEX_IMAGE)
	rm -f $(OBJS)
	rm -f $(PROJECT).lst

flash:
	openocd -f interface/stlink-v2.cfg \
		-f target/stm32f4x_stlink.cfg \
		-c "init" \
		-c "reset init" \
		-c "halt" \
		-c "flash write_image erase $(PROJECT).elf" \
		-c "verify_image $(PROJECT).elf" \
		-c "reset run" -c shutdown || \
	st-flash write $(BIN_IMAGE) 0x8000000

.PHONY: clean
