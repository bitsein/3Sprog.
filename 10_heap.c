#include "10_heap.h"
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)
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

void heap_swap(heap H,int x, int y){
    int i,j,a,b; double v;
    a = H->A[x].priority;
    b = H->A[y].priority;
    i = H->inv[a];
    H->inv[a] = H->inv[b];
    H->inv[b] = i;

    j = H->A[x].priority;
    H->A[x].priority = H->A[y].priority;
    H->A[y].priority = j;

    v = H->A[x].value;
    H->A[x].value = H->A[y].value;
    H->A[y].value = v;
}

void heapify(heap H, int i){
    int l,r,smallest, size;
    size = H->size;
    l = LEFT(i); r = RIGHT(i);
    if(l > size) return;
    else if(l == size){
        if(H->A[i].value < H->A[l].value) smallest = i;
        else smallest = l;
    }
    else{
        if(H->A[i].value < H->A[l].value) smallest = i;
        else smallest = l;
        if(H->A[r].value < H->A[smallest].value) smallest = r;
    }
    if (smallest != i) {
        heap_swap(H, i, smallest); // A[i]を子供と入れ替える
        heapify(H, smallest);
    }
}

heap heap_build(int n, heapdata* A, int max_size){
    int i;
    int* inv;
    heap H;
    NEW(H,1);
    H->max_size = max_size;
    H->size = n;
    H->A = A; // ヒープの構造体に配列 A をそのまま入れる (複製を作らない)
    NEW(inv,max_size+1);
    for(i=1; i<=max_size;i++){
        inv[i] = -1;
    }
    H->inv = inv;
    for (i = n/2; i >= 1; i--) {
        heapify(H,i);
    }
    return H;
}

heapdata heap_extract_max(heap H){
    heapdata h,i;
    int n,a;
    n = H->size;
    h = H->A[1];
    i.priority = h.priority;
    i.value = h.value;
    a = h.priority;
    heap_swap(H,1,n);
    H->inv[a] = -1;
    H->size = n-1;
    heapify(H,1);
    return i;
}

void heap_insert(heap H, heapdata x){
    int n,m,l;
    n = H->size;
    H->size = n+1;
    H->A[n+1].priority = x.priority;
    H->A[n+1].value = x.value;
    H->inv[x.priority] = n+1;
    m = n+1;
    l = PARENT(m);
    if(l == 0) return;
    while(H->A[l].value > H->A[m].value){
        heap_swap(H,l,m);
        m = l;
        l = PARENT(m);
        if(l == 0) break;
    }
}

int heap_exist(heap H, int j){
    int i;
    i = H->inv[j];
    if(i == -1) return 0;
    else return i;
}

void heap_delete(heap H, int i){//A[i]削除
    int m,n,l;
    l = H->size;
    n = i;
    m = PARENT(n);
    while(m != 0){
        heap_swap(H,m,n);
        n = m;
        m = PARENT(n);
    }
    heap_swap(H,1,l);
    H->size = l-1;
    heapify(H,1);
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
    NEW(G->E,m+1);
    for(i=1; i<=m; i++){
        G->E[i] = slist_new();
    }
    G->m = m; G->n = n;
    for(i=1; i<=m; i++){
        scanf("%d",&v);
        while(v != -1){
            scanf("%lf",&d);
            slist_append(G,v,d,i);
            scanf("%d",&v);
        }
    }
    return G;
}

void Dijkstra(graph G,int s,double *dist){
    int l,n;
    heap H;
    heapdata* A;
    heapdata h;
    dist[s] = 0;
    n = G->m;
    NEW(A,n+1);
    H = heap_build(0,A,n);
    for(l=1; l<=n; l++){
        h.priority = l;
        h.value = dist[l];
        heap_insert(H,h);
    }
    
    heapdata x;
    slobj p;
    int i,j,v;
    while(H->size != 0){
        x = heap_extract_max(H);
        v = x.priority;
        dist[v] = x.value;
        p = G->E[v]->head;
        while(p != NULL){
            j = p->v;
            i = heap_exist(H,j);
            if(i > 0){
                if(dist[j] > dist[v] + p->d){
                    dist[j] = dist[v] + p->d;
                    heap_delete(H,i);
                    x.priority = j;
                    x.value = dist[j];
                    heap_insert(H,x);
                }
            }
            p = p->next;
        }
    }
}
