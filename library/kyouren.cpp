#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<algorithm>
#include<functional>
#define ll long long
#define inf  999999999
#define pa pair<int,int>
using namespace std;
vector<int> gr[11000];
vector<int> igr[11000];
vector<int> ban;

int v,e;
int visit[11000]={0},gro[11000]={0};

void dfs(int i){
	if(visit[i]==0){
		visit[i]=1;
		for(int k=0;k<gr[i].size();k++) dfs(gr[i][k]);
		ban.push_back(i);
	}
}

void idfs(int i,int h){
	if(visit[i]==0){
		visit[i]=1;
		gro[i]=h;
		for(int k=0;k<igr[i].size();k++) idfs(igr[i][k],h);
	}
}

void kyouren(){
	for(int i=0;i<v;i++){
		dfs(i);
	}
	for(int i=0;i<v;i++) visit[i]=0;
	for(int i=v-1;i>=0;i--){
		idfs(ban[i],ban[i]);
	}


}




int main(){
int s,t,q,aa,aaa;
cin>>v>>e;
for(int i=0;i<e;i++){
cin>>s>>t;
gr[s].push_back(t);
igr[t].push_back(s);
}
kyouren();
//q個のクエリ　gro[i]=gro[j]なら同じ成分。
cin>>q;
for(int i=0;i<q;i++){
cin>>aa>>aaa;
if(gro[aa]==gro[aaa]) cout<<"1"<<endl;
else cout<<"0"<<endl;
}


return 0;
}