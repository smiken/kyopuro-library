// min{ax+b}��x=t�ł̒l�����߂�D�폜�͂ł��Ȃ�

// ������^���鏇�Ԃ��P������Ȃ��Ă�����CHT
// �N�G���̈ʒu���P������Ȃ��Ă������C���O�ɋ����Ă����K�v������D


//�g����

// add_pos(int x)�ɃN�G���̈ʒu��S��������
// shoki()�����

//���Ƃ� add_line(a,b) ��ax+b��ǉ�
//getmin(x)�ōŏ��l�����߂�D

// verify
// ���o�{�I2019G (��P��)
// CSA Squared Ends (��P��)
// �R���R���{�IC (�P��)
// EDPC Z(�P��)
// yukicoder 409,703 (�P��)

struct convex_hull{

	struct line{
		int a;
		int b;
	};

     */
    private:
    public:
     

	
	int f(line s,int x){
		return s.a*x+s.b;
	}
	

    int inff=inf*2000000000ll;
	
	
    int n;
	int cor=1;
	vector<line> lines;
	vector<int> points;
    vector<pa4> vec;
	map<int,int> point_to_id;
	
	
	void add_pos(int x){
		points.pb(x);
	}
	
    void shoki(){
    	if(points.size()==0) points.pb(0); //�󂾂Ɖ���̂�
    	sort(points.begin(), points.end());
    	points.erase(unique(points.begin(),points.end()),points.end());
    	n=points.size();
    	for(int i=0;i<n;i++){
    		point_to_id[points[i]]=i;
    	}
    	
    	lines.pb({0,inff});//�ԕ�
    	cor=1;
    	while(cor<=n)cor*=2;
    	while(points.size()<cor)points.pb(points.back()+1);
    	vec.resize(2*cor+3,{0,inff,inff,inff});
    }
	
	int getmin(int pos){
	
		int id=point_to_id[pos]+cor;
		
		int ans=inff;
		while(id){
			ans=min(ans,f(lines[vec[id].x],pos));
			id/=2;
		}
		return ans;
	}
	
	void add_line(int a,int b){// ax+b

		int id=1;
		int l=0;
		int r=cor;
		line new_line={a,b};
		lines.pb(new_line);
		int line_id=lines.size()-1;
		while(1){
			// 1:l
			// 2:m=(l+r)/2
			// 3:r-1
			
			// p: current
			// q: new
			
			int m=(l+r)/2;			
			
			int p1=f(lines[line_id],points[l]);
			int p2=f(lines[line_id],points[m]);
			int p3=f(lines[line_id],points[r-1]);
			
			if(p1>=vec[id].y && p3>=vec[id].w) break;
			if(p1<=vec[id].y && p3<=vec[id].w){
				vec[id]={line_id,p1,p2,p3};
				break;
			}
			if(p2<=vec[id].z){
				swap(vec[id].x,line_id);
				swap(vec[id].y,p1);
				swap(vec[id].z,p2);
				swap(vec[id].w,p3);
			}
			
			if(id>=cor)break;
			
			if(p1<=vec[id].y){
				id=2*id;
				r=m;
			}
			else if(p3<=vec[id].w){
				id=2*id+1;
				l=m;
			}
			else assert(0);
		}
		
		
	}
	

     
};