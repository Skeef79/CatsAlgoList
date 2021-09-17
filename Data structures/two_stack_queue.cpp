typedef ll qType;

struct Queue {
	stack<pair<qType,qType>> s1, s2;
	function<qType(qType, qType)> f;

	Queue(function<qType(qType, qType)> f) : f(f) {}

	int size() {
		return s1.size() + s2.size();
	}

	qType get()	{
		if (s1.empty() || s2.empty())
			return s1.empty() ? s2.top().second : s1.top().second;
		else
			return f(s1.top().second, s2.top().second);
	}

	void push(qType x) {
		s1.push({ x, s1.empty() ? x : f(s1.top().second,x) });
	}

	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				qType x = s1.top().first;
				s1.pop();
				s2.push({ x,s2.empty() ? x : f(s2.top().second,x) });
			}
		}
		s2.pop();
	}
};

qType _min(qType a, qType b){
	return min(a, b);
}

//Queue q(_min);
