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

const ui8 P=998244353;
ui8 fpow(ui8 a,ui8 n){
  if(!(a%=P))return 0;ui8 ans=1;
  for(n%=P-1;n;n>>=1,(a*=a)%=P)if(n&1)(ans*=a)%=P;
  return ans;
}
ui8 slove(ui8 a,ui8 b,ui8 n){
  ui8 ans=0;
  ui8 B=a/b%(P-1),T=a%b%P,b_T=(b%P+P-T)%P;
  a%=P,b%=P;
  ui8 bb=b*b%P,bpB=fpow(b,B);
  if(n==1)return (2*(T*bpB%P*b+b_T*bpB)+P-bb)%P;
  ui8 bC2=b*(b-1)/2%P,TC2=T*(T-1)/2%P,b_TC2=b_T*(b_T-1)/2%P;
  ui8 Tb_T=T*b_T%P,TT=T*T%P,b_Tb_T=b_T*b_T%P,b_1=(b+P-1)%P;
  ui8 bC2pB=fpow(bC2,B),b_1pB=fpow(b_1,B);
  ui8 bpB1=bpB*b%P,b_1pB1=b_1pB*b_1%P;
  ui8 bp2B=bpB*bpB%P,bp2B1=bp2B*b%P,bp2B2=bp2B1*b%P;
  ui8 b_1p2B=b_1pB*b_1pB%P,b_1p2B1=b_1p2B*b_1%P,b_1p2B2=b_1p2B1*b_1%P;
  ans=(ans+2*(T*bC2pB%P*bC2+b_T*bC2pB)%P)%P;
  ans=(ans+2*(TC2*bp2B2+Tb_T*bp2B1+b_TC2*bp2B))%P;
  ans=(ans+TT*(2*bpB1*b_1pB1%P+P-b_1p2B2))%P;
  ans=(ans+2*Tb_T*((bpB*b_1pB1+bpB1*b_1pB)%P+P-b_1p2B1))%P;
  ans=(ans+b_Tb_T*(2*bpB*b_1pB%P+P-b_1p2B))%P;
  ans=(ans+bb*(bb-1)/2)%P;
  ans=(ans+P-2*b*T%P*(b_1*bpB1%P+b_1pB1)%P)%P;
  ans=(ans+P-2*b*b_T%P*(b_1*bpB%P+b_1pB)%P)%P;
  return ans;
}


const ui8 T1=10,T2=p(5);

ui8 get(ui8 T){
  if(T<=T1)return pr(9)*P+1;
  if(T<=2*T1)return pr(9)*P;
  return pow(p(18),dr(0.1,1));
}

int main() {
  for(int i=1;i<=20;++i) {
    std::cerr<<i<<":";
    std::stringstream s;s<<i<<".in";
    freopen(s.str().c_str(),"w",stdout);
    
    if (i <= 1) {
      std::cout<<"25\n";
      for(int a=1;a<=5;++a)
        for(int b=1;b<=a;++b)
          std::cout<<a<<" "<<b<<" 1\n";
      for(int a=2;a<=5;++a)
        for(int b=2;b<=a;++b)
          std::cout<<a<<" "<<b<<" 2\n";
    } else if (i <= 4) {
      ui8 T=T1;std::cout<<T<<"\n";
      while(T--){
        ui8 a,b,n=r(1,2);
        if(n==1)b=r(100),a=b;
        if(n==2)b=r(37),a=b;
        while(slove(a,b,n)<=p(6))++a;
        std::cout<<a-1<<" "<<b<<" "<<n<<"\n";
      }
    } else if (i <= 7) {
      ui8 T=T1;std::cout<<T<<"\n";
      while(T--){
        ui8 b=plr(3)/2,a=r(b,2*b),n=r(1,2);
        std::cout<<a<<" "<<b<<" "<<n<<"\n";
      }
    } else if (i <= 9) {
      ui8 T=T2;std::cout<<T<<"\n";
      while(T--){
        ui8 b=get(T),a=b*r(1,p(18)/b);
        std::cout<<a<<" "<<b<<" 1\n";
      }
    } else if (i <= 12) {
      ui8 T=T2;std::cout<<T<<"\n";
      while(T--){
        ui8 b=get(T),a=r(b,p(18));
        std::cout<<a<<" "<<b<<" 1\n";
      }
    } else if (i <= 15) {
      ui8 T=T2;std::cout<<T<<"\n";
      while(T--){
        ui8 b=get(T),a=b*r(1,p(18)/b);
        std::cout<<a<<" "<<b<<" 2\n";
      }
    } else if (i <= 20) {
      ui8 T=T2;std::cout<<T<<"\n";
      while(T--){
        ui8 b=get(T),a=r(b,p(18));
        std::cout<<a<<" "<<b<<" 2\n";
      }
    }
    
    fclose(stdout);
    std::cerr<<"\n";
  }
  return 0;
}
