#ifndef  EKL_VECTOR_HPP
#define  EKL_VECTOR_HPP

namespace ekl{

class vector{
private:
	float x, y, z, w;

public:
	vector(float a = 0.0f): x(a), y(a), z(a), w(a) {}
	vector(float a, float b, float c, float d): x(a), y(b), z(c), w(d) {}
	vector(const vector & other): x(other.x), y(other.y), z(other.z), w(other.w) {}

	~vector() = default;

public:
	friend vector operator + (const vector &, const vector &);
	friend vector operator - (const vector &, const vector &);
	friend vector operator * (const float, const vector &);
	friend vector operator * (const vector &, const float);
	friend vector operator / (const vector &, const float);

public:
	float norm();
	float norm3();
	float norm3squared();

};

};

#endif //EKL_VECTOR_HPP
