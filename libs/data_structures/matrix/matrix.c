#include "matrix.h"

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

void swap(void *a, void *b, const size_t baseTypeSize){
    void *t = (void *) malloc(baseTypeSize);
    memcpy(t, a, baseTypeSize);
    memcpy(a, b, baseTypeSize);
    memcpy(b, t, baseTypeSize);
}

void swapRows(matrix *m, const int i1, const int i2){
    swap(&m->values[i1][0], &m->values[i2][0], m->nRows * sizeof(int));
}

void swapColumns(matrix *m, const int j1, const int j2){
    for (int i = 0; i < m->nRows; ++i)
        swap(&m->values[i][j1], &m->values[i][j2], sizeof(int));
}


