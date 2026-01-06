#include "SelfDrivingCar.h"
#include <iostream>
#include <string>
#include <vector>

// Constructor / Destructor
Car::Car(int spe, char dir, char gly) : speed(spe), direction(dir), glyph(gly) {}
Car::~Car() {}

char Car::getGlyph() const { 
    return glyph; 
}
char Car:: getDirection() const{
    return direction;
}

// Speed control
void Car::accelerate() { if (speed < 2) speed++; }
void Car::decelerate() { if (speed > 0) speed--; }

// Sensor data
void Car::collectSensorData() {}
void Car::syncNavigationSystem() {}

// Movement & navigation
void Car::executeMovement() {}
void Car::NavigationSystem() {}

// Data processing
void Car::fuseSensorData() {}
void Car::makeDecision() {}

// Heuristics
int Car::manhattan() { return 0; }

// Deceleration conditions
void Car::senseTrafficLight(char traffic, int distance) {
    if ((traffic == 'R' || traffic == 'Y') && distance <= 3) {
        if (traffic == 'R') decelerate();
        else if (traffic == 'Y' && distance == 3) decelerate();
    }
}

void Car::nearGoal(int distance) {
    if (distance <= 5) decelerate();
}
