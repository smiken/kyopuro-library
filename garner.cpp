// verify

// DDCC2019ó\ëI D
// yukicoder no. 695, no.186, no.187


ll extgcd(ll a, ll b, ll &x, ll &y) {
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
	ll gc=extgcd(r,mo,aa,bb);
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

