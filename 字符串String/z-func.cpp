// {"name": "Z函数", "intro": "也叫 exkmp"}
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
vector<int> z_function(string s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
        else {
            z[i] = r - i + 1;
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
    }
    return z;
}
int main() { return 0; }