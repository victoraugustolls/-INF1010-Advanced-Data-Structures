#include "esparsas.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    FILE* fp;

    if ((fp = fopen("matriz.txt", "r")) == NULL) {
        printf("Error opening matriz file\n");
    }

    tsm* matriz = createFromFile(fp);

    int tamb = 5;
    int *b = (int*)malloc(tamb*sizeof(int));
    for (int i = 0; i < tamb; i++) {
        b[i] = i+1;
    }
    int *result = matrixvectormult(matriz, b, tamb);

    if (result != NULL) {
        for (int i = 0; i < tamb; i++) {
            printf("%d\n", result[i]);
        }
    }

    fclose(fp);

    return 0;
}
