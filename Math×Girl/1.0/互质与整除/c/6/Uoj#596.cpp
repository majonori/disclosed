#include<algorithm>
#include<cstring>
#include<cstdio>
#define ll long long
#define ull unsigned ll
#define clr(f,n) memset(f,0,sizeof((f)[0])*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof((f)[0])*(n))
#define Maxn 270000
using namespace std;
const int mod=998244353,_G=3;
ll powM(ll a,ll t=mod-2){
	ll ans=1;
	while(t){
		if(t&1)ans=ans*a%mod;
		a=a*a%mod;t>>=1;
	}return ans;
}
int k;
struct CP
{
	int x[20];
	CP operator * (const CP B) const {
		CP R;
		for (int i=0;i<k;i++)R.x[i]=0;
		for (int i=0;i<k;i++){
			for (int j=0;i+j<k;j++)
				R.x[i+j]=(R.x[i+j]+1ll*x[i]*B.x[j])%mod;
			for (int j=k-i;j<k;j++)
				R.x[i+j-k]=(R.x[i+j-k]+1ll*x[i]*B.x[j])%mod;
		}return R;
	}
};
const int invG=powM(_G);
int tr[Maxn<<1],tf;
void tpre(int n){
	if (tf==n)return ;tf=n;
	for(int i=0;i<n;i++)
		tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
}
void NTT(int *g,bool op,int n)
{
	tpre(n);
	static ull f[Maxn<<1],w[Maxn<<1]={1};
	for (int i=0;i<n;i++)f[i]=(((ll)mod<<5)+g[tr[i]])%mod;
	for(int l=1;l<n;l<<=1){
		ull tG=powM(op?_G:invG,(mod-1)/(l+l));
		for (int i=1;i<l;i++)w[i]=w[i-1]*tG%mod;
		for(int k=0;k<n;k+=l+l)
			for(int p=0;p<l;p++){
				int tt=w[p]*f[k|l|p]%mod;
				f[k|l|p]=f[k|p]+mod-tt;
				f[k|p]+=tt;
			}
	}if (!op){
		ull invn=powM(n);
		for(int i=0;i<n;++i)
			g[i]=f[i]%mod*invn%mod;
	}else for(int i=0;i<n;++i)g[i]=f[i]%mod;
}
void NTT(CP *g,bool op,int n)
{
	static int f[Maxn<<1];
	for (int t=0;t<k;t++){
		for (int i=0;i<n;i++)f[i]=g[i].x[t];
		NTT(f,op,n);
		for (int i=0;i<n;i++)g[i].x[t]=f[i];
	}
}
void px(CP *f,CP *g,int n)
{for(int i=0;i<n;++i)f[i]=f[i]*g[i];}
int tx[Maxn];

void times(int *f,int *g,int n)
{
	static CP F[Maxn<<1],G[Maxn<<1];
	clr(F,n);clr(G,n);
	for (int i=0;i<n;i++){
		F[i].x[tx[i]]=f[i];
		G[i].x[tx[i]]=g[i];
	}NTT(F,1,n);NTT(G,1,n);
	px(F,G,n);NTT(F,0,n);
	for (int i=0;i<n;i++)
		f[i]=F[i].x[tx[i]];
}
void invp(int *f,int m)
{
	int n;for (n=1;n<m;n<<=1);
	static int w[Maxn<<1],r[Maxn<<1];
	w[0]=powM(f[0]);
	for (int len=2;len<=n;len<<=1){
		for (int i=0;i<(len>>1);i++)r[i]=w[i];
		times(r,f,len);clr(r,len>>1);
		times(r,w,len);
		for (int i=len>>1;i<len;i++)
			w[i]=(w[i]*2ll-r[i]+mod)%mod;
	}cpy(f,w,m);clr(w,n+n);clr(r,n+n);
}
int N,n[20],a[20][20],pw[20][Maxn];
int qx(int u)
{
	int ret=0,buf=1;
	for (int i=1;i<k;i++){
		buf*=n[i];
		ret=ret+u/buf;
	}return ret%k;
}
ll fac[Maxn],ifac[Maxn];
void Init(int n)
{
	fac[0]=1;
	for (int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%mod;
	ifac[n]=powM(fac[n]);
	for (int i=n;i;i--)
		ifac[i-1]=ifac[i]*i%mod;
}
int F[Maxn<<1],S[Maxn<<1],td[Maxn][20];
int main()
{
	scanf("%d",&k);
	N=1;
	for (int i=1;i<=k;i++){
		scanf("%d",&n[i]);
		N*=(++n[i]);
	}Init(*max_element(n+1,n+k+1));
	for (int u=0;u<N;u++){
		tx[u]=qx(u);
		F[u]=1;
		for (int i=1,tu=u;i<=k;i++){
			F[u]=F[u]*ifac[td[u][i]=tu%n[i]]%mod;
			tu/=n[i];
		}
	}
	for (int i=1;i<=k;i++)
		for (int j=1;j<=k;j++){
			scanf("%d",&a[i][j]);
			a[i][j]++;
		}
	for (int t=1;t<=k;t++){
		static int pw[Maxn];
		ll buf=a[t][t];
		pw[0]=pw[1]=1;
		for (int i=2;i<=n[t];i++)pw[i]=pw[i-1]*buf%mod;
		for (int i=1;i<=n[t];i++)pw[i]=1ll*pw[i]*pw[i-1]%mod;
		for (int i=0;i<N;i++)
			F[i]=1ll*F[i]*pw[td[i][t]]%mod;
	}
	for (int t1=1;t1<=k;t1++)
		for (int t2=1;t2<t1;t2++){
			static int pw[Maxn];
			ll buf=a[t1][t2];
			pw[0]=1;
			for (int i=1;i<=n[t1]*n[t2];i++)pw[i]=pw[i-1]*buf%mod;
			for (int i=0;i<N;i++)
				F[i]=1ll*F[i]*pw[td[i][t1]*td[i][t2]]%mod;
		}
	for (int i=0;i<N;i++)S[i]=F[i];
	invp(F,N);
	ll ans=0;
	for (int i=0;i<N;i++)
		ans=(ans+1ll*S[i]*i%mod*F[N-1-i])%mod;
	ans=ans*powM(N-1)%mod;
	for (int i=1;i<=k;i++)
		ans=ans*fac[n[i]-1]%mod;
	printf("%lld",ans);
	return 0;
}
