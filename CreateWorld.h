#pragma once
#include <vector>
#include "GridWorld.h" 
using namespace std;

// a cell to keep entities in , helps with entities overlapping
struct Cell {
    std::vector<MovingObjects*> movingObjects;
    std::vector<StaticObject*> staticObjects;
};

using Grid = std::vector<std::vector<Cell>>;

Grid createWorld(
    int seed,
    int dimX, int dimY,
    int numMovingCars, int numMovingBikes,
    int numParkedCars, int numStopSigns, int numTrafficLights
);
