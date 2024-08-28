#version 430

layout (local_size_x = 32, local_size_y = 32, local_size_z = 1) in;
layout (rgba8, binding = 0) uniform image2D uTexture;

dvec3 ray_colour(ray r, int depth, cube c) {
    hit_record hr;
    ray   scattered   = generateRay(dvec3(0.0), dvec3(0.0));
    dvec3 attenuation = dvec3(0.0);
    interval i        = createInterval(0.0001, M_INFINITY);
    bool hit_sky      = false;
    dvec3 retColour   = dvec3(1.0);

    while(depth > 0) {
        if(hitCube(hr, c, r, i)) {
            if(scatter(r, hr, attenuation, scattered)) {
                r = scattered;
                retColour *= attenuation;
                depth--;
                continue;
            }
            break;
        }
        hit_sky = true;
        break;
    }

    if(hit_sky) {
        dvec3 topColour    = dvec3(0.5, 0.7, 1.0);
        dvec3 bottomColour = dvec3(1.0, 1.0, 1.0);
        double t           = r.direction.y * 0.5 + 0.5;
        retColour         *= mix(topColour, bottomColour, t);
    } else {
        retColour = dvec3(0.0);
    }

    return retColour;
}

void main() {
    double focal_length = 1.0;
    dvec3 lookFrom   = dvec3(0.0, 0.0, 0.0); // Changed to avoid unnecessary conversions
    ivec2 currPixel  = ivec2(gl_GlobalInvocationID.xy);
    dvec3 lookAt     = dvec3(currPixel.x / 512.0 - 1.0, currPixel.y / 512.0 - 1.0, -focal_length); // Normalize coordinates
    ray   currentRay = generateRay(lookFrom, lookAt - lookFrom);

    material M0 = createMaterial(MAT_DIELECTRIC, 1.5);
    material M1 = createMaterial(MAT_LAMBERTIAN, dvec3(1.0, 0.0, 0.0));
    
    cube C0 = createCube(dvec3(0.0, 0.0, -2.0), dvec3(0.5, 0.5, 0.5), M0);

    dvec3 colour = ray_colour(currentRay, 2, C0);

    // Write the final color to the image texture
    imageStore(uTexture, currPixel, vec4(colour, 1.0));
}
