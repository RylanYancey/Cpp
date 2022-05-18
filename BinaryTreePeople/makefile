
root := $(shell pwd)

header := $(wildcard header/*.h)

source := $(wildcard source/*.cpp)

objects = 

build : $(objects)
	g++ -o edit $(objects)

main.o : main.cpp BinaryTree.h

BinaryTree.o : BinaryTree.cpp BinaryTree.h Person.h

Person.o : Person.cpp Person.h

.PHONY : clean
clean :
	rm btree $(objects)