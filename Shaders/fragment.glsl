out vec4 FragColor;
in vec2 TexCoord;

dvec3 ray_colour(ray r, int depth, sphere s){
	ray scattered = generateRay(dvec3(0.0), dvec3(0.0));
	dvec3 attenuation;
	dvec3 ret_colour = dvec3(1.0);
	hit_record hr;
	bool hit_sky = false;
	interval i = createInterval(0.0001, M_INFINITY);
	while(depth > 0 && !(hit_sky)){
		if(hitSphere(hr, s, r, i)){
			if(scatter(r, hr, attenuation, scattered)){
				r = scattered;
				ret_colour *= attenuation;
				depth--;
				continue;
			}
			else
			{
				return dvec3(0.0);
			}
		}

		hit_sky = true;
		dvec3 topColour = dvec3(0.5, 0.7, 1.0);
		dvec3 bottomColour = dvec3(1.0, 1.0, 1.0);
		double t = normalize(r.direction).y * 0.5 + 0.5;
		ret_colour *= mix(topColour, bottomColour, t);
	}

	if(!(hit_sky)){
		return dvec3(0.0);
	}
	return ret_colour;
}

void main()
{	
	double focal_length = 1.0;
	dvec3 lookFrom = dvec3(0.0, 0.0, 0.0);
	vec2 currentPixel = TexCoord*2.0 - 1.0;
	dvec3 lookAt = dvec3(vec2_to_dvec2(currentPixel), -focal_length);


	//uniform dvec3 sCenter;


	ray r = generateRay(lookFrom, lookAt-lookFrom);
	sphere s = createSphere(dvec3(0.0, 0.0, -2.0), 1.0, createMaterial(MAT_LAMBERTIAN, dvec3(0.2, 0.1, 0.2)));
    FragColor = vec4(dvec3_to_vec3(ray_colour(r, 10, s)), 1.0);
}

