#include<stdio.h>
#include<stdlib.h>

int refresh(int n,int* A, int* M){
    int i,j,k,len;
    len = 0;
    M[0] = -1;
    for(i=0;i<n;i++){
        scanf("%d",&A[i]);
        k=0;
        for(j=1;j<=len;j++){
            if((j == 1 || A[M[j-1]] < A[i]) && A[i] <= A[M[j]]){
                k = j; break;
            }
        }
        if(k==0){
            k = len + 1;
            len++;
        }
        M[k] = i;
    }
    return len;
}

int main(void){
    int i,n,len;
    int *A,*M;
    scanf("%d",&n);
    A = malloc(sizeof(int)*(n+1));
    M = malloc(sizeof(int)*(n+1));
    len = refresh(n,A,M);
    for(i=0;i<n;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
    printf("%d\n",len);
}