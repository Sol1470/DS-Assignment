#include <stdio.h>
#include <stdlib.h>
int compare(const void* a, const void* b);

void sortArrWithExp(int**arr, int polyNum1, int polyNum2){
    
    qsort(arr, polyNum1, sizeof(int*), compare);
    qsort(arr + polyNum1, polyNum2, sizeof(int*), compare);
    printf("sort in func\n");
}

void writeFile(){

}
void naivePoly(){

}
void improvedPoly(){
    
}
void linkedPoly(){

}
void naivePolyAdd(){
    
}
void improvedPolyAdd(){
    
}
void linkedPolyAdd(){

}
int main() {
    FILE* fp = NULL;
    fp = fopen("input.txt","r");
    if(fp == NULL){
        printf("File open ERROR\n");
        return 0;
    }
    int polyNum1, polyNum2; //다항식의 항의 갯수
    int** arr = NULL; //input.txt에서 데이터를 가져오는 포인터
    int sumNum = 0;
    int i, j;

    fscanf(fp,"%d\t%d",&polyNum1, &polyNum2);
    printf("read txt n1 n2\n");
    sumNum = polyNum1 + polyNum2;
    
    arr = malloc(sizeof(int*)*sumNum);
    for(int i = 0; i < sumNum; i++){
        arr[i]=malloc(sizeof(int)*2);
    }
    printf("malloc arr\n");
    for(int i = 0; i < sumNum; i++){
        fscanf(fp,"%d\t%d", &arr[i][0], &arr[i][1]);
    }
    fclose(fp);
    printf("read txt all and fclose fp\n");

    printf("before sort:\n");
    for (int i = 0; i < sumNum; i++) {
        printf("arr[%d] = %d\t%d\n", i, arr[i][0], arr[i][1]);
    }

    sortArrWithExp(arr, polyNum1, polyNum2);

    printf("sort\n");

    printf("result:\n");
    for (int i = 0; i < sumNum; i++) {
        printf("arr[%d] = %d\t%d\n", i, arr[i][0], arr[i][1]);
    }
    for (int i = 0; i < sumNum; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}
int compare(const void* a, const void* b){
    const int *A = *(const int **)a;
    const int *B = *(const int **)b;
    printf("compare: A[1]=%d, B[1]=%d\n", A[1], B[1]);
    return B[1] - A[1];
}