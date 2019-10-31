#include <bits/stdc++.h>
using namespace std;

int n, a[200233];
vector<pair<int, int>> b;
int main() {
  scanf("%d", &n);
  int ok1 = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    ok1 &= a[i] > a[i - 1];
  }
  if (ok1) {
    puts("1");
    return 0;
  }
  int l = 2, r = 1000000000;
  while (l < r) {
    int m = (l + r) >> 1, ok = 1;
    b.clear();
    for (int i = 1; i <= n; i++) {
      if (a[i] <= a[i - 1]) {
        while (!b.empty() && b.back().first > a[i]) {
          b.pop_back();
        }
        int bit = a[i];
        while (!b.empty() && b.back().first == bit && b.back().second == m - 1) {
          b.pop_back();
          bit--;
        }
        if (bit <= 0) {
          ok = 0;
          break;
        }
        if (!b.empty() && b.back().first == bit) {
          b.back().second++;
        } else {
          b.emplace_back(bit, 1);
        }
      }
    }
    if (ok) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  printf("%d\n", l);
}
