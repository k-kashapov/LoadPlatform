#-----------------------
# Compiler/linker flags
#-----------------------

CC = arm-none-eabi-gcc

CFLAGS = \
	-std=c18 \
	-Wall \
	-Wextra \
	-march=armv6-m \
	-mcpu=cortex-m0 

LDFLAGS = \
	-Wall \
	-Wextra \
	-Werror \
	-Wl,--start-group -lgcc -lc -lg -Wl,--end-group -Wl,--gc-sections \
	-march=armv6-m \
	-mcpu=cortex-m0 \
	-Wl,--warn-common \
	-Wl,--fatal-warnings \
	-Wl,-z,max-page-size=8 \
	-Wl,-T,entry.lds

ifeq ($(DEBUG),1)
	CFLAGS += -g
endif


#-------
# Files
#-------

SOURCES = \
	entry.S \
	uart.c \
	main.c \
	api.c  \
	crc.c

OBJECTS_HALFWAY_DONE = $(SOURCES:%.c=build/%.o)
OBJECTS              = $(OBJECTS_HALFWAY_DONE:%.S=build/%.o)

EXECUTABLE_FLASH = build/uart.elf
BINARY_FLASH     = build/uart.bin

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
	$(CC) $(CFLAGS) -o $@ -c $<

build/%.o: %.S
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build

#----------------------
# User prog
#----------------------

.PHONY: send

ULDFLAGS = \
	 -Wall \
	 -Wextra \
	 -Werror \
	 -Wl,--start-group -lgcc -lc -lg -Wl,--end-group -Wl,--gc-sections \
	 -march=armv6-m \
	 -mcpu=cortex-m0 \
	 -Wl,--warn-common \
	 -Wl,--fatal-warnings \
	 -Wl,-z,max-page-size=8 \
	 -Wl,-T,user.lds

USOURCES = user.S \
		   blinkled.c

UOBJECTS_HALFWAY_DONE = $(USOURCES:%.c=build/%.o)
UOBJECTS              = $(UOBJECTS_HALFWAY_DONE:%.S=build/%.o)

UEXECUTABLE = build/user.elf
UBINARY     = build/user.bin

ucode: $(UEXECUTABLE) $(UBINARY) $(USOURCES) send

$(UEXECUTABLE): $(UOBJECTS)
	$(CC) $(ULDFLAGS) $(UOBJECTS) -o $@

$(UBINARY): $(UEXECUTABLE)
	arm-none-eabi-objcopy -O binary $< $@

send: 
	sudo ./usart.py $(UBINARY)

#----------------------
# Hardware interaction
#----------------------

GDB_FLAGS = \
	--eval-command="set architecture arm" \
	--eval-command="set gnutarget elf32-littlearm" \
	--eval-command="target remote localhost:1234" \
	--eval-command="file $(EXECUTABLE_FLASH)"

flash: FORCE $(BINARY_FLASH)
	st-flash write $(BINARY_FLASH) 0x08000000

hardware: FORCE $(EXECUTABLE_FLASH)
	st-util -p 1234

gdb: FORCE $(BINARY_FLASH)
	arm-none-eabi-gdb $(GDB_FLAGS)

uart: FORCE
	- rm -f minicom.log 
	sudo cp minirc.stm32f051 /etc/minicom/
	sudo minicom -H -D /dev/ttyUSB0 stm32f051 -C minicom.log

FORCE: