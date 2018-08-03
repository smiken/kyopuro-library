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

int cnt=0;


	bool compare_sa(int i, int j){//n=S.length();
		cnt++;
		if(ran[sain[i+hax]]!=ran[sain[j+hax]]){
			return ran[sain[i+hax]]<ran[sain[j+hax]];
		}
		return i<j;

	}
	
	bool compare_sa2(int i, int j){//n=S.length();
		cnt++;
		if(ran[i]!=ran[j]) return ran[i] <ran[j];
		return i<j;

	}
	
	void nar(int *hai,int nag){
		int w=0;
		int it=-1;
		while(w<=nag){
			
			if(hai[w]>0){
				if(it<0){
					w += hai[w];
					continue;
				}
				else{
					hai[it] = -(w-it);
					w += hai[w];
					it=-1;
					continue;
				}
			}
			else if( it<0){
				it=w;
				w -= hai[w];
			}
			else{
				w -=hai[w];
			}

		}
		if(it>=0){
			hai[it]=-(nag-it)-1;
		}
		
	}
	void construct_sa(string S,int *sa){
		
		nagasa=S.length();
		S += "$";
		
		for(int i=0;i<=nagasa;i++) {
			sa[i]=i;
			ran[i] =(i<nagasa ?S[i]:-1);
		}
		sort(sa,sa+nagasa+1,compare_sa2);

		for(int i=0;i<=nagasa;i++) sain[sa[i]]=i;

		char c=S[sa[nagasa]];

		ran[nagasa]=nagasa;
		for(int i=nagasa-1;i>=0;i--){
			ran[i]= (S[sa[i]]==c ? ran[i+1] : i);
			c=S[sa[i]];
		}

		int ren=1;
		l[0]=-1;
		for(int i=nagasa-1;i>=0;i--){
			if(ran[i+1] != ran[i]){
				l[i+1]=(ren==1?-1:ren);
				ren=1;
			}
			else{
				l[i+1]=0;
				ren++;
			}
		}
		nar(l,nagasa);

		int w=0,ne;
		hax=1;
		while(1){
			double start = clock();  
			if(l[0]== -nagasa-1) break;
			w=0;

			while(w<=nagasa){
				if(l[w]<0){
					w -= l[w];
					continue;
				}
				int p=cnt;
					sort(sa+w,sa+w+l[w],compare_sa);
			cout<<w<<" "<<w+l[w]<<" "<<cnt-p<<endl;
//				for(int i=0;i<=nagasa;i++) cout<<sa[i]<<" ";
//				cout<<endl;
				for(int i=w;i<w+l[w];i++) sain[sa[i]]=i;

				for(int i=0;i<l[w];i++) temp[i]=ran[i+w];
				for(int i=w+l[w]-2;i>=w;i--){
					if(w <= sain[sa[i+1]+hax] && sain[sa[i+1]+hax] <w+l[w] &&w <= sain[sa[i]+hax] && sain[sa[i]+hax] <w+l[w]){
						ran[i]=(temp[sain[sa[i+1]+hax]-w]==temp[sain[sa[i]+hax]-w]?ran[i+1]:i);
					}
				else	ran[i]=(ran[sain[sa[i+1]+hax]]==ran[sain[sa[i]+hax]]?ran[i+1]:i);
					
				}

				ren=1;
				for(int i=w+l[w]-2;i>=w;i--){
					if(ran[i+1] != ran[i]){
						l[i+1]=(ren==1?-1:ren);
						ren=1;
					}
					else{
						ren++;
					}
				}
				ne= w+l[w];
				l[w]=(ren==1?-1:ren);
				w =ne;
				
			}
	       
 nar(l,nagasa);
        double end = clock();     // èIóπéûä‘
	printf("%.10lf\n",(end-start)/ CLOCKS_PER_SEC);
			
			hax *=2;


		}
	
		
	}
	/*
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
*/
int main(){
	string s;
	cin>>s;
	       double start = clock();  
 	construct_sa(s,sa);
        double end = clock();     // èIóπéûä‘
	printf("%.10lf\n",(end-start)/ CLOCKS_PER_SEC);

//	construct_lcp(s,sa,lcp);
//	for(int i=0;i<=s.length();i++){
	//	cout<<sa[i]<<endl;
	//	cout<<s.substr(sa[i])<<endl;
//	}
cout<<cnt<<endl;
return 0;
}
