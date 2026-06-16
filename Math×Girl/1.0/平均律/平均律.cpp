#include<bits/stdc++.h>
typedef unsigned int i4;
typedef unsigned long long i8;
const i8 MOD=998244353;
i8 fpow(i8 a,i8 n=MOD-2){
  i8 ans=1;a%=MOD;
  for(;n;n>>=1,(a*=a)%=MOD)if(n&1)(ans*=a)%=MOD;
  return ans;
}
struct frac{
#define il inline __attribute__((__always_inline__))
  i8 a,b;//frac{a}{b}
  il void rdt(){if(!a){b=1;return;}i8 g=std::gcd(a,b);a/=g,b/=g;}
  il frac(i8 A=0,i8 B=1):a(A),b(B){rdt();}
  il frac operator+(frac x){return frac(a*x.b+b*x.a,x.b*b);}
  il frac operator-(frac x){return frac(a*x.b-b*x.a,x.b*b);}
  il friend i8 model(frac x){return x.a%MOD*fpow(x.b)%MOD;}
  il friend frac inv(frac x){return frac(x.b,x.a);}
  il friend bool operator<(frac x,frac y){return x.a*y.b<x.b*y.a;}
};
std::ostream&operator<<(std::ostream&out,frac x) {
  return out<<"\\frac{"<<x.a<<"}{"<<x.b<<"}";
}
frac next(frac x,char f){
  if(x.a==1)return (f==1?frac(1,x.b-1):frac(0,1));
  frac v(x.b/x.a,1);return inv(v+next(inv(x)-v,-f));
}
void slove(){
  i4 n,a,b;std::cin>>n>>a>>b;
  frac delta(a,b);i4 ans=0;
  if(frac(1,n)<delta){std::cout<<"0\n";return;}
  for(i4 i=1;i<n;i++){
    if(std::gcd(i,n)!=1)continue;
    frac x(i,n);frac _x=next(x,-1),x_=next(x,1);
    _x=std::max(_x+delta,x-delta),x_=std::min(x_-delta,x+delta);
    std::cout<<_x<<"<"<<x<<"<"<<x_<<"-"<<x_-x<<"-"<<x-_x<<"\\\\\\\\\n";
    if(_x<x_)ans=(ans+model(x_-_x))%MOD;
  }std::cout<<ans<<"\n";
}
int main(){
//  std::ios::sync_with_stdio(0);
//  std::cin.tie(0),std::cout.tie(0);
  i4 T;std::cin>>T;
  while(T--)slove();
  return 0;
}
