# Shader Vertex
# version 400 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}


# Shader Fragment
# version 400 core
const double M_INFINITY = 1.0/0.0;
const double M_PI       = 3.1415926535897932384626;

uniform float prand[10];
int prand_count = 0;

double degrees_to_radians(double x){
	return (x * M_PI)/180.0;
}

vec2 dvec2_to_vec2(dvec2 dv2){
	return vec2(float(dv2.x), float(dv2.y));
}

dvec2 vec2_to_dvec2(vec2 v2){
	return dvec2(double(v2.x), double(v2.y));
}

vec3 dvec3_to_vec3(dvec3 dv3){
	return vec3(float(dv3.x), float(dv3.y), float(dv3.z));
}

dvec3 vec3_to_dvec3(vec3 v3){
	return dvec3(double(v3.x), double(v3.y), double(v3.z));
}

bool nearzero3(dvec3 dv3){
	return ((dv3.x < 0.0001) && (dv3.y < 0.0001) && (dv3.z < 0.0001));
}

float prand_gen_float(){
	float ret = sin(prand[prand_count]);
	if(ret < 0.0){ ret *= -1.0; }
	prand_count += int(ret);
	if(prand_count > 9){ prand_count = int(ret)%10; }
	return ret;
}

dvec3 prand_dvec3(){
	return dvec3(double(prand_gen_float()), double(prand_gen_float()), double(prand_gen_float()));
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

struct sphere{
	dvec3 center;
	double radius;
	material mat;
};

sphere createSphere(dvec3 center, double radius, material mat){
	sphere s;
	s.center = center;
	s.radius = radius;
	s.mat = mat;
	return s;
}

bool hitSphere(inout hit_record hr, sphere s, ray r, interval i){
	dvec3 o_c = r.origin - s.center;
	double a = dot(r.direction, r.direction);
	double h = dot(o_c, r.direction);
	double c = dot(o_c, o_c) - (s.radius * s.radius);
	double discriminant = h*h - a*c;
	if(discriminant < 0.0){ return false; }

	double sqrtd = sqrt(discriminant);
	double root = (-h-sqrtd)/a;
	if(!contains(i, root)){
		root = (-h+sqrtd)/a;
		if(!contains(i, root)){ return false; }
	}

	dvec3 point = rayAtParameter(r, root);
	hr.hitpoint = point;
	hr.lambda = root;
	hr.mat = s.mat;
	dvec3 outerNormal = (point-s.center)/s.radius;
	determineOuterFace(hr, r, outerNormal);
	return true;
}


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


