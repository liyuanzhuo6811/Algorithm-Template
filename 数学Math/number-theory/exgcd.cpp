#include <iostream>
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int ex_gcd(int a, int b, int &x, int &y)
{
 if (!b) return x = 1, y = 0, a;
 int g = ex_gcd(b, a % b, x, y), t = x;
 x = y, y = t - (a / b) * y;
 return g;
}
int main() { return 0; }