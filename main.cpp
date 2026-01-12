#include "GridWorld.h"
#include "CreateWorld.h"
#include "Sensors.h"
#include "SelfDrivingCar.h"
#include "FuseSensorData.h"
#include "DecisionMaking.h"
#include "UpdateWorld.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <thread> //for wait
#include <chrono> //for wait
using namespace std;

void printHelp(){
    cout << "Self-Driving Car Simulation" << endl;
    cout << "Usage:" << endl;
    cout << "  --seed <n>                   Random seed (default: current time)" << endl;
    cout << "  --dimX <n>                   World width (default: 40)" << endl;
    cout << "  --dimY <n>                   World height (default: 40)" << endl;
    cout << "  --numMovingCars <n>          Number of moving cars (default: 3)" << endl;
    cout << "  --numMovingBikes <n>         Number of moving bikes (default: 4)" << endl;
    cout << "  --numParkedCars <n>          Number of parked cars (default: 5)" << endl;
    cout << "  --numStopSigns <n>           Number of stop signs (default: 2)" << endl;
    cout << "  --numTrafficLights <n>       Number of traffic lights (default: 2)" << endl;
    cout << "  --simulationTicks <n>        Maximum simulation ticks (default: 100)" << endl;
    cout << "  --minConfidenceThreshold <n> Minimum confidence cutoff (default: 40)" << endl;
    cout << "  --gps <x1> <y1> [x2 y2 ...]  GPS target coordinates (required)" << endl;
    cout << "  --help                       Show this help message" << endl << endl;

    cout << "Example usage:" << endl;
    cout << "  ./oopp_proj_2025 --seed 12 --dimY 50 --gps 10 20 32 15" << endl;
}

//helper functions to parse cmd arguments
bool isFlag(const char* s){
    return strncmp(s, "--", 2) == 0;
}

bool parseIntOption(int& i, int argc, char* argv[], int& target){
    if (i + 1 >= argc) {
        return false;
    }

    target = stoi(argv[++i]);
    return true;
}

bool parseGPS(int& i, int argc, char* argv[],vector<pair<int,int>>& gpsPoints){
    ++i;
    vector<int> values;

    while (i < argc && !isFlag(argv[i])) {
        values.push_back(stoi(argv[i]));
        ++i;
    }

    --i; 

    if (values.size() % 2 != 0) {
        return false;
    }

    for (size_t j = 0; j < values.size(); j += 2) {
        gpsPoints.emplace_back(values[j], values[j + 1]);
    }

    return true;
}

// Function to Print Map to Terminal.
void printMap(int dimX, int dimY, const Grid& map) {

    // Upper Bound.
    for(int i=0; i<dimX+2; i++) {
        cout << "-";
    }
    cout << endl;

    for(int j = 0; j < dimY; j++){
        // Left Bound.
        cout << "|";

        for(int i = 0; i < dimX; i++){ 
            if(!map[i][j].car.empty()){
                // Auto Car.
                cout << map[i][j].car[0]->getGlyph();
            } else if(!map[i][j].movingObjects.empty()){
                // Other Cars.
                cout << map[i][j].movingObjects[0]->getGlyph();
            } else if(!map[i][j].staticObjects.empty()){
                // Static Objects (Signs, Traffic Lights).
                cout << map[i][j].staticObjects[0]->getGlyph();
            } else {
                // Nothing
                cout << ".";
            }
        }
        // Right Bound.
        cout << "|" << endl;
    }
    
    // Down Bound.
    for(int i=0; i<dimX+2; i++) cout << "-";
    cout << endl;
}


