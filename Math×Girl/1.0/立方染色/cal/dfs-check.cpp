#include<bits/stdc++.h>
const int d=4,pd=81;

int ans=0;
std::bitset<pd>a;
int check(){
	for(int w=0;w!=1<<d;w++){
		std::bitset<d>W(w);
		int sum=0;
		for(int p=0;p!=1<<d;p++){
			std::bitset<d>P(p);
			int pos=0;
			for(int i=0,k=1;i!=d;i++,k*=3)
				pos+=k*(W[i]+P[i]);
			sum+=a[pos];
		}
		if(sum> 1)return 2;
		if(sum==0)return 1;
	}
	return 0;
}
void dfs(int bit){
	int cnt=check();
	if(cnt==0){
		std::cout<<++ans<<":"<<a<<"\n";
		return;
	}
	if(cnt==2||bit==pd)return;
	dfs(bit+1);
	a[bit]=1,dfs(bit+1),a[bit]=0;
}
int main(){
	dfs(0);
	return 0;
}
