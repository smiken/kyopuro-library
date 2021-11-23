// shoki(N)で初期化

// add_edge(x,y) でx<->yに枝追加 x!=y 多重辺OK
// [0,N)でグラフは連結

// shori()で実行

// vector<int> bridge に橋の枝番号が入っている．
// vector<vector<int>> Cgr に縮約したグラフの連結リストが入っている．
// component_sizeに連結成分の個数が入っている．
// getid(x)で頂点xの成分番号

int dp[100020][20];
struct hasi{
private:
	int cnt=0;
	public:
	int V;
	vector<vector<int>> gr,Cgr;
	vector<pa> eda;
	vector<int> eda_shu,imo,oya_eda,bridge,id;
	vector<bool> vis;
	int component_size;
	void shoki(int N){
		V=N;
		imo.resize(N,0);
		gr.resize(N,{});
		vis.resize(N,false);
		id.resize(N);
		oya_eda.resize(N);
	}
	
	void add_edge(int x,int y){
		eda.pb(mp(x,y));
		eda_shu.pb(0);
		gr[x].pb(cnt);
		gr[y].pb(cnt);
		cnt++;
	}
	
	
	
	void dfs(int r){
		vis[r]=1;
		for(auto v:gr[r]){
			if(eda_shu[v]!=0)continue;
			int to=r^eda[v].first^eda[v].second;
			if(vis[to]){
				eda_shu[v]=2;
				imo[r]++;
				imo[to]--;
			}
			else{
				eda_shu[v]=1;
				if(eda[v].first!=r)swap(eda[v].first,eda[v].second);
				oya_eda[to]=v;
				dfs(to);
			}
		}
	}
	
	int imo_dfs(int r){
		for(auto v:gr[r])if(eda_shu[v]==1 && eda[v].first==r)imo[r]+=imo_dfs(eda[v].second);
		if(r!=0 && imo[r]==0){
			bridge.pb(oya_eda[r]);
		}
		return imo[r];
	}
	
	void dfs_group(int r){
		for(auto v:gr[r])if(eda_shu[v]==1 && eda[v].first==r){
			if(imo[eda[v].second]==0){
				cnt++;
				id[eda[v].second]=cnt;
				// 熱木々
				Cgr[id[r]].pb(cnt);
				// 子から親へ
				Cgr[cnt].pb(id[r]);
				
				
			}
			else id[eda[v].second]=id[r];
			dfs_group(eda[v].second);
		}
	}
	

	
	void shori(){
		dfs(0);
		imo_dfs(0);
		
		
		component_size=bridge.size()+1;
		cnt=0;
		id[0]=0;
		Cgr.resize(component_size,{});
		dfs_group(0);
		
		vector<int>().swap(eda_shu);
		vector<int>().swap(imo);
		vector<int>().swap(oya_eda);
		vector<int>().swap(bridge);
		vector<pa>().swap(eda);
		
		
		
		
	}

	int getid(int r){
		return id[r];
	}
	

};





// shoki(N)で初期化

// add_edge(x,y) でx<->yに枝追加 x!=y 多重辺OK
// [0,N)でグラフは連結でなくてOK

// shori()で実行

// vector<int> bridge に橋の枝番号が入っている．
// vector<vector<int>> Cgr に縮約したグラフの連結リストが入っている．
// component_sizeに連結成分の個数が入っている．
// getid(x)で頂点xの成分番号



struct hasi{
private:
	int cnt=0;
	public:
	int V;
	vector<vector<int>> gr,Cgr;
	vector<pa> eda;
	vector<int> eda_shu,imo,oya_eda,bridge,id;
	vector<bool> vis;
	int component_size;
	void shoki(int N){
		V=N;
		imo.resize(N,0);
		gr.resize(N,{});
		vis.resize(N,false);
		id.resize(N);
		oya_eda.resize(N);
	}
	
	void add_edge(int x,int y){
		eda.pb(mp(x,y));
		eda_shu.pb(0);
		gr[x].pb(cnt);
		gr[y].pb(cnt);
		cnt++;
	}
	
	
	
	void dfs(int r){
		vis[r]=1;
		for(auto v:gr[r]){
			if(eda_shu[v]!=0)continue;
			int to=r^eda[v].first^eda[v].second;
			if(vis[to]){
				eda_shu[v]=2;
				imo[r]++;
				imo[to]--;
			}
			else{
				eda_shu[v]=1;
				if(eda[v].first!=r)swap(eda[v].first,eda[v].second);
				oya_eda[to]=v;
				dfs(to);
			}
		}
	}
	
	int imo_dfs(int r,int root){
		for(auto v:gr[r])if(eda_shu[v]==1 && eda[v].first==r)imo[r]+=imo_dfs(eda[v].second,root);
		if(r!=root && imo[r]==0){
			bridge.pb(oya_eda[r]);
		}
		return imo[r];
	}
	
	void dfs_group(int r){
		for(auto v:gr[r])if(eda_shu[v]==1 && eda[v].first==r){
			if(imo[eda[v].second]==0){
				cnt++;
				id[eda[v].second]=cnt;
				// 熱木々
				Cgr[id[r]].pb(cnt);
				// 子から親へ
				Cgr[cnt].pb(id[r]);
				
				
			}
			else id[eda[v].second]=id[r];
			dfs_group(eda[v].second);
		}
	}
	

	
	void shori(){
		vector<int>comp_daihyou;
		for(int i=0;i<V;i++)if(vis[i]==0){
			comp_daihyou.pb(i);
			dfs(i);
		}
		//dfs(0);
		
		for(auto v:comp_daihyou){
			imo_dfs(v,v);
		}
		
		
		component_size=bridge.size()+comp_daihyou.size();
		Cgr.resize(component_size,{});
		
		//cnt=0;
		//id[0]=0;
		
		//dfs_group(0);
		cnt=-1;
		for(auto v:comp_daihyou){
			cnt++;
			id[v]=cnt;
			dfs_group(v);
		}
		
		vector<int>().swap(eda_shu);
		vector<int>().swap(imo);
		vector<int>().swap(oya_eda);
		vector<int>().swap(bridge);
		vector<pa>().swap(eda);
		
		
		
		
	}

	int getid(int r){
		return id[r];
	}
	

};
