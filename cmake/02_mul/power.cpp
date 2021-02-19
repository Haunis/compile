double power(double base ,int exponent){
	if(base==0){
		return 1;
	}
	double result = base;
	for(int i = 1;i<exponent;++i){
		result = result *base;
	}
	return result;
}
