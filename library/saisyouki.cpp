#include <bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<cstring>
#include<string>
#include <math.h>
#include<algorithm>
#include<functional>
//#define int long long
#define ll long long
#define inf  1000000007
#define mod 1000000007
#define PI acos(-1)
#define pa pair<int,int>
#define pal pair<ll,ll>
#define ppa pair<int,pa>
#define EPS (1e-8)
#define equals(a,b) (fabs((a)-(b))<EPS)

using namespace std;

int par[100100],ranks[100100];     

void shoki(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		ranks[i]=0;
	}
}

int root(int x){
	return par[x]==x ? x : par[x]=root(par[x]);
}

bool same(int x,int y){
return root(x)==root(y);
}

void unite(int x,int y){
 x=root(x);
 y=root(y);
 if(x==y) return;
 if(ranks[x]<ranks[y]) par[x]=y;
 else {
	par[y]=x;
	if(ranks[x]==ranks[y]) ranks[x]=ranks[x]+1;
 }
}

priority_queue<ppa ,vector<ppa>, greater<ppa> > pq;

int n;

int saisyouki(){
	int u=0;
	int ans=0;
	int V=  // V 頂点数
	shoki(V);
	while(u<V-1){
		ppa zz =pq.top();
		pa z=zz.second;
		pq.pop();
		if(same(z.first,z.second)) continue;
		unite(z.first,z.second);
		u++;
		ans += zz.first;
	}
	return ans;
}



int main(){
	/*
	pqに(コスト,(始点,終点))を入れる
	*/
	cout<<saisyouki()<<endl;
	
	return 0;
}
