CXX = g++
CXXFLAGS = -Wall -g0 -O3 -std=c++2a

SRCS = BinarySearchTree.cpp FileBinomiale.cpp Heap_array.cpp Heap_tree.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
