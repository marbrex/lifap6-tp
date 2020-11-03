all: bin/executable.out

bin/executable.out: obj/main.o obj/SkipList.o obj/element.o
	g++ -Wall -g obj/main.o obj/SkipList.o obj/element.o -o bin/executable.out

obj/main.o: src/main.cpp src/SkipList.h src/element.h
	g++ -Wall -g -c src/main.cpp -o obj/main.o

obj/SkipList.o: src/SkipList.h src/SkipList.cpp src/element.h
	g++ -Wall -g -c src/SkipList.cpp -o obj/SkipList.o

obj/element.o: src/element.h src/element.cpp
	g++ -Wall -g -c src/element.cpp -o obj/element.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*