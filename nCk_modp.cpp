
                         
vector<int> prime,kosuu,china;
int pr[1000002];                         

// if(p==-1) mod nasi
int rui(int r,int k,int p){ //reutn r^k mod p  ,p ha prime toha kagirannai 
	if(k==0) return 1;
	if(p==-1) return rui(r,k,1000000009);
	if(k%2==1) return (r*rui(r,k-1,p))%p;
	int y=rui(r,k/2,p);
	return (y*y)%p;
}

//w! = a*p^e return (a mod p^r , e)
pa kaijou_modp(int w,int p,int r,int pe,int fir){//pe=p^r
	if(w==0)return mp(1,0);
	
	if(fir==0){
	pr[0]=1;
		
		
	for(int i=1;i<=pe;i++){
		if(i%p!=0)pr[i]=(pr[i-1]*i) %pe;
		else pr[i]=pr[i-1];
		
	}
		
	}
	if(w<p) return mp(pr[w],0);
	pa z=kaijou_modp(w/p,p,r,pe,1);
	int fi=(rui(pr[pe],w/pe,pe)*z.first)%pe;
	fi *= pr[w%pe];
	fi %=pe;
	return mp(fi,z.second+w/p);
	/*
	if((w/p)%2==0)return mp((z.first*pr[w%p])%p,z.second+w/p);
	else return mp((p-(z.first*pr[w%p])%p)%p,z.second+w/p);
	*/
}


int inv(int r,int p,int e){ //retrn r^-1 mod p^e;
	int pe=rui(p,e,-1);// p^e
	int oira=rui(p,e-1,-1);
	oira *= (p-1); //oira ha isuu  p^oira = 1
	return rui(r,oira-1,pe);
	
}

signed main(){
int n,k,p,pp;
	cin>>n>>k>>p;
	
	pa z=kaijou_modp(3,2,3,8,0);
//	cout<<"z "<<z.first<<" "<<z.second<<endl;
	
	pp=p;
	for(int i=2;i<=1000002;i++){
		if(pp%i!=0) continue;
		int cnt=0;
		while(pp%i==0){
			pp /= i;
			cnt++;
		}
		prime.pb(i);
		kosuu.pb(cnt);
		if(pp==1) break;
	}
	
	int s=prime.size();
	for(int i=0;i<s;i++){
		int pe=rui(prime[i],kosuu[i],-1);// p^e
		pa a1=kaijou_modp(n,prime[i],kosuu[i],pe,0);
		pa a2=kaijou_modp(k,prime[i],kosuu[i],pe,0);
		pa a3=kaijou_modp(n-k,prime[i],kosuu[i],pe,0);
		/*
		cout<<prime[i]<<" "<<kosuu[i]<<endl;
		cout<<i<<" "<<a1.first<<" "<<a1.second<<endl;
		cout<<i<<" "<<a2.first<<" "<<a2.second<<endl;
		cout<<i<<" "<<a3.first<<" "<<a3.second<<endl;
		*/
		if(a1.second-(a2.second+a3.second)>=kosuu[i]){
			china.pb(0);
		}
		else{
			
			
			int d=a1.second-(a2.second+a3.second);
			
			int q=a1.first*inv(a2.first,prime[i],kosuu[i]);
			q %=pe;
			q *= inv(a3.first,prime[i],kosuu[i]);
			q %=pe;
			q *= rui(prime[i],d,-1);
			q %=pe;
			china.pb(q);
		
		}
	//	cout<<china[i]<<endl;
	}

	for(int i=0;i<p;i++){
		bool b=true;
		for(int j=0;j<s;j++){
			int pe=rui(prime[j],kosuu[j],-1);
	//			cout<<pe<<endl;
			if(i%pe != china[j] ){
				b=false;
				break;
			}
		}
		
		if(b) cout<<i<<endl;
	}
	
	return 0;
}