SRC = $(wildcard src/*.cpp)
CXX = g++
CXXFLAGS = -std=c++11
DBGFLAGS = -g -D DEBUG
EXE = $(SRC:.cpp=.x) 
DBGEXE = $(SRC:.cpp=:_debug.x)
INC = $(wildcard inc/*.h)

all: $(EXE)

# debug: $(DBGEXE)
# debug: all

%.x: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) -I inc $(DBGFLAGS)

%_debug.x: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) -I inc $(DBGFLAGS)

.PHONY: clean debug

clean:
	rm -f $(EXE)