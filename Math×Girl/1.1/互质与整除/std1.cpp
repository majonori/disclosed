#include<bits/stdc++.h>
#define il inline __attribute__((__always_inline__))
namespace Miller_Rabin{
  const int Pcnt=7;
  const int64_t p[Pcnt]={2,325,9375,28178,450775,9780504,1795265022};
  il int64_t mul(int64_t a,int64_t b,int64_t p){
    return __int128(a)*b%p;
  }
  il int64_t pow(int64_t a,int64_t b,int64_t p){
    int64_t ans=1;
    for(;b;a=mul(a,a,p),b>>=1)if(b&1)ans=mul(ans,a,p);
    return ans;
  }
  il bool prime(int64_t x){
    if(x<3||x%2==0)return x==2;
    int64_t u=x-1,t=0;
    while(u%2==0) u/=2,++t;
    int64_t ud[]={2,325,9375,28178,450775,9780504,1795265022};
    for(int64_t a:ud){
      int64_t v=pow(a,u,x);
      if(v==1||v==x-1||v==0) continue;
      for(int j=1;j<=t;j++){
        v=mul(v,v,x);
        if(v==x-1&&j!=t){v=1;break;}
        if(v==1) return 0;
      }
      if(v!=1) return 0;
    }
    return 1;
  }
}using Miller_Rabin::prime;

typedef std::complex<double> C;
typedef int64_t i64;

const int MAXS=16,MAXN=104000,MAXA=64;
const i64 P=998244353;

i64 p[MAXA];int T,s,a[MAXA];
struct Vec{
  char t[MAXS];
  int M=0;
  il Vec(){memset(t,0,sizeof(char)*MAXS);}
  il bool next(Vec v){
    for(int i=0,w=1;i!=s;w*=(a[i++]+1)){
      if(t[i]==v[i]){M-=t[i]*w,t[i]=0;continue;}
      M+=w,t[i]++;return 1;
    }
    return 0;
  }
  il char&operator[](char x){return t[x];}
  il Vec operator+(Vec v){Vec x;for(char i=0;i!=s;i++)x[i]=t[i]+v[i];return x;}
  il Vec operator-(Vec v){Vec x;for(char i=0;i!=s;i++)x[i]=t[i]-v[i];return x;}
};

il int M(Vec v){int x=0;for(int i=0,w=1;i!=s;w*=(a[i++]+1))x+=v[i]*w;return x;}
il i64 D(Vec v){i64 x=1;for(int i=0;i!=s;i++)x*=(v[i]+1);return x;}
il i64 V(Vec v){i64 x=1;for(int i=0;i!=s;i++)x=x*powl(p[i],v[i])+.5;return x;}

il void conv(int*f,Vec vd,Vec vp,Vec n,int Vd,int Vp,bool mod1,bool mod2){
  static int F[MAXN];Vec i;
  if(mod1)do F[i.M+Vd]=f[i.M];while(i.next(n-vd));
  if(mod2)do F[i.M+Vp]+=P-f[i.M];while(i.next(n-vp));
  if(mod1)do f[i.M+Vd]=(f[i.M+Vd]+F[i.M+Vd])%P,F[i.M+Vd]=0;while(i.next(n-vd));
  if(mod2)do f[i.M+Vp]=(f[i.M+Vp]+F[i.M+Vp])%P,F[i.M+Vp]=0;while(i.next(n-vp));
//  do f[i.M]=(f[i.M]+F[i.M])%P,F[i.M]=0;while(i.next(n));
}
il int slove(Vec n){
  static int f[MAXN];f[0]=1;int ans=0;
  std::map<i64,char>Pn;Vec d;
  for(int i=0;i!=s;i++){
    Vec d_1;i64 fact=p[i]-1;bool fg=1;
    for(auto [p_w,w]:Pn)while(fact%p_w==0)fact/=p_w,fg&=(++d_1[w]<=a[w]);
    if(fact!=1)fg=0;d[i]=1;conv(f,d_1,d,n,M(d_1),M(d),fg,1);d[i]=0;Pn[p[i]]=i;
  }
  do if(!Pn.count(V(d)+1)&&prime(V(d)+1))conv(f,d,d,n,d.M,0,1,0);while(d.next(n));
  do ans=(ans+D(n-d)*f[d.M])%P,f[d.M]=0;while(d.next(n));return ans;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
//  std::cin>>T;
  T=1;
  while(T--){
    std::cin>>s;Vec n;
    for(int i=0;i!=s;i++)std::cin>>p[i]>>a[i],n[i]=a[i];
    if(p[0]!=2){std::cout<<"2\n";continue;}
    std::cout<<slove(n)<<"\n";
  }
  return 0;
}
/*
1
6
2 12
3 9
5 6
7 3
11 2
13 1
*/
