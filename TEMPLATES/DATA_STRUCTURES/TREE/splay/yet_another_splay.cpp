#include <stdio.h>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

#define long long long
#define f1(i,n) for (int i=1; i<=n; i++)
#define f0(i,n) for (int i=0; i<n; i++)

struct node {
   int Size, Sum, Value;
   node *ll, *rr;
   bool Reverse;
   node(node* L, int AValue, node* R)
      { ll=L, rr=R; Sum=Value=AValue; Size=1, Reverse=false; }
} *Nil, *Root;

node* access(node* X){
   if (X==Nil) return NULL;
   if (X->Reverse){
      swap(X->ll, X->rr);
      if (X->ll!=Nil) X->ll->Reverse^=1;
      if (X->rr!=Nil) X->rr->Reverse^=1;
      X->Reverse=false;
   }
   return X;
}

node* update(node* X){
   if (!access(X)) return NULL;
   X->Size=X->ll->Size+X->rr->Size+1;
   X->Sum=X->ll->Sum+X->rr->Sum+X->Value;
   return X;
}

ostream& operator << (ostream& cout, node* X){
   if (!access(X)) return cout;
   return cout << "(" << X->ll << X->Value << X->rr << ")";
}

node* create(int ll, int rr, int a[]){
   if (ll>rr) return Nil;
   int mm = (ll+rr)/2;
   return update(new node(create(ll, mm-1, a), a[mm], create(mm+1, rr, a)));
}

// Splay, Split, Merge

stack<node*> Updates;

void update_now(stack<node*> &st=Updates)
   { while (st.size()) { update(st.top()); st.pop(); } }
node* link(node* L, node* X, node* R)
   { X->ll=L, X->rr=R, update(X); return X; }
node* llzig(node* X, node* L)
   { return link(L->ll, L, link(L->rr, X, X->rr)); }
node* rrzig(node* X, node* R)
   { return link(link(X->ll, X, R->ll), R, R->rr); }

node* get_splay(node* X, int Index){
   node Header(Nil, 0, Nil);
   node *Left=&Header, *Right=&Header;
   while (access(X)->ll->Size != Index) {
      if (access(X->ll) && Index<X->ll->ll->Size)
         { X=llzig(X, X->ll); continue; }
      if (access(X->rr) && Index>X->ll->Size+1+X->rr->ll->Size+1)
         { X=rrzig(X, X->rr); continue; }
      
      if (Index < X->ll->Size){
         node *P=X; X=X->ll;
         P->ll=Nil, update(P);
         Right->ll=P, Updates.push(Right);
         Right=Right->ll;
      }
      else {
         Index -= X->ll->Size+1;
         node *P=X; X=X->rr;
         P->rr=Nil, update(P);
         Left->rr=P, Updates.push(Left);
         Left=Left->rr;
      }
   }
   Left->rr=X->ll, Updates.push(Left);
   Right->ll=X->rr, Updates.push(Right);
   X->ll=Nil, X->rr=Nil, update(X);
   update_now();
   X->ll=Header.rr, X->rr=Header.ll, update(X);
   return X;
}

void split(node* X, int Index, node* &L, node* &R){
   if (Index==X->Size) { L=X, R=Nil; return; }
   X=access(get_splay(X, Index));
   L=X->ll, R=X;
   X->ll=Nil, update(X);
}

node* split(node* &X, int Index){
   node *L, *R;
   split(X, Index, L, R);
   return X=L, R;
}

node* merge(node* L, node* R){
   if (R==Nil) return L;
   R=access(get_splay(R, 0));
   return R->ll=L, update(R);
}

#define N 100005
int n, m, a[N];

main(){
   Root = Nil = new node(0, 0, 0);
   Nil->Size=0; Nil->ll=Nil->rr=Nil;
   scanf("%d", &n);
   f1(i,n) scanf("%d", &a[i]);
   Root = create(1, n, a);
// cout << Root << endl;

   scanf("%d", &m);
   while (m--){
      int x, y; char c;
      scanf(" %c%d%d", &c, &x, &y);
      if (c=='S') {
         Root=get_splay(Root, x-1);
         if (access(Root)) Root->Value=y, update(Root);
      }
      else if (c=='R') {
         node* R = split(Root, y);
         node* M = split(Root, x-1);
         if (access(M)) M->Reverse=true, update(M);
         Root = merge(Root, merge(M, R));
      }
      else if (c=='Q') {
         node* R = split(Root, y);
         node* M = split(Root, x-1);
         if (access(M)) cout << M->Sum << endl;
         Root = merge(Root, merge(M, R));
      }
//    cout << Root << endl;
   }
}
