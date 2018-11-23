/*
編集距離を動的計画法で解く

入力の形式
ACGTAT
CGCAT
動的計画法の表
      C G C A  T
   0  2 4 6 8 10
A  2  1 3 5 6  8
C  4  2 2 3 5  7
G  6  4 2 3 4  6
T  8  6 4 3 4  4
A 10  8 6 5 3  5
T 12 10 8 7 5  3
答え
3
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b, int c){
	return a > b ? (b > c ? c : b) : (a > c ? c : a);
}

//レーベンシュタイン距離を求める
int LevenshteinDistance(char *str1, char *str2){
	int lenstr1 = strlen(str1) + 1;
	int lenstr2 = strlen(str2) + 1;
	int d[lenstr1][lenstr2];
	int i1 = 0, i2 = 0, cost = 0;

	for (;i1 < lenstr1; i1++) d[i1][0] = 2*i1;
	for (;i2 < lenstr2; i2++) d[0][i2] = 2*i2;

	for (i1 = 1; i1 < lenstr1; i1++) {
		for (i2 = 1; i2 < lenstr2; i2++) {
			cost = str1[i1 - 1] == str2[i2 - 1] ? 0 : 1;
			d[i1][i2] = min(d[i1 - 1][i2] + 2, d[i1][i2 - 1] + 2, d[i1 - 1][i2 - 1] + cost);
		}
	}
	
	return d[lenstr1 - 1][lenstr2 - 1];
}

int main(void){
	char x[1001],y[1001];
    scanf("%s",x);
    scanf("%s",y);
	printf("%d\n", LevenshteinDistance(x, y));
    return 0;
}
