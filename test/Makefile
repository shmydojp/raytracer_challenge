CC=g++
COMPILER_FLAGS=-std=c++17 -Wall -g -pedantic

INC=-I../include -I../deps/catch/include
LIB=
LINKER_FLAG=-lSDL2main -lSDL2
OBJ=$(patsubst %.cpp,%.o,$(wildcard test_*.cpp))
OBJ+=../src/matrix.o ../src/mat_util.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(COMPILER_FLAGS) $(LINKER_FLAG) $(INC) $(LIB)

test: $(OBJ)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAG) $(INC) -o $@ $^ $(LIB)

.PHONY: clean
clean:
	rm -rf *.o *~ test
