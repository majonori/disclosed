#include <cstdio>
#include <iostream>
#define ll long long

ll FastPow(ll a, ll b){
  ll res = 1;
  while(b--) res *= a;
  return res;
}

ll Get(int a, int b){
  return 2 * ((a % b) * FastPow(b, a / b + 1) + (b - (a % b)) * FastPow(b, a / b)) - b * b;
}

ll Nex(int a, int b, int x, int y){
  if(y == a - b) return x + 1;
  return x;
}

ll Ney(int a, int b, int x, int y){
  if(y == a - b) return 0;
  return y + 1;
}

int Mex(int a, int b, int x, int y, int i, int j){
  if(j == y + b - 1) return i + 1;
  return i;
}

int Mey(int a, int b, int x, int y, int i, int j){
  if(j == y + b - 1) return y;
  return j + 1;
}

const int Mx = 25;
bool Map[Mx][Mx];
int Sum[Mx][Mx];
int Ans, n;

bool Legal(int a, int b, int x, int y){
  if(Map[x][y]) return false;
  int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
  for(int i = 0; i <= a - b; ++i){
    for(int j = 0; j <= a - b; ++j){
      if(i <= x && x < i + b && j <= y && y < j + b && Sum[i][j] == n){
        return false;
      }
    }
  }
  return true;
}

void Arouse(int a, int b, int x, int y, int k){
  for(int i = 0; i <= a - b; ++i){
    for(int j = 0; j <= a - b; ++j){
      if(i <= x && x < i + b && j <= y && y < j + b){
        Sum[i][j] += k;
      }
    }
  }
}

void Dfs(int a, int b, int x, int y);

void Inner(int a, int b, int x, int y, int i, int j, int rem){
  if(rem == 0){
    Dfs(a, b, Nex(a, b, x, y), Ney(a, b, x, y));
    return;
  }
  if(i == x + b) return;
  if(Legal(a, b, i, j)){
    Map[i][j] = 1, Arouse(a, b, i, j, 1);
    Inner(a, b, x, y, Mex(a, b, x, y, i, j), Mey(a, b, x, y, i, j), rem - 1);
    Map[i][j] = 0, Arouse(a, b, i, j, -1);
  }
  Inner(a, b, x, y, Mex(a, b, x, y, i, j), Mey(a, b, x, y, i, j), rem);
}

void Dfs(int a, int b, int x, int y){
  if(x == a - b + 1 && y == 0){ ++Ans; return;}
  Inner(a, b, x, y, x, y, n - Sum[x][y]);
}

ll Brute(int a, int b){
  Ans = 0, Dfs(a, b, 0, 0);
  return Ans;
}

ll Binom2(int a){
  return a * (a - 1) / 2;
}

ll Wisely(int a, int b){
  int B = a / b;
  return 2 * (b * FastPow(Binom2(b), B) + Binom2(b) * FastPow(b, 2 * B)) + b * b * (2 * FastPow(b, B) * FastPow(b - 1, B) - FastPow(b - 1, 2 * B)) + Binom2(b * b) - 2 * b * b *(FastPow(b - 1, B) + (b - 1) * FastPow(b, B));
} 

int main(){
  n = 2;
  for(int a = 18; a < Mx; ++a) for(int b = 1; b <= a; ++b) if(a % b == 0){
    printf("%d %d : %lld %lld\n", a, b, Brute(a, b), Wisely(a, b));
  }
  return 0;
} 

