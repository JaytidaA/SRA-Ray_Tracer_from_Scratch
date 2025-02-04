#ifndef  EKL_RAY_HPP
#define  EKL_RAY_HPP

#include "eklVector.hpp"

namespace ekl{

class ray{
private:
	vector origin, direction;

public:
	ray(): origin(vector()), direction(vector()) {}
	ray(const vector & o, const vector & d): origin(o), direction(d) {}
	ray(const ray & other): origin(other.origin), direction(other.direction) {}

	~ray() = default;

public:
	vector r_ori() const{ return origin; }
	vector r_dir() const{ return direction; }
};

};

#endif //EKL_RAY_HPP
