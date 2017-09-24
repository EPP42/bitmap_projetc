CXX= g++
CXXFLAGS= -std=c++14 -Wall -Werror -Wextra -pedantic -g3 -I $(INCLUDE_DIR)

EXEC= reader
SRC= $(wildcard ./src/*.cc)
INCLUDE_DIR=include 

VPATH= src

INCLUDE_DIRECTORIES=include
all_debug:  $(SRC)
	$(CXX) $(CXXFLAGS) -DDEBUG_MODE $^ -o $@

all: $(EXEC)

$(EXEC) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	@rm -rf $(EXEC)

.PHONY: clean all 
