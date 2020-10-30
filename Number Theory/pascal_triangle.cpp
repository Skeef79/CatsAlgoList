ll GetCnk(ll n, ll k){
    if(Cnk[n][k] != -1)
        return Cnk[n][k];
    if (k == 0 || n == k) return 1;
    return Cnk[n][k] = (GetCnk(n-1, k-1) + GetCnk(n-1, k)) % mod;
}  
