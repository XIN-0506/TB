#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
#define sqr(x) ((x)*(x))
double hudu(double x){
	return x/180*pi;
}
double kt;
double calc(double X1,double X2){
	return sqrt(kt*kt+1)*abs(X1-X2);
}
double get_cross(double k1,double b1,double k2,double b2){
	return (b2-b1)/(k1-k2);
}
double af,bt,gm,thta,a[10];
int main(){
	int n=8;
	af=hudu(1.5);
	for(int i=1;i<=n;i++)
		a[i]=0.3*1852*(i-1);
	for(int jd=0;jd<=315;jd+=45){
		printf("%d:\n",jd);
		double tag;
		if(jd<90||jd>270)tag=1;else tag=-1;
		bt=hudu(jd%180);
		if(bt==0){
			for(int i=1;i<=n;i++)
				printf("%.2lf ",sqrt(3)*(120+tag*tan(af)*a[i]));
			puts("");
			continue;
		}
		if(bt==pi/2){
			kt=tan(af);
			tag=0;
		}else{
			gm=acos(1/(cos(bt)*sqrt(1+sqr(tan(bt)/cos(af)))));
			double k=tan(gm);
			kt=k/tan(bt);
		}
		//printf("%lf\n",tag);
		for(int i=1;i<=n;i++){
			double X1=get_cross(tan(pi/6),tag*tan(pi/6)*a[i]+120,kt,0);
			double X2=get_cross(tan(pi/6*5),tag*tan(pi/6*5)*a[i]+120,kt,0);
			printf("%.2lf ",calc(X1,X2));
			//printf("%.3lf   %.3lf\n",X1[i],X2[i]);
		}
		puts("");
	}
	return 0;
}