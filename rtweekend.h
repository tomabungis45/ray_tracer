#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// util functions

inline double degrees_to_radians(const double &degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // return a random real in [0,1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // random number in [min, max)
    return min + (max - min) * random_double();
}

// common headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif