
struct edge{
	int to,cap,num,moto;
};


struct dinic{

	int n;
	vector<vector<edge>>ZANYO;
	vector<int> label,dokomade;
	queue<pa> qu_bfs;
	
	void shoki(int N){
		n=N;
		ZANYO.resize(n,vector<edge>());
		label.resize(n);
		dokomade.resize(n);
	}
	
	void add_edge(int s_point,int t_point, int capa){// (s!=t)  s-->t
		
			ZANYO[s_point].pb((edge){t_point,capa,(int)ZANYO[t_point].size(),0});
			ZANYO[t_point].pb((edge){s_point,0,(int)ZANYO[s_point].size()-1,1});
	}

	void bfs_dinic(int s_point){
		for(int i=0;i<n;i++)label[i]=-1;
		while(qu_bfs.size())qu_bfs.pop();
		qu_bfs.push(mp(s_point,0));
		while(qu_bfs.size()){
			pa z=qu_bfs.front();
			qu_bfs.pop();
			if(label[z.first]>=0)continue;
			label[z.first]=z.second;
			for(auto &v:ZANYO[z.first]){
				if(v.cap==0) continue;
				if(v.cap<0){
					cout<<"error"<<endl;
					exit(0);
				}
				if(label[v.to]>=0) continue;
				
				qu_bfs.push(mp(v.to,z.second+1));
			}
		}
		return;
	}

	int dfs_dinic(int s_point,int t_point, int ima_flow){
		if(s_point==t_point) return ima_flow;
		while(1){
			if(dokomade[s_point]>=ZANYO[s_point].size()) break;
			int edanum=dokomade[s_point];
			if(ZANYO[s_point][edanum].cap<0){
				cout<<"minus"<<endl;
				exit(0);
			}
			if(ZANYO[s_point][edanum].cap<=0 || label[s_point]+1!=label[ZANYO[s_point][edanum].to] ){
				dokomade[s_point]++;
				continue;
			}
			int W=dfs_dinic(ZANYO[s_point][edanum].to,t_point,min(ZANYO[s_point][edanum].cap,ima_flow));
			if(W>0){
				ZANYO[s_point][edanum].cap-=W;
				ZANYO[ZANYO[s_point][edanum].to][ZANYO[s_point][edanum].num].cap+=W;
				return W;
			}
			dokomade[s_point]++;
		}
		return 0;
	}

	int max_flow_dinic(int s_point,int t_point){
		int jougen=inf*1000000000ll; //容量の最大値
		int ans_flow=0;
		while(1){
		
			bfs_dinic(s_point);
			if(label[t_point]==-1) break;
			for(int i=0;i<n;i++)dokomade[i]=0;
			while(1){
				int ima_flow=dfs_dinic(s_point,t_point,jougen+1); 
				if(ima_flow==0)break;
				ans_flow+=ima_flow;
			}
		}
		return ans_flow;
	}


	/////////
	void fukugen(){
		for(int i=0;i<n;i++)for(auto v:ZANYO[i])if(v.moto==1){
			cout<<v.to<<" "<<i<<" "<<v.cap<<endl;
		}
	}
	/////////

};


struct flow_with_lowerbound{
	
	dinic di;
	int n;
	int low_sum=0;
	vector<int> need;
	
	void shoki(int N){
		n=N+2;
		di.shoki(n);
		need.resize(N,0);
	}
	
	void add_edge(int s_point,int t_point, int lower, int upper){
		need[t_point]+=lower;
		need[s_point]-=lower;
		low_sum+=lower;
		di.add_edge(s_point,t_point,upper-lower);
	}
	
	int max_flow(int s,int t){
		for(int i=0;i<n-2;i++){
			if(need[i]>0)di.add_edge(n,i,need[i]);
			if(need[i]<0)di.add_edge(i,n+1,-need[i]);
		}
		int ST=di.max_flow_dinic(n,n+1);
		int sT=di.max_flow_dinic(s,n+1);
		int St=di.max_flow_dinic(n,t);
		
		if(ST+St<low_sum || ST+sT<low_sum){
			return -1;
		}
		return sT+di.max_flow_dinic(s,t);
	}
	
};

// 下限付き最大流
// 使い方
// flow_with_lowerbound fw;
// fw.shoki(V) // 0 <= x < V
// fw.add_edge(s,t,low,up)  // low<=up
// fw.max_flow(s,t)
