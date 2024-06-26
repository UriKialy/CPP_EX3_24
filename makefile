CXX = g++
CXXFLAGS = -Wall  -g
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

Test = test
demo = demo


SRCS = $(wildcard *.cpp)					# Get all the .cpp files in the current directory
SRCS := $(filter-out $(demo).cpp, $(SRCS))	# Remove the demo file from the list of sources
SRCS := $(filter-out $(Test).cpp, $(SRCS))	# Remove the test file from the list of sources

OBJECTS = $(SRCS:.cpp=.o)


all: $(demo) $(Test) Game

$(demo): $(OBJECTS) $(demo).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(demo)
	valgrind $(VALGRIND_FLAGS) ./$(demo)

$(Test): $(OBJECTS) $(Test).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$(Test)

Game: $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(demo) $(Test) Game

.PHONY: all clean valgrind 