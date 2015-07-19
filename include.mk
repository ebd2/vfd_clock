COMMON_OBJ := display.o \
	tubechars.o \
	clock.o \
	bcd.o \
	DS1307.o

# Add the common source directory to VPATH
VPATH += $(DEPTH)/src

# Same for the common include directory
CPPFLAGS += -I $(DEPTH)/include

CFLAGS += -Wall -Werror

include $(OBJ:.o=.d)

%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MG $^ | sed -e 's@\(.*\)\.o:@\1.d \1.o:@' >$@

.PHONY: dep_clean
	-rm *.d
