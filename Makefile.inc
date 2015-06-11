COMMON_OBJS := display.o \
	tubechars.o \
	clock.o

VPATH += $(DEPTH)/src

CPPFLAGS += -I $(DEPTH)/include

CFLAGS += -Wall -Werror
