//отсюда потестил только FFT, остальные функции не протесчены, в целом нихуя не протесчено)

struct FFTSolver {
	using Complex = complex<double>;
	const double kPi = 4.0 * atan(1.0);
	vector<int> rev;

	int __lg(int n) { return n == 1 ? 0 : 1 + __lg(n / 2); }

	void compute_rev(int n, int lg) {
		rev.resize(n); rev[0] = 0;
		for (int i = 1; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
		}
	}

	vector<Complex> fft(vector<Complex> V, bool invert) {
		int n = V.size(), lg = __lg(n);
		if ((int)rev.size() != n) compute_rev(n, lg);

		for (int i = 0; i < n; ++i) {
			if (i < rev[i])
				swap(V[i], V[rev[i]]);
		}

		for (int step = 2; step <= n; step *= 2) {
			const double ang = 2 * kPi / step;
			Complex eps(cos(ang), sin(ang));
			if (invert) eps = conj(eps);

			for (int i = 0; i < n; i += step) {
				Complex w = 1;
				for (int a = i, b = i + step / 2; b < i + step; ++a, ++b) {
					Complex aux = w * V[b];
					V[b] = V[a] - aux;
					V[a] = V[a] + aux;
					w *= eps;
				}
			}
		}

		return V;
	}

	vector<Complex> transform(vector<Complex> V) {
		int n = V.size();
		vector<Complex> ret(n);
		Complex div_x = Complex(0, 1) * (4.0 * n);

		for (int i = 0; i < n; ++i) {
			int j = (n - i) % n;
			ret[i] = (V[i] + conj(V[j]))
				* (V[i] - conj(V[j])) / div_x;
		}

		return ret;
	}

	vector<int> Multiply(vector<int> A, vector<int> B) {
		int n = A.size() + B.size() - 1;
		vector<int> ret(n);
		while (n != (n & -n)) ++n;

		A.resize(n); B.resize(n);
		vector<Complex> V(n);
		for (int i = 0; i < n; ++i) {
			V[i] = Complex(A[i], B[i]);
		}

		V = fft(move(V), false);
		V = transform(move(V));
		V = fft(move(V), true);

		for (int i = 0; i < (int)ret.size(); ++i)
			ret[i] = round(real(V[i]));
		return ret;
	}
};
