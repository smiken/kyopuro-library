struct seg_chusho{
	//       1
	//   2        3
	// 4   5   6    7
	using Node =string;
	using Sayo =string;	
	
	private:
	public:
	
	// 1<<15 = 32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int cor=(1<<18);
	// node k : [ (cor/msb)*(k&(msb-1)) , (cor/msb)*((k&(msb-1))+1))
	// where msb=(1<<(31-__builtin_clz(k)));
	
	
	// 遅延が貯まっていないときに保持する値
	Sayo S_id="";
	Node N_id="";


	
	Node node_merge(Node x,Node y){
		// x と yをマージする 区間和なら和
		
		// ここに実装する
		return x+"/"+y;
		if(x==N_id)return y;
		if(y==N_id)return x;
	//	return x+y;
	}
	Sayo merge_sayo(Sayo x,Sayo y){
		// 作用xの上から作用yを更にのっける
		return x+y;
		// ここに実装する
		if(x==S_id)return y;
		if(y==S_id)return x;
		
		
	}
	
	Node node_sayo(Node x,Sayo y,int k){
		// 区間[l,r)のNode k に作用yを載せる
	// node k : [ (cor/msb)*(k&(msb-1)) , (cor/msb)*((k&(msb-1))+1))
	// where msb=(1<<(31-__builtin_clz(k)));
	// len = cor>>(31-__builtin_clz(k));
		//int len=cor>>(31-__builtin_clz(k));
		string ans="";
		for(char c:x){
			if(c=='/')ans+=y;
			ans+=c;
		}
	ans+=y;
		return ans;
		
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
	

	Node chien(int k){
		if(lazy[k]==S_id) return vec[k];
		if(k<cor){
			lazy[k*2]=merge_sayo(lazy[k*2],lazy[k]);
			lazy[k*2+1]=merge_sayo(lazy[k*2+1],lazy[k]);
		}
		vec[k]=node_sayo(vec[k],lazy[k],k);
		lazy[k]=S_id;
		return vec[k];
	}
	
	void  clear_chien(int r){
		// 1 ~ r までの遅延を開放する
		if(r==0)return;
		int f=31-__builtin_clz(r);
		int pos=0;
		int len=cor;
		for(int i=f;i>=0;i--){
			pos*=2;
			pos+=!!(r&(1<<i));
			chien(pos);
			len/=2;
		}
		
	}


	void rangeshori(int a,int b,Sayo w){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		clear_chien(aa);
		clear_chien(bb);
		while(a<b){
			if(a&1){
				lazy[a]=merge_sayo(lazy[a],w);
				a++;
			}
			if(b&1){
				b--;
				lazy[b]=merge_sayo(lazy[b],w);
			}
			a/=2,b/=2;
		}

		while(aa>0 || bb>0){
			if(aa>bb){
				vec[aa]=node_merge(chien(2*aa),chien(2*aa+1));
				aa/=2;		
			}
			else if(aa<bb){
				vec[bb]=node_merge(chien(2*bb),chien(2*bb+1));
				bb/=2;	
			}
			else{
				vec[aa]=node_merge(chien(2*aa),chien(2*aa+1));
				aa/=2;		
				bb/=2;
			}
		}

	}


	Node getrange(int a,int b){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		clear_chien(aa);
		clear_chien(bb);
		Node hi=N_id;
		Node mi=N_id;
			
		while(a<b){
			if(a&1){
				hi=node_merge(hi,chien(a));
				a++;
			}
			if(b&1){
				b--;
				mi=node_merge(chien(b),mi);
			}
			a/=2,b/=2;
		}
		return node_merge(hi,mi);
	}
	
	// 位置pから広げていき初めてboundary_check()がtrueになる場所を返す．ない場合はcorが返る
	
	bool boundary_check(Node x){

	}
	
	int lower_bound(int p,int x){
		p+=cor;
		Node ima=N_id;
		bool fst=1;
		while(1){
			while(!(p&1))p/=2;
			if(fst)fst=0,clear_chien(p/2);
			if(boundary_check(node_merge(ima,chien(p))))break;//条件を超える
			ima=node_merge(ima,vec[p]);
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			if(!boundary_check(node_merge(ima,chien(p)))){//条件を超えない
				ima=node_merge(ima,vec[p]);
				p++;
				chien(p);
			}
		}
	}

};
