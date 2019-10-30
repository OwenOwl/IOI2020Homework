#include <bits/stdc++.h>
using namespace std;

const int N = 200233;
int n, p[N], sufMaxCnt[N], sufEvenScore[N], sufOddScore[N];
bool isPreMax[N];

vector<pair<int*, int>> undoStack;
int tOdd[N], tEven[N], undoSize[N];
void add(int *t, int x, int y) {
  for (x = n + 1 - x; x <= n; x += x & -x) {
    if (t[x] < y) {
      undoStack.emplace_back(&t[x], t[x]);
      t[x] = y;
    }
  }
}
int ask(int *t, int x) {
  int r = 0xc0c0c0c0;
  for (x = n + 1 - x; x; x -= x & -x) {
    r = max(r, t[x]);
  }
  return r;
}
bool check(int mx, int req) {
  if (req < 0) return false;
  return ask(req & 1 ? tOdd : tEven, mx) >= req;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
  }
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    mx = max(mx, p[i]);
    if (p[i] == mx) {
      isPreMax[i] = true;
    }
  }
  for (int i = n; i; i--) {
    sufMaxCnt[i] = sufMaxCnt[i + 1] + (int) isPreMax[i];
  }
  memset(tOdd, 0xc0, sizeof tOdd);
  for (int i = n; i; i--) {
    int sOdd = ask(tOdd, p[i]), sEven = ask(tEven, p[i]);
    undoSize[i] = (int) undoStack.size();
    if (isPreMax[i]) {
      sufEvenScore[i] = sEven + 2;
      sufOddScore[i] = sOdd < 0 ? 0xc0c0c0c0 : sOdd + 2;
    } else {
      sufEvenScore[i] = sOdd < 0 ? 0xc0c0c0c0 : sOdd + 1;
      sufOddScore[i] = sEven + 1;
    }
    if (sufOddScore[i] > 0) add(tOdd, p[i], sufOddScore[i]);
    add(tEven, p[i], sufEvenScore[i]);
  }
  if (!check(1, sufMaxCnt[1])) {
    puts("-1");
    return 0;
  }
  int max0 = 1, max1 = 1, diff = 0;
  for (int i = 1; i <= n; i++) {
    while ((int) undoStack.size() > undoSize[i]) {
      *undoStack.back().first = undoStack.back().second;
      undoStack.pop_back();
    }
    if (max0 <= p[i]) {
      if (check(max1, diff + 1 + sufMaxCnt[i + 1]) || check(p[i], sufMaxCnt[i + 1] - diff - 1)) {
        putchar('0');
        max0 = p[i];
        diff++;
      } else {
        putchar('1');
        if (max1 <= p[i]) {
          max1 = p[i];
          diff--;
        }
      }
    } else {
      if (check(max1, diff + sufMaxCnt[i + 1]) || check(max0, sufMaxCnt[i + 1] - diff)) {
        putchar('0');
      } else {
        putchar('1');
        if (max1 <= p[i]) {
          max1 = p[i];
          diff--;
        }
      }
    }
  }
}
