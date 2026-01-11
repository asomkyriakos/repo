#include "GridWorld.h"
#include "CreateWorld.h"
#include "Sensors.h"
#include "SelfDrivingCar.h"
#include "FuseSensorData.h"
#include "DecisionMaking.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <ctime>
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

    //we start from here ,ok?
    int carX = 0, carY = 0; 
    char carDir = 'N';
    int carSpeed = 0;
    Grid map = createWorld(seed,dimX,dimY,numMovingCars,numMovingBikes,numParkedCars,numStopSigns,numTrafficLights);
    for(int i=0; i<dimX;i++){
        for(int j = 0; j < dimY; j++){
            if(map[i][j].movingObjects.empty() && map[i][j].staticObjects.empty() && map[i][j].car.empty()){
                cout << ".";
            } else if(!map[i][j].movingObjects.empty()){
                cout << map[i][j].movingObjects[0]->getGlyph();
            } else if(!map[i][j].staticObjects.empty()){
                cout << map[i][j].staticObjects[0]->getGlyph();
            }else if(!map[i][j].car.empty()){
                cout << map[i][j].car[0]->getGlyph();
                carX = i;
                carY = j;
                carDir = map[i][j].car[0]->getDirection();
                carSpeed = map[i][j].car[0]->getSpeed();
            }
        }
        cout << "\n";
    }

    double newMinConfidenceThreshold = static_cast<double>(minConfidenceThreshold)*0.01;


    // Create a sensor.
    LidarSensor lidar;
    cout << "\n--- scanning with Lidar at (" << carX << "," << carY << ") ---\n";

    // Scan map.
    vector<SensorReading> lidarReadings = lidar.scan(carX, carY, carDir, map);

    // Print what was detected.
    if(lidarReadings.empty()) {
        cout << "No objects detected in range.\n";
    } else {
        for (const auto& r : lidarReadings) {
            cout << "Found: " << r.type << " | ID: " << r.objectId 
                << " | Distance: " << r.distance 
                << " | X: " << r.x
                << " | Y: " << r.y
                << " | Confidence: " << r.confidence << endl;
        }
    }

    RadarSensor radar;

    cout << "\n--- scanning with Radar at (" << carX << "," << carY << ") ---\n";

    vector<SensorReading> radarReadings = radar.scan(carX, carY, carDir, map);

    if(radarReadings.empty()) {
        cout << "No objects detected in range.\n";
    } else {
        for (const auto& r : radarReadings) {
            cout << "Found: " << r.type << " | ID: " << r.objectId 
                << " | Distance: " << r.distance 
                << " | Confidence: " << r.confidence
                << " | X: " << r.x
                << " | Y: " << r.y
                << " | Speed: " << r.speed 
                << " | Direction: " << r.direction 
                << " | Info: " << r.info << endl;
        }
    }

    CameraSensor camera;

    cout << "\n--- scanning with Camera at (" << carX << "," << carY << ") ---\n";

    vector<SensorReading> cameraReadings = camera.scan(carX, carY, carDir, map);

    if(cameraReadings.empty()) {
        cout << "No objects detected in range.\n";
    } else {
        for (const auto& r : cameraReadings) {
            cout << "Found: " << r.type << " | ID: " << r.objectId 
                << " | Distance: " << r.distance 
                << " | Confidence: " << r.confidence 
                << " | Speed: " << r.speed 
                << " | X: " << r.x
                << " | Y: " << r.y
                << " | Direction: " << r.direction 
                << " | Info: " << r.info << endl;
        }
    }

    cout <<"\n";

    Fuse fusedLidarReadings = fuseLidarData(lidarReadings, newMinConfidenceThreshold);
    Fuse fusedRadarReadings = fuseRadarData(radarReadings, newMinConfidenceThreshold);
    Fuse fusedCameraReadings =fuseCameraData(cameraReadings, newMinConfidenceThreshold);

    Fuse fusedAll = fuseAllSensors(fusedLidarReadings,fusedRadarReadings,fusedCameraReadings);

    for (const auto& [id, vec] : fusedAll) {
        for (const auto& d : vec) {
            std::cout << " Id: " <<d.objectId << " | Type: " << d.type << " | Distance: "
                    << d.distance << " | Confidence: " << d.confidence << " | X: "
                    << d.x << " | Y: " << d.y << " | Speed: "
                    << d.speed << " | Dir: " << d.direction
                    << " | Info: " << d.info << "\n";
        }
    }


    auto move = decideNextMove(carX, carY, carDir, carSpeed, fusedAll, gpsPoints);
    cout << "Direction: " << move.first << ", Speed Action: " << move.second << endl;

    return 0;
}
