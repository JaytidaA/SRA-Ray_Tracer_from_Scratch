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