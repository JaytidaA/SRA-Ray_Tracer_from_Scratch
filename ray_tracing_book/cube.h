#ifndef CUBE_H
#define CUBE_H

#include <cmath>
#include "hittable.h"
#include "material.h"
#include "vec3.h"
#include "rtweekend.h"

class cube : public hittable {
private:
    vec3 center;
    vec3 half_sizes;
    std::shared_ptr<material> mat;

public:
    cube() : center(vec3(0.0, 0.0, 0.0)), half_sizes(vec3(0.0, 0.0, 0.0)), mat(nullptr) {}

    cube(const vec3 &center, const vec3 &half_sizes, const std::shared_ptr<material> &mat)
        : center(center), half_sizes(half_sizes), mat(mat) {}

    bool hit(const ray& r, interval ray_t, hit_record &rec) const override {
        vec3 r_ori = r.origin();
        vec3 r_dir = r.direction();
        
        double tmin = (center.x() - half_sizes.x() - r_ori.x()) / r_dir.x();
        double tmax = (center.x() + half_sizes.x() - r_ori.x()) / r_dir.x();

        if (tmin > tmax) std::swap(tmin, tmax);

        double tymin = (center.y() - half_sizes.y() - r_ori.y()) / r_dir.y();
        double tymax = (center.y() + half_sizes.y() - r_ori.y()) / r_dir.y();

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        double tzmin = (center.z() - half_sizes.z() - r_ori.z()) / r_dir.z();
        double tzmax = (center.z() + half_sizes.z() - r_ori.z()) / r_dir.z();

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax)) return false;

        if (tmin < ray_t.min || tmin > ray_t.max) return false;

        rec.t = tmin;
        rec.p = r.at(tmin);

        vec3 outward_normal;
        if (std::abs(rec.p.x() - (center.x() - half_sizes.x())) < 0.00001)
            outward_normal = vec3(-1, 0, 0);
        else if (std::abs(rec.p.x() - (center.x() + half_sizes.x())) < 0.00001)
            outward_normal = vec3(1, 0, 0);
        else if (std::abs(rec.p.y() - (center.y() - half_sizes.y())) < 0.00001)
            outward_normal = vec3(0, -1, 0);
        else if (std::abs(rec.p.y() - (center.y() + half_sizes.y())) < 0.00001)
            outward_normal = vec3(0, 1, 0);
        else if (std::abs(rec.p.z() - (center.z() - half_sizes.z())) < 0.00001)
            outward_normal = vec3(0, 0, -1);
        else
            outward_normal = vec3(0, 0, 1);

        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }
};

#endif // CUBE_H
