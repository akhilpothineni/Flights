#include "Calculate.h"

//using the Haversine formula
long double Calculate::calcFlightDistance(long double lat_1, long double long_1, long double lat_2, long double long_2){
    long double conv = 3.14159265358979323846 / 180;
    long double ret = 0.5 - cos((lat_2 - lat_1) * conv) / 2 + cos(lat_1 * conv) * 
        cos(lat_2 * conv) * (1-cos((long_2 - long_1) * conv)) / 2;
    //got distance in radians convert to km
    ret = asin(sqrt(ret));
    return 12756.2 * ret;
}