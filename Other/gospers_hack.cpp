// перебор всех масок , содержащих k бит
void permute(int n, int k)
{
	int set = (1 << k) - 1;
	int limit = (1 << n);
	while (set < limit)
	{
		// переход
		int c = set & -set;
		int r = set + c;
		set = (((r^set) >> 2) / c) | r;
	}
}
