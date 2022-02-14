#include "matrix.h"

#define ROWS 0
#define COLS 1

matrix getMemMatrix(const int nRows, const int nCols){
    int **values = (int **) malloc(nRows * sizeof(int *));
    for (int i = 0; i < nRows; ++i)
        values[i] = (int *) malloc((nCols * sizeof(int)));

    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(const int nMatrices, const int nRows, const int nCols){
    matrix *ms = (matrix *) malloc(nMatrices * sizeof(matrix));
    for (int i = 0; i < nMatrices; ++i)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}

void freeMemMatrix(matrix *m){
    for (int i = 0; i < m->nRows; ++i)
        free(m->values[i]);
    free(m->values);
}

void freeMemMatrices(matrix *ms, const int nMatrices){
    for (int i = 0; i < nMatrices; ++i)
        freeMemMatrix(&ms[i]);
    free(ms);
}

void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows; ++i)
        for (int j = 0; j < m->nCols; ++j)
            scanf("%d", &m->values[i][j]);
}

void inputMatrices(matrix ms[], const int nMatrices){
    for (int i = 0; i < nMatrices; ++i)
        inputMatrix(&ms[i]);
}

void outputMatrix(const matrix m){
    for (int i = 0; i < m.nRows; ++i){
        for (int j = 0; j < m.nCols; ++j)
            printf("%d ", m.values[i][j]);
        printf("\n");
    }
}

void outputMatrices(matrix ms[], const int nMatrices){
    for (int i = 0; i < nMatrices; ++i)
        outputMatrix(ms[i]);
}

void swap(void *a, void *b, const size_t size){
    void *t = (void *) malloc(size);
    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);

    free(t);
}

void swapRows(matrix *m, const int i1, const int i2){
    swap(&m->values[i1], &m->values[i2], sizeof(int));
}

void swapColumns(matrix *m, const int j1, const int j2){
    for (int i = 0; i < m->nRows; ++i)
        swap(&m->values[i][j1], &m->values[i][j2], sizeof(int));
}

void insertionSortMatrix(int a[], matrix *m, void (f)(matrix *, int, int)){
    for (int i = 1; i < m->nRows; ++i) {
        int k = i;
        while (k > 0 && a[i] >= a[k]){
            f(m, i, k);
            swap(&a[i], &a[k], sizeof(int));

            k--;
        }
    }
}

void insertionSortMatrixByCriteria(matrix *m, const int (*criteria)(int *, int), const int rowsOrCols){
    if (rowsOrCols == ROWS){
        int rowsArr[m->nRows];
        for (int i = 0; i < m->nRows; ++i)
            rowsArr[i] = criteria(m->values[i], m->nCols);

        insertionSortMatrix(rowsArr, m, swapRows);
    }
    else if (rowsOrCols == COLS){
        int colsArr[m->nCols];
        for (int i = 0; i < m->nCols; ++i) {
            int t[m->nRows];
            for (int j = 0; j < m->nRows; ++j)
                t[i] = m->values[j][i];

            colsArr[i] = criteria(t, m->nCols);
        }

        insertionSortMatrix(colsArr, m, swapColumns);
    }
}
