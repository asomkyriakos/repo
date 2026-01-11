#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include "FuseSensorData.h"


int manhattan(int x1, int y1, int x2, int y2);

std::pair<char, char> decideNextMove(int carX,int carY,char currentDir,int currentSpeed,const Fuse& fused,const std::vector<std::pair<int,int>>& gpsPoints);
