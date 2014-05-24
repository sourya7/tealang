CC = ccache g++
CC_FLAGS = -I./Include --std=c++11 -Wall -Werror -O2
WARN_FLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror

WARN_FLAGS2 = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror

ifeq ($(EGC), 1)
GC_FLAGS = -DALLOW_GC
GC_LIB= -lgc
endif

ifeq ($(EWARN), 1)
WARN = $(WARN_FLAGS)
endif


# File names
EXEC = tlang
SOURCES = $(wildcard *.cxx)
OBJECTS = $(SOURCES:.cxx=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(WARN) $(PFLAGS) $(CC_FLAGS) $(OBJECTS) $(GC_FLAGS) $(GC_LIB) -o $(EXEC)

# To obtain object files
%.o: %.cxx
	$(CC) $(WARN) $(PFLAGS) $(GC_FLAGS) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
