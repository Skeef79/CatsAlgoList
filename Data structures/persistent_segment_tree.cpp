
struct node // структура вершины
{
	node* l;
	node* r;
	int sum;
	node(int _sum = 0)
	{
		l = nullptr;
		r = nullptr;
		sum = _sum;
	}
};

typedef node* pnode;

pnode build(vector<int>& a, int vl, int vr)  // построение, работает как в обычном ДО
{
	if (vl == vr)
		return new node(a[vl]);

	int vm = vl + (vr - vl) / 2;

	pnode temp = new node();
	temp->l = build(a, vl, vm);
	temp->r = build(a, vm + 1, vr);

	temp->sum = temp->l->sum + temp->r->sum;
	return temp;
}

int query(pnode t, int vl, int vr, int l, int r) //запрос тоже работает как в обычном ДО, 
{												 // только вызываем его от нужного корня (версии ДО)
	if (vr < l || r < vl)
		return 0;

	if (vl >= l && vr <= r)
		return t->sum;

	int vm = vl + (vr - vl) / 2;
	int ql = query(t->l, vl, vm, l, r);
	int qr = query(t->r, vm + 1, vr, l, r);

	return ql + qr;
}

pnode modify(pnode t, int vl, int vr, int pos, int val)
{
	if (vl == vr)
		return new node(val); // вместо изменения мы создаем новую вершину

	int vm = vl + (vr - vl) / 2;

	if (pos <= vm)
	{
		pnode temp = new node();
		temp->l = modify(t->l, vl, vm, pos, val); // прицепляем ее в нужное место.
		temp->r = t->r;
		temp->sum = temp->l->sum + temp->r->sum;
		return temp;
	}
	else
	{
		pnode temp = new node();
		temp->l = t->l;
		temp->r = modify(t->r, vm + 1, vr, pos, val);
		temp->sum = temp->l->sum + temp->r->sum;
		return temp;
	}
}

vector<pnode> roots; // храним корни всех версий ДО 

//Например, задача кол-во различных на отрезке. 
//Посмотрим на первое вхождение каждого числа и запишем там 1 и построим ДО на сумму. (это работает для l=0)
//Далее для каждого l построим новых деревьев, будем идти и смотреть, если текущее число встретиться далее, то нужно перестроить ДО и поставить единичку в новой позиции, а в старой 0
