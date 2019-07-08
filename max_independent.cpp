struct MaxIndep{ 
	private:
	public:

	vector<bool> ok,miok;
	vector<int> an,dp;
	int hi,mi;
	vector<pa> e1,e2,e3;
 
	void makeok(){
		for(int i=0;i<(1<<hi);i++)ok[i]=true;
	
		for(auto t:e1){
			ok[(1<<t.first)+(1<<t.second)]=false;
		}
	
		for(int i=1;i<(1<<hi);i++){
			bool b=ok[i];
		
			for(int j=0;j<hi;j++){
				if(0==(i&(1<<j)))continue;
				if(ok[i-(1<<j)]==false)b=false;
			}
			ok[i]=b;
		}
		return;
	
	}
 
	void makean(){
		for(int i=0;i<(1<<hi);i++)an[i]=(1<<(mi))-1;
	
		for(auto t:e3){
			an[(1<<t.first)]^= (1<<(t.second-hi));
		}
	
		for(int i=0;i<(1<<hi);i++){
		
			for(int j=0;j<hi;j++){
				if(0==(i&(1<<j)))continue;
				an[i]=an[1<<j]&an[i-(1<<j)];
			}
		}
	
	}
 
	void makedp(){
		for(int i=0;i<(1<<mi);i++)miok[i]=true;
	
		for(auto t:e2){
			miok[(1<<t.first)+(1<<t.second)]=false;
		}
	
		for(int i=1;i<(1<<mi);i++){
			bool b=miok[i];
		
			for(int j=0;j<mi;j++){
				if(0==(i&(1<<j)))continue;
				if(miok[i-(1<<j)]==false)b=false;
			}
			miok[i]=b;
		}
	
		for(int i=0;i<(1<<mi);i++)if(miok[i]){
			int cnt=0;
			for(int  j=0;j<mi;j++)if(i&(1<<j))cnt++;
			dp[i]=cnt;
		}
	
		for(int i=0;i<(1<<mi);i++){
			for(int j=0;j<mi;j++){
				if(0==(i&(1<<j)))continue;
				dp[i]=max(dp[i],dp[i-(1<<j)]);
			}
		
		}
	}


	int solve(vector<vector<int>> ve){
		int n=ve.size();
		if(n==1) return 1;
		
		 hi=n/2;
   	 	 mi=n-hi;
		
		
		ok.resize(1<<mi,false);
		an.resize(1<<mi,0);
		dp.resize(1<<mi,0);
		miok.resize(1<<mi,false);
		
		for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(ve[i][j]){
    		if(j<hi)e1.pb(mp(i,j));
    		else if(i>=hi)e2.pb(mp(i-hi,j-hi));
    		else e3.pb(mp(i,j));
		}
	
	    makeok();
   		makean();
    	makedp();
    	
	    int ans=0;
	    	
	    for(int i=0;i<(1<<hi);i++)if(ok[i]){
	    	int cnt=0;
	    	for(int j=0;j<hi;j++)if(i&(1<<j))cnt++;
	    	
	    	ans=max(ans,cnt+dp[an[i]]);
	    }
		return ans;
	}


	
};