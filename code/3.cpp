#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
const double L=1852*2,H=1852*4;
#define sqr(x) ((x)*(x))
double u1,u2,l1,l2,bt,h,theta,af,gm,sgm,kt;
double hudu(double x){
	return x/180*pi;
}
double calck1(){
	return tan(sgm)-u1*(cos(sgm)+sin(sgm)*tan(sgm))/(1+u1*sin(sgm));
}
double calck2(){
	return tan(sgm)+u2*(cos(sgm)+sin(sgm)*tan(sgm))/(1+u2*sin(sgm));
}
double calcb(double b1){
	b1+=l1*(cos(sgm)+sin(sgm)*tan(sgm)/(1+u1*sin(sgm)));
	return b1;
}
double calcb1(double b){
	return -l1*(cos(sgm)+sin(sgm)*tan(sgm)/(1+u1*sin(sgm)))+b;
}
double calcb2(double b){
	return l2*(cos(sgm)+sin(sgm)*tan(sgm)/(1-u2*sin(sgm)))+b;
}
bool check (double k1,double b1,double k2,double b2){
	double x=(b2-b1)/(k1-k2);
	double y=k1*x+b1;
	return  y<0||x<0;
}
bool pd(double b,double x0,double y0){
	l1=b/tan(sgm)*sin(bt)-(h-tan(pi/6)*b/tan(sgm)*sin(bt))/(theta-tan(pi/6));
	l1*=kt;

	l2=(h-tan(-pi/6)*b/tan(sgm)*sin(bt))/(theta-tan(5*pi/6))-b/tan(sgm)*sin(bt);
	l2*=kt;

	//printf("%.2lf: %lf %lf %lf %lf\n",b,u1,l1,u2,l2);
	double k1=calck1();
	double b1=calcb1(b);

	return k1*x0+b1<y0;
}
double find(double x0,double y0){
	double l=-1e9,r=H;
	while(abs(l-r)>0.001){
		double mid=(l+r)/2;
		if(pd(mid,x0,y0))
			l=mid;
		else r=mid;
	}
	return l;
}
struct node{
	double x,y;
}out[10000],pt[10000];
int main(){
	freopen("data.out","w",stdout);
	af=hudu(1.5);
	printf("%lf\n",tan(af));
	h=110+tan(af)*H/2;
	double ans=1e9;
	int aef=-1;
	int cnt=0;
	double kf=-1;
	for(int jd=0;jd<=90;jd++){
		//printf("\n%d:\n",jd);
		int c=0;
		bt=hudu(jd);
		if(jd==90){
			double up=sqrt(3)*(h-tan(af)*H),down=sqrt(3)*h;
			double p=(down-up)/(2*(up+down));
			printf("%d\n",(int)(L/(2*up)));
			printf("%lf\n",p);
			printf("%.2lf\n",H*L/(2*up));
			continue;
		}
		if(bt==0){
			double x1=0,x0,sum=0;
			int cc=0;
			while(x1<H){
				x0=(tan(pi/6)*x1-tan(af)*x1+h)*sqrt(3);
				cc++;
				printf("(0,%.2lf)  (%.2lf,%.2lf)\n",x0,L,x0);
				x1=(tan(-pi/6)*x0-h)/(tan(-pi/6)-tan(af));
				sum+=L;
			}
			printf("\n%d %.2lf\n",cc ,sum);
			continue;
		}
		gm=acos(1/(cos(bt)*sqrt(1+sqr(tan(bt)/cos(af)))));
		theta=tan(gm)/tan(bt);
		kt=sqrt(sqr(theta)+1);
		sgm=acos(cos(gm)*cos(bt));
		
		u1=tan(pi/6)*tan(bt)/cos(bt)/(theta-tan(pi/6))+tan(bt)/cos(bt);
		u1*=kt;
		u2=-tan(-pi/6)*tan(bt)/cos(bt)/(theta-tan(-pi/6))-tan(bt)/cos(bt);
		u2*=kt;
		
		double k=tan(sgm);
		double b2,b1,b;
		double k1=calck1();
		double k2=calck2();
		double lb=-1,tb=-1;
		//printf("%.2lf %.2lf %.2lf\n",k1,k,k2);
		double x0=L,y0=0,res=0;
		if(k1<0)y0=H;
		bool flag=true;
		while(x0>0){
			b=find(x0,y0);
			
			b1=calcb1(b);	
			b2=calcb2(b);

			//printf("%.2lf %.2lf\n%.2lf %.2lf\n%.2lf %.2lf\n",k1,b1,k,b,k2,b2);
			double p=0;
			if(lb!=-1&&tb!=-1){
				double xt=(lb-b1)/(k1-k2);
				double yt=k1*xt+b1;
				double X1=-b1/k1,Xl=-lb/k2;
				if(lb>0&&b1>0)p=(lb-b1)/(b-tb)*xt/L;
				if(lb<0&&b1>0)p=(yt/H*lb+xt/L*X1)/(b-tb);
				if(lb<0&&b1<0)p=yt/H*(X1-Xl)*k/(b-tb);
				//printf("%.2lf %.2lf\n",lb,b1);
				lb=b2;tb=b;
			}else lb=0,tb=0;
			p=0.1+(p*10-(int)(p*10))/10;
			//printf("%.2lf\n",p);
			double r=min(L,(H-b)/k);
			double l=max(0.0,-b/k);
			//printf("%lf %lf\n",l,r);
			res+=(r-l)*sqrt(k*k+1);
			//printf("(%.2lf,%.2lf)--->(%.2lf,%.2lf)\n",l,k*l+b,r,k*r+b);
			

			//printf("%lf  %lf\n",x0,y0);
			//printf("%lf %lf %lf\n",b1,b,b2);
			x0=min(L,(H-b2)/k2);
			x0=max(0.0,x0);
			y0=k2*x0+b2;			
//			printf("%lf %lf %lf %lf\n",out[c].ur,out[c].ul,out[c].dr,out[c].dl);
//			double t=(out[c-1].ur-out[c].ul+out[c-1].dr-out[c].dl);
//			double p=(out[c].dr-out[c-1].dl)/2;
//			if(t!=0)p/=t;else t=1e9;
//			printf("%lf\n",p);
//			if(c==1)p=0.2;
			out[++c]={x0,y0};
			if(check(k1,b1,k2,b2)||k2>k||c>300){
				flag=false;
				break;
			}	
		}
		res=res*cos(gm);
		if(ans>res&&flag){
			ans=res;
			aef=jd;
			cnt=c;
			kf=k;
			for(int j=1;j<=cnt;j++)
				pt[j]=out[j];
		}
		//printf("%lf\n",res);
	}
	printf("%d\n",cnt);
	//printf("%lf\n",kf);
	printf("%lf %d\n",ans,aef);
	for(int i=1;i<=cnt;i++){
		double m=pt[i].y-kf*pt[i].x;
		double xf,yf;
		if(m>0)yf=m,xf=0;
		else xf=-m/kf,yf=0;
		printf("(%.2lf,%.2lf)-->(%.2lf,%.2lf)\n",xf,yf,pt[i].x,pt[i].y);
		//double p=(out[i].dr-out[i-1].dl)/(2*(out[i-1].ur-out[i].ul+out[i-1].dr-out[i].dl));
		//printf("%.2lf   ",p*100);
	}
	return 0;
}
