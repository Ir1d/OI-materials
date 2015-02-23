#include<cstdio>
#include<cstring>
#include<algorithm>
#define f(x,y,z) for(int x = (y),__ = (z);x < __;++x)
#define fd(x,y,z) for(int x = (y),__ = (z);x > __;--x)
#define gd(x,y,z) for(int x = (y),__ = (z);x >= __;--x)
#define g(x,y,z) for(int x = (y),__ = (z);x <= __;++x)

#define MAXN 100024
int ans = 0;
inline int minn(int x,int y){
	if (x < y)return x;
	else return y;
}
inline int abs(int x){
	if (x > 0)return x;
	else return -x;
}


class SplayTree{
private:
	struct node{
		int key,val;
		node* ls,*rs,*fa;
	} *root,*tail,pool[MAXN];
	inline void rotate(node* &x){
		node* y = x->fa;
		node* z = y->fa;
		// if(x == y->ls)
		node* b = x == y->ls ? x->rs : x->ls;
		x->fa = z;y->fa = x;
		if (b)b->fa = y;
		if (z){
			if (z->ls == y)z->ls = x;
			else z->rs = x;
		}
		if (x == y->ls){
			x->rs = y;
			y->ls = b;
		}else {
			x->ls = y;
			y->rs = b;
		}
	}
	inline void splay(node* &x,node* target = NULL){
		while (x->fa != target){
			if (x->fa->fa != target){
				if ((x->fa->fa->ls == x->fa) == (x->fa->ls == x)){
					rotate(x->fa);
				}else rotate(x);
			}
			rotate(x);
		}
		if (target == NULL)root = x;
	}
	inline node* find(const int &key){
		node* p = root;
		while (p){
			if (key < p->key)p = p->ls;
			else if(key > p->key)p = p->rs;
			else {
				return p;
			}
		}
		return NULL;
	}

public:
	SplayTree(){
		root = NULL;
		tail = pool;
	}
	inline void insert(const int &key,const int &val){
		node** q = &root;
		node* fp = NULL;
		node* p = root;
		while (p){
			fp = p;
			if (key < p->key){
				q = &p->ls;p = p->ls;
			}else {
				q = &p->rs;p = p->rs;
			}
		}
		p = tail++;
		p->key = key;p->val = val;
		p->fa = fp;
		p->ls = p->rs = NULL;
		*q = p;
		splay(p);
	}
	inline int Find(const int &key){
		node* p = find(key);
		splay(p);
		return p->val;
	}
	inline node* pre(node* &o){
		node* ans = o->ls;
		if(ans)while (ans->rs)ans = ans->rs;
		return ans;
	}
	inline node* suc(node* &o){
		node* ans = o->rs;
		if(ans)while (ans->ls)ans = ans->ls;
		return ans;
	}
	inline void del(const int &key){
		node* p = find(key);
		splay(p);
		if(!p->ls && !p->rs){
			root = NULL;
		}else if (p->ls){
			root = p->rs;
			root->fa = NULL;
		}else if (!p->rs){
			root = p->ls;
			root->fa = NULL;
		}else {
			node* prev = pre(p);
			node* next = suc(p);
			splay(prev);
			splay(next,prev);
			next->ls = NULL;
		}
	}
	inline void get(const int & key){
		node* p = find(key);
		splay(p);
	}
	inline void solve(int tee){
		int te = 1 << 28;
		node* p = pre(root),*q = suc(root);
		// ans += minn(abs(p->val - tee),abs(q->val - tee));
		// printf("%d\n",te);
		if (p)te = minn(te,abs(p->val - tee));
		// printf("%d\n",te);
		if (q)te = minn(te,abs(q->val - tee));
		// printf("%d\n",te);
		
		if(te != (1 << 28))ans += te;
		else ans += tee;
		// printf("%d\n",ans);
		// puts("");
	}
	
} S;
int n,tee;
//6 5 1 2 5 4 6
int main(){
	scanf("%d",&n);
	f(i,0,n){
		if (scanf("%d",&tee) == -1)tee = 0;//BZOJ 1588 Êý¾ÝÓÐBUG
		S.insert(tee,tee);
		S.solve(tee);
		
	}
	printf("%d\n",ans);
	
	return 0;
}





 // sqr(exp(sqrt(sqr(ln(cos(atan(sqrt(x))))))))=x+1