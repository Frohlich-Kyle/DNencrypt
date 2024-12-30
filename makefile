dna: main.o keyword.o
	g++ -o dna main.o keyword.o

main.o: keyword.h
	g++ -Wall -c main.cpp

keyword.o: keyword.h
	g++ -Wall -c keyword.cpp

clean:
	rm *.o dna