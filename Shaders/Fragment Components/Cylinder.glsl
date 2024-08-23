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
	double h = dot(r_dir_proj, -or_c_proj);
	double c = dot(or_c_proj, or_c_proj) - R.radius*R.radius;
	double discriminant = h*h - a*c;
	if(discriminant < 0){ return false; }
	double sqrtd = sqrt(discriminant);
	double root  = (-h-sqrtd)/a;
	if(!contains(i, root)){
		root = (-h+sqrtd)/a;
		if(!contains(i, root)){ return false; }
	}

	dvec3 hp = rayAtParameter(r, root);
	double height_on_axis = dot(hp-R.center, R.axis);
	if(height_on_axis <  R.height/2.0 || height_on_axis > R.height/2.0){ return false; }
	dvec3 point_on_axis = R.center + (R.axis * height_on_axis);

	hr.hitpoint = hp;
	hr.lambda   = root;
	hr.mat 		= R.mat;
	determineOuterFace(hr, r, (hp - point_on_axis)/R.radius);
	return true;
}
