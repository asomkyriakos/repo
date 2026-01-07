#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include "FuseSensorData.h" 


int manhattan(int x1, int y1, int x2, int y2);

char decideNextMove(int carX, int carY, const Fuse& fused, const std::vector<std::pair<int,int>>& gpsPoints);
