
/*
N�͗v�f��
*/
int N;
int bit[1000010]={0};
void add(int a,int w){//a�̈ʒu��w�������񂷂�
  for(int x=a;x<=N; x+=(x&(-x))) bit[x] +=w;
}
int sum(int a){// 1 ~ a �̘a
  int ret=0;
  for(int x=a;x>0; x-=(x&(-x))) ret +=bit[x];
  return ret;
}