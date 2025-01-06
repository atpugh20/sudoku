CXX 		= g++
CXXFLAGS 	= -Wall -I./include -I./src, -I./external
LDFLAGS 	= -L./external/GLFW -lglfw3

SRCS 	= ./src/board.cpp ./src/main.cpp
HDRS 	= ./include/board.h

OBJ 	= $(SRC:.cpp=.o)

EXE = main

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean

