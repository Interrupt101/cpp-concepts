# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Iheaders -std=c++11 -Wall

# Source files
SRCS = main.cpp sources/Book.cpp sources/Member.cpp sources/Library.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = main

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
