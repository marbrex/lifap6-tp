all: bin/executable.out

bin/executable.out: obj/main.o
	g++ -Wall -g obj/main.o -o bin/executable.out

obj/main.o: src/main.cpp src/table.h src/key.h src/info.h
	g++ -Wall -g -c src/main.cpp -o obj/main.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*