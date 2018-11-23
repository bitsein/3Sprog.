typedef int heapdata;
typedef struct {
    int max_size; // 配列 A に格納できる最大要素数
    int size; // ヒープに格納されている要素の数
    heapdata* A; // 要素を格納する配列
}* heap;

void heap_swap(heap H, int i,int largest);
void heapify(heap H, int i);
heap heap_build(int n, heapdata* A, int max_size);
void extract_max(heap H);
