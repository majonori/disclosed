#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;

int Read() {
  int res = 0;
  char c = getchar();
  while(c < '0' || c > '9') c = getchar();
  while(c >= '0' && c <= '9') res = res * 10 + (c ^ 48), c = getchar();
  return res;
}

const int Mx = 2e6 + 5, Mod = 998244353;

inline int FastPow(ll a, int b) {
  int res = 1;
  while(b) {
    if(b & 1) res = res * a % Mod;
    b >>= 1, a = a * a % Mod;
  }
  return res;
}
ll Inverse(ll x) {
  return FastPow(x % Mod, Mod - 2);
}

void Print(const int *F, int n) {
  for(int i = 1; i <= n; ++i) printf("%d ", F[i] < 0 ? F[i] + Mod : F[i]);
  puts("");
}

bool Vis[Mx];
int Prime[Mx], tot;
int Lns[Mx];
int Inv[30];
void Sieve() {
  for(int i = 2; i < Mx; ++i) {
    if(!Vis[i]) Prime[++tot] = i, Lns[i] = 1;
    for(int j = 1; j <= tot && Prime[j] * i < Mx; ++j) {
      Vis[i * Prime[j]] = true;
      Lns[i * Prime[j]] = 1 + Lns[i];
      if(i % Prime[j] == 0) break;
    }
  }
  for(int i = 1; i < 30; ++i) Inv[i] = Inverse(i);
}

int Temp[Mx], Temp2[Mx], Temp3[Mx], Temp4[Mx];
void Mul(const int *F, const int *G, int *H, int n) {
  for(int i = 1; i <= n; ++i) Temp[i] = 0;
  for(int i = 1; i <= n; ++i) for(int j = i; j <= n; j += i)
      Temp[j] = (Temp[j] + 1ll * F[i] * G[j / i]) % Mod;
  for(int i = 1; i <= n; ++i) H[i] = Temp[i];
}

void Div(const int *F, const int *G, int *H, int n) {
  for(int i = 1; i <= n; ++i) Temp[i] = F[i];
  ll Invg = Inverse(G[1]);
  for(int i = 1; i <= n; ++i) {
    H[i] = Temp[i] = Temp[i] * Invg % Mod;
    for(int j = (i << 1); j <= n; j += i) Temp[j] = (Temp[j] - 1ll * Temp[i] * G[j / i]) % Mod;
  }
}

void Derivate(const int *F, int *G, int n) {
  for(int i = 1; i <= n; ++i) G[i] = 1ll * F[i] * Lns[i] % Mod;
}
void Integrate(const int *F, int *G, int n) {
  for(int i = 1; i <= n; ++i) G[i] = 1ll * F[i] * Inv[Lns[i]] % Mod;
}

void Logarithm(const int *F, int *G, int n) {
  Derivate(F, Temp2, n), Div(Temp2, F, Temp3, n), Integrate(Temp3, G, n);
}

void Exponent(const int *F, int *G, int n) {
  Derivate(F, Temp2, n);
  for(int i = 2; i <= n; i++) Temp3[i] = 0;
  Temp3[1] = 1;
  for(int i = 1; i <= n; i++) {
    if(i != 1) Temp3[i] = 1ll * Temp3[i] * Inv[Lns[i]] % Mod;
    for(int j = (i << 1); j <= n; j += i) Temp3[j] = (Temp3[j] + 1ll * Temp3[i] * Temp2[j / i]) % Mod;
  }
  for(int i = 1; i <= n; ++i) G[i] = Temp3[i];
}

void Pow(const int *F, int *G, int n, int k) {
  Logarithm(F, Temp4, n);
  for(int i = 1; i <= n; ++i) Temp4[i] = 1ll * Temp4[i] * k % Mod;
  Exponent(Temp4, G, n);
}

int NT[Mx];
int NT1[Mx], NT2[Mx];
void Newton_Iteration(int n) {
  ll m = 2;
  NT[1] = 1;
  do {
    Mul(NT, NT, NT1, n);
    for(int i = 1; i <= n; ++i) {
      NT1[i] = 1 - NT1[i];
      NT2[i] = -2 * NT[i] % Mod;
    }
    ++NT1[1], NT2[1] += 3;
    Div(NT1, NT2, NT, n);
  } while((m = m * m) <= n);
}

int F[Mx];
int main() {

  Sieve();

  int n = 2e6;
  Newton_Iteration(n);
  Mul(NT, NT, F, n);
  for(int i = 1; i <= n; ++i)
    if(((i == 1) + 1 - 3ll * NT[i] + F[i]) % Mod != 0) puts("!");

  return 0;
}
