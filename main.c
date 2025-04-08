#include <stdio.h>
#include <stdlib.h>
FILE* fpPoly1 = NULL;

int main(){
    char PolyLen[2];
    fpPoly1 = fopen("input.txt", "r");
    sprintf(PolyLen, "%d\t%d", fpPoly1);
    printf("%c\t%c", PolyLen[0], PolyLen[1]);
    return 0;
}