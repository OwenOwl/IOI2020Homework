#include <bits/stdc++.h>
using namespace std;

const int N = 100344;
int n, m;
vector<int> G[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  int cnt4 = 0, cnt6 = 0;
  for (int i = 1; i <= n; i++) {
    if ((int) G[i].size() & 1) {
      puts("No");
      return 0;
    } else if ((int) G[i].size() == 4) {
      cnt4++;
    } else if ((int) G[i].size() >= 6) {
      cnt6++;
    }
  }
  if (cnt6 || cnt4 >= 3) {
    puts("Yes");
    return 0;
  }
  if (cnt4 == 2) {
    for (int i = 1; i <= n; i++) {
      if (G[i].size() == 2) {
        int x = G[i][0], y = G[i][1];
        if (x == y) {
          puts("Yes");
          return 0;
        }
        for (auto &t : G[x]) if (t == i) {t = y; break;}
        for (auto &t : G[y]) if (t == i) {t = x; break;}
      }
    }
  }
  puts("No");
}
