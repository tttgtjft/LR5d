#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"
#include <math.h>

#define EXIT_CODE 1
#define throwExceptionEmptyArray() fprintf(stderr, "empty array"); exit(EXIT_CODE)

void test();

int main() {
    test();

    return 0;
}

//------------------------------TASK 1------------------------------//

void task1(matrix m){
    position min = getMinValuePos(m);
    position max = getMaxValuePos(m);

    swapRows(&m, min.rowIndex, max.rowIndex);
}

//------------------------------TASK 2------------------------------//

int getMax(const int *a, const size_t n) {
    if (n < 1) {
        throwExceptionEmptyArray();
    }

    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}

void sortRowsByMinElement(matrix m) {
    insertionSortMatrixByCriteria(&m, getMax, ROWS);
}

void task2(matrix m){
    sortRowsByMinElement(m);
}

//------------------------------TASK 3------------------------------//

int getMin(const int *a, const size_t n) {
    if (n < 1) {
        throwExceptionEmptyArray();
    }

    int min = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < min)
            min = a[i];

    return min;
}

void sortColsByMinElement(matrix m) {
    insertionSortMatrixByCriteria(&m, getMin, COLS);
}

void task3(matrix m){
    sortColsByMinElement(m);
}

//------------------------------TASK 4------------------------------//

matrix mulMatrices(matrix m1, matrix m2) {
    matrix mulMatrix = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; ++i) {
        for (int j = 0; j < m2.nCols; ++j) {
            mulMatrix.values[i][j] = 0;
            for (int k = 0; k < m2.nRows; k++)
                mulMatrix.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }
    }

    return (matrix) mulMatrix;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m))
        *m = mulMatrices(*m, *m);
}

void task4(matrix *m){
    getSquareOfMatrixIfSymmetric(m);
}

//------------------------------TASK 5------------------------------//

void selectionSort(long long a[], const size_t n){
    for (int i = 1; i < n; ++i) {
        int k = i;
        while (k > 0 && a[k - 1] > a[k]){
            swap(&a[k - 1], &a[k], sizeof(int));

            k--;
        }
    }
}

bool isUnique(long long a[], const size_t n) {
    bool isUnique = true;

    selectionSort(a, n);

    int i = 1;
    while (i < n && isUnique) {
        if (a[i - 1] == a[i])
            isUnique = 0;
        i++;
    }

    return isUnique;
}

long long getSum(const int a[], const size_t n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long sum[m.nRows];

    for (int i = 0; i < m.nRows; i++)
        sum[i] = getSum(m.values[i], m.nCols);

    if (isUnique(sum, m.nRows))
        transposeMatrix(&m);
}

void task5(matrix m){
    transposeIfMatrixHasNotEqualSumOfRows(m);
}

//------------------------------TASK 6------------------------------//

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix mulMatrix = mulMatrices(m1, m2);
    bool isMutuallyInverse = isEMatrix(mulMatrix);

    free(mulMatrix.values);
    return isMutuallyInverse;
}

bool task6(matrix m1, matrix m2){
    return isMutuallyInverseMatrices(m1, m2);
}

//------------------------------TASK 7------------------------------//

long long findSumOfMaxOfPseudoDiagonal(const matrix m, const int countRows, const int countCols, const int n){
    int maxInDiagonal = m.values[countRows][countCols];
    for (int i = 0; i < n; ++i)
        if (maxInDiagonal < m.values[countRows + i][countCols + i])
            maxInDiagonal = m.values[countRows + i][countCols + i];

    return maxInDiagonal;
}

long long findSumOfMaxesOfPseudoDiagonal(const matrix m){
    long long sumOfMaxesOfPseudoDiagonal = 0;

    int k = 1;
    int countRows = m.nRows;
    while (--countRows){
        sumOfMaxesOfPseudoDiagonal += findSumOfMaxOfPseudoDiagonal(m, countRows, 0, k);

        if (k + 1 <= m.nCols)
            k++;
    }

    k = 1;
    int countCols = m.nCols;
    while (--countCols){
        sumOfMaxesOfPseudoDiagonal += findSumOfMaxOfPseudoDiagonal(m, 0, countCols, k);

        if (k + 1 <= m.nRows)
            k++;
    }

    return sumOfMaxesOfPseudoDiagonal;
}

long long task7(matrix m){
    return findSumOfMaxesOfPseudoDiagonal(m);
}

//------------------------------TASK 8------------------------------//

