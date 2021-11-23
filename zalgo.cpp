
vector<int> zalgo(string s){
	
	int n=s.length();
	vector<int> z(n,0);
	z[0]=n;
	int L=0;
	int R=0;
	for(int i=1;i<n;i++){
      if(i>R) {
         L=i;
         R=i;
         while(R<n&&s[R-L]==s[R])R++;
         z[i]=R-L;
         R--;
      }
	  else{
        int k=i-L;
        if(z[k]<R-i+1)z[i]=z[k];
        else{
         L=i;
         while(R<n&&s[R-L]==s[R])R++;
         z[i]=R-L;
         R--;
       }
      }
    }
	return z;
}
