#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "cube.h"
#include "material.h"
#include "color.h"
#include "rtweekend.h"

#include <iostream>
#include <memory>

int main() {
    // Image settings
    const int image_width = 800;
    const int image_height = 600;
    const int samples_per_pixel = 10;
    const int max_depth = 10;

    // Camera settings
    camera cam;
    cam.aspect_ratio = double(image_width) / image_height;
    cam.image_width = image_width;
    cam.vfov = 40.0;
    cam.lookfrom = vec3(3, 3, 2);
    cam.lookat = vec3(0, 0, -1);
    cam.vup = vec3(0, 1, 0);
    cam.focus_dist = 10.0;
    cam.defocus_angle = 0.0;

    // Create the scene directly in main
    hittable_list world;

    // Create materials
    auto red_material = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));

    // Add a single sphere to the scene
    world.add(std::make_shared<sphere>(vec3(0, 0, -5), 1.0, red_material));

    // Render the image
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, max_depth, world);
            }
            pixel_color /= samples_per_pixel;
            pixel_color = color(sqrt(pixel_color.x()), sqrt(pixel_color.y()), sqrt(pixel_color.z()));  // Gamma correction
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
