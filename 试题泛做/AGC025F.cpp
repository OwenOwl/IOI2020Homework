#include <bits/stdc++.h>
using namespace std;

int n, m, k_;
vector<pair<int, int>> s, t;
string p1, p2;

void solve(int x, int p) {
  int k = k_ - 1;
  if (x != 3) {
    if (x) s.emplace_back(x, p);
    return;
  }
  ++p;
  t.clear();
  while (!s.empty()) {
    int y = s.back().first, q = s.back().second;
    if (q > p) {
      if (x != 3) {
        t.emplace_back(x, p);
        k = -1;
        break;
      } else if (k <= 0) {
        t.emplace_back(3, p);
        k = -1;
        break;
      } else if (q - p > k) {
        t.emplace_back(3, p + k);
        k = -1;
        break;
      } else {
        k -= q - p;
        p = q;
      }
    }
    s.pop_back();
    if (y == 2) {
      if (x == 3) {
        t.emplace_back(1, p);
        x = 2;
      } else if (x == 2) {
        x = 2;
      } else if (x == 1) {
        x = 3;
        --k;
        if (k < 0) {
          t.emplace_back(3, p);
          break;
        }
      }
    } else if (y == 1) {
      if (x == 3) {
        t.emplace_back(2, p);
        x = 1;
      } else if (x == 1) {
        x = 1;
      } else if (x == 2) {
        x = 3;
        --k;
        if (k < 0) {
          t.emplace_back(3, p);
          break;
        }
      }
    } else {
      assert(0);
    }
    ++p;
  }
  if (k >= 0) {
    if (x != 3) {
      s.emplace_back(x, p);
    } else {
      s.emplace_back(3, p + k);
    }
  }
  while (!t.empty()) {
    s.push_back(t.back());
    t.pop_back();
  }
}

int main() {
  cin >> n >> m >> k_ >> p1 >> p2;
  reverse(p1.begin(), p1.end());
  reverse(p2.begin(), p2.end());
  while (n < m) p1.push_back('0'), ++n;
  while (m < n) p2.push_back('0'), ++m;
  for (int i = n - 1; i >= 0; i--) {
    solve(p1[i] - '0' << 1 | p2[i] - '0', i);
  }
  string q1(s[0].second + 1, '0'), q2(s[0].second + 1, '0');
  for (auto x : s) {
    q1[x.second] = '0' + (x.first >> 1);
    q2[x.second] = '0' + (x.first & 1);
  }
  while (q1.length() > 1 && q1.back() == '0') q1.pop_back();
  while (q2.length() > 1 && q2.back() == '0') q2.pop_back();
  reverse(q1.begin(), q1.end());
  reverse(q2.begin(), q2.end());
  cout << q1 << endl << q2 << endl;
}
