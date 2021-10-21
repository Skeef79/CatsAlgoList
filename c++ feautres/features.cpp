
//#include<algorithm>
// merge a and b into c 
merge(all(a), all(b), back_inserter(c));


//#include<algorithm>
//cycle shift, elements a[m...n-1] become first
rotate(a.begin(), a.begin() + m, a.end()); // 1,2,3,4,5 -> 3,4,5,1,2
rotate(a.rbegin(), a.rbegin() + m, a.rend()); // 1,2,3,4,5 -> 4,5,1,2,3


//coordinate compression
vector<ll>coords;
//add all possible values
sort(all(coords));
coords.resize(unique(all(coords)) - coords.begin());


//set operator overloading (modern C++17 solution by dimasidorenko)
auto cmp = [](point a, point b) { return a.x < b.x };
set<point, decltype(cmp)> st(cmp);

//working not only on C++17 by dimas
struct CMP {
	bool operator () (int a, int b) const {
		if (dist[a] != dist[b])
			return dist[a] < dist[b];
		return a < b;
	}
};
set<int, CMP> ss;

//priority_queue comporator (знак меньше  значит что на вершине хранится максимальное, то есть они перепутаны местами)
auto pqCmp = [&](const item x, const item y) {
		return f(x) < f(y) || f(x) == f(y) && x.lvl < y.lvl;
	};

priority_queue<item, vector<item>, decltype(pqCmp)> q(pqCmp);

//TODO add hash overloading for unordered_set 
