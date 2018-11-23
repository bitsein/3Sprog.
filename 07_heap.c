#include "7_heap.h"
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}
#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

void heap_swap(heap H,int i, int largest){
    int j;
    j = H->A[i];
    H->A[i] = H->A[largest];
    H->A[largest] = j;
}

void heapify(heap H, int i){
    int l,r,largest, size;
    heapdata* A;
    A = H->A; size = H->size;
    l = LEFT(i); r = RIGHT(i);
    if(l > size) return;
    else if(l == size){
        if(H->A[i] > H->A[l]) largest = i;
        else largest = l;
    }
    else{
        if(H->A[i] > H->A[l]) largest = i;
        else largest = l;
        if(H->A[r] > H->A[largest]) largest = r;
    }
    if (largest != i) {
        heap_swap(H, i, largest); // A[i]を子供と入れ替える
        heapify(H, largest);
    }
}

heap heap_build(int n, heapdata* A, int max_size){
    int i;
    heap H;
    NEW(H,1);
    H->max_size = max_size;
    H->size = n;
    H->A = A; // ヒープの構造体に配列 A をそのまま入れる (複製を作らない)
    for (i = n/2; i >= 1; i--) {
        heapify(H,i);
    }
    return H;
}

void extract_max(heap H){
    int n;
    n = H->size;
    heap_swap(H,1,n);
    H->size = n-1;
    heapify(H,1);
}


