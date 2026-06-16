#include <bits/stdc++.h>
#include <random>
char a[2][100000];
int main() {
	std::random_device rd;
	std::mt19937 random(rd());
	for (int number = 1; number <= 20; ++number) {
		std::cout << number << ":start----";
		std::stringstream s;
		s << "std.exe<" << number << ".in>" << number << ".out";
		system(s.str().c_str());
		std::cout << "end\n";
	}
	return 0;
}
