#include <bits/stdc++.h>
#include <conio.h>
#include <random>
typedef unsigned int ui4;
typedef unsigned long long ui8;
typedef int i4;
typedef long long i8;
typedef std::pair<ui8,ui8> P;

std::random_device rd;
std::mt19937 random(rd());

ui8 full(){return (1ull*random())<<32|random();}
ui8 r(ui8 l,ui8 r){return full()%(r-l)+l;}
ui8 r(P x){return r(x.first,x.second);}

i8 x,y;

i8 ydis(i8 ty){
  i8 kc=x/ty+1,xc=kc*ty,c=abs(ty-y)+abs(xc-x);
  i8 kf=x/ty  ,xf=kf*ty,f=abs(ty-y)+abs(xf-x);
  return std::min(c,f);
}i8 ysolve(){
  i8 ans=ydis(y);
  for(i8 t=1;t<ans;t++)
    ans=std::min(ans,ydis(y-t)),
    ans=std::min(ans,ydis(y+t));
  return ans;
}
i8 kdis(i8 k){
  i8 yc=x/k+1,xc=k*yc,c=abs(yc-y)+abs(xc-x);
  i8 yf=x/k  ,xf=k*yf,f=abs(yf-y)+abs(xf-x);
  return std::min(c,f);
}i8 ksolve(){
  i8 ans=kdis(x/y);
  for(i8 t=1;abs(1.0*x/(x/y-t)-y)<ans;t++)
    ans=std::min(ans,kdis(x/y-t));
  for(i8 t=1;abs(1.0*x/(x/y+t)-y)<ans;t++)
    ans=std::min(ans,kdis(x/y+t));
  return ans;
}

int size=0;
int main() {
//  freopen("big.in","w",stdout);
  
  std::cerr<<"start:\n";
  ui8 a=10000000000000000ull;
  for(i8 i=1;1;i++){
    ui8 v=r({1,a});
    x=v,y=r({0.5*sqrt(v),2*sqrt(v)});
//    x=v,y=r({pow(v,2.0/3),pow(v,3.0/4)});
    ui8 t=(y<x/y?ysolve():ksolve());
    if(t>=20000){
      size++;
      std::cerr<<"<"<<t<<">";
      std::cout<<x<<" "<<y<<"\n";
    }
    if(i%10000==0){
      std::cerr<<i<<":"<<size<<"\n";
      if(_kbhit())fclose(stdout),exit(0);
    }
//    std::cout<<x<<" "<<y<<"\n";
  }
  
  return 0;
}
