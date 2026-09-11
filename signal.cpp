#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define name "SIGNAL"
#define fof(i,a,b) for(int i = a; i <= b; ++i)
#define fob(i,a,b) for(int i = a; i >= b; --i)
#define fi first
#define se second
#define el '\n'
const int inf = 1e9;
const ll infl = 1e18;
const int mod = 1e9+7;

int n,q;
const int N = 1e5+5;
int a[N];
int spf[N];
int gr[N];

void sievespf(){
    fof(i,1,N-1) spf[i] = i;
    fof(i,2,N-1){
        if (spf[i] == i){
            for(int j = i*2; j < N; j += i) if (spf[j] == j) spf[j] = i;
        }
    }
}

vector<int> fact(int n){
    vector<int> f;
    while(n > 1){
        int p = spf[n];
        f.push_back(p);
        while(n % p == 0) n /= p;
    }
    return f;
}

void sub1(){
    sievespf();
    int g = 1;
    while(q--){
        int l,r;
        cin >> l >> r;
        int c = 1;
        fof(i,l,r){
            vector<int> f = fact(a[i]);
            for(int v:f){
                if (gr[v] != g) gr[v] = g;
                else{
                    gr[v] = ++g;
                    c++;
                }
            }
        }
        cout << c << el;
        ++g;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(name".inp","r")){
        freopen(name".inp","r",stdin);
        freopen(name".out","w",stdout);
    }

    cin >> n >> q;
    fof(i,1,n) cin >> a[i];
    sub1();
}
