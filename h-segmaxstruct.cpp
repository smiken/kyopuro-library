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
		vec.resize(2*cor+3, mp(1-(1ll<<31),0));
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
		x/=2;
		while(x){
			if(vec[2*x].first>=vec[2*x+1].first) vec[x]=vec[2*x];
			else vec[x]=vec[2*x+1];
			x/=2;
		}
	}
	
	void updchan(int x,int w){
		//x���ڂ�w�ɕύX
		x+=cor;
		vec[x].first=w;
		x/=2;
		while(x){
			if(vec[2*x].first>=vec[2*x+1].first) vec[x]=vec[2*x];
			else vec[x]=vec[2*x+1];
			x/=2;
		}
	}
	
	
	// [a,b)
	// k-th node
	// k no kukanha [l,r)
	pa segmax(int a,int b){
		a+=cor;
		b+=cor;
		pa ans=mp(1-(1ll<<31),-1);
		while(a<b){
			if(a&1){
				if(ans.first!=vec[a].first)ans=max(ans,vec[a]);
				else ans.second=min(ans.second,vec[a].second);
				a++;
			}
			if(b&1){
				b--;
				if(ans.first!=vec[b].first)ans=max(ans,vec[b]);
				else ans.second=min(ans.second,vec[b].second);
			}
			a/=2;
			b/=2;
		}
		return ans;
		
	}
	
	// �ʒu��p�ȏ�̗v�f�ŁC�l��x�ȏ�̂��̂ōł����ɂ������
	// �Ȃ��ꍇ��cor
	int lower_bound(int p,int x){
		p+=cor;
		while(1){
			while(!(p&1))p/=2;
			if(vec[p].first>=x)break;//�����𖞂����Ȃ��Ȃ�
			p++;
			if(p==(p&(-p))) return cor;
		}
		while(1){
			if(p>=cor) return p-cor;
			p*=2;
			if(vec[p].first<x){//�����𖞂���
				p++;
			}
		}
	}

	
};
