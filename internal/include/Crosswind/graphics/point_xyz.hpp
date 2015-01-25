#pragma once 

#include <atomic>

class point_xyz{
public:
    point_xyz(double xpoint, double ypoint, double zpoint): x(xpoint), y(ypoint), z(zpoint){

    }


    std::atomic<double> x, y, z;
};
