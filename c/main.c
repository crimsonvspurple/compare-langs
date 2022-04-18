#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define len(x) (sizeof(x) / sizeof((x)[0])) // do NOT use for array as params (pointers)

void readMatrix(int i, char* iterString, int size, char var, int dim, int v[][dim][dim]) {

    char path[1024] = "";
    strcat(path, "../../matrices/");

    char sizeString[128] = "";
    sprintf(sizeString, "%d", size);
    strcat(path, sizeString);
    strcat(path, "/");
    strcat(path, &var);
    strcat(path, iterString);
    strcat(path, ".matrix.txt");

    printf("Path is: %s\n", path);

    // read from file
    FILE *fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        exit(1);
    }

    for (int r = 0; r < size; r++) {         // for each row
        for (int c = 0; c < size; c++) {        // for each col
            int x = 0;
            fscanf(fp, "%d", &v[i][r][c]);
        }
    }
    fclose(fp);
}


int main() {
    const int ITERATION = 1;
    const int SIZES[] = {16};
// int SIZES[] = {16, 32, 64, 128, 256, 512, 1024};

    int a[ITERATION][16][16];
    int b[ITERATION][16][16];

    for (int s = 0; s < len(SIZES); s++) {  // for each size
        int size = SIZES[s];
        for (int i = 0; i < ITERATION; i++) {   // for each iteration per size
            char iterString[1024] = "";
            sprintf(iterString, "%03d", ITERATION - 1);

            readMatrix(i, iterString, size, 'a', 16, a);
            readMatrix(i, iterString, size, 'b', 16, b);

            for (int r = 0; r < size; r++) {         // for each row
                for (int c = 0; c < size; c++) {        // for each col
                    printf("%d ", a[i][r][c]);
                }
                printf("\n");
            }
            printf("\n");
            printf("\n");

            for (int r = 0; r < size; r++) {         // for each row
                for (int c = 0; c < size; c++) {        // for each col
                    printf("%d ", b[i][r][c]);
                }
                printf("\n");
            }
        }
        return 0;
    }
}


