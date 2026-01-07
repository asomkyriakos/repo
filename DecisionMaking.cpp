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


char decideNextMove(int carX, int carY, const Fuse& fused, const vector<pair<int,int>>& gpsPoints) {
    if (gpsPoints.empty()) {
        return 'X';
    } 
    
    pair<int,int> target = gpsPoints[0];
    int minDist = manhattan(carX, carY, target.first, target.second);

    for (const auto& p : gpsPoints) {
        int dist = manhattan(carX, carY, p.first, p.second);
        if (dist < minDist) {
            minDist = dist;
            target = p;
        }
    }
    
    auto isBlocked = [&](int x, int y) {
        for (const auto& [id, vec] : fused) {
            for (const auto& obj : vec) {
                if (obj.confidence > 0.5 && obj.x == x && obj.y == y && obj.type != "Moving")
                    return true;
            }
        }
        return false;
    };

    int dx = target.first - carX;
    int dy = target.second - carY;

    if (abs(dx) >= abs(dy)) {
        if (dx > 0 && !isBlocked(carX + 1, carY)) {
            return 'E';
        }
        if (dx < 0 && !isBlocked(carX - 1, carY)) {
            return 'W';
        }
        if (dy > 0 && !isBlocked(carX, carY + 1)) {
            return 'S';
        }
        if (dy < 0 && !isBlocked(carX, carY - 1)) {
            return 'N';
        }
    } else {
        if (dy > 0 && !isBlocked(carX, carY + 1)) {
            return 'S';
        }
        if (dy < 0 && !isBlocked(carX, carY - 1)) {
            return 'N';
        }
        if (dx > 0 && !isBlocked(carX + 1, carY)) {
            return 'E';
        }
        if (dx < 0 && !isBlocked(carX - 1, carY)) {
            return 'W';
        }

    }
 
    if (!isBlocked(carX + 1, carY)){ 
        return 'E';
    }
    if (!isBlocked(carX - 1, carY)) {
        return 'W';
    }
    if (!isBlocked(carX, carY + 1)) {
        return 'S';
    }   
    if (!isBlocked(carX, carY - 1)){
        return 'N';
    }

    return ' ';
}
