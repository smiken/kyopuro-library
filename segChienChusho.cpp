
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

	
	


	// �x�������܂��Ă��Ȃ��Ƃ��ɕێ�����l
	Sayo S_id=mp(0,0);
	
	Node N_id=mp(0,0);
	
	Node node_merge(Node x,Node y){
		// x �� y���}�[�W���� ��Ԙa�Ȃ�a

		// �����Ɏ�������

	}
	Sayo merge_sayo(Sayo x,Sayo y){
		// ��px�̏ォ���py���X�ɂ̂�����

		// �����Ɏ�������
		
		
		
	}
	
	Node node_sayo(Node x,Sayo y,int l,int r,int k){
		// ���[l,r)��Node x �ɍ�py���ڂ���
		// x == N_id�̐S�z�͊�{�I�ɕs�v
		// y == S_id ���s�K�v


		
		// �����Ɏ�������
		
		
	}
	
	
	vector<Node> vec;
	vector<Sayo> lazy;
	
	void shoki1(){
		//S_id,N_id������`�Ȃ炱���ł��
		
	
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
		if(r<=a || b<=l){// ��ԊO
			return N_id;
		}
		
		if(a<=l && r<=b){// ���S�܂�
			
			return vec[k];
		}
		Node w1=getrange(a,b,k*2,l,(l+r)/2);
		Node w2=getrange(a,b,k*2+1,(l+r)/2,r);
		return node_merge(w1,w2);

	}
	

};
