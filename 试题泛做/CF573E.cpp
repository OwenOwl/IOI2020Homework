#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233;

unsigned rnk[N];
int n, ch[N][2], size[N];
ll val[N], tag[N];

void pd(int x) {
  if (ch[x][0]) val[ch[x][0]] += tag[x], tag[ch[x][0]] += tag[x];
  if (ch[x][1]) val[ch[x][1]] += tag[x], tag[ch[x][1]] += tag[x];
  tag[x] = 0;
}
void ud(int x) {
  size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

int merge(int x, int y) {
  if (!x || !y) return x | y;
  pd(x), pd(y);
  if (rnk[x] < rnk[y]) {
    ch[x][1] = merge(ch[x][1], y);
    ud(x);
    return x;
  } else {
    ch[y][0] = merge(x, ch[y][0]);
    ud(y);
    return y;
  }
}
pair<int, int> split(int x, ll a, int sz) {
  if (!x) return make_pair(0, 0);
  pd(x);
  int j = sz + size[ch[x][0]] + 1;
  if (j * a >= val[x]) {
    auto y = split(ch[x][0], a, sz);
    ch[x][0] = y.second;
    ud(x);
    return make_pair(y.first, x);
  } else {
    auto y = split(ch[x][1], a, sz + size[ch[x][0]] + 1);
    ch[x][1] = y.first;
    ud(x);
    return make_pair(x, y.second);
  }
}
ll ans = 0;
void pdd(int x) {
  pd(x);
  if (val[x] > 0) ans += val[x];
  if (ch[x][0]) pdd(ch[x][0]);
  if (ch[x][1]) pdd(ch[x][1]);
}

int main() {
  scanf("%d", &n);
  mt19937 rng(233);
  int rt = 0;
  for (int i = 1; i <= n; i++) {
    ll x;
    scanf("%lld", &x);
    auto t = split(rt, x, 0);
    rnk[i] = rng();
    ch[i][0] = ch[i][1] = 0;
    size[i] = 1;
    val[i] = (size[t.first] + 1) * x;
    if (t.second) {
      tag[t.second] += x;
      val[t.second] += x;
    }
    rt = merge(merge(t.first, i), t.second);
  }
  pdd(rt);
  printf("%lld\n", ans);
}
