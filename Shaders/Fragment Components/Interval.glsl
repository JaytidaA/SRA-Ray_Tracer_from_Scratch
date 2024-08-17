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
