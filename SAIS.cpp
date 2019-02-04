// verify

// SPOJ sarray
// JAG 茂木地区2017 Separate String
// コドフェス2016トーナメント1B 数字列をカンマで分ける問題 / Problem where Commas Separate Digits
// ARC050 D

struct SAIS{
	private:
	public:
	
	vector<int> S;
	vector<int> SL;
	// L-type = 0
	// S-type = 1
	// LMS-type = -(length of LMS-substring)
	vector<pa> haba;
	vector<int> SA;
	int mojisu;
	
	
	void make_suffix_array_string(string str){
		set<char> setc;
		map<char,int> mapc;
		for(auto c:str)setc.insert(c);
		int cnt=1;
		for(auto it=setc.begin();it!=setc.end();it++){
			mapc[*it]=cnt;
			cnt++;
		}
		for(auto c:str)S.pb(mapc[c]);
		mojisu=cnt;
		S.pb(0);
		make_suffix_array_naibu();
	}
	
	void make_suffix_array_saiki(vector<int> ve,int max_valu){
		S=ve;
		S.pb(0);
		mojisu=max_valu+1;
		make_suffix_array_naibu();
	}
	
	
	void make_suffix_array_naibu(){
		int cnt=mojisu;
		int len=S.size();
		
		vector<int> kosuu(cnt,0);
		for(auto c:S)kosuu[c]++;
		
		haba.pb({0,0});
		for(int i=1;i<cnt;i++){
			haba.pb({haba.back().second+1,haba.back().second+kosuu[i]});
		}
		
		///////////////
		//S,L,LMSを判定
		// L-type   = 0
		// S-type   = 1
		// LMS-type <0: LMS-substrの長さ＊－１
		///////////////

		SL.resize(len);
		for(int i=len-1;i>=0;i--){
			if(i==len-1){
				SL[i]=1;
			}
			else{
				if(S[i]<S[i+1]) SL[i]=1;
				else if(S[i]>S[i+1])SL[i]=0;
				else{
					SL[i]=SL[i+1];
				}
			}
		}
		
		int LMS_num=0;
		vector<int> LMS;
		vector<int> LMS_id(len,0);
		int rt=0;
		for(int i=1;i<len;i++)if(SL[i-1]==0 &&SL[i]==1){
			LMS.pb(i);
			LMS_id[i]=rt;
			LMS_num++;
			rt++;
		}
		for(int i=0;i<LMS_num-1;i++){
			SL[LMS[i]]=-(LMS[i+1]-LMS[i]+1);
		}
		SL[len-1]=-1;
		/*
		for(int i=0;i<len;i++)cout<<SL[i]<<" ";
		cout<<endl;
		*/
		for(int i=0;i<len;i++)SA.pb(-1);
		vector<int> pos(cnt,0);
		for(int c=0;c<len;c++)if(SL[c]<0){
			
			SA[haba[S[c]].second-pos[S[c]]]=c;
			pos[S[c]]++;
		}
		///////////////
		// 
		// 
		// 最初のinduced sort
		// 
		///////////////
		
		
		induced_sort(SA,len,cnt);
		
	//	cout<<"d"<<endl;
		///////////////
		// 
		// 
		// LMSの重複チェック
		// 
		///////////////
		
		vector<pa> lms_sub_order;
		int mae_ind;
		for(int i=0;i<len;i++)if(SL[SA[i]]<0){
			if(i==0){
				lms_sub_order.pb({SA[i],1});
				
			}
			else if(lms_sub_order.back().second==1){
				lms_sub_order.pb({SA[i],2});
			}
			else if(SL[SA[mae_ind]]!=SL[SA[i]]){
				lms_sub_order.pb({SA[i],lms_sub_order.back().second+1});
			}
			else{
				int lmslen= -SL[SA[mae_ind]];
				bool bo=true;
				for(int j=0;j<lmslen;j++){
					if(S[SA[mae_ind]+j]!=S[SA[i]+j]){
						bo=0;
						break;
					}
				}
				if(bo)lms_sub_order.pb({SA[i],lms_sub_order.back().second});
				else lms_sub_order.pb({SA[i],lms_sub_order.back().second+1});
			}
			mae_ind=i;
		}
	//	for(auto v:lms_sub_order)cout<<v.first<<" "<<v.second<<endl;
	//	cout<<endl;
			for(int i=0;i<cnt;i++)pos[i]=0;
			for(int i=0;i<len;i++)SA[i]=-1;
		
		///////////////
		// 
		// LMS-substrがダブってるかどうかで場合分け
		// 
		// 
		///////////////		
		if(LMS_num==lms_sub_order.back().second){
			for(int i=LMS_num-1;i>=0;i--){
				int c=lms_sub_order[i].first;
				SA[haba[S[c]].second-pos[S[c]]]=c;
				pos[S[c]]++;
			}
	
		}
		else{
			vector<int> rec((int)LMS.size());
			for(int i=0;i<LMS_num;i++){
				rec[LMS_id[lms_sub_order[i].first]]=lms_sub_order[i].second;
			}
			SAIS ss_naibu;
			ss_naibu.make_suffix_array_saiki(rec,lms_sub_order.back().second);
			
			for(int i=LMS_num;i>0;i--){
				int c=LMS[ss_naibu.SA[i]];
				SA[haba[S[c]].second-pos[S[c]]]=c;
				pos[S[c]]++;
			}
		}
		///////////////
		// 
		// 最後のinduced sort
		// 
		// 
		///////////////		
			induced_sort(SA,len,cnt);
			return;
	}
	
	void induced_sort(vector<int> &ve, int len,int cnt){
		vector<int> ue(cnt,0);
		for(int i=0;i<len;i++){
			if(ve[i]==-1) continue;
			if(ve[i]==0) continue;
			if(SL[ve[i]-1]==0){
				ve[haba[S[ve[i]-1]].first+ue[S[ve[i]-1]]]=ve[i]-1;
				ue[S[ve[i]-1]]++;
			}
			if(SL[ve[i]]<0 && i>0) ve[i]=-1;
		}
		for(int i=0;i<cnt;i++)ue[i]=0;
		
		for(int i=len-1;i>=0;i--){
			if(ve[i]==-1) continue;
			if(ve[i]==0) continue;
			if(SL[ve[i]-1]!=0){
				ve[haba[S[ve[i]-1]].second-ue[S[ve[i]-1]]]=ve[i]-1;
				ue[S[ve[i]-1]]++;
			}
		}
		for(auto v:ve)if(v==-1)assert(0);
	}
};
SAIS SA;