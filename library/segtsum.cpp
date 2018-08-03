#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<algorithm>
#include<functional>
#define ll long long
#define inf  999999999
#define pa pair<int,int>

using namespace std;

int a[300000];
int con=131072;
int sumsx(int i,int j ){
	if(i>j) return 0;
if(i==j) return a[i];
else if(i%2==1) return a[i]+sumsx(i+1,j);
else if(j%2==0) return a[j]+sumsx(i,j-1);
else return sumsx(i/2,j/2);
}


void upd(int x,int y){
	x += con;
a[x]=a[x]+y;
x=x/2;
while(x != 0){
a[x]=a[2*x+1]+a[2*x];
x=x/2;
}
}

int sums(int i,int j){
	return sumsx(i+con,j+con);
}
int main(){
int n,q,com,x,y;
for(int i=0;i<270000;i++) a[i]=0;

//kokoni ireru a[i+con]=a_i

	for(int i=con-1;i>0;i--) a[i]=a[2*i]+a[2*i+1];
	
	upd(i,x);// a_i ni x kasan
	sums(i,j);//a_i ~ a_j
	return 0;
}


