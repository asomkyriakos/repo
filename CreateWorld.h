#pragma once
#include <vector>
#include "GridWorld.h" 
#include "SelfDrivingCar.h"
using namespace std;

class Car;

// a cell to keep entities in , helps with entities overlapping
struct Cell {
    std::vector<MovingObjects*> movingObjects;
    std::vector<StaticObject*> staticObjects;
    std::vector<Car*> car;
};

using Grid = std::vector<std::vector<Cell>>;

Grid createWorld(
    int seed,
    int dimX, int dimY,
    int numMovingCars, int numMovingBikes,
    int numParkedCars, int numStopSigns, int numTrafficLights
);
