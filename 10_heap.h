typedef struct {
    int priority;
    double value;
} heapdata;

typedef struct {
    int max_size; // 配列 A に格納できる最大要素数
    int size; // ヒープに格納されている要素の数
    heapdata* A; // 要素を格納する配列
    int* inv;
}* heap;

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

slist slist_new();
slobj slobj_new(int v, double d);
void heap_swap(heap H, int x,int y);
void heapify(heap H, int i);
heap heap_build(int n, heapdata* A, int max_size);
heapdata heap_extract_max(heap H);
void heap_insert(heap H, heapdata x);
int heap_exist(heap H, int j);
void heap_delete(heap H, int i);
void slist_append(graph G,int v,double d,int m);
graph graph_input();
void Dijkstra(graph G,int s,double *dist);