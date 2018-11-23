/*
文字列のinsertとdelete
入力の形式
i abc
i def
i xyz
d def
出力の形式
xyz abc
*/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}
typedef char* String;
typedef struct slobj_{
    String c;
    struct slobj_ *next;
    struct slobj_ *prev;
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

slobj slobj_new(String c){
    slobj p;
    NEW(p,1);
    p->c=c;
    p->next=NULL;
    p->prev=NULL;
    return p;
}

String string_input(){
    int c, i, len;
    char buf[1000];
    String str;
    scanf("%s", buf);
    len = strlen(buf);
    NEW(str, len+1);
    for (i=0; i<len; i++) {
        str[i] = buf[i];
    }
    str[len] =0;
    return str;
}

void slist_insert_head(slist L, slobj p){
    if(L->head == NULL){
        L->head = p;
        return;
    }
    p->next = L->head;
    L->head->prev = p;
    L->head = p;
}

slobj slist_search(slist L, String key){
    slobj p;
    p = L->head;
    while (p != NULL && strcmp(p->c, key) != 0) {
        p = p->next;
    }
    return p;
}

void slist_delete(slist L, String k){
    slobj q,r,s;
    q = slist_search(L,k);
    if(q == NULL) return;
    r = q->prev;
    s = q->next;
    if(r == NULL){
        if(s == NULL){
            L->head = NULL; return;
        }
        s->prev = NULL;
        L->head = s;
        return;
    }
    if(s == NULL){
        r->next = NULL;
        return;
    }
    else{
        s->prev = r;
        r->next = q->next;
    }
}

void slist_print(slist L){
    slobj p;
    p = L->head;
    while(p != NULL){
        printf("%s ",p->c);
        p = p->next;
    }
}

int main(void){
    int i, n;
    slist L;
    slobj p;
    String str;
    char buf[100];
    L = slist_new();
    while (1) {
        if (fscanf(stdin, "%s", buf)!=1) break; // 文字列を読み込めなければループを抜ける
        if (buf[0] == 'i'){ // 読み込んだ文字列の先頭が i のとき (注: “ ではない)
            str = string_input(stdin); // 挿入する文字列を str に読み込む
            slist_insert_head(L, slobj_new(str)); // リストの先頭に入れる
        }
        else if (buf[0] == 'd') { //読み込んだ文字列の先頭が d のとき
            str = string_input(stdin); //挿入する文字列を str に読み込む
            slist_delete(L, str); // str を含む要素をリストから削除する
            //if (p != NULL) slobj_free(p); // 削除した要素のメモリを開放する
            free(str); // str はもう不要なのでメモリを開放する
        }
    }
    slist_print(L); // 現在のリストを表示する
    //slist_free(L); // リストのメモリを開放する
    return 0;
}
