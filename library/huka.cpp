    #include<iostream>
    #include<cstdio>
    #include<vector>
    #include<queue>
    #include<map>
    #include<string>
    #include <cmath>
    #include <stack>
    #include<complex>
    #include<algorithm>
    #include<functional>
    #define ll long long
    #define inf  1000000007
    #define pa pair<int,int>
    using namespace std;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

stack<pa> st;

int main(){
int ma[500][500]={0};
int ta,yo,sx,sy,gx,gy;
string s;
cin>>ta>>yo;
for(int i=0;i<ta;i++){
	cin>>s;
	for(int j=0;j<yo;j++){
	if(s[j]=='#') ma[i][j]=1;
		if(s[j]=='s'){
			sx=i,sy=j;
		}
		 if(s[j]=='g'){
			gx=i,gy=j;
		}
	}
}
int ans=0;
pa b;
pa goal=make_pair(gx,gy);
st.push(make_pair(sx,sy));
//ma[sx][sy]=0;
while(st.size()>0){
b=st.top();
st.pop();
if(b==goal){
ans++;
break;
}
if(ma[b.first][b.second]!=0) continue;
for(int i=0;i<4;i++){
if(b.first+dx[i]>=0 && b.first+dx[i]<ta &&b.second+dy[i]>=0 &&b.second+dy[i]<yo){
if(ma[b.first+dx[i]][b.second+dy[i]]==0) st.push(make_pair(b.first+dx[i],b.second+dy[i]));
}
}

}
if(ans==0) cout<<"No"<<endl;
else cout<<"Yes"<<endl;
return 0;    
}