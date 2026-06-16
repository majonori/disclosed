#include<bits/stdc++.h>
#define P 998244353ull
#define int int64_t
int n,m,I,C[2][64],S[64],K[64];
int fpow(int a,int n=P-2){
  int ans=1;for(;n;n>>=1,(a*=a)%=P)if(n&1)(ans*=a)%=P;return ans;
}
void Init(){
  int a[64];a[0]=m+1,I=1;
  for(int i=0;a[i]!=1;++i)for(int f=1;f!=-1;--f){
    int v=(a[i]>>1)+(a[i]&f);
    for(int j=i+1;j!=I;++j)if(a[j]==v){C[f][i]=j;break;}
    if(!C[f][i])C[f][i]=I,a[I]=v,I++;
  }S[0]=1,S[--I-1]+=P-(m*(m+1ll)/2+1)%P,S[I]=(1ll*m*m+1)%P;
  for(int i=0;i!=I;++i)
    (S[C[0][i]]+=S[i])%=P,(S[C[1][i]]+=S[i])%=P;
//  S[I]=fpow(S[I]);
  for(int i=0;i!=I;++i)
    (K[C[0][i]]+=S[i])%=P,(K[C[1][i]]+=S[i])%=P;K[I]+=1;
  for(int i=0;i<=I;i++)std::cout<<K[i]<<"\t";std::cout<<"\n\n";
  for(int i=0;i!=I;++i)
    (K[C[0][i]]+=K[i])%=P,(K[C[1][i]]+=K[i])%=P;
  
  for(int i=0;i<=I;i++)std::cout<<i<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<a[i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<C[1][i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<C[0][i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<S[i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<K[i]<<"\t";std::cout<<"\n";
}
signed main(){
  m=8;Init();
  return 0;
}
//unsigned T,N[10],m,g[3500000];
//std::unordered_map<unsigned,unsigned>s;
//void Init(){
//	g[1]=1;m=std::max(100000u,m);
//	for(unsigned i=2;i<=m;++i){
//		g[i]=P-(3+g[i])%P;
//		for(unsigned j=2;i*j<=m&&j<i;++j)g[i*j]=(g[i*j]+1ull*g[i]*g[j]+P-1)%P;
//		if(i<9999&&i*i<=m)g[i*i]=(g[i*i]+(1ull*g[i]*g[i]+P-1)%P*(1+P>>1))%P;
//	}for(unsigned i=2;i<=m;++i)(g[i]+=g[i-1])%=P;
//}
//unsigned S(unsigned n){
//	if(n<=m)return g[n];
//	if(s.count(n))return s[n];
//	unsigned sn=8+S(n/2)+P-13ll*n/2%P;
//	for(unsigned l=2,r;l<=n/2;l=r+1)r=n/(n/l),
//		sn=(sn+(r-l+1)*(n/r)%P+P-(P+S(r)-S(l-1))*S(n/r)%P)%P;
//	return s[n]=sn*(1+P>>1)%P;
//}
//int main(){
//	std::cin>>T;
//	for(unsigned i=0;i!=T;++i)
//		std::cin>>N[i],m=std::max(m,N[i]);
//	m=pow(0.3*T*m,2.0/3),Init();
//	for(unsigned i=0;i!=T;++i)
//		std::cout<<(1+(P+N[i]-S(N[i]))*(1+3*P>>2)%P)%P<<"\n";
//	return 0;
//}
