int D[1000000];
const int MOD=998244353;
void fourie(int N,int d,vector<int> &vec ){// 1<<d == N
	// U‚Í‡•ûŒü‚Å‚Íexp(2pi*I/N)‹t‚¾‚Æexp(-2pi*I/N)
	if(N==1){
		return;
	}
	int gyaku=0;
	for(int i=1;i<N;i++){
		int e=1<<(d-1);
		while(gyaku&e){
			gyaku^=e;
			e>>=1;
		}
		gyaku^=e;
		if(i<gyaku)swap(vec[i],vec[gyaku]);	
	}
	for(int c=0;c<d;c++){
		int f=1<<c;
		for(int i=0;i<N;i+=(f<<1)){
			for(int j=i;j<i+f;j++){
				int A1=(vec[j]+vec[j+f]*D[(j-i)<<(d-c-1)])%MOD;
				int A2=(vec[j]-(vec[j+f]*D[(j-i)<<(d-c-1)]%MOD)+MOD)%MOD;
				vec[j]=A1;
				vec[j+f]=A2;
			}
		}
	}
 
	return;
}
 
vector<int> NTT(vector<int> input1,vector<int> input2){//MOD=998244353;
int N=1;
	int d=0;
	int size1=input1.size(),size2=input2.size();
	while(N<size1+size2){
		N*=2;
		d++;
	}
	assert(N==(1<<d));
	while(input1.size()<N)input1.pb(0);
	while(input2.size()<N)input2.pb(0);
	for(auto v:input1){
		if(v<0) v=MOD-((-v)%MOD);
		if(v>=MOD) v%=MOD;
	}
	for(auto v:input2){
		if(v<0) v=MOD-((-v)%MOD);
		if(v>=MOD) v%=MOD;
	}
	// (3^119)^(2^23)=1 mod 998244353
	int g=beki(3,119,MOD);
	for(int i=0;i<23-d;i++)g=(g*g)%MOD;
	
	//cout<<"   "<<beki(g,N,998244353)<<endl;
	
	D[0]=1;
	for(int i=1;i<N;i++){
		D[i]=D[i-1]*g%MOD;
	}
	fourie(N,d,input1);
	fourie(N,d,input2);
	vector<int> ANS;
	
	for(int i=0;i<N;i++)input1[i]=input1[i]*input2[i]%MOD;
	for(int i=1;i<N/2;i++)swap(D[i],D[N-i]);
	
	fourie(N,d,input1);
	int ninv=beki(N,MOD-2,MOD);
	for(int i=0;i<N;i++)input1[i]=input1[i]*ninv%MOD;
	
	for(int i=0;i<N;i++){
		ANS.pb(input1[i]);
	}
	return ANS;
}