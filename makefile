CC=gcc
CXX=g++
CXXFLAGS = -std=c++0x -Wall -I $(INCLUDE)

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build


SRC = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE = $(wildcard $(INCLUDE_DIR)/*.hpp)

run: compile 
	./$(OBJ_DIR)/main.o 

compile: clean
	$(CXX) $(CXXFLAGS) -o $(OBJ_DIR)/main.o $(SRC)

clean:
	touch $(OBJ_DIR)/o.o 
	rm $(OBJ_DIR)/*.o