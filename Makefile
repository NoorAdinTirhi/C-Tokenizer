
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./src/headers

SRC := $(wildcard src/*.cc) $(wildcard src/impl/*.cc)
OBJ := $(SRC:.cc=.o)

.PHONY: all build clean

all: build

build: run

run: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f run $(OBJ)
