#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include "SussyUtility.hpp"
#include "Hittable.hpp" 
#include "Material.hpp"

class camera{
    private:
    int image_height;                   // Height of image in Pixels
    double pixel_samples_scale;         // Color scale factor for a sum of pixel samples
    vec4 camera_center;                 // Camera Center
    vec4 pixel00_location;              // Location of Pixel 0, 0
    vec4 pixel_delta_u;                 // Pixel offset to the right
    vec4 pixel_delta_v;                 // Pixel offset to the bottom
    vec4 u, v, w;			// Camera frame basis vectors
    vec4 defocus_disk_u;		// Defocus disk horizontal radius
    vec4 defocus_disk_v;		// Defocus disk vertical radius

    public:
    double  aspect_ratio      = 1.0;    // Image width / Image Height
    int     image_width       = 100;    // Width of image in Pixels
    int     samples_per_pixel = 10;     // Count of random samples for each pixel
    int     max_depth         = 10;	// Maximum number of ray reflections
    bool    sample_pixels     = true;

    double  vfov  = 90;				// Vertical View Angle(FOV)
    vec4 lookfrom = vec4(0.0, 0.0, 0.0, 1.0);	// Point the camera is looking from
    vec4 lookat   = vec4(0.0, 0.0,-1.0, 1.0);	// Point camera is looking at
    vec4 vup      = vec4(0.0, 1.0, 0.0, 1.0);   // Camera-relative up direction

    double defocus_angle = 0;           // Variation angle of rays through each pixel
    double focus_dist    = 10;		// Distance from the camera lookfrom point to plane of perfect focus

    private:
    void initialize(){
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height >= 1)?image_height:1;
        camera_center = lookfrom;

        // Inverse function
        pixel_samples_scale = 1.0 / samples_per_pixel;

        // Determine Viewport Dimensions
	double theta = sussy::deg_to_rad(vfov);
	double h = std::tan(theta/2);
        double viewport_height = 2 * h * focus_dist;
        double viewport_width = viewport_height * (double(image_width) / (image_height));

	// Calculate the u, v, w basis vectors for the camera coordinates
	w = lookfrom - lookat;
	u = cross3(vup, w);
	w /= w.length3();
	u /= u.length3();
	v = cross3(w, u);

        // Viewport Vectors
        vec4 viewport_u = u * viewport_width;
        vec4 viewport_v = v * -viewport_height;

        // Calculate Viewport Delta Vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Location of Upper Left Corner
        vec4 viewport_upper_left = camera_center - (w * focus_dist) - (viewport_u/2) - (viewport_v/2);
        pixel00_location = viewport_upper_left + ((pixel_delta_u + pixel_delta_v)/2);

	//Calculate the camera defocus disk basis vectors
	double defocus_radius = focus_dist * std::tan(sussy::deg_to_rad(defocus_angle/2));
	defocus_disk_u = u * defocus_radius;
	defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j){
    	// Construct a camera ray originating from the defocus disk and directed at a 
	// randomly sampled point around the pixel location i, j

        vec4 pixel_sample(0.0);

        if(sample_pixels){
            vec4 offset = sample_square();
            double offset_x = offset.x();
            double offset_y = offset.y();
            pixel_sample = pixel00_location
                            + (pixel_delta_u * (i + offset_x))
                            + (pixel_delta_v * (j + offset_y));
        } else {
            pixel_sample = pixel00_location + (pixel_delta_u * i)+ (pixel_delta_v * j);
        }
        
        vec4 ray_origin = (defocus_angle <= 0)?camera_center:defocus_disk_sample();
        vec4 ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec4 sample_square() const{
        return vec4(sussy::random_double() - 0.5, sussy::random_double() - 0.5, 0.0, 1.0);
    }

    vec4 defocus_disk_sample(){
	// Return a random point in the Camera Defocus Disk.
	vec4 p = random_in_unit_disk();
	return (camera_center + (defocus_disk_u * p[0]) + (defocus_disk_v * p[1]));
    }

    vec4 ray_colour(ray r, int depth, const hittable & world){
	if(depth <= 0){ return vec4(0.0, 0.0, 0.0, 1.0); }

        hit_record rec;
        if(world.hit(r, interval(0.0001, sussy::infinity), rec)){
	    ray scattered = ray(vec4(0.0), vec4(0.0));
	    vec4 attenuation;
	    if(rec.mat->scatter(r, rec, attenuation, scattered)){ 
	        vec4 temp = ray_colour(scattered, depth-1, world);
		return vec4(temp.x()*attenuation.x(), temp.y()*attenuation.y(), temp.z()*attenuation.z(), 1.0);
	    }
            return vec4(0.0, 0.0, 0.0, 1.0);
        }

        vec4 color_start = vec4(0.5, 0.7, 1.0, 1.0);
        vec4 color_end = vec4(1.0, 1.0, 1.0, 1.0);

        vec4 ray_dirn = r.dir();
        ray_dirn /= ray_dirn.length3();
        double a = (ray_dirn.y() + 1.0) * 0.5;

        return ((color_end * (1.0 - a)) + (color_start * a));
    }

    public:
    void render(const hittable & world){
        initialize();

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        vec4 currpixel;

        for(int j = 0; j < image_height; j++){
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for(int i = 0; i < image_width; i++){
                vec4 pixel_colour = vec4(0.0, 0.0, 0.0, 1.0);
                for(int sample = 0; sample < samples_per_pixel; sample++){
                    ray r = get_ray(i, j);
                    pixel_colour += ray_colour(r, max_depth, world);
                }
                print3colour(std::cout, pixel_colour * pixel_samples_scale, 256);
                std::cout << std::endl;
            }
        }
        std::clog << "\rDone.                  \n";
    }
};

#endif //CAMERA_HPP
