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
int par[200100],ranks[200100],kosuu[200100];     

void shoki(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		ranks[i]=0;
		kosuu[i]=1;
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
	int xx=kosuu[x],yy=kosuu[y];
 if(x==y) return;
	if(ranks[x]<ranks[y]){
		par[x]=y;
		kosuu[y]=yy+xx;
	}
 else {
	par[y]=x;
	if(ranks[x]==ranks[y]) ranks[x]=ranks[x]+1;
 	kosuu[x]=yy+xx;
 }
	return;
}


/* ---memo---
shoki(n)でn個の点に対する初期化を必ず。
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
