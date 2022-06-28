all: bin/executable.out

bin/executable.out: obj/main.o obj/arn.o obj/element.o
	g++ -Wall -g obj/main.o obj/arn.o obj/element.o -o bin/executable.out

obj/main.o: src/main.cpp src/arn.h src/element.h
	g++ -Wall -g -c src/main.cpp -o obj/main.o

obj/arn.o: src/arn.h src/arn.cpp src/element.h
	g++ -Wall -g -c src/arn.cpp -o obj/arn.o

obj/element.o: src/element.h src/element.cpp
	g++ -Wall -g -c src/element.cpp -o obj/element.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*