DEPTH = ..

include $(DEPTH)/Makefile.inc

BIN := test

CPPFLAGS += -I. -I./mock/include
CFLAGS += -Wno-unused-function -g
LDFLAGS += -lcheck

VPATH += ./mock/src

TEST_OBJ := avrio.o delay.o main.o 

OBJ := $(TEST_OBJ) $(COMMON_OBJ) 

run: $(BIN)
	./$(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

include $(OBJ:.o=.d)

%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MG $^ | sed -e 's@\(.*\)\.o:@\1.d \1.o:@' >$@

.PHONY: clean
clean:
	-rm -f $(BIN) *.o *.d
