#include<bits/stdc++.h>
#define maxd_n 20002
int64_t n;
int64_t dgf[maxd_n];
bool is_prime(int64_t x){
	for(int64_t i=2;i*i<=x;++i)if(!(x%i))return 0;
	return 1;
}
void out(int64_t*f){
//	std::cout<<f[1]<<"("<<1<<")";
//	for(int64_t i=2;i!=20;++i)
//		if(f[i])std::cout<<(f[i]<0?"":"+")<<f[i]<<"("<<i<<")";
	for(int64_t i=1;i<=100;++i)
		std::cout<<f[i]<<",";
	std::cout<<"\n";
}
void conv(int64_t p){
	int64_t f[maxd_n];
	memset(f,0,maxd_n*sizeof(int64_t));
	for(int64_t i=1;i*(p-1)<maxd_n;++i)
		f[i*(p-1)]+=dgf[i];
	for(int64_t i=1;i*p<maxd_n;++i)
		f[i*p]-=dgf[i];
	for(int64_t i=0;i!=maxd_n;++i)dgf[i]+=f[i];
	std::cout<<p<<":\n";out(f);out(dgf);std::cout<<"------------\n";
}
int main(){
	std::cin>>n;
	dgf[1]=1;
	for(int p=2;p<=n;p++){
		if(!is_prime(p))continue;
		conv(p);
	}
	return 0;
}
