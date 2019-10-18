#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n * 2);
  for (int i = 0; i < n * 2; i++) {
    scanf("%d", &a[i]);
  }
  sort(a.begin(), a.end());
  int l = 0, r = n;
  while (l < r) {
    int mid = (l + r) >> 1;
    bool ok = true;
    for (int i = 0; i < n * 2 - mid * 2; i++) {
      if (a[mid * 2 + i] + a[n * 2 - 1 - i] < m) {
        ok = false;
        break;
      }
    }
    if (ok) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  int ans = 0;
  for (int i = 0; i < l * 2; i++) {
    ans = max(ans, (a[i] + a[l * 2 - 1 - i]) % m);
  }
  for (int i = 0; i < n * 2 - l * 2; i++) {
    ans = max(ans, (a[l * 2 + i] + a[n * 2 - 1 - i]) % m);
  }
  printf("%d\n", ans);
}

