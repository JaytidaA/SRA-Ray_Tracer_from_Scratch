const double M_INFINITY = 1.0/0.0;
const double M_PI       = 3.1415926535897932384626;

double degrees_to_radians(double x){
	return (x * M_PI)/180.0;
}

vec2 dvec2_to_vec2(dvec2 dv2){
	return vec2(float(dv2.x), float(dv2.y));
}

dvec2 vec2_to_dvec2(vec2 v2){
	return dvec2(double(v2.x), double(v2.y));
}

ivec2 dvec2_to_ivec2(dvec2 dv2){
	return ivec2(int(dv2.x), int(dv2.y));
}

dvec2 ivec2_to_dvec2(ivec2 iv2){
	return dvec2(double(iv2.x), double(iv2.y));
}

vec3 dvec3_to_vec3(dvec3 dv3){
	return vec3(float(dv3.x), float(dv3.y), float(dv3.z));
}

dvec3 vec3_to_dvec3(vec3 v3){
	return dvec3(double(v3.x), double(v3.y), double(v3.z));
}

vec4 dvec4_to_vec4(dvec4 dv4){
	return vec4(float(dv4.x), float(dv4.y), float(dv4.z), float(dv4.w));
}

dvec4 vec4_to_dvec4(vec4 v4){
	return dvec4(double(v4.x), double(v4.y), double(v4.z), double(v4.w));
}

bool nearzero3(dvec3 dv3){
	return ((dv3.x < 0.0001) && (dv3.y < 0.0001) && (dv3.z < 0.0001));
}

dvec2 prand_dvec2(dvec2 dv2){
	dvec2 seed = dvec2(1.2387, 5.8645);
	return dvec2(
		dot(dv2, seed.xy),
		dot(dv2, seed.yx)
	);
}

dvec3 prand_dvec3(dvec3 dv3){
	dvec3 seed = dvec3(1.23, 6.54, 8.97);
	return dvec3(
		dot(dv3, seed.zxy),
		dot(dv3, seed.yzx),
		dot(dv3, seed.xyz)
	);
}
struct ray{
	dvec3 origin;
	dvec3 direction;
};

ray generateRay(dvec3 origin, dvec3 direction){
	ray r;
	r.origin = origin;
	r.direction = direction;
	return r;
}

dvec3 rayAtParameter(ray r, double lambda){
	return r.origin + (lambda * r.direction);
}
struct interval{
	double maxEl, minEl;
};

interval createInterval(double minEl, double maxEl){
	interval i;
	i.minEl = minEl;
	i.maxEl = maxEl;
	return i;
}

bool contains(interval i, double x){
	if(x >= i.minEl && x <= i.maxEl){ return true; }
	else{ return false; }
}
const int MAT_LAMBERTIAN = 0;
const int MAT_METAL = 1;
const int MAT_DIELECTRIC = 2;

struct material{
	int type;
	dvec3 albedo;
	double f_or_d;
};

material createMaterial(int type, dvec3 albedo, double fd){
	material m;
	m.type = type;
	m.albedo = albedo;
	m.f_or_d = fd;
	return m;
}

material createMaterial(dvec3 albedo, double fd){
	material m;
	m.type = MAT_METAL;
	m.albedo = albedo;
	m.f_or_d = fd;
	return m;
}

material createMaterial(int type, dvec3 albedo){
    material m;
    m.type = type;
    m.albedo = albedo;
    m.f_or_d = 0;
    return m;
}

material createMaterial(dvec3 albedo){
    material m;
    m.type = MAT_LAMBERTIAN;
    m.albedo = albedo;
    m.f_or_d = 0;
    return m;
}

material createMaterial(int type, double fd){
    material m;
    m.type = type;
    m.albedo = dvec3(0);
    m.f_or_d = fd;
    return m;
}


material createMaterial(double fd){
    material m;
    m.type = MAT_DIELECTRIC;
    m.albedo = dvec3(0);
    m.f_or_d = fd;
    return m;
}
struct hit_record{
	dvec3 hitpoint;
	double lambda;
	material mat;
	dvec3 normal;
	bool outface;
};

void determineOuterFace(inout hit_record hr, ray r, dvec3 oN){
	if(dot(r.direction, oN) < 0.0){ hr.outface = true; hr.normal = oN; }
	else{ hr.outface = false; hr.normal = -oN; }
	return;
}
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
struct cube{
    dvec3 center;
    dvec3 half_size; // half the size in each dimension
    material mat;
};

cube createCube(dvec3 center, dvec3 half_size, material mat){
    cube c;
    c.center = center;
    c.half_size = half_size;
    c.mat = mat;
    return c;
}

bool hitCube(inout hit_record hr, cube c, ray r, interval i){
    dvec3 t_min = (c.center - c.half_size - r.origin) / r.direction;
    dvec3 t_max = (c.center + c.half_size - r.origin) / r.direction;
    
    dvec3 t1 = min(t_min, t_max);
    dvec3 t2 = max(t_min, t_max);
    
    double t_near = max(max(t1.x, t1.y), t1.z);
    double t_far = min(min(t2.x, t2.y), t2.z);
    
    if (t_near > t_far || !contains(i, t_near)) {
        return false;
    }
    
    hr.lambda = t_near;
    hr.hitpoint = rayAtParameter(r, hr.lambda);
    hr.mat = c.mat;
    
    // Determine which face was hit to calculate the normal
    if (t_near == t1.x) {
        hr.normal = dvec3(-sign(r.direction.x), 0.0, 0.0);
    } else if (t_near == t1.y) {
        hr.normal = dvec3(0.0, -sign(r.direction.y), 0.0);
    } else {
        hr.normal = dvec3(0.0, 0.0, -sign(r.direction.z));
    }
    
    determineOuterFace(hr, r, hr.normal);
    return true;
}

