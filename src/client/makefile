CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

LDFLAGS = -lboost_system -lftxui-component -lftxui-screen -lftxui-dom

SRC_DIR = ../client

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
