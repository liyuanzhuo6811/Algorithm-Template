#include <cstring>
#include <iostream>
using std::string;
using ull = unsigned long long;
ull base = 131, mod1 = 212370440130137957, mod2 = 1e9 + 7;
ull get_hash1(string s)
{
 int len = s.size();
 ull ans = 0;
 for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod1;
 return ans;
}
ull get_hash2(string s)
{
 int len = s.size();
 ull ans = 0;
 for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod2;
 return ans;
}
bool cmp(const string s, const string t)
{
 bool f1 = get_hash1(s) != get_hash1(t);
 bool f2 = get_hash2(s) != get_hash2(t);
 return f1 || f2;
}
int main() { return 0; }