#include "include/SussyUtility.hpp"

#include "include/Camera.hpp"
#include "include/Hittable.hpp"
#include "include/HittableList.hpp"
#include "include/Sphere.hpp"

int main()
{
    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(vec4(0.0, 0.0, -1.0, 1.0), 0.5));
    world.add(std::make_shared<sphere>(vec4(0.0, -100.5, 0.0, 1.0), 100.0));

    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 100;
    // cam.samples_per_pixel = 1;
    // cam.sample_pixels     = false;

    cam.render(world);

    return 0;
}