CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = simulation
SRCS = main.cpp GridWorld.cpp CreateWorld.cpp Sensors.cpp SelfDrivingCar.cpp FuseSensorData.cpp DecisionMaking.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
