/*
SCC = strongly connected component
SCCはDFS２回で計算できる（よくわからんかった）
入力グラフの強連結成分分解を行う
出力は,各点の親 (P) の値

入力例
8 14
2 1 5 1 -1
3 1 4 1 -1
2 1 -1
4 1 -1
1 1 4 1 -1
1 1 3 1 7 1 -1
3 1 8 1 -1
6 1 -1
出力例
-1 -1 2 -1 1 -1 8 6
*/
#include<stdio.h>
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}
#define WHITE 0
#define GRAY 1
#define BLACK 2
typedef struct slobj_ {
    struct slobj_ *next;
    int v;
    double d;
}* slobj;

typedef struct{
    slobj head;
}* slist;

typedef struct{
    int m;
    int n;
    slist* E;
}* graph;

slist slist_new(){
    slist L;
    NEW(L,1);
    L->head=NULL;
    return L;
}

slobj slobj_new(int v, double d){
    slobj p;
    NEW(p,1);
    p->v=v;
    p->d=d;
    p->next = NULL;
    return p;
}

void slist_append(graph G,int v,double d,int m){
    slobj p,x;
    p = G->E[m]->head;
    if(p == NULL){
        x = slobj_new(v,d);
        G->E[m]->head = x; return;
    }
    while(p->next != NULL){
        p = p->next;
    }
    x = slobj_new(v,d);
    p->next = x;
}

graph graph_input(){
    graph G;
    int m,n,i,v;
    double d;
    scanf("%d %d",&m,&n);
    NEW(G,1);
    NEW(G->E,m);
    for(i=0; i<m; i++){
        G->E[i] = slist_new();
    }
    G->m = m; G->n = n;
    for(i=0; i<m; i++){
        scanf("%d",&v);
        while(v != -1){
            scanf("%lf",&d);
            slist_append(G,v,d,i);
            scanf("%d",&v);
        }
    }
    return G;
}

void DFS_Visit(graph G, int u, int* pi, int* color, int* t, int* d){
    int k,n;
    n = G->m;
    slobj p;
    color[u] = GRAY;
    t[0]++;
    d[u] = t[0];
    p = G->E[u-1]->head;
    while(p != NULL){
        k = p->v;
        if(color[k] == WHITE){
            pi[k] = u;
            DFS_Visit(G,k,pi,color,t,d);
        }
        p = p->next;
    }
    color[u] = BLACK;
    t[0]++;
    d[u+n] = t[0];
}

int* DFS(graph G){
    int n,u;
    int* color;
    int* pi;
    int *d, *t;
    n = G->m;
    NEW(color, n+1);
    NEW(pi, n+1);
    NEW(d, 2*n+1);
    NEW(t, 1);
    for(u=1; u<=n; u++) color[u] = WHITE;
    for(u=1; u<=n; u++) pi[u] = -1;
    t[0] = 0;
    for(u=1; u<=n; u++) {
        if(color[u] == WHITE){
            DFS_Visit(G,u,pi,color,t,d);
        }
    }
    return d;
}

void slist_insert_tail(slist L, slobj r){
    if(L->head == NULL){
        L->head = r;
    }
    else{
        slobj p;
        p = L->head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = r;
    }
}

void graph_insert(graph GT, int i, int j,double d){
    slobj p;
    p = slobj_new(j,d);
    slist_insert_tail(GT->E[i-1],p);
}

graph transpose(graph G){
    int m,n,v,i;
    double d;
    slobj p;
    graph GT;
    m = G->m;
    n = G->n;
    NEW(GT,1);
    NEW(GT->E,m);
    for(i=0; i<m; i++){
        GT->E[i] = slist_new();
    }
    GT->m = m; GT->n = n;

    for(i=0; i<m; i++){
        p = G->E[i]->head;
        while(p != NULL){
            v = p->v;
            graph_insert(GT,v,i+1,d);
            p = p->next;
        }
    }
    return GT;
}

int* ord(graph G,int* d){
    int i,k,m;
    int *ord, *ord_tmp;
    m = G->m;
    NEW(ord, m+1);
    NEW(ord_tmp, 2*m+1);
    for (i=1; i<=2*m; i++) ord_tmp[i] = -1;
    for (i=1; i<=m; i++) ord_tmp[d[i+m]] = i;
    k = 0;
    for (i=2*m; i>=1; i--){
        if (ord_tmp[i] != -1){
            k++;
            ord[k] = ord_tmp[i];
        }
    }
    free(ord_tmp);
    return ord;
}

int* graph_DFS2(graph G, int* ord, int* d){
    int n,u,i;
    int* color;
    int* pi;
    int *t;
    n = G->m;
    NEW(color, n+1);
    NEW(pi, n+1);
    NEW(t, 1);
    for(u=1; u<=n; u++) color[u] = WHITE;
    for(u=1; u<=n; u++) pi[u] = -1;
    t[0] = 0;
    for(i=1; i<=n; i++) {
        u = ord[i];
        if(color[u] == WHITE){
            DFS_Visit(G,u,pi,color,t,d);
        }
    }
    return pi;
}

int* SCC(graph G){
    int m;
    int *d, *o, *pi;
    graph GT;
    m = G->m;
    d = DFS(G);
    o = ord(G,d);
    GT = transpose(G);
    pi = graph_DFS2(GT,o,d);
    return pi;
}

int main(){
    int i,m;
    int* pi;
    graph G;
    G = graph_input();
    m = G->m;
    pi = SCC(G);
    for(i=1; i<=m; i++){
        printf("%d ",pi[i]);
    }
    printf("\n");
    return 0;
}
