using fps=vector<long long>;

fps mul(fps x,fps y){
	int xl=x.size();
	int yl=y.size();
	vector<long long> ans(xl+yl-1,0);
	
	for(int i=0;i<xl;i++)for(int j=0;j<yl;j++){
		ans[i+j]+=x[i]*y[j]%mod;
		if(ans[i+j]>=mod)ans[i+j]-=mod;
	}
	return ans;
}

// p(x)/q(x) k-th term
int BM(fps p,fps q,int k){
	while(k){
		while(q.size()&&q.back()==0)q.pop_back();
		while(p.size()&&p.back()==0)p.pop_back();
		
		int pl=p.size();
		int ql=q.size();
		
		if(pl==0)return 0;
		
		fps qm=q;
		for(int i=1;i<ql;i+=2)if(qm[i])qm[i]=mod-qm[i];
		
		fps e=mul(q,qm);
		
		// s/t
		
		fps s,t;
		for(int i=0;i<(int)e.size();i+=2)t.pb(e[i]);
		e=mul(p,qm);
		if(k%2==0){
			for(int i=0;i<(int)e.size();i+=2)s.pb(e[i]);
		}
		else{
			for(int i=1;i<(int)e.size();i+=2)s.pb(e[i]);	
		}
		
		swap(s,p);
		swap(t,q);
		k/=2;
		
	}
	return p[0]*beki(q[0],mod-2,mod)%mod;
}

// A[0],A[1],A[2],..,A[k-1] = first k terms of sequence
// P[0]*A[n] + P[1]*A[n-1] + P[2]*A[n-2] + P[3]*A[n-3] + ... + P[k]A[n-k] = 0
// k>=1
// P[0]!=0 P.back()!=0
// return <bunsi,bunbo>

pair<fps,fps> get_fps_form_linear(vector<long long>A,vector<long long>P){
	int k=A.size();
	int l=P.size();
	assert(k+1==l);
	
	fps e=mul(A,P);
	
	for(int i=0;i<k;i++)e.pop_back();
	
	return mp(e,P);
}

void solve(){
	
	fps p={0,1};
	fps q={mod-1,1,1};
	auto z=get_fps_form_linear(p,q);
	for(int i=0;i<20;i++){
		cout<<BM(z.first,z.second,i)<<endl;
	}

}