#ifndef VEC4_HPP
#define VEC4_HPP

#include <ostream>

class vec4{
	private:
	double el[4];

	public:
	vec4(double init = 0.0):el[0](init), el[1](init), el[2](init), el[3](init){}
	vec4(double x, double y, double z, double w):el[0](x), el[1](y), el[2](z), el[3](w){}
	vec4(double arr[4]): el[0](arr[0]), el[1](arr[1]), el[2](arr[2]), el[3](arr[3]){}

	friend vec4 operator* (const vec4 &, double);
	friend vec4 operator* (double, const vec4 &);

	friend double dot3(const vec4 &, const vec4 &);
	friend vec4 cross3(const vec4 &, const vec4 &);

	//TODO: Overload * opeartor from smat4

	double length3() const;
	double length3squared() const;
	double euclidean_norm() const;

	double x() const{ return el[0]; }
	double y() const{ return el[1]; }
	double z() const{ return el[2]; }
	double w() const{ return el[3]; }

	double & operator[](int);

	friend ostream & operator<<(ostream &, const vec4 &);
};

#endif //VEC4_HPP
