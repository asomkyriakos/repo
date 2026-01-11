#include "Sensors.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iostream>

Sensor::Sensor(int r, double acc, std::string name) : range(r), baseAccuracy(acc), sensorName(name) {}

double Sensor::calculateConfidence(int dist) {
    // Out of range.
    if (dist > range) {
        return 0.0;
    }
    // Reduce certainty according the distance.
    double distFactor = 1.0 - (static_cast<double>(dist) / range);
    // Random noise.
    double noise = ((std::rand() % 11) - 5) / 100.0;
    double conf = (baseAccuracy * distFactor) + noise;
    return std::max(0.0, std::min(1.0, conf));
}

// Lidar Sensor.
LidarSensor::LidarSensor() : Sensor(9, 0.99, "Lidar") {
    cout << "[+LIDAR:" << sensorName << "] Lidar sensor ready - Sensing with pew pews!" << endl;
}

std::vector<SensorReading> LidarSensor::scan(int carX, int carY, char carDir, const Grid& world) {
    std::vector<SensorReading> readings;
    // 9x9 (360 degrees).
    for (int i = carX - 4; i <= carX + 4; ++i) {
        for (int j = carY - 4; j <= carY + 4; ++j) {
            if (i >= 0 && i < (int)world.size() && j >= 0 && j < (int)world[0].size()) {
                const Cell& cell = world[i][j];
                int dist = std::abs(carX - i) + std::abs(carY - j);
                
                for (auto* obj : cell.movingObjects) {
                    readings.push_back({obj->getId(), "Moving", (double)dist, calculateConfidence(dist), i, j, 0, ' ', ""});
                }
                for (auto* obj : cell.staticObjects) {
                    readings.push_back({obj->getId(), "Static", (double)dist, calculateConfidence(dist), i, j, 0, ' ', ""});
                }
            }
        }
    }
    return readings;
}

// Radar Sensor.
RadarSensor::RadarSensor() : Sensor(12, 0.95, "Radar") {
    cout << "[+RADAR:" << sensorName << "] Radar sensor ready - I'm a Radio star!" << endl;
}

std::vector<SensorReading> RadarSensor::scan(int carX, int carY, char carDir, const Grid& world) {
    std::vector<SensorReading> readings;
    // 12 straight ahead.
    for (int step = 1; step <= 12; ++step) {
        int tx = carX, ty = carY;

        if (carDir == 'N') {
            ty -= step;
        }
        else if (carDir == 'S') {
            ty += step;
        }
        else if (carDir == 'E') {
            tx += step;
        }
        else if (carDir == 'W') {
            tx -= step;
        }

        if (tx >= 0 && tx < (int)world.size() && ty >= 0 && ty < (int)world[0].size()) {
            // Only moving objects.
            for (auto* obj : world[tx][ty].movingObjects) {
                int speed = 0;
                char direction='N';
                if (auto* vehicle = dynamic_cast<Vehicle*>(obj)) {
                    speed = vehicle->getSpeed();
                    direction = vehicle->getDirection();
                }
                readings.push_back({obj->getId(), "Moving", (double)step, calculateConfidence(step), tx, ty, speed, direction, ""});
            }
        }
    }
    return readings;
}

// Camera Sensor.
CameraSensor::CameraSensor() : Sensor(7, 0.87, "Camera") {
    cout << "[+CAMERA:" << sensorName << "] Camera sensor ready - Say cheese!" << endl;
}

std::vector<SensorReading> CameraSensor::scan(int carX, int carY, char carDir, const Grid& world) {
    std::vector<SensorReading> readings;

    // 7x7 in front of the car.
    for (int offsetX = -3; offsetX <= 3; ++offsetX) {
        for (int offsetY = 1; offsetY <= 7; ++offsetY) {
            int tx = carX, ty = carY;
            if (carDir == 'N') {
                tx += offsetX; ty -= offsetY;
            }
            else if (carDir == 'S') {
                tx += offsetX; ty += offsetY;
            }
            else if (carDir == 'E') {
                tx += offsetY; ty += offsetX;
            }
            else if (carDir == 'W') {
                tx -= offsetY; ty += offsetX;
            }

            if (tx >= 0 && tx < (int)world.size() && ty >= 0 && ty < (int)world[0].size()) {
                const Cell& cell = world[tx][ty];
                int dist = std::abs(carX - tx) + std::abs(carY - ty);

                // Detects everything.
                for (auto* obj : cell.staticObjects) {
                    SensorReading r;
                    r.objectId = obj->getId();
                    r.distance = (double)dist;
                    r.confidence = calculateConfidence(dist);
                    r.x = tx; r.y = ty;

                    // Trafficlight Check.
                    TrafficLights* tl = dynamic_cast<TrafficLights*>(obj);
                    if (tl) {
                        r.type = "TrafficLight";
                        r.info = "Color: ";
                        r.info += tl->getColour();
                    }
                    // Sign Check.
                    else if (dynamic_cast<TrafficSigns*>(obj)) {
                        r.type = "TrafficSign";
                        r.info = "Text: STOP";
                    }
                    else {
                        r.type = "StaticObstacle";
                        r.info = "None";
                    }
                    readings.push_back(r);
                }

                // Moving Objects Check.
                for (auto* obj : cell.movingObjects) {
                    readings.push_back({obj->getId(), "MovingObject", (double)dist, calculateConfidence(dist), tx, ty, 0, ' ', "Detected"});
                }
            }
        }
    }
    return readings;
}

