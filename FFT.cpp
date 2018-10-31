class comp{
public:
double re,im;
comp(double re=0,double im=0):re(re),im(im) {};
comp operator + (comp p) {return comp(re+p.re,im+p.im);}	
comp operator - (comp p) {return comp(re-p.re,im-p.im);}
comp operator * (comp p) {return comp(re*p.re-im*p.im,re*p.im+im*p.re);}
comp operator / (double p){return comp(re/p,im/p);}
 
};
comp D[1000000];
void fourie(int N,int d,vector<comp> &vec ){// 1<<d == N
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
				comp A1=vec[j]+vec[j+f]*D[(j-i)<<(d-c-1)];
				comp A2=vec[j]-vec[j+f]*D[(j-i)<<(d-c-1)];
				vec[j]=A1;
				vec[j+f]=A2;
			}
		}
	}
 
	return;
}
 
vector<int> FFT(vector<comp> input1,vector<comp> input2){
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
//	complex<double> un=exp(complex<double>(0,2*PI/N));
	for(int i=0;i<N;i++){
		
		complex<double> un=exp(complex<double>(0.0,(double)2*PI*i/N));
		D[i]=(comp){un.real(),un.imag()};
	}
	fourie(N,d,input1);
	fourie(N,d,input2);
	vector<int> ANS;
	
	for(int i=0;i<N;i++)input1[i]=input1[i]*input2[i],(D[i].im)*=-1;
	
	fourie(N,d,input1);
	for(int i=0;i<N;i++)input1[i]=input1[i]/(N*1.0);
	
	for(int i=0;i<N;i++){
		ANS.pb((int) (0.5+input1[i].re));
	//	cout<<ANS.back()<<endl;
	//	printf("%.10lf\n", INV[i].real());
	}
	return ANS;
}
 