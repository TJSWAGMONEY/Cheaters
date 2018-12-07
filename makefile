# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary. 

plagiarismCatcher: plagiarismCatcher.o
	g++ -oplagiarismCatcher  plagiarismCatcher.o
	rm plagiarismCatcher.o
	clear
plagiarismCatcher.o: plagiarismCatcher.cpp hashTable.h
	g++ -std=c++0x -c plagiarismCatcher.cpp
	
