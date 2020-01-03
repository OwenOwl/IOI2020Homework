#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100233, B = 400, M = 500;
int n, q, cnt = 1;
#define bel(x) (((x)-1)/B+1)
#define lef(x) (((x)-1)/B*B+1)
#define rit(x) (((x)-1)/B*B+B)

struct Tree {
  vector<int> G[N];
  int dfn[N], las[N], idfn[N], dfc = 0;
  void dfs(int x) {
    dfn[x] = ++dfc;
    idfn[dfn[x]] = x;
    for (auto y : G[x]) {
      dfs(y);
    }
    las[x] = dfc;
  }
} T1, T2;
namespace partialBlock {
  ll t[M], a[N];
  void pAdd(int x, int v) {
    if (x > cnt) return;
    t[bel(x)] += v;
    a[x] += v;
  }
  ll pAsk(int x) {
    ll ret = 0;
    for (int i = 1; i < bel(x); i++) {
      ret += t[i];
    }
    for (int i = lef(x); i <= x; i++) {
      ret += a[i];
    }
    return ret;
  }
  void rangeAdd(int l, int r) {
    pAdd(l, 1);
    pAdd(r + 1, -1);
  }
  ll positionAsk(int x) {
    return pAsk(x);
  }
  void nodeAdd(int x) {
    rangeAdd(T1.dfn[x], T1.las[x]);
  }
  ll pathAsk(int x) {
    return positionAsk(T1.dfn[x]);
  }
}
namespace completeBlock {
  ll t[M];
  int occur[M];
  void rangeAdd(int l, int r) {
    for (int i = l; i <= r; i++) {
      t[i]++;
    }
  }
  void maintainNode(int x, int v) {
    occur[bel(T2.dfn[x])] += v;
  }
  ll getAnswer(int *c) {
    ll ret = 0;
    for (int i = 1; i <= bel(cnt); i++) {
      ret += c[i] * t[i];
    }
    return ret;
  }
}
void t2SubtreeAdd(int x) {
  int l = T2.dfn[x], r = T2.las[x];
  if (bel(l) == bel(r)) {
    for (int i = l; i <= r; i++) {
      partialBlock::nodeAdd(T2.idfn[i]);
    }
  } else {
    completeBlock::rangeAdd(bel(l) + 1, bel(r) - 1);
    for (int i = l; i <= rit(l); i++) {
      partialBlock::nodeAdd(T2.idfn[i]);
    }
    for (int i = lef(r); i <= r; i++) {
      partialBlock::nodeAdd(T2.idfn[i]);
    }
  }
}
int occur[N][M];
void t1OccurPredeal(int x) {
  completeBlock::maintainNode(x, 1);
  for (int i = 1; i <= bel(cnt); i++) {
    occur[x][i] = completeBlock::occur[i];
  }
  for (auto y : T1.G[x]) {
    t1OccurPredeal(y);
  }
  completeBlock::maintainNode(x, -1);
}
ll t1PathAsk(int x) {
  return completeBlock::getAnswer(occur[x]) + partialBlock::pathAsk(x);
}
namespace AhoCorasick {
  int ch[N][26], fail[N];
  int insert(char *s, int L) {
    int cur = 1;
    for (int i = 1; i <= L; i++) {
      if (!ch[cur][s[i] - 'a']) {
        ch[cur][s[i] - 'a'] = ++cnt;
      }
      cur = ch[cur][s[i] - 'a'];
    }
    return cur;
  }
  void buildT1() {
    for (int i = 1; i <= cnt; i++) {
      for (int j = 0; j < 26; j++) if (ch[i][j]) {
        T1.G[i].push_back(ch[i][j]);
      }
    }
  }
  void calculateFail() {
    for (int i = 0; i < 26; i++) {
      ch[0][i] = 1;
    }
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        if (ch[x][i]) {
          fail[ch[x][i]] = ch[fail[x]][i];
          q.push(ch[x][i]);
        } else {
          ch[x][i] = ch[fail[x]][i];
        }
      }
    }
  }
  void buildT2() {
    for (int i = 2; i <= cnt; i++) {
      T2.G[fail[i]].push_back(i);
    }
  }
}

int endpos[N], qx[N];
char s[N];
vector<int> query[N];
ll ans[N];

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    int L = (int) strlen(s + 1);
    endpos[i] = AhoCorasick::insert(s, L);
  }
  AhoCorasick::buildT1();
  AhoCorasick::calculateFail();
  AhoCorasick::buildT2();
  T1.dfs(1);
  T2.dfs(1);
  t1OccurPredeal(1);
  for (int i = 1, l, r; i <= q; i++) {
    scanf("%d%d%d", &l, &r, &qx[i]);
    qx[i] = endpos[qx[i]];
    query[l - 1].push_back(-i);
    query[r].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    t2SubtreeAdd(endpos[i]);
    for (auto x : query[i]) {
      if (x < 0) {
        ans[-x] -= t1PathAsk(qx[-x]);
      } else {
        ans[x] += t1PathAsk(qx[x]);
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    printf("%lld\n", ans[i]);
  }
}
