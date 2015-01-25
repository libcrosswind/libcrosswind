#pragma once 

#include <atomic>

class dimension_xyz{
public:
    dimension_xyz(double w, double h, double d): width(w), height(h), depth(d){

    }


    std::atomic<double> width, height, depth;
};
