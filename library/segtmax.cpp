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

using namespace std;
int N=262144;
pa sgt[530000];

pa maxis(int i,int j ){
if(i==j) return sgt[i];
	else if(i%2==1){
		pa z=maxis(i+1,j);
		if(sgt[i].first>z.first)return sgt[i] ;
		else return z;
	}
		else if(j%2==0) 	{
		pa z=maxis(i,j-1);
		if(sgt[j].first>z.first)return sgt[j] ;
		else return z;
	}
else return maxis(i/2,j/2);
}

pa sgtmax(int i ,int j) {
	return maxis(i+N,j+N);
}

void upd(int x,int y){
	x+=N;
sgt[x].first=y;
	sgt[x].second=x;
x=x/2;
while(x != 0){
	if(sgt[2*x+1].first>sgt[2*x].first){
		sgt[x]=sgt[2*x+1];
	}
	else sgt[x]=sgt[2*x];

x=x/2;
}
}


int main(){
	/* i+N ‚Ìfirst‚Éi‚Ì’lAsecond‚Éi‚ğ‚¢‚ê‚é */
	for(int i=N;i<2*N;i++) sgt[i]=make_pair(0,i-N);
	/*
	example.
	*/
	for(int i=N;i<N+100;i++) sgt[i].first=(100-i+N)*(100-i+N);
	
	for(int i=N-1;i>0;i--){
		if(sgt[2*i].first<sgt[2*i+1].first) sgt[i]=sgt[2*i+1];
		else sgt[i]=sgt[2*i];
	}

	while(1){
		int y,z;
		cin>>y>>z;
		if(y<0) break;
		pa zz=sgtmax(y,z);
		cout<<zz.first<<" "<<zz.second<<endl;
		
		
	}

	return 0;
}


