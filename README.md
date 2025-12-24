- Compile with:
g++ -std=c++17 -Wall main.cpp CreateWorld.cpp GridWorld.cpp -o simulation
- Execute with:
./simulation --seed 42 --dimX 10 --dimY 10 --numMovingCars 3 --numMovingBikes 2 --numParkedCars 4 --numStopSigns 2 --numTrafficLights 2 --gps 2 3 7 8
- For help run:
./simulation --help
- Also a make file:
make 
- And to clear cache of executables:
make clean
