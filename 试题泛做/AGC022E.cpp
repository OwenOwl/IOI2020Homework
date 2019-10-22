#include <bits/stdc++.h>
using namespace std;

const int N = 300233, mod = 1000000007;
int n, f[2][3][3], g[2][3][3];
char s[N];

int main() {
  scanf("%s", s + 1);
  int n = (int) strlen(s + 1);
  s[++n] = '1';
  f[1][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    memset(g, 0, sizeof g);
    for (int a = 0; a < 2; a++) {
      for (int b = 0; b < 3; b++) {
        for (int c = 0; c < 3; c++) {
          if (s[i] != '0') {
            int na = a, nb = 0, nc = c;
            if (!(b & 1)) na ^= 1;
            if (a == 1 && b == 0 && c == 0) nc = 1;
            if (a == 0 && b == 0 && c == 1) nc = 2;
            (g[na][nb][nc] += f[a][b][c]) %= mod;
          }
          if (s[i] != '1') {
            int na = a, nb = b == 2 ? 1 : b + 1, nc = c;
            (g[na][nb][nc] += f[a][b][c]) %= mod;
          }
        }
      }
    }
    memcpy(f, g, sizeof g);
  }
  printf("%d\n", f[1][0][2]);
}
