CXX = gcc
CXXFLAGS = -g -Wall


OBJECTS = pars.o lex.o

main: $(OBJECTS) main.o
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@./main
clean:
	rm *.o main

