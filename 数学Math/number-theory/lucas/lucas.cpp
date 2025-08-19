long long Lucas(long long n, long long k long long p)
{
 if (k == 0) return 1;
 return (C(n % p, k % p, p) * Lucas(n / p, k / p, p)) % p;
}