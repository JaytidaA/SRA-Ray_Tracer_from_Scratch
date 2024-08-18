bool scatter(const ray r_in, inout hit_record hr, inout dvec3 attenuation, inout ray scattered){
	if((hr.mat).type == MAT_LAMBERTIAN){
		dvec3 scattered_direction = hr.normal + normalize(prand_dvec3());
		if(nearzero3(scattered_direction)){ scattered_direction = hr.normal; }
		scattered = generateRay(hr.hitpoint, scattered_direction);
		attenuation = (hr.mat).albedo;
		return true;
	}
	else{ return false; }
}
