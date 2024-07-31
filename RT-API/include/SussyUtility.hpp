#ifndef SUSSYUTILITY_HPP
#define SUSSYUTILITY_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

namespace sussy{

    // Constants
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // Utility Functions
    inline double deg_to_rad(double degrees) {
        return degrees * pi / 180.0;
    }

    inline double random_double(double min = 0.0, double max = 1.0) {
        // Returns a random double in between [0, 1)
        return (min + ((max - min) * (std::rand() / (RAND_MAX + 1.0))));
    }

};

#include "Vec4.hpp"
#include "Ray.hpp"
#include "Interval.hpp"

vec4 random_vector(double min = 0.0, double max = 1.0){
    return vec4(
        sussy::random_double(min, max),
        sussy::random_double(min, max),
        sussy::random_double(min, max),
        1.0
    );
}

inline vec4 random_in_unit_sphere() {
    while (true) {
        vec4 p = random_vector(-1,1);
        if (p.length3squared() < 1)
            return p;
    }
}

inline vec4 random_unit_vector() {
    vec4 p = random_in_unit_sphere();
    p /= p.length3();
    return p;
}

inline vec4 random_on_hemisphere(const vec4 & normal) {
    vec4 on_unit_sphere = random_unit_vector();
    if (dot3(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

#endif //SUSSYUTILITY_HPP