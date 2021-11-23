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

struct edge{ int to,cap,rev;};
vector<edge> G[100010];
bool used[100010];

void add_edge(int from ,int to, int cap){
 	G[from].push_back((edge){to,cap,(int)G[to].size()});
 	G[to].push_back((edge){from,0,(int)G[from].size()-1});
}

int ddfs(int v,int t,int f){
	if(v==t) return f;
	used[v]=true;
	for(int i=0;i<G[v].size();i++){
		edge &e=G[v][i];
		if(!used[e.to] && e.cap>0){
			int d=ddfs(e.to,t,min(f,e.cap));
			if(d>0){
				e.cap -=d;
				G[e.to][e.rev].cap +=d;
				return d;
			}
		}
	}
return 0;
}

int max_flow(int s ,int t){
int flow=0;
for(;;){
memset(used,0,sizeof(used));
int f =ddfs(s,t,inf);
if(f==0) return flow;
flow +=f;
}
}

/*　　　---memo---
add_edge(始点,終点,コスト)で枝追加
maxflow(始点,終点)で最大流=最小カットをintで返す
*/

int main(){
int n,e,g;
cin>>n>>g>>e;
int z,zz;


for(int i=0;i<g;i++){
cin>>z;
add_edge(z,n,1);
}
for(int i=0;i<e;i++){
cin>>z>>zz;
add_edge(z,zz,1);
add_edge(zz,z,1);
}
	int ans=max_flow(0,n)
cout<<max_flow(0,n)<<endl;

	return 0;
}


