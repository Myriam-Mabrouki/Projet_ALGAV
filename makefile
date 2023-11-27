CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = FileBinomiale.cpp Heap_array.cpp Heap_tree.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)