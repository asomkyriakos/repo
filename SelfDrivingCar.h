#pragma once

#include <string>
#include <vector>
#include "Sensors.h"

// Self-driving car class
class Car {
private:
    int speed;         // 0, 1, 2
    char direction;    // N S E W
    char glyph;        // @

public:
    // Constructor & Destructor
    Car(int spe, char dir, char gly);
    ~Car();

    
    char getGlyph() const;
    char getDirection() const;
    char getSpeed() const;

    // Speed control
    void accelerate();
    void decelerate();


    // Sensor data methods
    void collectSensorData();
    void syncNavigationSystem();

    // Movement & navigation
    void executeMovement();
    void NavigationSystem();

    // Data processing
    void fuseSensorData();
    void makeDecision();

    // Heuristics
    int manhattan();

    // Deceleration conditions
    void senseTrafficLight(char traffic, int distance);
    void nearGoal(int distance);

    // Reserved for future acceleration logic
};
