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

int n;
vector<pa> a[10200];
void dij(int shiten){
	int d[10200]={0};
	int ans[10200]={0};
	priority_queue<pa ,vector<pa>, greater<pa> >  PQ; 
	pair<int,pa> q;
	pa r;
	int wei=0;
	int u=shiten,z=0;
	d[shiten]=1;
	while(z!=n-1){
		for(int j=0;j<a[u].size();j++){
			r=make_pair(ans[u]+a[u][j].second,a[u][j].first);
//pair(‚¢‚«‚³‚«A‚»‚±‚Ü‚Å‚Ì‚«‚å‚è)
			if(d[a[u][j].first]==0 ) PQ.push(r);
		}
		if(PQ.size()==0) goto outof;
	while(1){
		r=PQ.top();
		PQ.pop();

		if(d[r.second]==0) break;
		if(PQ.size()==0) goto outof;
		}
	u=r.second;
	d[u]=1;
	ans[u]=r.first;
	z++;
	}
	
	outof:;
	for(int i=0;i<n;i++) cout<<i<<" "<<ans[i]<<endl;
}



int main(){
	int m,k,z,l;
	cin>>n;
	for(int i=0;i<n;i++){
	cin>>z>>k;
	
		for(int j=0;j<k;j++){
		cin>>m>>l;
		a[i].push_back(make_pair(m,l));
		}
	}
	dij();

	return 0;
}


