#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, t;
  cin >> s;
  for (int i = 0; i < (int) s.length(); i++) if (!i || s[i] != s[i - 1]) t += s[i];
  vector<int> c(3);
  for (int i = 0; i < (int) t.length(); i++) c[t[i] - 'A']++;
  int A = 'A', B = 'B', C = 'C';
  if (c[0] > c[1]) swap(c[0], c[1]), swap(A, B);
  if (c[1] > c[2]) swap(c[1], c[2]), swap(B, C);
  if (c[0] > c[1]) swap(c[0], c[1]), swap(A, B);
  int x = 0, y = 0;
  string w = "";
  for (int i = 0, front = 1; i <= (int) t.length(); i++) {
    if (i == (int) t.length() || t[i] == A) {
      if (w[0] == B || w.length() >= 2) x++;
      if (!front && i != (int) t.length() && w.length() == 1 && w[0] == C) y++;
      front = 0;
      w = "";
    } else {
      w += t[i];
    }
  }
  int deal = max(0, y - x);
  w = s = "";
  for (int i = 0, front = 1; i <= (int) t.length(); i++) {
    int ok = 1;
    if (i == (int) t.length() || t[i] == A) {
      if (!front && i != (int) t.length() && w.length() == 1 && w[0] == C && deal) {
        ok = 0;
        deal--;
      }
      front = 0;
      w = "";
    } else {
      w += t[i];
    }
    if (i != (int) t.length() && ok && (s == "" || s.back() != t[i])) {
      s += t[i];
    }
  }
  int ka = 0, kb = 0, kc = 0;
  for (int i = 0; i < (int) s.length(); i++) {
    if (s[i] == A) ka++;
    if (s[i] == B) kb++;
    if (s[i] == C) kc++;
  }
  w = t = "";
  for (int i = 0, front = 1; i <= (int) s.length(); i++) {
    int ok = 1;
    if (i == (int) s.length() || s[i] == A) {
      if (!front && i != (int) s.length() && w.length() == 1 && w[0] == C) {
        ok = 0;
      }
      if (ok) {
        if (kc > kb && w != "" && w.back() == C) w.pop_back(), kc--;
        reverse(w.begin(), w.end());
        if (kc > kb && w != "" && w.back() == C) w.pop_back(), kc--;
        reverse(w.begin(), w.end());
      }
      t += w;
      if (i != (int) s.length()) t += char(A);
      front = 0;
      w = "";
    } else {
      w += s[i];
    }
  }
  w = s = "";
  for (int i = 0, front = 1; i <= (int) t.length(); i++) {
    if (i == (int) t.length() || t[i] == A) {
      int limit = front || i == (int) t.length() ? 2 : 3;
      while (kb > ka && (int) w.length() >= limit) {
        w.pop_back();
        w.pop_back();
        kb--;
      }
      s += w;
      if (i != (int) t.length()) s += char(A);
      front = 0;
      w = "";
    } else {
      w += t[i];
    }
  }
  cout << s << endl;
}
