
typedef struct trie{
	int moji;
	int id;
	int deb;
	trie* parent;
	trie* flink;
	trie* child[26];
}trie;

int cd=0;
trie* new_trie(){
	trie *p = new trie;
	p->id=-1;
	p->deb=cd;
	cd++;
	p->flink=NULL;
	p->parent=NULL;
	for(int i=0;i<26;i++) p->child[i]=NULL;
	return p;
}

void add_string(trie* root,string str, int str_id){
	int it=0;
	trie* trie_now=root; 
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
queue<trie*> queue_trie;
void make_fail(trie* root){
	root->parent=root;
	root->flink=root;
	queue_trie.push(root);
	while(queue_trie.size()){
		trie* trie_now=queue_trie.front();
		queue_trie.pop();
		
		for(int i=0;i<26;i++)if(trie_now->child[i]!=NULL) queue_trie.push(trie_now->child[i]);
		if(trie_now==root) continue;
		if(trie_now->parent==root){
			trie_now->flink=root;
			continue;
		}
		trie* itr=(trie_now->parent)->flink;
		while(1){
			if(itr==root){
				if(root->child[trie_now->moji] ==NULL){
					trie_now->flink=root;
					break;
				}
				else{
					trie_now->flink=root->child[trie_now->moji];
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
	
}

void shori(int id,int iti);
void string_find(trie* root,string str){
	int it=0;
	trie* trie_now=root;
	int l=str.length();
	int moji=str[0]-'a'; // komoji
	while(1){
		
		if(trie_now->id>=0){
			shori(trie_now->id,it);
			//cout<<trie_now->id<<" "<<it<<endl;
		}
		if(moji==-1){
			while(trie_now!=root){
				trie_now=trie_now->flink;
				if(trie_now->id>=0){
					shori(trie_now->id,it);
				//cout<<trie_now->id<<" "<<it<<endl;
				}
			}
			return;
			
		}
		while(trie_now->child[moji]==NULL){
			trie_now=trie_now->flink;
			if(trie_now->id>=0){
				//cout<<trie_now->id<<" "<<it<<endl;
				shori(trie_now->id,it);
			}
			if(trie_now==root) break;
		}
		
		if(trie_now->child[moji]!=NULL){
			trie_now=trie_now->child[moji];
		}
		it++;
		if(it==l) moji=-1;
		else moji=str[it]-'a';
		
		
	}
	
}

vector<int> G[200020];
vector<pair<int,string>> ve[320];
int ans[100020];
int v[5100];

void shori(int id,int iti){
//	cout<<id<<" "<<iti<<endl;
	G[iti].pb(id);
	//id は文字列番号
	//iti は終了位置
//	cout<<iti<<" "<<id<<endl;
}
string s[5100];
int dp[200020]={0};
signed main(){
		string str;
	cin>>str;
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
	cin>>s[i];
		ve[s[i].length()].pb(mp(i,s[i]));
	}
	for(int i=0;i<n;i++){
	cin>>v[i];
		
	}
	for(int i=1;i<=210;i++)if(ve[i].size()){
		trie* root;
		root=new_trie();
		for(auto v:ve[i]){
			//void add_string(trie* trie_now,string str, int str_id)
			// (root, string , id)
			add_string(root,v.second,v.first);
			// 全部addする
		}
		make_fail(root);

		string_find(root, str);
		// strにマッチするのを列挙
	// shori関数の中で処理している

	}
	
	for(int i=1;i<=str.length();i++){
		dp[i]=dp[i-1];
		for(auto vv:G[i]){
			dp[i]=max(dp[i],dp[i-s[vv].length()]+v[vv]);
		}
	}
	cout<<dp[str.length()]<<endl;
	
	return 0;
        }