// {"name": "字符串哈希", "intro": "过于朴素"}
#include <cstring>
#include <string>
using std::string;
constexpr int M = 1e9 + 7;
constexpr int B = 233;
using ll = long long;
int get_hash(const string &s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) { res = ((ll)res * B + s[i]) % M; }
    return res;
}
bool cmp(const string &s, const string &t) { return get_hash(s) == get_hash(t); }
int main() { return 0; }