#include <bits/stdc++.h>
#define ll long long
typedef std::pair<int, int> par;
#define fx first
#define fy second
#define mpar std::make_pair
#define pb push_back
const int N = 300233;

namespace Interval_Expand {
  int L[N], R[N], p[N], n;
  int mn[N << 2], tg[N << 2];
#define mid ((l + r) >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)
  inline void pd(int p) {
    if (tg[p]) {
      tg[ls] += tg[p];
      tg[rs] += tg[p];
      mn[ls] += tg[p];
      mn[rs] += tg[p];
      tg[p] = 0;
    }
  }
  void modify(int p, int l, int r, int ql, int qr, int v) {
    if (l == ql && r == qr) {
      mn[p] += v;
      tg[p] += v;
      return;
    }
    pd(p);
    if (qr <= mid) {
      modify(ls, l, mid, ql, qr, v);
    } else if (ql > mid) {
      modify(rs, mid + 1, r, ql, qr, v);
    } else {
      modify(ls, l, mid, ql, mid, v);
      modify(rs, mid + 1, r, mid + 1, qr, v);
    }
    mn[p] = std::min(mn[ls], mn[rs]);
  }
  int query(int p, int l, int r, int v) {
    if (l == r) {
      return l;
    }
    pd(p);
    if (mn[ls] == v) {
      return query(ls, l, mid, v);
    } else {
      return query(rs, mid + 1, r, v);
    }
  }
#undef mid
#undef ls
#undef rs
  struct Stack {
    int sta[N], top;
    std::function<bool(int, int)> cmp;
    void Insert(int x) {
      while (top && !cmp(p[x], p[sta[top]])) {
        modify(1, 1, n, sta[top - 1] + 1, sta[top], abs(p[x] - p[sta[top]]));
        top--;
      }
      sta[++top] = x;
    }
  } sta[2];
  int h[N], top;
  int G[N];
  inline void Expand_Prepare(int *t) {
    sta[0].cmp = std::less<int>();
    sta[1].cmp = std::greater<int>();
    sta[0].top = sta[1].top = 0;
    memset(mn, 0x3f, sizeof mn);
    memset(tg, 0, sizeof tg);
    for (int i = 1; i <= n; i++) {
      modify(1, 1, n, i, i, i - 0x3f3f3f3f);
      sta[0].Insert(i);
      sta[1].Insert(i);
      G[i] = query(1, 1, n, i);
    }
    top = 0;
    for (int i = n; i; i--) {
      while (top && G[h[top]] >= G[i]) top--;
      h[++top] = i;
      while (top && G[h[top]] >= i) top--;
      t[i] = h[top];
    }
  }
  int stl[21][N], str[21][N];
  par mnp[21][N], mxp[21][N];
  inline void Prepare(int *_p, int _n) {
    n = _n;
    for (int i = 1; i <= n; i++) {
      p[i] = _p[i];
    }
    Expand_Prepare(R);
    std::reverse(p + 1, p + 1 + n);
    Expand_Prepare(L);
    std::reverse(p + 1, p + 1 + n);
    std::reverse(L + 1, L + 1 + n);
    std::for_each(L + 1, L + 1 + n, [&](int &x){x = n + 1 - x;});
    for (int i = 1; i <= n; i++) {
      stl[0][i] = L[i];
      str[0][i] = R[i];
      mnp[0][i] = mpar(p[i], i);
      mxp[0][i] = mpar(p[i], i);
    }
    for (int k = 1; k <= 20; k++) {
      for (int i = 1; i + (1 << k) - 1 <= n; i++) {
        stl[k][i] = std::min(stl[k - 1][i], stl[k - 1][i + (1 << (k - 1))]);
        str[k][i] = std::max(str[k - 1][i], str[k - 1][i + (1 << (k - 1))]);
        mnp[k][i] = std::min(mnp[k - 1][i], mnp[k - 1][i + (1 << (k - 1))]);
        mxp[k][i] = std::max(mxp[k - 1][i], mxp[k - 1][i + (1 << (k - 1))]);
      }
    }
  }
  inline par Expand(int l, int r) {
    if (l == r) return mpar(l, r);
    int k = 31 - __builtin_clz(r - l);
    int x = std::min(stl[k][l], stl[k][r - (1 << k)]);
    int y = std::max(str[k][l + 1], str[k][r - (1 << k) + 1]);
    return mpar(x, y);
  }
  inline par Min_Max(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    int x = std::min(mnp[k][l], mnp[k][r - (1 << k) + 1]).fy;
    int y = std::max(mxp[k][l], mxp[k][r - (1 << k) + 1]).fy;
    return mpar(x, y);
  }
}
using Interval_Expand::Prepare;
using Interval_Expand::Expand;
using Interval_Expand::Min_Max;

const int mod = 1000000007;

namespace Interval_Tree {
  int n, cnt, fa[N << 1];
  std::vector<int> G[N << 1];
  int type[N << 1];
  par interval[N << 1];
  int Solve(int l, int r) {
    if (l == r) {
      interval[l] = mpar(l, r);
      return l;
    }
    int p = ++cnt;
    interval[p] = mpar(l, r);
    par M = Min_Max(l, r);
    par t = Expand(l, std::min(M.fx, M.fy));
    if (t.fx == l && t.fy == r) {
      type[cnt] = 2;
      int cur = l;
      while (cur <= r) {
        int nl = cur, nr, sl = cur, sr = r - (cur == l);
        while (sl < sr) {
          int mid = (sl + sr + 1) >> 1;
          par q = Expand(cur, mid);
          if (q.fx < cur || q.fy > sr) {
            sr = mid - 1;
          } else {
            sl = q.fy;
          }
        }
        nr = sl;
        int son = Solve(nl, nr);
        G[p].pb(son);
        fa[son] = p;
        cur = nr + 1;
      }
    } else {
      type[cnt] = 1;
      int cur = l;
      while (cur <= r) {
        int s = M.fx < M.fy ? Min_Max(cur, r).fx : Min_Max(cur, r).fy;
        par q = Expand(cur, s);
        int son = Solve(q.fx, q.fy);
        G[p].pb(son);
        fa[son] = p;
        cur = q.fy + 1;
      }
    }
    return p;
  }
  ll ans = 0;
  void dfs(int x) {
    ans++;
    if (G[x].empty()) return;
    for (auto y : G[x]) {
      dfs(y);
    }
    if (type[x] == 1) {
      ans += (ll) (G[x].size() - 1) * G[x].size() / 2 - 1;
    }
  }
  inline ll Main(int _n) {
    n = _n;
    cnt = n;
    Solve(1, n);
    dfs(n + 1);
    return ans;
  }
}

int n, p[N];
int main() {
  scanf("%d", &n);
  for (int i = 1, x, y; i <= n; i++) {
    scanf("%d%d", &x, &y);
    p[x] = y;
  }
  Prepare(p, n);
  printf("%lld\n", Interval_Tree::Main(n));
  return 0;
}

