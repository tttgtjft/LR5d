#ifndef LR5D_MATRIX_H
#define LR5D_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>

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

void outputMatrices(matrix ms[], size_t nMatrices);

void swapRows(matrix *m, int i1, int i2);

void swapColumns(matrix *m, int j1, int j2);

void insertionSortMatrixByCriteria(matrix *m, int (criteria)(int [], int), bool rowsOrCols);

void insertionSortMatrixByCriteriaF(matrix *m, double (criteria)(int [], int), bool rowsOrCols);

bool isSquareMatrix(matrix m);

bool areTwoMatricesEqual(matrix m1, matrix m2);

bool isEMatrix(matrix m);

bool isSymmetricMatrix(matrix m);

void transposeMatrix(matrix *m);

position getMinValuePos(matrix m);

position getMaxValuePos(matrix m);

matrix createMatrixFromArray(const int a[], int nRows, int nCols);

matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices, int nRows, int nCols);

#include "matrix.c"
#endif
