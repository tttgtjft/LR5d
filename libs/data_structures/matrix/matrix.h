#ifndef LR5D_MATRIX_H
#define LR5D_MATRIX_H

#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>

typedef struct matrix {
    int **values;
    int nRows;
    int nCols;
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix *m);

void freeMemMatrices(matrix *ms, int nMatrices);

void swap(void *a, void *b, size_t baseTypeSize);

#include "matrix.c"
#endif
