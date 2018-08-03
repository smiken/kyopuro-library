                            #include <bits/stdc++.h>
                            #include<iostream>
                            #include<cstdio>
                            #include<vector>
                            #include<queue>
                            #include<map>
                            #include<cstring>
                            #include<string>
                            #include <math.h>
                            #include<algorithm>
                        //    #include <boost/multiprecision/cpp_int.hpp>
                            #include<functional>
                    #define int long long
                            #define inf  1000000007
                            #define pa pair<int,int>
                            #define ll long long
                            #define pal pair<double,pa>
                            #define ppa pair<int,int>
                            #define ppap pair<int,pa>
                            #define ssa pair<string,int>
                            #define  mp make_pair
                            #define  pb push_back
                            #define EPS (1e-10)
                            #define equals(a,b) (fabs((a)-(b))<EPS)
                     
                            using namespace std;
                  
                            class Point{
                            	public:
                            	double x,y;
                            	Point(double x=0,double y=0):x(x),y(y) {}
                            	Point operator + (Point p) {return Point(x+p.x,y+p.y);}
                            	Point operator - (Point p) {return Point(x-p.x,y-p.y);}
                            	Point operator * (double a) {return Point(x*a,y*a);}
                            	Point operator / (double a) {return Point(x/a,y/a);}
                            	double absv() {return sqrt(norm());}
                            	double norm() {return x*x+y*y;}
                            	bool operator < (const Point &p) const{
                            		return x != p.x ? x<p.x: y<p.y;
                            	}
                            	bool operator == (const Point &p) const{
                            		return fabs(x-p.x)<EPS && fabs(y-p.y)<EPS;
                            	}
                            };
                            typedef Point Vector;
                     
                            struct Segment{
                            Point p1,p2;
                            };
                             double dot(Vector a,Vector b){
                            	return a.x*b.x+a.y*b.y;
                            }
                            double cross(Vector a,Vector b){
                            	return a.x*b.y-a.y*b.x;
                            }
                        
bool parareru(Point a,Point b,Point c,Point d){
//	if(abs(cross(a-b,d-c))<EPS)cout<<"dd "<<cross(a-b,d-c)<<endl;
	return abs(cross(a-b,d-c))<EPS;
}
double distance_ls_p(Point a, Point b, Point c) {
  if ( dot(b-a, c-a) < EPS ) return (c-a).absv();
  if ( dot(a-b, c-b) < EPS ) return (c-b).absv();
  return abs(cross(b-a, c-a)) / (b-a).absv();
}
bool is_intersected_ls(Segment a,Segment b) {
	if(a.p1==b.p1||a.p2==b.p1||a.p1==b.p2||a.p2==b.p2) return false;
	if(parareru((a.p2),(a.p1),(a.p1),(b.p2))&&parareru((a.p2),(a.p1),(a.p1),(b.p1))){
//		cout<<"sss"<<endl;
		if(dot(a.p1-b.p1,a.p1-b.p2)<EPS) return true;
		if(dot(a.p2-b.p1,a.p2-b.p2)<EPS) return true;
		if(dot(a.p1-b.p1,a.p2-b.p1)<EPS) return true;
		if(dot(a.p1-b.p2,a.p2-b.p2)<EPS) return true;
		return false;
	}
  else return ( cross(a.p2-a.p1, b.p1-a.p1) * cross(a.p2-a.p1, b.p2-a.p1) < EPS ) && ( cross(b.p2-b.p1, a.p1-b.p1) * cross(b.p2-b.p1, a.p2-b.p1) < EPS );
}
 
double segment_dis(Segment a,Segment b){
	if(is_intersected_ls(a,b))return 0;
	double r=distance_ls_p(a.p1, a.p2, b.p1);
	r=min(r,distance_ls_p(a.p1, a.p2, b.p2));
	r=min(r,distance_ls_p(b.p1, b.p2, a.p2));
	r=min(r,distance_ls_p(b.p1, b.p2, a.p1));
	return r;
}
Point intersection_ls(Segment a, Segment b) {
  Point ba = b.p2-b.p1;
  double d1 = abs(cross(ba, a.p1-b.p1));
  double d2 = abs(cross(ba, a.p2-b.p1));
  double t = d1 / (d1 + d2);
 
  return a.p1 + (a.p2-a.p1) * t;
}
 
                string itos( int i ) {
                ostringstream s ;
                s << i ;
                return s.str() ;
                }
                 
                int gcd(int v,int b){
                	if(v>b) return gcd(b,v);
                	if(v==b) return b;
                	if(b%v==0) return v;
                	return gcd(v,b%v);
                }
 
                double distans(double x1,double y1,double x2,double y2){
                	double rr=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                	return sqrt(rr);
                	
                }
                /*
int pr[100010];
//int inv[100010];
*/ 
int beki(int wa,int rr,int warukazu){
	if(rr==0) return 1ll;
	if(rr==1) return wa%warukazu;
	if(rr%2==1) return (beki(wa,rr-1,warukazu)*wa)%warukazu;
	int zx=beki(wa,rr/2,warukazu);
	return (zx*zx)%warukazu;
}
  /*
void gya(){
	pr[0]=1;
	for(int i=1;i<100010;i++){
		pr[i]=(pr[i-1]*i)%inf;
	}
	for(int i=0;i<100010;i++) inv[i]=beki(pr[i],inf-2);
	
}
 
*/
 
                         //----------------kokomade tenpure------------
                         
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