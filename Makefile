
remove_comments.x: main.o
	g++ -std=c++17 -g main.o -o remove_comments.x

main.o: main.cpp
	g++ -std=c++17 -g main.cpp -o main.o -c

clean:
	rm -f remove_comments.x *.o

