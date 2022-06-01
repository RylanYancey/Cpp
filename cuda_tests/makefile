
# Place this file in the root of your project. 
# In the root, also create a file called 'bin', 'header' and 'source'

# use command `make` in the shell to run the makefile.
# All .o files will be placed in the 'bin' file.
# A binary will be generated in the root of the file.

# use ./run to run the program. 

# Compiler Command
CC = nvcc
CFLAGS = -c -I./header -I./kernel -I./source -I./lib/EasyBMP/

# collecting object file names
src = $(wildcard source/*.cpp)
src1 = $(src:.cpp=.o)

gpu = $(wildcard kernel/*.cu)
gpu1 = $(gpu:.cu=.o)

objects := $(src1:source/%=bin/%)
kernels := $(gpu1:kernel/%=bin/%)

#echo $(info $(objects) $(kernels))

# Compile object files into binary
all : $(objects) $(kernels)
	$(CC) -o run $(objects) $(kernels)

# Generate object files by compiling .cpp and .h files
bin/%.o : source/%.cpp
	$(CC) $(CFLAGS) $?
	mv *.o bin

bin/%.o : kernel/%.cu
	$(CC) $(CFLAGS) $?
	mv *.o bin

# Clean Recipe
.PHONY : clean
clean : 
	rm ./bin/*.o
