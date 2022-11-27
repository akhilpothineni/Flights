#pragma once

#include "Airports.h"

#include <cmath>
#include <iomanip>
#include <queue>
#include <algorithm>


class Calculate{
    public:
        //calculates flight path using the Haversine formula
        //input: latitude and longitude of 2 points 
        //output: distance between those two points
        long double calcFlightDistance(long double lat1, long double long1, long double lat2, long double long2);
};


