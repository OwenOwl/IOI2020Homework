#include <bits/stdc++.h>
using namespace std;

int n, k;
string s;
int main() {
  cin >> n >> k >> s;
  char c = *min_element(s.begin(), s.end());
  string t = s;
  reverse(t.begin(), t.end());
  s += t;
  int l = 0;
  for (int i = 0, j = 0; i < n << 1; i++) {
    j = s[i] == c ? j + 1 : 0;
    l = max(l, j);
  }
  int l1 = l;
  for (int i = 1; i < k; i++) {
    l <<= 1;
    if (l >= n) {
      for (int i = 0; i < n; i++) putchar(c);
      return 0;
    }
  }
  string x = "{";
  for (int i = 0, j = 0; i < n << 1; i++) {
    j = s[i] == c ? j + 1 : 0;
    if (j == l1) {
      if (i - n < 0) continue;
      string t = s.substr(i - j - n + l + 1 , n - l);
      reverse(t.begin(), t.end());
      x = min(x, t);
    }
  }
  for (int i = 0; i < l; i++) putchar(c);
  cout << x;
}
