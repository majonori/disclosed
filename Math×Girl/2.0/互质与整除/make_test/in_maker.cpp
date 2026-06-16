#include <bits/stdc++.h>
#include <random>
//typedef unsigned int ui4;
typedef unsigned long long ui8;
//typedef int i4;
//typedef long long i8;
typedef long double ld;

std::random_device rd;
std::mt19937 random(rd());

ui8 full(){return (1ull*random())<<32|random();}
ui8 r(ui8 l,ui8 r){return full()%(r-l+1)+l;}
ui8 r(ui8 r){return ::r(1,r);}
ui8 p(short r){return pow(10,r);}
ui8 pr(short l,short r){return ::r(p(l),p(r));}
ui8 pr(short r){return ::r(p(r));}
ui8 plr(short r){return 0.9*p(r)+::r(p(r-1));}
ld dr(){return 1.0L*full()/powl(2,64);}
ld dr(ld l,ld r){return l+dr()*(r-l);}

const ui8 T1=5,trytimes=10000;

struct node{
  std::map<ui8,ui8>fact;
  ui8 N,d,d3;
}a[trytimes+5];
bool operator==(node a,node b){
  return a.N==b.N;
}

ui8 getp(){
  ld p=dr();
  if(p<0.25)return 2;
  if(p<0.45)return 3;
  if(p<0.55)return 5;
  if(p<0.60)return 7;
  if(p<0.64)return 11;
  if(p<0.67)return 13;
  if(p<0.70)return 17;
  if(p<0.73)return 19;
  if(p<0.76)return 23;
  if(p<0.78)return 29;
  if(p<0.80)return 31;
  if(p<0.82)return 37;
  if(p<0.84)return 41;
  if(p<0.86)return 43;
  if(p<0.88)return 47;
  if(p<0.90)return 53;
  if(p<0.92)return 59;
  if(p<0.94)return 61;
  if(p<0.96)return 67;
  if(p<0.98)return 71;
  return 73;
}

node maken(ui8 max,ui8 st=2){
  std::map<ui8,ui8>fact;
  ui8 N=st,d=1,d3=1;fact[st]++;
  while(1){
    ui8 p=getp();
    if(N>=max/p)break;
    N*=p,fact[p]++;
  }
  for(auto[p,t]:fact)
    d*=(t+1),d3*=(t+1)*(t+2)/2;
  return {fact,N,d,d3};
}
void makea(ui8 max){
  for(ui8 i=1;i<=trytimes;i++)
    a[i]=maken(max);
}

bool cmpd(node a,node b){
  return a.d>b.d;
}
bool cmpd3(node a,node b){
  return a.d3>b.d3;
}

int main() {
  for(int i=1;i<=20;++i) {
    std::cerr<<i<<":";
    std::stringstream s;s<<i<<".in";
    freopen(s.str().c_str(),"w",stdout);
    
    if (i <= 2) {
      std::cout<<T1<<"\n";
      makea(p(7));
      std::sort(a+1,a+1+trytimes,cmpd);
      for(ui8 j=1;j<=T1;++j){
        std::cout<<a[j].fact.size()<<"\n";
        for(auto[p,t]:a[j].fact)
          std::cout<<p<<" "<<t<<"\n";
      }
    } else if (i <= 4) {
      std::cout<<T1<<"\n";
      makea(p(9));
      std::sort(a+1,a+1+trytimes,cmpd);
      for(ui8 j=1;j<=T1;++j){
        std::cout<<a[j].fact.size()<<"\n";
        for(auto[p,t]:a[j].fact)
          std::cout<<p<<" "<<t<<"\n";
      }
    } else if (i <= 8) {
      std::cout<<T1<<"\n";
      makea(p(12));
      std::sort(a+1,a+1+trytimes,cmpd);
      if(i==5)a[T1]=maken(p(12),3ull<<36|1);
      for(ui8 j=1;j<=T1;++j){
        std::cout<<a[j].fact.size()<<"\n";
        for(auto[p,t]:a[j].fact)
          std::cout<<p<<" "<<t<<"\n";
      }
    } else if (i <= 12) {
      std::cout<<T1<<"\n";
      makea(p(14));
      std::sort(a+1,a+1+trytimes,cmpd3);
      if(i==9)a[T1]=maken(p(14),5ull<<39|1);
      for(ui8 j=1;j<=T1;++j){
        std::cout<<a[j].fact.size()<<"\n";
        for(auto[p,t]:a[j].fact)
          std::cout<<p<<" "<<t<<"\n";
      }
    }else if (i <= 16) {
      std::cout<<T1<<"\n";
      makea(p(16));
      std::sort(a+1,a+1+trytimes,cmpd3);
      if(i==13)a[T1]=maken(p(16),5ull<<39|1);
      for(ui8 j=1;j<=T1;++j){
        std::cout<<a[j].fact.size()<<"\n";
        for(auto[p,t]:a[j].fact)
          std::cout<<p<<" "<<t<<"\n";
      }
    } else if (i <= 20) {
      std::cout<<T1<<"\n";
      makea(p(18));
      std::sort(a+1,a+1+trytimes,cmpd3);
      std::unique(a+1,a+1+trytimes);
      if(i==17)a[T1]=maken(p(18),5ull<<39|1);
      for(ui8 j=1;j<=T1;++j){
        std::cout<<a[j].fact.size()<<"\n";
        std::cerr<<a[j].d3<<"\n";
        for(auto[p,t]:a[j].fact)
          std::cout<<p<<" "<<t<<"\n";
      }
    }
    
    fclose(stdout);
    std::cerr<<"\n";
  }
  return 0;
}
