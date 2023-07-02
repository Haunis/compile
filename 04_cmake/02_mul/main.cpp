#include<stdio.h>
#include<stdlib.h>
#include"power.h"

#include<iostream>
using namespace std;
int main(){
	double base = 2;
	int exponent = 4;
	double result = power(base,exponent);
	printf("%.2f ^ %d =%.2f\n",base,exponent,result);
	
	cout<<"result = "<<result<<endl;
	return 0;
}
