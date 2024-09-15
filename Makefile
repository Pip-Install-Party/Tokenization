main.exe: main.o commentDFA.o
	g++ -std=c++17 -g main.o commentDFA.o -o main.exe

main.o: main.cpp commentDFA.h
	g++ -std=c++17 -g main.cpp -o main.o -c

commentDFA.o: commentDFA.cpp commentDFA.h
	g++ -std=c++17 -g commentDFA.cpp -o commentDFA.o -c

clean:
	rm -f main.exe *.o