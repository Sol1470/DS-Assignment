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
void writeNaivePoly(int* poly, int size){
    FILE* fp = fopen("output.txt","a");
    for(int i = 0; i < size; i++){
        if(poly[i] == 0) continue;
        
        fprintf(fp, "%dx^%d", poly[i], size - i - 1);

        if(i == size - 1) fprintf(fp, "\n");
        else fprintf(fp, " + ");
    }
    fclose(fp);
}
void writeImprovedPoly(int**poly, int startA, int startB, int finishA, int finishB, int startC, int finishC){
    FILE* fp = fopen("output.txt", "a");
    for(int i = startA; i < finishA + 1; i++){
        fprintf(fp, "%dx^%d", poly[0][i], poly[1][i]);
        if(i == finishA) fprintf(fp, "\n");
        else fprintf(fp, " + ");
    }
    for(int i = startB; i < finishB + 1; i++){
        fprintf(fp, "%dx^%d", poly[0][i], poly[1][i]);
        if(i == finishB) fprintf(fp, "\n");
        else fprintf(fp, " + ");
    }
    for(int i = startC; i < finishC + 1; i++){
        fprintf(fp, "%dx^%d", poly[0][i], poly[1][i]);
        if(i == finishC) fprintf(fp, "\n");
        else fprintf(fp, " + ");
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
    writeNaivePoly(poly1, sizePoly1);
    writeNaivePoly(poly2, sizePoly2);
    writeNaivePoly(resultPoly, sizeResultPoly);
    free(poly1);
    free(poly2);
    free(resultPoly);
}
void improvedPoly(int**arr, int polyNum1, int polyNum2){
    int startA = 0;
    int finishA = startA + polyNum1 - 1;
    int startB = finishA + 1;
    int finishB = startB + polyNum2 - 1;
    int avail = finishB + 1;
    int totalNum = polyNum1 + polyNum2;
    int finishC = totalNum + (polyNum1 > polyNum2 ? polyNum1 : polyNum2);
    int**polyArr = malloc(sizeof(int)*2);

    printf("startA : %d, startB : %d\nfinishA : %d, finishB : %d\navail : %d\n", startA, startB, finishA, finishB, avail);

    for(int i = 0; i < 2; i++){
        polyArr[i] = malloc(sizeof(int)*finishC);
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
    improvedPolyAdd(polyArr, startA, startB, finishA, finishB, avail);
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < finishC; j++){
            printf("%d\t", polyArr[i][j]);
        }
        printf("\n");
    }
    writeImprovedPoly(polyArr, startA, startB, finishA, finishB, avail, finishC);
}
void linkedPoly(){

}
void naivePolyAdd(int* poly1, int* poly2, int* resultPoly, int polyNum1, int polyNum2){
    int sizeResultPoly = (polyNum1 > polyNum2 ? polyNum1 : polyNum2) + 1;
    int indexPoly1 = 0, indexPoly2 = 0;
    
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
}

void improvedPolyAdd(int**polyArr, int startA, int startB, int finishA, int finishB, int avail){
    while(startA <= finishA && startB <= finishB){
        if(polyArr[1][startA] < polyArr[1][startB]){
            polyArr[0][avail] = polyArr[0][startB];
            polyArr[1][avail] = polyArr[1][startB];
            startB++;
            avail++;
        }
        else if(polyArr[1][startA] == polyArr[1][startB]){
            polyArr[0][avail] = polyArr[0][startA] + polyArr[0][startB];
            polyArr[1][avail] = polyArr[1][startA];
            startA++;
            startB++;
            avail++;
        }
        else{
            polyArr[0][avail] = polyArr[0][startA];
            polyArr[1][avail] = polyArr[1][startA];
            startA++;
            avail++;
        }
    }
    
}
void linkedPolyAdd(){

}
int main() {
    FILE* fp = NULL;
    FILE* fp2 = NULL;
    fp = fopen("input.txt","r");
    if(fp == NULL){
        printf("File open ERROR\n");
        return 0;
    }

    fp2 = fopen("output.txt","w");
    if(fp2 == NULL){
        printf("File open ERROR\n");
        return 0;
    }
    fclose(fp2);

    int polyNum1, polyNum2;
    int** arr = NULL;
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