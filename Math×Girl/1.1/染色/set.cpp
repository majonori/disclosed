#include<bits/stdc++.h>
#define a 10
#define b 4
typedef unsigned long long i8;
typedef std::bitset<a*a> MAP;
typedef std::unordered_set<MAP> SET;
SET X,Y,U,I;//X,Y,并,交
inline i8 p(i8 x,i8 y){return x+a*y;}
inline void out(MAP x){
	std::cout<<"\n";
	for(i8 i=0;i!=a;i++){
		for(i8 j=0;j!=a;j++)
			std::cout<<x[p(i,j)];
		std::cout<<"\n";
	}
	std::cout<<"\n";
}
inline SET S_intersection(const SET&A,const SET&B){
	SET V;
	for(auto i:A)
		if(B.count(i))V.insert(i);
	return V;
}
inline SET S_union(const SET&A,const SET&B){
	SET V=A;
	V.insert(B.begin(),B.end());
	return V;
}
inline SET operator *(const SET&A,const SET&B){
	SET V;
	for(auto i:A){
		for(auto j:B){
			if((i&j).count())continue;
			V.insert(i|j);
		}
	}
	return V;
}
int main(){
	for(i8 k=0;k<b;k++){
		for(i8 x=0;x<=i8(pow(b,a/b+1));x++){
			MAP node;
			for(i8 v=x,t1=0;b*t1+k<a;t1++,v/=b){
				for(i8 t2=0;v%b+b*t2<a;t2++)
					node[p(v%b+b*t2,b*t1+k)]=1;
			}
			X.insert(node);
		}
	}
	for(i8 k=0;k<b;k++){
		for(i8 x=0;x<=i8(pow(b,a/b+1));x++){
			MAP node;
			for(i8 v=x,t1=0;b*t1+k<a;t1++,v/=b){
				for(i8 t2=0;v%b+b*t2<a;t2++)
					node[p(b*t1+k,v%b+b*t2)]=1;
			}
			Y.insert(node);
		}
	}
	I=S_intersection(X,Y);
	U=S_union(X,Y);
	
//	for(auto i:X)out(i);
	std::cout<<"|U|="<<U.size()<<"\n";
	std::cout<<"|X|="<<X.size()<<"\n";
	std::cout<<"|Y|="<<Y.size()<<"\n";
	std::cout<<"|I|="<<I.size()<<"\n";
	std::cout<<"|X|+|Y|-|I|="<<X.size()+Y.size()-I.size()<<"\n";
	std::cout<<"\n";
	std::cout<<"|U*U|="<<(U*U).size()<<"\n";
	std::cout<<"|X*X|="<<(X*X).size()<<"\n";
	std::cout<<"|X*Y|="<<(X*Y).size()<<"\n";
	std::cout<<"|Y*Y|="<<(Y*Y).size()<<"\n";
	std::cout<<"|X*I|="<<(X*I).size()<<"\n";
	std::cout<<"|I*Y|="<<(I*Y).size()<<"\n";
	std::cout<<"|I*I|="<<(I*I).size()<<"\n";
//	std::cout<<"2|XX|+|XY|-2|XI|="<<2*(X*X).size()+(X*Y).size()-2*(X*I).size()<<"\n";
//	std::cout<<"\n";
//	std::cout<<"|U*U*U|="<<(U*U*U).size()<<"\n";
//	std::cout<<"|X*X*X|="<<(X*X*X).size()<<"\n";
//	std::cout<<"|X*X*Y|="<<(X*X*Y).size()<<"\n";
//	std::cout<<"|X*Y*Y|="<<(X*Y*Y).size()<<"\n";
//	std::cout<<"|Y*Y*Y|="<<(Y*Y*Y).size()<<"\n";
//	std::cout<<"\n";
//	std::cout<<"|U*U*U*U|="<<(U*U*U*U).size()<<"\n";
	
	return 0;
}
