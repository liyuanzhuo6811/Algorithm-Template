#include <cstring>
#include <iostream>
using namespace std;
struct trie
{
 int son[100000][26], cnt;
 bool exist[100000];
 void insert(char *s, int l)
 {
  int p = 0;
  for (int i = 0; i < l; i++)
  {
   int c = s[i] - 'a';
   if (!son[p][c]) son[p][c] = ++cnt;
   p = son[p][c];
  }
  exist[p] = true;
 }
 bool find(char *s, int l)
 {
  int p = 0;
  for (int i = 0; i < l; i++)
  {
   int c = s[i] - 'a';
   if (!son[p][c]) return 0;
   p = son[p][c];
  }
  return exist[p];
 }
};
int main() { return 0; }