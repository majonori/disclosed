#include<bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long 
#define vi vector < int > 
#define sz(a) ((int) (a).size())
#define ll long long 
#define ull unsigned long long
#define me(a, x) memset(a, x, sizeof(a)) 
using namespace std;
const int mod = 998244353, _G = 3, N = 1 << 21, inv2 = (mod + 1) / 2;
#define add(a, b) (a + b >= mod ? a + b - mod : a + b)
#define dec(a, b) (a < b ? a - b + mod : a - b)
int qpow(int x, int y = mod - 2) {
  int res = 1;
  for(; y; x = (ll) x * x % mod, y >>= 1) if(y & 1) res = (ll) res * x % mod;
  return res;
}
int rt[N * 2 + 3], Lim;
void Pinit(int x) {
  for(Lim = 1; Lim <= x; Lim <<= 1) ;
  for(int i = 1; i < Lim; i <<= 1) {
    int sG = qpow (_G, (mod - 1) / (i << 1));
    rt[i] = 1;
    L(j, i + 1, i * 2 - 1) rt[j] = (ll) rt[j - 1] * sG % mod;
  }
}
struct poly {
  vector<int> a;
  int size() { return sz(a); }
  int & operator [] (int x) { return a[x]; }
  int v(int x) { return x < 0 || x >= sz(a) ? 0 : a[x]; }
  void clear() { vector<int> ().swap(a); }
  void rs(int x = 0) { a.resize(x); }
  poly (int n = 0) { rs(n); }
  poly (vector<int> o) { a = o; }
  poly (const poly &o) { a = o.a; }
  poly Rs(int x = 0) { vi res = a; res.resize(x); return res; }
  inline void dif() {
    int n = sz(a);
    for (int l = n >> 1; l >= 1; l >>= 1) 
      for(int j = 0; j < n; j += l << 1) 
        for(int k = 0, *w = rt + l; k < l; k++, w++) {
          int x = a[j + k], y = a[j + k + l];
          a[j + k] = add(x, y);
          a[j + k + l] = (ll) * w * dec(x, y) % mod;
        }
  }
  void dit () {
    int n = sz(a);
    for(int i = 2; i <= n; i <<= 1) 
      for(int j = 0, l = (i >> 1); j < n; j += i) 
        for(int k = 0, *w = rt + l; k < l; k++, w++) {
          int pa = a[j + k], pb = (ll) a[j + k + l] * *w % mod;
          a[j + k] = add(pa, pb), a[j + k + l] = dec(pa, pb);
        }
    reverse(a.begin() + 1, a.end());
    for(int i = 0, iv = qpow(n); i < n; i++) a[i] = (ll) a[i] * iv % mod;
  } 
  friend poly operator * (poly aa, poly bb) {
    if(!sz(aa) || !sz(bb)) return {};
    int lim, all = sz(aa) + sz(bb) - 1;
    for(lim = 1; lim < all; lim <<= 1);
    aa.rs(lim), bb.rs(lim), aa.dif(), bb.dif();
    L(i, 0, lim - 1) aa[i] = (ll) aa[i] * bb[i] % mod;
    aa.dit(), aa.a.resize(all);
    return aa;
  }
  poly Inv() {
    poly res, f, g;
    res.rs(1), res[0] = qpow(a[0]);
    for(int m = 1, pn; m < sz(a); m <<= 1) {
      pn = m << 1, f = res, g.rs(pn), f.rs(pn);
      for(int i = 0; i < pn; i++) g[i] = (*this).v(i);
      f.dif(), g.dif();
      for(int i = 0; i < pn; i++) g[i] = (ll) f[i] * g[i] % mod;
      g.dit();
      for(int i = 0; i < m; i++) g[i] = 0;
      g.dif();
      for(int i = 0; i < pn; i++) g[i] = (ll) f[i] * g[i] % mod;
      g.dit(), res.rs(pn);
      for(int i = m; i < min(pn, sz(a)); i++) res[i] = (mod - g[i]) % mod;
    } 
    return res.rs(sz(a)), res;
  }
  poly Shift (int x) {
    poly zm (sz(a) + x);
    L(i, max(-x, 0), sz(a) - 1) zm[i + x] = a[i];
    return zm; 
  }
  friend poly operator * (poly aa, int bb) {
    poly res(sz(aa));
    L(i, 0, sz(aa) - 1) res[i] = (ll) aa[i] * bb % mod;
    return res;
  }
  friend poly operator + (poly aa, poly bb) {
    vector<int> res(max(sz(aa), sz(bb)));
    L(i, 0, sz(res) - 1) res[i] = add(aa.v(i), bb.v(i));
    return poly(res);
  }
  friend poly operator - (poly aa, poly bb) {
    vector<int> res(max(sz(aa), sz(bb)));
    L(i, 0, sz(res) - 1) res[i] = dec(aa.v(i), bb.v(i));
    return poly(res);
  }
  poly & operator += (poly o) {
    rs(max(sz(a), sz(o)));
    L(i, 0, sz(a) - 1) (a[i] += o.v(i)) %= mod;
    return (*this);
  }
  poly & operator -= (poly o) {
    rs(max(sz(a), sz(o)));
    L(i, 0, sz(a) - 1) (a[i] += mod - o.v(i)) %= mod;
    return (*this);
  }
  poly & operator *= (poly o) {
    return (*this) = (*this) * o;
  }
} ;

