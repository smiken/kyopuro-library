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
#define int long long

using namespace std;


struct seg_addsum_getsum{
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
	vector<int> lazy;
	void shoki1(){
		vec.resize(2*cor+3, 0);
		lazy.resize(2*cor+3, 0);
	}
	void shoki2(){
			for(int i=cor-1;i>0;i--) vec[i]=vec[2*i]+vec[2*i+1];
	}
		
	void chien(int k,int l,int r){
		if(lazy[k]==0) return;
		if(l+1<r){
			lazy[k*2]+=lazy[k]/2;
			lazy[k*2+1]+=lazy[k]/2;
		}
		vec[k]+=lazy[k];
		lazy[k]=0;
	}
	
	void rangeadd(int a,int b,int w, int k=1,int l=0,int r=-3){
		//[a,b)‚É w‰ÁŽZ
		if(r<0) r=cor;
		chien(k,l,r);
		if(a<=l && r<=b){
			lazy[k]+=w*(r-l);
			
			chien(k,l,r);
			return ;
		}
		if(r<=a || b<=l){
			return ;
		}
		
		rangeadd(a,b,w,k*2,l,(l+r)/2);
		rangeadd(a,b,w,k*2+1,(l+r)/2,r);
		vec[k]=vec[2*k]+vec[2*k+1];
		return ;
	}
	
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	int getsum(int a,int b,int k=1,int l=0,int  r=-3){
		if(r<0) r=cor;
		chien(k,l,r);
		if(a<=l && r<=b){
			return vec[k];
		}
		if(r<=a || b<=l){
			return 0;
		}
		return getsum(a,b,k*2,l,(l+r)/2)+getsum(a,b,k*2+1,(l+r)/2,r);
		
	}
	
	void pre(){
		for(int i=1;i<2*cor;i++){
			cout<<vec[i]<<"/"<<lazy[i]<<" ";
			if(((i+1)&(-(i+1)))==i+1) cout<<endl;
		}
	}
	
};

//[a,b)‚Éx‚ðˆê—l‰ÁŽZ rangeadd(a,b,x)
//[a,b)‚Ì˜a getsum(a,b)

signed main(){
seg_addsum_getsum SE;
	
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
			
			SE.rangeadd(b,c+1,d);
		}
		else{
			cin>>b;
			
			cout<<SE.getsum(b,b+1)<<endl;
		}
	}
	return 0;
}


