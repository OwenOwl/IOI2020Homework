#include <bits/stdc++.h>
using namespace std;

const int N = 50022;
int n, m, q, MOD, eu[N], ev[N], ec[N], is4[1000233];
int fa[N * 6];
inline int F(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}
inline void merge(int x, int y) {fa[F(x)] = y;}
inline bool ask(int x, int y) {return F(x) == F(y);}
inline int P(int s, int p, int q) {return s * 6 + p * 3 + q;}

int main() {
  scanf("%d%d%d%d", &n, &m, &q, &MOD);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &eu[i], &ev[i], &ec[i]);
  }
  int g = MOD;
  for (int i = 2; i <= m; i++) {
    g = __gcd(g, abs(ec[i] - ec[1]));
  }
  MOD = MOD / g % 3 ? g : g * 3;
  int z = ec[1] % g;
  for (int i = 1; i <= n * 6 + 6; i++) fa[i] = i;
  for (int i = 1; i <= m; i++) {
    ec[i] = (ec[i] - z) / g % 3;
    for (int p = 0; p < 2; p++) {
      for (int q = 0; q < 3; q++) {
        merge(P(eu[i], p, q), P(ev[i], !p, (2 * q + ec[i]) % 3));
        merge(P(ev[i], p, q), P(eu[i], !p, (2 * q + ec[i]) % 3));
      }
    }
  }
  for (int i = 1, x = z; i <= MOD; i++, x = (x << 2) % MOD) {
    is4[x] = 1;
  }
  while (q--) {
    int s, t, r, ok = 0;
    scanf("%d%d%d", &s, &t, &r);
    for (int p = 0; p < 2; p++) {
      for (int q = 0; q < 3; q++) if (ask(P(t, 0, 0), P(s, p, q))) {
        int x = ((r + z - q * g) % MOD + MOD) % MOD;
        if (p) x = (x << 1) % MOD;
        if (is4[x]) ok = 1;
      }
    }
    puts(ok ? "YES" : "NO");
  }
}
