int basis[LOG];

void add(int mask) {
	for (int i = LOG - 1; i >= 0; i--) {
		if (!(mask&(1 << i)))
			continue;
		if (!basis[i]) {
			basis[i] = mask;
			return;
		}
		mask ^= basis[i];
	}
}
