/*
疎行列の積
入力
5 5
1 1 2 2 -1
1 2 2 1 3 2 -1
2 2 3 1 -1
4 1 -1
5 1 -1
5 5
1 1 2 2 -1
1 2 2 1 3 2 -1
2 2 3 1 -1
4 1 -1
5 1 -1
出力
5 5
1 5.000000 2 4.000000 3 4.000000 -1
1 4.000000 2 9.000000 3 4.000000 -1
1 4.000000 2 4.000000 3 5.000000 -1
4 1.000000 -1
5 1.000000 -1
*/
#include<stdio.h>
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory¥n"); exit(1);};}
typedef struct slobj_ {
    struct slobj_ *next; // 後の要素へのポインタ
    int j; // j 列目
    double v; // (i, j) 要素
}* slobj;

typedef struct {
    slobj head; // 先頭要素のポインタ
    slobj tail;
}* slist;

typedef struct {
    int m,n;
    slist *R;
}* smatrix;

slist slist_new(){
    slist L;
    NEW(L,1);
    L->head=NULL;
    L->tail=NULL;
    return L;
}

slobj slobj_new(int j, double v){
    slobj p;
    NEW(p,1);
    p->j=j;
    p->v=v;
    p->next=NULL;
    return p;
}

void slist_insert_tail(slist L, slobj r){
    if(L->head == NULL){
        L->head = r;
        L->tail = r;
        L->tail->next = NULL;
    }
    else{
        L->tail->next = r;
        L->tail = r;
    }
}

smatrix create_smatrix(int m, int n){
    smatrix S;
    S = malloc(sizeof(smatrix));
    //S = NEW(S,1);
    S->R = malloc(m*sizeof(slist));
    S->m = m;
    S->n = n;
    int i;
    for(i=0; i<m ; i++){
        S->R[i]=slist_new();
    }
    return S;
}

void smatrix_insert(smatrix S, int i, int j, double v){
    slobj p;
    p = slobj_new(j,v);
    slist_insert_tail(S->R[i-1],p);
}

smatrix read_smatrix(){
    int m,n,i,j;
    double x;
    smatrix S;
    scanf("%d %d",&m,&n);
    S = create_smatrix(m,n);
    for(i=1; i<=m; i++){
        while(1){
            scanf("%d",&j);
            if(j==-1) break;
            scanf("%lf",&x);
            smatrix_insert(S,i,j,x);
        }
    }
    return S;
}

void print_smatrix(smatrix A){
    int m,n,i,j;
    double x;
    slobj p;
    m=A->m; n=A->n;
    printf("%d %d\n",m,n);
    for(i=0; i<m; i++){
        p=A->R[i]->head;
        while(p != NULL){
            printf("%d %lf ",p->j,p->v);
            p = p->next;
        }
        printf("%d \n",-1);
    }

}

double smatrix_access(smatrix S, int i, int j){
    double v;
    v=0;
    slobj p;
    p = S->R[i-1]->head;
    while(p != NULL){
        if(p->j == j){
            v= p->v;
            break;
        }
        p=p->next;
    }
    return v;
}

smatrix multiply_smatrix(smatrix A, smatrix B){
    int l,m,n,i,j,k;
    double x;
    smatrix C;
    if(A->n != B->m){
        C = create_smatrix(0,0);
    }
    else{
        l=A->m; m=A->n; n=B->n;
        C = create_smatrix(l,n);
        for(i=1; i<=l; i++){
            for(j=1; j<=n; j++){
                x = 0;
                for(k=1; k<=m; k++){
                    x += smatrix_access(A,i,k)*smatrix_access(B,k,j);
                }
                if(x != 0) smatrix_insert(C,i,j,x);
            }
        }
    }
    return C;
}

void free_smatrix(smatrix X){

}

int main(){
    smatrix A,B,C;
    A = read_smatrix();
    B = read_smatrix();
    C = multiply_smatrix(A,B);
    print_smatrix(C);
    return 0;
}
