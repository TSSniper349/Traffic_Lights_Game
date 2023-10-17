CXX = g++
CXXFLAGS = -std=c++11

TARGET = main

# Source files
INC = -I src/include -L src/lib 
SRCS = main.cpp Button.cpp HighScores.cpp RenderWindow.cpp text.cpp TrafficLight.cpp Timer.cpp Road.cpp Lane.cpp Vehicle.cpp
SDL = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
# Build and run tests

.PHONY: all

all:

	$(CXX) $(CXXFLAGS) $(INC) -o $(TARGET) $(SRCS) $(SDL)

	./$(TARGET)

# Clean rule

.PHONY: clean

clean:

	del $(TARGET).exe
