#ifndef RAY_HPP
#define RAY_HPP

#include "Vec4.hpp"
#include "SqMatrix4.hpp"

class ray{
	private:
	vec4 origin, direction;

	public:
	ray(): origin(vec4()), direction(vec4()){}
	ray(const vec4 & dir): origin(vec4()), direction(dir){}
	ray(const vec4 & ori, const vec4 & dir): origin(ori), direction(dir){}

	const vec4 & ori() const{ return origin; }
	const vec4 & dir() const{ return direction; }

	vec4 at(double λ) const;
};

#endif //RAY_HPP
