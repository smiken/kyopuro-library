
typedef struct trie{
	char moji;
	int las;
	int hukasa;
	int child;
	vector< trie* > ne;
}trie;


void makeend(trie* t){
	(*t).las=1;
	return;
}

trie* maketrie(){
	trie *p;
	p=new trie;
	p->las=0;
	p->child=0;
	return p;
}

void addstring(trie* t,string s,int ichi){
//	cout<<ichi<<endl;
	int d=s.length();
	t->child ++;
	if(d==ichi) return;
	
	int l=((*t).ne).size();
	for(int i=0;i<l;i++){
		if((*(((*t).ne)[i])).moji==s[ichi]){
			if(d==ichi+1) makeend((((*t).ne)[i]));
			addstring((((*t).ne)[i]),s,ichi+1);
			return;
		}
		
		
	}
 	trie *p;
	p=maketrie();
	p->hukasa=ichi+1;
	p->moji=s[ichi];
	(*t).ne.push_back(p);
	if(d==ichi+1) makeend((((*t).ne)[l]));
	addstring((((*t).ne)[l]),s,ichi+1);
			
	
	return;
}



void checktrie(trie *p){
	cout<< p->moji <<" "<<p->hukasa<<" "<<p->child;
	int l=((*p).ne).size();
	for(int i=0;i<l;i++){
		cout<<" "<<((*p).ne)[i]->moji;
	}
	if(p->las==1) cout<<" last";
	cout<<endl;
	for(int i=0;i<l;i++){
		checktrie(((*p).ne)[i]);
	}
}

signed main(){
	
	trie *nekko;
	
	nekko=maketrie();
	nekko->moji='^';
	
	
	addstring(nekko,"abra",0);
	addstring(nekko,"abram",0);
	addstring(nekko,"abroad",0);
	addstring(nekko,"arrow",0);
	
	checktrie(nekko);
	return 0;
}
