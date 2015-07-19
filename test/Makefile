DEPTH = ..

BIN := test

.PHONY: run
run: $(BIN)
	./$(BIN)

CPPFLAGS += -I. -I./mock/include
CFLAGS += -Wno-unused-function -g
LDFLAGS += -lcheck

VPATH += ./mock/src

TEST_OBJ := main.o \
	delay.o \
	avrio.o \
	display_test.o \
	bcd_test.o \
	bcd.o \
	i2c.o

# Must be recursively expanded for the dependencies rules in include.mk to work
OBJ = $(TEST_OBJ) $(COMMON_OBJ) 

include $(DEPTH)/include.mk

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	-rm -f $(BIN) *.o
