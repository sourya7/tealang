CC = ccache g++
CC_FLAGS = -I../Include --std=c++11 -Wall -Werror -ggdb

ifeq ($(EGC), 1)
GC_FLAGS = -DALLOW_GC
GC_LIB= -lgc
endif

ifeq ($(EWARN), 1)
WARN = $(WARN_FLAGS)
endif

# File names
EXEC = tlang
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
BUILTOBJ = $(wildcard build/*.o)

# Main target
all: $(OBJECTS)

# To obtain object files
%.o: %.cpp
	$(CC) $(WARN) $(PFLAGS) $(GC_FLAGS) -c $(CC_FLAGS) $< -o ../build/$@
