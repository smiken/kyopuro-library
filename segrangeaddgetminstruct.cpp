struct seg_rangeadd_getmin{
    //       1
    //   2        3
    // 4   5   6    7
     
     
    private:
    public:
     
    // (1<<15)=32768
    // 1<<16 = 65536
    // 1<<17 = 131072
    // 1<<18 = 262144
     
    int cor=(1<<17);
    int inff=inf*1000000ll;
     
    vector<int> vec;
    vector<int> lazy;
    void shoki1(){
        vec.resize(2*cor+3, 0);
        lazy.resize(2*cor+3, 0);
    }
    void shoki2(){
        //lazy[1]=(1ll<<31)-1;
        //�����l
    }
         
    void chien(int k,int l,int r){
        //if(lazy[k]==-1) return;
        if(l+1<r){
            vec[k]+=lazy[k];
            lazy[2*k]+=lazy[k];
            lazy[2*k+1]+=lazy[k];
            lazy[k]=0;
        }
        else {
            vec[k]+=lazy[k];
            lazy[k]=0;
        }
    }
     
    int rangeadd(int a,int b,int w, int k=1,int l=0,int r=-3){
        //[a,b)�� w�ɕύX
        if(r<0) r=cor;
         
        if(a<=l && r<=b){
            lazy[k]+=w;
            chien(k,l,r);
            return vec[k];
        }
        if(r<=a || b<=l){
            chien(k,l,r);
            return vec[k];
        }
         
        chien(k,l,r);
//  cout<<k<<" "<<l<<" "<<r<<endl;
        int w1=rangeadd(a,b,w,k*2,l,(l+r)/2);
        int w2=rangeadd(a,b,w,k*2+1,(l+r)/2,r);
        vec[k]=min(w1,w2);
        return vec[k];
    }
     
    // [a,b)
    // k-th node
    // k no kukanha [l,r)
     
    int getmin(int a,int b,int k=1,int l=0,int r=-1){
        //[a,b)��min���擾
        if(r<0) r=cor;
        chien(k,l,r);
        if(r<=a || b<=l){// ��ԊO
            return inff;
        }
         
        if(a<=l && r<=b){// ���S�܂�
             
            return vec[k];
        }
        int w1=getmin(a,b,k*2,l,(l+r)/2);
        int w2=getmin(a,b,k*2+1,(l+r)/2,r);
        return min(w1,w2);
    }
    void pre(){
        for(int i=1;i<2*cor;i++){
            cout<<vec[i]<<" ";
            if(((i+1)&(-(i+1)))==i+1) cout<<endl;
        }
    }
     
};
 