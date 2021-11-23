struct seg_rangeadd_getmin{
    //       1
    //   2        3
    // 4   5   6    7
     
     
    private:
    public:
     
    // (1<<15)=32768
    // 1<<16 = 65536
    // 1<<17 = 131072
    // 1<<18 = 262144
	// node k : [ (cor/msb)*(k&(msb-1)) , (cor/msb)*((k&(msb-1))+1))
	// where msb=(1<<(31-__builtin_clz(k)));
	
	     
    int cor=(1<<18);
    int inff=inf*1000000ll;
     
    vector<int> vec;
    vector<int> lazy;
    void shoki1(){
        vec.resize(2*cor+3, 0);
        lazy.resize(2*cor+3, 0);
    }
    void shoki2(){
        //lazy[1]=(1ll<<31)-1;
        //初期値
    }
         
    int chien(int k,int len){
        if(lazy[k]==0) return vec[k];
        if(k<cor){
            vec[k]+=lazy[k];
            lazy[2*k]+=lazy[k];
            lazy[2*k+1]+=lazy[k];
            lazy[k]=0;
        }
        else {
            vec[k]+=lazy[k];
            lazy[k]=0;
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
	
	void rangeadd(int a,int b,int w){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		int lenaa=2*(a&-a);
		int lenbb=2*(b&-b);
//	clear_chien(aa);
//	clear_chien(bb);
		while(a<b){
			if(a&1){
				lazy[a]+=w;
				a++;
			}
			if(b&1){
				b--;
				lazy[b]+=w;
			}
			a/=2,b/=2;
		}

		while(aa>0 || bb>0){
			if(aa>bb){
				vec[aa]=min(chien(2*aa,lenaa/2),chien(2*aa+1,lenaa/2));
				aa/=2;		
				lenaa*=2;
			}
			else if(aa<bb){
				vec[bb]=min(chien(2*bb,lenbb/2),chien(2*bb+1,lenbb/2));
				bb/=2;	
				lenbb*=2;
			}
			else{
				vec[aa]=min(chien(2*aa,lenaa/2),chien(2*aa+1,lenaa/2));
				aa/=2;		
				lenaa*=2;
				bb=aa,lenbb=lenaa;
			}
		}

	}
	
    int getmin(int a,int b){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		clear_chien(aa);
		clear_chien(bb);
	
		int ans=inf*1000000000ll;
		
		int len=1;
		while(a<b){
			if(a&1){
				ans=min(ans,chien(a,len));
				a++;
			}
			if(b&1){
				b--;
				ans=min(ans,chien(b,len));
			}
			a/=2,b/=2,len*=2;
		}
		return ans;
	}
	
	// 位置がp以上の要素で，値がx以下のもので最も左にあるもの
	// ない場合はcor
	int lower_bound(int p,int x){
		p+=cor;
		bool fst=1;
		int len=1;
		while(1){
			while(!(p&1))p/=2;
			if(fst)fst=0,clear_chien(p/2);
			if(chien(p,len)<=x)break;//条件を満たさなくなる
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			if(chien(p,len)>x){//条件を満たす
				p++;
				chien(p,len);
			}
		}
	}
	
     
};
 
 
 
struct seg_rangeadd_getmax{
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
        lazy.resize(2*cor+3, 0);
    }
    void shoki2(){
        //lazy[1]=(1ll<<31)-1;
        //初期値
    }
         
    int chien(int k,int len){
        if(lazy[k]==0) return vec[k];
        if(k<cor){
            vec[k]+=lazy[k];
            lazy[2*k]+=lazy[k];
            lazy[2*k+1]+=lazy[k];
            lazy[k]=0;
        }
        else {
            vec[k]+=lazy[k];
            lazy[k]=0;
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
	
	void rangeadd(int a,int b,int w){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		int lenaa=2*(a&-a);
		int lenbb=2*(b&-b);
//	clear_chien(aa);
//	clear_chien(bb);
		while(a<b){
			if(a&1){
				lazy[a]+=w;
				a++;
			}
			if(b&1){
				b--;
				lazy[b]+=w;
			}
			a/=2,b/=2;
		}

		while(aa>0 || bb>0){
			if(aa>bb){
				vec[aa]=max(chien(2*aa,lenaa/2),chien(2*aa+1,lenaa/2));
				aa/=2;		
				lenaa*=2;
			}
			else if(aa<bb){
				vec[bb]=max(chien(2*bb,lenbb/2),chien(2*bb+1,lenbb/2));
				bb/=2;	
				lenbb*=2;
			}
			else{
				vec[aa]=max(chien(2*aa,lenaa/2),chien(2*aa+1,lenaa/2));
				aa/=2;		
				lenaa*=2;
				bb=aa,lenbb=lenaa;
			}
		}

	}
	
    int getmax(int a,int b){
		a+=cor,b+=cor;
		int aa=a/(a&(-a))/2;
		int bb=b/(b&(-b))/2;
		clear_chien(aa);
		clear_chien(bb);
	
		int ans=-inf*1000000000ll;
		
		int len=1;
		while(a<b){
			if(a&1){
				ans=max(ans,chien(a,len));
				a++;
			}
			if(b&1){
				b--;
				ans=max(ans,chien(b,len));
			}
			a/=2,b/=2,len*=2;
		}
		return ans;
	}
	
	// 位置がp以上の要素で，値がx以上のもので最も左にあるもの
	// ない場合はcor
	int lower_bound(int p,int x){
		p+=cor;
		bool fst=1;
		int len=1;
		while(1){
			while(!(p&1))p/=2;
			if(fst)fst=0,clear_chien(p/2);
			if(chien(p,len)>=x)break;//条件を満たさなくなる
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			if(chien(p,len)<x){//条件を満たす
				p++;
				chien(p,len);
			}
		}
	}
	
     
};
 