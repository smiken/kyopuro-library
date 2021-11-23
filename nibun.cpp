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
        #include<functional>
 //      #define int long long
        #define inf  1000000007
        #define pa pair<int,int>
#define ll long long
        #define pal pair<ll,ll>
        #define ppa pair<int,pa>
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
        double dot(Vector a,Vector b){
        	return a.x*b.x+a.y*b.y;
        }
        double cross(Vector a,Vector b){
        	return a.x*b.y-a.y*b.x;
        }
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        //----------------kokomade temple------------
//int a[100100]={0};

struct nib{
	int key;
	nib *r;
	nib *l;
};


void ins(nib *e,nib *j){
	// j - new sruct
	
	
	if(e->key < j->key){
		if(e->r ==NULL) e->r = j;
		else ins(e->r , j);
	}
	
	else{
		if(e->l ==NULL) e->l = j;
		else ins(e->l , j);
	}
}

string st(nib *e){
	string s="(";
	if(e->l != NULL ) s+= st(e->l),s+= "<-";
		s += "&";
		if(e->r != NULL )s+="->", s+= st(e->r);
		s+= ")";
	return s;
}

signed main(){
set<string> z;
	int n,k;
	cin>>n>>k;
	for(int i=0;i<n;i++){
		nib *f;
	f=new nib();
		int y;
		cin>>y;
		f->key=y;
		for(int j=1;j<k;j++){
		//	cout<<j<<endl;
			int l;
			cin>>l;
			nib *g= new nib();
			g->key=l;
			ins(f,g);
		}
		
		string s=st(f);
		cout<<s<<endl;
		z.insert(s);
	}
	cout<<z.size()<<endl;
	
	
return 0;
        }
        
// printf("%.10f\n", ans);
