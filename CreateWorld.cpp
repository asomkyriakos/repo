#include "CreateWorld.h"
#include "GridWorld.h"  
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <ctime>
using namespace std;

//To do:
//Add the SelfDrivingCar in the map
//Add the goal States and make the functions for the self driving car

Grid createWorld(
    int seed,
    int dimX, int dimY,
    int numMovingCars, int numMovingBikes,
    int numParkedCars, int numStopSigns, int numTrafficLights
){
    srand(seed);
    Grid world(dimX, vector<Cell>(dimY));

    //Moving Cars
    for(int i=0; i< numMovingCars ; i++){
        string id= "Car"+to_string(i);
        string glyph="C";
        int x = rand() % dimX;
        int y = rand() % dimY;
        int speed = rand() % 3;
        char direction = 'N';
        switch((rand()%4)+1){
            case 1:  direction = 'N'; y--; break;
            case 2:  direction = 'S'; y++; break;
            case 3:  direction = 'E'; x++; break;
            case 4:  direction = 'W'; x--; break;
        }
        char type = 'C';
        Vehicle* car = new Vehicle(id, glyph, x, y, speed, direction, type);
        world[x][y].movingObjects.push_back(car);

    }

    // Moving Bikes
    for(int i=0; i< numMovingBikes; i++){
        string id = "Bike" + to_string(i);
        string glyph = "B";
        int x = rand() % dimX;
        int y = rand() % dimY;
        int speed = rand() % 3;
        char direction = 'N';
        switch((rand()%4)+1){
            case 1: direction = 'N'; y--; break;
            case 2: direction = 'S'; y++; break;
            case 3: direction = 'E'; x++; break;
            case 4: direction = 'W'; x--; break;
        }
        char type = 'B';
        Vehicle* bike = new Vehicle(id, glyph, x, y, speed, direction, type);
        world[x][y].movingObjects.push_back(bike);
    }

    // Parked Cars
    for(int i=0; i< numParkedCars; i++){
        string id = "ParkedCar" + to_string(i);
        string glyph = "P";
        int x = rand() % dimX;
        int y = rand() % dimY;
        char type = 'P';
        StationaryVehicles* parked = new StationaryVehicles(id, glyph, x, y, type);
        world[x][y].staticObjects.push_back(parked);
    }

    // Traffic Signs
    for(int i=0; i< numStopSigns; i++){
        string id = "Sign" + to_string(i);
        string glyph = "S";
        int x = rand() % dimX;
        int y = rand() % dimY;
        char type = 'S';
        TrafficSigns* sign = new TrafficSigns(id, glyph, x, y, type);
        world[x][y].staticObjects.push_back(sign);
    }

    // Traffic Lights
    for(int i=0; i< numTrafficLights; i++){
        string id = "Light" + to_string(i);
        string glyph = "L";
        int x = rand() % dimX;
        int y = rand() % dimY;
        char colour = 'R';          //need to make this random
        int tick = 0;               //also make this random
        TrafficLights* light = new TrafficLights(id, glyph, x, y, colour, tick);
        world[x][y].staticObjects.push_back(light);
    }
    return world;
}
