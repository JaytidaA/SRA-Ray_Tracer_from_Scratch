#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include "Hittable.hpp"

class sphere: public hittable{
    private:
    vec4 center;
    double radius;

    public:
    sphere(const vec4 & ctr, double rad): center(ctr), radius(std::fmax(0.0, rad)){}

    bool hit(ray & r, interval ray_λ, hit_record & hr) const{
        vec4 ray_ori = r.ori();
        vec4 ray_dir = r.dir();
        vec4 or_c = -(ray_ori - center);
        double a = ray_dir.length3squared();
        double h = dot3(ray_dir, or_c);
        double c = or_c.length3squared() - (radius * radius);
        double determinant = (h*h) - (a*c);
    
        if(determinant < 0){ return false; }

        double sqrtd = std::sqrt(determinant);

        //Nearest root that lies in the acceptable range
        double root = (h - sqrtd)/a;
        if(!ray_λ.surrounds(root)){
            root = (h + sqrtd)/a;
            if(!ray_λ.surrounds(root)){ return false; }
        }

        hr.λ = root;
        hr.hitpoint = r.at(hr.λ);
        vec4 outward_normal = (hr.hitpoint - center) / radius;
        hr.set_face_normal(r, outward_normal);

        return true;
    }
};

#endif