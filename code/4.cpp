#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
const double dlt=1852*0.02;
const double pi=acos(-1);
double hudu(double x){
	return x/180*pi;
}
struct node{
	double sw,len,sz,sc;
	bool operator < (const node &rhs)const{
		double p1=sw/sc,p2=rhs.sw/rhs.sc;
		if((p1<=0.1)^(p2<=0.1))return p1<p2;
		if(len!=rhs.len)return len<rhs.len;
		return sc*rhs.sz<rhs.sc*sz;
	}
}f[N];
struct T{
	double x,y,v;
	bool operator < (const T &rhs)const{
		return x==rhs.x ? y<rhs.y:x<rhs.x;
	}
}v[N],h[505][505];
int pre[N],hnum[N];
double e[N],al[N],ar[N],hl[N],hr[N],sum[N];
double get_len(int l,int r){
	int cnt=0;
	int tl=0,tr=0;
	double res=0;
	for(int i=1;i<=hnum[l];i++)e[++cnt]=al[++tl]=h[l][i].y;
	for(int i=1;i<=hnum[r];i++)e[++cnt]=ar[++tr]=h[r][i].y;
	sort(e+1,e+cnt+1);
	cnt=unique(e+1,e+cnt+1)-e-1;
/*	puts("e:");for(int i=1;i<=cnt;i++)printf("%lf ",e[i]);puts("");
	puts("al:");for(int i=1;i<=tl;i++)printf("%lf ",al[i]);puts("");
	puts("ar:");for(int i=1;i<=tr;i++)printf("%lf ",ar[i]);puts("");
*/
	int p=1,q=1;
	for(int i=1;i<=cnt;i++){
		while(al[p]<e[i]&&p<tl)p++;
		if(al[tl]<e[i]||al[1]>e[i])continue;
		if(h[l][p].y==e[i])hl[i]=h[l][p].v;
		else{
			double k=(h[l][p+1].v-h[l][p].v)/(al[p+1]-al[p]);
			hl[i]=k*(e[i]-al[p])+h[l][p].v;
		}

		while(ar[q]<e[i]&&q<tr)q++;
		if(ar[tr]<e[i]||ar[1]>e[i])continue;
		if(h[r][q].y==e[i])hr[i]=h[r][q].v;
		else{
			double k=(h[r][q+1].v-h[r][q].v)/(ar[q+1]-ar[q]);
			hr[i]=k*(e[i]-ar[q])+h[r][q].v;
		}

		double ctp=sqrt(3)*hr[i]*2;
		double tmp=sqrt(3)*(hl[i]+hr[i])-(h[r][q].x-h[l][p].x)*dlt;
		//printf("%lf \n",tmp);
		if(tmp>0.4*ctp)res+=(e[i]-e[i-1])*dlt;
	}
	return res;
}
node calc(int l,int r){
	int cnt=0;
	int tl=0,tr=0;
	node res={sum[r]-sum[l],0,0,0};
	for(int i=1;i<=hnum[l];i++)e[++cnt]=al[++tl]=h[l][i].y;
	for(int i=1;i<=hnum[r];i++)e[++cnt]=ar[++tr]=h[r][i].y;
	sort(e+1,e+cnt+1);
	cnt=unique(e+1,e+cnt+1)-e-1;
	int p=1,q=1;
	for(int i=1;i<=cnt;i++){
		while(al[p]<e[i]&&p<tl)p++;
		if(al[tl]<e[i]||al[1]>e[i])continue;
		if(h[l][p].y==e[i])hl[i]=h[l][p].v;
		else{
			double k=(h[l][p+1].v-h[l][p].v)/(al[p+1]-al[p]);
			hl[i]=k*(e[i]-al[p])+h[l][p].v;
		}
		while(ar[q]<e[i]&&q<tr)q++;
		if(ar[tr]<e[i]||ar[1]>e[i])continue;
		if(h[r][q].y==e[i])hr[i]=h[r][q].v;
		else{
			double k=(h[r][q+1].v-h[r][q].v)/(ar[q+1]-ar[q]);
			hr[i]=k*(e[i]-ar[q])+h[r][q].v;
		}
		double tmp=sqrt(3)*(hl[i]+hr[i])-(h[r][q].x-h[l][p].x)*dlt;
		if(tmp>0)res.sc+=tmp*(e[i]-e[i-1])*dlt;
	}
	for(int i=2;i<=tl;i++)
		res.sz+=sqrt(3)*h[l][i].v*(al[i]-al[i-1])*dlt;
	for(int i=2;i<=tr;i++)
		res.sz+=sqrt(3)*h[r][i].v*(ar[i]-ar[i-1])*dlt;
	res.sz-=res.sc;
	res.len=(ar[tr]-ar[1])*dlt;
	res.sw-=res.sz;
	if(res.sw<0)res.sw=0;
//	printf("%.1lf  %.1lf  %.1lf  %.1lf\n",res.sw,res.len,res.sz,res.sc);
	return res;
}
bool cmp(T a,T b){return a.y<b.y;};
int n,m;double a[251][251],id[N];int out[N];
node add(node a,node b){
	a.sw+=b.sw;
	a.len+=b.len;
	a.sz+=b.sz;
	a.sc+=b.sc;
	a.sz=min(a.sz,50000*dlt*dlt);
	return a;
}
int sol[N];
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	double gma;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&a[i][j]);
	node ans={1e9,1e9,1,1e9};
	int ed;
	for(double the=34.98;the<=34.98;the+=0.01){
		int cnt=0;
		double theta=hudu(the);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				v[++cnt]={i*cos(theta)-j*sin(theta),i*sin(theta)+j*cos(theta),a[i][j]};
		sort(v+1,v+cnt+1);
		
		int num=0;
		for(int i=1;i<=cnt;i++){
			if(abs(id[num]-v[i].x)>=1)id[++num]=v[i].x;
			h[num][++hnum[num]]=v[i];
		}
		//for(int i=1;i<=num;i++)printf("%lf  ",id[i]);puts("");
		//printf("%d\n",num);
		for(int i=1;i<=num;i++){
			sort(h[i]+1,h[i]+hnum[i]+1,cmp);
			sum[i]=sum[i-1]+(h[i][hnum[i]].y-h[i][1].y)*dlt*dlt;
			f[i]={1e9,1e9,1,1e9};
		}
	//printf("sum=%lf %lf\n",50000*dlt*dlt,sum[num]);
		f[1]={0,0,0,0};	
		//node t=calc(0,1);
		//printf("%lf %lf %lf %lf\n",t.sw,t.len,t.sc,t.sz);
		for(int i=2;i<=num;i++)
			for(int j=1;j<i;j++){
				node tmp=add(f[j],calc(j,i));
				//node tp=f[j];
				//puts("");
				//printf("pre=   %d->%d %lf %lf %lf %lf\n",j,i,tp.sw,tp.len,tp.sc,tp.sz);
				//printf("add=   %d->%d  %.1lf  %.1lf %.1lf %.1lf\n",j,i,tmp.sw,tmp.len,tmp.sc,tmp.sz);
				if(tmp<f[i]){
					f[i]=tmp;
					pre[i]=j;
				}
			}
		
		for(int j=2;j<=num;j++){
			//printf("%lf %lf %lf %lf\n",f[j].sw,f[j].len,f[j].sc,f[j].sz);
			if(f[j].sz+f[j].sw>=67000000&&f[j]<ans){
				ans=f[j];
				gma=the;
				ed=j;
				for(int i=1;i<=num;i++)
					out[i]=pre[i];
			}
		}
		for(int i=1;i<=num;i++)hnum[i]=0;
	}
	printf("%lf\n",gma);
	printf("%lf %lf\n",ans.len,ans.sw/(ans.sw+ans.sz));
	int pos=ed;
	int kt=0;
	while(pos!=0){
		sol[++kt]=pos;
		pos=out[pos];
	}
	int cnt=0;
	double theta=hudu(gma);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			v[++cnt]={i*cos(theta)-j*sin(theta),i*sin(theta)+j*cos(theta),a[i][j]};
	sort(v+1,v+cnt+1);

	int num=0;
	for(int i=1;i<=cnt;i++){
		if(abs(id[num]-v[i].x)>=1)id[++num]=v[i].x;
		h[num][++hnum[num]]=v[i];
	}
	for(int i=1;i<=num;i++)
		sort(h[i]+1,h[i]+hnum[i]+1,cmp);
	double res=0;
	for(int i=2;i<=kt;i++)
		res+=get_len(sol[i],sol[i-1]);
	printf("%lf\n",res);

	for(int i=kt;i>0;i--)
		printf("%d ",sol[i]);
	return 0;
}




