#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <cmath>
#include "Hittable.hpp"

class plane_disc: public hittable{
	private:
	vec4 center, normal;
	double radius;
	std::shared_ptr<material> mat;

	public:
	plane_disc(const vec4 & ctr, const vec4 & nrml, double rad, const std::shared_ptr<material> mat)
	: center(ctr), normal(nrml), radius(rad), mat(mat){ normal /= normal.length3(); }

	bool hit(ray & r, interval ray_λ, hit_record & hr) const{
		//\vec{r}\cdot\vec{n} = \vec{a}\cdot\vec{n}
		vec4 r_ori = r.ori();
		vec4 r_dir = r.dir();

		double denom = dot3(r_dir, normal);
		if(denom > 0.000001){
			double λ = -dot3(r_ori-center, normal)/denom;
			if(λ < ray_λ.min || λ > ray_λ.max) return false;

			vec4 hitpoint = r.at(λ);

			if((hitpoint - center).length3squared() <= radius*radius){
				hr.hitpoint = hitpoint;
				hr.λ = λ;
				hr.mat = mat;
				vec4 outward_normal = normal;
				hr.set_face_normal(r, outward_normal);
				return true;
			}
		}
		return false;
	}
};

/*
class cylinder: public hittable{
	private:
	vec4 center;
	ray axis;
	double radius, height;
	std::shared_ptr<material> mat;

	public:
	cylinder(): center(vec4(0.0)), axis(ray(vec4(0.0), vec4(0.0))), radius(0), height(0){}
	cylinder(vec4 center, vec4 axis, double radius, double height, std::shared_ptr<material> mat)
	: center(center), axis(ray(center, axis)), radius(radius), height(height), mat(mat) {}

	bool hit(ray r, interval ray_λ, hit_record hr){
		
	}
};
*/

#endif //CYLINDER_HPP
