#ifndef VEC4_HPP
#define VEC4_HPP

#include <array>
#include <ostream>
#include <cmath>

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
    vec4 operator+(const vec4 &);
    vec4 operator-(const vec4 &);

    // Vector-Vector Products
    friend double dot3(const vec4 &, const vec4 &);
    friend vec4 cross3(const vec4 &, const vec4 &);

    // Shorthand Vector Arithmetic
    void operator+=(const vec4 &);
    void operator-=(const vec4 &);

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
    // Length in 3 dimensions
    double length3() const{
        return std::sqrt(
            my_Elem[0] * my_Elem[0] +
            my_Elem[1] * my_Elem[1] +
            my_Elem[2] * my_Elem[2]
        );
    }

    double length3squared() const{
        return (
            my_Elem[0] * my_Elem[0] +
            my_Elem[1] * my_Elem[1] +
            my_Elem[2] * my_Elem[2]
        );
    }

    // What the name says
    double euclidean_norm() const{
        return std::sqrt(
            my_Elem[0] * my_Elem[0] +
            my_Elem[1] * my_Elem[1] +
            my_Elem[2] * my_Elem[2] +
            my_Elem[3] * my_Elem[3]
        );
    }

    // Print the first 3 elements
    friend void print3(std::ostream &, const vec4 &);

    // Print the first 3 elements as colours
    friend void print3colour(std::ostream &, const vec4 &, int);
};

#endif //VEC4_HPP