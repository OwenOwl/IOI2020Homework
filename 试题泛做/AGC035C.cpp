#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  if ((n & -n) == n) return puts("No"), 0;
  printf("Yes\n1 2\n2 3\n3 %d\n%d %d\n%d %d\n", n + 1, n + 1, n + 2, n + 2, n + 3);
  for (int i = 5; i <= n; i += 2) printf("1 %d\n%d %d\n1 %d\n%d %d\n", i - 1, i - 1, i + n, i, i, i - 1 + n);
  if (!(n & 1)) printf("%d %d\n%d %d\n", n, n & -n, n + n, (n & -n) ^ n ^ 1);
}
