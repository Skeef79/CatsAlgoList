
//#include<algorithm>
// merge a and b into c 
merge(all(a), all(b), back_inserter(c));
merge(all(a),all(b), c.begin());

//#include<algorithm>
//cycle shift

//left cycle shift, elements [0,i) goes back
rotate(a.begin(), a.begin() + 2, a.end()); // 1,2,3,4,5 -> 3,4,5,1,2
//right cycle shift, k elements from back goes to the front
rotate(a.rbegin(), a.rbegin() + 2, a.rend()); // 1,2,3,4,5 -> 4,5,1,2,3

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

//priority_queue comporator (начало очереди находится в конце вектора, нужно сортить соответсвенно)
auto pqCmp = [&](const item x, const item y) {/* тело сравнения */};
priority_queue<item, vector<item>, decltype(pqCmp)> q(pqCmp);

//comporator for upper_bound - аргументы в другом порядке (значение по которому ищем, значение из массива)

//TODO add hash overloading for unordered_set 

//random
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

