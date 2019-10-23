#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n;
ll S, x[100233], p[100233], ans;
int main() {
  scanf("%d%lld", &n, &S);
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", &x[i], &p[i]);
  }
  int l = 1, r = n;
  while (x[l] < S && x[r] > S) {
    ans += x[r] - x[l];
    if (p[l] >= p[r]) {
      while (p[l] >= p[r] && x[r] > S) {
        p[l] += p[r--];
      }
    } else {
      while (p[l] < p[r] && x[l] < S) {
        p[r] += p[l++];
      }
    }
  }
  ans += max(abs(S - x[l]), abs(S - x[r]));
  printf("%lld\n", ans);
}
