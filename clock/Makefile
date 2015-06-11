DEPTH = ..

include $(DEPTH)/Makefile.inc

BIN=vfd_characters
CLOCK_OBJS=main.o

MCU=atmega328
PROGRAMMER=usbtiny

CC=avr-gcc
OBJCOPY=avr-objcopy

CPPFLAGS += -I.
CFLAGS += -O1 -DF_CPU=1000000UL -mmcu=$(MCU)
LDFLAGS += -O1 -mmcu=$(MCU)

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(COMMON_OBJS) $(CLOCK_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

install: $(BIN).hex
	sudo avrdude -V -c $(PROGRAMMER) -p $(MCU)  -U flash:w:$<

.PHONY: clean
clean:
	-rm -f $(BIN).elf $(BIN).hex $(OBJS) *.o
