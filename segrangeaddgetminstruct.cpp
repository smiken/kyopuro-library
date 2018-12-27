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


struct seg_rangeupd_getsum{
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
	int inff=inf*1000000ll;
	
	vector<int> vec;
	vector<int> lazy;
	void shoki1(){
		vec.resize(2*cor+3, 0);
		lazy.resize(2*cor+3, inff);
	}
	void shoki2(){
		//lazy[1]=(1ll<<31)-1;
		//初期値
	}
		
	void chien(int k,int l,int r){
		if(lazy[k]==inff) return;
		if(l+1<r){
			vec[k]=lazy[k]*(r-l);
			lazy[2*k]=lazy[k];
			lazy[2*k+1]=lazy[k];
			lazy[k]=inff;
		}
		else {
			vec[k]=lazy[k];
			lazy[k]=inff;
		}
	}
	
	int rangeadd(int a,int b,int w, int k=1,int l=0,int r=-3){
		//[a,b)を wに変更
		if(r<0) r=cor;
		
		if(a<=l && r<=b){
			lazy[k]=w;
			chien(k,l,r);
			return vec[k];
		}
		if(r<=a || b<=l){
			chien(k,l,r);
			return vec[k];
		}
		
		chien(k,l,r);
//	cout<<k<<" "<<l<<" "<<r<<endl;
		int w1=rangeupd(a,b,w,k*2,l,(l+r)/2);
		int w2=rangeupd(a,b,w,k*2+1,(l+r)/2,r);
		vec[k]=w1+w2;
		return vec[k];
	}
	
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	
	int getadd(int a,int b,int k=1,int l=0,int r=-1){
		//[a,b)のminを取得
		if(r<0) r=cor;
		chien(k,l,r);
		if(r<=a || b<=l){// 区間外
			return 0;
		}
		
		if(a<=l && r<=b){// 完全含む
			
			return vec[k];
		}
		int w1=getmin(a,b,k*2,l,(l+r)/2);
		int w2=getmin(a,b,k*2+1,(l+r)/2,r);
		return (w1+w2);
	}
	void pre(){
		for(int i=1;i<2*cor;i++){
			cout<<vec[i]<<" ";
			if(((i+1)&(-(i+1)))==i+1) cout<<endl;
		}
	}
	
};

int main(){
segsum SE;
	
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
			cin>>d;
			
			cout<<SE.getnum(d)<<endl;
		}
	}
	return 0;
}


