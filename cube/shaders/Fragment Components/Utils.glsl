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