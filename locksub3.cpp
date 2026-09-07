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
const int N = 1e6+5;
int a[N];
int dif[N];

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
        dif[l]++;
        dif[r+1]--;
    }
    fof(i,1,n) a[i] = a[i-1] + dif[i];
    int c = 0;
    fof(i,1,n){
        a[i] = a[i] % 3;
        if (a[i] == 0) c++;
    }
    cout << c;
    return 0;
}
