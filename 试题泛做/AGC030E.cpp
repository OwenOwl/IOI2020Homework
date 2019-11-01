#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int n, ans = 0;
char s[N], t[N];
vector<int> a, b;
int check(int x, int y) {
  int i = 0, j = 0, ret = 0;
  while (i < x) ret += a[i++];
  while (j < y) ret += b[j++];
  while (i < (int) a.size() && j < (int) b.size()) ret += abs(a[i++] - b[j++]);
  while (i < (int) a.size()) ret += n - a[i++];
  while (j < (int) b.size()) ret += n - b[j++];
  return ret;
}
int main() {
  scanf("%d%s%s", &n, s + 1, t + 1);
  s[0] = t[0] = '0';
  for (int i = 0; i < n; i++) {
    if (s[i + 1] != s[i]) a.push_back(i);
    if (t[i + 1] != t[i]) b.push_back(i);
  }
  for (int i = 0; i < (int) a.size(); i += 2) {
    if (i + 1 < (int) a.size()) ans += min(a[i] + a[i + 1], n - a[i] + n - a[i + 1]);
    else ans += n - a[i];
  }
  for (int j = 0; j < (int) b.size(); j += 2) {
    if (j + 1 < (int) b.size()) ans += min(b[j] + b[j + 1], n - b[j] + n - b[j + 1]);
    else ans += n - b[j];
  }
  for (int i = 0; i < (int) a.size(); i += 2) {
    for (int j = 0; j < (i ? 1 : (int) b.size()); j += 2) {
      ans = min(ans, check(i, j));
    }
  }
  printf("%d\n", ans);
}
