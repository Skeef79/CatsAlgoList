struct node {
	ll x;
	ll sum;
	int y;
	int size;
	node *left;
	node *right;
 
 
	node(ll key = 0, int prior = (rand() << 16) + rand()) {
		x = key;
		y = prior;
		left = nullptr;
		right = nullptr;
		size = 1;
		sum = x * x;
	}
};
 
int get_size(node* root) {
	if (!root)
		return 0;
	else
		return root->size;
}
 
long long get_sum(node* root) {
	if (!root)
		return 0;
	else
		return root->sum;
}
 
void update(node *root) {
	root->size = 1 + get_size(root->left) + get_size(root->right);
	root->sum = get_sum(root->left) + get_sum(root->right) + root->x*root->x;
}
 
 
bool exist(node *root, int key) {
	if (!root)
		return false;
	else if (root->x == key)
		return true;
	else if (key < root->x)
		return exist(root->left, key);
	else
		return exist(root->right, key);
}
 
 
pair<node*, node*> split(node* root, int key) {
	if (!root)
		return { nullptr, nullptr };
	if (key > root->x) {
		auto res = split(root->right, key);
		root->right = res.first;
		update(root);
		return { root, res.second };
	}
	else {
		auto res = split(root->left, key);
		root->left = res.second;
		update(root);
		return { res.first, root };
	}
}
 
pair<node*, node*> split_kth(node* root, int x) {
	if (!root)
		return { nullptr, nullptr };
	if (get_size(root->left) + 1 <= x) {
		auto res = split_kth(root->right, x - get_size(root->left) - 1);
		root->right = res.first;
		update(root);
		return { root, res.second };
	}
	else {
		auto res = split_kth(root->left, x);
		root->left = res.second;
		update(root);
		return { res.first, root };
	}
}
 
int kth(node* root, int k) {
	if (k <= get_size(root->left))
		return kth(root->left, k);
	else if (k == get_size(root->left) + 1)
		return root->x;
	return kth(root->right, k - get_size(root->left) - 1);
}
 
node *merge(node* root1, node* root2) {
	if (!root1)
		return root2;
	if (!root2)
		return root1;
	if (root1->y > root2->y) {
		root1->right = merge(root1->right, root2);
		update(root1);
		return root1;
	}
	else {
		root2->left = merge(root1, root2->left);
		update(root2);
		return root2;
	}
}
 
node *add(node *root, int key) {
	if (exist(root, key))
		return root;
	auto res = split(root, key);
	node * newnode = new node(key);
	return merge(merge(res.first, newnode), res.second);
}
 
node *erase(node *root, int key) {
	if (!exist(root, key))
		return root;
	auto res1 = split(root, key);
	auto res2 = split(res1.second, key + 1);
	return merge(res1.first, res2.second);
}
 
/*long long query_sum(node *root, int l, int r) {
	if (r < l)
		return 0;
	auto res1 = split(root, l);
	auto res2 = split(res1.second, r + 1);
	long long ans = get_sum(res2.first);
	root = merge(merge(res1.first, res2.first), res2.second);
	return ans;
}*/
long long next(node *root, int x) {
	auto res = split(root, x + 1);
	long long ans;
	if (!res.second)
		ans = -2000000000;
	else
		ans = kth(res.second, 1);
	root = merge(res.first, res.second);
	return ans;
}
long long prev(node *root, int x) {
	auto res = split(root, x);
	long long ans;
	if (!res.first)
		ans = -2000000000;
	else
		ans = kth(res.first, res.first->size);
	root = merge(res.first, res.second);
	return ans;
}
 
void print(node* root) {
	if (!root)
		return;
	print(root->left);
	cout << root->x << " ";
	print(root->right);
}
 
node *rev(node *root) {
	if (!root)
		return root;
	swap(root->left, root->right);
	rev(root->left);
	rev(root->right);
	return root;
}
 
node* kth_node(node* root, int k) {
	if (k <= get_size(root->left))
		return kth_node(root->left, k);
	else if (k == get_size(root->left) + 1)
		return root;
	return kth_node(root->right, k - get_size(root->left) - 1);
 
}
 
