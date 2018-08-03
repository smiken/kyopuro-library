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


struct segsum{
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
		vec.resize(2*cor+3, 0);

	}
		void shoki2(){
			
		}
		
	void rangeadd(int a,int b,int w, int k=1,int l=0,int r=-3){
		//[a,b)‚É w‰ÁŽZ
	if(r<0) r=cor;
		
		if(a<=l && r<=b){
			vec[k]+=w;
			return ;
		}
		if(r<=a || b<=l){
			return ;
		}
		
		rangeadd(a,b,w,k*2,l,(l+r)/2);
		rangeadd(a,b,w,k*2+1,(l+r)/2,r);
		return ;
	}
	
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	int getnum(int x){
		x+=cor;
		int ans=0;
		while(1){
			if(x==0) return ans;
			ans+=vec[x];
			
			x/=2;
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


