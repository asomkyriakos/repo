#pragma once
#include <string>
using namespace std;

// Base class for moving objects
class MovingObjects {
protected:
    string id;
    string glyph;
    int x, y;

public:
    MovingObjects(string i, string g, int xc, int xy);
    virtual ~MovingObjects();

    int getX() const;
    int getY() const;
    string getGlyph() const;
    string getId() const;
};

// Base class for static objects
class StaticObject {
protected:
    string id;
    string glyph;
    int x, y;

public:
    StaticObject(string i, string g, int xc, int xy);
    virtual ~StaticObject();

    int getX() const;
    int getY() const;
    string getGlyph() const;
    string getId() const;
};

// Stationary vehicles (parked cars)
class StationaryVehicles : public StaticObject {
    char type; // P
public:
    StationaryVehicles(string id, string glyph, int x, int y, char tp);
    ~StationaryVehicles();
};

// Traffic signs
class TrafficSigns : public StaticObject {
    char type; // S
public:
    TrafficSigns(string id, string glyph, int x, int y, char tp);
    ~TrafficSigns();
};

// Traffic lights
class TrafficLights : public StaticObject {
private:
    char colour; // R,Y,G
    int tick;

public:
    TrafficLights(string id, string glyph, int x, int y, char col, int tck);
    ~TrafficLights();
};

// Moving vehicles (cars and bikes)
class Vehicle : public MovingObjects {
private:
    int speed;      // 0 = stop, 1 = half, 2 = full
    char direction; // NSEW
    char type;      // C or B

public:
    Vehicle(string id, string glyph, int x, int y, int sp, char dir, char t);
    ~Vehicle();

    int getSpeed() const;
    char getDirection() const;
    char getType() const;
};
