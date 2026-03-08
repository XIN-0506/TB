#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
double k;
double hudu(double x){
	return x/180*pi;
}
double calc(double X1,double X2){
	return sqrt(k*k+1)*abs(X1-X2);
}
double get_cross(double k1,double b1,double k2,double b2){
	return (b2-b1)/(k1-k2);
}
double X1[10],X2[10],l[10],dep[10],p[10];
int main(){
	int n=9;
	k=tan(hudu(1.5));
	for(int i=1;i<=9;i++){
		double x0=200*(i-5);
		dep[i]=70-k*x0;
		X1[i]=get_cross(tan(pi/6),-tan(pi/6)*x0+70,k,0);
		X2[i]=get_cross(tan(pi/6*5),-tan(pi/6*5)*x0+70,k,0);
		l[i]=calc(X1[i],X2[i]); 
		//printf("%.3lf   %.3lf\n",X1[i],X2[i]);
		if(i!=1)
			p[i]=(X2[i-1]-X1[i])/(X2[i]-X1[i]);
	}
	for(int i=1;i<=n;i++)printf("%.2lf ",dep[i]);
		puts("");
	for(int i=1;i<=n;i++)printf("%.2lf ",l[i]);
		puts("");
	for(int i=2;i<=n;i++)printf("%.2lf ",p[i]*100);
		puts("");
	return 0;
}