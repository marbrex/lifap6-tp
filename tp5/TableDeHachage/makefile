all: bin/executable.out

bin/executable.out: obj/main.o obj/table.o obj/info.o
	g++ -Wall -g obj/main.o obj/table.o obj/info.o -o bin/executable.out

obj/main.o: src/main.cpp src/table.h src/key.h src/info.h
	g++ -Wall -g -c src/main.cpp -o obj/main.o

obj/table.o: src/table.h src/table.cpp src/key.h src/info.h
	g++ -Wall -g -c src/table.cpp -o obj/table.o

obj/info.o: src/info.h src/info.cpp
	g++ -Wall -g -c src/info.cpp -o obj/info.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*