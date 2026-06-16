#include<bits/stdc++.h>
namespace Miller_Rabin{
	std::unordered_map<int64_t,bool>P;
	const int Pcnt=7;
	const int64_t p[Pcnt]={2,325,9375,28178,450775,9780504,1795265022};
	int64_t pow(int64_t a,int64_t b,int64_t p){
		int64_t ans=1;
		for(;b;a=(__int128)a*a%p,b>>=1)if(b&1)ans=(__int128)ans*a%p;
		return ans;
	}
	bool check(int64_t x,int64_t p){
		if(x%p==0||pow(p%x,x-1,x)^1)return 1;
		int64_t t,k=x-1;
		while((k^1)&1){
			t=pow(p%x,k>>=1,x);
			if(t^1&&t^(x-1))return 1;
			if(!(t^(x-1)))return 0;
		}return 0;
	}
	bool prime(int64_t x){
		if(x<2)return 0;
		if(P.count(x))return P[x];
		for(int64_t i=0;i!=Pcnt;++i){
			if(x<=p[i]){P[x]=1;return 1;}
			if(check(x,p[i])){P[x]=0;return 0;}
		}P[x]=1;return 1;
	}
}
int64_t T,s,p[99],a[99],n,d_n,ans;
std::unordered_set<int64_t>D;
std::unordered_map<int64_t,int64_t>Chi;
std::unordered_map<int64_t,int64_t>Sig;
void dfs(int64_t t,int64_t d,int64_t sig){
	if(t==s){D.insert(d),Sig[d]=sig;return;}
	for(int64_t i=0,x=1;i<=a[t];i++,x*=p[t])
		dfs(t+1,d*x,sig*(i+1));
}
void conv(uint64_t p,bool flag=0){
	std::unordered_map<int64_t,int64_t>dgf;
	if(flag)for(auto [d,Chi_d]:Chi)
		if(!(n%(d*(p-1))))dgf[d*(p-1)]+=Chi_d;
	if(!(n%p))for(auto [d,Chi_d]:Chi)
		if(!(n%(d*p)))dgf[d*p]-=Chi_d;
	for(auto [d,dgf_d]:dgf)Chi[d]+=dgf_d;
}
int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0),std::cout.tie(0);
	std::cin>>T;
	while(T--){
		n=1,ans=0,D.clear(),Sig.clear();
		Chi.clear(),Chi[1]=1;
		std::cin>>s;
		for(int64_t i=0;i!=s;i++)
			std::cin>>p[i]>>a[i],n*=powl(p[i],a[i]);
		dfs(0,1,1);
		for(auto d:D)if(Miller_Rabin::prime(d+1))conv(d+1,1);
		for(int i=0;i!=s;i++)if(n%(p[i]-1)!=0)conv(p[i]);
		for(auto d:D)ans+=Chi[d]*Sig[n/d];
		std::cout<<ans<<"\n";
	}
	return 0;
}
/*
1
3
2 10
3 10
5 10

12052034
\varpai(x)\mid590490000000000
*/
