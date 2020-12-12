# Files and Directories
BIN = bin
SRC = src
OBJ = obj

exec = executable.out
objects = $(OBJ)/main.o $(OBJ)/graph.o $(OBJ)/element.o

# Commands
create_OBJ_if_doesnt_exist = if [ ! -d "./$(OBJ)" ]; then mkdir $(OBJ); fi;

# Makefile
all : $(BIN)/$(exec)

$(BIN)/$(exec) : $(objects)
	if [ ! -d "./$(BIN)" ]; then mkdir $(BIN); fi;
	g++ -Wall -g $(objects) -o $(BIN)/$(exec)

$(OBJ)/main.o : $(SRC)/main.cpp $(SRC)/graph.h
	$(create_OBJ_if_doesnt_exist)
	g++ -Wall -g -c $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/graph.o : $(SRC)/graph.h $(SRC)/graph.cpp $(SRC)/element.h
	$(create_OBJ_if_doesnt_exist)
	g++ -Wall -g -c $(SRC)/graph.cpp -o $(OBJ)/graph.o

$(OBJ)/element.o : $(SRC)/element.h $(SRC)/element.cpp
	$(create_OBJ_if_doesnt_exist)
	g++ -Wall -g -c $(SRC)/element.cpp -o $(OBJ)/element.o

clean :
	rm -f $(OBJ)/*

veryclean : clean
	rm -f $(BIN)/*