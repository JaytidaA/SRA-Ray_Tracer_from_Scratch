#ifndef SUSSYUTILITY_HPP
#define SUSSYUTILITY_HPP

#include <cmath>
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

};

#endif //SUSSYUTILITY_HPP