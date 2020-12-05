struct Queue
{
	stack<pll> s1, s2;
	// функция, на которую будет очередь
	function<ll(ll, ll)> f;
	//параметром передаем тупо функцию
	Queue(function<ll(ll, ll)> _f)
	{
		f = _f;
	}
 
	int size()
	{
		return s1.size() + s2.size();
	}
	ll get()
	{
		if (s1.empty() || s2.empty())
			return s1.empty() ? s2.top().second : s1.top().second;
		else
			return f(s1.top().second, s2.top().second);
	}
 
	void push(ll x)
	{
		s1.push({ x, s1.empty() ? x : f(s1.top().second,x) });
	}
 
	void pop()
	{
		if (s2.empty())
		{
			while (!s1.empty())
			{
				ll x = s1.top().first;
				s1.pop();
				s2.push({ x,s2.empty() ? x : f(s2.top().second,x) });
			}
		}
		s2.pop();
	}
};
 
ll _min(ll a, ll b)
{
	return min(a, b);
}

//Queue q(_min);
