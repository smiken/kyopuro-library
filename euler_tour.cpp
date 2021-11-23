 
// 連結成分ごとに準オイラーグラフかオイラーグラフであることが必要
// 頂点は0以上N未満
// add_edgeで枝追加　多重辺自己辺OK
// merge_pathまでやると各連結成分ごとのオイラーパス(閉路)をvector<vector<int>> answerに格納
// 閉路は A-B-C(-A)でn個のみ出力(最後の次に先頭が来る)

// verify CF1186F 1152E  確認不十分!!

//.メモリを食うのでdefine int long long を外すべき
struct euler{

	
	
	private:
	public:
	//vector<int> degree;
	vector<int> eda;
	vector<int> visited_path;
	vector<vector<pa>> GG;
	vector<int> odd_node;
	vector<vector<int>> paths;
	vector<vector<int>> answer;
	vector<vector<int>> contain_path;
	int N;
	euler(int NN){
		N=NN;
		GG.resize(N);
	//	degree.resize(N);
		contain_path.resize(N);
	}
	void add_edge(int x,int y){// 0 <= x,y < N
		int eda_num=eda.size();
		eda.pb(0);
		GG[x].pb({y,eda_num});
		GG[y].pb({x,eda_num});
		//degree[x]++,degree[y]++;
	}
	
	bool dfs_greedy(int r,int path_id,bool first_node=true){
	//	cout<<r<<" "<<path_id<<endl;
		while(GG[r].size()){
			pa z=GG[r].back();
			if(eda[z.second]){
				GG[r].pop_back();
				continue;
			}
			break;
		}
		if(GG[r].size()==0){
			if(first_node) return false;
			else{
				if(paths.back()[0]==r)return true;
				contain_path[r].pb(path_id);
				paths.back().pb(r);
				return true;
			}
		}
		else{
			if(first_node){
				paths.pb(vector<int>());
			}
			
			contain_path[r].pb(path_id);
			paths.back().pb(r);
			eda[GG[r].back().second]=1;
			dfs_greedy(GG[r].back().first,path_id,false);
			return true;
		}
 
	}
	
	void merge_path(int id,bool first_path=true,int node_id=-1){
		visited_path[id]=true;
		if(first_path)answer.pb(vector<int>());
		
		int siz=paths[id].size();
		int st=0;
		if(!first_path){
			for(int i=0;i<siz;i++)if(paths[id][i]==node_id){
				st=i;
				break;
			}
		}
		for(int i=st;i<st+siz;i++){
			int v=paths[id][i%siz];
		
			line1:;
			while(contain_path[v].size()){
				if(visited_path[contain_path[v].back()]){
					contain_path[v].pop_back();
					continue;
				}
				break;
			}
			if(contain_path[v].size()){
				merge_path(contain_path[v].back(),false,v);
				goto line1;
			}
			
			answer.back().pb(v);
		}
	}
	
	void solve(){
		
		for(int i=0;i<N;i++)if(GG[i].size()%2)odd_node.pb(i);
		int path_num=0;
		for(auto v:odd_node){
			bool f = dfs_greedy(v,path_num++);
			if(!f) path_num--;
		}
		for(int i=0;i<N;i++){
			bool f = dfs_greedy(i,path_num++);
			if(!f) path_num--;
		}
		eda.clear();
		odd_node.clear();
		visited_path.resize(path_num);
	//	cout<<path_num<<endl;
		for(int i=0;i<path_num;i++)if(!visited_path[i])merge_path(i);
	}
	void output2(){
		for(auto V:paths){
			for(auto v:V)cout<<v<<" ";
			cout<<endl;
		}
		
	}
	void output(){
		for(auto V:answer){
			for(auto v:V)cout<<v<<" ";
			cout<<endl;
		}
		
	}
};