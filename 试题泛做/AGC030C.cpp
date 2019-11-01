#include <bits/stdc++.h>
using namespace std;
int main() {
  int k;
  scanf("%d", &k);
  if (k == 1) return puts("1\n1"), 0;
  int n = (k / 4 + !!(k % 4)) << 1;
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", (i + j) % n + 1 + ((i & 1) && (i + j) % n + n < k ? n : 0));
    }
    puts("");
  }
}
