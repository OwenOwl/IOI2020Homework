#include <bits/stdc++.h>
using namespace std;

long long ans = 0;
const int inf = 114514;

inline void solve(vector<string> a) {
  int n = (int) a.size(), m = (int) a[0].size();
  if (n < m) {
    vector<string> b(m, string(n, ' '));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        b[j][i] = a[i][j];
      }
    }
    a = b;
    swap(n, m);
  }
  if (m == 1) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      if (a[i][0] != '#') {
        ans += sum * (a[i][0] - '0');
        sum += a[i][0] - '0';
      } else {
        sum = 0;
      }
    }
    return;
  }

  // Divide & Conquer
  vector<string> U = vector<string> (a.begin(), a.begin() + (n >> 1));
  vector<string> D = vector<string> (a.begin() + (n >> 1), a.end());
  solve(U);
  solve(D);
  U.push_back(D[0]);
  int HU = n >> 1, HD = n - HU;

  // Calculate Left, Right in D
  vector<vector<int>> lef(HD, vector<int>(m, inf)), rit(HD, vector<int>(m, -inf));
  for (int j = 0; j < m; j++) if (D[0][j] != '#') {
    lef[0][j] = rit[0][j] = j;
  }
  for (int i = 0; i < HD; i++) {
    for (int j = 0; j < m; j++) if (D[i][j] != '#') {
      if (i) lef[i][j] = min(lef[i][j], lef[i - 1][j]);
      if (i) rit[i][j] = max(rit[i][j], rit[i - 1][j]);
      if (j) lef[i][j] = min(lef[i][j], lef[i][j - 1]);
      if (j) rit[i][j] = max(rit[i][j], rit[i][j - 1]);
    }
  }

  // Calculate Top in U, and Bottom in D
  vector<vector<int>> upper(HU + 1, vector<int>(m, inf));
  vector<vector<int>> lower(HD, vector<int>(m, -inf));
  vector<int> top(m, inf), bot(m, -inf);
  for (int i = 0; i <= HU; i++) {
    for (int j = 0; j < m; j++) if (U[i][j] != '#') {
      upper[i][j] = i;
      if (i) upper[i][j] = min(upper[i][j], upper[i - 1][j]);
      if (j) upper[i][j] = min(upper[i][j], upper[i][j - 1]);
    }
  }
  for (int i = HD - 1; ~i; i--) {
    for (int j = m - 1; ~j; j--) if (D[i][j] != '#') {
      lower[i][j] = i;
      if (i < HD - 1) lower[i][j] = max(lower[i][j], lower[i + 1][j]);
      if (j < m  - 1) lower[i][j] = max(lower[i][j], lower[i][j + 1]);
    }
  }
  for (int j = 0; j < m; j++) {
    top[j] = upper[HU][j];
    bot[j] = lower[0][j];
  }

  // Calculate MeetPoint in D
  vector<vector<int>> met(m, vector<int>(m, inf));
  for (int i = 0; i < HD; i++) {
    for (int j = 0; j < m; j++) {
      if (lef[i][j] <= rit[i][j]) {
        met[lef[i][j]][rit[i][j]] = min(met[lef[i][j]][rit[i][j]], i);
      }
    }
  }
  for (int l = 0; l < m; l++) {
    for (int r = m - 1; ~r; --r) {
      if (l        ) met[l][r] = min(met[l][r], met[l - 1][r]);
      if (r < m - 1) met[l][r] = min(met[l][r], met[l][r + 1]);
    }
  }
  for (int l = 0; l < m; l++) {
    for (int r = 0; r < m; r++) {
      met[l][r] = met[l][r] <= bot[l] && met[l][r] <= bot[r] ? met[l][r] : inf;
    }
  }

  // Inclusion-Exclusion of BothReachable in D
  vector<int> SLR(HD, 0);
  vector<vector<int>> SAL(HD, vector<int>(m, 0)), SRB(HD, vector<int>(m, 0));
  vector<vector<int>> SAB(m, vector<int>(m, 0));
  for (int i = 0; i < HD; i++) {
    if (i) SLR[i] = SLR[i - 1];
    for (int j = 0; j < m; j++) if (lef[i][j] <= rit[i][j]) {
      SLR[i] += D[i][j] - '0';
    }
  }
  for (int i = 0; i < HD; i++) {
    for (int j = 0; j < m; j++) if (i) {
      SAL[i][j] = SAL[i - 1][j];
      SRB[i][j] = SRB[i - 1][j];
    }
    for (int j = 0; j < m; j++) if (lef[i][j] <= rit[i][j]) {
      if (lef[i][j]        ) SAL[i][lef[i][j] - 1] += D[i][j] - '0';
      if (rit[i][j] < m - 1) SRB[i][rit[i][j] + 1] += D[i][j] - '0';
    }
  }
  for (int i = 0; i < HD; i++) {
    for (int j = m - 2; ~j; j--) {
      SAL[i][j] += SAL[i][j + 1];
    }
    for (int j = 1; j < m; j++) {
      SRB[i][j] += SRB[i][j - 1];
    }
  }
  for (int i = 0; i < HD; i++) {
    for (int j = 0; j < m; j++) if (lef[i][j] <= rit[i][j]) {
      if (lef[i][j] && rit[i][j] < m - 1) SAB[lef[i][j] - 1][rit[i][j] + 1] += D[i][j] - '0';
    }
  }
  for (int l = m - 1; ~l; l--) {
    for (int r = l; r < m; r++) {
      if (l < m - 1) SAB[l][r] += SAB[l + 1][r];
      if (r        ) SAB[l][r] += SAB[l][r - 1];
      if (l < m - 1 && r) SAB[l][r] -= SAB[l + 1][r - 1];
    }
  }

  // Implement BothReachable in D
  auto both = [&](int a, int b, int l) {
    return met[a][b] > l ? 0 : SLR[l] - SAL[l][a] - SRB[l][b] + SAB[a][b];
  };

  // Calculate Reachable int D
  vector<int> reach(m, 0);
  for (int i = 0; i < m; i++) {
    reach[i] = both(i, i, bot[i]);
  }

  // Calculate Min, Max in U
  vector<vector<int>> mn(HU + 1, vector<int>(m, inf)), mx(HU + 1, vector<int>(m, -inf));
  for (int i = m - 1; ~i; i--) if (U[HU][i] != '#') {
    mn[HU][i] = i;
    mx[HU][i] = max(i, i + 1 < m ? mx[HU][i + 1] : -inf);
  }
  for (int i = HU - 1; ~i; i--) {
    for (int j = m - 1; ~j; j--) if (U[i][j] != '#') {
      mn[i][j] = mn[i + 1][j];
      mx[i][j] = mx[i + 1][j];
      if (j < m - 1) mn[i][j] = min(mn[i][j], mn[i][j + 1]);
      if (j < m - 1) mx[i][j] = max(mx[i][j], mx[i][j + 1]);
    }
  }

  // Implemention of Stack
  vector<int> has(m), st(m);
  int sum = 0, stl = 0, str = 0, cul = 0, cur = -1, row = 0;
  auto init = [&]() {
    has = st = vector<int>(m, 0);
    sum = stl = str = cul = 0; cur = -1;
  };

  // Implement Insert
  auto insert = [&](int x) {
    if (top[x] > row) return;
    if (stl < str) {
      int delta = both(st[str - 1], x, min(bot[st[str - 1]], bot[x]));
      sum -= delta;
      has[st[str - 1]] -= delta;
      if (bot[st[str - 1]] <= bot[x]) {
        --str;
        while (stl < str) {
          delta = both(st[str - 1], x, min(bot[st[str - 1]], bot[x])) - both(st[str - 1], x, min(bot[st[str]], bot[x]));
          sum -= delta;
          has[st[str - 1]] -= delta;
          if (bot[st[str - 1]] <= bot[x]) {
            --str;
          } else {
            break;
          }
        }
      }
    }
    st[str++] = x;
    has[x] = reach[x];
    sum += has[x];
  };

  // Implement Erase
  auto erase = [&](int x) {
    if (top[x] > row) return;
    sum -= has[x];
    if (stl < str && st[stl] == x) ++stl;
  };

  // Iterate through U
  for (row = 0; row < HU; row++) {
    init();
    for (int i = 0; i < m; i++) {
      if (mn[row][i] <= mx[row][i]) {
        while (cur < mx[row][i]) insert(++cur);
        while (cul < mn[row][i]) erase(cul++);
        ans += (U[row][i] - '0') * sum;
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  vector<string> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  solve(a);
  printf("%lld\n", ans);
}
