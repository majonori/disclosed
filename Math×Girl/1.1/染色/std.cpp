#include<bits/stdc++.h>
typedef unsigned long long i8;
const i8 P=998244353;
i8 fpow(i8 a,i8 n){
  if(!a)return 0;i8 ans=1;
  for(n%=P-1;n;n>>=1,(a*=a)%=P)if(n&1)(ans*=a)%=P;
  return ans;
}
i8 slove(){
  i8 a,b,n,ans=0;
  std::cin>>a>>b>>n;
  i8 B=a/b%(P-1),T=a%b%P,b_T=(b%P+P-T)%P;
  a%=P,b%=P;
  i8 bb=b*b%P,bpB=fpow(b,B);
  if(n==1)return (2*(T*bpB%P*b+b_T*bpB)+P-bb)%P;
  i8 bC2=b*(b-1)/2%P,TC2=T*(T-1)/2%P,b_TC2=b_T*(b_T-1)/2%P;
  i8 Tb_T=T*b_T%P,TT=T*T%P,b_Tb_T=b_T*b_T%P,b_1=(b+P-1)%P;
  i8 bC2pB=fpow(bC2,B),b_1pB=fpow(b_1,B);
  i8 bpB1=bpB*b%P,b_1pB1=b_1pB*b_1%P;
  i8 bp2B=bpB*bpB%P,bp2B1=bp2B*b%P,bp2B2=bp2B1*b%P;
  i8 b_1p2B=b_1pB*b_1pB%P,b_1p2B1=b_1p2B*b_1%P,b_1p2B2=b_1p2B1*b_1%P;
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
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  i8 T;std::cin>>T;
  while(T--)std::cout<<slove()<<"\n";
  return 0;
}
