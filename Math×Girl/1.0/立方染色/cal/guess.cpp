#include<bits/stdc++.h>
const int d=4,pd=81,fd=16;

int ans=0;
std::bitset<pd>a;
int vis[fd];
inline int m(int a0,int a1,int a2,int a3){
	return a0+a1*3+a2*9+a3*27;
}
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
void dfs(int f){
	if(f==fd){
		if(check())return;
		std::cout<<++ans<<":"<<a<<"\n";
		return;
	}
	if(vis[f]){dfs(f+1);return;}
	std::bitset<d>W(f);
	for(int a0=0;a0<=1-W[0];a0++){
		for(int a1=0;a1<=1-W[1];a1++){
			for(int a2=0;a2<=1-W[2];a2++){
				for(int a3=0;a3<=1-W[3];a3++){
					a[m(W[0]*2+a0,W[1]*2+a1,W[2]*2+a2,W[3]*2+a3)]=1;
					for(int b0=0;b0<=a0;b0++)
						for(int b1=0;b1<=a1;b1++)
							for(int b2=0;b2<=a2;b2++)
								for(int b3=0;b3<=a3;b3++)
									vis[f+b0+(b1<<1)+(b2<<2)+(b3<<3)]++;
					dfs(f+1);
					for(int b0=0;b0<=a0;b0++)
						for(int b1=0;b1<=a1;b1++)
							for(int b2=0;b2<=a2;b2++)
								for(int b3=0;b3<=a3;b3++)
									vis[f+b0+(b1<<1)+(b2<<2)+(b3<<3)]--;
					a[m(W[0]*2+a0,W[1]*2+a1,W[2]*2+a2,W[3]*2+a3)]=0;
				}
			}
		}
	}
}
int main(){
	dfs(0);
	system("PAUSE");
	return 0;
}
