#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>
#include <utility>

#include "DecisionMaking.h"
#include "FuseSensorData.h"

using namespace std;

using Fuse = unordered_map<string, vector<FusedData>>;


int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}


pair<char,char> decideNextMove(int carX,int carY,char currentDir,int currentSpeed,const Fuse& fused,const vector<pair<int,int>>& gpsPoints
) {
    if (gpsPoints.empty()) {
        return {'X','K'};
    }

    
    pair<int,int> target = gpsPoints[0];
    int minDist = manhattan(carX, carY, target.first, target.second);

    for (const auto& p : gpsPoints) {
        int d = manhattan(carX, carY, p.first, p.second);
        if (d < minDist) {
            minDist = d;
            target = p;
        }
    }

   
    auto isBlocked = [&](int x, int y) {
        for (const auto& [id, vec] : fused) {
            for (const auto& obj : vec) {
                if (obj.confidence >= 0.7 &&
                    obj.x == x && obj.y == y &&
                    obj.type != "Moving") {
                    return true;
                }
            }
        }
        return false;
    };

    
    int dx = target.first - carX;
    int dy = target.second - carY;

    char nextDir = currentDir;

    if (abs(dx) >= abs(dy)) {
        if (dx > 0 && !isBlocked(carX + 1, carY)) nextDir = 'E';
        else if (dx < 0 && !isBlocked(carX - 1, carY)) nextDir = 'W';
        else if (dy > 0 && !isBlocked(carX, carY + 1)) nextDir = 'S';
        else if (dy < 0 && !isBlocked(carX, carY - 1)) nextDir = 'N';
    } else {
        if (dy > 0 && !isBlocked(carX, carY + 1)) nextDir = 'S';
        else if (dy < 0 && !isBlocked(carX, carY - 1)) nextDir = 'N';
        else if (dx > 0 && !isBlocked(carX + 1, carY)) nextDir = 'E';
        else if (dx < 0 && !isBlocked(carX - 1, carY)) nextDir = 'W';
    }

    
    char speedAction = 'K';

    
    bool obstacleClose = false;

    for (const auto& [id, vec] : fused) {
        for (const auto& obj : vec) {
            if (obj.confidence < 0.7) continue;

            int d = manhattan(carX, carY, obj.x, obj.y);

            
            if (obj.type == "Moving" && d <= 2) {
                obstacleClose = true;
            }

            if (obj.type == "Static" && d <= 3) {
                obstacleClose = true;
            }
        }
    }

    
    if (minDist <= 5) {
        speedAction = 'D';
    }

    if (obstacleClose) {
        speedAction = 'D';
    }

    if (!obstacleClose && minDist > 5) {
        if (currentSpeed < 2) {
            speedAction = 'A';
        }
    }

    return {nextDir, speedAction};
}
