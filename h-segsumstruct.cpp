struct segsum{
	//       1
	//   2        3
	// 4   5   6    7
	
	
	private:
	public:
	
	// 1<<15 = 32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int cor=(1<<18);
	
	vector<int> vec;
	
	void shoki1(){
		vec.resize(2*cor+3, 0);
	}
	void shoki2(){
		for(int i=cor-1;i>0;i--) vec[i]=vec[2*i]+vec[2*i+1];
	}
	void clear(){    
	    for(int i=0;i<(int)vec.size();i++)vec[i]=0;
    }
	
	void updadd(int x,int w){
		//x ���ڂ� w���Z
		x+=cor;
		vec[x]+=w;
		x/=2;
		while(x){
			vec[x]=vec[2*x]+vec[2*x+1];
			x/=2;
		}
	}
	
	void updchan(int x,int w){
		//x���ڂ�w�ɕύX
		x+=cor;
		vec[x]=w;
		while(x){
			x/=2;
			vec[x]=vec[2*x]+vec[2*x+1];
		}		
	}
	
	// [a,b)
	int sum(int a,int b){
		int hi=0,mi=0;
		a+=cor,b+=cor;
		while(a<b){
			if(a&1){
				hi=hi+vec[a];
				a++;
			}
			if(b&1){
				b--;
				mi=vec[b]+mi;
			}
			a/=2,b/=2;
		}
		return hi+mi;
	}
	
	// �ʒup����͂��߂Ęa��x�ȏ�ɂȂ�ʒu�D�Ȃ��ꍇ��cor���Ԃ�
	int lower_bound(int p,int x){
		p+=cor;
		int ima=0;
		while(1){
			while(!(p&1))p/=2;
			if(ima+vec[p]>=x)break;//�����𖞂����Ȃ��Ȃ�
			ima=ima+vec[p];
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			if(ima+vec[p]<x){//�����𖞂���
				ima+=vec[p];
				p++;
			}
		}
	}
	
	// �ʒup����͂��߂Ęa��x����ɂȂ�ʒu�D�Ȃ��ꍇ��cor���Ԃ�
	int upper_bound(int p,int x){
		p+=cor;
		int ima=0;
		while(1){
			while(!(p&1))p/=2;
			if(ima+vec[p]>x)break;//�����𖞂����Ȃ��Ȃ�
			ima=ima+vec[p];
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			if(ima+vec[p]<=x){//�����𖞂���
				ima+=vec[p];
				p++;
			}
		}
	}	
	
};

