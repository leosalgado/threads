CXX = g++
CXXFLAGS = -std=c++11 -pthread
INCLUDES = -I./include
SRC = src/main.cpp src/functions.cpp
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

build: $(TARGET)

$(TARGET): $(SRC) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) build/*.o
