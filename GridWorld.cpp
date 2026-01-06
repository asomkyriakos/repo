#include "GridWorld.h"
#include <iostream>
using namespace std;

// MovingObjects
MovingObjects::MovingObjects(string i, string g, int xc, int xy): id(i), glyph(g), x(xc), y(xy) {
    
    }
MovingObjects::~MovingObjects() {

}
int MovingObjects::getX() const { 
    return x; 
}
int MovingObjects::getY() const { 
    return y; 
}
string MovingObjects::getGlyph() const { 
    return glyph;
}
string MovingObjects::getId() const {
     return id; 
}

// StaticObject
StaticObject::StaticObject(string i, string g, int xc, int xy): id(i), glyph(g), x(xc), y(xy) {

}
StaticObject::~StaticObject() {

}
int StaticObject::getX() const { 
    return x; 
}
int StaticObject::getY() const { 
    return y; 
}
string StaticObject::getGlyph() const { 
    return glyph; 
}
string StaticObject::getId() const { 
    return id; 
}

// StationaryVehicles
StationaryVehicles::StationaryVehicles(string id, string glyph, int x, int y, char tp): StaticObject(id, glyph, x, y), type(tp) {
    cout << "Parked Made\n";
}
StationaryVehicles::~StationaryVehicles() { 
    cout << "Parked Deleted\n"; 
}

// TrafficSigns
TrafficSigns::TrafficSigns(string id, string glyph, int x, int y, char tp): StaticObject(id, glyph, x, y), type(tp) {
    cout << "Signs Made\n";
}
TrafficSigns::~TrafficSigns() { 
    cout << "Signs Deleted\n"; 
}

// TrafficLights
TrafficLights::TrafficLights(string id, string glyph, int x, int y, char col, int tck): StaticObject(id, glyph, x, y), colour(col), tick(tck) {
    cout << "Lights Made\n";
}
TrafficLights::~TrafficLights() { 
    cout << "Lights Deleted\n"; 
}
char TrafficLights::getColour()const {
    return colour;
}

// Vehicle
Vehicle::Vehicle(string id, string glyph, int x, int y, int sp, char dir, char t): MovingObjects(id, glyph, x, y), speed(sp), direction(dir), type(t) {
    cout << "Vehicle Made\n";
}
Vehicle::~Vehicle() { 
    cout << "Vehicle Deleted\n"; 
}
int Vehicle::getSpeed() const { 
    return speed; 
}
char Vehicle::getDirection() const { 
    return direction; 
}
char Vehicle::getType() const { 
    return type; 
}
