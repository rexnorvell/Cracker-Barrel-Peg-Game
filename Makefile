# Define variables
CXX = g++
CXXFLAGS = -Wall -g -Iinclude
TARGET = main
SRC_DIR = src
BUILD_DIR = build
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Board.cpp $(SRC_DIR)/Node.cpp $(SRC_DIR)/Solver.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(TARGET) $(OBJS)