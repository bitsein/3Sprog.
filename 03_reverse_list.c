/*
入力したリストを逆順に出力する
入力の形式
3 2 1 3 5 -1
出力の形式
5 3 1 2 3 -1
*/
#include<stdio.h>
#include<stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}
typedef struct slobj_{
    int key;
    struct slobj_ *next;
}* slobj;

typedef struct{
    slobj head;
}* slist;


slist slist_new(){
    slist L;
    NEW(L,1);
    L->head=NULL;
    return L;
}

slobj slobj_new(int x){
    slobj p;
    NEW(p,1);
    p->key=x;
    p->next=NULL;
    return p;
}

void slist_insert_head(slist L, slobj p){
    p->next=L->head;
    L->head=p;
}

void slist_print(slist L){
    slobj p;
    p = L->head;
    while(p != NULL){
        printf("%d ",p->key);
        p = p->next;
    }
    printf("%d \n",-1);
}

void slist_insert(slist L, slobj r){

}

slobj slist_search(slist L, int k){
    slobj p;
    p = L->head;
    while (p != NULL && p->key != k) {
        p = p->next;
    }
    return p;
}

slist slist_join(slist L1, slist L2){

}

int main(){
    slist L;
    slobj p;
    int x;
    L = slist_new();
    while(1){
        scanf("%d",&x);
        if(x<0) break;
        p = slobj_new(x);
        slist_insert_head(L,p);
    }
    slist_print(L);
    return 0;
}
