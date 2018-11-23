#include<stdio.h>
#include<stdlib.h>
#include "7_2_heap.h"
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

int main(){
    int p;
    double x;
    int i,l,n,m,s,t;
    heap H;
    heapdata* A;
    heapdata h;

    scanf("%d",&l);
    scanf("%d",&n);
    NEW(A,n+1);
    H = heap_build(0,A,n);
    for(i=1; i<=n; i++){
        scanf("%d %lf",&p,&x);
        h.priority = p;
        h.value = x;
        heap_insert(H,h);
    }

    scanf("%d",&m);
    //printf("%d",H->A[1].priority);
    for(i=1; i<=m; i++){
        scanf("%d",&s);
        t = heap_exist(H,s);
        if(t != 0){
            printf("%lf\n",H->A[t].priority);
            heap_delete(H,t);
        }
        else printf("%d\n",-1);
    }
    
    return 0;
}
