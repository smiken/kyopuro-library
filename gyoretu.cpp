const int sz=2;
using T=array<array<int,sz>,sz>;
T W;

T kake(T A ,T B){
	T ans;
	for(int i=0;i<sz;i++)for(int j=0;j<sz;j++){
		int ho=0;
		for(int k=0;k<sz;k++){
			ho+=A[i][k]*B[k][j]%mod;
		}
		ans[i][j]=ho%mod;
	}
	return ans;
}

T beki(T A,int r){
	//if(r==0)return uni;
	if(r==1)return A;
	if(r%2)return kake(beki(A,r-1),A);
	else{
		T ho=beki(A,r/2);
		return kake(ho,ho);
	}
		
}
