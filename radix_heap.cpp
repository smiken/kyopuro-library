struct radix_heap32{

	private:
	public:
	using T=pa;
	
	struct kv{
		int key;
		T val;
	};
	
	
	int sz=0;
	int mn=0;
	
	deque<kv> VEC[33];
	
	
	int msb(int r){
		if(r==0)return 0;
		return 32-__builtin_clz(r);
	}
	
	int size(){
		return sz;
	}
	
	void push(int key,T val){
		assert(mn<=key);
		VEC[msb(mn^key)].pb((kv){key,val});
		sz++;
	}

	kv pop(){
		assert(sz>0);
		if(!VEC[0].size()){
			int it=-1;
			for(int i=1;i<=32;i++)if(VEC[i].size()){
				it=i;
				break;
			}
			assert(it>0);
			int mi=2147483647;
			for(auto v:VEC[it])mi=min(mi,v.key);
			while(VEC[it].size()){
				VEC[msb(mi^VEC[it].back().key)].pb(VEC[it].back());
				VEC[it].pop_back();
			}
		}
		
		
		kv ans=VEC[0].back();
		mn=ans.key;
		sz--;
		VEC[0].pop_back();
		return ans;

	}
	
};


struct radix_heap64{

	private:
	public:
	using T=int;
	
	struct kv{
		ll key;
		T val;
	};
	

	int sz=0;
	ll  mn=0ll;
	
	deque<kv> VEC[65];
	
	
	int msb(ll r){
		if(r==0)return 0;
		return 64-__builtin_clzll((ll)r);
	}
	
	int size(){
		return sz;
	}
	
	
	
	void push(ll key,T val){
		VEC[msb(mn^key)].pb((kv){key,val});
		sz++;
	}
	

	
	kv pop(){
		assert(sz>0);
		if(!VEC[0].size()){
			int it=-1;
			for(int i=1;i<=64;i++)if(VEC[i].size()){
				it=i;
				break;
			}
			ll mi=9223372036854775807ll;

			for(auto v:VEC[it])mi=min(mi,v.key);
			
			while(VEC[it].size()){
				VEC[msb(mi^VEC[it].back().key)].pb(VEC[it].back());
				VEC[it].pop_back();
			}
			
			
		}
		
		
		
		kv ans=VEC[0].back();
		mn=ans.key;
		sz--;
		VEC[0].pop_back();
		
		return ans;

	}
	
};