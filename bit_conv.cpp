// bitwise-convolution

//
// vec‚ÌƒTƒCƒY‚Í2™p
// rev=false‚Å•ÏŠ· rev=true‚Å‹t•ÏŠ·
//
// A=???_conv(a,0);
// B=???_conv(b,0);
// C=???_conv(c,0);
//
// for(int i=0;i<n;i++)X[i]=A[i]*B[i]*C[i]%mod;
// x=???_conv(X,1);
// cout<<x<<endl;

vector<int> xor_conv(vector<int> vec,bool rev) {
    int n = vec.size();
	for(int i=1;i<n;i*=2){
		for(int j=0;j<n;j++)if((j&i)==0){
			int x=vec[j],y=vec[i|j];
			vec[j]=x+y;
			if(vec[j]>=mod)vec[j]-=mod;
			vec[j|i]=x+mod-y;
			if(vec[j|i]>=mod)vec[j|i]-=mod;
		}
	}
	
	if(rev){
		int g=beki(n,mod-2,mod);
		for(auto &v:vec)v=(v*g)%mod;
	}
	return vec;
}

vector<int> and_conv(vector<int> vec,bool rev) {
    int n = vec.size();
	for(int i=1;i<n;i*=2){
		for(int j=0;j<n;j++)if((j&i)==0){
			if(!rev){
				vec[j]+=vec[i|j];
				if(vec[j]>=mod)vec[j]-=mod;
			}	
			else{
				vec[j]+=mod-vec[i|j];
				if(vec[j]>=mod)vec[j]-=mod;
			}
		}
	}
	return vec;
}


vector<int> or_conv(vector<int> vec,bool rev) {
    int n = vec.size();
	for(int i=1;i<n;i*=2){
		for(int j=0;j<n;j++)if((j&i)==0){
			if(!rev){
				vec[i|j]+=vec[j];
				if(vec[i|j]>=mod)vec[i|j]-=mod;
			}	
			else{
				vec[i|j]+=mod-vec[j];
				if(vec[i|j]>=mod)vec[i|j]-=mod;
			}
		}
	}
	return vec;
}
