#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Inheritable shit
class MovingObjects{
    private:
        string id;
        string glyph; //used in last question(question 4) don't bother yet
};

class StaticObject{
    private: 
        string id;
        string glyph; //used in last question(question 4) don't bother yet

};

//Stationary classes with inheritance(rich daddy)

class StationaryVehicles : public StaticObjects{
    private:

};

class TrafficSigns : public StaticObjects{
    private:
    
};

class TrafficLights : public StaticObjects{
    private:
        string colour; //use either R,Y,G to keep it simple
        int tick; //make a method that changes the colour if tick goes from 0->4(red->green),4->12(green->orange),12->14(orange->red) on start we set the tick to the border number of the colour, will see how to do it
    
};

//Moving classes with inheritance(they get yatch)

class Vehicle : public MovingObjects{
    private:
        int speed; //0 for stop, 1 for half speed, 2 for full speed
        string direction; // NSEW system

};
