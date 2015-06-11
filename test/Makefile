DEPTH = ..

include $(DEPTH)/Makefile.inc

BIN := test

CPPFLAGS += -I. -I./mock/include
CFLAGS += -Wno-unused-function -g
LDFLAGS += -lcheck

VPATH += ./mock/src

TEST_OBJS=avrio.c delay.o main.o 

run: $(BIN)
	./$(BIN)

$(BIN): $(COMMON_OBJS) $(TEST_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	-rm -f $(BIN) *.o
