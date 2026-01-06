#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include "FuseSensorData.h"

// Lidar: distance, type, confidence
Fuse fuseLidarData(const std::vector<SensorReading>& readings, double minConfidence) {
    Fuse temp, fused;

    for (const auto& r : readings) {
        if (r.confidence < minConfidence) continue;

        FusedData d;
        d.objectId = r.objectId;
        d.type = r.type;
        d.distance = static_cast<int>(r.distance);
        d.confidence = r.confidence;
        temp[r.objectId].push_back(d);
    }


    for (const auto& [id, vec] : temp) {
        FusedData d;
        double totalConf = 0, weightedDist = 0;

        for (const auto& k : vec) {
            weightedDist += k.distance * k.confidence;
            totalConf += k.confidence;
        }

        if (totalConf > 0) {
            d.distance = static_cast<int>(weightedDist / totalConf + 0.5);
            d.confidence = totalConf / vec.size();
        }

        if (!vec.empty()) {
            d.objectId = vec[0].objectId;
            d.type = vec[0].type;
        }

        fused[id].push_back(d);
    }

    return fused;
}

// Radar: distance, speed, direction, confidence
Fuse fuseRadarData(const std::vector<SensorReading>& readings, double minConfidence) {
    Fuse temp, fused;

    for (const auto& r : readings) {
        if (r.confidence < minConfidence) continue;

        FusedData d;
        d.objectId = r.objectId;
        d.distance = static_cast<int>(r.distance);
        d.speed = r.speed;
        d.direction = r.direction;
        d.confidence = r.confidence;
        temp[r.objectId].push_back(d);
    }

    for (const auto& [id, vec] : temp) {
        FusedData d;
        double totalConf = 0, weightedDist = 0, weightedSpeed = 0;

        for (const auto& k : vec) {
            weightedDist += k.distance * k.confidence;
            weightedSpeed += k.speed * k.confidence;
            totalConf += k.confidence;
        }

        if (totalConf > 0) {
            d.distance = static_cast<int>(weightedDist / totalConf + 0.5);
            d.speed = static_cast<int>(weightedSpeed / totalConf + 0.5);
            d.confidence = totalConf / vec.size();
        }

        if (!vec.empty()) {
            d.objectId = vec[0].objectId;
            d.direction = vec[0].direction;
        }

        fused[id].push_back(d);
    }

    return fused;
}

// Camera: distance, type, confidence, x, y, speed, direction, info
Fuse fuseCameraData(const std::vector<SensorReading>& readings, double minConfidence) {
    Fuse temp, fused;

    for (const auto& r : readings) {
        if (r.confidence < minConfidence) continue;

        FusedData d;
        d.objectId = r.objectId;
        d.type = r.type;
        d.distance = static_cast<int>(r.distance);
        d.confidence = r.confidence;
        d.x = r.x;
        d.y = r.y;
        d.speed = r.speed;
        d.direction = r.direction;
        d.info = r.info;

        temp[r.objectId].push_back(d);
    }

    for (const auto& [id, vec] : temp) {
        FusedData d;
        double totalConf = 0, weightedDist = 0, weightedSpeed = 0;

        for (const auto& k : vec) {
            weightedDist += k.distance * k.confidence;
            weightedSpeed += k.speed * k.confidence;
            totalConf += k.confidence;
        }

        if (totalConf > 0) {
            d.distance = static_cast<int>(weightedDist / totalConf + 0.5);
            d.speed = static_cast<int>(weightedSpeed / totalConf + 0.5);
            d.confidence = totalConf / vec.size();
        }

        if (!vec.empty()) {
            d.objectId = vec[0].objectId;
            d.type = vec[0].type;
            d.x = vec[0].x;
            d.y = vec[0].y;
            d.direction = vec[0].direction;
            d.info = vec[0].info;
        }

        fused[id].push_back(d);
    }

    return fused;
}

Fuse fuseAllSensors(const Fuse& lidar, const Fuse& radar, const Fuse& camera) {
    Fuse finalFused;

    for (const auto& sensorSet : {lidar, radar, camera}) {
        for (const auto& [id, vec] : sensorSet) {
            FusedData d;
            d.objectId = id;

            if (!finalFused[id].empty()) d = finalFused[id][0];

            for (const auto& f : vec) {
                d.type = f.type;
                d.distance = f.distance;
                d.confidence = f.confidence;
                d.x = f.x;
                d.y = f.y;

                if (f.speed != 0 || f.type == "Moving") d.speed = f.speed;
                if (f.direction != ' ') d.direction = f.direction;
                if (!f.info.empty()) d.info = f.info;
            }

            finalFused[id].clear();
            finalFused[id].push_back(d);
        }
    }

    return finalFused;
}
