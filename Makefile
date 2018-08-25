SRC = $(wildcard src/*.cc)
CC = g++
CFLAGS = -Wall -Wextra #-std=c++11
DBGFLAGS = -g -D DEBUG
EXE := $(SRC:.cc=.x) 
DBGEXE := $(SRC:.cc=_debug.x)
# INC = $(wildcard inc/*.h)

all: $(EXE)

# debug: CFLAGS += $(DBGFLAGS)
debug: $(DBGEXE)

%.x: %.cc
	$(CC) $< -o $@ $(CFLAGS)

%_debug.x: %.cc
	$(CC) $< -o $@ $(CFLAGS) $(DBGFLAGS)

clean:
	rm -f $(EXE) $(DBGEXE)

.PHONY: clean debug