//on BZOJ 3223
#include<cstdio>
#include<cstring>
#include<algorithm>
#define f(x,y,z) for(int x = (y),__ = (z);x < __;++x)
#define fd(x,y,z) for(int x = (y),__ = (z);x > __;--x)
#define gd(x,y,z) for(int x = (y),__ = (z);x >= __;--x)
#define g(x,y,z) for(int x = (y),__ = (z);x <= __;++x)

int ans = 0;
inline int minn(int x,int y){
	if (x < y)return x;
	else return y;
}
inline int abs(int x){
	if (x > 0)return x;
	else return -x;
}
struct node{
	int val,key;
	int flip,s;
	node *ch[2];
	inline int cmp(int k)const {
		int d = k - ch[0]->s;
		if (d == 1)return -1;
		if (d > 0)return 1;
		return 0;
	}
	inline void maintain(){
		s = ch[0]->s + ch[1]->s + 1;
	}
	inline void pushdown(){
		if(flip){
			flip = 0;
			std::swap(ch[0],ch[1]);
			ch[0]->flip ^= 1;
			ch[1]->flip ^= 1;
		}
	}
};
node* null = new node();

void rotate(node* &o,int d){
	node* k = o->ch[d ^ 1];
	o->ch[d ^ 1] = k->ch[d];
	k->ch[d] = o;
	o->maintain();
	k->maintain();
	o = k;
}
void splay(node* &o,int k){
	o->pushdown();
	int d = o->cmp(k);
	if (d == 1)k -= o->ch[0]->s + 1;
	if(d != -1){
		node* p = o->ch[d];
		p->pushdown();
		int d2 = p->cmp(k);
		int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);
		if(d2 != -1){
			splay(p->ch[d2],k2);
			if(d == d2){
				rotate(o,d ^ 1);
			}else rotate(o->ch[d],d);
		}
		rotate(o,d ^ 1);
	}
}
node* merge(node* left,node* right){
	splay(left,left->s);
	left->ch[1] = right;
	left->maintain();
	return left;
}
void split(node* &o,int k,node* &left,node* &right){
	splay(o,k);
	left = o;
	right = o->ch[1];
	o->ch[1] = null;
	left->maintain();
}
#define MAXN 100024
node* root;
int id = 0;
node seq[MAXN];
void insert(int v){
	node *p = &seq[++id];
	p->val = v;
	p->ch[0] = p->ch[1] = null;
	splay(root,root->s);
	root->ch[1] = p;
}
int v[MAXN];
struct SplaySequence{
	node* build(int sz){
		if(!sz)return null;
		node* L = build(sz >> 1);
		node* o = &seq[++id];
		// o->val = v[n];
		o->val = id;
		o->ch[0] = L;
		o->ch[1] = build(sz - (sz >> 1) - 1);
		o->flip = o->s = 0;
		o->maintain();
		return o;
	}
	void init(int sz){
		id = 0;
		null->s = 0;
		root = build(sz);
	}
} S;
// vector<int> ans;
int q;
void print(node* &o){
	if(o != null){
		o->pushdown();
		print(o->ch[0]);
		// ans.push_back(o->v);
		if(q++)printf("%d ",o->val - 1);
		print(o->ch[1]);
	}
}
node* pre(node* &x){
	node* p = x->ch[0];
	if(p != null)while (p->ch[1] != null)p = p->ch[1];
	return p;
}
node* suc(node* &x){
	node* p = x->ch[1];
	if(p != null)while (p->ch[0] != null)p = p->ch[0];
	return p;
}

//6 5 1 2 5 4 6	
int n,tee;
inline void get_min(int &x,int y){
	if (x > y)x = y;
}
inline void solve(int x){
	int tee = 1 << 28,te = tee;
	node *ll = pre(root),*rr = suc(root);
	if (ll != null)get_min(tee,abs(x - ll->val));
	// printf("%d\n",tee);
	if (rr != null)get_min(tee,abs(x - rr->val));
	// printf("%d\n\n",tee);
	if (tee != te)ans += tee;
	else ans += x;
}
int main(){
	scanf("%d",&n);
	// scanf("%d",&m);
	S.init(1);
	// print(S.root);
	f(i,0,n){
		if(scanf("%d",&tee) == -1)tee = 0;
		insert(tee);
		solve(tee);
	}
	printf("%d\n",ans);
	
	
	return 0;
}


