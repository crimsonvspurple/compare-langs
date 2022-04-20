#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define len(x) (sizeof(x) / sizeof((x)[0])) // do NOT use for array as params (pointers)

void readMatrix(int i, char *iterString, int size, char *var, int dim, const int *ptr) {

    char path[1024] = "";
    strcat(path, "../../matrices/");

    char sizeString[128] = "";
    sprintf(sizeString, "%d", size);
    strcat(path, sizeString);
    strcat(path, "/");
    strcat(path, var);
    strcat(path, iterString);
    strcat(path, ".matrix.txt");

    /// printf("Path is: %s\n", path);

    // read from file
    FILE *fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        exit(1);
    }

    for (int r = 0; r < size; r++) {         // for each row
        for (int c = 0; c < size; c++) {        // for each col
            int item = 0;
            fscanf(fp, "%d", &*(ptr + (i * size * size) + (r * size) + c));
            // printf(" = %d\n", *(ptr + (i * size * size) + (r * size) + c));
        }
    }
    fclose(fp);
}

void saveBenchMark(int ITERATION, int size, double benchmark[]) {
    char path[1024] = "";
    strcat(path, "../../benchmark/cpointer");

    char sizeString[128] = "";
    sprintf(sizeString, "%04d", size);
    strcat(path, sizeString);
    strcat(path, ".log");

    printf("Path is: %s\n", path);

    FILE *fp;
    fp = fopen(path, "w");

    double bestTime = DBL_MAX;
    double totalTime = 0.0;
    for (int i = 0; i < ITERATION; ++i) {
        if (bestTime > benchmark[i]) {
            bestTime = benchmark[i];
        }
        totalTime += benchmark[i];
        fprintf(fp, "%f\n", benchmark[i]);
    }
    printf("Best Time: %f | Total Time: %f\n", bestTime, totalTime);
    fclose(fp);

}


int main() {
    const int ITERATION = 20;
    // const int SIZES[] = {256};
    int SIZES[] = {16, 32, 64, 128, 256, 512, 1024};


    for (int s = 0; s < len(SIZES); ++s) {  // for each size
        int size = SIZES[s];

        int *ptrA = malloc(ITERATION * size * size * sizeof(int));
        int *ptrB = malloc(ITERATION * size * size * sizeof(int));

        double benchmark[ITERATION];

        for (int i = 0; i < ITERATION; ++i) {   // for each iteration per size
            char iterString[1024] = "";
            sprintf(iterString, "%04d", ITERATION - 1);

            readMatrix(i, iterString, size, "a", size, ptrA);
            readMatrix(i, iterString, size, "b", size, ptrB);

//            for (int x = 0; x < size; ++x) {         // for each row
//                for (int y = 0; y < size; ++y) {        // for each col
//                    printf("%d ", *(ptrA + (i * size * size) + (x * size) + y));
//                }
//                printf("\n");
//            }
//            printf("\n");
//            printf("\n");
//
//            for (int x = 0; x < size; ++x) {         // for each row
//                for (int y = 0; y < size; ++y) {        // for each col
//                    printf("%d ", *(ptrB + (i * size * size) + (x * size) + y));
//                }
//                printf("\n");
//            }
//            printf("\n");
//            printf("\n");
        }

        for (int i = 0; i < ITERATION; i++) {   // for each iteration per size
            int c[size][size];
            // actual multiplication

            clock_t start = clock();
            for (int x = 0; x < size; ++x) {         // for each row
                for (int y = 0; y < size; ++y) {        // for each col
                    c[x][y] = 0;
                    for (int z = 0; z < size; ++z) {
                        c[x][y] += *(ptrA + (i * size * size) + (x * size) + z) * *(ptrB + (i * size * size) + (z * size) + y);
                    }
                }
            }
            benchmark[i] = (double) (clock() - start) / CLOCKS_PER_SEC;

            // printf("Done in %f seconds\n", benchmark);

            // we can print result matrix here; but we are not interested in that.
            // we have however, verified that the multiplication results are correct
//            for (int x = 0; x < size; ++x) {         // for each row
//                for (int y = 0; y < size; ++y) {        // for each col
//                    printf("%d ", c[x][y]);
//                }
//                printf("\n");
//            }


        }

        saveBenchMark(ITERATION, size, benchmark);
    }
    return 0;
}


