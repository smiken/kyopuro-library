	//segsum2Dの使い方
	// shoki1(x方向最大値,y方向最大値)
	// precomp(x,y) 値の入るクエリの来る場所を全部一度教える(範囲和クエリの座標はいらない)
	// shoki2();
	// この3つを必ずやる
	
	// クエリは
	//rangesum(x1,x2,y1,y2)
	//point_add(x,y,val)
	//point_change(x,y,val) (これは定数倍遅いので注意)



	// verify
	
	// CF 1093E
	// CF 848C
	// JAG2018合宿Day3D
	// ABC016D
	
	
struct BIT{

	
	private:
	public:
	

	
	vector<int> vec;
	
	
	void shoki1(int siz){
		cor=1;
		while(cor<=siz+1) cor*=2;
		
		vec.resize(cor+3, 0);
	}
	
	void updadd(int a,int w){
		a++;
		//a 項目に w加算
		for(int x=a;x<=cor; x+=(x&(-x))) vec[x] +=w;
		
		
	}
	int sum(int a){
		int ret=0;
 		 for(int x=a;x>0; x-=(x&(-x))) ret +=vec[x];
 		 return ret;
	}

	int sum(int a,int b){
		a++;
		b++;
		return sum(b-1)-sum(a-1);
	}
	
};

struct segsum2D{

	private:
	public:
	
	int corx=1;
	int cory=1;
	
	vector<BIT> seg;
	vector<vector<int>> index;
	
	void shoki1(int sizx,int sizy){
		while(sizx>=corx)corx*=2;
		while(sizy>=cory)cory*=2;
		
		seg.resize(2*corx+3);
		index.resize(2*corx+3);
	}
	
	void pre(int x,int y,int k=1,int l=0,int r=-1){
		if(r<0) r=corx;
	//	cout<<k<<" "<<l<<" "<<r<<" "<<x<<" "<<y<<endl;
		index[k].pb(y);
		if(r-l==1) return;
		int med=(l+r)/2;
		if(x<med) pre(x,y,2*k,l,med);
		else pre(x,y,2*k+1,med,r);
	}
	
	
	void precomp(int x,int y){
		pre(x,y);
	}
	
	void shoki2(){
		for(int i=1;i<2*corx;i++){
			sort(index[i].begin(),index[i].end());
			index[i].erase(unique(index[i].begin(),index[i].end()),index[i].end());
			seg[i].shoki1((int)index[i].size());
		}
	}
	
	void point_add(int x,int y,int val){// 点加算
		int k=x+corx;
		
		while(k){
			int id=lower_bound(index[k].begin(),index[k].end(),y)-index[k].begin();
		
			seg[k].updadd(id,val);
			k/=2;
		}
	}
	
	void point_change(int x,int y,int val,int k=1,int l=0,int r=-1){// 点変更
	
		int moto=rangesum(x,x+1,y,y+1);
		point_add(x,y,val-moto);
	}
	
	int rangesum(int x1,int x2,int y1,int y2,int k=1,int l=0,int r=-1){//[x1,x2) [y1,y2)の和
	
		if(r<0) r=corx;
		if(x1<=l && r<=x2){
			
			int id1=lower_bound(index[k].begin(),index[k].end(),y1)-index[k].begin();
			
			int id2=lower_bound(index[k].begin(),index[k].end(),y2)-index[k].begin();
		//	cout<<l<<" "<<r<<" "<<seg[k].sum(id1,id2)<<endl;
				return seg[k].sum(id1,id2);
		}
		if(r<=x1||x2<=l){
		//	cout<<l<<" "<<r<<" "<<0<<endl;
			return 0;
		}
		
		int v1=rangesum(x1,x2,y1,y2,2*k,l,(l+r)/2);
		int v2=rangesum(x1,x2,y1,y2,2*k+1,(l+r)/2,r);
		return v1+v2;
		
	}
	
};