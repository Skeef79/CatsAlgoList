
//x попадает в правое поддерево
struct node {
	ll x, y;
	node* left;
	node* right;
	int cnt;
	node(ll _x) {
		x = _x;
		y = rand()*rand() + rand();
		left = right = nullptr;
		cnt = 1;
	}
};

int cnt(node* t) {
	return t ? t->cnt : 0;
}

void update(node* t) {
	if (t)
		t->cnt = 1 + cnt(t->left) + cnt(t->right);
}

node* merge(node * L, node* R) {
	if (!L)
		return R;
	if (!R)
		return L;
	if (L->y > R->y) {
		L->right = merge(L->right, R);
		update(L);
		return L;
	}
	else {
		R->left = merge(L, R->left);
		update(R);
		return R;
	}
}

pair<node*, node*> split(node *t, ll x) {
	if (!t)
		return { nullptr, nullptr };
	if (x > t->x) {
		auto res = split(t->right, x);
		t->right = res.first;
		update(t);
		return { t,res.second };
	}
	else {
		auto res = split(t->left, x);
		t->left = res.second;
		update(t);
		return { res.first, t };
	}
}

bool exist(node* t, ll  x) {
	if (!t)
		return false;
	if (x == t->x)
		return true;
	if (x > t->x)
		return exist(t->right, x);
	else
		return exist(t->left, x);
}

node* insert(node* t, ll x) {
	if (exist(t, x))
		return t;

	auto res = split(t, x);
	return merge(merge(res.first, new node(x)), res.second);
}

node* erase(node *t, ll x) {
	if (!exist(t, x))
		return t;
	auto res = split(t, x);
	return merge(res.first, split(res.second, x + 1).second);
}

//k - с нуля
ll kth(node *t, int k) {
	if (!t)
		return bad;
	if (k == cnt(t->left))
		return t->x;
	if (cnt(t->left) > k)
		return kth(t->left, k);
	else
		return kth(t->right, k - cnt(t->left) - 1);
}
