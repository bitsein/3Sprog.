/*
入力例
i coffee コーヒー
i milk 牛乳
s milk
d milk
s milk
s coffee

出力例
milk 牛乳
Not found
coffee コーヒー
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0])); if ((p)==NULL) {printf("not enough memory¥n"); exit(1);};}
typedef char* String;
typedef struct slobj_ {
    struct slobj_* next; // 後の要素へのポインタ
    struct slobj_* prev;
    String eng; // 英語文字列
    String jpn; // 日本語文字列
}* slobj;

typedef struct{
    slobj head;
}* slist;

typedef struct {
    int n; // ハッシュに格納されている要素数
    int m; // ハッシュ表のサイズ
    slist *T; // リストの配列
}* hash;

slist slist_new(){
    slist L;
    NEW(L,1);
    L->head=NULL;
    return L;
}

slobj slobj_new(String stre, String strj){
    slobj p;
    NEW(p,1);
    p->eng = stre;
    p->jpn = strj;
    p->next=NULL;
    p->prev=NULL;
    return p;
}

int hash_func(String key) {
    int h = 0, i = 0;
    while (key[i] != 0) {
        h = h * 101 + key[i]; // ハッシュ値を計算
        i++;
    }
    return abs(h); // 非負の値にする
}//この値を mで割った余りをハッシュ値とする

slobj hash_search(hash H, String key){
    int h;
    slobj p;
    h = hash_func(key) % (H->m);
    p = H->T[h]->head;
    while(p != NULL && strcmp(p->eng, key) != 0){
        p = p->next;
    }
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

hash hash_new(int m){//nって何？
    hash H;
    H = malloc(sizeof(hash));
    H->T = malloc(m*sizeof(slist));
    H->m = m;
    H->n = 0;
    int i;
    for(i=0; i<m; i++){
        H->T[i] = slist_new();
    }
    return H;
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

void hash_insert(hash H, slobj obj){
    int h;
    String key;
    slobj p,q;
    key = obj->eng;
    p = hash_search(H,key);
    if(p != NULL) return;
    h = hash_func(obj->eng)%H->m;
    q = slobj_new(obj->eng,obj->jpn);
    slist_insert_head(H->T[h],q);
}

void hash_delete(hash H, String key){
    slobj p,r,s;
    slist L;
    int h;
    h = hash_func(key) % 100;
    L = H->T[h];
    p = L->head;
    while(p != NULL && strcmp(p->eng, key) != 0){
        p = p->next;
    }
    if(p == NULL) return;
    r = p->prev;
    s = p->next;
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
        r->next = p->next;
    }
}

int main(){
    int i, n;
    slobj p;
    String stre, strj;
    hash H;
    char buf[100];
    H = hash_new(100);
    p = H->T[0]->head;
    while (1) {
        if (fscanf(stdin, "%s", buf)!=1) break; // 文字列を読み込めなければループを抜ける
        if (buf[0] == 'i'){ // 読み込んだ文字列の先頭が i のとき (注: “ ではない)
            stre = string_input(stdin); // 挿入する文字列を str に読み込む
            strj = string_input(stdin);
            p = slobj_new(stre,strj);
            hash_insert(H,p);
        }
        else if (buf[0] == 'd') { //読み込んだ文字列の先頭が d のとき
            stre = string_input(stdin); //挿入する文字列を str に読み込む
            hash_delete(H, stre); // str を含む要素をリストから削除する
            //if (p != NULL) slobj_free(p); // 削除した要素のメモリを開放する
            free(stre); // str はもう不要なのでメモリを開放する
        }
        else if (buf[0] == 's') { //読み込んだ文字列の先頭が d のとき
            stre = string_input(stdin); //挿入する文字列を str に読み込む
            p = hash_search(H, stre); // str を含む要素をリストから削除する
            //if (p != NULL) slobj_free(p); // 削除した要素のメモリを開放する
            if(p == NULL){
                printf("Not found\n");
            }
            else{
                printf("%s %s\n",p->eng,p->jpn);
                free(stre); // str はもう不要なのでメモリを開放する
            }
        }
    }
    //slist_free(L); // リストのメモリを開放する
    return 0;
}
