
struct seg_chusho{
	//       1
	//   2        3
	// 4   5   6    7
	using Node =pa;
	using Sayo =pa;	
	
	private:
	public:
	
	// (1<<15)=32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int cor=(1<<18);

	
	


	// 遅延が貯まっていないときに保持する値
	Sayo S_id=mp(0,0);
	
	Node N_id=mp(0,0);
	
	Node node_merge(Node x,Node y){
		// x と yをマージする 区間和なら和

		// ここに実装する

	}
	Sayo merge_sayo(Sayo x,Sayo y){
		// 作用xの上から作用yを更にのっける

		// ここに実装する
		
		
		
	}
	
	Node node_sayo(Node x,Sayo y,int l,int r,int k){
		// 区間[l,r)のNode x に作用yを載せる
		// x == N_idの心配は基本的に不要
		// y == S_id も不必要


		
		// ここに実装する
		
		
	}
	
	
	vector<Node> vec;
	vector<Sayo> lazy;
	
	void shoki1(){
		//S_id,N_idが未定義ならここでやる
		
	
		vec.resize(2*cor+3, N_id);
		lazy.resize(2*cor+3,S_id);
	}
	void shoki2(){
		for(int i=cor-1;i>0;i--) vec[i]=node_merge(vec[2*i],vec[2*i+1]);
	}
	
	
	void chien(int k,int l,int r){
		if(lazy[k]==S_id) return;
		if(l+1<r){
			vec[k]=node_sayo(vec[k],lazy[k],l,r,k);
			lazy[2*k]=merge_sayo(lazy[2*k],lazy[k]);
			lazy[2*k+1]=merge_sayo(lazy[2*k+1],lazy[k]);
			lazy[k]=S_id;
		}
		else {
			vec[k]=node_sayo(vec[k],lazy[k],l,r,k);
			lazy[k]=S_id;
		}
	}
	
	Node rangeshori(int a,int b,Sayo w, int k=1,int l=0,int r=-3){
		
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
		Node w1=rangeshori(a,b,w,k*2,l,(l+r)/2);
		Node w2=rangeshori(a,b,w,k*2+1,(l+r)/2,r);
		vec[k]=node_merge(w1,w2);
		return vec[k];
	}

	
	

	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	
	Node getrange(int a,int b,int k=1,int l=0,int r=-1){
		
		if(r<0) r=cor;
		chien(k,l,r);
		if(r<=a || b<=l){// 区間外
			return N_id;
		}
		
		if(a<=l && r<=b){// 完全含む
			
			return vec[k];
		}
		Node w1=getrange(a,b,k*2,l,(l+r)/2);
		Node w2=getrange(a,b,k*2+1,(l+r)/2,r);
		return node_merge(w1,w2);

	}
	

};
