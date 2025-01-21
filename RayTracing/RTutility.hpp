#ifndef RTUTILITY_HPP
#define RTUTILITY_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#include "Vec3.hpp"
#include "Color.hpp"
#include "Interval.hpp"

// Constants
const double PI = 3.1415926535897932385;
const double RT_INFINITY = std::numeric_limits<double>::infinity();  // Defined here, usable after including RTutility.hpp

// Utility Functions
inline double radians(double degrees) {
    return degrees * PI / 180.0;
}

#endif // RTUTILITY_HPP