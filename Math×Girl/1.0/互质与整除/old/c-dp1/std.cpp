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
#define maxd_n 20002
uint64_t n,ans,d_n;
std::unordered_map<uint64_t,int> dm;
std::vector<uint64_t> D;
uint64_t dgf[maxd_n];
//void out(uint64_t*f){
//	for(uint64_t i=0;i!=d_n;++i)
//		if(f[i])std::cout<<f[i]<<"("<<D[i]<<")"<<"+";
//	std::cout<<"\n";
//}
void conv(uint64_t p){
	uint64_t f[d_n];
	memset(f,0,d_n*sizeof(uint64_t));
	for(uint64_t i=0;i!=d_n;++i)
		if(dm.count(D[i]*(p-1)))f[dm[D[i]*(p-1)]]=dgf[i];
	if(!(n%p))for(uint64_t i=0;i!=d_n;++i)
		if(!(D[i]%p))f[i]+=f[dm[D[i]/p]];
	for(uint64_t i=0;i!=d_n;++i)dgf[i]+=f[i];
//	std::cout<<p<<":\n";out(f);out(dgf);std::cout<<"------------\n";
}
int main(){
	std::cin>>n;
	for(uint64_t i=1;i*i<=n;++i)if(!(n%i))dm[i]=D.size(),D.push_back(i);
	d_n=(D.size()<<1)-(D.back()*D.back()==n),dgf[0]=1;
	for(uint64_t i=d_n>>1;i;--i)dm[n/D[i-1]]=D.size(),D.push_back(n/D[i-1]);
	
	for(uint64_t d:D)if(Miller_Rabin::prime(d+1))conv(d+1);
	
	for(uint64_t i=0;i!=d_n;++i)ans+=dgf[i];
	std::cout<<ans;
//	for(auto [i,j]:dm)std::cout<<i<<","<<j<<":"<<D[j]<<"\n";
	return 0;
}
