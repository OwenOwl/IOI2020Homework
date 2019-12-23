#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int S = 1006, M = 55, N = 500233;
int n, d, ch[N][10], fail[N], pc = 1, f[N][2], g[N][2];
bool fix[N];
char s[S], x[M], y[M];
int solve(char *p) {
  memset(f, 0, sizeof f);
  f[1][1] = 1;
  for (int i = 1; i <= d; i++) {
    for (int x = 1; x <= pc; x++) {
      for (int t = 0; t < 2; t++) if (f[x][t]) {
        for (int c = 0; c < 10; c++) {
          if (t && c > p[i] - '0') continue;
          int nt = t && c == p[i] - '0';
          g[ch[x][c]][nt] = (g[ch[x][c]][nt] + f[x][t]) % mod;
        }
        f[x][t] = 0;
      }
    }
    swap(f, g);
  }
  int ans = 0;
  for (int x = 1; x <= pc; x++) if (fix[x]) {
    for (int t = 0; t < 2; t++) if (f[x][t]) {
      ans = (ans + f[x][t]) % mod;
    }
  }
  return ans;
}
int main() {
  scanf("%s%s%s", s + 1, x + 1, y + 1);
  n = (int) strlen(s + 1);
  d = (int) strlen(x + 1);
  for (int i = 1; i <= n - (d / 2) + 1; i++) {
    int cur = 1;
    for (int j = 0; j < d / 2; j++) {
      if (!ch[cur][s[i + j] - '0']) ch[cur][s[i + j] - '0'] = ++pc;
      cur = ch[cur][s[i + j] - '0'];
    }
    fix[cur] = true;
  }
  queue<int> q;
  q.push(1);
  fail[1] = 0;
  for (int c = 0; c < 10; c++) {
    ch[0][c] = 1;
  }
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int c = 0; c < 10; c++) {
      if (ch[x][c]) {
        fail[ch[x][c]] = ch[fail[x]][c];
        q.push(ch[x][c]);
      } else {
        ch[x][c] = ch[fail[x]][c];
      }
    }
  }
  for (int i = 1; i <= pc; i++) if (fix[i]) {
    for (int c = 0; c < 10; c++) {
      ch[i][c] = i;
    }
  }
  for (int i = d; i; i--) {
    if (x[i] == '0') {
      x[i] = '9';
    } else {
      x[i]--;
      break;
    }
  }
  printf("%d\n", (solve(y) - solve(x) + mod) % mod);
}
