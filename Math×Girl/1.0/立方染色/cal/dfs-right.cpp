#include<bits/stdc++.h>
const int d=3,pd=27,fd=8;

int ans=0;
std::bitset<pd>a;
int vis[fd];
inline int m(int a0,int a1,int a2){
	return a0+a1*3+a2*9;
}
void out(){
  for(int x=0;x!=3;x++){
    for(int y=0;y!=3;y++){
      for(int z=0;z!=3;z++)
        std::cout<<a[m(x,y,z)];
      std::cout<<"  ";
    }
    std::cout<<"\n";
  }
  std::cout<<"\n\n";
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
		out();
		std::cout<<check()<<"\n\n";
		return;
	}
	if(vis[f]){dfs(f+1);return;}
	std::bitset<d>W(f);
	for(int a0=0;a0<=1-W[0];a0++){
		for(int a1=0;a1<=1-W[1];a1++){
			for(int a2=0;a2<=1-W[2];a2++){
				a[m(W[0]*2+a0,W[1]*2+a1,W[2]*2+a2)]=1;
				for(int b0=0;b0<=a0;b0++)
					for(int b1=0;b1<=a1;b1++)
						for(int b2=0;b2<=a2;b2++)
							vis[f+b0+(b1<<1)+(b2<<2)]++;
				dfs(f+1);
				for(int b0=0;b0<=a0;b0++)
					for(int b1=0;b1<=a1;b1++)
						for(int b2=0;b2<=a2;b2++)
							vis[f+b0+(b1<<1)+(b2<<2)]--;
				a[m(W[0]*2+a0,W[1]*2+a1,W[2]*2+a2)]=0;
			}
		}
	}
}
int main(){
	dfs(0);
	return 0;
}
