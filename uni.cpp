struct unionfind{
	private:
	public:
	
vector<int> par,ranks,kosuu;
	
	void shoki(int N){
		par.resize(N+1,0);
		ranks.resize(N+1,0);
		kosuu.resize(N+1,1);
		for(int i=0;i<=N;i++){
			par[i]=i;
		}
	}

	int root(int x){
		return par[x]==x ? x : par[x]=root(par[x]);
	}

	bool same(int x,int y){
		return root(x)==root(y);
	}
	bool is_root(int x){
		return x==root(x);
	}
	void unite(int x,int y){
 		x=root(x);
	 	y=root(y);
		int xx=kosuu[x],yy=kosuu[y];
	 	if(x==y) return;
		if(ranks[x]<ranks[y]){
			par[x]=y;
			kosuu[y]=yy+xx;
		}
	 	else {
			par[y]=x;
			if(ranks[x]==ranks[y]) ranks[x]=ranks[x]+1;
	 		kosuu[x]=yy+xx;
	 	}
		return;
	}
};