CXX = gcc
CXXFLAGS = -g -Wall -s -static

OBJECTS = pars.o lex.o

main: $(OBJECTS) main.o
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./main
clean:
	rm *.o main

