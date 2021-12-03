int mu[]

void precalc() {
	mu[1] = 1;
	for (int x = 1; x < N; x++)
		for (int y = 2 * x; y < N; y += x)
			mu[y] -= mu[x];
}
