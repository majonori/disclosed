#include<bits/stdc++.h>
namespace poly{
/*支持multivariate polynomial*/
	#define clr(f,n) memset(f,0,sizeof((f)[0])*(n))
	#define cpy(f,g,n) memcpy(f,g,sizeof((f)[0])*(n))
	#define Maxn 104000
	const int mod=998244353;
	int s,chi[Maxn],inverse[Maxn];
/*初始化*/
	void Init(int64_t *a,int64_t n,int64_t sigma_0){
		s=n;//维数
		//EI 的占位函数预处理
		int f[16];f[0]=1;//主函数从0开始读入
		for(int i=1;i<s;i++)f[i]=f[i-1]*(a[i-1]+1);
		for(int i=0;i<sigma_0;i++){
			chi[i]=0;
			for(int k=1;k<s;k++)chi[i]+=i/f[k];
			chi[i]%=s;
		}
		inverse[1]=1;//反正线性求逆元很快
		for(int i=2;i<=sigma_0;i++)
			inverse[i]=1ll*(mod-mod/i)*inverse[mod%i]%mod;
	}
/*第二维封装*/
	struct CP{
		int x[16];//这里直接暴力卷积
		CP operator * (const CP B) const {
			CP R;
			for (int i=0;i<s;i++)R.x[i]=0;
			for (int i=0;i<s;i++){
				for (int j=0;i+j<s;j++)
					R.x[i+j]=(R.x[i+j]+1ll*x[i]*B.x[j])%mod;
				for (int j=s-i;j<s;j++)
					R.x[i+j-s]=(R.x[i+j-s]+1ll*x[i]*B.x[j])%mod;
			}return R;
		}
	};
/*NTT板子*/
	int tr[Maxn<<1],tf;
	void tpre(int n){
		if(tf==n)return;tf=n;
		for(int i=0;i<n;i++)
			tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
	}
	int64_t fpow(int64_t a,int64_t n=mod-2){
		int64_t ans=1;
		for(;n;n>>=1,(a*=a)%=mod)if(n&1)(ans*=a)%=mod;
		return ans;
	}
	const int _G=3,invG=fpow(_G);
	void NTT(int *g,bool op,int n){
		tpre(n);
		static uint64_t f[Maxn<<1],w[Maxn<<1]={1};
		for (int i=0;i<n;i++)f[i]=(((int64_t)mod<<5)+g[tr[i]])%mod;
		for(int l=1;l<n;l<<=1){
			uint64_t tG=fpow(op?_G:invG,(mod-1)/(l+l));
			for (int i=1;i<l;i++)w[i]=w[i-1]*tG%mod;
			for(int k=0;k<n;k+=l+l)
				for(int p=0;p<l;p++){
					int tt=w[p]*f[k|l|p]%mod;
					f[k|l|p]=f[k|p]+mod-tt;
					f[k|p]+=tt;
				}
		}if (!op){
			uint64_t invn=fpow(n);
			for(int i=0;i<n;++i)
				g[i]=f[i]%mod*invn%mod;
		}else for(int i=0;i<n;++i)g[i]=f[i]%mod;
	}
	//高维NTT
	void NTT(CP *g,bool op,int n){
		static int f[Maxn<<1];
		for (int t=0;t<s;t++){
			for (int i=0;i<n;i++)f[i]=g[i].x[t];
			NTT(f,op,n);
			for (int i=0;i<n;i++)g[i].x[t]=f[i];
		}
	}
/*多项式运算,上方已经封装好了高维*/
  //多项式乘法,需要 EI 的占位函数映射
	void times(int *f,int *g,int n){
		static CP F[Maxn<<1],G[Maxn<<1];
		clr(F,n);clr(G,n);
		for (int i=0;i<n;i++){
			F[i].x[chi[i]]=f[i];
			G[i].x[chi[i]]=g[i];
		}NTT(F,1,n);NTT(G,1,n);
		for(int i=0;i<n;++i)F[i]=F[i]*G[i];
		NTT(F,0,n);
		for (int i=0;i<n;i++)
			f[i]=F[i].x[chi[i]];
	}
  //多项式乘法逆
	void inv(int *f,int m){
		int n;for (n=1;n<m;n<<=1);
		static int w[Maxn<<1],r[Maxn<<1];
		w[0]=fpow(f[0]);
		for (int len=2;len<=n;len<<=1){
			for (int i=0;i<(len>>1);i++)r[i]=w[i];
			times(r,f,len);clr(r,len>>1);
			times(r,w,len);
			for (int i=len>>1;i<len;i++)
				w[i]=(w[i]*2ll-r[i]+mod)%mod;
		}cpy(f,w,m);clr(w,n+n);clr(r,n+n);
	}
//	//多项式求导,其实是一个特殊的微分算子
//	void deriv(int *f,int m){
//		for(int i=0;i<m;i++)
//			f[i]=1ll*f[i]*i%mod;
//	}
//	//多项式积分
//	void integ(int *f,int m){
//		for(int i=0;i<m;i++)
//			f[i]=1ll*f[i]*inverse[i]%mod;
//	}
	//多项式求导,其实是一个特殊的微分算子
	void deriv(int *f,int m){
		for(int i=1;i<m;i++)
			f[i-1]=1ll*f[i]*i%mod;
		f[m-1]=0;
	}
	//多项式积分
	void integ(int *f,int m){
		for(int i=m;i;i--)
			f[i]=1ll*f[i-1]*inverse[i]%mod;
		f[0]=0;
	}
	//多项式对数函数
	void ln(int *f,int m){
		int n;for (n=1;n<m;n<<=1);
		static int g[Maxn<<1];
		cpy(g,f,m);
		inv(g,m);deriv(f,m);
		times(f,g,n);
		integ(f,m-1);
		clr(g,m);
	}
	//多项式指数函数
	void exp(int *f,int m){
		int n;for (n=1;n<m;n<<=1);
		static int s[Maxn<<1],s2[Maxn<<1];
		s2[0]=1;
		for (int len=2;len<=n;len<<=1){
			cpy(s,s2,len>>1);ln(s,len);
			for (int i=0;i<len;i++)
				s[i]=(f[i]-s[i]+mod)%mod;
			s[0]=(s[0]+1)%mod;
			times(s2,s,len);
		}cpy(f,s2,m);clr(s,n);clr(s2,n);
	}
}
int main(){
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0),std::cout.tie(0);
//	int64_t s=3,a[5]={3,4,5},sigma_0=120;
	int64_t s=1,a[5]={7},sigma_0=7;
	poly::Init(a,s,sigma_0);
	int p[1145]={1,2,3},q[1145];
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	poly::integ(p,sigma_0);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	poly::deriv(p,sigma_0);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	cpy(q,p,sigma_0+1);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<q[i]<<",";
	std::cout<<"\n";
	poly::times(q,p,128);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<q[i]<<",";
	std::cout<<"\n";
	
	poly::inv(p,sigma_0);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	poly::inv(p,sigma_0);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	poly::ln(p,sigma_0);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	poly::exp(p,7);
	for(int i=0;i<=sigma_0;i++)
		std::cout<<p[i]<<",";
	std::cout<<"\n";
	
	return 0;
}
/*
multivariate multiplication

维度爆炸问题优化：
https://www.luogu.com/article/wje8kchr




*/
