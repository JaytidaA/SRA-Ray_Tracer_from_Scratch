#ifndef VEC4_HPP
#define VEC4_HPP

#include <array>
#include <ostream>

class vec4{
    private:
    std::array<double, 4> my_Elem;

    public:
    vec4(double value = 0.0){ my_Elem.fill(value); }
    vec4(double x, double y, double z, double w): my_Elem({x, y, z, w}){}
    ~vec4(){}

    public:
    // Element Access
    double x() const{ return my_Elem[0]; }
    double y() const{ return my_Elem[1]; }
    double z() const{ return my_Elem[2]; }
    double w() const{ return my_Elem[3]; }

    double & operator[](int);

    public:
    // Unary Minus
    vec4 operator-();

    // Vector Arithmetic
    vec4 operator+(vec4);
    vec4 operator-(vec4);

    // Shorthand Vector Arithmetic
    void operator+=(vec4);
    void operator-=(vec4);

    // Scalar Arithmetic
    vec4 operator+(double);
    vec4 operator-(double);
    vec4 operator*(double);
    vec4 operator/(double);

    // Shorthand Scalar Arithmetic
    void operator+=(double);
    void operator-=(double);
    void operator*=(double);
    void operator/=(double);

    public:
    // Printing out for PPM.
    friend std::ostream& operator<<(std::ostream &, const vec4 &);
};

#endif //VEC4_HPP