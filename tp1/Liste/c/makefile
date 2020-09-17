all: bin/executable.out

bin/executable.out: obj/main.o obj/liste.o obj/element.o
	gcc -Wall -g obj/main.o obj/liste.o obj/element.o -o bin/executable.out

obj/main.o: src/main.c src/liste.h src/element.h
	gcc -Wall -g -c src/main.c -o obj/main.o

obj/liste.o: src/liste.h src/liste.c src/element.h
	gcc -Wall -g -c src/liste.c -o obj/liste.o

obj/element.o: src/element.h src/element.c
	gcc -Wall -g -c src/element.c -o obj/element.o

clean:
	rm obj/*

veryclean: clean
	rm bin/*