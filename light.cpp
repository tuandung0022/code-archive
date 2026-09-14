#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define name "light"
#define fof(i,a,b) for(int i = a; i <= b; ++i)
#define fob(i,a,b) for(int i = a; i >= b; --i)
#define el '\n'
const int inf = 1e9;
const ll infl = 1e18;
const int mod = 1e9+7;

int n,p,q;
vector<int> w1, w2;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(name".inp","r")){
        freopen(name".inp","r",stdin);
        freopen(name".out","w",stdout);
    }

    cin >> n >> p;
    fof(i,1,p){
        int t,w;
        cin >> t >> w;
        if (t == 1) w1.push_back(w);
        else w2.push_back(w);
    }
    sort(w1.begin(),w1.end());
    sort(w2.begin(),w2.end());
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        int c1 = w1.end() - lower_bound(w1.begin(),w1.end(),max(x,y));
        int c2 = upper_bound(w2.begin(),w2.end(),min(x,y)) - w2.begin();
        cout << (c1 + c2) % 2 << el;
    }
    return 0;
}

/*
Cho một bảng a kích thước n*n (bảng 1-indexed). Ban đầu mọi phần tử đều là 0.
Cho p thao tác, mỗi thao tác có dạng t,w với ý nghĩa:
- t = 1: đảo trạng thái mọi ô (x,y) thỏa mãn 1 <= x,y <= w;
- t = 2: đảo trạng thái mọi ô (x,y) thỏa mãn w <= x,y <= n;
Sau p thao tác, có q truy vấn. Mỗi truy vấn yêu cầu đưa ra trạng thái hiện tại của ô (x,y)
Input:
n,p (n <= 1e9, p <= 2e5)
P dòng: t, w
q (q <= 2e5)
q dòng: x, y
Output:
q dòng: a[xi][yi] (trạng thái của ô tại vị trí truy vấn thứ i)
Subtask:
1. n,p,q <= 200
2. n,p,q <= 2000
3. n <= 2e5
4. n <= 1e9
*/