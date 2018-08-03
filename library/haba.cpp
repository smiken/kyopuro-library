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
#define inf  1999999999
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


double dot(Vector a,Vector b){
	return a.x*b.x+a.y*b.y;
}
double cross(Vector a,Vector b){
	return a.x*b.y-a.y*b.x;
}
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
//----------------kokomade temple------------



int main(){
int a[60][60]={0};
int r,c,sx,sy,gx,gy;
string s;
cin>>r>>c>>sx>>sy>>gx>>gy;
for(int i=1;i<=r;i++){
cin>>s;
for(int j=1;j<=c;j++){
if(s[j-1]=='#') a[i][j]=1;
}
}
pa goal=make_pair(gx,gy);
queue<ppa> qu;
qu.push(make_pair(0,make_pair(sx,sy)));
int ans;
while(1){
ppa zz=qu.front();
pa z=zz.second;
qu.pop();

if(zz.second==goal){ 
ans=zz.first;
break;
}
if(a[z.first][z.second]==1) continue;
a[z.first][z.second]=1;
for(int r=0;r<4;r++){
if(a[z.first+dx[r]][z.second+dy[r]]==0) qu.push(make_pair(zz.first+1,make_pair(z.first+dx[r],z.second+dy[r])));


}
}
cout<<ans<<endl;
return 0;
}