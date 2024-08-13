#include "include/SussyUtility.hpp"

#include "include/Camera.hpp"
#include "include/Hittable.hpp"
#include "include/HittableList.hpp"
#include "include/Material.hpp"
#include "include/Sphere.hpp"
#include "include/Cylinder.hpp"

int main()
{
    // World
    hittable_list world;

    auto ground_material = std::make_shared<lambertian>(vec4(0.5, 0.5, 0.0, 1.0));
    world.add(std::make_shared<sphere>(vec4(0, -1000, 0, 1), 1000, ground_material));

    /*
    for(int a = -11; a < 11; a=a+2){
	for(int b = -11; b < 11; b=b+2){
	    double choose_mat = sussy::random_double();
	    vec4 center = vec4(a + 0.9*sussy::random_double(), 0.2, b + 0.9*sussy::random_double(), 1.0);

	    if((center - vec4(4, 0.2, 0, 1)).length3() > 0.9){
	    	std::shared_ptr<material> sphere_material;

		if(choose_mat < 0.8){
		    //Diffuse Material
		    vec4 r1 = random_vector();
		    vec4 r2 = random_vector();
		    vec4 albedo = vec4(r1.x() * r2.x(), r1.y() * r2.y(), r1.z() * r2.z(), 1.0);
		    sphere_material = std::make_shared<lambertian>(albedo);
		    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
		} else if(choose_mat < 0.95) {
		    //Metallic Material
		    vec4 albedo = random_vector(0.5, 1);
		    double fuzz = sussy::random_double(0, 0.5);
		    sphere_material = std::make_shared<metal>(albedo, fuzz);
		    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
		} else {
		    //Glass
		    sphere_material = std::make_shared<dielectric>(1.5);
		    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
		}
		}
	}}

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(vec4( 0,  1,  0, 1), 1.0, material1));
    
    auto material2 = std::make_shared<lambertian>(vec4(0.4, 0.2, 0.1, 1.0));
    world.add(std::make_shared<sphere>(vec4(-4,  1,  0, 1), 1.0, material2));
        
    auto material3 = std::make_shared<metal>(vec4(0.7, 0.6, 0.5, 1.0), 0.0);
    world.add(std::make_shared<sphere>(vec4(-1.0, 1.0, -1.0, 1.0), 1.0, material3));
    */
    
    
    vec4 disc_ctr = vec4(1, 1, 0, 1);
    vec4 disc_nrm = vec4(-1, 0, 0, 1);

    auto material_disc_1 = std::make_shared<lambertian>(vec4(0.3, 0.0, 0.8, 1.0));
    auto material_disc_2 = std::make_shared<metal>(vec4(1.0, 0.3, 0.7, 1.0), 0.3);
    auto material_disc_3 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<plane_disc>(disc_ctr, disc_nrm, 1, material_disc_1));
    world.add(std::make_shared<plane_disc>(disc_ctr + disc_nrm*2, disc_nrm, 1, material_disc_1));
    world.add(std::make_shared<cylinder>(disc_ctr + disc_nrm, -disc_nrm, 1, 2, material_disc_1));

    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth	  = 25;
    // cam.samples_per_pixel = 1;
    // cam.sample_pixels     = false;

    cam.vfov 		  = 20;
    cam.lookat		  = vec4( 0,  1,  0,  1);
    cam.lookfrom          = vec4( 10,  5,  10,  1);
    cam.vup               = vec4( 0,  1,  0,  1);

    cam.defocus_angle     = 0.8;
    cam.focus_dist        = 10;

    cam.render(world);

    return 0;
}