int main(int argc, char* argv[]){
    int seed;
    bool userSetSeed = false;
    int dimX = 40;
    int dimY = 40;
    int numMovingCars = 3;
    int numMovingBikes = 4;
    int numParkedCars = 5;
    int numStopSigns = 2;
    int numTrafficLights = 2;
    int simulationTicks = 100;
    int minConfidenceThreshold = 40;

    vector<pair<int,int>> gpsPoints;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "--help") {
            printHelp();
            return 0;
        }
        else if (arg == "--seed") {
            if (!parseIntOption(i, argc, argv, seed)) {
                return 1;
            }
            userSetSeed = true;
        }
        else if (arg == "--dimX") {
            if (!parseIntOption(i, argc, argv, dimX)){
                return 1;
            }
        }
        else if (arg == "--dimY") {
            if (!parseIntOption(i, argc, argv, dimY)){
                return 1;
            }
        }
        else if (arg == "--numMovingCars") {
            if (!parseIntOption(i, argc, argv, numMovingCars)){
                return 1;
            }
        }
        else if (arg == "--numMovingBikes") {
            if (!parseIntOption(i, argc, argv, numMovingBikes)){
                return 1;
            }
        }
        else if (arg == "--numParkedCars") {
            if (!parseIntOption(i, argc, argv, numParkedCars)){
                return 1;
            }
        }
        else if (arg == "--numStopSigns") {
            if (!parseIntOption(i, argc, argv, numStopSigns)){
                return 1;
            }
        }
        else if (arg == "--numTrafficLights") {
            if (!parseIntOption(i, argc, argv, numTrafficLights)){
                return 1;
            }
        }
        else if (arg == "--simulationTicks") {
            if (!parseIntOption(i, argc, argv, simulationTicks)){
                return 1;
            }
        }
        else if (arg == "--minConfidenceThreshold") {
            if (!parseIntOption(i, argc, argv, minConfidenceThreshold)){
                return 1;
            }
        }
        else if (arg == "--gps") {
            if (!parseGPS(i, argc, argv, gpsPoints)){
                return 1;
            }
        }
        else {
            cerr << "Unknown option: " << arg << endl;
            return 1;
        }
    }

    if (gpsPoints.empty()) {
        cout << "Error: --gps is required" << endl;
        return 1;
    }

    if (!userSetSeed) {
        seed = static_cast<int>(time(nullptr));
    }

    // Create Map.
    Grid map = createWorld(seed, dimX, dimY, numMovingCars, numMovingBikes, numParkedCars, numStopSigns, numTrafficLights);

    //we start from here ,ok?
    int carX = 0, carY = 0; 
    char carDir = 'N';
    int carSpeed = 0;
    Car* myCarPtr = nullptr;
    
    bool found = false;
    for(int i = 0; i < dimX; i++){
        for(int j = 0; j < dimY; j++){
            if(!map[i][j].car.empty()){
                myCarPtr = map[i][j].car[0];
                carX = i;
                carY = j;
                carDir = myCarPtr->getDirection();
                carSpeed = myCarPtr->getSpeed();
                found = true;
                break;
            }
        }
        if(found) {
            break;
        }
    }

    if (!myCarPtr) {
        cerr << "Error: Self-driving car not found in generated world!" << endl;
        return 1;
    }

    double newMinConfidenceThreshold = static_cast<double>(minConfidenceThreshold)*0.01;

    // Initialize Sensors.
    LidarSensor lidar;
    RadarSensor radar;
    CameraSensor camera;

    // Simulation Loop.
    for (int tick = 0; tick < simulationTicks; ++tick) {
        
        // Update World.
        updateWorld(map); 

        // Print Current Sate.
        cout << "--- Tick: " << tick + 1 << " / " << simulationTicks << " ---" << endl;
        cout << "GPS Target: ";
        if(!gpsPoints.empty()) {
            cout << "(" << gpsPoints[0].first << ", " << gpsPoints[0].second << ")";
        }
        else {
            cout << "NONE";
        }
        cout << " | Car Pos: (" << carX << ", " << carY << ") | Speed: " << carSpeed << endl;
        
        printMap(dimX, dimY, map);

        // Scanning.
        auto lidarReadings = lidar.scan(carX, carY, carDir, map);
        auto radarReadings = radar.scan(carX, carY, carDir, map);
        auto cameraReadings = camera.scan(carX, carY, carDir, map);

        // Sensor Fusion.
        auto fLidar = fuseLidarData(lidarReadings, newMinConfidenceThreshold);
        auto fRadar = fuseRadarData(radarReadings, newMinConfidenceThreshold);
        auto fCamera = fuseCameraData(cameraReadings, newMinConfidenceThreshold);
        auto fusedAll = fuseAllSensors(fLidar, fRadar, fCamera);

        // Decision Making.
        auto decision = decideNextMove(carX, carY, carDir, carSpeed, fusedAll, gpsPoints);
        char nextDir = decision.first;
        char speedAction = decision.second;

        cout << "Decision -> Turn: " << nextDir << ", Action: " << speedAction << endl;

        // Update Auto Car's State.
        
        // Update Speed.
        if (speedAction == 'A' && carSpeed < 2) {
            carSpeed++;
        }
        if (speedAction == 'D' && carSpeed > 0) {
            carSpeed--;
        }

        // Update Direction.
        carDir = nextDir;

        // Update Car's Object.
        if (speedAction == 'A') {
            myCarPtr->accelerate();
        }
        if (speedAction == 'D') {
            myCarPtr->decelerate();
        }

        // Movement Execution in Map.
        if (carSpeed > 0) {
            int newX = carX;
            int newY = carY;

            // Calculate new Coordinates.
            if (carDir == 'N') {
                newY--;
            }
            else if (carDir == 'S') {
                newY++;
            }
            else if (carDir == 'E') {
                newX++;
            }
            else if (carDir == 'W') {
                newX--;
            }

            // Bounds Check.
            if (newX >= 0 && newX < dimX && newY >= 0 && newY < dimY) {
                // Collision Check.
                bool blocked = !map[newX][newY].staticObjects.empty() || !map[newX][newY].movingObjects.empty();
                
                if (!blocked) {
                    // Move in Map.
                    map[newX][newY].car.push_back(myCarPtr); //add to new cell
                    map[carX][carY].car.clear(); //delete from old cell
                    carX = newX;
                    carY = newY;
                } else {
                    // Immobilization due to Obstacle
                    cout << "(!) Movement Blocked by object at (" << newX << "," << newY << ")!" << endl;
                    carSpeed = 0;
                    myCarPtr->decelerate(); 
                }
            } else {
                cout << "(!) Hit World Boundary!" << endl;
                carSpeed = 0;
            }
        }

        // GPS' Goal Check.
        if (!gpsPoints.empty()) {
            // Manhattan Distance.
            int d = abs(carX - gpsPoints[0].first) + abs(carY - gpsPoints[0].second);

            // If we Reach the Goal (or near).
            if (d <= 1) {
                cout << "\nREACHED CHECKPOINT (" << gpsPoints[0].first << "," << gpsPoints[0].second << ")\n";
                gpsPoints.erase(gpsPoints.begin()); //delete goal
                std::this_thread::sleep_for(std::chrono::seconds(1)); //pause
            }
        }

        // All Goals Completed.
        if (gpsPoints.empty()) {
            cout << "\nMISSION ACCOMPLISHED! ALL TARGETS REACHED\n";
            break; //end of program
        }

        // Small pause for better visualisation.
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return 0;
}
