
typedef	struct node{
	
		node* rc;
		node* lc;
		int sub_size;
		int val; // これが数列の値
		int mi;
		int su;
	}node;


vector<int> vec;
typedef struct RBST{
 	private:
	public:


	
	
	 unsigned long long ran(){
 		  static unsigned long long x=123456789,y=362436069,z=521288629,w=88675123; 
   			 unsigned long long t; 
  			  t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) ); 
	}
	
	void fix(node *v){
		if(v==NULL) return;
		
		v->sub_size=1;
		if(v->lc!=NULL)v->sub_size+=v->lc->sub_size;
		if(v->rc!=NULL)v->sub_size+=v->rc->sub_size;
		
		// ここに子→親の操作を書く
		v->su=v->val;
		
		
		v->mi=v->val;
		v->mi=min(v->mi,mi(v->lc));
		
		v->mi=min(v->mi,mi(v->rc));
		return;
	}
	
	int siz(node* v){
		return v==NULL ? 0:v->sub_size;
	}
	
	int mi(node* v){
		return v==NULL? inf*100000ll:v->mi;
	}
	
	
	node* init(const vector<int> &vec,int l,int r){
		if(l>=r) return NULL;
		int c=(l+r)/2;
		node* v=new_node(vec[c]);
		
		v->lc = init(vec,l,c);
		v->rc = init(vec,c+1,r);
		fix(v);
		return v;
	}
	
	node* init(const vector<int> &vec){
		int n=vec.size();
		if(n==0) return NULL;
		
		node* v=init(vec,0,n);
		return v;
	}
	
	node* new_node(int val){
		node* no=new node;
		no->val=val;
		no->sub_size=1;
		no->mi=val;
		no->lc=NULL;
		no->rc=NULL;
		return no;
	}
	
	node* merge(node* l,node* r){
		if(l==NULL) return r;
		if(r==NULL) return l;
		
		unsigned int rr=ran();
		//cout<<rr<<endl;
		if(rr%(siz(l)+siz(r)) <(unsigned int )siz(l)){
			l->rc=merge(l->rc,r);
			fix(l);
			return l;
		}
		else{
			r->lc=merge(l,r->lc);
			fix(r);
			return r;
		}
	}
	
	pair<node* , node*> split(node* v,int k){
		if(v==NULL) return {NULL,NULL};
		
		//int n=v->sub_size;
		//[0,k),[k,n)に分割
		//0<=k<=n
		
		if(siz(v->lc) >= k){
			pair<node* , node*> t1 = split(v->lc,k);
			v->lc=t1.second;
			fix(v);
			return {t1.first,v};
			
		}
		else{
			pair<node*,node*> t1 = split(v->rc,k-siz(v->lc) -1);
			v->rc=t1.first;
			fix(v);
			return {v,t1.second};
		}
		
		
	}
	
	node* insert(node* v,int pos,int val){//pos 項目にvalを挿入 戻り値は新しいroot
		pair<node* , node*> t1=split(v,pos);
		
		return merge(t1.first,merge(new_node(val),t1.second));
	}
	
	pair<node*,int> erase(node *v,int pos){//pos項目を削除　戻り値は新しいrootと消した値
		pair<node* , node*> t1=split(v,pos);
		pair<node* , node*> t2=split(t1.second,1);
		return {merge(t1.first,t2.second),t2.first->val};
	}
	
	
	node* access(node *v,int k){
		if(siz(v->lc)==k) return v;
		if(siz(v->lc)>=k)return access(v->lc,k);
		else return access(v->rc,k-siz(v->lc)-1);
	}
	
	int lower_bound(node *root, int val){ //番兵が必要！！！！
		if(root==NULL) return 0;
		if(root->val>=val){
		//	cout<<val<<endl;
			return lower_bound(root->lc,val);
		}
		return 1+lower_bound(root->rc,val)+siz(root->lc);
	}
	
	int upper_bound(node *root, int val){ //番兵が必要！！！！
		if(root==NULL) return 0;
		if(root->val>val) return upper_bound(root->lc,val);
		
		return 1+upper_bound(root->rc,val)+siz(root->lc);
	}

	
	int rangemin(node* &v,int l,int r){
		if(v==NULL) return inf*10000ll;
		
		
		auto t1=split(v,r);
		auto t2=split(t1.first,l);
		int ima=mi(t2.second);
		
		v=merge(merge(t2.first,t2.second),t1.second);
		
		return ima;
	}
	
void update(node *v,int pos,int val){
	if(pos==siz(v->lc)){
		v->val=val;
		
		fix(v);
		return;
	}
	if(pos<siz(v->lc)){
		update(v->lc,pos,val);
		fix(v);
		return;
	}
	else{
		update(v->rc,pos-siz(v->lc)-1,val);
		fix(v);
		return;
	}
	
}
	
	
	
void sequence(node* v){//いまの数列
	
	if(v->lc!=NULL){
		sequence(v->lc);
	}
	//cout<<"   "<<(v->val)<<" "<<mi(v)<<endl;
	vec.pb(v->val);	
	if(v->rc!=NULL){
		sequence(v->rc);
	}
	
	
}
	
}RBST;
