#include<bits/stdc++.h>
typedef unsigned long long i8;
const i8 MOD=998244353,MX=10000005;
i8 Inv[MX],Invp[MX],da,db,v;
long double I=1,V;
std::vector<i8>Prime;
bool vis[MX];
const __int128 II=1;
void exgcd(i8 a,i8 b,i8&x,i8&y) {
  if(!b)x=1,y=0;
  else exgcd(b,a%b,y,x),y-=a/b*x;
}
void sieve(const i8 n){
  Inv[1]=1;Prime={};
  for(i8 i=2;i<=n;i++){
    if(!vis[i]){
      Prime.push_back(i);
      if(n%i==0)Inv[i]=0;
      else{i8 x,y;exgcd(i,n,x,y);Inv[i]=(x+n)%n;}
    }
    for(i8 p:Prime){
      if(i*p>n)break;
      vis[i*p]=1;Inv[i*p]=Inv[i]*Inv[p]%n;
      if(i%p==0)break;
    }
  }
}
struct frac{
#define il inline __attribute__((__always_inline__))
  i8 a,b;char f;//frac{a}{b}+f\delta
  il frac(i8 A,i8 B,char F):a(A),b(B),f(F){}
  il friend i8 model(frac x){return (x.a*Invp[x.b]+(x.f==1?v:MOD-v));}
  il friend bool operator<(frac x,frac y){
//    return I*x.a/x.b+x.f*I*da/db<I*y.a/y.b+y.f*I*da/db;//精度会炸
    return (y.f-x.f)*II*da*y.b*x.b>(II*x.a*y.b-II*y.a*x.b)*db;
  }
};
void slove(){
  i8 n,g,ans=0;
  std::cin>>n>>da>>db;
  g=std::gcd(da,db),da/=g,db/=g;
  i8 x,y;exgcd(db%MOD,MOD,x,y);v=da%MOD*(x+MOD)%MOD;
  if(n==1){std::cout<<(2*da<db?2*v%MOD:1)<<"\n";return;}
  if((__int128)2*n*da>=db){std::cout<<"0\n";return;}
  sieve(n);Invp[1]=1;
  for(i8 i=2;i<=n;i++)Invp[i]=Invp[MOD%i]*(MOD-MOD/i)%MOD;
  for(i8 d=1;d<n;d++){
    if(!Inv[d])continue;
    frac _x=std::max(frac((d*Inv[d]-1)/n,Inv[d],+1),frac(d,n,-1));
    frac x_=std::min(frac((d*(n-Inv[d])+1)/n,n-Inv[d],-1),frac(d,n,+1));
    if(_x<x_)ans=(ans+model(x_)+MOD-model(_x)%MOD)%MOD;
  }
  std::cout<<ans<<"\n";
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  i8 T;std::cin>>T;
  while(T--)slove();
  return 0;
}
