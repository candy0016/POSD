
all: hw8 shell

hw8: mainUTShell.o atom.o list.o struct.o scanner.h parser.h exp.h
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainUTShell.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 mainUTShell.o atom.o list.o struct.o -lgtest -lpthread
endif

shell: Shell.o atom.o list.o struct.o
ifeq (${OS}, Windows_NT)
    
	g++ -o shell Shell.o atom.o list.o struct.o -lgtest
else
	
	g++ -o shell Shell.o atom.o list.o struct.o -lgtest -lpthread
endif

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp

mainUTShell.o: utShell.h
	g++ -std=gnu++0x -c mainUTShell.cpp

Shell.o: Shell.cpp scanner.h parser.h exp.h
	g++ -std=gnu++0x -c Shell.cpp


clean:
	rm -f *.o hw8 shell
stat:
	wc *.h *.cpp
