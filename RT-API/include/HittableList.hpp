#ifndef HITTABLELIST_HPP
#define HITTABLELIST_HPP

#include <memory>
#include <vector>
#include "Hittable.hpp"

class hittable_list: public hittable{
    public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list(){}
    hittable_list(std::shared_ptr<hittable> object){ add(object); }

    void clear(){ objects.clear(); }

    void add(const std::shared_ptr<hittable> & object){ objects.push_back(object); }

    bool hit(ray & r, interval ray_λ, hit_record & hr) const{
        hit_record temp_record;
        bool hit_anything = false;
        double closest_current = ray_λ.max;

        for(const auto& obj_ptr: objects){
            if(obj_ptr->hit(r, interval(ray_λ.min, closest_current), temp_record)){
                hit_anything = true;
                closest_current = temp_record.λ;
                hr = temp_record;
            }
        }
        return hit_anything;
    }
};

#endif //HITTABLELIST_HPP