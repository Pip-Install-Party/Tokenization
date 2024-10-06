tokenize.exe: main.o commentDFA.o tokenizer.o
	g++ -std=c++17 -g main.o commentDFA.o tokenizer.o -o tokenize.exe

main.o: main.cpp commentDFA.h
	g++ -std=c++17 -g main.cpp -o main.o -c

commentDFA.o: commentDFA.cpp commentDFA.h 
	g++ -std=c++17 -g commentDFA.cpp -o commentDFA.o -c

tokenizer.o: tokenizer.cpp tokenizer.h 
	g++ -std=c++17 -g tokenizer.cpp -o tokenizer.o -c

clean:
	rm -f tokenize.exe *.o
