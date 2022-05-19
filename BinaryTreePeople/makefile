
objects = source/BinaryTree.o source/main.o source/Person.o

build : $(objects)
	g++ -o bin/build $(objects)

source/main.o : header/BinaryTree.h

source/BinaryTree.o : header/Person.h

source/Person.o : 

.PHONY : clean
clean :
	rm build $(objects)