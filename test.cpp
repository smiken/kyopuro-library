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
#define pb push_back
#define mp make_pair
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
#define chai pair<char,int>


int sa[1000010],ran[1000010],sain[1000010],lcp[1000010],l[1000010],temp[1000010];
int nagasa,ki,hax;
vector<int> sa2(1000010) ;
int cnt=0;


	bool comp(int i, int j){//n=S.length();
		cnt++;
cout<<i<<" "<<j<<endl;
		return i<j;

	}


int main(){
	for(int i=0;i<120000;i++) sa[i]= i;
//	sa[0]=100000000;
	sort(sa,sa+100,comp);
	cout<<cnt<<endl;
//	construct_lcp(s,sa,lcp);
//	for(int i=0;i<=s.length();i++){
	//	cout<<sa[i]<<endl;
	//	cout<<s.substr(sa[i])<<endl;
//	}
cout<<cnt<<endl;
return 0;
}
