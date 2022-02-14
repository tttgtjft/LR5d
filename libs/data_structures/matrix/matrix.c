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

void swap(void *a, void *b, const size_t baseTypeSize){
    void *t = (void *) malloc(baseTypeSize);
    memcpy(t, a, baseTypeSize);
    memcpy(a, b, baseTypeSize);
    memcpy(b, t, baseTypeSize);
}