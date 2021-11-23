
struct combination{ // îCà”mod <10^9 ,n<10^6
	
	private:
    public:
	int P;
	int N;
	vector<int> sosu,ko,seki;
	vector<vector<pa>> memo;
	void shoki(int P_mod,int n){// mod Ç∆ n ÇÃè„å¿Çó^Ç¶ÇÈ
		P=P_mod;
		N=n;
		int nn=P;
		for(int i=2;i*i<=P;i++)if(nn%i==0){
			int k=0;
			int g=1;
			while(nn%i==0){
				k++;
				nn/=i;
				g*=i;
			}
			sosu.pb(i);
			ko.pb(k);
			seki.pb(g);
		}
		if(nn>1){
			sosu.pb(nn);
			ko.pb(1);
			seki.pb(nn);
		}
		memo.resize((int)sosu.size(),{});
		for(int i=0;i<sosu.size();i++){
			memo[i].pb(mp(1,0));
			for(int j=1;j<=N;j++){
				memo[i].pb(memo[i].back());
				int jj=j;
				while(jj%sosu[i]==0){
					memo[i].back().second++;
					jj/=sosu[i];
				}
				memo[i].back().first*=jj;
				memo[i].back().first%=seki[i];
			}
		}
	}
	

	int binom(int n,int k){
		vector<pa> hoge;
		for(int i=0;i<sosu.size();i++){
			pa bunsi=memo[i][n];
			pa bunbo=memo[i][k];
			pa bunbo2=memo[i][n-k];
			bunbo.first=bunbo.first*bunbo2.first%seki[i];
			bunbo.second+=bunbo2.second;
			if(bunsi.second-bunbo.second>=ko[i]){
				hoge.pb(mp(seki[i],0));
			}
			else{
				int g=beki(bunbo.first,seki[i]-seki[i]/sosu[i]-1,seki[i])*bunsi.first%seki[i];
				g*=beki(sosu[i],bunsi.second-bunbo.second,seki[i]);
				g%=seki[i];
				hoge.pb(mp(seki[i],g));	
			}		
			
		}
		return garner(hoge,P);
	}
	
	
	ll extgcd2(ll a, ll b, ll &x, ll &y) {
	    if (b == 0ll) {
	        x = 1ll;
	        y = 0ll;
	        return a;
	    }
	    ll d = extgcd(b, a%b, y, x);
	    y -= a/b * x;
	    return d;
	}

	ll modinv(ll r,ll mo){// mod mo Ç≈ÇÃ r ÇÃãtêî Ç»Ç¢Ç∆Ç´ÇÕ-1
		// r*x +mo*r = 1
		
		ll aa,bb;
		ll gc=extgcd2(r,mo,aa,bb);
		if(gc!=-1){
		//	cout<<-1<<endl;
		}
		if(gc!=1) return -1;
		aa%=mo;
		if(aa<0)aa+=mo;
		
		return aa;
	}


	ll garner(vector<pair<ll,ll>> vec,ll MOD){
		// vec[i]: x % vec[i].first == vec[i].second
		// 0<= vec[i].second<vec[i].first
		
		// vec[i].first ÇÕÇ«ÇÃ2Ç¬Ç‡å›Ç¢Ç…ëfÅIÅIÅIÅI
		// MOD ÇÕÇ«Ç§Ç≈Ç‡Ç¢Ç¢
		vec.pb({MOD,0ll});
		
		int siz=vec.size();
		
		vector<ll> ruiseki(siz,1ll);
		vector<ll> teisuu(siz,0ll);
		
		ll val;
		for(int i=0;i<siz-1;i++){
			
			// (teisuu[i] + val*ruiseki[i]) % vec[i].first = vec[i].second
			
			val= (ll)vec[i].second-teisuu[i];
			while(val<0) val+=(ll)vec[i].first;
			val%=(ll)vec[i].first;
			val*= modinv(ruiseki[i],(ll)vec[i].first);
			val%=(ll)vec[i].first;
		
			
			for(int j=i+1;j<siz;j++){
				teisuu[j]+=(ll)ruiseki[j]*val%(ll)vec[j].first;
				teisuu[j]%=(ll)vec[j].first;
		//		cout<<teisuu[j]<<endl;
				ruiseki[j]*=(ll)vec[i].first;
				ruiseki[j]%=(ll)vec[j].first;
			}
		}
		return teisuu.back();
		
		
	}
  
	
};