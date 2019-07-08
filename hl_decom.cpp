int cont=0;
int sz[200020];
int in[200020];
int rin[200020];
int nxt[200020];
int out[200020];
int down[200020];
void dfs_sz(int v,vector<int> *GG){
    sz[v]=1;
    for(auto &u :GG[v]){
        dfs_sz(u,GG);
        sz[v]+=sz[u];
        if(sz[u]>sz[GG[v][0]])swap(u,GG[v][0]);
    }
}
void dfs_hld(int v,vector<int> *GG){
    if(v==1) nxt[v]=1;
    in[v]=cont;
    cont++;
    rin[in[v]]=v;
    for(auto u:GG[v]){
        if(u==GG[v][0])nxt[u]=nxt[v];
        else nxt[u]=u;
        dfs_hld(u,GG);
    }
    out[v]=cont;
}

void make_hl(int N,vector<int> *GG){//頂点は1,2,...,n
	dfs_sz(1,GG);
	dfs_hld(1,GG);
	bool itt=1;
	for(int i=N-1;i>=0;i--){
		if(itt){
			down[rin[i]]=rin[i];
		}
		else{
			down[rin[i]]=down[rin[i+1]];
		}
		if(rin[i]==nxt[rin[i]])itt=1;
		else itt=0;
	}
}
// 使い方 make_hl(N,G2) (Nは頂点数)
// グラフG2は1-indexed でN頂点


//G2は1-indexed
//1~nを一列に並べたものが rin[0,1,2,...,n)
// 頂点 v が列のどこにあるのかが in[v]   in[1,2,...,n]={0,1,...,n-1}
// vのsubtreeに含まれる区間は[in[v],out[v])
// vを含むheavy列の一番上はnxt[v]
//vを含むheavy列の一番下はdown[v]
// heavy列で[in[nxt[v]],...,in[v]]に一様操作すればOK
// vがheavy^pathのてっぺん <=> v==nxt[v]
