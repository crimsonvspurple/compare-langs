#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#define len(x) (sizeof(x) / sizeof((x)[0])) // do NOT use for array as params (pointers)

void readMatrix(int i, char *iterString, int size, char *var, int dim, int v[][dim][dim]) {

    char path[1024] = "";
    strcat(path, "../../matrices/");

    char sizeString[128] = "";
    sprintf(sizeString, "%d", size);
    strcat(path, sizeString);
    strcat(path, "/");
    strcat(path, var);
    strcat(path, iterString);
    strcat(path, ".matrix.txt");

    // printf("Path is: %s\n", path);

    // read from file
    FILE *fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        exit(1);
    }

    for (int r = 0; r < size; r++) {         // for each row
        for (int c = 0; c < size; c++) {        // for each col
            fscanf(fp, "%d", &v[i][r][c]);
        }
    }
    fclose(fp);
}

void saveBenchMark(int ITERATION, int size, double benchmark[]) {
    char path[1024] = "";
    strcat(path, "../../benchmark/c");

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
//    const int SIZES[] = {256};
    int SIZES[] = {16, 32, 64, 128, 256, 512, 1024};


    for (int s = 0; s < len(SIZES); ++s) {  // for each size
        int size = SIZES[s];
        int a[ITERATION][size][size];
        int b[ITERATION][size][size];
        double benchmark[ITERATION];

        for (int i = 0; i < ITERATION; ++i) {   // for each iteration per size
            char iterString[1024] = "";
            sprintf(iterString, "%04d", ITERATION - 1);

            readMatrix(i, iterString, size, "a", size, a);
            readMatrix(i, iterString, size, "b", size, b);

//            for (int x = 0; x < size; ++x) {         // for each row
//                for (int y = 0; y < size; ++y) {        // for each col
//                    printf("%d ", a[i][x][y]);
//                }
//                printf("\n");
//            }
//            printf("\n");
//            printf("\n");

//            for (int x = 0; x < size; ++x) {         // for each row
//                for (int y = 0; y < size; ++y) {        // for each col
//                    printf("%d ", b[i][x][y]);
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
                        c[x][y] += a[i][x][z] * b[i][z][y];
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


