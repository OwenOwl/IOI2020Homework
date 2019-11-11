#include <bits/stdc++.h>
using namespace std;

int n, k;
typedef vector<int> perm;
perm operator + (const perm &a, const perm &b) {
  perm c(n, 0);
  for (int i = 0; i < n; i++) {
    c[i] = b[a[i]];
  }
  return c;
}
perm operator ~ (const perm &a) {
  perm c(n);
  for (int i = 0; i < n; i++) {
    c[a[i]] = i;
  }
  return c;
}

int main() {
  scanf("%d%d", &n, &k);
  perm a(n), b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    --a[i];
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
    --b[i];
  }
  perm p = ~b + a + b + ~a, q(n);
  vector<int> visit(n, 0), d;
  for (int i = 0; i < n; i++) {
    if (!visit[i]) {
      d.clear();
      int j = i;
      do {
        d.push_back(j);
        visit[j] = 1;
        j = p[j];
      } while (j ^ i);
      for (int j = 0; j < (int) d.size(); j++) {
        q[d[j]] = d[(j + (k - 1) / 6) % d.size()];
      }
    }
  }
  a = q + a + ~q;
  b = q + b + ~q;
  for (int t = (k - 1) % 6; t; t--) {
    perm c = ~a + b;
    a = b, b = c;
  }
  for (int i = 0; i < n; i++) {
    printf("%d%c", a[i] + 1, i == n - 1 ? '\n' : ' ');
  }
}
