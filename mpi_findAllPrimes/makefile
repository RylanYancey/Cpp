# Compiler Command
CC = mpiCC
CFLAGS = -c -I./header -std=c++0x

# collecting object file names
src = $(wildcard source/*.cpp)
src1 = $(src:.cpp=.o)

objects := $(src1:source/%=bin/%)

# Compile object files into binary
all : $(objects)
	$(CC) -o run $(objects)
ifneq ($(n),)
	mpirun -np $(n) run
endif

# Generate object files by compiling .cpp and .h files
bin/%.o : source/%.cpp
	$(CC) $(CFLAGS) $?
	mv *.o bin

# Clean Recipe
.PHONY : clean
clean : 
	rm -rf all $(objects)

# Debugger Command
# mpirun -np 4 xterm -e gdb ./run