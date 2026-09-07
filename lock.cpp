#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define name "lock"
#define fof(i,a,b) for (int i = a; i <= b; i++)
#define fob(i,a,b) for (int i = a; i >= b; i--)
#define el "\n"
const int inf = 1e9;
const ll infl = 1e18;
const int mod = 1e9+7;

int n,t;
vector<pii> e;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(name".inp", "r")){
        freopen(name".inp", "r", stdin);
        freopen(name".out", "w", stdout);
    }
    
    cin >> n >> t;
    fof(i,1,t){
        int l,r;
        cin >> l >> r;
        e.push_back({l,1});
        e.push_back({r+1,-1});
    }
    e.push_back({n+1,0});
    sort(e.begin(),e.end());
    ll c = 0;
    int cur = 0, last = 1;
    for(pii x:e){
        if (x.first > last){
            if (cur % 3 == 0) c += x.first - last;
            last = x.first;
        }
        cur += x.second;
    }
    cout << c;
    return 0;
}
