#include<bits/stdc++.h>
namespace Miller_Rabin{
	const int Pcnt=7;
	const int64_t p[Pcnt]={2,325,9375,28178,450775,9780504,1795265022};
	int64_t pow(int64_t a,int64_t b,int64_t p){
		int64_t ans=1;
		for(;b;a=(__int128)a*a%p,b>>=1)if(b&1)ans=(__int128)ans*a%p;
		return ans;
	}
	bool check(int64_t x,int64_t p){
		if(x%p==0||pow(p%x,x-1,x)^1)return 1;
		int64_t t,k=x-1;
		while((k^1)&1){
			t=pow(p%x,k>>=1,x);
			if(t^1&&t^(x-1))return 1;
			if(!(t^(x-1)))return 0;
		}return 0;
	}
	bool prime(int64_t x){
		if(x<2)return 0;
		for(int64_t i=0;i!=Pcnt;++i){
			if(x<=p[i])return 1;
			if(check(x,p[i]))return 0;
		}return 1;
	}
}using Miller_Rabin::prime;

typedef std::complex<double> C;
typedef int32_t i32;
typedef int64_t i64;

const double PI2=6.2831853071795864769l;
const i32 MAXS=16,MAXN=104000,MAXA=64;
const i64 P=998244353;

i64 T,s,p[MAXA],a[MAXA];
i64 nCr[MAXA<<1][MAXA],Inv[MAXA<<1];

struct Vec{
	i32 t[MAXS];
  Vec(){memset(t,0,sizeof(i32)*MAXS);}
  bool next(Vec v,i32 w=-1){
    for(i32 i=0;i!=s;i++){
      if(i==w||t[i]==v[i]){t[i]=0;continue;}
      t[i]++;return 1;
    }return 0;
  }
  i32&operator[](i32 x){return t[x];}
  bool operator+=(Vec v){for(i32 i=0;i!=s;i++)if((t[i]+=v[i])>a[i])return 0;return 1;}
  Vec operator-(Vec v){Vec x;for(i32 i=0;i!=s;i++)x[i]=t[i]-v[i];return x;}
};
i64 fpow(i64 a,i64 n=P-2){i64 x=1;for(;n;(a*=a)%=P,n>>=1)if(n&1)(x*=a)%=P;return x;}

i64 M(Vec v){i64 x=0;for(i64 i=0,w=1;i!=s;w*=(a[i++]+1))x+=v[i]*w;return x;}
i64 D(Vec v){i64 x=1;for(i64 i=0;i!=s;i++)x*=(v[i]+1);return x;}
i64 S(Vec v){i64 x=0;for(i64 i=0;i!=s;i++)x+=v[i];return x;}
i64 V(Vec v){i64 x=1;for(i64 i=0;i!=s;i++)x=x*powl(p[i],v[i])+.5;return x;}

void Init(){
  for(i32 i=1;i!=MAXA<<1;i++)Inv[i]=fpow(i);
  for(i32 i=0,j=1;i!=MAXA<<1;i++)
    for(nCr[i][0]=1,j=1;j<=i&&j!=MAXA;j++)
      nCr[i][j]=(nCr[i-1][j-1]+nCr[i-1][j])%P;
//  for(int i=0;i<=100;i++){
//    for(int j=0;j<=10;j++){
//      std::cout<<nCr[i][j]<<" ";
//    }std::cout<<"\n";
//  }
}

void exp(int*f,Vec n){
  static int g[MAXN];Vec d,i;g[0]=1,d.next(n);
  do{
    std::cout<<"2^:"<<M(d)<<"\n";
    do{
      g[M(d)]=(g[M(d)]+S(i)*f[M(i)]%P*g[M(d-i)])%P;
      std::cout<<S(i)<<","<<S(i)*f[M(i)]%P*g[M(d-i)]<<"\n";
    }
    while(i.next(d));
    g[M(d)]=g[M(d)]*fpow(S(d))%P;
  }while(d.next(n));
  do f[M(d)]=g[M(d)],g[M(d)]=0;while(d.next(n));
}

int slove(Vec n){
  static int f[MAXN],f2[MAXN];
  std::map<i64,i32> Pn;
  for(int i=0;i!=s;i++){
    Vec d_1,t;i64 fact=p[i]-1,j=0,k=0;
    if(fact==1){Pn[2]=0;continue;}
    for(auto [p_w,w]:Pn)
      while(fact%p_w==0)d_1[w]++,fact/=p_w;
    if(fact!=1)d_1[0]=MAXA;
    std::cout<<"-------";
    do{
      do{
        std::cout<<"\n"<<M(t)<<":"<<j<<","<<k<<","<<Inv[j+k]<<","<<nCr[j+k][j];
        f[M(t)]=(f[M(t)]+(j&1?1ll:P-1)*Inv[j+k]%P*nCr[j+k][j])%P;
      }
      while((t[i]=++k)<=a[i]);t[i]=k=0;++j;
    }while(t+=d_1);Pn[p[i]]=i;
    
    Vec d;do std::cout<<"\n "[d[0]>0]<<V(d)<<":"<<f[M(d)];
    while(d.next(n));std::cout<<"\n";
  }
  std::cout<<"-------\n";
  Vec d;d.next(n);do{
    if(Pn.count(V(d)+1)||!prime(V(d)+1))continue;
    Vec t;int j=1;
    std::cout<<V(d)<<":";
    for(;t+=d;j++){
      std::cout<<M(t)<<","<<V(t)<<":"<<(f[M(t)]+(j&1?1ll:P-1)*Inv[j])%P<<")(";
      f[M(t)]=(f[M(t)]+(j&1?1ll:P-1)*Inv[j])%P;
    }
    std::cout<<"\n";
  }while(d.next(n));
  
  do std::cout<<V(d)<<":"<<f[M(d)]<<"\n";
  while(d.next(n));
  
  exp(f,n);i64 ans=0;
  
  if(Pn.count(2))do if(M(d)%a[0])f2[M(d)]=-f[M(d)];
  while(d.next(n));
  do f[M(d)]=2*f[M(d)]-f2[M(d)],f2[M(d)]=0;
  while(d.next(n));
  
  do std::cout<<V(d)<<":"<<f[M(d)]<<"\n";
  while(d.next(n));
  
  do ans=(ans+f[M(d)]*D(n-d))%P,f[M(d)]=0;
  while(d.next(n));return ans;
}
//0 1 499122177 332748118
int f[100]={1,1,1,1};//,3,4,5,6,7,8,9,10};
Vec n;
int main(){
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0),std::cout.tie(0);
	Init();std::cin>>T;
	while(T--){
    std::cin>>s;Vec n;
    for(int i=0;i!=s;i++)std::cin>>p[i]>>a[i],n[i]=a[i];
    std::cout<<slove(n)<<"\n";
	}
	return 0;
}
/*
1
3
2 10
3 10
5 10

12052034
\varpai(x)\mid590490000000000
*/
