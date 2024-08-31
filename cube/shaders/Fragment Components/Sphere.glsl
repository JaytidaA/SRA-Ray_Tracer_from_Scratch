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