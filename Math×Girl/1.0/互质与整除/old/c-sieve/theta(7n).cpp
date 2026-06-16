#include<bits/stdc++.h>
#define maxn 70000010
int phi[maxn],n,ans,max;
bool vis[maxn];
std::vector<int> pri;
int main(){
  std::cin>>n;
  phi[1]=1,max=7*n;
  for(int i=2;i!=max;++i){
    if(!vis[i])pri.push_back(i),phi[i]=i-1;
    for(auto p:pri){
      if(i*p>=max)break;
      vis[i*p]=1;
      if(i%p==0){phi[i*p]=phi[i]*p;break;}
      phi[i*p]=phi[i]*(p-1);
    }
    ans+=!(n%phi[i]);
  }
  std::cout<<ans+1;
  return 0;
}
