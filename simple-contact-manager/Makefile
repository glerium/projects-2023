CCPAR = -Wall -std=c++20

all: contact

# compile
main.o: main.cpp contact.h
	g++ -c -o main.o main.cpp $(CCPAR)

contact.o: contact.cpp contact.h
	g++ -c -o contact.o contact.cpp $(CCPAR)

io.o: io.cpp contact.h
	g++ -c -o io.o io.cpp $(CCPAR)

# link
contact: main.o contact.o io.o contact.h
	g++ -o contact main.o contact.o io.o $(CCPAR)

# clean
.PHONY: clean
clean:
	rm -f main.o contact.o io.o contact