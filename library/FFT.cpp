complex<double> ARR[1000000][2];
complex<double> D[1000000];
vector<int> jun;
vector<complex<double>> fourie(int N,complex<double> U){
	//ARR[i][0]‚É“ü‚Á‚Ä‚¢‚é“z‚ğFT‚·‚éBN‚Í€”i2™pj
	// U‚Í‡•ûŒü‚Å‚Íexp(2pi*I/N)‹t‚¾‚Æexp(-2pi*I/N)
	//D[i]=U^i
	vector<complex<double>> ANS(N);
	if(N==1){
		ANS.pb(ARR[0][0]);
		return ANS;
	}
	D[0]=complex<double>(1,0);
	D[1]=U;
	jun.clear();
	jun.pb(0);
	for(int i=2;i<N;i++)D[i]=D[i-1]*U;
	int las;
	for(int c=0;;c++){
		
		int d=N>>(c+1);
		if(d==0) break;
		if(jun.size()<(1<<c)){
			int l=jun.size();
			for(int i=0;i<l;i++)jun.pb(jun[i]+(N>>(c+1)));
		}
		int W=2*d;
		for(int i=0;i<N/(2*d);i++){
			for(int j=0;j<d;j++){
				ARR[2*d*i+j][(c+1)%2]=ARR[2*d*i+j][c%2]+ARR[2*d*i+j+d][c%2]*D[jun[i]];
			}
			for(int j=d;j<2*d;j++){
				ARR[2*d*i+j][(c+1)%2]=-ARR[2*d*i+j][c%2]*D[jun[i]]+ARR[2*d*i+j-d][c%2];
			}
		}
		las=(c+1)%2;
	}
	for(int i=0;i<N/2;i++)jun[i]*=2;
	for(int i=0;i<N/2;i++)jun.pb(jun[i]+1);
	for(int i=0;i<N;i++){
		ANS[jun[i]]=ARR[i][las];
	//	cout<<jun[i]<<" ";
	}
	//cout<<endl;
	return ANS;
}

vector<int> FFT(vector<int> input1,vector<int> input2){
int N=1;
	int size1=input1.size(),size2=input2.size();
	while(N<max(size1,size2))N*=2;
	N*=2;
	while(input1.size()<N)input1.pb(0);
	while(input2.size()<N)input2.pb(0);
	complex<double> un=exp(complex<double>(0,2*PI/N));
	for(int i=0;i<N;i++)ARR[i][0]=complex<double>((double)input1[i],0);
	vector<complex<double>> F1=fourie(N,un);
	for(int i=0;i<N;i++)ARR[i][0]=complex<double>((double)input2[i],0);
	vector<complex<double>> F2=fourie(N,un);
	vector<int> ANS;
	for(int i=0;i<N;i++)ARR[i][0]=F1[i]*F2[i];
	vector<complex<double>> INV=fourie(N,conj(un));
	for(int i=0;i<N;i++)INV[i]/=N*1.0;
	
	for(int i=0;i<N;i++){
		ANS.pb((int) (0.5+INV[i].real()));
	//	cout<<ANS.back()<<endl;
	//	printf("%.10lf\n", INV[i].real());
	}
	return ANS;
}

