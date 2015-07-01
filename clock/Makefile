DEPTH = ..

BIN = vfd_characters

.PHONY: all
all: $(BIN).hex

# Variables defining the hardware in use
MCU=atmega328
PROGRAMMER=usbtiny

# Hardware specific tools
CC=avr-gcc
OBJCOPY=avr-objcopy

CPPFLAGS += -I.
CFLAGS += -O1 -DF_CPU=8000000UL -mmcu=$(MCU) -g
LDFLAGS += -O1 -mmcu=$(MCU)

# Clock-specific object files.
CLOCK_OBJ := main.o

# All of the object files for the clock.  Must be recursively expanded because
# $(COMMON_OBJ) is defined in include.mk, which is included below.
OBJ = $(COMMON_OBJ) $(CLOCK_OBJ)

include $(DEPTH)/include.mk

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

install: $(BIN).hex
	sudo avrdude -V -c $(PROGRAMMER) -p $(MCU)  -U flash:w:$<

.PHONY: clean
clean:
	-rm -f $(BIN).elf $(BIN).hex $(OBJ) *.o
