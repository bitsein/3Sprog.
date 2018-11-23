/*
２つの数列の共通部分を昇順に出力
入力の形式
3 2 1 4 5 -1
4 6 2 -1
出力の形式
2 4 -1
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
    slobj p,q,s;
    p = L->head;
    s = slobj_new(r->key);
    while (p != NULL && p->key < r->key){
        q = p;
        p = p->next;
    }
    if(p == L->head){
        slist_insert_head(L,s);
    }
    else{
        s->next = q->next;
        q->next = s;
    }
}

slist slist_join(slist L1, slist L2){
    slist L3;
    L3 = slist_new();
    slobj p1, p2;
    p1 = L1->head; p2 = L2->head;
    while(p1 != NULL && p2 != NULL){
        if(p1->key == p2->key){
            slist_insert(L3,p1);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->key < p2->key){
            p1 = p1->next;
        }
        else p2 = p2->next;
    }
    return L3;
}

int main(){
    slist L1, L2, L3;
    slobj p;
    int x;
    L1 = slist_new();
    L2 = slist_new();
    while(1){
        scanf("%d",&x);
        if(x<0) break;
        p = slobj_new(x);
        slist_insert(L1,p);
    }
    while(1){
        scanf("%d",&x);
        if(x<0) break;
        p = slobj_new(x);
        slist_insert(L2,p);
    }
    L3 = slist_join(L1,L2);
    slist_print(L3);
    return 0;
}
