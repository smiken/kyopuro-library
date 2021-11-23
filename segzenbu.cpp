// 範囲を一様にa倍してb足す操作．区間maxminsumに対応

//要はupdate, addにも対応して3種の区間クエリに回答可能


struct seg_zenbu{
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
	int max_inf=inf*1000000ll;
	int min_inf=-max_inf;
	
	
	struct node{
		int mi;
		int ma;
		int su;
	};
	
	struct sayo{
		int a;
		int b;
		
		
		bool operator==(sayo v){
			return a==v.a && b==v.b;
		}
	
	};
	
	sayo yuni={1,0};
	
	node node_merge(node x,node y){
		return {min(x.mi,y.mi),max(x.ma,y.ma),x.su+y.su};
	}
	
	
	vector<node> vec;
	vector<sayo> lazy;
	void shoki1(){
		vec.resize(2*cor+3, {0,0,0});
		lazy.resize(2*cor+3,yuni);
	}
	void shoki2(){
		for(int i=cor-1;i>0;i--) vec[i]=node_merge(vec[2*i],vec[2*i+1]);
	}
	
	sayo merge_sayo(sayo x,sayo y){
		int t1=x.a*y.a;
		int t2=x.b*y.a+y.b;
		return {t1,t2};
	}
	
	node node_sayo(node x,sayo y,int l,int r){
		if(y.a==0){
			return {y.b,y.b,y.b*(r-l)};
		}
		else if(y.a>0){
			return {x.mi*y.a+y.b,x.ma*y.a+y.b,x.su*y.a+(r-l)*y.b};
		}
		else{
			return {x.ma*y.a+y.b,x.mi*y.a+y.b,x.su*y.a+(r-l)*y.b};
		}
	}
		
	void chien(int k,int l,int r){
		if(lazy[k]==yuni) return;
		if(l+1<r){
			vec[k]=node_sayo(vec[k],lazy[k],l,r);
			lazy[2*k]=merge_sayo(lazy[2*k],lazy[k]);
			lazy[2*k+1]=merge_sayo(lazy[2*k+1],lazy[k]);
			lazy[k]=yuni;
		}
		else {
			vec[k]=node_sayo(vec[k],lazy[k],l,r);
			lazy[k]=yuni;
		}
	}
	
	node rangeshori(int a,int b,sayo w, int k=1,int l=0,int r=-3){
		//[a,b)を w.a倍してw.bをたす
		if(r<0) r=cor;
		
		if(a<=l && r<=b){
			lazy[k]=merge_sayo(lazy[k],w);
			chien(k,l,r);
			return vec[k];
		}
		if(r<=a || b<=l){
			chien(k,l,r);
			return vec[k];
		}
		
		chien(k,l,r);
//	cout<<k<<" "<<l<<" "<<r<<endl;
		node w1=rangeshori(a,b,w,k*2,l,(l+r)/2);
		node w2=rangeshori(a,b,w,k*2+1,(l+r)/2,r);
		vec[k]=node_merge(w1,w2);
		return vec[k];
	}
	
	////////////////////////
	////////////////////////
	//       区間 update ///
	////////////////////////	
	////////////////////////
	
	void range_upd(int l,int r,int v){
			rangeshori(l,r,(sayo){0,v});
	}
	
	
	
	////////////////////////
	////////////////////////
	//       区間 add    ///
	////////////////////////	
	////////////////////////
	
	
	void range_add(int l,int r,int v){
			rangeshori(l,r,(sayo){1,v});
	}
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	
	int getmin(int a,int b,int k=1,int l=0,int r=-1){
		//[a,b)のminを取得
		if(r<0) r=cor;
		chien(k,l,r);
		if(r<=a || b<=l){// 区間外
			return max_inf;
		}
		
		if(a<=l && r<=b){// 完全含む
			
			return vec[k].mi;
		}
		int w1=getmin(a,b,k*2,l,(l+r)/2);
		int w2=getmin(a,b,k*2+1,(l+r)/2,r);
		return min(w1,w2);
	}
	
	
	int getmax(int a,int b,int k=1,int l=0,int r=-1){
		//[a,b)のminを取得
		if(r<0) r=cor;
		chien(k,l,r);
		if(r<=a || b<=l){// 区間外
			return min_inf;
		}
		
		if(a<=l && r<=b){// 完全含む
			
			return vec[k].ma;
		}
		int w1=getmax(a,b,k*2,l,(l+r)/2);
		int w2=getmax(a,b,k*2+1,(l+r)/2,r);
		return max(w1,w2);
	}
	
	int getsum(int a,int b,int k=1,int l=0,int r=-1){
		if(r<0) r=cor;
		chien(k,l,r);
		if(r<=a || b<=l){// 区間外
			return 0;
		}
		
		if(a<=l && r<=b){// 完全含む
			
			return vec[k].su;
		}
		int w1=getsum(a,b,k*2,l,(l+r)/2);
		int w2=getsum(a,b,k*2+1,(l+r)/2,r);
		return (w1+w2);
	}
};
