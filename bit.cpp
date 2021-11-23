
/*
Nは要素数
*/
int N;
int bit[1000010]={0};
void add(int a,int w){//aの位置にwをかさんする
  for(int x=a;x<=N; x+=(x&(-x))) bit[x] +=w;
}
int sum(int a){// 1 ~ a の和
  int ret=0;
  for(int x=a;x>0; x-=(x&(-x))) ret +=bit[x];
  return ret;
}