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
