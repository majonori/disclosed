#include<bits/stdc++.h>
typedef long long i8;
i8 x,y,ans;
i8 dis(i8 k){
	i8 yc= ceil(1.0*x/k),xc=k*yc,c=abs(yc-y)+abs(xc-x);
	i8 yf=floor(1.0*x/k),xf=k*yf,f=abs(yf-y)+abs(xf-x);
	return std::min(c,f);
}
int main(){
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin>>x>>y;
	if(x<y)std::swap(x,y);
	
	ans=dis(x/y);
	for(i8 t=1;abs(1.0*x/(x/y-t)-y)<ans;t++)
		ans=std::min(ans,dis(x/y-t));
	for(i8 t=1;abs(1.0*x/(x/y+t)-y)<ans;t++)
		ans=std::min(ans,dis(x/y+t));
	std::cout<<ans;
	
	return 0;
}
/*
x>y

两条线的斜率的倒数：
k= ceil(x/y)
        x/y
k=floor(x/y)

若确定 k,那么:
y'=ceil(x/k)  or  floor(x/k)
x'=ky'

x/(x/y-1)-y<1
1234567890123456789
1000000000000000000
114514191981
*/
