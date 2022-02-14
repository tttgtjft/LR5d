#ifndef LR5D_MATRIX_H
#define LR5D_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
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

void inputMatrix(matrix *m);

void inputMatrices(matrix ms[], int nMatrices);

void outputMatrix(matrix m);

void outputMatrices(matrix ms[], int nMatrices);

void swap(void *a, void *b, size_t size);

void swapRows(matrix *m, int i1, int i2);

void swapColumns(matrix *m, int j1, int j2);

void insertionSortRowsMatrixByRowCriteria(matrix *m, int (*criteria)(int *, int));

#include "matrix.c"
#endif
