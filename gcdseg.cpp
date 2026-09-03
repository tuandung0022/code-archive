#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define name "GCDSEG"
#define fof(i,a,b) for (int i = a; i <= b; i++)
#define fob(i,a,b) for (int i = a; i >= b; i--)
#define el "\n"
const int inf = 1e9;
const ll infl = 1e18;
const int mod = 1e9+7;

const int MAXN = 100005;
int n, q;
int a[MAXN];
int st[4 * MAXN];

int gcd(int x, int y) {
    while (y) {
        x %= y;
        swap(x, y);
    }
    return x;
}

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    st[id] = gcd(st[2 * id], st[2 * id + 1]);
}

void update(int id, int l, int r, int u, int val) {
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (u <= mid) update(2 * id, l, mid, u, val);
    else update(2 * id + 1, mid + 1, r, u, val);
    st[id] = gcd(st[2 * id], st[2 * id + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) / 2;
    return gcd(get(2 * id, l, mid, u, v), get(2 * id + 1, mid + 1, r, u, v));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if (fopen(name ".inp", "r")) {
        freopen(name ".inp", "r", stdin);
        freopen(name ".out", "w", stdout);
    }

    if (!(cin >> n >> q)) return 0;
    fof(i, 1, n) cin >> a[i];

    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, x;
            cin >> u >> x;
            update(1, 1, n, u, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << get(1, 1, n, l, r) << el;
        }
    }

    return 0;
}
