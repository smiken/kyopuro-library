// shoki(N)�ŏ�����

// add_edge(x,y) ��x->y�Ɏ}�ǉ�

// shori()�Ŏ��s

// same(x,y)�œ���������A�������ɓ����Ă邩
// id(x)�Œ��_x�̘A�������ԍ�


struct kyouren{
private:
	public:
int V;
	vector<vector<int>> gr,igr;
	vector<int> visit,gro,ban;
	void shoki(int N){
		V=N;
			gr.resize(N,{});
			igr.resize(N,{});
		visit.resize(N,0);
		gro.resize(N,0);
	}
	
	void add_edge(int x,int y){
		// 0<= x,y <N
		gr[x].pb(y);
		igr[y].pb(x);
	}
	
	
	
	void dfs(int i){
		if(visit[i]==0){
			visit[i]=1;
			for(int k=0;k<(int)gr[i].size();k++) dfs(gr[i][k]);
			ban.push_back(i);
		}
	}

	void idfs(int i,int h){
		if(visit[i]==0){
			visit[i]=1;
			gro[i]=h;
			for(int k=0;k<(int)igr[i].size();k++) idfs(igr[i][k],h);
		}
	}

	void shori(){
		for(int i=0;i<V;i++){
			dfs(i);
		}
		for(int i=0;i<V;i++) visit[i]=0;
		for(int i=V-1;i>=0;i--){
			idfs(ban[i],ban[i]);
		}
	}
		bool same(int x,int y){
			return gro[x]==gro[y];
		}
		
		int id(int x){
			return gro[x];
		}

	
	

};