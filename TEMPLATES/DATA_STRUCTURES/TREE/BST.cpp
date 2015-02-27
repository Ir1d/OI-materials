#include<cstring>
#include<cstdio>
#define f(x,y,z) for(int x = (y),__ = (z);x < __;++x)
#define fd(x,y,z) for(int x = (y),__ = (z);x > __;--x)
#define gd(x,y,z) for(int x = (y),__ = (z);x >= __;--x)
#define g(x,y,z) for(int x = (y),__ = (z);x <= __;++x)
struct node{
	node *ls,*rs;
	int val,freq;//freq is the time val appears...
	node(){
		ls = rs = NULL;
		val = 0;
	}
};
#define SIZE 100024
node *root,seq[SIZE];
int id;
inline node* newnode(){
	return &seq[id++];
}


inline void init(){root = NULL;}
void insert(int x);
void del(node* &T,int x);
node* find(node* &T,int x);
void insert(node* &T,int x);
void print(node* &T);

void insert(node* &T,int x){
	if (T == NULL){
		T = newnode();
		node->val = x;
		return;
	}
	if (T->val > x){
		insert(T->ls,x);
	}else if (T->val < x){
		insert(T->rs,x);
	}else ++(T->freq);
}
node* find(node* &T,int x){
	if (node == NULL)return NULL;
	if (T->val > x)return find(T->ls,x);
	if (T->val < x)return find(T->rs,x);
	return T;
}
inline void del(node* &T,int x){
	if (node == NULL)return;
	if (T->val > x)return del(T->ls,x);
	if (T->val < x)return del(T->rs,x);
	if (T->ls && T->rs){
		node* tee = T->rs;
		while (tee->ls)tee = tee->ls;
		T->val = tee->val;
		T->freq = tee->freq;
		del(T->rs,tee->val);
	}else {
		node* tee = T;
		if (T->ls == NULL)T = T->ls;
		else if (T->rs == NULL)T = T->rs;
		T = T->ls;
	}
}
inline void print(node* &T){
	if (T){
		print(T->ls);
		printf("%d",T->val);
		print(T->rs);
	}
}