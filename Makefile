CC = g++
CFLAGS = -std=c++17
SRC = main.cpp heuristicas_golosas.cpp busqueda_local.cpp archivo.cpp metaheuristica.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = gap_simulator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)