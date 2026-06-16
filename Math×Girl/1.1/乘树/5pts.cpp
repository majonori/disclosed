#include<bits/stdc++.h>
typedef unsigned int i4;
typedef unsigned long long i8;
const i8 MOD=998244353,I=1,MX=10005;
i4 n,m,f[MX];
signed main(){
//  std::cin>>n>>m;
  
  n=100;
  std::cout<<"1 ";
  f[1]=1;
  for(i4 i=2;i<=n;++i){
    f[i]=1;
    for(i4 j=2;j<i;++j)
      if(i%j==0)f[i]=(f[i]+I*f[j]*f[i/j])%MOD;
    std::cout<<f[i]<<" ";
  }
  return 0;
}











#include<bits/stdc++.h>
#define MAXN 200005
int64_t strength(int64_t SA,int64_t SD){return SA*SA+SD*SD;}
bool cmp(std::pair<int,int> X,std::pair<int,int> Y)
{if(X.first==Y.first)return X.second<Y.second;return X.first>Y.first;}
std::pair<int,int> A[MAXN],D[MAXN];//val,id
bool used[MAXN];int N,M,TA,TD,SA[MAXN],SD[MAXN];
int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);
  freopen("pick.in","r",stdin);
  freopen("pick.out","w",stdout);
  
  std::cin>>N;
  for(int i=0,a;i!=N;i++)std::cin>>a,A[i]={a,i};std::sort(A,A+N,cmp);
  for(int i=0,d;i!=N;i++)std::cin>>d,D[i]={d,i};std::sort(D,D+N,cmp);
  std::cin>>M;
  for(int i=0;i!=M;i++)std::cin>>SA[i];for(int i=0;i!=M;i++)std::cin>>SD[i];
  for(int i=0;i!=M;i++){
    int64_t VA=strength(SA[i]+A[TA].first,SD[i]);
    int64_t VD=strength(SA[i],SD[i]+D[TD].first);
    if(VA==VD){if(A[TA].second<D[TD].second)++VA;else ++VD;}
    if(VA>VD)std::cout<<A[TA].second+1<<"\n",used[A[TA].second]=1;
    else     std::cout<<D[TD].second+1<<"\n",used[D[TD].second]=1;
    while(used[A[TA].second])++TA;while(used[D[TD].second])++TD;
  }
  return 0;
}
