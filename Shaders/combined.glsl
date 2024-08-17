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

double degrees_to_radians(double x){
	return (x * M_PI)/180.0;
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

struct hit_record{
	dvec3 hitpoint;
	double lambda;
	dvec3 normal;
	bool outface;
};

void determineOuterFace(inout hit_record hr, ray r, dvec3 oN){
	if(dot(r.direction, oN) < 0.0){ hr.outface = true; hr.normal = oN; }
	else{ hr.outface = false; hr.normal = -oN; }
	return;
}

struct sphere{
	dvec3 center;
	double radius;
};

sphere createSphere(dvec3 center, double radius){
	sphere s;
	s.center = center;
	s.radius = radius;
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
	dvec3 outerNormal = (point-s.center)/s.radius;
	determineOuterFace(hr, r, outerNormal);
	return true;
}


out vec4 FragColor;
in vec2 TexCoord;

void main()
{	
	double focal_length = 1.0;
	dvec3 lookFrom = dvec3(0.0, 0.0, 0.0);
	vec2 currentPixel = TexCoord*2.0 - 1.0;
	dvec3 lookAt = dvec3(double(currentPixel.x), double(currentPixel.y), -focal_length);

	interval i = createInterval(0.0, M_INFINITY);
	ray r = generateRay(lookFrom, lookAt-lookFrom);
	sphere s = createSphere(dvec3(0.0, 0.0, -2.0), 1.0);
	hit_record temp;
	if(hitSphere(temp, s, r, i)){
		dvec3 normal = temp.normal*0.5 + 0.5;
		FragColor = vec4(float(normal.x), float(normal.y), float(normal.z), 1.0);
		return;
	}

    vec3 topColor = vec3(0.5, 0.7, 1.0);
    vec3 bottomColor = vec3(1.0, 1.0, 1.0);

    float t = TexCoord.y; //blend factor
    vec3 blendedColor = mix(bottomColor, topColor, t);
    FragColor = vec4(blendedColor, 1.0);
}


