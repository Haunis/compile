/*
 * g++ -c -o power.o power.cpp
 * ar -crv libpower.a power.o (-c：创建，r:向add.a插入add.o v:附加信息)
 * 
 */
double power(double base ,int exponent){
	if(base ==0){
		return 1;
	}
	double result = base;
	for(int i = 1;i<exponent;++i){
		result = result*base;	
	}
	return result;
}
