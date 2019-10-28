#include <bits/stdc++.h>
using namespace std;

int n, a[300233], W = 0, B = 0;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    (i & 1 ? B : W) += a[i];
  }
  if (!(n & 1)) {
    printf("%d %d\n", max(B, W), min(B, W));
    return 0;
  }
  int l = 0, r = 300000001;
  while (l < r) {
    int mid = (l + r + 1) >> 1, sum = a[1];
    for (int i = 2; i <= n; i += 2) {
      if (sum >= mid) {
        sum = max(sum - a[i] + a[i + 1], a[i + 1]);
      } else {
        sum = sum - a[i] + a[i + 1];
      }
    }
    if (sum >= mid) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  printf("%d %d\n", W + l, B - l);
}
