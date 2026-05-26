
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -I./src/headers

SRC := $(wildcard src/*.cc) $(wildcard src/impl/*.cc)
OBJ := $(patsubst src/%.cc,build/%.o,$(SRC))

.PHONY: all build clean

all: build

build: bin/run


bin/run: $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@


build/%.o: src/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f bin/run $(OBJ)
