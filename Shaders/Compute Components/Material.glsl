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
