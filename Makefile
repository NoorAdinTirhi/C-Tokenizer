
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./src/headers

SRC := $(wildcard src/*.cc) $(wildcard src/impl/*.cc)
OBJ := $(patsubst src/%.cc,build/%.o,$(SRC))

.PHONY: all build clean

all: build

build: run

run: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f run $(OBJ)
