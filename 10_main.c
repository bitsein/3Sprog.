#include<stdio.h>
#include<stdlib.h>
#include "10_heap.h"
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}

int main(){
    int i,m;
    graph G;
    G = graph_input();
    m = G->m;
    double* dist;
    NEW(dist,m+1);
    for(i=1;i<=m;i++){
        dist[i] = 999999;
    }
    Dijkstra(G,1,dist);
    for(i=1;i<=m;i++){
        printf("%d %lf\n",i,dist[i]);
    }
    return 0;
}
