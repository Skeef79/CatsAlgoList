struct node
{
	ll x, y;
	node* left;
	node * right;
	int cnt;
	node(ll _x)
	{
		x = _x;
		y = rand()*rand() + rand();
		left = right = nullptr;
		cnt = 1;
	}
};

int cnt(node *t)
{
	return t ? t->cnt : 0;
}

void update(node*t)
{
	if (t)
		t->cnt = 1 + cnt(t->left) + cnt(t->right);
}

node* merge(node *L, node* R)
{
	if (!L)
		return R;
	if (!R)
		return L;
	if (L->y > R->y)
	{
		L->right = merge(L->right, R);
		update(L);
		return L;
	}
	else
	{
		R->left = merge(L, R->left);
		update(R);
		return R;
	}
}

//в левом поддереве первые x элементов, то есть элемент с индексом x попадет в правое поддерево
pair<node*, node*> split(node *t, int x)
{
	if (!t)
		return { nullptr, nullptr };
	int idx = cnt(t->left);
	if (x > idx)
	{
		auto res = split(t->right, x - idx - 1);
		t->right = res.first;
		update(t);
		return { t, res.second };
	}
	else
	{
		auto res = split(t->left, x);
		t->left = res.second;
		update(t);
		return { res.first,t };
	}
}
//вставляется на позицию x (с нуля), остальное сдвигается вправо
node* insert(node *t, int pos, ll x)
{
	auto res = split(t, pos);
	return merge(merge(res.first, new node(x)), res.second);
}

node* erase(node *t, int pos)
{
	auto res = split(t, pos);
	return merge(res.first, split(res.second, 1).second);
}

ll get(node *t, int x)
{
	int idx = cnt(t->left);
	if (x == idx)
		return t->x;
	else
		if (x > idx)
			return get(t->right, x - idx - 1);
		else
			return get(t->left, x);
}
