#include<bits/stdc++.h>
namespace Miller_Rabin{
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
    for(int64_t i=0;i!=Pcnt;++i){
      if(x<=p[i])return 1;
      if(check(x,p[i]))return 0;
    }return 1;
  }
}using Miller_Rabin::prime;

typedef std::complex<double> C;
typedef int32_t i32;
typedef int64_t i64;

const i32 MAXS=16,MAXN=104000,MAXA=64;
const i64 P=998244353;

i64 T,s,p[MAXA],a[MAXA];
struct Vec{
  i32 t[MAXS];
  Vec(){memset(t,0,sizeof(i32)*MAXS);}
  bool next(Vec v,i32 w=-1){for(i32 i=0;i!=s;i++){if(i==w||t[i]==v[i]){t[i]=0;continue;}t[i]++;return 1;}return 0;}
  i32&operator[](i32 x){return t[x];}
  Vec operator+(Vec v){Vec x;for(i32 i=0;i!=s;i++)x[i]=t[i]+v[i];return x;}
  Vec operator-(Vec v){Vec x;for(i32 i=0;i!=s;i++)x[i]=t[i]-v[i];return x;}
};
i64 fpow(i64 a,i64 n=P-2){i64 x=1;for(;n;(a*=a)%=P,n>>=1)if(n&1)(x*=a)%=P;return x;}

i64 M(Vec v){i64 x=0;for(i64 i=0,w=1;i!=s;w*=(a[i++]+1))x+=v[i]*w;return x;}
i64 D(Vec v){i64 x=1;for(i64 i=0;i!=s;i++)x*=(v[i]+1);return x;}
i64 V(Vec v){i64 x=1;for(i64 i=0;i!=s;i++)x=x*powl(p[i],v[i])+.5;return x;}

void conv(int*f,Vec vd,Vec vp,Vec n,int mod){
  int64_t F[MAXN];Vec i;
  if(mod&1)do F[M(i+vd)]=f[M(i)];while(i.next(n-vd));
  if(mod&2)do F[M(i+vp)]+=P-f[M(i)];while(i.next(n-vp));
  do f[M(i)]=(f[M(i)]+F[M(i)])%P,F[M(i)]=0;while(i.next(n));
}
int slove(Vec n){
  static int f[MAXN];f[0]=1;int ans=0;
  std::map<i64,i32> Pn;Vec d;
  for(int i=0;i!=s;i++){
    Vec d_1;i64 fact=p[i]-1;bool fg=1;
    for(auto [p_w,w]:Pn)while(fact%p_w==0)fact/=p_w,fg&=(++d_1[w]<=a[w]);
    if(fact!=1)fg=0;d[i]=1;conv(f,d_1,d,n,2+fg);d[i]=0;Pn[p[i]]=i;
  }
  do if(prime(V(d)+1)&&!Pn.count(V(d)+1))conv(f,d,d,n,1);while(d.next(n));
  do ans=(ans+D(n-d)*f[M(d)])%P,f[M(d)]=0;while(d.next(n));return ans;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  std::cin>>T;
  while(T--){
    std::cin>>s;Vec n;
    for(int i=0;i!=s;i++)std::cin>>p[i]>>a[i],n[i]=a[i];
    if(p[0]!=2){std::cout<<"2\n";continue;}
    std::cout<<slove(n)<<"\n";
  }
  return 0;
}
