#ifndef  EKL_VECTOR_HPP
#define  EKL_VECTOR_HPP

namespace ekl{

#pragma pack(push, 1)
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
	float e_norm() const;
	float e_norm3() const;
	float e_norm3squared() const;

	const float * data() const;

};
#pragma pack(pop)

};

#endif //EKL_VECTOR_HPP
