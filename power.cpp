#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,ll>;
#define name "power"
#define fof(i,a,b) for(int i = a; i <= b; ++i)
#define fob(i,a,b) for(int i = a; i >= b; --i)
#define el '\n'
const int inf = 1e9;
const ll infl = 1e18;
const int mod = 1e9+7;

struct Edge{
    int u,v;
    ll w;
    bool operator < (const Edge &o) const{
        return w < o.w;
    }
};

int n,m,k;
const int N = 5e5+5;
int p[N];
vector<Edge> edge;
int par[N], sz[N];

int findset(int u){
    return (u == par[u]) ? u : par[u] = findset(par[u]);
}

bool unite(int u, int v){
    u = findset(u);
    v = findset(v);
    if (u == v) return 0;
    if (sz[u] < sz[v]) swap(u,v);
    par[v] = u;
    sz[u] += sz[v];
    return 1;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(name".inp","r")){
        freopen(name".inp","r",stdin);
        freopen(name".out","w",stdout);
    }

    cin >> n >> m >> k;
    fof(i,0,n) par[i] = i;
    fill(sz,sz+n+1,1);
    fof(i,1,k){
        cin >> p[i];
        unite(0,p[i]);
    }
    fof(i,1,m){
        int u, v; ll w;
        cin >> u >> v >> w;
        edge.push_back({u,v,w});
    }
    ll t = 0;
    for(Edge e:edge){
        if (unite(e.u,e.v)){
            t += e.w;
        }
    }
    if (sz[findset(0)] == n+1) cout << t;
    else cout << -1;
    return 0;
}