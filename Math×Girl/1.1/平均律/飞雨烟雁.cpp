#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
#define lll __int128
using namespace std;

const int Mx = 1e7 + 5, Mod = 998244353;
int n;
ll a, b;

int inv_mod(ll a){ // a < Mod
  int res = 1, b = Mod - 2;
  while(b){
    if(b & 1) res = res * a % Mod;
    a = a * a % Mod, b >>= 1;
  }
  return res;
}

bool coprime[Mx], vis[Mx];
int prime[Mx], tot;
int inv[Mx], invp[Mx];

void sieve(){
  tot = 0, inv[1] = coprime[1] = 1;
  for(int i = 2; i < n; ++i){
    if(!vis[i]) prime[++tot] = i, coprime[i] = (n % i > 0);
    for(int j = 1; j <= tot && prime[j] * i < n; ++j){
      vis[i * prime[j]] = true;
      coprime[i * prime[j]] = coprime[i] & coprime[prime[j]];
      if(i % prime[j] == 0) break;
    }
  }
  for(int i = 2; i < n; ++i){
    if(coprime[i]) inv[i] = 1ll * inv[i - 1] * i % n;
    else inv[i] = inv[i - 1];
  }
  int back = 1, temp = inv[n - 1];
  for(int i = n - 1; i > 1; --i) if(coprime[i]){
    inv[i] = 1ll * inv[i - 1] * back % n;
    back = 1ll * back * i % n;
  }
  if(temp == n - 1) for(int i = 2; i < n; ++i) inv[i] = n - inv[i];
}

int solve(){
  int delta = a % Mod * inv_mod(b % Mod) % Mod;
  if(n == 1) return 2 * a < b ? 2 * delta % Mod : 1;
  sieve();
  invp[1] = 1;
  for(int i = 2; i <= n; i++) invp[i] = -invp[Mod % i] * (ll)(Mod / i) % Mod;
  ll Ans = 0;
  for(int d = 1; d < n; ++d) if(coprime[d]){
    int y = inv[d], w = n - inv[d];
    int x = 1ll * d * y / n, z = (1 + 1ll * d * w) / n;
    if((lll)b * z * y <= (lll)2 * a * w * y + (lll)b * w * x) continue;
    if(b / 2 / a / n >= y) Ans -= 1ll * d * invp[n] % Mod - delta;
    else Ans -= 1ll * x * invp[y] % Mod + delta;
    if(b / 2 / a / n >= w) Ans += 1ll * d * invp[n] % Mod + delta;
    else Ans += 1ll * z * invp[w] % Mod - delta;
  }
  Ans %= Mod;
  return Ans < 0 ? Ans + Mod : Ans;
}

int main(){
  int T;
  scanf("%d", &T);
  while(T--){
    scanf("%d%lld%lld", &n, &a, &b);
    printf("%d\n", solve());
  }
  return 0;
}
