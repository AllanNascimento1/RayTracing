#ifndef RTUTILITY_HPP
#define RTUTILITY_HPP

#include <memory>

#include "Interval.hpp"
#include "Vec3.hpp"

using std::shared_ptr;

// Constants - - - - - - - - - - - - - - - - - -
const double PI = 3.1415926535897932385;

/*
RT_INFINITY - from Interval
*/


// Utility Functions - - - - - - - - - - - - - - 
inline double radians(double degrees) {
    return degrees * PI / 180.0;
}

/*
randomDouble() - from Vec3
*/

#endif // RTUTILITY_HPP