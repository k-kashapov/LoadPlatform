#-----------------------
# Compiler/linker flags
#-----------------------

CC = arm-none-eabi-gcc

CFLAGS = 			\
	-std=c18 		\
	-Wall 			\
	-Wextra 		\
	-Werror 		\
	-I inc  		\
	-march=armv6-m  \
	-mcpu=cortex-m0 \
	-Os

LDFLAGS = 															  \
	-Wall 															  \
	-Wextra 														  \
	-Werror 														  \
	-Wl,--start-group -lgcc -lc -lg -Wl,--end-group -Wl,--gc-sections \
	-march=armv6-m 													  \
	-mcpu=cortex-m0 												  \
	-Wl,--warn-common 												  \
	-Wl,--fatal-warnings 											  \
	-Wl,-z,max-page-size=8 											  \
	-Wl,-T,entry.lds

ifeq ($(DEBUG),1)
	CFLAGS += -g
endif


#-------
# Files
#-------

SOURCES = 		\
	entry.S 	\
	main.c      \
	src/RCC.c   \
	src/tick.c  \
	src/clock.S \
	src/btn.c   \
	src/uart.c  \
	src/SPI.c   \
	src/screen.c\
	src/GPIO.c

OBJECTS_HALFWAY_DONE = $(SOURCES:%.c=build/%.o)
OBJECTS              = $(OBJECTS_HALFWAY_DONE:%.S=build/%.o)

EXECUTABLE_FLASH = build/main.elf
BINARY_FLASH     = build/main.bin

#---------------
# Build scripts
#---------------

all: $(EXECUTABLE_FLASH) $(BINARY_FLASH) $(SOURCES)

$(EXECUTABLE_FLASH): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BINARY_FLASH): $(EXECUTABLE_FLASH)
	arm-none-eabi-objcopy -O binary $< $@

build/%.o: %.c
	@mkdir -p build
	@mkdir -p build/src
	$(CC) $(CFLAGS) -o $@ -c $<

build/%.o: %.S
	@mkdir -p build
	@mkdir -p build/src
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build

#----------------------
# Hardware interaction
#----------------------

GDB_FLAGS = 										\
	--eval-command="set architecture arm" 			\
	--eval-command="set gnutarget elf32-littlearm" 	\
	--eval-command="target remote localhost:1234" 	\
	--eval-command="file $(EXECUTABLE_FLASH)"

flash: FORCE $(BINARY_FLASH) inc/*
	st-flash write $(BINARY_FLASH) 0x08000000

hardware: FORCE $(EXECUTABLE_FLASH)
	st-util -p 1234

gdb: FORCE $(BINARY_FLASH)
	arm-none-eabi-gdb $(GDB_FLAGS)

uart: FORCE
	sudo cp minirc.stm32f051 /etc/minicom/
	sudo minicom -D /dev/ttyUSB0 stm32f051

FORCE:
