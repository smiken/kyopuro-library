
// verify
// CF 813E
// JAG夏2018 day3D
// yukicoder 738 743
// AOJ 1549



// wavlet_matrix wm;
// wm.shoki1(ve,d)   <- 数列を表す vector とビット数 d つまりすべての項やクエリは1<<d 未満
// wm.shoki2()
// 
// 個数だけでなく和をも必要な時は3か所のコメントアウトを外す

struct BV{//O(n) words O(1) time
	
	private:
	public:
	int N;
	vector<int> RAN;
	vector<int> SEL1;
	vector<int> SEL0;
	int k0=0,k1=0;
	vector<bool> VEC;
	void shoki1(int NN){
		
		N=NN;
		
		VEC.resize(N,false);
		RAN.resize(N+1,0);
		
		
	}
	void setbit(int i){
		VEC[i]=1;
	}
	void resetbit(int i){
		VEC[i]=0;
	}
	void shoki2(){
		for(int i=0;i<N;i++){
			if(VEC[i]){
				RAN[i]=k1;
				k1++;
			}
			else{
				RAN[i]=k0;
				k0++;
			}
		}
		SEL1.resize(k1);
		SEL0.resize(k0);
		k0=0,k1=0;
		for(int i=0;i<N;i++){
			if(VEC[i]){
				SEL1[k1]=i;
				k1++;
			}
			else{
				SEL0[k0]=i;
				k0++;
			}
		}
	}
	
	
	int rank(int it){ return RAN[it];}
	int rank0(int it){
		if(it==N) return k0;
		if(VEC[it])return it-RAN[it];
		else return RAN[it];
	}
	int rank1(int it){
		if(it==N) return k1;
		if(VEC[it]==0)return it-RAN[it];
		else return RAN[it];
	}
	int select(int ko,bool b){
		if(b){
			if(ko>=k1)return -1;
			else return SEL1[ko];
		}
		else{
			if(ko>=k0)return -1;
			else return SEL0[ko];
		}
	}
	int access(int it) {return VEC[it];}

};

struct wavlet_matrix{
	private:
	public:
	
	int N;
	
	vector<int> VEC;
	int d;
	
	vector<BV> bv;
	vector<int> zero;
	
	//vector<vector<int>> rui;
	
	void shoki1(vector<int> &input,int D){
		VEC=input;
		N=input.size();
		d=D;
		bv.resize(d);
		zero.resize(d);
		/*
		/////////////////////////////////////////////////////////////
		rui.resize(d);
		/////////////////////////////////////////////////////////////
		*/
	}
	void shoki2(){
		
		for(int i=d-1;i>=0;i--){
			
			bv[i].shoki1(N);
			vector<int> mae,ato;
			for(int j=0;j<N;j++){
			
				if(VEC[j]&(1ll<<i)){
					
					ato.pb(VEC[j]);
					bv[i].setbit(j);
				}
				else{
					mae.pb(VEC[j]);
				}
			}
			
			zero[i]=(int)mae.size();
			bv[i].shoki2();
			
			mae.insert(mae.end(),ato.begin(),ato.end());
			
			/*
			/////////////////////////////////////////////////////////////
			rui[i]=mae;
			for(int j=1;j<N;j++)rui[i][j]+=rui[i][j-1];
			/////////////////////////////////////////////////////////////
			*/
			
			
			swap(VEC,mae);
		}
		
	}
	
	
	int access(int r){
		int ans=0;
		for(int i=d-1;i>=0;i--){
			if(bv[i].access(r)){
				ans+=(1ll<<i);
				r=zero[i]+bv[i].rank(r);
			}
			else{
				r=bv[i].rank(r);
			}
		}
		
		return ans;
	}
	
	int range_rank(int val, int l,int r){ // [l,r) にあるvalの個数
		
		
		
		for(int i=d-1;i>=0;i--){
			if(val&(1ll<<i)){
				r=zero[i]+bv[i].rank1(r);
				l=zero[i]+bv[i].rank1(l);
			}
			else{
				r=bv[i].rank0(r);
				l=bv[i].rank0(l);
			}
			
			
			if(l>=r) return 0;
		}
	
	return r-l;
	}
	
	int rank(int val,int pos){// 0,1,...,pos にあるvalの個数
		return range_rank(val,0,pos+1);
	}
	
	int select(int val,int kth){// kth 番目の valの位置 無いなら-1
		
		
		int l=0,r=N;
		for(int i=d-1;i>=0;i--){
			if(val&(1ll<<i)){
				r=zero[i]+bv[i].rank1(r);
				l=zero[i]+bv[i].rank1(l);
			}
			else{
				r=bv[i].rank0(r);
				l=bv[i].rank0(l);
			}
			
			
			if(l+kth>=r) return -1;
		}
		int pos=l+kth;
		//cout<<" "<<pos<<" "<<endl;;
		for(int i=0;i<d;i++){
			if(val&(1ll<<(i))){
			
				pos=bv[i].select(pos-zero[i],1);
			}
			else{
				pos=bv[i].select(pos,0);
			}
	//		cout<<pos<<endl;
		}
		return pos;
		
	}
	
	int x_th_min(int x,int l,int r){
		//区間[l,r)で小さいほうからk番目の値
		// 0 <= x < r-l
		// 0 <= l < r <= N
		int ans=0;
		
		
		for(int i=d-1;i>=0;i--){
			int t1=bv[i].rank0(l);
			int t2=bv[i].rank0(r);
			int z=t2-t1;
		//	cout<<x<<" "<<l<<" "<<r<<" "<<ans<<endl;
			if(z>x){
				l=t1,r=t2;
			}
			else{
				ans+=(1ll<<i);
				x-=z;
				l=zero[i]+l-t1;
				r=zero[i]+r-t2;
			}
		}
		return ans;
	}
	
	int range_min(int l,int r){
		return x_th_min(0,l,r);
	}
	
	int range_max(int l,int r){
		return x_th_min(r-l-1,l,r);
	}
	
	
	int range_count_prefix(int l,int r,int val){
		//区間[l,r)に存在する値が[0,val)な項の個数
		if(val<=0) return 0;
		if(l>=r)return 0;
		val--;
		//[0,val]に変更
		int ans=0;
		
		for(int i=d-1;i>=0;i--){
			int t1=bv[i].rank0(l);
			int t2=bv[i].rank0(r);
			
			if(val&(1ll<<i)){
				ans+=t2-t1;				
				l=zero[i]+l-t1;
				r=zero[i]+r-t2;
			}
			else{
				l=t1;
				r=t2;
			}
		}
		ans+=r-l;
		
		return ans;
		
	}
	