int getMinInArea(matrix m){ //O(n * m)
    int maxInArea = m.values[0][0];
    position minInArea = {0, 0};
    for (int i = 0; i < m.nCols; ++i)
        if (maxInArea < m.values[0][i]){
            maxInArea = m.values[0][i];
            minInArea.colIndex = i;
        }

    for (int i = 1; i < m.nRows; ++i)
        for (int j = 0; j < m.nCols; ++j) {
            int t = m.values[i][j];

            if (j != 0 && m.values[i][j] > m.values[i - 1][j - 1])
                m.values[i][j] = m.values[i - 1][j - 1];
            if (m.values[i][j] > m.values[i - 1][j])
                m.values[i][j] = m.values[i - 1][j];
            if (j != m.nCols - 1 && m.values[i][j] > m.values[i - 1][j + 1])
                m.values[i][j] = m.values[i - 1][j + 1];

            if (maxInArea < t){
                maxInArea = t;
                minInArea.rowIndex = i;
                minInArea.colIndex = j;
            }
        }

    return m.values[minInArea.rowIndex][minInArea.colIndex];
}

//------------------------------TASK 9------------------------------//

//------------------------------TASK 10-----------------------------//

//------------------------------TASK 11-----------------------------//

//------------------------------TASK 12-----------------------------//

//------------------------------TASK 13-----------------------------//

//------------------------------TASK 14-----------------------------//

int task8(matrix m){
    return getMinInArea(m);
}

//------------------------------TESTS-------------------------------//

void test_matrix_tasks();

void test_task1_maxAndMinInDifferentRows();
void test_task1_maxAndMinInSameRow();
void test_task1_oneElem();
void test_task2_squareMatrix();
void test_task2_notSquareMatrix();
void test_task2_oneElem();
void test_task2_oneRow();
void test_task2_oneCol();
void test_task3_squareMatrix();
void test_task3_notSquareMatrix();
void test_task3_oneElem();
void test_task3_oneRow();
void test_task3_oneCol();
void test_task4_SymmetricSquareMatrix_v1();
void test_task4_SymmetricSquareMatrix_v2();
void test_task4_SymmetricSquareMatrix_v3();
void test_task4_oneElem();
void test_task4_NotSymmetricSquareMatrix();
void test_task5_oneElem();
void test_task5_hasEqualSum();
void test_task5_hasNotEqualSum();
void test_task5_lastsSumIsEqual();
void test_task6_matrix2x2ProduceIsEMatrix();
void test_task6_matrix3x3ProduceIsEMatrix();
void test_task6_matrix2x2ProduceIsNotEMatrix();
void test_task6_matrix3x3ProduceIsNotEMatrix();
void test_task7_ColsMoreRowsAndRowsMoreCols();
void test_task7_3x6matrixAnd6x3matrix();
void test_task8_v1();
void test_task8_v2();
void test_task8_v3();
void test_task8_minIndexInFirstRow();

void test_matrix_functions();

void test_swapRows();
void test_swapColumns();
void test_isSquareMatrix();
void test_AreTwoMatricesEqual();
void test_isEMatrix_matrixIsE();
void test_isEMatrix_matrixIsNotE();
void test_isEMatrix_matrixIsNotSquare();
void test_isSymmetricMatrix_matrixIsSymmetric();
void test_isSymmetricMatrix_matrixIsNotSymmetric();
void test_isSymmetricMatrix_matrixIsNotSquare();
void test_transposeMatrix_matrixIsSquare();
void test_transposeMatrix_matrixIsRowsMoreCols();
void test_transposeMatrix_matrixIsColsMoreRows();

void test(){
    test_matrix_functions();
    test_matrix_tasks();
}

void test_matrix_tasks(){
    test_task1_maxAndMinInDifferentRows();
    test_task1_maxAndMinInSameRow();
    test_task1_oneElem();
    test_task2_squareMatrix();
    test_task2_notSquareMatrix();
    test_task2_oneElem();
    test_task2_oneRow();
    test_task2_oneCol();
    test_task3_squareMatrix();
    test_task3_notSquareMatrix();
    test_task3_oneElem();
    test_task3_oneRow();
    test_task3_oneCol();
    test_task4_SymmetricSquareMatrix_v1();
    test_task4_SymmetricSquareMatrix_v2();
    test_task4_SymmetricSquareMatrix_v3();
    test_task4_oneElem();
    test_task4_NotSymmetricSquareMatrix();
    test_task5_oneElem();
    test_task5_hasEqualSum();
    test_task5_hasNotEqualSum();
    test_task5_lastsSumIsEqual();
    test_task6_matrix2x2ProduceIsEMatrix();
    test_task6_matrix3x3ProduceIsEMatrix();
    test_task6_matrix2x2ProduceIsNotEMatrix();
    test_task6_matrix3x3ProduceIsNotEMatrix();
    test_task7_ColsMoreRowsAndRowsMoreCols();
    test_task7_3x6matrixAnd6x3matrix();
    test_task8_v1();
    test_task8_v2();
    test_task8_v3();
    test_task8_minIndexInFirstRow();
}

