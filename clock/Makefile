DEPTH = ..

BIN = vfd_characters

.PHONY: all
all: $(BIN).hex

MCU=atmega328
PROGRAMMER=usbtiny

CC=avr-gcc
OBJCOPY=avr-objcopy

CPPFLAGS += -I.
CFLAGS += -O1 -DF_CPU=1000000UL -mmcu=$(MCU)
LDFLAGS += -O1 -mmcu=$(MCU)

CLOCK_OBJ := main.o
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
	-rm -f $(BIN).elf $(BIN).hex $(OBJ) *.o *.d
