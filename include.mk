COMMON_OBJ := display.o \
	tubechars.o \
	clock.o

# Add the common source directory to VPATH
VPATH += $(DEPTH)/src

# Same for the common include directory
CPPFLAGS += -I $(DEPTH)/include

CFLAGS += -Wall -Werror

include $(OBJ:.o=.d)

%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MG $^ | sed -e 's@\(.*\)\.o:@\1.d \1.o:@' >$@

