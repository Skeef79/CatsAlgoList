#define _USE_MATH_DEFINES
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<climits>
#include<set>
#include<map>
#include<cmath>
#include<iomanip>
#include<iterator>
#include<queue>
#include<stack>
#include<cctype>
#include<deque>
#include<time.h>
#include<bitset>
#include<random>
#include<functional>
#include<unordered_set>
#include<unordered_map>
#include<random>
#include<numeric>
#include<sstream>
#include<cassert>
#include<chrono>

//by Skeef79

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:16777216")
#define pb push_back
#define en '\n'
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define vec vector
#define pii pair<int,int>
#define pll pair<ll,ll>
#define szof(x) int(x.size())
#define debug(x) cerr<<#x<<" = "<<x<<'\n' 

using namespace std;

const int INF = 1000000000 + 1e8;
const ll LINF = 2000000000000000000;

void solve() {

}

int main() {
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif

	int tst = 1;
	//cin >> tst;

	while (tst--)
		solve();
}
