struct Segmax{
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
	
	vector<pa> vec;
	
	void shoki1(){
		
		vec.resize(2*cor+3, mp(0,0));
		for(int i=cor;i<2*cor;i++)vec[i].second=i-cor;
	}
		void shoki2(){
			for(int i=cor-1;i>0;i--) {
				if(vec[2*i].first>=vec[2*i+1].first) vec[i]=vec[2*i];
				else vec[i]=vec[2*i+1];
			}
		}
		
	void updadd(int x,int w){
		//x ���ڂ� w���Z
		x+=cor;
		vec[x].first+=w;
		while(1){
			x/=2;
			if(x==0) break;
			if(vec[2*x].first>=vec[2*x+1].first) vec[x]=vec[2*x];
			else vec[x]=vec[2*x+1];
		}
		
	}
	
	void updchan(int x,int w){
		//x���ڂ�w�ɕύX
		
		x+=cor;
		vec[x].first=w;
		
		while(1){
			x/=2;
			if(x==0) break;
			if(vec[2*x].first>=vec[2*x+1].first) vec[x]=vec[2*x];
			else vec[x]=vec[2*x+1];
		}
		
	}
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	pa segmax(int a,int b,int k=1,int l=0,int r=-10){
		if(r<0)r=cor;
		
	//	cout<<a<<" "<<b<<" "<<k<<" "<<l<<" "<<r<<endl;
		
		if(a<=l && r<=b){
			return vec[k];
		}
		if(r<=a || b<=l){
			return mp(-(1ll<<31),-1);
		}
		
		pa v1=segmax(a,b,k*2,l,(l+r)/2),v2=segmax(a,b,k*2+1,(l+r)/2,r);
		
		if(v1.first>=v2.first)return v1;
		else return v2;
	}
	
	// leftmost �u���b�Nk�͒l��b�ȏ�̂Ƃ��ɁC���̃u���b�N�ɑ�����l��b�ȏ�̂��̂̂����ł����̂��̂�Ԃ�
	pa leftmost(int b, int k,int l,int r){
		if(r-l==1) return vec[k]; 
		if(vec[2*k].first>=b) return leftmost(b,2*k,l,(l+r)/2);
		else return leftmost(b,2*k+1,(l+r)/2,r);
		
	}
	
	// bound �C���f�b�N�X��a�ȏ�Œl��b�ȏ�̍ŏ��̂��̂�Ԃ�
	// �Ȃ��Ȃ�(-1,-1)
	pa bound(int a,int b,int k=-1,int l=0,int r=0){
		if(k<0){
			k=cor+a;
			l=a,r=a+1;
		}
	//	cout<<k<<" "<<l<<" "<<r<<endl;
		if(vec[k].first>=b) return leftmost(b,k,l,r);
		if(r==cor) return mp(-1,-1);
		if(k%2==0){
			int dd=r-l;
			return bound(a,b,k+1,r,r+dd);
		}
		else{
			int dd=r-l;
			return bound(a,b,k/2+1,r,r+2*dd);
			
		}
	}
	
};