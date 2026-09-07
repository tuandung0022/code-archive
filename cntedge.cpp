#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define fof(i,a,b) for (int i = a; i <= b; i++)
#define fob(i,a,b) for (int i = a; i >= b; i--)
#define el "\n"
const int inf = 1e9;
const ll infl = 1e18;
const int mod = 1e9+7;

int n;
const int N = 1e5+5;
vector<pii> adj[N];
int sz[N];
ll ans[N];

void dfs(int u, int p){
    sz[u] = 1;
    for(pii e:adj[u]){
        int v = e.first, id = e.second;
        if (v == p) continue;
        dfs(v,u);
        sz[u] += sz[v];
        ans[id] = 1LL * sz[v] * (n - sz[v]);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    fof(i,1,n-1){
        int u,v;
        cin >> u >> v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    dfs(1,0);
    fof(i,1,n-1) cout << ans[i] << el;
    return 0;
}
