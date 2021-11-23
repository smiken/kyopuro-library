#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<algorithm>
#include<functional>
#define ll long long

#define pa pair<int,int>
#define int long long

using namespace std;

int inf=(1ll<<40);
struct seg_rangeupd_getpoint{
	//       1
	//   2        3
	// 4   5   6    7
	
	
	private:
	public:
	
	// (1<<15)=32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int cor=(1<<17);
	
	vector<int> vec;
	void shoki1(){
		vec.resize(2*cor+3, inf);
	}
	void shoki2(){
		vec[1]=(1ll<<31)-1;
		//‰Šú’l
	}
		
	void chien(int k,int l,int r){
		if(l+1<r)if(vec[k]!=inf){
			vec[2*k]=vec[k];
			vec[2*k+1]=vec[k];
			vec[k]=inf;
		}
	}
	
	void rangeupd(int a,int b,int w, int k=1,int l=0,int r=-3){
		//[a,b)‚ð w‚É•ÏX
		if(r<0) r=cor;
		if(a<=l && r<=b){
			vec[k]=w;
			return ;
		}
		if(r<=a || b<=l){
			return ;
		}
		chien(k,l,r);
//	cout<<k<<" "<<l<<" "<<r<<endl;
		rangeupd(a,b,w,k*2,l,(l+r)/2);
		rangeupd(a,b,w,k*2+1,(l+r)/2,r);
		return ;
	}
	
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	int getpoint(int x){
		x+=cor;
		int ans=0;
		while(1){
			if(x==0) break;
			if(vec[x]!=inf) ans=vec[x];
			x/=2;
		}
		
		return ans;
		
	}
	
	void pre(){
		for(int i=1;i<2*cor;i++){
			cout<<vec[i]<<" ";
			if(((i+1)&(-(i+1)))==i+1) cout<<endl;
		}
	}
	
};

//[a,b)‚Éx‚ðˆê—l‰ÁŽZ rangeadd(a,b,x)
//[a,b)‚Ì˜a getsum(a,b)

signed main(){
seg_rangeupd_getpoint SE;
	
	SE.shoki1();
//	for(int i=0;i<SE.cor;i++){
//		SE.vec[i+SE.cor]=i;
//	}
	SE.shoki2();
	
	
	int n,q;
	cin>>n>>q;
	
	for(int i=0;i<q;i++){
	int d,a,b,c;
		cin>>a;
		
		if(a==0){
			cin>>b>>c>>d;
			
			SE.rangeupd(b,c+1,d);
		}
		else{
			cin>>b;
			
			cout<<SE.getpoint(b)<<endl;
		}
		//SE.pre();
	}
	return 0;
}


