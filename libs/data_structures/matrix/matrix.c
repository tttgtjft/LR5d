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

void insertionSortMatrix(int a[], matrix *m, void (f)(matrix *, int, int), const int rowsOrCols){
    for (int i = 1; i < rowsOrCols; ++i) {
        int k = i;
        while (k > 0 && a[k - 1] >= a[k]){
            swap(&a[k - 1], &a[k], sizeof(int));
            f(m, k - 1, k);

            k--;
        }
    }
}

void insertionSortMatrixByCriteria(matrix *m, int (criteria)(int [], int), const bool rowsOrCols){
    if (rowsOrCols == ROWS){
        int rowsArr[m->nRows];
        for (int i = 0; i < m->nRows; ++i)
            rowsArr[i] = criteria(m->values[i], m->nCols);
        insertionSortMatrix(rowsArr, m, swapRows, m->nRows);
    }
    else if (rowsOrCols == COLS){
        int colsArr[m->nCols];
        for (int i = 0; i < m->nCols; ++i) {
            int t[m->nRows];
            for (int j = 0; j < m->nRows; ++j)
                t[j] = m->values[j][i];

            colsArr[i] = criteria(t, m->nRows);
        }

        insertionSortMatrix(colsArr, m, swapColumns, m->nCols);
    }
}

void insertionSortMatrixF(double a[], matrix *m, void (f)(matrix *, int, int), const int rowsOrCols){
    for (int i = 1; i < rowsOrCols; ++i) {
        int k = i;
        while (k > 0 && a[k - 1] >= a[k]){
            swap(&a[k - 1], &a[k], sizeof(double));
            f(m, k - 1, k);

            k--;
        }
    }
}

void insertionSortMatrixByCriteriaF(matrix *m, double (criteria)(int [], int), const bool rowsOrCols){
    if (rowsOrCols == ROWS){
        double rowsArr[m->nRows];
        for (int i = 0; i < m->nRows; ++i)
            rowsArr[i] = criteria(m->values[i], m->nCols);

        insertionSortMatrixF(rowsArr, m, swapRows, m->nRows);
    }
    else if (rowsOrCols == COLS){
        double colsArr[m->nCols];
        for (int i = 0; i < m->nCols; ++i) {
            int t[m->nRows];
            for (int j = 0; j < m->nRows; ++j)
                t[j] = m->values[j][i];

            colsArr[i] = criteria(t, m->nRows);
        }

        insertionSortMatrixF(colsArr, m, swapColumns, m->nCols);
    }
}

bool isSquareMatrix(const matrix m){
    return m.nRows == m.nCols;
}

bool areTwoMatricesEqual(matrix m1, matrix m2){
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return false;

    for (int i = 0; i < m1.nRows; ++i)
        if (memcmp(m1.values[i], m2.values[i], m1.nCols * sizeof(int)) != 0)
            return false;

    return true;
}

bool isEMatrix(const matrix m){
    if (!isSquareMatrix(m))
        return false;

    for (int i = 0; i < m.nRows; ++i){
        if (m.values[i][i] != 1)
            return false;
        for (int j = 0; j < m.nCols; ++j)
            if (i != j && m.values[i][j])
                return false;
    }

    return true;
}

bool isSymmetricMatrix(const matrix m){
    if (!isSquareMatrix(m))
        return false;

    for (int i = 0; i < m.nRows; ++i)
        for (int j = i + 1; j < m.nCols; ++j)
            if (m.values[i][j] != m.values[j][i])
                return false;

    return true;
}

void transposeMatrix(matrix *m){
    int max = m->nRows;
    if (m->nCols > m->nRows){
        m->values = (int **) realloc(m->values, m->nCols * sizeof(int *));
        for (int i = m->nRows; i < m->nCols; ++i)
            m->values[i] = (int *) calloc(m->nCols, sizeof(int));
        max = m->nCols;
    }
    else if (m->nRows > m->nCols)
        for (int i = 0; i < m->nRows; ++i)
            m->values[i] = (int *) realloc(m->values[i], m->nRows * sizeof(int));

    for (int i = 0; i < max; ++i)
        for (int j = i + 1; j < max; ++j)
            swap(&m->values[i][j], &m->values[j][i], sizeof(int));

    if (m->nCols > m->nRows)
        for (int i = 0; i < m->nCols; ++i)
            m->values[i] = (int *) realloc(m->values[i], m->nRows * sizeof(int));
    else if (m->nRows > m->nCols){
        for (int i = m->nCols; i < m->nRows; ++i)
            free(m->values[i]);
        m->values = (int **) realloc(m->values, m->nCols * sizeof(int));
    }

    if (!isSquareMatrix(*m))
        swap(&m->nRows, &m->nCols, sizeof(int));
}

position getMinValuePos(matrix m){
    position minIndex = {0, 0};
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (m.values[minIndex.rowIndex][minIndex.colIndex] > m.values[i][j]){
                minIndex.rowIndex = i;
                minIndex.colIndex = j;
            }

    return minIndex;
}

position getMaxValuePos(matrix m){
    position maxIndex = {0, 0};
    for (int i = 0; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j)
            if (m.values[maxIndex.rowIndex][maxIndex.colIndex] < m.values[i][j]){
                maxIndex.rowIndex = i;
                maxIndex.colIndex = j;
            }

    return maxIndex;
}

matrix createMatrixFromArray(const int a[], const int nRows, const int nCols){
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; ++i)
        for (int j = 0; j < nCols; ++j)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, const int nMatrices, const int nRows, const int nCols){
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; ++k)
        for (int i = 0; i < nRows; ++i)
            for (int j = 0; j < nCols; ++j)
                ms[k].values[i][j] = values[l++];

    return ms;
}