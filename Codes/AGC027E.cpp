#include <cstdio>
#include <algorithm>

#define ll long long
#define db double
#define ull unsigned long long
#define uint unsigned int
#define FIO ""
#define dbug(...) fprintf(stderr, __VA_ARGS__)

template <typename Y> inline bool updmin(Y &a, Y b){if (a > b) {a = b; return 1;} return 0;}
template <typename Y> inline bool updmax(Y &a, Y b){if (a < b) {a = b; return 1;} return 0;}
template <typename Y> inline Y abs(Y a){if (a < 0) a = -a; return a;}
template <typename Y> inline Y sqr(Y a){return a * a;}

typedef std::pair<int, int> par;
#define fx first
#define fy second
#define mpar std::make_pair
#define pb push_back

int read() {
  int w = 1, q = 0, ch = ' ';
  for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
  for (; ch >= '0' && ch <= '9'; ch = getchar()) q = q * 10 + ch - 48;
  return q * w;
}

inline void FileIO(){freopen(FIO".in", "r", stdin); freopen(FIO".out", "w", stdout);}

#include <cstring>
const int N = 100010, mod = 1000000007;
char s[N];
int g[N], f[N], n, sum[N];

int main() {
  scanf("%s", s + 1);
  n = (int)strlen(s + 1);
  g[n + 1] = n + 1;
  sum[n + 1] = 0;
  for (int i = n; i; i--) {
    g[i] = s[i] == s[i + 1] ? i + 1 : g[i + 1];
    sum[i] = (sum[i + 1] + s[i] - 'a' + 1) % 3;
  }
  if (g[1] == n + 1) {
    puts("1");
    return 0;
  }
  f[0] = 1;
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    if (i && sum[i + 1] == 0) {
      ans = (ans + f[i]) % mod;
    }
    f[i + 1] = (f[i + 1] + f[i]) % mod;
    f[g[i + 1]] = (f[g[i + 1]] + f[i]) % mod;
  }
  printf("%d\n", ans);
  return 0;
}

