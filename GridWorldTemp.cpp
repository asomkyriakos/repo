#include <iostream>
#include <string>
#include <vector>
#include "GridWorld.h"
using namespace std;

//Inheritable shit
class MovingObjects{
    protected:
        string id;
        string glyph; //used in last question(question 4) don't bother yet
        int x,y;

    public:
        MovingObjects(string i , string g, int xc, int xy) : id(i) , glyph(g) , x(xc) , y(xy){
        }
        ~MovingObjects(){
        }

        int getX() const { 
            return x; 
        }
        int getY() const { 
            return y; 
        }
        string getGlyph() const { 
            return glyph; 
        }
        string getId() const { 
            return id; 
        }
};

class StaticObject{
    protected: 
        string id;
        string glyph; //used in last question(question 4) don't bother yet
        int x,y;
    public:
        StaticObject(string i , string g, int xc, int xy) : id(i) , glyph(g) , x(xc) , y(xy){
        }
        ~StaticObject(){
        }

        int getX() const { 
            return x; 
        }
        int getY() const { 
            return y; 
        }
        string getGlyph() const { 
            return glyph; 
        }
        string getId() const { 
            return id; 
        }
};

//Stationary classes with inheritance(rich daddy)

class StationaryVehicles : public StaticObject{
    char type; //P
    protected:

    public:
        StationaryVehicles(string id ,string glyph,int x,int y, char tp) :StaticObject(id,glyph,x,y), type(tp){
            cout<< "Parked Made\n";
        }
        ~StationaryVehicles(){
            cout<< "Parked Deleted\n";
        }
        
};

class TrafficSigns : public StaticObject{
    char type; //S
    protected:

    public:
        TrafficSigns(string id ,string glyph,int x,int y, char tp) :StaticObject(id,glyph,x,y) , type(tp){
            cout<< "Signs Made\n";
        }
        ~TrafficSigns(){
            cout<< "Signs Deleted\n";
        }
};

class TrafficLights : public StaticObject{
    private:
        char colour; //use either R,Y,G to keep it simple
        int tick; //make a method that changes the colour if tick goes from 0->4(red->green),4->12(green->orange),12->14(orange->red) on start we set the tick to the border number of the colour, will see how to do it
    
    public:
        TrafficLights(string id ,string glyph,int x,int y, char col , int tck) :StaticObject(id,glyph,x,y), colour(col), tick(tck){
            cout<< "Lights Made\n";
        }
        ~TrafficLights(){
            cout<< "Lights Deleted\n";
        }
    };

//Moving classes with inheritance(they get yatch)

class Vehicle : public MovingObjects{
    private:
        int speed; //0 for stop, 1 for half speed, 2 for full speed
        char direction; // NSEW system
        char type; //either car or bike (C,B)

    public:
        Vehicle(string id ,string glyph,int x,int y,int sp, char dir, char t ) : MovingObjects(id ,glyph ,x,y) , speed(sp) , direction(dir),type(t){
            cout << "Vehicle Made\n";
        }
        ~Vehicle(){
            cout<< "Vehicle Deleted\n";
        }
    
        int getSpeed() const { 
            return speed; 
        }
        char getDirection() const { 
            return direction; 
        }
        char getType() const { 
            return type; 
        }
};
