//Можно не только минимум, а также максимум, гсд и подобные этим функции
struct MinQueue
{
	stack<pll> s1, s2;
	
	//получить минимум
	ll get()
	{
		if (s1.empty() || s2.empty())
			return s1.empty() ? s2.top().second : s1.top().second;
		else
			return min(s1.top().second, s2.top().second);
	}

	void push(ll x)
	{
		s1.push({ x,s1.empty() ? x : min(s1.top().second,x) });
	}

	void pop()
	{
		if (s2.empty())
		{
			while (!s1.empty())
			{
				ll x = s1.top().first;
				s1.pop();
				s2.push({ x,s2.empty() ? x : min(s2.top().second,x) });			
			}
		}
		s2.pop();
	}
};
