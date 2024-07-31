#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "SussyUtility.hpp"

struct hit_record{
    vec4 hitpoint;
    vec4 normal;
    double λ;
    bool out_face;

    void set_face_normal(ray & r, vec4 & outward_normal){
        out_face = (dot3(r.dir(), outward_normal) < 0);
        normal = out_face ? outward_normal : (outward_normal * -1.0);
    }
};

class hittable{
    public:
    //Virtual destructor
    virtual ~hittable() = default;
    virtual bool hit(ray &, interval, hit_record &) const= 0;
};

#endif //HITTABLE_HPP