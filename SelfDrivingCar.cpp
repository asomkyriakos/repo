#include <iostream>
#include <string>
#include <vector>
using namespace std;
//any dummy data is to be deleted later, they are just for showcase

//either we use mahattan or we make something less effiecient that first does the horizontal movement and then the vertican(the 2nd if easier)

class Car{
    private:
        int speed; //0,1,2
        string direction; //NSEW

    public:
        void accelerate(){
            if(this.speed < 2){
                this.speed++;
            }
        }
        void decelerate(){
            if(this.speed >0){
                this.speed--;
            }
        }

        //collections data methods

        void collectSensorData(){ //collects data

        }

        void syncNavigationSystem(){ //feed this the collected data from the function collectSensorData

        }
        
        void executeMovement(){ //feed this 1)position on grid, 2)mahattan heuristics, and 3)a true or false value about traffic lights or near goals(so it decelarates)

        }

        //data management

        void NavigationSystem(){ //feed this x,y coordinates

        }

        void fuseSensorData(){

        }

        void makeDecision(){

        }

        //manhattan heuristics

        void manhattan(){ //feed this x,y coordinates and make this an int function
            
        }

        //reasons to decelarate

        void senseTrafficLight(){ //feed this the traffic light you saw
            string traffic = 'R'; //dummy data
            int distance_of_traffic_light = 3; //dummy data
            if((traffic == 'R' || traffic == 'Y') && distance_of_traffic_light <= 3){
                if(traffic == 'R'){
                    decelarate();
                }else if(traffic == 'Y' && distance_of_traffic_light == 3){
                    decelerate();
                }
                
            }
        }
        void nearGoal(){ //feed this the distance from target
            int distance_of_goal =5; //dummy data
            if(distance_of_goal <= 5){
                decelerate();
            }
        }

        //reasons to accelarate

};
