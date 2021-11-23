
struct edge{
	int to,cap,num,moto;
};

struct push_relabel{
	
	int n;
	vector<vector<edge>>ZANYO;
	vector<vector<int>> active;
	vector<int> excess;
	vector<int> label;
	
	void shoki(int N){
		n=N;
		ZANYO.resize(n,vector<edge>());
		active.resize(2*n+10,vector<int>());
		excess.resize(n,0);
		label.resize(n,0);
	}
	
	void add_edge(int s_point,int t_point, int capa){ // s!=t 0<=s,t<n cap>=0
		ZANYO[s_point].pb((edge){t_point,capa,(int)ZANYO[t_point].size(),0});
		ZANYO[t_point].pb((edge){s_point,0,(int)ZANYO[s_point].size()-1,1});
	}
	
	int max_frow(int s,int t){
		
		// first preflow
		for(auto &v:ZANYO[s])if(v.moto==0){
			excess[s]-=v.cap;
			excess[v.to]+=v.cap;
			ZANYO[v.to][v.num].cap=v.cap;
			v.cap=0;
		}
		
		// first label;
		label[s]=n;
		
		for(int i=0;i<n;i++)if(i!=s&&i!=t)if(excess[i]>0)active[0].pb(i);
		
		int max_label=0;
		
		while(1){
			while(active[max_label].size()==0){
				max_label--;
				if(max_label<0)break;
			}
			if(max_label<0)break;
			
			int u=active[max_label].back();
			
			for(;pos[u]<ZANYO[u].size();pos[u]++){
				edge v=ZANYO[u][pos[u]];
				if(v.cap==0)continue;
				assert(label[v.to]>=label[u]-1);
				if(label[v.to]>=label[u])continue;
				if(excess[u]>v.cap){
					ZANYO[v.to][v.num].cap+=v.cap;
					ZANYO[u][pos[u]].cap=0;
					if(excess[v.to]==0){
						active[label[v.to]].pb(v.to);
					}
					excess[v.to]+=v.cap;
					excess[u]-=v.cap;
				}
				else{
					ZANYO[v.to][v.num].cap+=excess[u];
					ZANYO[u][pos[u]].cap-=excess[u];
					
					if(excess[v.to]==0){
						active[label[v.to]].pb(v.to);
					}
					excess[v.to]+=excess[u];
					excess[u]=0;
					active[max_label].pop_back();
					owari=1;
					break;
				}
				
			}
			if(owari)continue
			
			// relabel
			int w=-1;
			for(auto v:ZANYO[u])if(v.cap>0)w=max(w,label[v.to]);
			assert(w>=0);
			active[max_label].pop_back();
			max_label=w+1;
			active[max_label].pb(u);
			
		}
		return excess[t];
		
	}
	
	void fukugen(){
		for(int i=0;i<n;i++)for(auto v:ZANYO[i])if(v.moto==1){
			cout<<v.to<<" "<<i<<" "<<v.cap<<endl;
		}
	}
}



