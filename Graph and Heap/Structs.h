#pragma once

#include <cmath>

struct IdPair
{
    int vertexId0;
    int vertexId1;
};

struct Double3
{
    double x, y, z;

    static double Distance(Double3 left, Double3 right);
};

inline
double Double3::Distance(Double3 left, Double3 right)
{
    //TODO
    double left_x=left.x;
    double left_y=left.y;
    double left_z=left.z;
    double right_x=right.x;
    double right_y=right.y;
    double right_z=right.z;
    double filter_parameter= sqrt(pow(left_x-right_x,2)+pow(left_y-right_y,2)+pow(left_z-right_z,2));
    return filter_parameter;
}