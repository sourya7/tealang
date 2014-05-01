CC = clang++
CC_FLAGS = --std=c++11 -ggdb -m32

# File names
EXEC = tlang
SOURCES = $(wildcard *.cxx)
OBJECTS = $(SOURCES:.cxx=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cxx
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
