vector<int> G[100002];
vector<int> G2[100002];


void saikisaiki(int u,int mae){

	for(int i=0;i<G[u].size();i++){
		if(G[u][i]==mae) continue;
		G2[u].push_back(G[u][i]);
		saikisaiki(G[u][i],u);
	}
	
}

void make_root(int root){
saikisaiki(root,-1);
return ;
}

// make_root( --- kokoni root wo ireru--     );