CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
TARGET = eventflow
SOURCES = main.cpp Observer.cpp Subject.cpp EventGroup.cpp EventUnit.cpp EventControl.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
