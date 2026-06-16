#include<bits/stdc++.h>
#define il inline __attribute__((__always_inline__))

typedef unsigned int i4;
typedef unsigned long long i8;

namespace Miller_Rabin{
  const i4 Pcnt=7;
  const i8 p[Pcnt]={2,325,9375,28178,450775,9780504,1795265022};
  il i8 mul(i8 a,i8 b,i8 p){
    return __int128(a)*b%p;
  }
  il i8 pow(i8 a,i8 b,i8 p){
    i8 ans=1;
    for(;b;a=mul(a,a,p),b>>=1)if(b&1)ans=mul(ans,a,p);
    return ans;
  }
  il bool prime(i8 x){
    if(x<3||x%2==0)return x==2;
    i8 u=x-1,t=0;
    while(u%2==0) u/=2,++t;
    i8 ud[]={11,61,13,97};
    for(i8 a:ud){
      i8 v=pow(a,u,x);
      if(v==1||v==x-1||v==0) continue;
      for(i4 j=1;j<=t;j++){
        v=mul(v,v,x);
        if(v==x-1&&j!=t){v=1;break;}
        if(v==1) return 0;
      }
      if(v!=1) return 0;
    }
    return 1;
  }
}using Miller_Rabin::prime;

const i4 MAXS=16,MAXN=104000,MAXA=64;
const i8 P=998244353;

i8 p[MAXA];i4 T,s,a[MAXA];
struct Vec{
  char t[MAXS];
  i4 M=0;
  il Vec(){memset(t,0,sizeof(char)*MAXS);}
  il bool next(Vec&v){
    for(i4 i=0,w=1;i!=s;w*=(a[i++]+1)){
      if(t[i]==v[i]){M-=t[i]*w,t[i]=0;continue;}
      M+=w,t[i]++;return 1;
    }
    return 0;
  }
  il char&operator[](char x){return t[x];}
  il Vec operator+(Vec v){Vec x;for(char i=0;i!=s;i++)x[i]=t[i]+v[i];return x;}
  il Vec operator-(Vec v){Vec x;for(char i=0;i!=s;i++)x[i]=t[i]-v[i];return x;}
};

il i4 M(Vec v){i4 x=0;for(i4 i=0,w=1;i!=s;w*=(a[i++]+1))x+=v[i]*w;return x;}
il i8 D(Vec v){i8 x=1;for(i4 i=0;i!=s;i++)x*=(v[i]+1);return x;}
il i8 V(Vec v){i8 x=1;for(i4 i=0;i!=s;i++)x=x*powl(p[i],v[i])+.5;return x;}

il void conv(i4*f,Vec n_vd,Vec n_vp,const i4 Vd,const i4 Vp,const bool mod1,const bool mod2){
  static i4 F[MAXN];Vec i;
  if(mod1)do F[i.M+Vd]=f[i.M];while(i.next(n_vd));
  if(mod2)do F[i.M+Vp]+=P-f[i.M];while(i.next(n_vp));
  if(mod1)do f[i.M+Vd]=(f[i.M+Vd]+F[i.M+Vd])%P,F[i.M+Vd]=0;while(i.next(n_vd));
  if(mod2)do f[i.M+Vp]=(f[i.M+Vp]+F[i.M+Vp])%P,F[i.M+Vp]=0;while(i.next(n_vp));
}
il i4 slove(Vec n){
  static i4 f[MAXN];f[0]=1;i4 ans=0;
  std::map<i8,char>Pn;Vec d;
  for(i4 i=0;i!=s;i++){
    Vec d_1;i8 fact=p[i]-1;bool fg=1;
    for(auto [p_w,w]:Pn)while(fact%p_w==0)fact/=p_w,fg&=(++d_1[w]<=a[w]);
    if(fact!=1)fg=0;d[i]=1;conv(f,n-d_1,n-d,M(d_1),M(d),fg,1);d[i]=0;Pn[p[i]]=i;
  }
  do if(!Pn.count(V(d)+1)&&prime(V(d)+1))conv(f,n-d,d,d.M,0,1,0);while(d.next(n));
  do ans=(ans+D(n-d)*f[d.M])%P,f[d.M]=0;while(d.next(n));return ans;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  std::cin>>T;
  while(T--){
    std::cin>>s;Vec n;
    for(i4 i=0;i!=s;i++)std::cin>>p[i]>>a[i],n[i]=a[i];
    if(p[0]!=2){std::cout<<"2\n";continue;}
    std::cout<<slove(n)<<"\n";
  }
  return 0;
}
