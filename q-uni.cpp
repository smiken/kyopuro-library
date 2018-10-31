    #include<iostream>
    #include<cstdio>
    #include<vector>
    #include<queue>
    #include<map>
    #include<string>
    #include <cmath>
    #include<complex>
    #include<algorithm>
    #include<functional>
    #define ll long long
    #define inf  1000000007
    #define pa pair<int,int>
    using namespace std;
vector<int> i2g;         
vector<vector<int>> g2i; 

void init(int n) {
  i2g.resize(n);
  g2i.resize(n);
  for (int i = 0; i <= n; ++i) {
  
    i2g[i] = i;
    g2i[i].assign(1, i);
  }
}
bool same(int ia, int ib) {
  return i2g[ia] == i2g[ib];
}
void unite(int ia, int ib) {
 
  if (g2i[i2g[ia]].size() < g2i[i2g[ib]].size()) {
    swap(ia, ib);
  }


  int ga = i2g[ia], gb = i2g[ib];
  for (int j : g2i[gb]) i2g[j] = ga;
  g2i[ga].insert(g2i[ga].end(), g2i[gb].begin(), g2i[gb].end());
  g2i[gb].clear();
}



/* ---memo---
init(n)でn個の点に対する初期化を必ず。
unite(a,b)でaとbを同じグループに入れる
same(a,b)がtrueなら同グループ,falseなら別。
*/


int main(){
int n,q,p,a,b;
cin>>n>>q;
shoki(n);
for(int i=0;i<q;i++){
	cin>>p>>a>>b;
//cout<<a<<endl;
	if(p==0) unite(a,b);
	else{
		if(same(a,b)) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}


return 0;    
}
