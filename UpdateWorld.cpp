#include "UpdateWorld.h"
#include "GridWorld.h"
#include <vector>
#include <iostream>
#include <algorithm>

// Helper Function to Save Needed Moves.
struct MoveRequest {
    MovingObjects* obj;
    int oldX, oldY;
    int newX, newY;
};

void updateWorld(Grid& world) {
    int dimX = world.size();
    if (dimX == 0) {
        return;
    }
    int dimY = world[0].size();

    // Update Traffic Lights.
    for (int x = 0; x < dimX; ++x) {
        for (int y = 0; y < dimY; ++y) {
            for (auto* obj : world[x][y].staticObjects) {
                // Check if it is a traffic light.
                TrafficLights* light = dynamic_cast<TrafficLights*>(obj);
                if (light) {
                    light->updateTrafficLight();
                }
            }
        }
    }

    // Update Moving Objects.
    std::vector<MoveRequest> moves;
    std::vector<MovingObjects*> toDelete; //list to delete

    for (int x = 0; x < dimX; ++x) {
        for (int y = 0; y < dimY; ++y) {
            // Iteration to Cell's Objects.
            for (auto* obj : world[x][y].movingObjects) {
                Vehicle* v = dynamic_cast<Vehicle*>(obj);
                if (v) {
                    int speed = v->getSpeed();
                    char dir = v->getDirection();

                    // If it has Speed, Calculate New Position.
                    if (speed > 0) {
                        int dx = 0, dy = 0;
                        // Assumption: If speed > 0, Objects move 1 step.
                        int step = 1; 

                        if (dir == 'N') dy = -step;
                        else if (dir == 'S') dy = step;
                        else if (dir == 'E') dx = step;
                        else if (dir == 'W') dx = -step;

                        moves.push_back({obj, x, y, x + dx, y + dy});
                    }
                }
            }
        }
    }

    // Motion Application.
    for (const auto& m : moves) {
        // Delete from old cell.
        auto& oldList = world[m.oldX][m.oldY].movingObjects;
        oldList.erase(std::remove(oldList.begin(), oldList.end(), m.obj), oldList.end());

        // Boundary Check.
        if (m.newX >= 0 && m.newX < dimX && m.newY >= 0 && m.newY < dimY) {
            // In bounds -> Move.
            // Update Coordinates in Object.
            m.obj->setPosition(m.newX, m.newY);
            world[m.newX][m.newY].movingObjects.push_back(m.obj); //put to new cell
        } else {
            // Out of Bounds -> Delete.
            delete m.obj;
            // std::cout << "Object " << m.obj->getId() << " left the map and was deleted.\n";
        }
    }
}