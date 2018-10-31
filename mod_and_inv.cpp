ll frac[100010];
ll inv[100010];

ll saikif(ll a,int n){
  if(n==1) return a%mod;
  else if(n%2==0){
    ll q=saikif(a,n/2);
    return (q*q)%mod;
  }
  else return (a*saikif(a,n-1))%mod;
}

void gyakugen(){
  frac[0]=1;
  for(int i=1;i<=100000;i++) frac[i]=(frac[i-1]*i)%mod;
  for(int i=0;i<=100000;i++) inv[i]=saikif(frac[i],mod-2);
}
