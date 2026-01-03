#pragma once
#include "GridWorld.h"
#include "CreateWorld.h"
#include <vector>
#include <string>

// Struct data.
struct SensorReading {
    std::string objectId;
    std::string type;
    double distance;
    double confidence;
    int x, y;
    int speed;
    char direction;
    std::string info; //kind of sign, color of traffic light...
};

// Main Sensor Class.
class Sensor {
protected:
    int range;
    double baseAccuracy;
    std::string sensorName;

public:
    Sensor(int r, double acc, std::string name);
    virtual ~Sensor() = default;

    double calculateConfidence(int dist);
    virtual std::vector<SensorReading> scan(int carX, int carY, char carDir, const Grid& world) = 0;
};

// Subclasses of Sensors
class LidarSensor : public Sensor {
public:
    LidarSensor();
    std::vector<SensorReading> scan(int carX, int carY, char carDir, const Grid& world) override;
};

class RadarSensor : public Sensor {
public:
    RadarSensor();
    std::vector<SensorReading> scan(int carX, int carY, char carDir, const Grid& world) override;
};

class CameraSensor : public Sensor {
public:
    CameraSensor();
    std::vector<SensorReading> scan(int carX, int carY, char carDir, const Grid& world) override;
};