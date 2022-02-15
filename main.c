#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"

void test();

void test_matrix();

void test_matrix_insertionSortMatrixByCriteria();
void test_transposeMatrix();

int main() {
    test();

    return 0;
}

void test(){
    test_matrix();
}

//------------------------------TESTS MATRIX-----------------------------//

void test_matrix(){
    test_matrix_insertionSortMatrixByCriteria();
    test_transposeMatrix();
}

int countEvenNumbers(const int a[], const int n){
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (!(a[i] % 2))
            count++;

    return count;
}

int getMax(const int *row, int sizeRow){
    int maxElement = row[0];
    for (int i = 0; i < sizeRow; ++i)
        if (maxElement < row[i])
            maxElement = row[i];

    return maxElement;
}

void test_matrix_insertionSortMatrixByCriteria(){
    matrix m = getMemMatrix(3, 3);

    insertionSortMatrixByCriteria(&m, getMax, ROWS);

    //outputMatrix(m);
}

void test_transposeMatrix(){
    matrix m = getMemMatrix(3, 2);
    inputMatrix(&m);

    transposeMatrix(&m);

    outputMatrix(m);
}