#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:16777216")
#define pb push_back
#define en '\n'
#define forn(i,n) for(int i = 0;i<n;i++)
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define vec vector
#define pii pair<int,int>
#define pll pair<ll,ll>
#define szof(x) int(x.size())

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

const int INF = 1000000000 + 1e8;
const ll LINF = 2000000000000000000;

void solve() {

}

int main() {
    srand(time(0));
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tst = 1;
    //cin >> tst;

    while (tst--)
        solve();

}
