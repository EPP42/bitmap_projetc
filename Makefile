CXX= g++
CXXFLAGS= -std=c++14 -Wall -Werror -Wextra -pedantic -g3

EXEC= reader
SRC= header.cc main.cc image.cc



all: $(EXEC)

$(EXEC) : $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	@rm -rf $(EXEC)

.PHONY: clean all 
