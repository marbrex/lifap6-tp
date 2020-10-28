all: bin/executable.out

bin/executable.out: obj/main.o obj/table.o
	g++ -Wall -g obj/main.o obj/table.o -o bin/executable.out

obj/main.o: src/main.cpp src/table.h src/key.h
	g++ -Wall -g -c src/main.cpp -o obj/main.o

obj/table.o: src/table.h src/table.cpp src/key.h
	g++ -Wall -g -c src/table.cpp -o obj/table.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*