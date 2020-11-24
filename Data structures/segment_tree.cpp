struct node
{
	ll sum;
	ll add;
	node()
	{
		sum = 0;
		add = 0;
	}
	node(ll _sum)
	{
		sum = _sum;
		add = 0;
	}
};
 
struct SegmentTree
{
	static const int N = 2e5;
	int n;
	vector<node> t;
 
	SegmentTree(vector<ll>&a)
	{
		t = vector<node>(4 * N);
		n = a.size();
		build(a);
	}
	SegmentTree()
	{
		t = vector<node>(4 * N);
		n = N;
	}
	SegmentTree(int _n)
	{
		t = vector<node>(4 * N);
		n = _n;
	}
 
	node combine(node a, node b)
	{
		node res;
		res.sum = a.sum + b.sum;
		return res;
	}
 
	void build(int v, int vl, int vr,vector<ll>&a)
	{
		if (vl == vr)
		{
			t[v] = node(a[vl]);
			return;
		}
		int vm = (vl + vr) / 2;
		build(2 * v + 1, vl, vm,a);
		build(2 * v + 2, vm + 1, vr,a);
		t[v] = combine(t[2 * v + 1], t[2 * v + 2]);
	}
 
	void push(int v, int vl, int vr)
	{
		if (t[v].add != 0)
		{
			t[v].sum += (vr-vl+1)*1LL*t[v].add;
			if (vl != vr)
			{
				t[2 * v + 1].add += t[v].add;
				t[2 * v + 2].add += t[v].add;
			}
 
			t[v].add = 0;
		}
	}
 
	node query(int v, int vl, int vr, int l, int r)
	{
		push(v, vl, vr);
		if (r < vl || vr < l)
			return node();
 
		if (vl >= l && vr <= r)
			return t[v];
 
		int vm = (vl + vr) / 2;
		node ql = query(2 * v + 1, vl, vm, l, r);
		node qr = query(2 * v + 2, vm + 1, vr, l, r);
		return combine(ql, qr);
	}
 
	void modify(int v, int vl, int vr, int l, int r, ll d)
	{
		push(v, vl, vr);
 
		if (r < vl || vr < l)
			return;
 
		if (vl >= l && vr <= r)
		{
			t[v].add = d;
			push(v, vl, vr);
			return;
		}
 
		int vm = (vl + vr) / 2;
		modify(2 * v + 1, vl, vm, l, r, d);
		modify(2 * v + 2, vm + 1, vr, l, r, d);
		t[v] = combine(t[2 * v + 1], t[2 * v + 2]);
	}
 
	void build(vector<ll>&a)
	{
		build(0, 0, n - 1, a);
	}
 
	node query(int l, int r)
	{
		return query(0, 0, n - 1, l, r);
	}
 
	void modify(int l, int r, ll d)
	{
		modify(0, 0, n - 1, l, r, d);
	}
 
};
