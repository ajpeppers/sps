#A.J. Peppers

CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -Wall -O2 -std=c++11
DEBUG = -g
OBJECTS = slidepuzzle.o slidepuzzleNode.o

a.out: $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS) -o a.out
	@doxygen

slidepuzzle.o: slidepuzzle.cpp slidepuzzleNode.h

slidepuzzleNode.o: slidepuzzleNode.cpp slidepuzzleNode.h

.PHONY: clean
clean:
	-rm -f *.o a.out
