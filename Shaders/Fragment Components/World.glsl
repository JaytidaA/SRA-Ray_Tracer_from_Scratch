struct world{
	int sphDefined;
	sphere sphEl[10];
	int cylDefined;
	roll cylEl[10];
};

bool hitWorld(inout hit_record hr, world w, ray r, interval i){
	hit_record temp;
	bool hit_anything = false;

	for(int j = 0; j < w.sphDefined; j++){
		if(hitSphere(temp, w.sphEl[j], r, i))
		{
			hit_anything = true;
			i.maxEl = hr.lambda;
			hr = temp;
		}
	}

	for(int j = 0; j < w.cylDefined; j++){
		if(hitRoll(temp, w.cylEl[j], r, i))
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

