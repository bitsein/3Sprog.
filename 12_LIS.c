#include<stdio.h>
#include<stdlib.h>

int bisearch(int n,int* S, int k){
    int high,low,mid;
    low = 0; // 探索の範囲は最初は配列全体 [0..n-1]
    high = n-1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (S[mid] == k) { // 見つかった
            while(S[mid] == k){
                mid--;
            }
            return mid+1;
        }
        else if (S[mid] < k) {
            low = mid + 1; // 探索範囲を後半だけにする
        }
        else {
            high = mid - 1; // 探索範囲を前半だけにする
        }
    }
    return -1; // 見つからなかった
}

int main(void){
    int n,i,k,l,b,c;
    int *A;
    scanf("%d",&n);
    A = malloc(sizeof(int) * n);
    for(i=0;i<n;i++){
        scanf("%d",&A[i]);
    }
    scanf("%d",&k);
    for(i=0;i<n;i++){
        printf("%d ",A[i]);
    }
    b = bisearch(n,A,k);
    printf("\n");
    if(k < A[n-1] && b == -1){
        l = k-1;
        while(l>0){ 
            c = bisearch(n,A,l);
            if(c != -1){
                b = c+1;
                break;
            }
            l--;
        }
    }
    if(k <= 0) b = 0;
    if(k > A[n-1]) b = n;
    printf("%d",b);
    return 0;
}
