#include <bits/stdc++.h>
using namespace std;

int n;
string s;

inline string get(int l, int r) {
  string ret = "";
  if (s[l] == 'a') {
    for (int i = l, j = 0, k = 0, m = 0; i <= r; i++) {
      if (s[i] == 'a') {
        ++j;
        if (k <= m) {
          ret += "ab";
          k = j;
        }
      } else {
        ++m;
      }
    }
  } else {
    for (int t = 1; t <= r - l + 1 >> 1; t++) {
      string cur = "";
      for (int i = l, j = 0, k = 0; i <= r; i++) {
        if (++(s[i] == 'a' ? j : k) >= t) {
          cur += s[i];
        }
      }
      ret = max(ret, cur);
    }
  }
  return ret;
}

int main() {
  cin >> n >> s;
  vector<string> t, f;
  for (int i = 0, sum = 0, last = 0; i < n << 1; i++) {
    sum += s[i] == 'a' ? 1 : -1;
    if (sum == 0) {
      t.push_back(get(last, i));
      last = i + 1;
    }
  }
  f.resize(t.size());
  for (int i = (int) t.size() - 1; ~i; i--) {
    f[i] = i == (int) t.size() - 1 ? t[i] : max(f[i + 1], t[i] + f[i + 1]);
  }
  cout << f[0] << endl;
}