ll n, sq;
bool Prime[N];
int p[N], ptot;
mt19937_64 orz;
void xxs(int x) {
  L(i, 2, x) {
    if(!Prime[i]) p[++ptot] = i;
    for(int j = 1; p[j] * i <= x && j <= ptot; ++j) {
      Prime[p[j] * i] = true;
      if(i % p[j] == 0) break;
    } 
  }
}
ll w[N], id1[N], id2[N], tp;
inline int getid(ll x) {
  return x <= sq ? id1[x] : id2[n / x];
}
double iv[N];

double lg[N];
vi Mul(vi A, vi B) {
  L(i, 1, sz(A) - 2) (A[i] += mod - A[i + 1]) %= mod;
  L(i, 1, sz(B) - 2) (B[i] += mod - B[i + 1]) %= mod;
  vi ans(tp + 1);
  vi av(sq + 1), bv(sq + 1);
  
  int bp = id1[sq] - 1;
  vi as(sq + 1), bs(sq + 1), cs(sq + 3);
  vi ma(sq + 3), mb(sq + 3), mc(sq + 3);
  L(i, 1, sq) 
  ma[i] = A[getid(i)], mb[i] = B[getid(i)];
  L(i, 1, bp) 
  as[i] = A[getid(n / i)], bs[i] = B[getid(n / i)];
  
  L(i, 1, sq) {
    L(j, 1, sq / i) {
      (mc[i * j] += (ll) ma[i] * mb[j] % mod) %= mod;
    }
  }
  
  vi asuf(bp + 2), bsuf(bp + 2);
  L(i, 1, bp) {
    asuf[i] = as[i];
    bsuf[i] = bs[i];
  }
  R(i, bp, 1) (asuf[i] += asuf[i + 1]) %= mod;
  R(i, bp, 1) (bsuf[i] += bsuf[i + 1]) %= mod;
  
  L(i, 1, sq) {
    L(j, 1, bp / i) {
      (cs[j] += (ll) mb[i] * (asuf[i * j] + mod - asuf[min(bp + 1, i * (j + 1))]) % mod) %= mod;
    }
    L(j, 1, bp / i) {
      (cs[j] += (ll) ma[i] * (bsuf[i * j] + mod - bsuf[min(bp + 1, i * (j + 1))]) % mod) %= mod;
    }
//		L(j, i, bp) 
//			(cs[j / i] += (ll) as[j] * mb[i] % mod) %= mod;
//		L(j, i, bp) 
//			(cs[j / i] += (ll) bs[j] * ma[i] % mod) %= mod;
  }
  
  vector < double > LG(tp + 3), slg(tp + 3);
  L(i, 1, sq) {
    LG[i] = log(i);
  }
  double lgn = log(n);
  L(i, 1, bp) {
    slg[i] = lgn - LG[i];
  }
  ll kanz = sq * 0.8;
  kanz = max(kanz, 1LL);
  
  vi BL(tp + 1);
  L(i, 1, sq) {
    BL[i] = ceil(LG[i] * kanz + 1e-10);
  }
  L(i, 1, bp) {
    slg[i] *= kanz;
  }
  
  ll WA = 0;
  int BOUND = BL[sq] * 2;
  vi pointer(BOUND + 1);
  int P = 1;
  R(i, BOUND, 0) {
    while(P <= bp && i < slg[P]) ++P; 
    pointer[i] = P - 1;
  }
  
  vi spin(BOUND + 1);
  cerr << "BOUND = " << 1. * BOUND << endl;
  
  poly MA(BL[sq] + 1), MB(BL[sq] + 1);
  L(i, 1, sq) 
  (MA[BL[i]] += ma[i]) %= mod, 
  (MB[BL[i]] += mb[i]) %= mod;
  MA *= MB;
  L(i, 1, BOUND) 
  spin[i] = MA[i];
  
  L(i, 1, sq) 
  L(j, 1, sq / i) 
  (spin[BL[i] + BL[j]] += mod - (ll) ma[i] * mb[j] % mod) %= mod;
  
  ll TL = n, TR = n;
  for(; TL && (log(n) - log(TL)) * kanz <= 2; --TL) ;
  TL -= 5, TL = max(TL, 1LL);
  
  ll lens = TR - TL + 1;
  vector < ll > val(lens + 1);
  vector < vector < pair < ll, int > > > FAC(lens + 1);
  L(i, 1, lens) val[i] = i + TL - 1;
  L(u, 1, ptot) {
    ll p = ::p[u];
    if(p > sq) continue; 
    ll ii = (p - TL % p) % p + 1;
    for(ll j = ii; j <= lens; j += p) {
      int nt = 0;
      while(val[j] % p == 0) {
        val[j] /= p, ++nt;
      }
      FAC[j].emplace_back(p, nt); 
    }
  }
  
  vector < pair < ll, int > > curs; 
  
  ll MULS = 0;
  auto check = [&] (int i, int j) {
    int p = pointer[BL[i] + BL[j]];
    ll ML = (ll) i * j * (p + 1);
    if((ll)i * j > sq && ML == MULS) {
      (spin[BL[i] + BL[j]] += mod - (ll) ma[i] * mb[j] % mod) %= mod;
      while((ll)i * j * (p + 1) <= n) ++p, ++WA;
      (cs[p] += (ll) ma[i] * mb[j] % mod) %= mod;
    }
    return ;
  } ;
  
  auto Dfs = [&] (auto self, int x, int i, int j) -> void {
    if(x == sz(curs)) {
      check(i, j);
      return ;
    }
    ll v = curs[x].first;
    int cnt = curs[x].second;
    L(t1, 0, cnt) {
      L(t2, 0, cnt - t1) {
        ll ni = i, nj = j;
        L(o, 1, t1) ni *= v;
        L(o, 1, t2) nj *= v;
        if(ni <= sq && nj <= sq) 
          self(self, x + 1, ni, nj);
      }
    } 
  };
  
  L(i, 1, lens) 
  MULS = TL + i - 1, curs = FAC[i], Dfs(Dfs, 0, 1, 1);
  
  L(i, 1, BOUND) {
    (cs[pointer[i]] += spin[i]) %= mod;
  }
  
  cerr << "WA = " << WA << ' ' << BOUND << endl;
//	L(i, 1, sq) {
//		L(j, sq / i + 1, sq) {
//			(cs[n / i / j] += (ll) ma[i] * mb[j] % mod) %= mod;
//		}
//	}
  
  L(i, 1, bp) if(cs[i]) (ans[getid(n / i)] += cs[i]) %= mod;
  L(i, 1, sq) if(mc[i]) (ans[getid(i)] += mc[i]) %= mod;
  
  R(i, tp - 1, 1) (ans[i] += ans[i + 1]) %= mod;
  return ans;
}
int f1[N], f2[N], trans[N];
int main() {
  ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0); 
//	cin >> n;
  n = 1e10;
  Pinit(1 << 21);
  sq = sqrt(n);
  xxs(sq + 5);
  for(ll l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    w[++tp] = n / l;
    if(w[tp] <= sq) id1[w[tp]] = tp;
    else id2[n / w[tp]] = tp;
  }
  L(i, 1, tp) f1[i] = orz() % mod, f2[i] = orz() % mod; 
  L(i, 1, tp) {
    ll W = w[i];
    for(ll l = 1, r; l <= W; l = r + 1) 
      r = W / (W / l), 
      (trans[i] += (ll) (f1[getid(r)] - f1[getid(l - 1)] + mod) * f2[getid(W / l)] % mod) %= mod;
  }
  double clock1 = clock();
  cout << "solver1 : " << clock1 << endl;
  vi A(tp + 1), B(tp + 1);
  L(i, 1, tp) A[i] = f1[i], B[i] = f2[i];
  auto C = Mul(A, B);
  L(i, 1, tp) 
  if(trans[i] != C[i]) {
    cout << "wa" << endl;
  }
  double clock2 = clock();
  cout << "solver2 : " << clock2 - clock1 << endl;
  return 0;
}
