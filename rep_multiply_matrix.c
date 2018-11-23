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

smatrix create_smatrix(int m, int n){
    smatrix S;
    S = malloc(sizeof(smatrix));
    S->R = malloc(m*sizeof(slist));
    S->m = m;
    S->n = n;
    int i;
    for(i=0; i<m ; i++){
        S->R[i]=slist_new();
    }
    return S;
}

void slist_insert_tail(slist L, slobj r){
    if(L->head == NULL){
        L->head = r;
        L->tail = r;
    }
    else{
        L->tail->next = r;
        L->tail = r;
    }
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
    int i,j,m;
    double x;
    slobj p;
    m = A->m;
    printf("%d %d\n",m, m);
    for(i=0; i<m; i++){
        p=A->R[i]->head;
        while(p != NULL){
            printf("%d %lf ",p->j,p->v);
            p = p->next;
        }
        printf("%d \n",-1);
    }

}

smatrix transpose_smatrix(smatrix A){
    int m,i,j;
    double v;
    slobj p;
    smatrix S;
    m = A->m;
    S = create_smatrix(m,m);
    for(i=0; i<m; i++){
        p = A->R[i]->head;
        while(p != NULL){
            j = p->j; v = p->v;
            smatrix_insert(S,j,i+1,v);
            p = p->next;
        }
    }
    return S;
}

double slist_join(slist L1, slist L2){
    slobj p1, p2;
    double v; v = 0;
    p1 = L1->head; p2 = L2->head;
    while(p1 != NULL && p2 != NULL){
        if(p1->j == p2->j){
            v += p1->v * p2->v;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->j < p2->j){
            p1 = p1->next;
        }
        else p2 = p2->next;
    }
    return v;
}

smatrix multiply_smatrix(smatrix A){
    int m,i,j;
    double x;
    slist L; slobj p;
    m = A->m;
    smatrix B,C;
    B = transpose_smatrix(A);
    C = create_smatrix(m, m);
    for(i=0; i<m; i++){
        for(j=0; j<m; j++){
            x = 0;
            x += slist_join(A->R[i], B->R[j]);
            if(x != 0) smatrix_insert(C,i+1,j+1,x);
        }
    }
    return C;
}

int main(){
    smatrix A,B;
    A = read_smatrix();
    B = multiply_smatrix(A);
    print_smatrix(B);
    return 0;
}