#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<stack>
#include<string.h>
#include<string>
#include<algorithm>
#include<functional>
#define ll long long
#define inf  1000000007
#define pa pair<int,int>

using namespace std;
typedef pair<int,int> P;
struct edge{ int to,cap,cost,rev;};
vector<int> G[100010];
bool used[100010];
int match[100010];
int V;//Vは頂点数

void add_edge(int u,int v){
G[u].push_back(v);
G[v].push_back(u);
}

bool ddffss(int v){
used[v]=true;
  for(int i=0;i<G[v].size();i++){
    int u=G[v][i],w=match[u];
    if(w<0 || !used[w] &&ddffss(w)){
      match[v]=u;
      match[u]=v;
      return true;
    }
  }
  return false;
}

int bi_match(){
  int res=0;
  memset(match,-1,sizeof(match));
  for(int v=0;v<V;v++){
    if(match[v]<0){
      memset(used,0,sizeof(used));
      if(ddffss(v)){
        res++;
      }
    }
  }
  return res;
}


struct bi_match{
	private:
	public:
	
	// 頂点は0以上n未満
	// 各頂点がどっち側かは意識しなくていい
	// 多重辺はダメ
	
	vector<vector<int>> Graph;
	
	bi_match(int V){
		this->V=V;
		Graph.resize(V);
		match.resize(V,-1);
		used.resize(V,-1);
	}
	
	void add_edge(int u,int v){
		Graph[u].pb(v);
		Graph[v].pb(u);		
	}
	
	bool dfs_bi(int v,int num){
		used[v] = num;
  		for(int u:Graph[v]){
    		int w=match[u];
    		if(w<0 || used[w]<num && dfs_bi(w,num)){
      			match[v]=u;
      			match[u]=v;
      			return true;
    		}
  		}
  		return false;
	}
	
	int solve(){
 		int res=0;
  		for(int v=0;v<V;v++){
    		if(match[v]<0){
      			if(ddffss(v)){
       				 res++;
      			}
    		}
  		}
 		return res;
	}
};

/*　　　---memo---
add_edge(始点,終点)で枝追加
bi_match()でmatchingをintで返す
*/

int main(){
// Vは頂点数
int n,k,a,b;
cin>>n>>k;
V=2*n;
for(int i=0;i<k;i++){
  cin>>a>>b;
  add_edge(a-1,n+b-1);
}
cout<<bi_match()<<endl;
	return 0;
}
