#include <iostream>
#include "include/Vec4.hpp"

int main()
{
    int width = 800;
    int height = 600;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    vec4 colorstart = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 colorend = vec4(1.0, 1.0, 0.0, 1.0);
    vec4 currpixel;

    for(int j = 0; j < height; j++){
    std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
    for(int i = 0; i < width; i++){
        currpixel = (colorstart * (height - j))/height + (colorend * j)/height;
        currpixel *= 255.999;
        int arr[] = {(int)currpixel.x(), (int)currpixel.y(), (int)currpixel.z()};
        std::cout << arr[0] << " " << arr[1] << " " << arr[2] << std::endl;
    }}
    std::clog << "\rDone.                  \n";

    return 0;
}