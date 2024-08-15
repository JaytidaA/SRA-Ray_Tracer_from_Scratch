#ifndef VEC4_HPP
#define VEC4_HPP

#include <ostream>

class vec4{
	private:
	double el[4];

	public:
	vec4(double init = 0.0):el{init, init, init, init}{}
	vec4(double x, double y, double z, double w):el{x, y, z, w}{}
	vec4(double arr[4]): el{arr[0], arr[1], arr[2], arr[3]}{}

	friend vec4 operator* (const vec4 &, double);
	friend vec4 operator* (double, const vec4 &);
	void operator*= (double);
	vec4 operator/  (double) const;
	void operator/= (double);

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

	friend std::ostream & operator<<(std::ostream &, const vec4 &);
};

#endif //VEC4_HPP
