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

void make_hl(int N,vector<int> *GG){//���_��1,2,...,n
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
// �g���� make_hl(N,G2) (N�͒��_��)
// �O���tG2��1-indexed ��N���_


//G2��1-indexed
//1~n�����ɕ��ׂ����̂� rin[0,1,2,...,n)
// ���_ v ����̂ǂ��ɂ���̂��� in[v]   in[1,2,...,n]={0,1,...,n-1}
// v��subtree�Ɋ܂܂���Ԃ�[in[v],out[v])
// v���܂�heavy��̈�ԏ��nxt[v]
//v���܂�heavy��̈�ԉ���down[v]
// heavy���[in[nxt[v]],...,in[v]]�Ɉ�l���삷���OK
// v��heavy^path�̂Ă��؂� <=> v==nxt[v]
