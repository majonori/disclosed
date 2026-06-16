#include<bits/stdc++.h>
#define il inline __attribute__((__always_inline__))
typedef unsigned int i4;
typedef unsigned long long i8;
const i8 MOD=998244353,I=1,MX=2000005;

//il i8 Mul(const i4*F,const i4*G,const i4 n){
//  i4 ans=0;
//  for(i4 i:d[n])ans=(ans+I*F[i]*G[n/i])%MOD;
//  return ans;
//}
//il i4 Div(const i4 F_n,const i4 IG_1,const i4*G,const i4 *H,const i4 n){
//  i4 ans=F_n;
//  for(i4 i:d[n])if(i!=n)ans=(ans+MOD-I*H[i]*G[n/i])%MOD;
//  return I*ans*IG_1%MOD;
//}
i4 G[3][MX],IG_1;//G=G[0],分子=G[1],分母=G[2]
void Newton_Iteration(const i4 n){
  for(i4 i=2;i<=n;i++){
    for(i4 j=1;j<=i&&i*j<=n;j++)
      G[1][i*j]=(G[1][i*j]+I*G[0][i]*G[0][j])%MOD;
    for(i4 j=1;j< i&&i*j<=n;j++)
      G[1][j*i]=(G[1][j*i]+I*G[0][j]*G[0][i])%MOD;
    G[1][i]=(G[1][i]+1)%MOD;
    
    G[2][i]=0;
    
    for(i4 j=2;j<=i&&i*j<=n;j++)
      G[0][i*j]=(G[0][i*j]+MOD-I*G[0][i]*G[2][j])%MOD;
    for(i4 j=1;j< i&&i*j<=n;j++)
      G[0][j*i]=(G[0][j*i]+MOD-I*G[0][j]*G[2][i])%MOD;
    G[0][i]=I*(G[1][i]+G[0][i])*IG_1%MOD;
  }
//  G[1][n]=(Mul(G[0],G[0],n)+3*(MOD-G[0][n])+1)%MOD,G[2][n]=2*(MOD-G[0][n])%MOD;
//  G[0][n]=Div(G[1][n],IG_1,G[2],G[0],n);
}
int main(){
  i4 n = 2e6;
  IG_1=1;G[0][1]=1,G[1][1]=0,G[2][1]=1;
  Newton_Iteration(n);
  for(i4 i = 1; i <= 100; ++i)
    std::cout<<G[0][i]<<" ";
  return 0;
}
