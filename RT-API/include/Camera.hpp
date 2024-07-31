#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include "SussyUtility.hpp"
#include "Hittable.hpp" 

class camera{
    private:
    int image_height;                   // Height of image in Pixels
    double pixel_samples_scale;         // Color scale factor for a sum of pixel samples
    vec4 camera_center;                 // Camera Center
    vec4 pixel00_location;              // Location of Pixel 0, 0
    vec4 pixel_delta_u;                 // Pixel offset to the right
    vec4 pixel_delta_v;                 // Pixel offset to the bottom

    public:
    double  aspect_ratio      = 1.0;    // Image width / Image Height
    int     image_width       = 100;    // Width of image in Pixels
    int     samples_per_pixel = 10;     // Count of random samples for each pixel
    bool    sample_pixels     = true;

    private:
    void initialize(){
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height >= 1)?image_height:1;
        camera_center = vec4(0.0, 0.0, 0.0, 1.0);

        // Inverse function
        pixel_samples_scale = 1.0 / samples_per_pixel;

        // Determine Viewport Dimensions
        double focal_length = 1.0;
        double viewport_height = 2.25;
        double viewport_width = viewport_height * (double(image_width) / (image_height));

        // Viewport Vectors
        vec4 viewport_u = vec4(viewport_width, 0.0, 0.0, 1.0);
        vec4 viewport_v = vec4(0.0, -viewport_height, 0.0, 1.0);

        // Calculate Viewport Delta Vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Location of Upper Left Corner
        vec4 viewport_upper_left = camera_center + vec4(0.0, 0.0, -focal_length, 1.0) - (viewport_u/2) - (viewport_v/2);
        pixel00_location = viewport_upper_left + ((pixel_delta_u + pixel_delta_v)/2);
    }

    ray get_ray(int i, int j){
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
        
        vec4 ray_origin = camera_center;
        vec4 ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec4 sample_square() const{
        return vec4(sussy::random_double() - 0.5, sussy::random_double() - 0.5, 0.0, 1.0);
    }

    vec4 ray_colour(ray r, const hittable & world){
        hit_record rec;
        if(world.hit(r, interval(0.0, sussy::infinity), rec)){
            vec4 direction = random_on_hemisphere(rec.normal);
            return (ray_colour(ray(rec.hitpoint, direction), world) * 0.5);
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
                    pixel_colour += ray_colour(r, world);
                }
                print3colour(std::cout, pixel_colour * pixel_samples_scale, 256);
                std::cout << std::endl;
            }
        }
        std::clog << "\rDone.                  \n";
    }
};

#endif //CAMERA_HPP