	int range_count(int l,int r,int vl,int vr){
		//区間[l,r)に存在する値が[vl,vr)な項の個数
		if(vr<=vl) return 0;
		if(r<=l) return 0;
		return range_count_prefix(l,r,vr)-range_count_prefix(l,r,vl);
		
	}		
	
	
	int range_bound_max(int l,int r,int val){
		//区間[l,r)に存在する値がval以下の中で最大の値
		//該当しない場合は -1
		
		if(l>=r) return -1;
		
		int dep=-1;
		int cl=-1;
		int cr=-1;
		int cur=0;
		
		int ima=0;
		for(int i=d-1;i>=0;i--){
			
			if(i==0){
				if(val&1){
					if(l<r){
						dep=0;
						cl=l,cr=r;
						cur=ima;
					}
				}
				else{
					int t1=bv[i].rank0(l);
					int t2=bv[i].rank0(r);
					if(t1<t2) return ima;
				}
				break;
				
			}
			
			if(val&(1ll<<i)){
				int t1=bv[i].rank0(l);
				int t2=bv[i].rank0(r);
				if(t1!=t2){
					dep=i-1;
					cl=t1,cr=t2;
					cur=ima;
				}
				l=zero[i]+l-t1;
				r=zero[i]+r-t2;
				ima+=(1ll<<i);
			}
			else{
				int t1=bv[i].rank0(l);
				int t2=bv[i].rank0(r);
				l=t1,r=t2;
				
			}
		}
		if(dep==-1) return -1;
		ima=cur;
		l=cl,r=cr;
		for(int i=dep;i>=0;i--){
			int t1=bv[i].rank0(l);
			int t2=bv[i].rank0(r);
			if(r-l>t2-t1){
				ima+=(1ll<<i);
				l=zero[i]+l-t1;
				r=zero[i]+r-t2;
			}
			else{
				l=t1,r=t2;
			}
		}
		
		return ima;
	}
	
	
	int range_bound_min(int l,int r,int val){
		//区間[l,r)に存在する値がval以上の中で最小の値
		//該当しない場合は -1
		if(l>=r) return -1;
		
		int dep=-1;
		int cl=-1;
		int cr=-1;
		int cur=0;
		
		int ima=0;
		for(int i=d-1;i>=0;i--){
			
			if(i==0){
				if((val&1)==0){
					if(l<r){
						dep=0;
						cl=l,cr=r;
						cur=ima;
					}
				}
				else{
					int t1=zero[i]+l-bv[i].rank0(l);
					int t2=zero[i]+r-bv[i].rank0(r);
					ima+=(1ll<<i);
					if(t1<t2) return ima;
				}
				break;
				
			}
			
			if((val&(1ll<<i))==0){
				int t1=bv[i].rank0(l);
				int t2=bv[i].rank0(r);
				int s1=zero[i]+l-t1;
				int s2=zero[i]+r-t2;
				if(s1<s2){
					dep=i-1;
					cl=s1,cr=s2;
					cur=ima+(1ll<<i);
				}
				l=t1,r=t2;
			}
			else{
				int t1=bv[i].rank0(l);
				int t2=bv[i].rank0(r);
				int s1=zero[i]+l-t1;
				int s2=zero[i]+r-t2;
				l=s1,r=s2;
				ima=ima+(1ll<<i);
				
			}
		}
	
		if(dep==-1) return -1;
		ima=cur;
		l=cl,r=cr;
		
		for(int i=dep;i>=0;i--){
			int t1=bv[i].rank0(l);
			int t2=bv[i].rank0(r);
			if(t2-t1==0){
				ima+=(1ll<<i);
				l=zero[i]+l-t1;
				r=zero[i]+r-t2;
			}
			else{
				l=t1,r=t2;
			}
			assert(l<r);
		}
		
		return ima;
	}
	
	
			/////////////////////////////////////////////////////////////
	/*
	int range_sum_prefix(int l,int r,int val){
		//区間[l,r)に存在する値が[0,val)な項の和
		if(val<=0) return 0;
		if(l>=r)return 0;
		val--;
		//[0,val]に変更
		int ans=0;
		
		for(int i=d-1;i>=0;i--){
			int t1=bv[i].rank0(l);
			int t2=bv[i].rank0(r);
			
			if(val&(1ll<<i)){
				ans+=(t2>0?rui[i][t2-1]:0)-(t1>0?rui[i][t1-1]:0);
				
				l=zero[i]+l-t1;;
				r=zero[i]+r-t2;
			}
			else{
				l=t1;
				r=t2;
			}
			
		}
		
		ans-=(l>0?rui[0][l-1]:0)-(r>0?rui[0][r-1]:0);
		
		return ans;
		
	}
	
	int range_sum(int l,int r,int vl,int vr){
		//区間[l,r)に存在する値が[vl,vr)な項の和
		
		if(vr<=vl) return 0;
		if(r<=l) return 0;
		return range_sum_prefix(l,r,vr)-range_sum_prefix(l,r,vl);
		
	}
	*/
			/////////////////////////////////////////////////////////////
};