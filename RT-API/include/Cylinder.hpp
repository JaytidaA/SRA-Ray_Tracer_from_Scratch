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
	plane_disc(){}
	plane_disc(const vec4 & ctr, const vec4 & nrml, double rad, std::shared_ptr<material> mat):
	center(ctr), normal(nrml), radius(rad), mat(mat){ normal/=normal.length3(); }

	bool hit(ray & r, interval ray_λ, hit_record & hr) const override{
		vec4 ctr = center;
		vec4 nrm = normal;

		double dot_dir_nrm = dot3(r.dir(), nrm);

		double denom = dot3((ctr - r.ori()), nrm);
		if(denom < 0) return false;

		double λ = denom/dot_dir_nrm;
		if(!ray_λ.contains(λ)) return false;

		vec4 temp_vec = r.at(λ) - ctr;
		if(temp_vec.length3squared() > radius*radius) return false;

		hr.hitpoint = r.at(λ);
		hr.λ = λ;
		hr.mat = mat;
		if(dot_dir_nrm < 0){
			hr.set_face_normal(r, nrm);
		} else{
			nrm *= -1.0;
			hr.set_face_normal(r, nrm);
		}

		return true;
	}
};

class cylinder: public hittable{
	private:
	vec4 center, axis;
	double radius, height;
	std::shared_ptr<material> mat;

	public:
	cylinder(){}
	cylinder(const vec4 & ctr, const vec4 & Axis, double radius, double height, std::shared_ptr<material> mat)
	:center(ctr), axis(Axis), radius(radius), height(height), mat(mat) { axis/=axis.length3(); }

	bool hit(ray & r, interval ray_λ, hit_record & hr) const override{
		vec4 r_dir = r.dir(), r_ori = r.ori();
		vec4 ctr = center;
		vec4 axis_dir = axis;

		vec4 r_dir_proj = r_dir - (axis_dir * dot3(axis_dir, r_dir));
		vec4 or_c = (r_ori - ctr);
		vec4 or_c_proj = or_c - (axis_dir * dot3(axis_dir, or_c));
		
		double a = r_dir_proj.length3squared();
		double h = dot3(or_c_proj, r_dir_proj);
		double c = or_c_proj.length3squared() - radius*radius;
		double determinant = h*h - a*c;
		
		if(determinant < 0) return false;

		double sqrtd = std::sqrt(determinant);
		double root = (-h-sqrtd)/a;
		if(!ray_λ.contains(root)){
			root = (-h+sqrtd)/a;
			if(!ray_λ.contains(root)){ return false; }
		}

		vec4 hitpoint = r.at(root);

		double height_proj = dot3(hitpoint-ctr, axis_dir);
		if(height_proj < -height/2 || height_proj > height/2) return false;

		vec4 outward_normal = (hitpoint - (ctr + (axis_dir * height_proj)))/radius;

		hr.λ = root;
		hr.hitpoint = hitpoint;
		hr.mat = mat;
		hr.set_face_normal(r, outward_normal);
		return true;
	}
};

#endif //CYLINDER_HPP
