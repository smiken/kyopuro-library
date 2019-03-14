struct aho{
	
	// add_string(文字列, id)で検索パターンを追加 文字列は全部distinct!!
	// shori()で前処理
	// find_string(s) で文字列s内にあるパターンを列挙(YARU内でその処理を書く)
	
	
	
	typedef struct trie{
		int moji;
		int id;
//		int deb;
		trie* parent;
		trie* flink;
		trie* outer;
		trie* child[26];
	}trie;
    private:
    public:
	
	int cd=0;
	trie* new_trie(){
		trie *p = new trie;
		p->id=-1;
//		p->deb=cd;
		cd++;
		p->flink=NULL;
		p->parent=NULL;
		p->outer=NULL;
		for(int i=0;i<26;i++) p->child[i]=NULL;
		return p;
	}
	
	trie* ROOT;
	
	aho(){
		ROOT=new_trie();
		ROOT->moji=-1;
		
	}
	
	void add_string(string str, int str_id){
		int it=0;
		trie* trie_now=ROOT; 
		while(1){
			if(it==str.length()){
				trie_now->id=str_id;
				return;
			}
			int tugi=str[it]-'a'; // komoji
	
			if(trie_now->child[tugi] ==NULL){
				trie* p_new=new_trie();
				p_new->moji= tugi;
				p_new->parent=trie_now;
				trie_now->child[tugi]=p_new;
	
			}
			trie_now=trie_now->child[tugi];
	
			it++;
		}
	}
	
	void debug(){
		debug_dfs(ROOT);
	}
	void debug_dfs(trie* e){
//		cout<<e->deb<<" "<<e->id<<" "<<e->moji<<" ";
//		if(e->flink!=NULL)cout<<e->flink->deb<<" ";
		cout<<"c " ;
		for(int i=0;i<26;i++)if(e->child[i]!=NULL) cout<<i<<" ";
		cout<<endl;
		for(int i=0;i<26;i++)if(e->child[i]!=NULL) debug_dfs(e->child[i]);
		
	}
	
	queue<trie*> queue_trie;
	void shori(){
		ROOT->parent=ROOT;
		ROOT->flink=ROOT;
		queue_trie.push(ROOT);
		while(queue_trie.size()){
			trie* trie_now=queue_trie.front();
			queue_trie.pop();
		
			for(int i=0;i<26;i++)if(trie_now->child[i]!=NULL) queue_trie.push(trie_now->child[i]);
			if(trie_now==ROOT) continue;
			if(trie_now->parent==ROOT){
				trie_now->flink=ROOT;
				continue;
			}
			trie* itr=(trie_now->parent)->flink;
			while(1){
				if(itr==ROOT){
					if(ROOT->child[trie_now->moji] ==NULL){
						trie_now->flink=ROOT;
						break;
					}
					else{
						trie_now->flink=ROOT->child[trie_now->moji];
						break;
					}
				}
				else{
					if(itr->child[trie_now->moji] !=NULL){
						trie_now->flink=itr->child[trie_now->moji];
						break;
					}
					else itr=itr->flink;	
				}
			}
		//cout<<trie_now->deb<<" "<<trie_now->flink->deb<<endl;
		
		}
		
			while(queue_trie.size())queue_trie.pop();
		queue_trie.push(ROOT);
			
		while(queue_trie.size()){
			trie* trie_now=queue_trie.front();
			queue_trie.pop();
			for(int i=0;i<26;i++)if(trie_now->child[i]!=NULL)queue_trie.push(trie_now->child[i]);
			if(trie_now==ROOT) continue;
			if(trie_now->flink->id<0) trie_now->outer=trie_now->flink->outer;
			else{
				trie_now->outer=trie_now->flink;
			}
		}
	
	}

//void shori(int id,int iti);
	void string_find(string str){
		int it=0;
		trie* trie_now=ROOT;
		int l=str.length();
		int moji=str[0]-'a'; // komoji
		while(1){
		
			if(trie_now->id>=0){
				YARU(trie_now->id,it);
			//cout<<trie_now->id<<" "<<it<<endl;
			}
			
			trie* tr=trie_now->outer;
			while(tr!=NULL){
				YARU(tr->id,it);
				tr=tr->outer;
			}
			
			if(moji==-1){
				
				return;
			
			}
			while(trie_now->child[moji]==NULL){
				trie_now=trie_now->flink;
				
				if(trie_now==ROOT) break;
			}
		
			if(trie_now->child[moji]!=NULL){
				trie_now=trie_now->child[moji];
			}
			it++;
			if(it==l) moji=-1;
			else moji=str[it]-'a';
		}	
	}

	void YARU(int id,int iti){
//		cout<<iti<<" "<<id<<endl;
	//	G[iti].pb(id);
		G[iti]=max(G[iti],iti-(int)t[id].length()+1);
//	ans++;	
		//id は文字列番号
		//iti は終了位置

	}

};