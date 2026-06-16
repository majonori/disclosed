#include<bits/stdc++.h>
typedef long long i8;
i8 T,x,y;

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

int main(){
  std::cin>>T;
  while(T--){
    scanf("%lld%lld",&x,&y);
//    std::cin>>x>>y;
    if(x<y)std::swap(x,y);
    std::cout<<(y<x/y?ysolve():ksolve())<<"\n";
  }return 0;
}
