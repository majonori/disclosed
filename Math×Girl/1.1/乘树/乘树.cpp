#include<bits/stdc++.h>
#define P 998244353ull
#define int int64_t
int n,m,I,C[2][64],S[64],K[64];
int fpow(int a,int n=P-2){
  int ans=1;for(;n;n>>=1,(a*=a)%=P)if(n&1)(ans*=a)%=P;return ans;
}
void Init(){
  int a[64];a[0]=m+1,I=1;
  for(int i=0;a[i]!=1;++i)for(int f=1;f!=-1;--f){
    int v=(a[i]>>1)+(a[i]&f);
    for(int j=i+1;j!=I;++j)if(a[j]==v){C[f][i]=j;break;}
    if(!C[f][i])C[f][i]=I,a[I]=v,I++;
  }S[0]=1,S[--I-1]+=P-(m*(m+1ll)/2+1)%P,S[I]=(1ll*m*m+1)%P;
  for(int i=0;i!=I;++i)
    (S[C[0][i]]+=S[i])%=P,(S[C[1][i]]+=S[i])%=P;
//  S[I]=fpow(S[I]);
  for(int i=0;i!=I;++i)
    (K[C[0][i]]+=S[i])%=P,(K[C[1][i]]+=S[i])%=P;K[I]-=1;
  for(int i=0;i<=I;i++)std::cout<<K[i]<<"\t";std::cout<<"\n\n";
  for(int i=I-1;i>=0;--i)
    (K[C[0][i]]+=K[i])%=P,(K[C[1][i]]+=K[i])%=P;
  
  for(int i=0;i<=I;i++)std::cout<<i<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<a[i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<C[1][i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<C[0][i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<S[i]<<"\t";std::cout<<"\n";
  for(int i=0;i<=I;i++)std::cout<<K[i]<<"\t";std::cout<<"\n";
}
signed main(){
  m=6;Init();
  return 0;
}
