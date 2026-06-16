#include <bits/stdc++.h>
#include <random>
char a[2][100000];
std::random_device rd;
std::mt19937 random(rd());//uint32_t
uint64_t N(uint64_t key) {
	return (random() % key) + 1;
}
int main() {
	for (int i = 1; i <= 20; ++i) {
		std::cerr << i << "\n";
		std::stringstream s;
		s << i << ".in";
		freopen(s.str().c_str(), "w", stdout);
		
		std::cout << "10\n";
		if (i <= 2) {
      for(int i=1;i<=10;++i)
        std::cout<<900+N(100)<<"\n";
		} else if (i <= 5) {
			for(int i=1;i<=10;++i)
				std::cout<<90000+N(10000)<<"\n";
		} else if (i <= 10) {
			for(int i=1;i<=10;++i)
				std::cout<<9000000+N(1000000)<<"\n";
		} else if (i <= 20) {
			for(int i=1;i<=10;++i)
				std::cout<<1500000000+N(500000000)<<"\n";
		}

		fclose(stdout);
	}
	return 0;
}
