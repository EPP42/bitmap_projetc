CXX= g++
CXXFLAGS= -std=c++14 -Wall -Werror -Wextra -pedantic -g3 -I $(INCLUDE_DIR)

EXEC= reader
SRC= $(wildcard ./src/*.cc)
OBJ= $(patsubst %.cc,%.o,$(wildcard ./src/*.cc))
INCLUDE_DIR=include 
LIB=bitmap.so
VPATH= src
RM=rm -rf

INCLUDE_DIRECTORIES=include

all: $(EXEC)

all_debug:  $(SRC)
	$(CXX) $(CXXFLAGS) -DDEBUG_MODE $^ -o $@

src/%.o: src/%.cc
	$(CXX) -c $(CXXFLAGS) -fPIC $< -o $@   

lib: $(LIB)

$(LIB) : $(OBJ)
	$(CXX) $(CXXFLAGS) -fPIC -shared  -DDEBUG_MODE $^ -o $@
	$(RM) $(OBJ)

$(EXEC) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	@$(RM) $(EXEC) $(LIB)

.PHONY: clean all 