void test_matrix_functions(){
    test_swapRows();
    test_swapColumns();
    test_isSquareMatrix();
    test_AreTwoMatricesEqual();
    test_isEMatrix_matrixIsE();
    test_isEMatrix_matrixIsNotE();
    test_isEMatrix_matrixIsNotSquare();
    test_isSymmetricMatrix_matrixIsSymmetric();
    test_isSymmetricMatrix_matrixIsNotSymmetric();
    test_isSymmetricMatrix_matrixIsNotSquare();
    test_transposeMatrix_matrixIsSquare();
    test_transposeMatrix_matrixIsRowsMoreCols();
    test_transposeMatrix_matrixIsColsMoreRows();
}

//-----------------------TESTS TASKS-------------------------------//

void test_task1_maxAndMinInDifferentRows() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    task1(m);

    matrix expectation = createMatrixFromArray((int[]) {7, 8, 9,
                                                        4, 5, 6,
                                                        1, 2, 3}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task1_maxAndMinInSameRow() {
    matrix m = createMatrixFromArray((int[]) {1, 10, 9,
                                              4, 5, 6,
                                              7, 8, 2}, 3, 3);

    task1(m);

    matrix expectation = createMatrixFromArray((int[]) {1, 10, 9,
                                                        4, 5, 6,
                                                        7, 8, 2}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task1_oneElem() {
    matrix m = createMatrixFromArray((int[]) {1}, 1, 1);

    task1(m);

    matrix expectation = createMatrixFromArray((int[]) {1}, 1, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task2_squareMatrix() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3}, 3, 3);

    task2(m);

    matrix expectation = createMatrixFromArray((int[]) {3, 2, 3,
                                                        7, 1, 2,
                                                        1, 8, 1}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task2_notSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2, 3,
                                              1, 8, 1, 6,
                                              3, 2, 3, 8}, 3, 4);

    task2(m);

    matrix expectation = createMatrixFromArray((int[]) {7, 1, 2, 3,
                                                        3, 2, 3, 8,
                                                        1, 8, 1, 6}, 3, 4);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task2_oneElem() {
    matrix m = createMatrixFromArray((int[]) {7}, 1, 1);

    task2(m);

    matrix expectation = createMatrixFromArray((int[]) {7}, 1, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task2_oneRow() {
    matrix m = createMatrixFromArray((int[]) {7, 2, 4, 6}, 1, 4);

    task2(m);

    matrix expectation = createMatrixFromArray((int[]) {7, 2, 4, 6}, 1, 4);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task2_oneCol() {
    matrix m = createMatrixFromArray((int[]) {7,
                                              2,
                                              4,
                                              6}, 4, 1);

    task2(m);

    matrix expectation = createMatrixFromArray((int[]) {2,
                                                        4,
                                                        6,
                                                        7}, 4, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task3_squareMatrix() {
    matrix m = createMatrixFromArray((int[]) {7, -1, 2,
                                              1, 8, -2,
                                              3, 2, 3}, 3, 3);

    task3(m);

    matrix expectation = createMatrixFromArray((int[]) {2, -1, 7,
                                                        -2, 8, 1,
                                                        3, 2, 3}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task3_notSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 1, 0,
                                              -1, -1, -1, -1,
                                              -2, -5, -7, -6}, 3, 4);

    task3(m);

    matrix expectation = createMatrixFromArray((int[]) {1, 0, 2, 3,
                                                        -1, -1, -1, -1,
                                                        -7, -6, -5, -2}, 3, 4);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task3_oneElem() {
    matrix m = createMatrixFromArray((int[]) {7}, 1, 1);

    task3(m);

    matrix expectation = createMatrixFromArray((int[]) {7}, 1, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task3_oneRow() {
    matrix m = createMatrixFromArray((int[]) {7, 2, 4, 6}, 1, 4);

    task3(m);

    matrix expectation = createMatrixFromArray((int[]) {2, 4, 6, 7}, 1, 4);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task3_oneCol() {
    matrix m = createMatrixFromArray((int[]) {7,
                                              2,
                                              4,
                                              6}, 4, 1);

    task3(m);

    matrix expectation = createMatrixFromArray((int[]) {7,
                                                        2,
                                                        4,
                                                        6}, 4, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task4_SymmetricSquareMatrix_v1() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              2, 1, 3}, 3, 3);

    task4(&m);

    matrix expectation = createMatrixFromArray((int[]) {54, 17, 21,
                                                        17, 66, 13,
                                                        21, 13, 14}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task4_SymmetricSquareMatrix_v2() {
    matrix m = createMatrixFromArray((int[]) {0, 11, 7,
                                              11, 0, 4,
                                              7, 4, 22}, 3, 3);

    task4(&m);

    matrix expectation = createMatrixFromArray((int[]) {170, 28, 198,
                                                        28, 137, 165,
                                                        198, 165, 549}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task4_SymmetricSquareMatrix_v3() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    task4(&m);

    matrix expectation = createMatrixFromArray((int[]) {1, 0, 0,
                                                        0, 1, 0,
                                                        0, 0, 1}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task4_oneElem() {
    matrix m = createMatrixFromArray((int[]) {7}, 1, 1);

    task4(&m);

    matrix expectation = createMatrixFromArray((int[]) {49}, 1, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task4_NotSymmetricSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 3, 3}, 3, 3);

    task4(&m);

    matrix expectation = createMatrixFromArray((int[]) {7, 1, 2,
                                                        1, 8, 1,
                                                        3, 3, 3}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task5_oneElem() {
    matrix m = createMatrixFromArray((int[]) {2}, 1, 1);

    task5(m);

    matrix expectation = createMatrixFromArray((int[]) {2}, 1, 1);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task5_hasEqualSum() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 1, 3}, 3, 3);

    task5(m);

    matrix expectation = createMatrixFromArray((int[]) {7, 1, 2,
                                                        1, 8, 1,
                                                        3, 1, 3}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task5_hasNotEqualSum() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 1,
                                              1, 8, 1,
                                              3, 1, 3}, 3, 3);

    task5(m);

    matrix expectation = createMatrixFromArray((int[]) {7, 1, 3,
                                                        1, 8, 1,
                                                        1, 1, 3}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task5_lastsSumIsEqual() {
    matrix m = createMatrixFromArray((int[]) {3, 1, 3,
                                              1, 8, 1,
                                              7, 1, 2}, 3, 3);

    task5(m);

    matrix expectation = createMatrixFromArray((int[]) {3, 1, 3,
                                                        1, 8, 1,
                                                        7, 1, 2}, 3, 3);

    assert(areTwoMatricesEqual(m, expectation));

    freeMemMatrix(&m);
    freeMemMatrix(&expectation);
}

void test_task6_matrix2x2ProduceIsEMatrix() {
    matrix m1 = createMatrixFromArray((int[]) {3, 4,
                                               5, 7}, 2, 2);

    matrix m2 = createMatrixFromArray((int[]) {7, -4,
                                               -5, 3}, 2, 2);

    assert(task6(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_task6_matrix3x3ProduceIsEMatrix() {
    matrix m1 = createMatrixFromArray((int[]) {2, 5, 7,
                                               6, 3, 4,
                                               5, -2, -3}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, -1, 1,
                                               -38, 41, -34,
                                               27, -29, 24}, 3, 3);

    assert(task6(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_task6_matrix2x2ProduceIsNotEMatrix() {
    matrix m1 = createMatrixFromArray((int[]) {3, 4,
                                               5, 7}, 2, 2);

    matrix m2 = createMatrixFromArray((int[]) {7, 4,
                                               -5, 3}, 2, 2);

    assert(!task6(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_task6_matrix3x3ProduceIsNotEMatrix() {
    matrix m1 = createMatrixFromArray((int[]) {2, 5, 7,
                                               6, 3, 4,
                                               5, -2, -3}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, -1, -1,
                                               -38, 41, -34,
                                               27, -29, 24}, 3, 3);

    assert(!task6(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_task7_ColsMoreRowsAndRowsMoreCols() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);

    assert(task7(m) == 20);

    transposeMatrix(&m);

    assert(task7(m) == 20);

    freeMemMatrix(&m);
}

void test_task7_3x6matrixAnd6x3matrix() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4, 1, 1,
                                                 1, 3, 6, 3, 1, 1,
                                                 3, 2, 1, 2, 1, 1}, 3, 6);

    assert(task7(m) == 22);

    transposeMatrix(&m);

    assert(task7(m) == 22);

    freeMemMatrix(&m);
}

void test_task8_v1() {
    matrix m = createMatrixFromArray((int []) {10, 7, 5, 6,
                                               3, 11, 8, 9,
                                               4, 1, 12, 2}, 3, 4);
    assert(task8(m) == 5);

    freeMemMatrix(&m);
}
void test_task8_v2() {
    matrix m = createMatrixFromArray((int []) {6, 8, 9, 2,
                                               7, 12, 3, 4,
                                               10, 11, 5, 1}, 3, 4);
    assert(task8(m) == 6);

    freeMemMatrix(&m);
}
void test_task8_v3() {
    matrix m = createMatrixFromArray((int []) {10, 7, 5, 0,
                                               3, 11, 8, 9,
                                               4, 1, 12, 2}, 3, 4);
    assert(task8(m) == 0);

    freeMemMatrix(&m);
}
void test_task8_minIndexInFirstRow() {
    matrix m = createMatrixFromArray((int []) {8, 30, 9, 2,
                                               7, 12, 3, 4,
                                               10, 11, 5, 1}, 3, 4);
    assert(task8(m) == 30);

    freeMemMatrix(&m);
}

//-----------------------TESTS FUNCTIONS---------------------------//

void test_swapRows() {
    matrix m1 = createMatrixFromArray((int[]) {1, 4, 5,
                                               3, 6, 7,
                                               4, 7, 2}, 3, 3);


    swapRows(&m1, 1, 2);

    matrix m2 = createMatrixFromArray((int[]) {1, 4, 5,
                                               4, 7, 2,
                                               3, 6, 7}, 3, 3);

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_swapColumns() {
    matrix m1 = createMatrixFromArray((int[]) {1, 4, 5,
                                               3, 6, 7,
                                               4, 7, 2}, 3, 3);

    swapColumns(&m1, 0, 2);

    matrix m2 = createMatrixFromArray((int[]) {5, 4, 1,
                                               7, 6, 3,
                                               2, 7, 4}, 3, 3);

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 4, 5,
                                              3, 6, 7,
                                              4, 7, 2}, 3, 3);

    assert(isSquareMatrix(m));

    freeMemMatrix(&m);
}

void test_AreTwoMatricesEqual() {
    matrix m1 = createMatrixFromArray((int[]) {1, 4, 5,
                                               3, 6, 7,
                                               4, 7, 2}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]) {1, 4, 5,
                                               3, 6, 7,
                                               4, 7, 2}, 3, 3);
    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isEMatrix_matrixIsE() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    assert(isEMatrix(m));

    freeMemMatrix(&m);
}

void test_isEMatrix_matrixIsNotE() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    assert(!isEMatrix(m));

    freeMemMatrix(&m);
}

void test_isEMatrix_matrixIsNotSquare() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0}, 2, 3);

    assert(!isEMatrix(m));

    freeMemMatrix(&m);
}

void test_isSymmetricMatrix_matrixIsSymmetric() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 5, 6,
                                              3, 6, 7}, 3, 3);

    assert(isSymmetricMatrix(m));

    freeMemMatrix(&m);
}

void test_isSymmetricMatrix_matrixIsNotSymmetric() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    assert(!isSymmetricMatrix(m));

    freeMemMatrix(&m);
}

void test_isSymmetricMatrix_matrixIsNotSquare() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6}, 2, 3);

    assert(!isSymmetricMatrix(m));

    freeMemMatrix(&m);
}

void test_transposeMatrix_matrixIsSquare() {
    matrix m1 = createMatrixFromArray((int[]) {1, 2, 3,
                                               4, 5, 6,
                                               7, 8, 9}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, 4, 7,
                                               2, 5, 8,
                                               3, 6, 9}, 3, 3);
    transposeMatrix(&m1);

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_transposeMatrix_matrixIsRowsMoreCols() {
    matrix m1 = createMatrixFromArray((int[]) {1, 2,
                                               3, 4,
                                               5, 6}, 3, 2);

    matrix m2 = createMatrixFromArray((int[]) {1, 3, 5,
                                               2, 4, 6}, 2, 3);
    transposeMatrix(&m1);

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_transposeMatrix_matrixIsColsMoreRows() {
    matrix m1 = createMatrixFromArray((int[]) {1, 3, 5,
                                               2, 4, 6}, 2, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, 2,
                                               3, 4,
                                               5, 6}, 3, 2);
    transposeMatrix(&m1);

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

