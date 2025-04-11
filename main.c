#include <stdio.h>
#include <stdlib.h>
int compare(const void* a, const void* b);

void sortArrWithExp(int**arr, int polyNum1, int polyNum2){
    
    qsort(arr, polyNum1, sizeof(int*), compare);
    qsort(arr + polyNum1, polyNum2, sizeof(int*), compare);
    printf("sort in func\n");
}

void writeFileLinkedList(){

}
void writePoly(int* poly, int size){
    FILE* fp = fopen("output.txt","w");
    for(int i = 0; i < size; i++){
        if(poly[i] == 0) continue;
        
        fprintf(fp, "%dx^%d", poly[i], size - i - 1);

        if(i != size - 1) fprintf(fp, " + ");
        else fprintf(fp, "\n");
    }
}
void naivePoly(int**arr, int polyNum1, int polyNum2){
    int sizePoly1 = arr[0][1]+1;
    int sizePoly2 = arr[polyNum1][1]+1;
    int sizeResultPoly = sizePoly1 > sizePoly2 ? sizePoly1 : sizePoly2;
    int polyindex = 0, arrindex = 0;
    int* poly1 = malloc(sizeof(int)*sizePoly1);
    int* poly2 = malloc(sizeof(int)*sizePoly2);
    int* resultPoly = malloc(sizeof(int)*sizeResultPoly);

    for(int i = 0; i < sizePoly1; i++){
        if(arr[arrindex][1] == sizePoly1 - 1 - polyindex){
            poly1[polyindex++] = arr[arrindex++][0];
        }
        else {
            poly1[polyindex++] = 0;
            continue;
        }
        
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
        
    }

    naivePolyAdd(poly1, poly2, resultPoly, arr[0][1], arr[polyNum1][1]);
    writePoly(poly1, sizePoly1);
    writePoly(poly2, sizePoly2);

    free(poly1);
    free(poly2);
    free(resultPoly);
}
void improvedPoly(int**arr, int polyNum1, int polyNum2){
    int startA = 0, finishA = polyNum1 - 1, startB = polyNum1, finishB = polyNum2 - 1, avail = polyNum2;
    int totalNum = polyNum1 + polyNum2;
    int**polyArr = malloc(sizeof(int)*2);
    for(int i = 0; i < 2; i++){
        polyArr[i] = malloc(sizeof(int)*(totalNum+(polyNum1 > polyNum2 ? polyNum1 + 1 : polyNum2 + 1)));
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < totalNum; j++){
            polyArr[i][j] = arr[j][i];
        }
    }
    printf("Check PolyArr\n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < totalNum; j++){
            printf("%d\t", polyArr[i][j]);
        }
        printf("\n");
    }
    
}
void linkedPoly(){

}
void naivePolyAdd(int* poly1, int* poly2, int* resultPoly, int polyNum1, int polyNum2){
    int sizeResultPoly = (polyNum1 > polyNum2 ? polyNum1 : polyNum2) + 1;
    int sizePoly1 = polyNum1 + 1, sizePoly2 = polyNum2 + 1;
    
    for(int i = 0; i < sizeResultPoly; i++){
        int valuePoly1 = (i < sizePoly1) ? poly1[i] : 0;
        int valuePoly2 = (i < sizePoly2) ? poly2[i] : 0;
        resultPoly[i] = valuePoly1 + valuePoly2;
    }
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
    sumNum = polyNum1 + polyNum2;
    
    arr = malloc(sizeof(int*)*sumNum);
    for(int i = 0; i < sumNum; i++){
        arr[i]=malloc(sizeof(int)*2);
    }
    for(int i = 0; i < sumNum; i++){
        fscanf(fp,"%d\t%d", &arr[i][0], &arr[i][1]);
    }
    fclose(fp);

    printf("before sort:\n");
    for (int i = 0; i < sumNum; i++) {
        printf("arr[%d] = %d\t%d\n", i, arr[i][0], arr[i][1]);
    }

    sortArrWithExp(arr, polyNum1, polyNum2);

    printf("result:\n");
    for (int i = 0; i < sumNum; i++) {
        printf("arr[%d] = %d\t%d\n", i, arr[i][0], arr[i][1]);
    }

    naivePoly(arr, polyNum1, polyNum2);
    improvedPoly(arr, polyNum1, polyNum2);


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