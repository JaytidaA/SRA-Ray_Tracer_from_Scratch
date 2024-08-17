out vec4 FragColor;
in vec2 TexCoord;

void main()
{	
	double focal_length = 1.0;
	dvec3 lookFrom = dvec3(0.0, 0.0, 0.0);
	vec2 currentPixel = TexCoord*2.0 - 1.0;
	dvec3 lookAt = dvec3(double(currentPixel.x), double(currentPixel.y), -focal_length);


	//uniform dvec3 sCenter;


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

