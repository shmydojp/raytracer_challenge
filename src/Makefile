CC=g++
COMPILER_FLAGS=-std=c++17 -Wall -g -pedantic

INC=-I../include
LIB=
LINKER_FLAG=-lSDL2main -lSDL2
OBJ=main.o matrix.o mat_util.o MainGame.o
DEPS=tuple.h color.h canvas.h matrix.h constant.h

%.o: %.cpp
	$(CC) -c -o $@ $< $(COMPILER_FLAGS) $(INC) $(LIB) $(LINKER_FLAG)

main: $(OBJ)
	$(CC) $(COMPILER_FLAGS) $(INC) -o $@ $^ $(LIB) $(LINKER_FLAG)

.PHONY: clean
clean:
	rm -rf *.o *~ main
