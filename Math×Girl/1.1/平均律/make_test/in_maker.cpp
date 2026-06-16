#include <bits/stdc++.h>
#include <random>
//typedef unsigned int ui4;
typedef unsigned long long ui8;
//typedef int i4;
//typedef long long i8;
typedef long double ld;
typedef std::pair<ui8,ui8> P;

std::random_device rd;
std::mt19937 random(rd());

ui8 full(){return (1ull*random())<<32|random();}
ui8 r(ui8 l,ui8 r){return full()%(r-l+1)+l;}
ui8 r(ui8 r){return ::r(1,r);}
ui8 p(short r){return pow(10,r);}
ui8 pr(short l,short r){return ::r(p(l),p(r));}
ui8 pr(short r){return ::r(p(r));}
ui8 plr(short r){return p(r)-p(r-1)+::r(p(r-1));}
ui8 r(P x){return r(x.first,x.second);}
ld dr(){return 1.0L*full()/powl(2,64);}
ld dr(ld l,ld r){return l+dr()*(r-l);}

void make(ui8 maxn,ld(*f)(ui8)){
  ui8 n=r(0.9*maxn,maxn);
  ui8 b=pr(18),a=r(b/(2*n*n),b/f(n));
  std::cout<<n<<" "<<a<<" "<<b<<"\n";
}

const ui8 T1=5;
int main() {
  for(int i=1;i<=20;++i) {
    std::cerr<<i<<":";
    std::stringstream s;s<<i<<".in";
    freopen(s.str().c_str(),"w",stdout);
    
    ui8 T=T1,N=p(6);
    if (i <= 2) {
      std::cout<<T<<"\n";
      while(T--){
        ui8 n=r(N/10,N),b=pr(18),a=dr(1.0/n,1)*b;
        std::cout<<n<<" "<<a<<" "<<b<<"\n";
      }
    } else if (i <= 4) {
      std::cout<<T<<"\n";
      while(T--){
        ui8 n=r(N/10,N),b=pr(17,18),a=dr(0,1.0/(2*n*n))*b;
        std::cout<<n<<" "<<a<<" "<<b<<"\n";
      }
    }else{
      T=(i>=17?1:5);
      std::cout<<T<<"\n";
      while(T--){
        switch (i) {
        case 5:make(p(3),[](ui8 n)->ld{return 2*n;});break;
        case 6:make(p(3),[](ui8 n)->ld{return pow(n,1.8);});break;
        case 7:make(p(3),[](ui8 n)->ld{return 0.5*n*n;});break;
        
        case 8:make(p(4),[](ui8 n)->ld{return 2*n;});break;
        case 9:make(p(4),[](ui8 n)->ld{return pow(n,1.8);});break;
        case 10:make(p(4),[](ui8 n)->ld{return 0.5*n*n;});break;
        
        case 11:make(p(5),[](ui8 n)->ld{return 2*n;});break;
        case 12:make(p(5),[](ui8 n)->ld{return pow(n,1.8);});break;
        case 13:make(p(5),[](ui8 n)->ld{return 0.5*n*n;});break;
        
        case 14:make(2*p(6),[](ui8 n)->ld{return 2*n;});break;
        case 15:make(2*p(6),[](ui8 n)->ld{return pow(n,1.8);});break;
        case 16:make(2*p(6),[](ui8 n)->ld{return 0.5*n*n;});break;
        
        case 17:make(p(7),[](ui8 n)->ld{return 2*n;});break;
        case 18:make(p(7),[](ui8 n)->ld{return pow(n,1.5);});break;
        case 19:make(p(7),[](ui8 n)->ld{return pow(n,1.9);});break;
        case 20:make(p(7),[](ui8 n)->ld{return 0.5*n*n;});break;
        }
      }
    }
    
    fclose(stdout);
    std::cerr<<"\n";
  }
  return 0;
}
