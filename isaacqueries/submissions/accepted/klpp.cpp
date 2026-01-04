#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long int lld;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
#define rep(i,a,b) for(int i=a;i<b;i++)
#define trav(a,v) for(auto a:v)
#define DEBUG false

lld sec[1000];
double score;
lld bitlen(lld X){
  int ans=0;
  while(X>0){
    X>>=1;
    ans+=1;
  }
  return ans-1;
}

lld query(int u, int v){
  u++;
  if(DEBUG){
    score+=1/((double)v-u+1);
    lld A=0;
    rep(i,u-1,v){
      A^=sec[i];
    }
    cout<<"Q "<<u<<" "<<v<<" "<<bitlen(A)<<endl;
    return bitlen(A);
  }else{
    cout<<"? "<<u<<" "<<v<<endl;
    lld A;
    cin>>A;
    return A;
  }
}

lld ANS[1000];


void res(vector<int> X){
  int mid=X.size()/2;
  int n=X.size();
  if(n==1)return;
  vector<int> ans(n,-1);
  ans[0]=0;
  int best=-1;
  rep(i,mid,n){
    int A=query(X[0],X[i]);
    if(A>best){
      best=A;
      rep(j,0,n){
        if(ans[j]>-1)ans[j]=0;
      }
    }
    if(A==best)ans[i]=1;
    else ans[i]=0;
  }

  rep(i,1,mid){
    int A=query(X[i],X[n-1]);
    if(A>best){
      best=A;
      rep(j,0,n){
        if(ans[j]>-1)ans[j]=0;
      }
    }
    if(A==best)ans[i]=ans[n-1]^1;
    else ans[i]=ans[n-1];
  }

  if(best==-1){
    return;
  }
  rep(i,0,n)assert(ans[i]!=-1);
  rep(i,0,n){
    if(ans[i]==1)ANS[X[i]]^=(1<<best);
  }
  vector<int> X1,X2;
  rep(i,0,n){
    if(ans[i]==0){
      X1.push_back(X[i]);
    }else X2.push_back(X[i]);
  }
  assert(X1.size()!=0);
  assert(X2.size()!=0);
  res(X1);
  res(X2);
}

int n;
void check(){
  if(DEBUG){
    rep(i,0,n)cout<<sec[i]<<" ";
    cout<<endl;
    rep(i,0,n)cout<<(ANS[i]^ANS[i+1])<<" ";
    cout<<endl;
    rep(i,0,n){
      rep(j,i,n){
        lld X1=0;
        rep(v,i,j+1){
          X1^=sec[v];
        }
        lld X2=ANS[i]^ANS[j+1];
        X1=bitlen(X1);
        X2=bitlen(X2);
        cout<<i<<" "<<j<<" "<<X1<<" "<<X2<<endl;
        assert(X1==X2);
      }
    }
    cout<<fixed<<setprecision(10)<<score<<endl;
  }else{
    cout<<"!"<<endl;
    rep(i,0,n){
      rep(j,i,n){
        cout<<bitlen(ANS[i]^ANS[j+1])<<" ";
      }cout<<endl;
    }
  }
}

void solve(){
  cin>>n;
  for (int i = 0; i < 1000; i++) ANS[i] = 0;
  if(DEBUG){
    score=0;
    rep(i,0,n)sec[i]=i;
  }

  vector<int> V;
  rep(i,0,n+1)V.push_back(i);
  res(V);
  check();
}

int main(){
	int tt=1;
	cin>>tt;

	while(tt--){
		solve();
	}
}
