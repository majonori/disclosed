#include <bits/stdc++.h>
#include <random>
std::random_device rd;
std::mt19937 random(rd());//uint32_t
uint64_t N(uint64_t key) {
	return (random() % key) + 1;
}
uint64_t d(uint64_t n){
	uint64_t ans=1;
	for(uint64_t i=2,k=0;i*i<=n;i++)
		if(!(n%i)){k=0;while(!(n%i))++k,n/=i;ans*=(k+1);}
	if(n!=1)ans*=2;
	return ans;
}
int main() {
	for (int i = 1; i <= 20; ++i) {
		std::cerr << i << ":";
		std::stringstream s;
		s << i << ".in";
		freopen(s.str().c_str(), "w", stdout);

		if (i <= 4) {
			std::cout << 9000000 + N(1000000) << "\n";
		} else if (i <= 8) {
			uint64_t k=1,t=N(1000);
			while(d(k*t)<=100)k*=t,t=N(1000);
			std::cout<<k;
			std::cerr<<d(k);
		} else if (i <= 20) {
			uint64_t k=1,t=N(100);
			while(d(k*t)<=10000)k*=t,t=N(100);
			std::cout<<k;
			std::cerr<<d(k);
		}

		fclose(stdout);
		std::cerr<<"\n";
	}
	return 0;
}
