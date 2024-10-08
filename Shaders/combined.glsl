# Shader Vertex
# version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}


# Shader Fragment
# version 430 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, TexCoord);
	return;
}


# Shader Compute 
# version 430
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

struct plane_disc{
	dvec3 center, normal;
	double radius;
	material mat;
};

plane_disc createPlaneDisc(dvec3 center, dvec3 normal, double radius, material mat){
	plane_disc pd;
	pd.center = center;
	pd.normal = normalize(normal);
	pd.radius = radius;
	pd.mat	  = mat;
	return pd;
}

bool hitPlaneDisc(inout hit_record hr, plane_disc pd, ray r, interval i){
	double lambda = dot(pd.center - r.origin, pd.normal)/dot(r.direction, pd.normal);
	if(!contains(i, lambda)){ return false; }
	dvec3 hp = rayAtParameter(r, lambda);
	if(dot(hp-pd.center, hp-pd.center) > pd.radius * pd.radius){ return false; }

	hr.hitpoint = hp;
	hr.lambda 	= lambda;
	hr.mat 		= pd.mat;
	determineOuterFace(hr, r, pd.normal);
	return true;
}

struct roll{
	dvec3 center, axis;
	double radius, height;
	material mat;
};

roll createRoll(dvec3 center, dvec3 axis, double radius, double height, material mat){
	roll R;
	R.center = center;
	R.axis = normalize(axis);
	R.radius = radius;
	R.height = height;
	R.mat = mat;
	return R;
}

bool hitRoll(inout hit_record hr, roll R, ray r, interval i){
	dvec3 r_dir_proj = r.direction - (R.axis * dot(r.direction, R.axis));
	dvec3 or_c_proj  = (r.origin - R.center) - (R.axis * dot(r.origin - R.center, R.axis));
	
	double a = dot(r_dir_proj, r_dir_proj);
	double h = dot(r_dir_proj, or_c_proj);
	double c = dot(or_c_proj, or_c_proj) - (R.radius * R.radius);
	double discriminant = h*h - a*c;
	if(discriminant < 0.0){ return false; }

	double sqrtd = sqrt(discriminant);
	double root  = (-h-sqrtd)/a;
	if(!contains(i, root)){
		root = (-h+sqrtd)/a;
		if(!contains(i, root)){ return false; }
	}

	dvec3 hp = rayAtParameter(r, root);
	double height_on_axis = dot(hp-R.center, R.axis);
	if(height_on_axis < -R.height/2.0 || height_on_axis > R.height/2.0){ return false; }
	dvec3 point_on_axis = R.center + (R.axis * height_on_axis);

	hr.hitpoint = hp;
	hr.lambda   = root;
	hr.mat 		= R.mat;
	determineOuterFace(hr, r, (hp - point_on_axis)/R.radius);
	return true;
}

struct cylinder{
	roll my_roll;
	plane_disc my_disc_1, my_disc_2;
};

cylinder createCylinder(dvec3 center, dvec3 axis, double radius, double height, material mat){
	cylinder c;
	c.my_roll	= createRoll(center, axis, radius, height, mat);
	c.my_disc_1 = createPlaneDisc(center + (height/2.0)*normalize(axis),-axis, radius, mat);
	c.my_disc_2 = createPlaneDisc(center - (height/2.0)*normalize(axis), axis, radius, mat);
	return c;
}

bool hitCylinder(inout hit_record hr, cylinder c, ray r, interval i){
	hit_record temp;
	bool hit_anything = false;

	if(hitRoll(temp, c.my_roll, r, i)){
		hit_anything = true;
		i.maxEl = hr.lambda;
		hr = temp;
	}

	if(hitPlaneDisc(temp, c.my_disc_1, r, i)){
		hit_anything = true;
		i.maxEl = hr.lambda;
		hr = temp;
	}

	if(hitPlaneDisc(temp, c.my_disc_2, r, i)){
		hit_anything = true;
		i.maxEl = hr.lambda;
		hr = temp;
	}

	return hit_anything;
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
struct world{
	int sphDefined;
	sphere sphEl[10];
	int cylDefined;
	cylinder cylEl[10];
	int cubDefined;
	cube cubEl[10];
};

bool hitWorld(inout hit_record hr, world w, ray r, interval i){
	hit_record temp;
	bool hit_anything = false;

	// Check collision with sphere
	for(int j = 0; j < w.sphDefined; j++){
		if(hitSphere(temp, w.sphEl[j], r, i))
		{
			hit_anything = true;
			i.maxEl = hr.lambda;
			hr = temp;
		}
	}

	// Check collision with cylinder
	for(int j = 0; j < w.cylDefined; j++){
		if(hitCylinder(temp, w.cylEl[j], r, i))
		{
			hit_anything = true;
			i.maxEl = hr.lambda;
			hr = temp;
		}
	}

	// Check collision with cube
	for(int j = 0; j < w.cubDefined; j++){
		if(hitCube(temp, w.cubEl[j], r, i))
		{
			hit_anything = true;
			i.maxEl = hr.lambda;
			hr = temp;
		}
	}
	
	return hit_anything;
}

dvec3 ray_colour(ray r, int depth, world w){
    hit_record hr;
    ray   scattered   = generateRay(dvec3(0.0), dvec3(0.0));
    dvec3 attenuation = dvec3(0.0);
    interval i        = createInterval(0.0001, M_INFINITY);
    bool hit_sky      = false;
    dvec3 retColour   = dvec3(1.0);

    while(depth > 0){
        if(hitWorld(hr, w, r, i)){
            if(scatter(r, hr, attenuation, scattered)){
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

    if(hit_sky){
        dvec3 topColour    = dvec3(0.5, 0.7, 1.0);
        dvec3 bottomColour = dvec3(1.0, 1.0, 1.0);
        double t           = r.direction.y*0.5 + 0.5;
        retColour         *= mix(topColour, bottomColour, t);
    } else {
        retColour = dvec3(0.0);
    }

    return retColour;
}



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

