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
