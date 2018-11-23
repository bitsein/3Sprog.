#include "7_2_heap.h"
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

void heap_swap(heap H,int x, int y){
    int i,j; double v;

    i = H->inv[H->A[x].value];
    H->inv[H->A[x].value] = H->inv[H->A[y].value];
    H->inv[H->A[y].value] = i;

    j = H->A[x].priority;
    H->A[x].priority = H->A[y].priority;
    H->A[y].priority = j;

    v = H->A[x].value;
    H->A[x].value = H->A[y].value;
    H->A[y].value = v;
}

void heapify(heap H, int i){
    int l,r,smallest, size;
    heapdata* A;
    A = H->A; size = H->size;
    l = LEFT(i); r = RIGHT(i);
    if(l > size) return;
    else if(l == size){
        if(H->A[i].priority < H->A[l].priority) smallest = i;
        else smallest = l;
    }
    else{
        if(H->A[i].priority < H->A[l].priority) smallest = i;
        else smallest = l;
        if(H->A[r].priority < H->A[smallest].priority) smallest = r;
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
    inv = malloc((n+1)*sizeof(int));
    for(i=1; i<=n;i++){
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
    int n;
    n = H->size;
    h = H->A[1];
    i.priority = h.priority;
    i.value = h.value;
    H->inv[h.value] = -1;
    heap_swap(H,1,n);
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
    H->inv[x.value] = n+1;
    m = n+1;
    l = PARENT(m);
    if(l == 0) return;
    while(H->A[l].priority > H->A[m].priority){
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
    int m,n;
    n = i;
    m = PARENT(n);
    while(m != 0){
        heap_swap(m,n);
        n = m;
        m = PARENT(n);
    }
    heap_swap(1,H->size);
    H->size += -1;
    heapify(H,1);
}
