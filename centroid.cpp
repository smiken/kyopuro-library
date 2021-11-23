     
    vector<int> Tree[100020];
    // 寝つき木tree
     
     
    vector<pa3> centroid[100020];
    // index: 重心の番号
    // first: 新しくできた部分木の重心
    // second: 部分木のサイズ
    // third: 重心から直接生えている頂点番号
     
    int subtree_size[100020];
    bool locked[100020]={0};
    int oya[100020];
    int root_cen;
    int dfs_subtree_size(int node_id,int par_id){
    	int cn=1;
    	for(auto v:Tree[node_id])if(v!=par_id){
    		cn+=dfs_subtree_size(v,node_id);
    	}
    	subtree_size[node_id]=cn;
    	return cn;
    }
     
     
    void recurcive_center(int root,int parent,int dir){
    	int tree_size=subtree_size[root];
    	//cout<<root<<" "<<parent<<" "<<tree_size<<endl;
    	if(tree_size==1){
    			if(parent>=0)centroid[parent].pb((pa3){root,tree_size,dir});
    		else root_cen=root;
    		locked[root]=1;
    		return;
    	}
    	int r=root;
    	while(1){
    		
    		bool bo=true;
    		if(tree_size-subtree_size[r]>tree_size/2)bo=false;
    		int next_child=-1,maxnum=-1;
    		for(auto v:Tree[r])if(!locked[v]){
    			if(subtree_size[v]>tree_size/2) bo=false;
    			if(maxnum<subtree_size[v]){
    				next_child=v;
    				maxnum=subtree_size[v];
    			}
    		}
    		if(bo){
    			
    			if(parent>=0)centroid[parent].pb((pa3){r,tree_size,dir});
    			else root_cen=r;
    			locked[r]=1;
    			if(r!=root){
    				int r2=oya[r];
    				while(r2!=root){
    					subtree_size[r2]-=subtree_size[r];
    					r2=oya[r2];
    				}
    				subtree_size[root]-=subtree_size[r];
    			}
    			
    			if(r!=root)recurcive_center(root,r,oya[r]);
    			for(auto v:Tree[r])if(!locked[v]) recurcive_center(v,r,v);
    			return;
    		}
    		r=next_child;
    	}
    	
    }
     
     
    void make_centroid(int start_node){
    	//start_node がTreeの根になっているようにする
    	
    	dfs_subtree_size(start_node,-1);
    	//Tree no root ga start_node
    	for(int i=0;i<100020;i++)for(auto v:Tree[i])oya[v]=i;
    	oya[start_node]=start_node;
    	recurcive_center(start_node,-1,1);
    	
    	
    	// root_cenが重心分解木の根
    }