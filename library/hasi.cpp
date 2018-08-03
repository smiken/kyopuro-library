
set<pa> hasi;
int pre[100100],lowlink[100100];
int counter_hasi=1;
void dfs_hasi(int r,int mae,vector<int> *graph){
	if(pre[r]>=0) return;
	pre[r]=counter_hasi;
	counter_hasi++;
	int f=pre[r];
	int oyacnt=0;
	for(int i=0;i<graph[r].size();i++){
	//	cout<<r<<" "<<graph[r][i]<<endl;
		if(graph[r][i]==mae){
			oyacnt++;
			if(oyacnt==1) continue; 
		}
		if(pre[graph[r][i]]<0){
			dfs_hasi(graph[r][i],r,graph);
			f=min(f,lowlink[graph[r][i]]);
			//cout<<r<<" "<<graph[r][i]<<" "<<pre[graph[r][i]]<<" "<<lowlink[graph[r][i]]<<endl;
			if(pre[graph[r][i]]==lowlink[graph[r][i]]){
			//	cout<<" "<<graph[r][i]<<endl;
				
				//ryouhoukou
			//	hasi.insert(mp(r,graph[r][i]));
			//	hasi.insert(mp(graph[r][i],r));
				
				//katahou
				if(r<graph[r][i])	hasi.insert(mp(r,graph[r][i]));
				else hasi.insert(mp(graph[r][i],r));	
				
			}
		}
		else{
			f=min(f,pre[graph[r][i]]);
		}
		
	}
	lowlink[r]=f;
	
	return ;
}

void hashi_kenshutu(int V,vector<int> *graph){// V=tyoutensuu
	for(int i=0;i<=V;i++)pre[i]=-1,lowlink[i]=-1;
	counter_hasi=1;
	
	for(int i=0;i<V;i++){//0-index
		if(pre[i]==-1)dfs_hasi(i,i,graph);
	}
	
	return;
}

   signed main(){
 int n,m;
   	cin>>n>>m;
   	
   	for(int i=0;i<m;i++){
   		int y,yy;
   		cin>>y>>yy;
   		y--;
   		yy--;
   		G[y].pb(yy);
   		G[yy].pb(y);
 
   	}
   	hashi_kenshutu(n,G);
   	// set<pa> hasi ni hasiga haitteiru (a,b) tadasi a<b
  
   	return 0;
        }