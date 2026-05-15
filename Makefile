CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc
TARGET = marketplace
SRCS = main.cpp $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o src/*.o
