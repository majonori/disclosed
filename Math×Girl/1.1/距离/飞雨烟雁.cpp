#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;

ll x, y;

ll GetDistY(ll yy){
  ll ka = x / yy, xa = ka * yy;
  ll kb = x / yy + 1, xb = kb * yy;
  return min(abs(xa - x), abs(xb - x)) + abs(yy - y);
}

ll GetDistK(ll k){
  ll ya = x / k, xa = k * ya;
  ll yb = x / k + 1, xb = k * yb;
  return min(abs(xa - x) + abs(ya - y), abs(xb - x) + abs(yb - y));
}

ll Solve(){
  if(x < y) swap(x, y);
  if(x % y == 0) return 0;
  ll ans = 114514 + 1919810;
  if(y <= x / y){
    ans = GetDistY(y);
    for(ll i = 1; i < ans; ++i) ans = min(ans, min(GetDistY(y + i), GetDistY(y - i)));
  }
  else{
    ans = GetDistK(x / y);
    for(ll i = x / y + 1; y - 1.0L * x / i < ans; ++i) ans = min(ans, GetDistK(i));
    for(ll i = x / y - 1; 1.0L * x / i - y < ans; --i) ans = min(ans, GetDistK(i));
  }
  return ans;
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T; cin >> T;
  while(T--){
    cin >> x >> y;
    cout << Solve() << endl;
  }
  return 0;
}
