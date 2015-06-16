COMMON_OBJ := display.o \
	tubechars.o \
	clock.o

# Add the common source directory to VPATH
VPATH += $(DEPTH)/src

# Same for the common include directory
CPPFLAGS += -I $(DEPTH)/include

CFLAGS += -Wall -Werror

