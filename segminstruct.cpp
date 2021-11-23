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
#define mp make_pair
#define int long long
using namespace std;


struct Segmin{
	//       1
	//   2        3
	// 4   5   6    7
	
	
	private:
	public:
	
	// (1<<15)=32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int cor=(1<<18);
	
	vector<pa> vec;
	
	void shoki1(){
		
		vec.resize(2*cor+3, mp(0,0));
		for(int i=cor;i<2*cor;i++)vec[i].second=i-cor;
	}
		void shoki2(){
			for(int i=cor-1;i>0;i--) {
				if(vec[2*i].first<=vec[2*i+1].first) vec[i]=vec[2*i];
				else vec[i]=vec[2*i+1];
			}
		}
		
	void updadd(int x,int w){
		//x €–Ú‚É w‰ÁŽZ
		x+=cor;
		vec[x].first+=w;
		while(1){
			x/=2;
			if(x==0) break;
			if(vec[2*x].first<=vec[2*x+1].first) vec[x]=vec[2*x];
			else vec[x]=vec[2*x+1];
		}
		
	}
	
	void updchan(int x,int w){
		//x€–Ú‚ðw‚É•ÏX
		x+=cor;
		vec[x].first=w;
		while(1){
			x/=2;
			if(x==0) break;
			if(vec[2*x].first<=vec[2*x+1].first) vec[x]=vec[2*x];
			else vec[x]=vec[2*x+1];
		}
		
	}
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	pa segmin(int a,int b,int k=1,int l=0,int r=-10){
		if(r<0)r=cor;
		
	//	cout<<a<<" "<<b<<" "<<k<<" "<<l<<" "<<r<<endl;
		
		if(a<=l && r<=b){
			return vec[k];
		}
		if(r<=a || b<=l){
			return mp((1ll<<31)-1,-1);
		}
		
		pa v1=segmin(a,b,k*2,l,(l+r)/2),v2=segmin(a,b,k*2+1,(l+r)/2,r);
		
		if(v1.first<=v2.first)return v1;
		else return v2;
	}
	
};

signed main(){
Segmin SE;
	
		int n,q;
	cin>>n>>q;
	
	SE.shoki1();
	for(int i=0;i<n;i++){
		SE.vec[i+SE.cor].first=(1ll<<31)-1;
	}
	SE.shoki2();
	
	

	
	for(int i=0;i<q;i++){
	int a,b,c;
		cin>>a>>b>>c;
		
		if(a==0)SE.updchan(b,c);
		else cout<<SE.segmin(b,c+1).first<<endl;
	
	}
	return 0;
}


