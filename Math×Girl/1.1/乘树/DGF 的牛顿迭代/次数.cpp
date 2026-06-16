#include<bits/stdc++.h>
typedef unsigned int i4;
typedef unsigned long long i8;
const i8 MOD=998244353,I=1,MX=10005;
i8 count(i8 n){
  i8 ans=0;
  for(i8 i=2;i*i<=n;i++){
    i8 k=0;
    while(n%i==0)++k,n/=i;
    ans=std::max(ans,k);
  }
  return std::max(1ull,ans);
}
signed main(){
  i8 cnt=0;
  for(i4 i=1;i<=100;++i){
    if(count(i)<3)cnt++;
    std::cout<<cnt<<" ";
  }
  return 0;
}
