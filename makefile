# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary. 

plagiarismCatcher: plagiarismCatcher.o
	g++ -oplagiarismCatcher  plagiarismCatcher.o
#also include header files here
plagiarismCatcher.o: plagiarismCatcher.cpp
	g++ -c plagiarismCatcher.cpp
	
