
# Compiler Command
CC = g++
CFLAGS = -c -Wall -I./header

# collecting object file names
src = $(wildcard source/*.cpp)
src1 = $(src:.cpp=.o)

objects := $(src1:source/%=bin/%)

# Compile object files into binary
all : $(objects)
	$(CC) -o run $(objects)

# Generate object files by compiling .cpp and .h files
bin/%.o : source/%.cpp
	$(CC) $(CFLAGS) $?
	mv *.o bin

# Clean Recipe
.PHONY : clean
clean : 
	rm -rf all $(objects)
