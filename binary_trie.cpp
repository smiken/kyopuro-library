// hightがdの頂点から生える子は数のdビット目を見る。葉のhightは-1
// root のhightは最大ビット数。dビット目が絶対0ならdでおｋ
typedef struct trie{
	
	int hight;
	int num;
	trie* child[2];
}trie;


trie* newtrie(int hight,int num){
	trie* TR=new trie;
	TR->hight=hight;
	TR->num=num;
	TR->child[0]=NULL;
	TR->child[1]=NULL;
	return TR;
}

void add_num(trie* root,int val){
	trie* node_now=root;
	while(1){
		node_now->num++;
		if(node_now->hight==-1)break;
		int next_bit=((val>>(node_now->hight))&1ll);
		if(node_now->child[next_bit]==NULL){
			node_now->child[next_bit]=newtrie(node_now->hight-1,0);
		}
		node_now=node_now->child[next_bit];
		
	}
	return;
}

int exist_num(trie* root, int val){//valがいくつ入っているか
	trie* node_now=root;
	while(1){
		if(node_now->num==0) return false;
		if(node_now->hight==-1)return node_now->num;
		int next_bit=((val>>(node_now->hight))&1ll);
		if(node_now->child[next_bit]==NULL){
			return 0;
		}
		node_now=node_now->child[next_bit];
	}
}

void delete_num(trie* root,int val,int kesukosuu=-1){
	int kesu;
	if(kesukosuu==-1) kesu=exist_num(root,val);
	else kesu=kesukosuu;
	if(kesu==0)return;

	trie* node_now=root;
	while(1){
		node_now->num-=kesu;
		if(node_now->hight==-1){
			return;
		}
		int next_bit=((val>>(node_now->hight))&1ll);
		if(node_now->child[next_bit]==NULL){
			cout<<"!!!!!! no such key!!"<<endl;
			assert(0);
		}
		node_now=node_now->child[next_bit];
	}
}

