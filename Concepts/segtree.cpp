/*

1. All ranges can be represented as 2*logn nodes
2. Merge should be possible. ansl and ansr is known, then ans should be known
3. Update answer of range update should be known
4. Combining updates should be known

*/

#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9;


template<typename node,typename update>
struct segtree
{
  int len;
  vector<node> t;
  vector<update> u;
  vector<bool> lazy;
  node identity_element;
  update identity_transformation;
  segtree(int l){
    len = l;
    t.resize(4 * len);
    u.resize(4 * len);
    lazy.resize(4 * len);
    identity_element = node(); // identity element i + x = x, x ->  
    identity_transformation = update(); // identity element for update operatuin
  }

  void pushdown(const int32_t &v, const int32_t &tl, const int32_t &tr){
    if(!lazy[v]) return;
    int32_t tm = (tl + tr) >> 1;
    apply(v<<1,tl,tm,u[v]);
    apply(v<<1|1,tm+1,tr,u[v]);
    u[v] = identity_transformation;
    lazy[v] = 0;
  }

  void apply(const int32_t &v, const int32_t &tl, const int32_t &tr, update upd){
    if(tl != tr){
      lazy[v] = 1;
      u[v].combine(upd,tl,tr);
    }
    upd.apply(t[v],tl,tr);
  }

  template<typename T>
  void build(const T &arr,const int32_t &v, const int32_t &tl, const int32_t &tr){
    if(tl == tr){
      t[v] = arr[tl];
      return;
    }
    int32_t tm = (tl + tr) >> 1;
    build(arr,v<<1,tl,tm);
    build(arr,v<<1|1,tm+1,tr);
    t[v].merge(t[v<<1],t[v<<1|1]);
  }

  node query(const int32_t &v,const int32_t &tl,const int32_t &tr,const int32_t &l,const int32_t &r){
    if(l > tr || r < tl){
      return identity_element;
    }
    if(tl >= l && tr <= r){
      return t[v];
    }
    pushdown(v,tl,tr);
    int32_t tm = (tl + tr) >> 1;
    node a = query(v<<1,tl,tm,l,r),b = query(v<<1|1,tm+1,tr,l,r),ans;
    ans.merge(a,b);
    return ans;
  }

  // rupd = range update
  void rupd(const int32_t &v,const int32_t &tl,const int32_t &tr,const int32_t &l,const int32_t &r,const update &upd){
    if(l > tr || r < tl){
      return;
    }
    if(tl >= l && tr <= r){
      apply(v,tl,tr,upd);
      return;
    }
    pushdown(v,tl,tr);
    int32_t tm = (tl + tr) >> 1;
    rupd(v<<1,tl,tm,l,r,upd);
    rupd(v<<1|1,tm+1,tr,l,r,upd);
    t[v].merge(t[v<<1],t[v<<1|1]);
  }

  public:
  template<typename T>
  void build(const T &arr){
    build(arr,1,0,len-1);
  }
  node query(const int32_t &l,const int32_t &r){
    return query(1,0,len-1,l,r);
  }
  void rupd(const int32_t &l,const int32_t &r,const update &upd){
    rupd(1,0,len-1,l,r,upd)
  }
};


struct node
{
  int mn = INF;
  int freq = 0;
  node(){}
  node(int val){ // val is what you get from array, fill it in segtree here
    mn = val;
    freq = 1;
  }
  void merge(const node &l,const node &r){ // 2 nodes combine how.
    mn = min(l.mn,r.mn);
    freq = 0;
    if(l.mn == mn) freq += l.freq;
    if(r.mn == mn) freq += r.freq;
  }
};

struct update
{
  int v = 0;
  update(){}
  update(int val){
    v = val;
  }
  void combine(update &other,const int32_t &tl,const int32_t &tr){ // other is new UPDATE, v has currVal, v <- new value 
    v += other.v;
  }
  void apply(node &x,const int32_t &tl,const int32_t &tr){
    x.mn += v;
  }
};
