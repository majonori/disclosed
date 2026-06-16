#include<bits/stdc++.h>
#define P 998244353ull
unsigned T,N[10],m,g[3500000];
std::unordered_map<unsigned,unsigned>s;
void Init(){
	g[1]=1;m=std::max(100000u,m);unsigned i=2;
	for(;i<=m;++i){
		if(i>9999||i*i>m)break;
		g[i]=P-(3+g[i])%P;g[i*i]=(g[i*i]+(1ull*g[i]*g[i]+P-1)%P*(1+P>>1))%P;
		for(unsigned j=2;i*j<=m&&j<i;++j)g[i*j]=(g[i*j]+1ull*g[i]*g[j]+P-1)%P;
	}for(;i<=m;++i){
		g[i]=P-(3+g[i])%P;
		for(unsigned j=2;i*j<=m&&j<i;++j)g[i*j]=(g[i*j]+1ull*g[i]*g[j]+P-1)%P;
	}for(unsigned i=2;i<=m;++i)(g[i]+=g[i-1])%=P;
}
unsigned fS(unsigned n){return (n<=m?g[n]:s[n]);}
void S2(unsigned n){
	if(s.count(n))return;
	unsigned sn=8+fS(n/2)+P-13ll*n/2%P;
	for(unsigned l=2,r;l<=n/2;l=r+1)r=n/(n/l),
		sn=(sn+(r-l+1)*(n/r)%P+P-(P+fS(r)-fS(l-1))*fS(n/r)%P)%P;
	s[n]=sn*(1+P>>1)%P;
}
unsigned S(unsigned n){
	if(n<=m)return g[n];
	if(s.count(n))return s[n];
	for(unsigned l=m,r;l<=n/2;l=r+1)r=n/(n/l),S2(r);
	
	unsigned sn=8+fS(n/2)+P-13ll*n/2%P;
	for(unsigned l=2,r;l<=n/2;l=r+1)r=n/(n/l),
		sn=(sn+(r-l+1)*(n/r)%P+P-(P+fS(r)-fS(l-1))*fS(n/r)%P)%P;
	return s[n]=sn*(1+P>>1)%P;
}
int main(){
	std::cin>>T;
	for(unsigned i=0;i!=T;++i)
		std::cin>>N[i],m=std::max(m,N[i]);
	m=pow(0.3*T*m,2.0/3),Init();
	for(unsigned i=0;i!=T;++i)
		std::cout<<(1+(P+N[i]-S(N[i]))*(1+3*P>>2)%P)%P<<"\n";
	return 0;
}
