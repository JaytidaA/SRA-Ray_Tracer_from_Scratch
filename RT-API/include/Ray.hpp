#ifndef RAY_HPP
#define RAY_HPP

#include "Vec4.hpp"

class ray{
    private:
    vec4 origin;
    vec4 direction;

    public:
    ray(const vec4 & ori, const vec4 & dir): origin(ori), direction(dir) {};

    // Any point on the ray
    vec4 at(double λ){ return origin + direction * λ; }

    // Element Access
    const vec4 & ori() const{ return origin; }
    const vec4 & dir() const{ return direction; }
};

#endif //RAY_HPP