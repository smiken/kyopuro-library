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
#define ll long long
#define inf  1000000007
#define mod 1000000007
#define pa pair<int,int>
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

double dot(Vector a,Vector b){
  return a.x*b.x+a.y*b.y;
}
double cross(Vector a,Vector b){
  return a.x*b.y-a.y*b.x;
}
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};


//----------------kokomade temple------------

int sa[1000010],ran[1000010],tmpo[1000010],lcp[1000010];
int nagasa,ki;
int cnt=0;
	bool compare_sa(int i, int j){//n=S.length();
		cnt++;
		if(ran[i]!=ran[j]) return ran[i] <ran[j];
		int ri=(i+ki <= nagasa ?ran[i+ki]:-1);
		int rj= (j+ki <=nagasa ? ran[j+ki]:-1);
		return ri<rj;
		//if(ri!=rj)return ri<rj;
		//return i<j;
	
	}

	void construct_sa(string S,int *sa){
		
		nagasa=S.length();
			
		for(int i=0;i<=nagasa;i++){
			sa[i]=i;
			ran[i] =(i<nagasa ?S[i]:-1);
		}
		for(ki=1;ki<=nagasa;ki*=2){
	int p=cnt;
			sort(sa,sa+nagasa+1,compare_sa);
cout<<nagasa<<" "<<cnt-p<<endl;
			tmpo[sa[0]]=0;
			for(int i=1;i<=nagasa;i++){
				tmpo[sa[i]]=tmpo[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
			}

			for(int i=0;i<=nagasa;i++) ran[i]=tmpo[i];

		}
	
		
	}
	
void construct_lcp(string S,int *sa,int *lcp){
	int n=S.length();
	for(int i=0;i<=n;i++) ran[sa[i]]=i;
	int h=0;
	lcp[0]=0;
	for(int i=0;i<n;i++){
		int j=sa[ran[i]-1];
		if(h>0) h--;
		for(;j+h<n&&i+h<n;h++)if(S[j+h]!=S[i+h]) break;
		lcp[ran[i]-1]=h;
	}
}

int main(){
	string s;
	cin>>s;
		       double start = clock();  
 	construct_sa(s,sa);
        double end = clock();    
	printf("%.10lf\n",(end-start)/ CLOCKS_PER_SEC);
cout<<cnt<<endl;

return 0;
}
