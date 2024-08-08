#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "SussyUtility.hpp"

struct hit_record;

class material{
    public:
    virtual ~material() = default;

    virtual bool scatter(const ray & r_in, hit_record & rec, vec4 & attenuation, ray & scattered) const{ return false; }
};

class lambertian: public material{
    private:
    vec4 albedo;

    public:
    lambertian(const vec4 & albedo): albedo(albedo){}

    bool scatter(const ray & r_in, hit_record & rec, vec4 & attenuation, ray & scattered) const override{
	vec4 scattered_direction = rec.normal + random_unit_vector();
	if(scattered_direction.near_zero3()){ scattered_direction = rec.normal; }
	scattered = ray(rec.hitpoint, scattered_direction);
	attenuation = albedo;
	return true;
    }
};

class metal: public material{
    private:
    vec4 albedo;
    double fuzz;

    public:
    metal(const vec4 & albedo, double fuzz): albedo(albedo), fuzz(fuzz){}

    bool scatter(const ray & r_in, hit_record & rec, vec4 & attenuation, ray & scattered) const override{
	vec4 rin_dir = r_in.dir();
	vec4 reflected = reflect(rin_dir, rec.normal) + (random_unit_vector() * fuzz);
	scattered = ray(rec.hitpoint, reflected);
	attenuation = albedo;
	return (dot3(scattered.dir(), rec.normal) > 0);
    }
};

class dielectric: public material{
    private:
    double refraction_index;

    private:
    static double reflectance(double cosine, double ri){
	// Use Schlick's Approximation for reflectance
	double r0 = (1.0 - ri)/(1.0 + ri);
	r0 *= r0;
	return (r0 + (1-r0)*std::pow((1-cosine), 5));
    }

    public:
    dielectric(double ri): refraction_index(ri){}

    bool scatter(const ray & r_in, hit_record & rec, vec4 & attenuation, ray & scattered) const override{
        attenuation = vec4(1.0, 1.0, 1.0, 1.0);
	double ri = rec.out_face ? (1.0/refraction_index):refraction_index;

	vec4 rin_dir = r_in.dir();
	vec4 unit_direction = rin_dir/rin_dir.length3();
	vec4 refracted = refract(unit_direction, rec.normal, ri);

        double cos_theta = std::fmin(dot3(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = (ri * sin_theta) > 1.0;
        vec4 direction;

        if(cannot_refract || reflectance(cos_theta, ri) > sussy::random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

	scattered = ray(rec.hitpoint, direction);
	return true;
    }
};

#endif //MATERIAL_HPP
