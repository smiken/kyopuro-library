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
#define con 131072
#define pa pair<int,int>
#define int long long

using namespace std;
int N=262144;
int data[262144]={0},datab[262144]={0};

void addseg(int a,int b,int x,int k,int l, int r){
//	if(l==r) return;
	if(a<=l && r<=b) data[k] += x;
	else if(l<b && a<r){
		datab[k] += (min(b,r)-max(a,l))*x;
		addseg(a,b,x,k*2+1,l,(l+r)/2);
		addseg(a,b,x,k*2+2,(l+r)/2,r);
	}
}

int sumseg(int a,int b,int k,int l,int r){ //k-th kukan ga [l,r)
	if(b<=l || r<=a) return 0;
	else if(a<=l && r <= b) return data[k]*(r-l)+datab[k];
	else{
		ll res=(min(b,r)-max(a,l))*data[k];
		res += sumseg(a,b,k*2+1,l,(r+l)/2);
		res += sumseg(a,b,k*2+2,(l+r)/2,r);
		return res;
	}
}


signed main(){
 /* 
	2 no beki janakute OK
	0 ~ N-1
	hankaikukan [a,b)
	kukan add p for[a,b)   ==> addseg(a,b,p,0,0,N)
	kukan sum for [a,b)  ==> sumseg(a,b,0,0,N)
*/
		int n,q;
		cin>>n>>q;
for(int i=1;i<=n;i++){
	int y;
	scanf("%lld",&y);
	addseg(i-1,i,y,0,0,n);
}
string s;
int y,yy,yyy;
for(int e=0;e<q;e++){

	cin>>s;

	if(s=="C"){
		scanf("%lld %lld %lld",&y,&yy,&yyy);
		addseg(y-1,yy,yyy,0,0,n);
	}
	else if(s=="Q"){

		scanf("%lld %lld",&y,&yy);
		printf("%lld\n",sumseg(y-1,yy,0,0,n));
	}
}
	return 0;
}


