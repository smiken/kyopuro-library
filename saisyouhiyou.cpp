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
vector<edge> G[100010];
bool used[100010];
int h[100010],dist[100010],prevv[100010],preve[100010];
int V;//Vは頂点数

void add_edge(int from,int to,int cap,int cost){
G[from].push_back( (edge){to,cap,cost,G[to].size()} );
	G[to].push_back( (edge){from,0,-cost,G[from].size()-1 });
}

int min_cost_flow(int s,int t,int f){
	int res=0;
	fill(h,h+V,0);
	while(f>0){
		priority_queue <P,vector<P>,greater<P> > que;
		fill(dist,dist+V,inf);
		dist[s]=0;
		que.push(P(0,s));
		while( !que.empty() ){
			P p=que.top();que.pop();
			int v=p.second;
			if(dist[v]<p.first) continue;
			for(int i=0;i<G[v].size();i++){
				edge &e=G[v][i];
				if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
					dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
					prevv[e.to]=v;
					preve[e.to]=i;
					que.push(P(dist[e.to],e.to));
				}
		}
	}
	if(dist[t]==inf) return -1;
	for(int v=0;v<V;v++)h[v] += dist[v];
	int d=f;
	for(int v=t;v!=s;v=prevv[v]){
		d=min(d,G[prevv[v]][preve[v]].cap);
	}
	f -= d;
	res += d*h[t];
	for(int v=t; v!=s;v=prevv[v]){
		edge &e =G[prevv[v]][preve[v]];
		e.cap -=d;
		G[v][e.rev].cap +=d;
	}
}
return res;
}

/*　　　---memo---
add_edge(始点,終点,youryou ,コスト)で枝追加
min_cost_flow(始点,終点,ryou)でhiyouをintで返す
*/

int main(){
// Vは頂点数


	return 0;
}
