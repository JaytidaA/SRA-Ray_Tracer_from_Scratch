double reflectance(double cosine, double ri){
	// Use Schlick's Approximation for reflectance
	double r0 = (1.0 - ri)/(1.0 + ri);
	r0 *= r0;
	return r0 + (1.0-r0)*double(pow(float(1-cosine), 5.0f));
}

bool scatter(const ray r_in, inout hit_record hr, inout dvec3 attenuation, inout ray scattered){
	if(hr.mat.type == MAT_LAMBERTIAN)
	{
		dvec3 scattered_direction = hr.normal + normalize(prand_dvec3(hr.normal));
		if(nearzero3(scattered_direction)){ scattered_direction = hr.normal; }
		scattered = generateRay(hr.hitpoint, scattered_direction);
		attenuation = (hr.mat).albedo;
		return true;
	}
	else if(hr.mat.type == MAT_METAL)
	{
		if (dot(r_in.direction, hr.normal) >= 0){ return false; }

		dvec3 reflected = reflect(r_in.direction, hr.normal);
		if(hr.mat.f_or_d > 0.0){ reflected += hr.mat.f_or_d * normalize(prand_dvec3(reflected)); }
		scattered = generateRay(hr.hitpoint, reflected);
		attenuation = (hr.mat).albedo;
		return true;
	}
	else if(hr.mat.type == MAT_DIELECTRIC)
	{
		attenuation = dvec3(1.0);
		double ri   = (hr.outface)?double(1/hr.mat.f_or_d):hr.mat.f_or_d;

		dvec3 unit_dirn = normalize(r_in.direction);
		dvec3 refracted = refract(unit_dirn, hr.normal, ri);
		double cosine   = min(dot(unit_dirn, hr.normal), 1.0);
		double sine     = sqrt(1.0 - cosine*cosine);

		bool cannot_refract = (ri * sine) > 1.0;
		dvec3 dirn;

		if(cannot_refract || reflectance(cosine, ri) > dot(dvec2(cosine, sine), unit_dirn.xy)){
			dirn = reflect(unit_dirn, hr.normal);
		}
		else{
			dirn = refracted;
		}
		scattered = generateRay(hr.hitpoint, dirn);
		return true;
	}
	else
	{
		return false;
	}
}
