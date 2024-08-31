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
