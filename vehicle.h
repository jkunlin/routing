#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct VehicleType {
    std::string name;
    double capacity;
    double speed;
    double cost_per_km;
};

#endif // VEHICLE_H

