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
void naivePoly(int**arr, int polyNum1, int polyNum2){
    int sizePoly1 = arr[0][1]+1;
    int sizePoly2 = arr[polyNum1][1]+1;
    int polyindex = 0, arrindex = 0;
    int* poly1 = malloc(sizeof(int)*sizePoly1);
    int* poly2 = malloc(sizeof(int)*sizePoly2);
    printf("arr[0][1] = %d, arr[polyNum1][1] = %d\n",arr[0][1], arr[polyNum1][1]);
    for(int i = 0; i < sizePoly1; i++){
        if(arr[arrindex][1] == sizePoly1 - 1 - polyindex){
            poly1[polyindex++] = arr[arrindex++][0];
        }
        else {
            poly1[polyindex++] = 0;
            continue;
        }
        printf("arr[%d][1] = %d, sizePoly1 - temp = %d\n", i, arr[arrindex - 1][1], sizePoly1 - polyindex);
    }
    polyindex = 0;
    for(int i = 0; i < sizePoly2; i++){
        if(arr[arrindex][1] == sizePoly2 - 1 - polyindex){
            poly2[polyindex++] = arr[arrindex++][0];
        }
        else {
            poly2[polyindex++] = 0;
            continue;
        }
        printf("arr[%d][1] = %d, sizePoly2 - temp = %d\n", i, arr[arrindex - 1][1], sizePoly2 - polyindex);
    }
    printf("naive poly check:\n");
    for(int i = 0; i < sizePoly1; i++){
        printf("poly1[%d] = %d\n", i, poly1[i]);
    }
    for(int i = 0; i < sizePoly2; i++){
        printf("poly2[%d] = %d\n", i, poly2[i]);
    }
    naivePolyAdd(poly1, poly2, arr[0][1], arr[polyNum1][1]);
}
void improvedPoly(){
    
}
void linkedPoly(){

}
void naivePolyAdd(int* poly1, int* poly2, int polyNum1, int polyNum2){
    int sizeResultPoly = (polyNum1 > polyNum2 ? polyNum1 : polyNum2) + 1;
    int* resultPoly = malloc(sizeof(int)*sizeResultPoly);
    int indexPoly1 = 0, indexPoly2 = 0;
    printf("sizeResultPoly = %d\n", sizeResultPoly);
    printf("polyNum1 = %d, polyNum2 = %d\n", polyNum1, polyNum2);
    printf("poly1 value: \n");
    for(int i = 0; i < polyNum1+1; i++){
        printf("poly1[%d] = %d\n",i ,poly1[i]);
    }
    printf("poly2 value:\n");
    for(int i = 0; i < polyNum2+1; i++){
        printf("poly2[%d] = %d\n",i ,poly2[i]);
    }
    
    for(int i = 0; i < sizeResultPoly; i++){
        if(polyNum1 == polyNum2){
            resultPoly[i] = poly1[indexPoly1++] + poly2[indexPoly2++];
            polyNum1--;
            polyNum2--;
        }
        else if(polyNum1 > polyNum2){
            resultPoly[i] = poly1[indexPoly1++];
            polyNum1--;
        }
        else if(polyNum1 < polyNum2--){
            resultPoly[i] = poly2[indexPoly2++];
            polyNum2--;
        }
    }
    printf("Result : \n");
    for(int i = 0; i < sizeResultPoly; i++){
        printf("resultPoly[%d] = %d\n", i, resultPoly[i]);
    }
    writeFile();
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
    printf("read txt n1 = %d, n2 = %d\n", polyNum1, polyNum2);
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

    naivePoly(arr, polyNum1, polyNum2);

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