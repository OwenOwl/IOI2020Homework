#include <bits/stdc++.h>
using namespace std;

int n, p[300233];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
  for (int l = 1, r = 1; l <= n; l = ++r) {
    while (r + 1 <= n && ((p[r] == r) ^ (p[r + 1] == r + 1))) ++r;
    int ml = 0, mr = 0;
    for (int i = l; i <= r; i++) if (p[i] != i) {
      if (p[i] < l || p[i] > r) return puts("No"), 0;
      else if ((p[i] < i ? ml : mr) < p[i]) (p[i] < i ? ml : mr) = p[i];
      else return puts("No"), 0;
    }
  }
  puts("Yes");
}
