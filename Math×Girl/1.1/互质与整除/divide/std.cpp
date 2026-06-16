#include <cstdio>
#include <iostream>
#include <cmath>
#define ll long long
using namespace std;

ll FastMul(ll x, ll y, ll mod){return (__int128)x * y % mod;}
ll FastPow(ll a, ll b, ll mod){
	ll res = 1;
	while(b){
		if(b & 1) res = FastMul(res, a, mod);
		b >>= 1, a = FastMul(a, a, mod);
	}
	return res;
}

ll FastPowNoMod(ll a, int b){
	ll res = 1;
	while(b){
		if(b & 1) res *= a;
		b >>= 1, a *= a;
	}
	return res;
}

const int ListNum = 12, List[ListNum] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool Miller_Rabin(ll x){
	if(x == 1) return false;
	ll D = x - 1;
	while(!(D & 1)) D >>= 1;
	for(int i = 0; i < ListNum; ++i){
		if(x == List[i]) return true;
		ll k = FastPow(List[i], D, x), d = D;
		if(k != 1){
			while(d < x - 1){
				if(k == x - 1) break;
				d <<= 1, k = FastMul(k, k, x);
			}
			if(d == x - 1) return false;
		}
	}
	return true;
}

const int Mx = 103700, Nx = 16, Mod = 998244353;

ll N;
ll prime[Nx], ksm[Nx]; // power[i][j] = prime[i] ^ j
int alpha[Nx], cnt; // N = prod_{i \le cnt} prime[i] ^ alpha[i]
int sigma0, prod[Nx]; // Find position for vector beta[]

int F[Mx], G[Mx]; // ans = sum_{d|n} f(d) sigma0(n/d)

int beta[Nx], id; ll now; // Numerate divisor of n, now = prod_{i \le cnt} prime[i] ^ beta[i]
int gamma[Nx], ids; // Numerate pres such that pre * now | n 
inline void getpos(ll x){
	id = 0;
	for(int i = 1; i <= cnt; ++i){
		int sum = 0;
		while(x % prime[i] == 0) x /= prime[i], ++sum;
		id += prod[i - 1] * sum, beta[i] = sum;
	}
}
inline bool pushup(){
	int pos = 1; ++id;
	while(beta[pos] == alpha[pos] && pos <= cnt) beta[pos] = 0, now /= ksm[pos], ++pos;
	return (pos == cnt + 1) ? 0 : (++beta[pos], now *= prime[pos], 1);
}
inline bool reduce(){
	int pos = 1;
	while(gamma[pos] == 0 && pos <= cnt) gamma[pos] = alpha[pos] - beta[pos], ids += prod[pos - 1] * gamma[pos], ++pos;
	return (pos == cnt + 1) ? 0 : (--gamma[pos], ids -= prod[pos - 1], 1);
}
inline bool add(){ // now = divisor(now)
	int pos = 1; ++id;
	while(beta[pos] == alpha[pos] && pos <= cnt) beta[pos] = 0, now /= (alpha[pos] + 1), ++pos;
	return (pos == cnt + 1) ? 0 : (++beta[pos], now += now / beta[pos], 1);
}

//int list[Mx];
//void print(){ cout << F[7] << endl; return;
//	for(int i = 0; i < sigma0; ++i) cout << list[i] << ' ' << F[i] << '\n';
//	cout << "===============\n";
//}

int Solve(){
	if(prime[1] != 2) return 2;
	prod[0] = N = 1;
	for(int i = 1; i <= cnt; ++i){
		prod[i] = prod[i - 1] * (alpha[i] + 1);
//		power[i][0] = 1;
		ksm[i] = FastPowNoMod(prime[i], alpha[i]);
//		for(int j = 1; j <= alpha[i]; ++j) power[i][j] = power[i][j - 1] * prime[i];
		N *= ksm[i];
	}
  
	sigma0 = prod[cnt];
	F[0] = 2, F[1] = -1;
	for(int i = 2; i < sigma0; ++i) F[i] = 0;
//	for(int i = 1; i <= cnt; ++i) beta[i] = 0;
//	now = 1, id = 0;
//	do list[id] = now; while(pushup());
//	print();
	for(int i = 2; i <= cnt; ++i){
		for(int j = 0; j < sigma0; ++j) G[j] = F[j];
		int idp = prod[i - 1];
		for(int j = 1; j <= cnt; ++j) gamma[j] = alpha[j] - (i == j), beta[j] = (i == j);
		ids = sigma0 - 1 - idp;
		do F[ids + idp] = (F[ids + idp] - F[ids]) % Mod; while(reduce());
//		cout << "prime " << prime[i] << " mod " << N % (prime[i] - 1) << endl;
//		print();
		if(N % (prime[i] - 1) == 0){
			getpos(prime[i] - 1);
			for(int j = 1; j <= cnt; ++j) gamma[j] = alpha[j] - beta[j];
			ids = sigma0 - 1 - id;
//			cout << "yesmod " << ids << ' ' << id << endl;
			do F[ids + id] = (F[ids + id] + G[ids]) % Mod; while(reduce());
		}
//		cout << "prime " << prime[i] << " don " << idp << endl;
//		print();
	}
	
	for(int i = 1; i <= cnt; ++i) beta[i] = 0; id = 0; now = 1;
	while(pushup()) if(N % (now + 1) != 0 && Miller_Rabin(now + 1)){
		for(int i = 1; i <= cnt; ++i) gamma[i] = alpha[i] - beta[i];
		ids = sigma0 - 1 - id;
		do F[ids + id] = (F[ids + id] + F[ids]) % Mod; while(reduce());
//		cout << "divisor " << now << endl;
//		print();
	}
//	print();
	for(int i = 1; i <= cnt; ++i) beta[i] = 0; id = 0; now = 1;
	ll ans = 0;
	do ans += 1ll * now * F[sigma0 - 1 - id]; while(add());
	ans %= Mod;
	return ans < 0 ? ans + Mod : ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
  cin >> cnt;
  for(int i = 1; i <= cnt; ++i) cin >> prime[i] >> alpha[i];
  cout << Solve() << endl;
	return 0;
}