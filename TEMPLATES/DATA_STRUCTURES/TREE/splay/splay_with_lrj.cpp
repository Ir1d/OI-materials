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
	node *ch[2],*fa;
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
int v[MAXN];
struct SplaySequence{
	int id;
	node seq[MAXN];
	node* root;
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
int n,tee,m;
//5 3 1 3 1 3 1 4
int a,b;
int main(){
	scanf("%d",&n);
	scanf("%d",&m);
	S.init(n + 1);
	// print(S.root);
	
	while (m--){
		scanf("%d%d",&a,&b);
		node *left,*mid,*right,*o;
		split(S.root,a,left,o);
		split(o,b - a + 1,mid,right);
		mid->flip ^= 1;
		S.root = merge(merge(left,mid),right);
	}
	
	// printf("%d\n",ans);
	print(S.root);
	
	return 0;
}





 // sqr(exp(sqrt(sqr(ln(cos(atan(sqrt(x))))))))=x+1