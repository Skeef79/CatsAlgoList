vector<int>evenPalindrome(string s) 
{
	int n = s.length();
	vector<int>d(n);
	for (int i = 1, l = 0, r = 0; i < n; i++)
	{
		if (i <= r)
			d[i] = min(r - i + 1, d[l + r - i]);
		while (i + d[i] < n && i - d[i] >= 0 && s[i + d[i]] == s[i - d[i]])
			d[i]++;
		d[i]--;
		if (i + d[i] > r)
			l = i - d[i], r = i + d[i];
	}
	return d;
}

vector<int>oddPalindrome(string s)
{
	int n = s.length();
	vector<int>d(n);
	for (int i = 1, l = 0, r = 0; i < n; i++)
	{
		if (i <= r)
			d[i] = min(r - i + 1, d[l + r - i + 1]);

		while (i + d[i] < n && i - d[i] - 1 >= 0 && s[i + d[i]] == s[i - d[i] - 1])
			d[i]++;

		if (i + d[i] > r)
			l = i - d[i], r = i + d[i] - 1;
	}
	return d;
}
