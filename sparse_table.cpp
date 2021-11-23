struct Sparsetable_max{
	
	
	private:
	public:
	
	// (1<<15)=32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int beki=18;
	
	int cor=(1<<beki);
	
	vector<vector<int>> vec;
	vector<int> lo;
	
	void shoki1(){
		
		vec= vector<vector<int>>(beki+1, vector<int>(cor, 0));
		lo=vector<int>(cor+1);
		lo[0]=-1;
		for(int i=1;i<=cor;i++)lo[i]=lo[i>>1]+1;
		
	}
	
	void shoki2(){
		for(int i=1;i<=beki;i++)for(int j=0;j<cor;j++){
			if((j+(1<<(i-1)))<cor)vec[i][j]=max(vec[i-1][j],vec[i-1][j+(1<<(i-1))]);
			else vec[i][j]=vec[i-1][j];
		}
	
	}
	
	
	int rangemax(int i,int j){ //  [i,j)
		int haba=lo[j-i];
		
		return max(vec[haba][i],vec[haba][j-(1<<haba)]);
	}
	
};

struct Sparsetable_min{
	
	
	private:
	public:
	
	// (1<<15)=32768
	// 1<<16 = 65536
	// 1<<17 = 131072
	// 1<<18 = 262144
	
	int beki=18;
	
	int cor=(1<<beki);
	
	vector<vector<int>> vec;
	vector<int> lo;
	
	void shoki1(){
		vec= vector<vector<int>>(beki+1, vector<int>(cor, 0));
		lo=vector<int>(cor+1);
		lo[0]=-1;
		for(int i=1;i<=cor;i++)lo[i]=lo[i>>1]+1;
	}
	
	void shoki2(){
		for(int i=1;i<=beki;i++)for(int j=0;j<cor;j++){
			if((j+(1<<(i-1)))<cor)vec[i][j]=min(vec[i-1][j],vec[i-1][j+(1<<(i-1))]);
			else vec[i][j]=vec[i-1][j];
		}
	}
	
	int rangemin(int i,int j){
		int haba=lo[j-i];
		
		return min(vec[haba][i],vec[haba][j-(1<<haba)]);
	}
	
};

Sparsetable_max sa;
Sparsetable_min sb;

  signed main(){
  	               cin.tie(0);
    		ios::sync_with_stdio(false);

int n;
  	cin>>n;
  	sa.shoki1();
  	sb.shoki1();
  	for(int i=0;i<n;i++)cin>>sa.vec[0][i];
  	for(int i=0;i<n;i++)cin>>sb.vec[0][i];
  	
  	sa.shoki2();
  	sb.shoki2();
  	
  	return 0;
  }