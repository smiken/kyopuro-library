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
	
	int cor=(1<<18);
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
		
	int chien(int k,int len){
		if(lazy[k]==inff) return vec[k];
		if(k<cor){
			vec[k]=lazy[k]*len;
			lazy[2*k]=lazy[k];
			lazy[2*k+1]=lazy[k];
			lazy[k]=inff;
		}
		else {
			vec[k]=lazy[k];
			lazy[k]=inff;
		}
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
			chien(pos,len);
			len/=2;
		}
		
	}


	void rangeupd(int a,int b,int w){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		int lenaa=2*(a&-a);
		int lenbb=2*(b&-b);
		clear_chien(aa);
		clear_chien(bb);
		while(a<b){
			if(a&1){
				lazy[a]=w;
				a++;
			}
			if(b&1){
				b--;
				lazy[b]=w;
			}
			a/=2,b/=2;
		}

		while(aa>0 || bb>0){
			if(aa>bb){
				vec[aa]=chien(2*aa,lenaa/2)+chien(2*aa+1,lenaa/2);
				aa/=2;		
				lenaa*=2;
			}
			else if(aa<bb){
				vec[bb]=chien(2*bb,lenbb/2)+chien(2*bb+1,lenbb/2);
				bb/=2;	
				lenbb*=2;
			}
			else{
				vec[aa]=chien(2*aa,lenaa/2)+chien(2*aa+1,lenaa/2);
				aa/=2;		
				lenaa*=2;
				bb=aa,lenbb=aa;
			}
		}

	}

	int getsum(int a,int b){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		clear_chien(aa);
		clear_chien(bb);
	
		int ans=0;
		
		int len=1;
		while(a<b){
			if(a&1){
				ans+=chien(a,len);
				a++;
			}
			if(b&1){
				b--;
				ans+=chien(b,len);
			}
			a/=2,b/=2,len*=2;
		}
		return ans;
	}
	
	
	// 位置pからはじめて和がx以上になる位置．ない場合はcorが返る
	int lower_bound(int p,int x){
		p+=cor;
		int ima=0;
		bool fst=1;
		int len=1;
		while(1){
			while(!(p&1))p/=2,len*=2;
			if(fst)fst=0,clear_chien(p/2);
			if(ima+chien(p,len)>=x)break;//条件を満たさなくなる
			ima=ima+vec[p];
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			len/=2;
			if(ima+chien(p,len)<x){//条件を満たす
				ima+=vec[p];
				p++;
				chien(p,len);
			}
		}
	}
	
		// 位置pからはじめて和がxより大になる位置．ない場合はcorが返る
	int upper_bound(int p,int x){
		p+=cor;
		int ima=0;
		bool fst=1;
		int len=1;
		while(1){
			while(!(p&1))p/=2,len*=2;
			if(fst)fst=0,clear_chien(p/2);
			if(ima+chien(p,len)>x)break;//条件を満たさなくなる
			ima=ima+vec[p];
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			len/=2;
			if(ima+chien(p,len)<=x){//条件を満たす
				ima+=vec[p];
				p++;
				chien(p,len);
			}
		}
	}
	
};
