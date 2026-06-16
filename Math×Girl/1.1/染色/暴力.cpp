#include<bits/stdc++.h>
typedef long long i8;
#define C 6
i8 cnt(i8 v,i8 x,i8 y){
	i8 sum=0;
	for(i8 i=0;i<=2;i++){
		for(i8 j=0;j<=2;j++){
			sum+=bool(v&(1ull<<(C*(i+x)+(j+y))));
		}
	}
	return sum;
}
std::unordered_set<i8>s[10];
int main(){
	i8 ans=0;
#pragma omp parallel for schedule(guided)
	for(i8 v=0;v!=(1ull<<(C*C));v++){
		for(i8 i=0;i<=(C-3);i++){
			for(i8 j=0;j<=(C-3);j++){
				if(cnt(v,i,j)!=2)goto next;
			}
		}
		s[1].insert(v);
		ans++;
		next:;
	}
	std::cout<<ans<<"\n";
	for(auto i:s[1]){
		for(auto j:s[1]){
			if(i&j)continue;
			s[2].insert(i|j);
		}
	}
	for(auto i:s[2]){
		for(auto j:s[1]){
			if(i&j)continue;
			s[3].insert(i|j);
		}
	}
	for(auto i:s[3]){
		for(auto j:s[1]){
			if(i&j)continue;
			s[4].insert(i|j);
		}
	}
	std::cout<<s[2].size()<<"\n";
	std::cout<<s[3].size()<<"\n";
	std::cout<<s[4].size()<<"\n";
	return 0;
}
/*
#include<bits/stdc++.h>
typedef long long i8;
i8 cnt(i8 v,i8 x,i8 y){
	i8 sum=0;
	for(i8 i=0;i<=2;i++){
		for(i8 j=0;j<=2;j++){
			sum+=bool(v&(1<<(5*(i+x)+(j+y))));
		}
	}
	return sum;
}
std::unordered_set<i8>s;
std::unordered_set<i8>s2;
int main(){
	i8 ans=0;
	for(i8 v=0;v!=(1<<25);v++){
		for(i8 i=0;i<=2;i++){
			for(i8 j=0;j<=2;j++){
				if(cnt(v,i,j)!=1)goto next;
			}
		}
		s.insert(v);
		ans++;
		next:;
	}
	std::cout<<ans<<"\n";
	for(auto i:s){
		for(auto j:s){
			if(i&j)continue;
			s2.insert(i|j);
		}
	}
	std::cout<<s2.size()<<"\n";
	return 0;
}
*/
