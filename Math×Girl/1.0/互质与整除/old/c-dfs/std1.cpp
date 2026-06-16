#include<stdio.h>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1000005,maxm=2505,maxk=700;
int T,n,cnt,m,Ps,Ds,anss;
int p[maxn],a[maxn],P[maxk],D[maxm],ans[maxn],ord[maxn],nord[maxn],f[maxm][maxk];
void sieve(int n){
	for(int i=2;i<=n;i++){
		if(p[i]==0)
			a[++cnt]=i;
		for(int j=1;j<=cnt;j++){
			if(i*a[j]>n)
				break;
			p[i*a[j]]=1;
			if(i%a[j]==0)
				break;
		}
	}
}
int check(int x){
	if(x<=1000000)
		return p[x]==0;
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return 0;
	return 1;
}
void dfs(int pos,int val,int now){
	if(now==1){
		ans[++anss]=val;
		return ;
	}
	if(now<=m)
		pos=f[ord[now]][pos];
	else pos=f[nord[n/now]][pos];
	if(pos==Ps+1)
		return ;
	dfs(pos+1,val,now);
	val*=P[pos],now/=P[pos]-1,dfs(pos+1,val,now);
	while(now%P[pos]==0)
		val*=P[pos],now/=P[pos],dfs(pos+1,val,now);
}
signed main(){
	scanf("%lld",&T),sieve(1000000);
	while(T--){
		scanf("%lld",&n);
		if(n==1){
			puts("2");
			continue;
		}
		for(m=1;1ll*(m+1)*(m+1)<=n;m++);
		for(int i=1;i<=m;i++)
			if(n%i==0){
				D[++Ds]=i;
				if(check(i+1))
					P[++Ps]=i+1;
				if(1ll*i*i!=n){
					D[++Ds]=n/i;
					if(check(n/i+1))
						P[++Ps]=n/i+1;
				}
			}
		sort(P+1,P+1+Ps),sort(D+1,D+1+Ds);
		for(int i=1;i<=Ds;i++){
			if(D[i]<=m)
				ord[D[i]]=i;
			else nord[n/D[i]]=i;
			f[i][Ps+1]=Ps+1;
			for(int j=Ps;j>=0;j--)
				f[i][j]=D[i]%(P[j]-1)==0? j:f[i][j+1];
		}
		dfs(1,1,n);
		sort(ans+1,ans+1+anss);
		printf("%lld\n",anss);
		for(int i=1;i<=anss;i++)
			printf("%lld%c",ans[i],i==anss? '\n':' ');
		if(anss==0)
			puts("");
		for(int i=1;i<=Ds;i++){
			if(D[i]<=m)
				ord[D[i]]=0;
			else nord[n/D[i]]=0;
		}
		anss=Ds=Ps=0;
	}
	return 0;
}
