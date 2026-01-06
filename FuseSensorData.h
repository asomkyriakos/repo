#pragma once
#include <vector>
#include <unordered_map>
#include "Sensors.h"

struct FusedData {
    std::string objectId;
    std::string type;
    int distance;
    double confidence;
    int x, y;
    int speed;
    char direction;
    std::string info;
};

//key = objectId
using Fuse = std::unordered_map<std::string, std::vector<FusedData>>;

Fuse fuseLidarData(const std::vector<SensorReading>& readings, double minConfidenceThreshold);

Fuse fuseRadarData(const std::vector<SensorReading>& readings, double minConfidenceThreshold);

Fuse fuseCameraData(const std::vector<SensorReading>& readings, double minConfidenceThreshold);

Fuse fuseAllSensors(const Fuse& lidar, const Fuse& radar, const Fuse& camera);
