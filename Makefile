# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

# Source files (using wildcards to automatically find all .cpp files in src/)
A1_SRCS = assignment_01/driver/driver.cpp $(wildcard assignment_01/src/*.cpp)
A2_SRCS = assignment_02/driver/driver.cpp $(wildcard assignment_02/src/*.cpp)
A3_SRCS = assignment_03/driver/driver.cpp $(wildcard assignment_03/src/*.cpp)
A4_SRCS = assignment_04/driver/driver.cpp $(wildcard assignment_04/src/*.cpp)
WRAPPER_SRC = common_wrapper/wrapper.cpp

# Output binaries
A1_OUT = assignment_01/outputs/driver.out
A2_OUT = assignment_02/outputs/driver.out
A3_OUT = assignment_03/outputs/driver.out
A4_OUT = assignment_04/outputs/driver.out
WRAPPER_OUT = wrapper

# Default target: compile everything
.PHONY: all clean a1 a2 a3 a4 wrapper

all: a1 a2 a3 a4 wrapper

# Compile Assignment 1
a1: $(A1_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $(A1_OUT)
	@echo "Built $(A1_OUT)"

# Compile Assignment 2
a2: $(A2_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $(A2_OUT)
	@echo "Built $(A2_OUT)"

# Compile Assignment 3
a3: $(A3_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $(A3_OUT)
	@echo "Built $(A3_OUT)"

# Compile Assignment 4
a4: $(A4_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $(A4_OUT)
	@echo "Built $(A4_OUT)"

# Compile the Common Wrapper
wrapper: $(WRAPPER_SRC)
	$(CXX) $(CXXFLAGS) $< -o $(WRAPPER_OUT)
	@echo "Built $(WRAPPER_OUT)"

# Clean all generated binaries
clean:
	rm -f $(A1_OUT) $(A2_OUT) $(A3_OUT) $(A4_OUT) $(WRAPPER_OUT)
	@echo "Cleaned all binaries."