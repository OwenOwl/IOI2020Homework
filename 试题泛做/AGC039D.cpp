#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1);
int n, L, t[3033];
long double sx = 0, sy = 0;
int main() {
  scanf("%d%d", &n, &L);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &t[i]);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      long double x = cosl(pi * (t[i] + t[j]) / L);
      long double y = sinl(pi * (t[i] + t[j]) / L);
      sx += x * (n - j + i - 1);
      sy += y * (n - j + i - 1);
      sx -= x * (j - i - 1);
      sy -= y * (j - i - 1);
    }
  }
  sx = sx * 6 / n / (n - 1) / (n - 2);
  sy = sy * 6 / n / (n - 1) / (n - 2);
  printf("%.10lf %.10lf\n", (double) sx, (double) sy);
}
