CC = ccache g++
CC_FLAGS = -I./Include --std=c++11 -Wall -Werror -ggdb
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
SOURCES = $(wildcard *.cpp) $(wildcard Modules/*.cpp) $(wildcard Objects/*.cpp) $(wildcard Ast/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
BUILTOBJS = $(wildcard build/*.o) $(wildcard build/Modules/*.o) $(wildcard build/Objects/*.o)  $(wildcard build/Ast/*.o) 

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(WARN) $(PFLAGS) $(CC_FLAGS) $(BUILTOBJS) $(GC_FLAGS) $(GC_LIB) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) $(WARN) $(PFLAGS) $(GC_FLAGS) -c $(CC_FLAGS) $< -o build/$@

# To remove generated files
clean:
	rm -f $(EXEC) build/*.o build/Modules/*.o build/Objects/*.o build/Ast/*.o
