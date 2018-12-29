struct weight_unionfind{
	private:
	public:
	
vector<int> par,ranks,kosuu,dif;
	
	void shoki(int N){
		par.resize(N+1,0);
		ranks.resize(N+1,0);
		kosuu.resize(N+1,1);
		dif.resize(N+1,0);
		
		for(int i=0;i<=N;i++){
			par[i]=i;
		}
	}

	int root(int x){
		if(par[x]==x) return x;
		int r=root(par[x]);
		dif[x]+=dif[par[x]];
		par[x]=r;
		return r;
	}
	
	int poten(int x){
		root(x);
		return dif[x];
	}
	
	int diff(int x,int y){//po[y]-po[x]
		return poten(y)-poten(x);
	}
	
	bool same(int x,int y){
		return root(x)==root(y);
	}
	
	
	
	bool is_root(int x){
		return x==root(x);
	}
	void unite(int x,int y,int val){
		//矛盾がないかsameとdiffから確認してから使う！！
		//po[x]+val=po[y]
		int px=poten(x),py=poten(y);
		x=root(x);
	 	y=root(y);
		int xx=kosuu[x],yy=kosuu[y];
	 	if(x==y) return;
		if(ranks[x]<ranks[y]){
			val=py-px-val;
			par[x]=y;
			dif[x]=val;
			kosuu[y]=yy+xx;
		}
	 	else {
	 		val=val+px-py;
			par[y]=x;
	 		dif[y]=val;
			if(ranks[x]==ranks[y]) ranks[x]=ranks[x]+1;
	 		kosuu[x]=yy+xx;
	 	}
		return;
	}
};

void solve(){
	int n,m;
	cin>>n>>m;
	if(n==0 && m==0) exit(0);
	weight_unionfind UF;
	UF.shoki(n+1);
	for(int i=0;i<m;i++){
		string s;
		cin>>s;
		if(s=="!"){
			int a,b,w;
			cin>>a>>b>>w;
			UF.unite(a,b,w);
		}
		else{
			int a,b;
			cin>>a>>b;
			if(!UF.same(a,b)){
				cout<<"UNKNOWN"<<endl;
			}
			else cout<<UF.diff(a,b)<<endl;
		}
	}
}