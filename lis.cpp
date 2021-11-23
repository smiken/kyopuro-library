//LIS (strictly monotone)
int LIS_strict(vector<int>A){
	vector<int>t;
	int sz=0;
	
	for(auto v:A){
		int r=lower_bound(t.begin(),t.end(),v)-t.begin();
		if(r>=sz)t.pb(0),sz++;
		t[r]=v;
	}
	return t.size();
}

//LIS (not strictly monotone)
int LIS_NOT_strict(vector<int>A){
	vector<int>t;
	int sz=0;
	
	for(auto v:A){
		int r=upper_bound(t.begin(),t.end(),v)-t.begin();
		if(r>=sz)t.pb(0),sz++;
		t[r]=v;
	}
	return t.size();
}


//LIS lexically minimum indices
vector<int> LIS_strict_fukugen(vector<int>A){
	int n=A.size();
	vector<int>B=A;
	reverse(B.begin(),B.end());
	for(auto &v:B)v*=-1;
	vector<int>t;
	int sz=0;
	vector<int>W(n); //W_i is max lis size of [A_i,...,A_{n-1}]
	
	
	int lis_size=-1;
	for(int i=0;i<n;i++){
		int v=B[i];
		int r=lower_bound(t.begin(),t.end(),v)-t.begin();
		if(r>=sz)t.pb(0),sz++;
		t[r]=v;
		W[n-1-i]=r+1;
		lis_size=max(lis_size,r+1);
	}
	vector<int>ans;
	int nx=lis_size;
	int ima;
	for(int i=0;i<n;i++){
		if(W[i]==nx && (nx==lis_size || ima<A[i])){
			ans.pb(i);
			ima=A[i];
			nx--;
		}
	}
	return ans;
}