#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std; 

ll Read(){
  ll res = 0; char c = getchar();
  while(c < '0' || c > '9') c = getchar();
  while(c >= '0' && c <= '9') res = res * 10 + c - 48, c = getchar();
  return res;
}

const int Mod = 998244353, Nod = Mod - 1;

ll a, b, B, T; // < 10 ^ 9
// B = a // b, T = a mod b

ll FastPow(ll x, int y = B){ // return x^y		x < Mod
  if(!x) return 0;
  int res = 1;
  while(y){
    if(y & 1) res = res * x % Mod;
    y >>= 1, x = x * x % Mod;
  }
  return res;
}

ll Easy(){
  ll ans = (2 * (b * T + b - T) % Mod * FastPow(b) - b * b) % Mod;
  return ans < 0 ? ans + Mod : ans;
}

ll Binom(ll x){ return (x * (x - 1) / 2) % Mod;} // x < Mod
ll Hard(){
  ll bbp = FastPow(Binom(b)); // binom(b) ^ B
  ll bbp1 = bbp * Binom(b) % Mod; // binom(b) ^ (B + 1)
  ll bp = FastPow(b); // b ^ B
  ll bp1 = bp * b % Mod; // b ^ (B + 1)
  ll bps = bp * bp % Mod; // b ^ 2B
  ll bps1 = bp * bp1 % Mod; // b ^ (2B + 1)
  ll bps2 = bp1 * bp1 % Mod; // b ^ (2B + 2)
  ll ans1 = (T * bbp1 % Mod + (b - T) * bbp + Binom(T) * bps2 + T * (b - T) % Mod * bps1 + Binom(b - T) * bps) % Mod;
  ll c = b - 1;
  ll cp = FastPow(c); // (b - 1) ^ B
  ll cp1 = cp * c % Mod; // (b - 1) ^ (B + 1)
  ll cps = cp * cp % Mod; // (b - 1) ^ 2B
  ll cps1 = cp * cp1 % Mod; // (b - 1) ^ (2B + 1)
  ll cps2 = cp1 * cp1 % Mod; // (b - 1) ^ (2B + 2)
  ll bsm = Binom(b * b % Mod); // binom(b ^ 2)
  ll ans2 = (T * T % Mod * ((2 * bp1 * cp1 - cps2) % Mod) + 2 * T * (b - T) % Mod * ((bp * cp1 + bp1 * cp - cps1) % Mod) + (b - T) * (b - T) % Mod * ((2 * bp * cp - cps) % Mod) - bsm) % Mod;
  ll ans3 = (((c * bp1 + cp1) % Mod * T + (c * bp + cp) % Mod * (b - T)) % Mod * b - bsm) % Mod;
  ll ans = (2 * ans1 + ans2 - 2 * ans3) % Mod;
  return ans < 0 ? ans + Mod : ans;
}

int main(){
  int tt = Read();
  while(tt--){
    a = Read(), b = Read();
    B = (a / b) % Nod, T = (a % b) % Mod;
    a %= Mod, b %= Mod;
    int op = Read();
    if(op == 1) printf("%lld\n", Easy());
    else printf("%lld\n", Hard());
  }
  return 0;
}
