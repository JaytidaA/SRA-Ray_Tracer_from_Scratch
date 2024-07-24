#include <iostream>
#include "include/Vec4.hpp"
#include "include/Ray.hpp"

bool hit_sphere(const vec4 & center, double radius, const ray & r){
    vec4 ray_ori = r.ori();
    vec4 ray_dir = r.dir();
    vec4 or_c = -(ray_ori - center);
    double a = ray_dir.length3squared();
    double b = -2 * dot3(r.dir(), or_c);
    double c = or_c.length3squared() - (radius * radius);
    return (b * b >= 4.0 * a * c);
}

vec4 ray_colour(ray r, int image_height){
    vec4 ctr = vec4(100.0, -100.0, 2.0, 1.0);
    double rad = 10.0;
    bool hit = hit_sphere(ctr, rad, r);
    if(hit){ return vec4(1.0, 0.0, 0.0, 1.0); }

    vec4 color_start = vec4(0.5, 0.7, 1.0, 1.0);
    vec4 color_end = vec4(1.0, 1.0, 1.0, 1.0);

    vec4 ray_dirn = r.dir();
    double a = ((ray_dirn.y()/image_height) + 1.0);

    return ((color_end * (1.0 - a)) + (color_start * a));
}

int main()
{
    // Image
    double aspect_ratio = 16.0/9.0;
    int image_width = 800;
    
    // Calculate the image height
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height >= 1)?image_height:1;

    // Camera Setup
    double focal_length = 1.0;
    double viewport_height = 2.25;
    double viewport_width = viewport_height * (double(image_width) / (image_height));
    vec4 camera_center = vec4(0.0, 0.0, 0.0, 1.0);

    // Viewport Vectors
    vec4 viewport_u = vec4(viewport_width, 0.0, 0.0, 1.0);
    vec4 viewport_v = vec4(0.0, -viewport_height, 0.0, 1.0);
    vec4 pixel_delta_u = viewport_u / viewport_width;
    vec4 pixel_delta_v = viewport_v / viewport_height;

    // Location of Upper Left Corner
    vec4 viewport_upper_left = camera_center + vec4(0.0, 0.0, -focal_length, 1.0) - (viewport_u/2) - (viewport_v/2);
    vec4 pixel00_location = viewport_upper_left + ((pixel_delta_u + pixel_delta_v)/2);


    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // std::cout << "Image lengths: " << image_width << " " << image_height << std::endl;
    // std::cout << "Viewport lengths: " << viewport_width << " " << viewport_height << std::endl;
    // std::cout << "Pixel delta u: ";
    // print3(std::cout, pixel_delta_u);
    // std::cout << std::endl << "Pixel delta v: ";
    // print3(std::cout, pixel_delta_v);
    // std::cout << std::endl << "Viewport upper left: ";
    // print3(std::cout, viewport_upper_left);
    // std::cout << std::endl << "Pixel 00: ";
    // print3(std::cout, pixel00_location);
    // std::cout << std::endl;

    vec4 currpixel;

    for(int j = 0; j < image_height; j++){
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for(int i = 0; i < image_width; i++){
        currpixel = pixel00_location + (pixel_delta_u * i) + (pixel_delta_v * j);
        vec4 ray_dirn = currpixel - camera_center;
        ray r = ray(camera_center, ray_dirn);
        vec4 colour_of_current_pixel = ray_colour(r, image_height);
        print3colour(std::cout, colour_of_current_pixel, 256);
        std::cout << std::endl;
    }}
    std::clog << "\rDone.                  \n";

    return 0;
}