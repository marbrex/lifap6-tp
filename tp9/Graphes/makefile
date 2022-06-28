# Directories
BIN = bin
SRC = src
OBJ = obj
DATA = data

# Files
exec = $(BIN)/executable.out
objects = $(OBJ)/main.o $(OBJ)/graph.o $(OBJ)/element.o

# Commands
create_OBJ_if_doesnt_exist = if [ ! -d "./$(OBJ)" ]; then mkdir $(OBJ); fi;
create_BIN_if_doesnt_exist = if [ ! -d "./$(BIN)" ]; then mkdir $(BIN); fi;
create_DATA_if_doesnt_exist = if [ ! -d "./$(DATA)" ]; then mkdir $(DATA); fi;

# Makefile Rules
all : $(exec)

$(exec) : $(objects)
	$(create_BIN_if_doesnt_exist)
	$(create_DATA_if_doesnt_exist)
	g++ -Wall -g $(objects) -o $(exec)

$(OBJ)/main.o : $(SRC)/main.cpp $(SRC)/graph.h
	$(create_OBJ_if_doesnt_exist)
	g++ -Wall -g -c $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/graph.o : $(SRC)/graph.h $(SRC)/graph.cpp $(SRC)/element.h
	$(create_OBJ_if_doesnt_exist)
	g++ -Wall -g -c $(SRC)/graph.cpp -o $(OBJ)/graph.o

$(OBJ)/element.o : $(SRC)/element.h $(SRC)/element.cpp
	$(create_OBJ_if_doesnt_exist)
	g++ -Wall -g -c $(SRC)/element.cpp -o $(OBJ)/element.o

# -f (--force) -> doesn't throw an error if files don't exist
clean :
	rm -f $(OBJ)/*

veryclean : clean
	rm -f $(BIN)/*