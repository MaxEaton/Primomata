CC=g++
CFLAGS=-Wall -Wextra -pedantic

SRC=src
BIN=bin
OBJ=$(BIN)/obj
TESTS=tests

all: $(BIN)/newGraph $(BIN)/newNames $(BIN)/rexTOnfa $(BIN)/nfaTOdfa $(BIN)/dfaTOmin $(BIN)/dfaTOcpp

$(OBJ)/help.o: $(SRC)/help.cpp $(SRC)/help.hpp
	mkdir -p bin bin/obj
	$(CC) $(CFLAGS) -c -o $(OBJ)/help.o $(SRC)/help.cpp

$(BIN)/newGraph: src/newGraph.cpp $(OBJ)/help.o
	$(CC) $(CFLAGS) -c -o $(OBJ)/newGraph.o $(SRC)/newGraph.cpp
	$(CC) $(CFLAGS) -o $(BIN)/newGraph $(SRC)/newGraph.cpp $(OBJ)/help.o -DALONE

$(BIN)/newNames: src/newNames.cpp $(OBJ)/help.o
	$(CC) $(CFLAGS) -c -o $(OBJ)/newNames.o $(SRC)/newNames.cpp
	$(CC) $(CFLAGS) -o $(BIN)/newNames $(SRC)/newNames.cpp $(OBJ)/help.o -DALONE

$(BIN)/rexTOnfa: src/rexTOnfa.cpp $(OBJ)/help.o
	$(CC) $(CFLAGS) -c -o $(OBJ)/rexTOnfa.o $(SRC)/rexTOnfa.cpp
	$(CC) $(CFLAGS) -o $(BIN)/rexTOnfa $(SRC)/rexTOnfa.cpp $(OBJ)/help.o -DALONE

$(BIN)/nfaTOdfa: src/nfaTOdfa.cpp $(OBJ)/help.o
	$(CC) $(CFLAGS) -c -o $(OBJ)/nfaTOdfa.o $(SRC)/nfaTOdfa.cpp
	$(CC) $(CFLAGS) -o $(BIN)/nfaTOdfa $(SRC)/nfaTOdfa.cpp $(OBJ)/help.o -DALONE

$(BIN)/dfaTOmin: src/dfaTOmin.cpp $(OBJ)/help.o
	$(CC) $(CFLAGS) -c -o $(OBJ)/dfaTOmin.o $(SRC)/dfaTOmin.cpp
	$(CC) $(CFLAGS) -o $(BIN)/dfaTOmin $(SRC)/dfaTOmin.cpp $(OBJ)/help.o -DALONE

$(BIN)/dfaTOcpp: src/dfaTOcpp.cpp $(OBJ)/help.o
	$(CC) $(CFLAGS) -c -o $(OBJ)/dfaTOcpp.o $(SRC)/dfaTOcpp.cpp
	$(CC) $(CFLAGS) -o $(BIN)/dfaTOcpp $(SRC)/dfaTOcpp.cpp $(OBJ)/help.o -DALONE

main: all
	$(CC) $(CFLAGS) -o $(BIN)/main $(SRC)/main.cpp $(OBJ)/help.o $(OBJ)/newGraph.o $(OBJ)/newNames.o $(OBJ)/rexTOnfa.o $(OBJ)/nfaTOdfa.o $(OBJ)/dfaTOmin.o $(OBJ)/dfaTOcpp.o

test: all
	./$(BIN)/rexTOnfa $(TESTS)/test.rex
	./$(BIN)/nfaTOdfa $(TESTS)/test.rex.nfa
	./$(BIN)/newNames $(TESTS)/test.rex.nfa.dfa
	./$(BIN)/dfaTOmin $(TESTS)/test.rex.nfa.dfa
	./$(BIN)/newNames $(TESTS)/test.rex.nfa.dfa.min
	./$(BIN)/dfaTOcpp $(TESTS)/test.rex.nfa.dfa.min
	$(CC) $(CFLAGS) -o $(TESTS)/test.rex.nfa.dfa.min.out $(TESTS)/test.rex.nfa.dfa.min.cpp
	./$(BIN)/newGraph $(TESTS)/test.rex.nfa
	dot -Tsvg < $(TESTS)/test.rex.nfa.dot > $(TESTS)/test.rex.nfa.dot.svg
	./$(BIN)/newGraph $(TESTS)/test.rex.nfa.dfa
	dot -Tsvg < $(TESTS)/test.rex.nfa.dfa.dot > $(TESTS)/test.rex.nfa.dfa.dot.svg
	./$(BIN)/newGraph $(TESTS)/test.rex.nfa.dfa.min
	dot -Tsvg < $(TESTS)/test.rex.nfa.dfa.min.dot > $(TESTS)/test.rex.nfa.dfa.min.dot.svg

flush:
	rm -f $(TESTS)/test.rex.*

clean:
	rm -f -r $(BIN)/*
	mkdir $(OBJ)
