CXX= g++
CXXFLAGS= -std=c++14 -Wall -Werror -Wextra -pedantic -g3

EXEC= reader
SRC= header.cc main.cc image.cc image_nb.cc



all_debug:  $(SRC)
	$(CXX) $(CXXFLAGS) -DDEBUG_MODE $^ -o $@

all: $(EXEC)

$(EXEC) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	@rm -rf $(EXEC)

.PHONY: clean all 
