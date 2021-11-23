vector<int> get_kitei(vector<int> vec){
	vector<int> kitei;
	for(auto v:vec){
		for(auto w:kitei)v=min(v,v^w);
		if(v)kitei.pb(v);
	}
	
	
	// ³‹KŒ`‚ÌŠî’ê‚ª—~‚µ‚¢ê‡
	/*
	sort(kitei.begin(),kitei.end(),greater<int>());
	for(int i=0;i<kitei.size();i++){
		for(int j=0;j<i;j++)kitei[j]=min(kitei[j],kitei[j]^kitei[i]);
	}
	*/
	
	
	//debug
	/*
	for(auto v:kitei){
		cout<<bitset<64>(v)<<endl;
	}
	*/
	
	return kitei;
}