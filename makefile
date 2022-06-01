
output: planters.o plantermgr.o crops.o BST.o
	g++ planters.o plantermgr.o crops.o BST.o struct.h -o planters

planters.o: planters.cpp
	g++ -c planters.cpp

plantermgr.o: plantermgr.cpp plantermgr.h
	g++ -c plantermgr.cpp

crops.o: crops.cpp crops.h
	g++ -c crops.cpp

BST.o: BST.cpp binaryTree.h
	g++ -c BST.cpp

clean:
	rm *.o planters
