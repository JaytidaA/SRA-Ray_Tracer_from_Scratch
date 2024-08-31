layout (local_size_x = 32, local_size_y = 32, local_size_z = 1) in;
layout (rgba8, binding = 0) uniform image2D uTexture;

void main()
{
	double focal_length = 1.0;
	dvec3 lookFrom   = vec3_to_dvec3(vec3(0.0, 0.0, 0.0));
	dvec2 TexCoords  = ivec2_to_dvec2(ivec2(gl_GlobalInvocationID.xy))/640;
	dvec2 currPixel  = TexCoords * 2.0 - 1.0;
	dvec3 lookAt     = dvec3(currPixel, -focal_length);
	ray   currentRay = generateRay(lookFrom, lookAt-lookFrom);

	material M0 = createMaterial(MAT_LAMBERTIAN, dvec3(0.5, 0.5, 0.0));
	material M1 = createMaterial(MAT_LAMBERTIAN, dvec3(1.0, 0.0, 0.0));
	material M2 = createMaterial(MAT_DIELECTRIC, 1.5);
	material M3 = createMaterial(MAT_METAL, dvec3(0.7, 0.7, 0.7), 0.2);
	world    W0;
	W0.sphDefined = 1;
	W0.cylDefined = 0;
	W0.cubDefined = 2;
	W0.sphEl[0] = createSphere(dvec3( 0.0, -1000.5, -2.0), 1000.0, M0);
	//W0.sphEl[1] = createSphere(dvec3(0.0,  0.0, -2.0), 0.5, M1);
	//W0.sphEl[2] = createSphere(dvec3( 2.0,  0.0, -2.0), 0.5, M3);
	//W0.cylEl[0] = createCylinder(dvec3(-1.0, 0.0, -2.0), dvec3(0.0, 1.0, 0.5), 0.5, 1.0, M1);
	dvec3 some_rv = dvec3(1, 1, 1);
	double some_db = sqrt(3)/2.0;
	W0.cubEl[0] = createCube(dvec3( 1.0, 0.2, -2.0), some_db * normalize(some_rv), M3);
	W0.cubEl[1] = createCube(dvec3(-1.0, 0.2, -2.0), some_db * normalize(some_rv), M1);

	dvec3 colour = dvec3(0.0);
	colour = ray_colour(currentRay, 20, W0);

	imageStore(uTexture, ivec2(gl_GlobalInvocationID.xy), vec4(dvec3_to_vec3(colour), 1.0));
}
