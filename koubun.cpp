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
  //   #define int long long
            #define mod  1000000009
            #define pa pair<int,int>
            #define ll long long
            #define pal pair<double,int>
            #define ppa pair<int,pa>
            #define ssa pair<string,int>
            #define  mp make_pair
            #define  pb push_back
            #define EPS (1e-10)
            #define equals(a,b) (fabs((a)-(b))<EPS)
     
            using namespace std;
     //priority_queue<int, vector<int>, greater<int> > que;
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
     
        double hen(Vector a){
        if(fabs(a.x)<EPS && a.y>0) return acos(0);
        else if(fabs(a.x)<EPS && a.y<0) return 3*acos(0);
        else if(fabs(a.y)<EPS && a.x<0) return 2*acos(0);
        else if(fabs(a.y)<EPS && a.x>0) return 0.0;
        else if(a.y>0) return acos(a.x/a.absv());
        else return 2*acos(0)+acos(-a.x/a.absv());
     
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
            double dot(Vector a,Vector b){
            	return a.x*b.x+a.y*b.y;
            }
            double cross(Vector a,Vector b){
            	return a.x*b.y-a.y*b.x;
            }
        
double distans(double x1,double y1,double x2,double y2){
	double rr=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	return sqrt(rr);
	
}
            //----------------kokomade tenpure------------
string s;
int kakko(string &t ,int &b);

int suuji(string &t, int &b){
	int r=0;
	if(isdigit(t[b])){
	while(isdigit(t[b])){
		r *=10;
		r += t[b]-'0';
		(b)++;
	}
	}
	else if(t[b]=='('){
	
		r=kakko(t,b);
		
	}
	
	return r;
}


int kake(string &t, int &b){
	
		int i=suuji(t,b);
	//cout<<i<<endl;
		while((t[b]=='*')||(t[b]=='/')){
			b++;
			if(t[b-1]=='*')i *= suuji(t,b);
			else i /= suuji(t,b);
		}
		return i;
	
}

int tashi(string &t ,int &b){

		int i=kake(t,b);
		while((t[b]=='+')||(t[b]=='-')){
		b++;
			if(t[b-1]=='+')	i += kake(t,b);
			else i -= kake(t,b);
		}
		return i;
	
}

int kakko(string &t ,int &b){
	
	if(t[b]=='('){
		int y;
		b++;
		y=tashi(t,b);
//		cout<<y<<endl;
		b++;
		return y;
	}
	else{
		return tashi(t,b);
	}
}
    signed  main(){
    	int n;
    	cin>>n;
    	for(int g=0;g<n;g++){
cin>>s;
    	int i=0;
    	cout<<tashi(s,i)<<endl;
    	}
    
  //  	printf("%.10f\n",ans[n-1]);
    	return 0;
    }