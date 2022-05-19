
objects = source/BinaryTree.o source/main.o source/Person.o

build : $(objects)
	g++ -o bin/build $(objects)

source/main.o : header/BinaryTree.h source/main.cpp

source/BinaryTree.o : source/BinaryTree.cpp header/BinaryTree.h

source/Person.o : source/Person.cpp  header/Person.h

.PHONY : clean
clean :
	rm build $(objects)