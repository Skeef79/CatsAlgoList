ll gcd(ll a, ll b, ll &x, ll &y){
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll g = gcd(b, a%b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}

//need to calc lcm in main program
ll _lcm;

//O(logn) + a lot operation with modulo
ll crt(ll a1, ll a2, ll mod1, ll mod2) {
	ll x1, x2;
	//g = gcd(mod1, mod2)
	ll g = gcd(mod1, mod2, x1, x2);
	if ((a1 - a2) % g != 0)
		return -1;
	
	ll k1 = (a2 - a1) / g * x1;	
	ll res = a1 + mod1 * (k1 % mod2);

	return (res + _lcm) % _lcm;
}
