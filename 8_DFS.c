/*
DFS = deapth-first search
cf. BFS = breadth-first search
• 入力グラフのDFSを行う
• 出力は,DFSでの各点の親
• 親が無いときは -1 を出力
入力例
6 8
2 1 4 1 -1
5 1 -1
5 1 6 1 -1
2 1 -1
4 1 -1
6 6 -1
出力例
-1 1 -1 5 2 3

pdfを参照して
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

void DFS_Visit(graph G, int u, int* pi, int* color){
    int k;
    slobj p;
    color[u] = GRAY;
    p = G->E[u-1]->head;
    while(p != NULL){
        k = p->v;
        if(color[k] == WHITE){
            pi[k] = u;
            DFS_Visit(G,k,pi,color);
        }
        p = p->next;
    }
    color[u] = BLACK;
}

int* DFS(graph G){
    int n,u;
    int* color;
    int* pi;
    n = G->m;
    NEW(color, n+1);
    NEW(pi, n+1);
    for(u=1; u<=n; u++) color[u] = WHITE;
    for(u=1; u<=n; u++) pi[u] = -1;
    for(u=1; u<=n; u++) {
        if(color[u] == WHITE){
            DFS_Visit(G,u,pi,color);
        }
    }
    return pi;
}

int main(){
    int i,m;
    int* pi;
    graph G;
    G = graph_input();
    m = G->m;
    pi = DFS(G);
    for(i=1; i<=m; i++){
        printf("%d ",pi[i]);
    }
    printf("\n");
    return 0;
}
