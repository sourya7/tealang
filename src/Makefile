CC = g++
CC_FLAGS = -I./Include --std=c++11 -ggdb 

ifeq ($(EGC), 1)
	GC_FLAGS = -DGC_DEBUG -DALLOW_GC
	GC_LIB= -lgc
endif

# File names
EXEC = tlang
SOURCES = $(wildcard *.cxx)
OBJECTS = $(SOURCES:.cxx=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) $(GC_FLAGS) $(GC_LIB) -o $(EXEC)

# To obtain object files
%.o: %.cxx
	$(CC) $(GC_FLAGS) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
