    #include<iostream>
    #include<cstdio>
    #include<vector>
    #include<queue>
    #include<map>
    #include<string>
    #include <cmath>
    #include<complex>
    #include<algorithm>
    #include<functional>
    #define ll long long
    #define inf  1000000007
    #define pa pair<int,int>
    using namespace std;
     
     
    typedef complex<double> Complex;
    const Complex I(0, 1);
    const double PI = 4.0*atan(1.0);
    Complex a[300100]={0};
    Complex b[300100]={0} ;
    Complex ab[300100]={0};
    int beki(int n){
    int k;
     
    for(int i=0;i<25;i++){
    if(((n+1)>>i & 1)== 1) k=i;
    }
    return (1 << (k+1));
    }
     
     
    void fft(int n, double theta, Complex a[]) {
      for (int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        for (int i = 0; i < mh; i++) {
          Complex w = exp(i*theta*I);
          for (int j = i; j < n; j += m) {
            int k = j + mh;
            Complex x = a[j] - a[k];
            a[j] += a[k];
            a[k] = w * x;
          }
        }
        theta *= 2;
      }
      int i = 0;
      for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
      }
    }
     
    int main(){
    //
    int n,nbeki,k,l;
    cin>>n;
    nbeki=beki(n);
    for(int i=1;i<=n;i++){
    cin>>a[i]>>b[i];
    }
    fft(2*nbeki, PI/nbeki, a);
    fft(2*nbeki, PI/nbeki, b);
    for(int i=0;i<2*nbeki;i++) ab[i]=a[i]*b[i];
    //for(int i=0;i<2*nbeki;i++) cout<<ab[i]<<endl;
    fft(2*nbeki, -PI/nbeki, ab);
    for(int i=1;i<=2*n;i++) cout<<int (real(ab[i]/(2*nbeki+0.0))+0.5)<<endl;
    return 0;
    }
